#ifndef ERROR_COUNT_H
#define	ERROR_COUNT_H
/*  Класс для подсчета количества ошибок. */
class Error_count {
public:
    Error_count() : number_of_errors(0) {}
    void increment_number_of_errors();
    void print();
    int get_number_of_errors();
private:
    int number_of_errors;
};
#endif


