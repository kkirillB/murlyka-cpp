#include "file_contents.h"
#include "fsize.h"
#include <cstdio>

Contents get_contents(const char* name){
    Contents result = std::make_pair(Get_contents_return_code::Normal, "");
    FILE* fptr = fopen(name, "rb");
    if(!fptr){
        result.first = Get_contents_return_code::Impossible_open;
        return result;
    }
    long file_size = fsize(fptr);
    if(!file_size){
        return result;
    }
    char* test_text = new char[file_size + 1];
    size_t fr = fread(test_text, 1, file_size, fptr);
    if(fr < (unsigned long)file_size){
        delete [] test_text;
        result.first = Get_contents_return_code::Read_error;
        return result;
    }
    test_text[file_size] = 0;
    fclose(fptr);
    result.second = std::string(test_text);
    delete []test_text;
    return result;
}
