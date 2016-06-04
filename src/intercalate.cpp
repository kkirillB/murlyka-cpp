#include "intercalate.h"
#include <string>
#include <vector>

std::string intercalate(const std::string& delimiter, const std::vector<std::string>& strs){
  std::string result;
  unsigned int strs_size = strs.size() - 1;
  if(!strs_size){
	return strs[strs_size];
  }
  for(ssize_t i = 0; i < strs_size; ++i){
    result += strs[i];
    result += delimiter;
  }
  result += strs[strs_size];
  return result;
}
