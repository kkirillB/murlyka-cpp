#include "project_info.h"
#include "extension_operations.h"

/* Функция, корректирующая информацию
 * о имени проекта и имени главного файла */
void correctProjectTitle(ParsedProjectInfo& ppi){
	enum Project_title_state
	{
		Projectname_not_empty_mainfile_not_empty,
		Projectname_not_empty_mainfile_empty,
		Projectname_empty_mainfile_not_empty,
		Projectname_empty_mainfile_empty
	};

	size_t project_title_state = (ppi.project.name.empty() << 1ULL)|(ppi.project.main_file.empty());
	switch(project_title_state){
		case Projectname_not_empty_mainfile_not_empty:
			break;
		case Projectname_not_empty_mainfile_empty:
			ppi.project.main_file = ppi.project.name + ".cpp";
			break;
		case Projectname_empty_mainfile_not_empty:
			ppi.project.name = splitExtension(ppi.project.main_file).first;
			break;
		case Projectname_empty_mainfile_empty:
			ppi.project.name      = "main";
			ppi.project.main_file = "main.cpp";
			break;
	}
}


void correctParsedProjectInfo(ParsedProjectInfo& ppi){
	correctProjectTitle(ppi);
	
	if(ppi.compiler.empty()){
		ppi.compiler = "g++";
	}
	if(ppi.compiler_flags.empty()){
        ppi.compiler_flags = "-std=c++14 -Wall";
	}
	if(ppi.linker.empty()){
		ppi.linker = ppi.compiler;
	}
	if(ppi.source_exts.empty()){
		ppi.source_exts.push_back("cpp");
	}
	if(ppi.source_dir.empty()){
		ppi.source_dir = ".";
	}
  	if(ppi.makefile_name.empty()){
    		ppi.makefile_name = "Makefile";
  	}
}
