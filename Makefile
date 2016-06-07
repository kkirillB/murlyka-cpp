CPP = g++
CXXFLAGS = -std=c++14 -Wall
LINKER = g++
LINKERFLAGS = -lboost_filesystem-mgw53-mt-s-1_60 -lboost_filesystem-mgw53-mt-sd-1_60 -lboost_system-mgw53-mt-s-1_60 -lboost_thread-mgw53-mt-sd-1_60
vpath %.cpp src
vpath %.o build
vpath murlyka-cpp build
OBJ = main.o construct_makefile.o convert_project_info.o correct_parsed_project_info.o create_makefile.o error_count.o extension_operations.o file_contents.o fsize.o get_directory_content.o get_make_info.o get_token_stream.o intercalate.o lines.o line_scaner.o makefile_content.o makefile_handler.o splitBy.o syntax_parser.o trie.o words.o
LINKOBJ = build/main.o build/construct_makefile.o build/convert_project_info.o build/correct_parsed_project_info.o build/create_makefile.o build/error_count.o build/extension_operations.o build/file_contents.o build/fsize.o build/get_directory_content.o build/get_make_info.o build/get_token_stream.o build/intercalate.o build/lines.o build/line_scaner.o build/makefile_content.o build/makefile_handler.o build/splitBy.o build/syntax_parser.o build/trie.o build/words.o
BIN = murlyka-cpp

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	rm -f ./build/*.o
	rm -f ./build/$(BIN)

.cpp.o:
	$(CPP) -c $< -o $@ $(CXXFLAGS) -Iinclude
	mv $@ ./build

$(BIN): $(OBJ)
	$(LINKER) -o $(BIN) $(LINKOBJ) $(LINKERFLAGS)
	mv $(BIN) ./build

