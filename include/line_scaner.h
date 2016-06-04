#ifndef LINE_SCANER_H
#define LINE_SCANER_H

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <map>

#include "abstract_scaner.h"
#include "errors_and_tries.h"

enum LScan_lexem_code : unsigned short {
  None,                 Unknown,          Open_round_bracket, 
	Close_round_bracket,  Kw_project,       Kw_compiler,
	Kw_compiler_flags,    Kw_linker,        Kw_linker_flags,
	Kw_source_dir,        Kw_source_exts,   Kw_build_dir,  
	Kw_include_dirs,      Kw_makefile_name, Identifier,    
	String_literal  
};

struct LScan_lexem_info{
    LScan_lexem_code  code;
    union{
		size_t        id_name_index;
		size_t        str_lit_name_index; 
	};
};

using Token       = std::pair<LScan_lexem_info, size_t>;
using TokenVector = std::vector<Token>;

typedef std::map<std::string, LScan_lexem_code> Keyword_codes;

class Line_scaner : public Scaner<LScan_lexem_info> {
public:
    Line_scaner() = default;
    Line_scaner(Location_ptr location, Errors_and_tries_ptr et) :
        Scaner<LScan_lexem_info>(location, et) {}
    Line_scaner(const Line_scaner& orig) = default;
    virtual ~Line_scaner() = default;
    virtual LScan_lexem_info current_lexem();
    void update();
    
private:
    enum Category : unsigned short {
    Spaces,                 Other,                         Symbols_for_id_and_keyword,  
		String_literal_quotes,  String_literal_other_symbols,  Delimiters 
    };

    enum Automaton_name : unsigned short {
    A_start,          A_unknown,   A_keyword_or_id,
		A_string_literal, A_delimiters  
    };
    
    enum String_literal_states : unsigned short {
    	Quotes_state_begin,	None_quotes_state,
    	Quotes_state_end
		};
    
    Automaton_name automaton; /* текущий автомат */
    int            state; /* текущее состояние
                           * текущего автомата */

    typedef bool (Line_scaner::*Automaton_proc)();
    /* Это тип указателя на функцию--член, реализующую
     * конечный автомат, обрабатывающий лексему. Функция
     * эта должна возвращать true, если лексема ещё не
     * разобрана до конца, и false --- в противном случае. */

    typedef void (Line_scaner::*Final_proc)();
    /* А это -- тип указателя на функцию-член, выполняющую
     * необходимые действия в случае неожиданного окончания
     * лексемы. */

    static Automaton_proc procs[];
    static Final_proc     finals[];
    /* функции обработки лексем: */
    bool start_proc();		    bool unknown_proc();
		bool keyword_or_id_proc();  bool string_literal_proc();
		bool delimiters_proc();	    
    /* функции для выполнения действий в случае неожиданного
     * окончания лексемы */
    void none_final_proc();           void unknown_final_proc();
    void keyword_or_id_final_proc();  void string_literal_final_proc();
		void delimiters_final_proc();
    /* Функция, корректирующая код лексемы, скорее всего, являющейся
     * классом символов, и выводящая нужную диагностику. */
};
using Line_scaner_ptr = std::shared_ptr<Line_scaner>;

#endif
