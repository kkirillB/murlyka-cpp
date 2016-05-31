#ifndef GET_DIRECTORY_CONTENT_H
#define GET_DIRECTORY_CONTENT_H

#include <boost/optional.hpp>
#include <string>
#include <vector>

/* Возвращает список файлов директории, поданной на вход,
 * в удачном случае. В неудачном: boost::none */
boost::optional<std::vector<std::string>> get_directory_content(const std::string& dir);

#endif // GET_DIRECTORY_CONTENT_H
