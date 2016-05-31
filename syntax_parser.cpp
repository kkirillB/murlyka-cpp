#include "project_info.h"
#include "abstract_scaner.h"
#include "syntax_parser.h"
#include "line_scaner.h"
#include <map>

Syntax_parser::Parser_state_proc Syntax_parser::procs[] = {
	&Syntax_parser::State_A_proc, &Syntax_parser::State_B_proc,
	&Syntax_parser::State_C_proc, &Syntax_parser::State_D_proc,
	&Syntax_parser::State_E_proc, &Syntax_parser::State_F_proc,
	&Syntax_parser::State_G_proc, &Syntax_parser::State_H_proc,
	&Syntax_parser::State_I_proc
};

Syntax_parser::Diagnostic_parser_state_proc Syntax_parser::diagnostic_procs[] = {
  &Syntax_parser::State_A_diagnostic_proc,           &Syntax_parser::State_B_or_C_or_D_diagnostic_proc,
  &Syntax_parser::State_B_or_C_or_D_diagnostic_proc, &Syntax_parser::State_B_or_C_or_D_diagnostic_proc,
  &Syntax_parser::State_E_or_F_or_G_diagnostic_proc, &Syntax_parser::State_E_or_F_or_G_diagnostic_proc,
  &Syntax_parser::State_E_or_F_or_G_diagnostic_proc, &Syntax_parser::State_H_or_I_diagnostic_proc,
  &Syntax_parser::State_H_or_I_diagnostic_proc
};

ProjectInfo Syntax_parser::compile(){
  kw_info = None;
  parser_state = State_A;
  for(auto& token : tv_){
  	lli          = token.first;
  	llc          = token.first.code;
  	current_line = token.second;
  	(this->*procs[parser_state])();
  }
	if(parser_state != State_A){
        printf("Неожиданный конец файла в строке %zu\n", current_line);
		et_->ec->increment_number_of_errors();
	}
    return project_info;
}

void Syntax_parser::State_A_proc(){
	kw_info = llc;
  switch(lexem_class(llc)){
    case Class_A:
      parser_state = State_B;
      break;
    case Class_B:
      parser_state = State_C;
      break;
    case Class_C:
      parser_state = State_D;
      break;
    default:
      diagnostic();
      break;
  }
}

void Syntax_parser::State_B_proc(){
	if(lexem_class(llc) == Class_K){
		parser_state = State_E;
	}else{
    diagnostic();
	}
}

void Syntax_parser::State_C_proc(){
	if(lexem_class(llc) == Class_K){
		parser_state = State_F;
	}else{
    diagnostic();
	}
}

void Syntax_parser::State_D_proc(){
	if(lexem_class(llc) == Class_K){
		parser_state = State_G;
	}else{
    diagnostic();
	}
}

void Syntax_parser::State_E_proc(){
	if(lexem_class(llc) == Class_M){
    set_project_info();
		parser_state = State_H;
	}else{
    diagnostic();
	}
}

void Syntax_parser::State_F_proc(){
	if(lexem_class(llc) == Class_M){
    set_project_info();
		parser_state = State_I;
	}else{
    diagnostic();
	}
}

void Syntax_parser::State_G_proc(){
	if(lexem_class(llc) == Class_N){
    set_project_info();
		parser_state = State_I;
	}else{
    diagnostic();
	}
}

void Syntax_parser::State_H_proc(){
  switch (lexem_class(llc)){
    case Class_N:
      project_info.project.main_file =
      std::string(et_->str_lit_trie->get_cstring(lli.str_lit_name_index));
      parser_state = State_I;
      break;
    case Class_L:
      parser_state = State_A;
    default:
      diagnostic();
      break;
  }
}

void Syntax_parser::State_I_proc(){
	if(lexem_class(llc) == Class_L){
		parser_state = State_A;
	}else{
    diagnostic();
	}
}

Syntax_parser::Lexem_clases Syntax_parser::lexem_class(const LScan_lexem_code lslc){
	const static std::map<LScan_lexem_code, Lexem_clases> class_belongs =
	{
	{Kw_project,          Class_A},
	{Kw_compiler,         Class_B},
	{Kw_linker,           Class_B},
	{Kw_makefile_name,    Class_B},
	{Kw_compiler_flags,   Class_C},
	{Kw_linker_flags,     Class_C},
	{Kw_source_dir,       Class_C},
	{Kw_source_exts,      Class_C},
	{Kw_build_dir,        Class_C},
	{Kw_include_dirs,     Class_C},
	{Open_round_bracket,  Class_K},
	{Close_round_bracket, Class_L},
	{Identifier,          Class_M},
	{String_literal,      Class_N}
	};
	
	auto it = class_belongs.find(lslc);
	if(it != class_belongs.end()){
		return it->second;
	}else{
		return Class_A;
	}
}

void Syntax_parser::diagnostic(){
  (this->*diagnostic_procs[parser_state])();
	//et_->ec->increment_number_of_errors();
	return;
}

void Syntax_parser::State_A_diagnostic_proc(){
  printf("В строке %zu ожидается ключевое слово\n",
    current_line);
  switch(lexem_class(llc)){
    case Class_K:
      parser_state = State_E;
      break;
    case Class_M:
      parser_state = State_H;
      set_project_info();
      break;
    case Class_L:
      parser_state = State_A;
      break;
    case Class_N:
      parser_state = State_I;
      project_info.project.main_file =
      std::string(et_->str_lit_trie->get_cstring(lli.str_lit_name_index));
      break;
  }
  return;
}

void Syntax_parser::State_B_or_C_or_D_diagnostic_proc(){
  printf("В строке %zu ожидается открывающаяся круглая скобка\n",
    current_line);
  switch(lexem_class(llc)){
    case Class_A:
      parser_state = State_B;
      break;
    case Class_B:
      parser_state = State_C;
      break;
    case Class_C:
      parser_state = State_D;
      break;
    case Class_M:
      if(parser_state == State_B){
        set_project_info();
        parser_state = State_H;
      }else{
        if(parser_state == State_C)
          set_project_info();
        parser_state = State_I;
      }
      break;
    case Class_L:
      parser_state = State_A;
      break;
    case Class_N:
      if(parser_state != State_C)
        set_project_info();
      parser_state = State_I;
      break;
  }
  return;
}

void Syntax_parser::State_E_or_F_or_G_diagnostic_proc(){
  printf("В строке %zu ожидается идентификатор или строковой литерал\n",
    current_line);
  switch(lexem_class(llc)){
    case Class_A:
      parser_state = State_B;
      break;
    case Class_B:
      parser_state = State_C;
      break;
    case Class_C:
      parser_state = State_D;
      break;
    case Class_M:
      parser_state = State_I;
      break;
    case Class_L:
      parser_state = State_A;
      break;
    case Class_N:
      if(parser_state == State_E)
        set_project_info();
      parser_state = State_I;
      break;
  }
  return;
}

void Syntax_parser::State_H_or_I_diagnostic_proc(){
  printf("В строке %zu ожидается закрывающаяся круглая скобка\n",
    current_line);
  switch(lexem_class(lli.code)){
    case Class_A:
      parser_state = State_B;
      break;
    case Class_B:
      parser_state = State_C;
      break;
    case Class_C:
      parser_state = State_D;
      break;
    case Class_K: Class_M:
      parser_state = State_A;
      break;
    case Class_N:
      parser_state = State_I;
      break;
  }
  return;
}


void Syntax_parser::set_project_info(){
	switch(kw_info){
		case Kw_project:
      project_info.project.name =
			std::string(et_->ids_trie->get_cstring(lli.id_name_index));
			break;
		case Kw_compiler:
      project_info.compiler =
			std::string(et_->ids_trie->get_cstring(lli.id_name_index));
			break;
		case Kw_linker:
      project_info.linker =
			std::string(et_->ids_trie->get_cstring(lli.id_name_index));	
			break;
		case Kw_makefile_name:
      project_info.makefile_name =
			std::string(et_->ids_trie->get_cstring(lli.id_name_index));
			break;
		case Kw_compiler_flags:
      project_info.compiler_flags =
			std::string(et_->str_lit_trie->get_cstring(lli.str_lit_name_index));
			break;
		case Kw_linker_flags:
      project_info.linker_flags =
			std::string(et_->str_lit_trie->get_cstring(lli.str_lit_name_index));
			break;
		case Kw_source_dir:
      project_info.source_dir =
			std::string(et_->str_lit_trie->get_cstring(lli.str_lit_name_index));
			break;
		case Kw_source_exts:
      project_info.source_exts =
			std::string(et_->str_lit_trie->get_cstring(lli.str_lit_name_index));
			break;
		case Kw_build_dir:
      project_info.build_dir =
			std::string(et_->str_lit_trie->get_cstring(lli.str_lit_name_index));
			break;
		case Kw_include_dirs:
      project_info.include_dirs =
			std::string(et_->str_lit_trie->get_cstring(lli.str_lit_name_index));
			break;							
	}
	return;
}

