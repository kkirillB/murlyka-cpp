#include "trie.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <cstdio>

Char_trie_as_map::~Char_trie_as_map(){
    for(auto x : *m){
        delete [] x.second;
    }
}

Char_trie_as_map Char_trie::as_map(){
    Char_trie_as_map t;
    t.m = new std::map<size_t,char*>();
    for(auto x : nodes_indeces){
        t.m -> insert({x,get_cstring(x)});
    }
    return t;
}

char* Char_trie::get_cstring(size_t idx){
    size_t id_len = node_buffer[idx].path_len;
    char* p = new char[id_len + 1];
    p[id_len] = 0;
    size_t current = idx;
    size_t i       = id_len-1;
    /* Поскольку idx -- индекс элемента в node_buffer, содержащего
     * последний символ вставленной строки, а каждый элемент
     * вектора node_buffer содержит поле parent, указывающее на
     * элемент с предыдущим символом строки, то для получения
     * вставленной строки, которой соответствует индекс idx, в виде
     * массива символов, нужно пройтись от элемента с индексом idx
     * к корню. При этом символы вставленной строки будут читаться
     * от её конца к началу. */
    for( ; current; current = node_buffer[current].parent){
        p[i--] = node_buffer[current].c;
    }
    return p;
}

void Char_trie::print(size_t idx){
    char* p = get_cstring(idx);
    printf("%s",p);
    delete [] p;
}

size_t Char_trie::get_length(size_t idx){
    return node_buffer[idx].path_len;
}


