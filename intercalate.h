#ifndef INTERCALATE_H
#define INTERCALATE_H

#include <string>
#include <vector>

/* На вход подается разделитель и список строк.
 * Возвращает строку из списка строк strs,
 * разделенных разделителем delimiter */
std::string intercalate(const std::string& delimiter, const std::vector<std::string>& strs);

#endif // INTERCALATE_H
