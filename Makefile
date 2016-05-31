CPP = g++
CXXFLAGS = -std=c++14 -Wall -Wextra
LINKER = g++
LINKERFLAGS = -o Course 
OBJ = main.o get_directory_content.o lines.o file_contents.o syntax_parser.o construct_makefile.o get_make_info.o splitBy.o convert_project_info.o line_scaner.o create_makefile.o words.o correct_parsed_project_info.o intercalate.o makefile_handler.o makefile_content.o get_token_stream.o fsize.o error_count.o extension_operations.o trie.o
LINKOBJ = main.o get_directory_content.o lines.o file_contents.o syntax_parser.o construct_makefile.o get_make_info.o splitBy.o convert_project_info.o line_scaner.o create_makefile.o words.o correct_parsed_project_info.o intercalate.o makefile_handler.o makefile_content.o get_token_stream.o fsize.o error_count.o extension_operations.o trie.o
BIN = Course.exe

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	rm -f $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(LINKER) -o $(BIN) $(LINKOBJ) -lboost_filesystem-mgw53-mt-s-1_60 -lboost_filesystem-mgw53-mt-sd-1_60 -lboost_system-mgw53-mt-s-1_60 -lboost_thread-mgw53-mt-sd-1_60

.cpp.o:
	$(CPP) -c $< -o $@ $(CXXFLAGS)

