#include <string>
#include <vector>

std::vector<std::string> splitBy(const char e, const std::string s){
	std::vector<std::string> splited_str;
	std::string str;
    for (const auto& c : s){
		if(c != e){
			str += c;
		}else{
			splited_str.push_back(str);
			str.clear();
		}
	}
    //splited_str.push_back(str);
	return splited_str;
}
