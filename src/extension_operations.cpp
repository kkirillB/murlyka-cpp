#include "extension_operations.h"
#include <string>
#include <vector>
#include <utility>

std::pair<std::string, std::string> splitExtension(const std::string& st){
  int pos = st.rfind(".");
  if(pos < 0){
    return std::make_pair(st, "");
  }
  if(pos == 0){
    return std::make_pair("", st);
  }
  return std::make_pair(st.substr(0, pos), st.substr(pos, st.size() - 1));
}

std::string tail(const std::string& s){
  if(s.compare("") == 0)
    return "";

  return s.substr(1, s.size() - 1);
}

std::string replaceExt(const std::string& file, const std::string& ext){
  if(ext[0] == '.'){
    return splitExtension(file).first + ext;
  }
  return splitExtension(file).first + "." + ext;
}

std::vector<std::string> sort_files_by_exts(const std::vector<std::string>& files, const std::vector<std::string>& exts){
  std::vector<std::string> result_files;
  for(auto& file : files){
    for(auto& ext : exts){
      if(tail(splitExtension(file).second).compare(ext) == 0)
        result_files.push_back(file);
    }
  }
  return result_files;
}
