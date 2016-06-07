#include "makefile_content.h"
#include "project_info.h"
#include "extension_operations.h"
#include "get_directory_content.h"
#include "intercalate.h"
#include <boost/optional.hpp>
#include <vector>
#include <string>

std::string get_compiler_string(const ParsedProjectInfo& _ppi){
  std::string result;
  result += "CPP = " + _ppi.compiler + "\n";
  result += "CXXFLAGS = " + _ppi.compiler_flags + "\n";
  return result;
}

std::string get_linker_string(const ParsedProjectInfo& _ppi){
  std::string result;
  result += "LINKER = " + _ppi.linker + "\n";
  if(!_ppi.linker_flags.empty()){
    result += "LINKERFLAGS = " + _ppi.linker_flags + "\n";
  }
  return result;
}

std::string get_bin(const ParsedProjectInfo& _ppi){
    return "BIN = " + _ppi.project.name + "\n";
}

std::string get_objects(const ParsedProjectInfo& _ppi){
  std::string result_str;	
  auto files_of_source_dir = get_directory_content(_ppi.source_dir);
  if(files_of_source_dir){
    auto source_files = sort_files_by_exts(*files_of_source_dir, _ppi.source_exts);
    std::vector<std::string> result_files;
    result_files.push_back(replaceExt(_ppi.project.main_file, "o"));
    for(auto& file : source_files){
      auto tmp_file = replaceExt(file, "o");
      if(tmp_file.compare(replaceExt(_ppi.project.main_file, "o")) != 0){
        result_files.push_back(tmp_file);
      }
    }
    result_str += "OBJ = " + intercalate(" ", result_files) + "\n";
    if(!_ppi.build_dir.empty()){
        result_str += "LINKOBJ = " + _ppi.build_dir + "/" + intercalate(" " +  _ppi.build_dir + "/", result_files) + "\n";
    }else{
      result_str += "LINKOBJ = " + intercalate(" ", result_files) + "\n";
    }
  }
  return result_str;
}

const std::string PHONY = ".PHONY: all all-before all-after clean clean-custom\n";

std::string get_includes(const ParsedProjectInfo& _ppi){
  std::string result = "";
  if(_ppi.include_dirs.empty()){
    return result += "\ngovno";
  }else{
    return result += "-I" + intercalate(" -I", _ppi.include_dirs) + "\n";
  }
}
/***********************************************************************/

std::string makefile_content(const ParsedProjectInfo& _ppi){
    std::string result_makefile;

    /*********************Variables**************************/
    result_makefile += get_compiler_string(_ppi);

    result_makefile += get_linker_string(_ppi);

    if(_ppi.source_dir.compare(".") != 0){
      for(auto& ext : _ppi.source_exts){
        result_makefile += "vpath %%." + ext + " " + _ppi.source_dir + "\n";
      }
    }
    if(!_ppi.build_dir.empty()){
      result_makefile += "vpath %%.o " + _ppi.build_dir + "\n";
      result_makefile += "vpath " + _ppi.project.name + " " + _ppi.build_dir + "\n";
    }

    result_makefile += get_objects(_ppi);

    result_makefile += get_bin(_ppi);
    result_makefile += "\n";

    /*********************Rules*******************************/
    result_makefile += PHONY;
    result_makefile += "\n";

    result_makefile += "all: all-before $(BIN) all-after\n";
    result_makefile += "\n";

    result_makefile += "clean: clean-custom\n";
	if(!_ppi.build_dir.empty()){
	  result_makefile += "\trm -f ./" + _ppi.build_dir + "/*.o\n";
	  result_makefile += "\trm -f ./" + _ppi.build_dir + "/$(BIN)\n";	
	}else{
	  result_makefile += "\trm -f ./*.o\n";
	  result_makefile += "\trm -f ./$(BIN)\n";	
	}
    result_makefile += "\n";
	

    for(auto& exts : _ppi.source_exts){
       result_makefile += "." + exts + ".o:\n";
       result_makefile += "\t$(CPP) -c $< -o $@ $(CXXFLAGS) " + get_includes(_ppi);
	   if(!_ppi.build_dir.empty()){
	     result_makefile += "\tmv $@ ./" + _ppi.build_dir + "\n"; 	   
	   }
       result_makefile += "\n";
    }
	
	
	result_makefile += "$(BIN): $(OBJ)\n";
	if(!_ppi.linker_flags.empty()){
	  result_makefile += "\t$(LINKER) -o $(BIN) $(LINKOBJ) $(LINKERFLAGS)\n";	
	}else{
	  result_makefile += "\t$(LINKER) -o $(BIN) $(LINKOBJ)\n";	
	}
    if(!_ppi.build_dir.empty()){
      result_makefile += "\tmv $(BIN) ./" + _ppi.build_dir + "\n";
    }
    result_makefile += "\n";

    return result_makefile;
}
