#include "makefile_handler.h"
#include <stdio.h>
#include <clocale>

int main(int argc, char** argv) {
	#if (defined(_WIN64) || defined(_WIN32))
    	setlocale(LC_CTYPE, "rus");
	#endif
    if(1 == argc){
      printf("Не задан обрабатываемый файл.");
    }else{
    	for (int i = 1; i < argc; ++i){
    		makefile_handler(argv[i]);
      }
    }
    return 0;
}
