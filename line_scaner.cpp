#include "line_scaner.h"
#include "abstract_scaner.h"
#include "belongs.h"
#include <cstdlib>
#include <cstdio>

static const unsigned short categories_table[256]={
   1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
   1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
  17,   16,   24,   16,   16,   16,   16,    2,   48,   48,   16,   20,   16,   20,   20,   16,
  20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   16,   16,   16,   16,   16,   16,
  16,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,
  20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   16,   16,   16,   16,   20,
   2,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,
  20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   16,   16,   16,   16,    2,
   2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
   2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
   2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
   2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
   2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
   2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
   2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
   2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2
};

static const Keyword_codes keywords = {
	{"project",        Kw_project}, 
	{"compiler",       Kw_compiler},
	{"compiler_flags", Kw_compiler_flags},
	{"linker",         Kw_linker},
	{"linker_flags",   Kw_linker_flags},
	{"source_dir",     Kw_source_dir},
	{"source_exts",    Kw_source_exts},
	{"build_dir",      Kw_build_dir},
	{"include_dirs",   Kw_include_dirs},
	{"makefile_name",  Kw_makefile_name}
};

Line_scaner::Automaton_proc Line_scaner::procs[] = {
  &Line_scaner::start_proc,         &Line_scaner::unknown_proc, 
	&Line_scaner::keyword_or_id_proc, &Line_scaner::string_literal_proc,
	&Line_scaner::delimiters_proc
};

Line_scaner::Final_proc Line_scaner::finals[] = {
    &Line_scaner::none_final_proc,
    &Line_scaner::unknown_final_proc,  
	  &Line_scaner::keyword_or_id_final_proc,
    &Line_scaner::string_literal_final_proc,
    &Line_scaner::delimiters_final_proc
};

void Line_scaner::update(){
	lexem_begin = loc->pcurrent_char;
	lexem_begin_line = loc->current_line;
}

LScan_lexem_info Line_scaner::current_lexem(){
    automaton = A_start; 
	  token.code = None;
    lexem_begin = loc->pcurrent_char;
    bool t = true;
    while((ch = *(loc->pcurrent_char)++)){
        char_categories = categories_table[ch];
        t = (this->*procs[automaton])();
        if(!t){
            /* Сюда попадаем, лишь если лексема уже прочитана.
             * При этом текущим автоматом уже прочитан символ,
             * идущий сразу за концом прочитанной лексемы, на
             * основании этого символа принято решение о том,
             * что лексема прочитана, и совершён переход к
             * следующему за ним символу. Поэтому для того,
             * чтобы не пропустить первый символ следующей
             * лексемы, нужно уменьшить на единицу указатель
             * pcurrent_char. */
            (loc->pcurrent_char)--;
						if(Identifier == token.code){
                /* Если текущая лексема является идентификатором,
                 * то этот идентификатор нужно записать в таблицу
                 * идентификаторов. */
              token.id_name_index      = ids->insert(buffer);
            }else if(String_literal == token.code){
            	token.str_lit_name_index = str_lit->insert(buffer);
			      }	
            return token;
        }
    }
    /* Здесь можем оказаться, только если уже прочли весь
     * обрабатываемый текст. При этом указатель на текущий символ
     * указывает на байт, который находится сразу же после нулевого
     * символа, являющегося признаком конца текста. Чтобы не выйти
     * при последующих вызовах за пределы текста, нужно перейти
     * обратно к нулевому символу. */
    (loc->pcurrent_char)--;
    /* Далее, поскольку мы находимся здесь, то конец текущей
     * лексемы (возможно, неожиданный) ещё не обработан. Надо эту
     * обработку выполнить, и, возможно, вывести какую-то
     * диагностику.*/
    (this->*finals[automaton])();
    return token;
}

bool Line_scaner::start_proc() {
	buffer.clear();
    bool t = true;
    state = -1;
    if(belongs(Spaces, char_categories)){
        return t;
    }
    if(belongs(Delimiters, char_categories)){
        automaton = A_delimiters; 
        (loc->pcurrent_char)--;
    }else if(belongs(Symbols_for_id_and_keyword, char_categories)){
	      automaton = A_keyword_or_id;	 
        buffer += ch;
	}else if(belongs(String_literal_quotes, char_categories)){
        automaton = A_string_literal;	
				token.code = String_literal;	
        (loc->pcurrent_char)--;
	}else{
        printf("Нераспознаваемая лексема в строке %zu.\n", 
				loc->current_line);
		en->increment_number_of_errors();
		automaton = A_unknown;
		token.code = Unknown;
	}
    return t;
}

bool Line_scaner::unknown_proc(){
    return belongs(Other, char_categories);
}

bool Line_scaner::keyword_or_id_proc(){
    if(belongs(Symbols_for_id_and_keyword, char_categories)){	
        buffer += ch;
        return true;
    }else{
    	auto it = keywords.find(buffer);
    	if(it == keywords.end()){
    		token.code = Identifier;
		}else{
			token.code = it->second;
		}
	}
    return false;
}

bool Line_scaner::string_literal_proc(){
	bool t = false;
	if (state == -1) {
		state = 0;	
		return true;
	}
	switch(state){
		case Quotes_state_begin :
			if(belongs(String_literal_other_symbols, char_categories)){
				state = None_quotes_state;			
				t = true;
			}else if(belongs(String_literal_quotes, char_categories)){
				state = Quotes_state_end;	
				t = true;
			}else{
				printf("В строке %zu ожилаются кавычки или другие символы строкового литерала.\n", 
						loc->current_line);					
				en->increment_number_of_errors();
				return false;
			}
			buffer += ch;
			break;
		
		case None_quotes_state :
			if (belongs(String_literal_quotes, char_categories)){
				state = Quotes_state_end;
				t = true;
			}else if(belongs(String_literal_other_symbols, char_categories)){
				state = None_quotes_state;
				t = true;
			}else{
				printf("В строке %zu ожилаются кавычки.\n",
						loc->current_line);					
				en->increment_number_of_errors();
				return false;
			}
			buffer += ch; 
			break;
		
		case Quotes_state_end :
			if (belongs(String_literal_quotes, char_categories)){
				state = Quotes_state_begin;	
				t = true;
			}else{
				buffer.pop_back();
			}
		break;		
	}
	return t;
}

bool Line_scaner::delimiters_proc(){
	switch((char)ch){
		case '(':
			token.code = Open_round_bracket;
			break;				
		case ')':
			token.code = Close_round_bracket;
			break;					
	}
	(loc->pcurrent_char)++;
	return false;	
}


void Line_scaner::none_final_proc(){
    /* Данная подпрограмма будет вызвана, если по прочтении
     * входного текста оказались в автомате A_start. Тогда
     * ничего делать не нужно. */
}

void Line_scaner::unknown_final_proc(){
    /* Данная подпрограмма будет вызвана, если по прочтении
     * входного текста оказались в автомате A_unknown. Тогда
     * ничего делать не нужно. */
}

void Line_scaner::keyword_or_id_final_proc(){
    	auto it = keywords.find(buffer);
    	if(it == keywords.end()){
    		token.code = Identifier;
		}else{
			token.code = it->second;
		}	
}

void Line_scaner::string_literal_final_proc(){
	if(state == 2){
		buffer.pop_back();
		token.str_lit_name_index = str_lit -> insert(buffer);
	}else{
		printf("В строке %zu ожилаются кавычки или другие символы строкового литерала.\n",
				loc->current_line);					
		en->increment_number_of_errors();	
	}
}

void Line_scaner::delimiters_final_proc(){
	switch((char)ch){
		case '(':
			token.code = Open_round_bracket;
			break;				
		case ')':
			token.code = Close_round_bracket;
			break;					
	}
}

