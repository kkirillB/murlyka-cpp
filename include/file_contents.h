#ifndef FILE_CONTENTS_H
#define FILE_CONTENTS_H
#include <string>
#include <utility>

/** Коды возврата из функции get_contents. */
enum class Get_contents_return_code{
    Normal,           ///< Этот код означает, что всё прошло успешно.
    Impossible_open,  ///< Этот код означает, что не удалось открыть файл.
    Read_error        ///< Этот код означает, что во время чтения файла произошла ошибка.
};

typedef std::pair<Get_contents_return_code, std::string> Contents;

/**
   Возвращает всё содержимое файла с заданным именем.
   \param [in] name --- имя читаемого файла
   \returns Пару из кода возврата (первая компонента) и значения, имеющего 
тип std::string (вторая компонента). При возникновении ошибки вторая компонента
возвращаемого значения представляет собой пустую строку.
*/
Contents get_contents(const char* name);
#endif
