#ifndef PROJECT_INFO_H
#define PROJECT_INFO_H
#include <string>
#include <vector>

struct ProjectTitle{
	std::string name;
	std::string main_file;
	ProjectTitle()  = default;
	~ProjectTitle() = default;
};

struct ProjectInfo{
	ProjectTitle project;
	std::string  compiler;
	std::string  compiler_flags;
	std::string  linker;
	std::string  linker_flags;
	std::string  source_dir;
	std::string  source_exts;
	std::string  build_dir;
	std::string  include_dirs;
	std::string  makefile_name;
	ProjectInfo()  = default;
	~ProjectInfo() = default;
};

struct ParsedProjectInfo{
	ProjectTitle             project;
	std::string              compiler;
	std::string              compiler_flags;
	std::string              linker;
	std::string              linker_flags;
	std::string              source_dir;
	std::vector<std::string> source_exts;
	std::string              build_dir;
	std::vector<std::string> include_dirs;
	std::string              makefile_name;
	ParsedProjectInfo()  = default;
	~ParsedProjectInfo() = default;	
};

#endif
