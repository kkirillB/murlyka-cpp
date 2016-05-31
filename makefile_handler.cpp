#include <cstdio>
#include "makefile_handler.h"
#include "file_contents.h"
#include "construct_makefile.h"

void makefile_handler(const char* file){
	Contents content = get_contents(file);	
	switch(content.first){
    case Get_contents_return_code::Normal:
      construct_makefile(content.second);
			break;
		case Get_contents_return_code::Impossible_open:
			printf("Невозможно открыть файл %s\n", file);
			return;
		case Get_contents_return_code::Read_error:
			printf("Во время чтения файла %s возникла ошибка\n", file);
			return;		
	}
}
