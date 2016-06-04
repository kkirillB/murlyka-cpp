#ifndef CREATE_MAKEFILE_H
#define CREATE_MAKEFILE_H

#include "project_info.h"

/* Создает Makefile на основе информации,
 * полученной из структуры ParsedProjectInfo*/
void create_makefile(const ParsedProjectInfo& _ppi);

#endif
