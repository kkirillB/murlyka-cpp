#ifndef SYNTAX_PARSER_H
#define SYNTAX_PARSER_H

#include "errors_and_tries.h"
#include "line_scaner.h"
#include "project_info.h"

#include <memory>

class Syntax_parser{
public:
    Syntax_parser(const TokenVector& tv, Errors_and_tries_ptr et) :
        et_(et), tv_(tv) {}
    Syntax_parser() = default;
    Syntax_parser(const Syntax_parser& orig) = default;
    ~Syntax_parser(){}
    
	/*Функция, запускающая разбор грамматики языка 
	 *и выводящая результат*/
    ProjectInfo compile();
private:
    Errors_and_tries_ptr et_;
    TokenVector          tv_;
    LScan_lexem_info     lli;
    LScan_lexem_code     llc;
    size_t               current_line;
    LScan_lexem_code     kw_info;
    ProjectInfo         project_info;
    
    /*Ключевые слова нашего языка были разбиты 
	на классы:
	A - project;
	B - compiler, linker, makefile_name;
	C - compiler_flags, linker_flags,
		source_dir, source_exts,
		build_dir, include_dirs;
	K - open_round_bracket;
	L - close_round_bracket;
	M - Identifier;
	N - String_literal*/
  enum Lexem_clases{
    	Class_A,  Class_B,  Class_C,
    	Class_K,  Class_L,  Class_M,
    	Class_N
	};
	/*Состояния ДКА, описывающего нашу грамматику*/
	enum Parser_states{
		State_A,  State_B,  State_C,
		State_D,  State_E,  State_F,
		State_G,  State_H,  State_I
	};
	
	Parser_states parser_state;
	
	typedef void (Syntax_parser::*Parser_state_proc)();

	static Parser_state_proc procs[];
	
	void State_A_proc();
	void State_B_proc();
	void State_C_proc();
	void State_D_proc();
	void State_E_proc();
	void State_F_proc();
	void State_G_proc();
	void State_H_proc();
	void State_I_proc();


  typedef void (Syntax_parser::*Diagnostic_parser_state_proc)();

  static Diagnostic_parser_state_proc diagnostic_procs[];

  void State_A_diagnostic_proc();
  void State_B_or_C_or_D_diagnostic_proc();
  void State_E_or_F_or_G_diagnostic_proc();
  void State_H_or_I_diagnostic_proc();

	/*Функция определяет, какому классу принадлежит текущая лексема*/
	Lexem_clases lexem_class(const LScan_lexem_code lslc);
	/*Функция выводит диагностику при неправильном вводе*/
  void diagnostic();
	/*Функция заполняет информацией структуру ProjectInfo*/
  void set_project_info();
};

using Syntax_parser_ptr = std::shared_ptr<Syntax_parser>;

#endif
