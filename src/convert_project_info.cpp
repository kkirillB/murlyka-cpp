#include "convert_project_info.h"
#include "project_info.h"
#include "words.h"
#include "splitBy.h"

ParsedProjectInfo convert_project_info(const ProjectInfo &_pi){
  ParsedProjectInfo ppi;
	ppi.project.name      = _pi.project.name;
	ppi.project.main_file = _pi.project.main_file;
	ppi.compiler          = _pi.compiler;
	ppi.compiler_flags    = _pi.compiler_flags;
	ppi.linker            = _pi.linker;
	ppi.linker_flags      = _pi.linker_flags;
	ppi.source_dir        = _pi.source_dir;
	ppi.source_exts       =  words(_pi.source_exts);
	ppi.build_dir         = _pi.build_dir;
	ppi.include_dirs      = splitBy(';', _pi.include_dirs);
	ppi.makefile_name     = _pi.makefile_name;
  return ppi;
}
