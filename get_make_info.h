#ifndef GET_MAKE_INFO
#define GET_MAKE_INFO

#include "boost/optional.hpp"
#include "project_info.h"
#include <string>

/*Возвращает информацию о проекте. Либо boost::none при ошибке.*/
boost::optional<ProjectInfo> getMakeInfo(const std::string& txt);

#endif
