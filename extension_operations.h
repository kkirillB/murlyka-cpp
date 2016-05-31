#ifndef EXTENSION_OPERATIONS_H
#define EXTENSION_OPERATIONS_H

#include <string>
#include <vector>
#include <utility>

/* Принимает на вход имя файла и возвращает
 * пару, разделяющую имя файла и его расширение */
std::pair<std::string, std::string> splitExtension(const std::string& st);

/* Принимает на вход список файлов и список расширений.
 * Возвращает список файлов, отсортированный по типам списка расширений */
std::vector<std::string> sort_files_by_exts(const std::vector<std::string>& files, const std::vector<std::string>& exts);

/* Заменяет текущее расширение файла на расширение,
 * поданное на вход */
std::string replaceExt(const std::string& file, const std::string& ext);

/* Возвращает имя расширения без точки
 * Пример: ".exe" -> "exe" */
std::string tail(const std::string& s);
#endif // EXTENSION_OPERATIONS_H
