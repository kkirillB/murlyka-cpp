#include "construct_makefile.h"
#include "project_info.h"
#include "get_make_info.h"
#include "convert_project_info.h"
#include "correct_parsed_project_info.h"
#include "create_makefile.h"
#include <boost/optional.hpp>
#include <string>

void construct_makefile(std::string info){
  boost::optional<ProjectInfo> project_info;
  ParsedProjectInfo            parsed_project_info;

  project_info = getMakeInfo(info);
  if(project_info){
    parsed_project_info = convert_project_info(*project_info);
    correctParsedProjectInfo(parsed_project_info);
    create_makefile(parsed_project_info);
  }
}
