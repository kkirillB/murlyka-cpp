#include "project_info.h"
#include "makefile_content.h"
#include <string>
#include <cstdio>

void create_makefile(const ParsedProjectInfo& _ppi){
  FILE* pFile;
  pFile = fopen(_ppi.makefile_name.c_str(), "w");
  if (!pFile){
    printf("Can't open file %s", _ppi.makefile_name.c_str());
    fclose (pFile);
    return;
  }
  fprintf(pFile, makefile_content(_ppi).c_str());
  fclose (pFile);
}




