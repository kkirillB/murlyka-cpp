#ifndef MAKEFILE_CONTENT_H
#define MAKEFILE_CONTENT_H

#include "project_info.h"
#include <string>
/* Возвращает строку, состоящую из содержимого
 * Makefile'а */
std::string makefile_content(const ParsedProjectInfo& _ppi);

#endif // MAKEFILE_CONTENT_H
