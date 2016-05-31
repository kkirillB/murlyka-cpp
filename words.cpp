#include "words.h"

std::vector<std::string> words(const std::string& str){
	std::string current_word;
	std::vector<std::string> words_list;
	enum WordsState{
		SpaceChars,  NonSpaces
	};
	WordsState state = SpaceChars;
	for(char c : str){
		switch(state){
			case SpaceChars:
				if(c > ' '){
					current_word.push_back(c);
					state = NonSpaces;
				}
				break;
			case NonSpaces:
				if(c > ' '){
					current_word.push_back(c);
				}else{
					words_list.push_back(current_word);
					state = SpaceChars;
					current_word.clear();
				}
				break;	
		}
	}
	if(state == NonSpaces){
		words_list.push_back(current_word);
	}
	return words_list;
}
