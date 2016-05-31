#ifndef BELONGS_H
#define BELONGS_H
/* Данная функция проверяет, принадлежит ли элемент element
 * множеству s. При этом считаем, что множество s состоит из
 * не более чем 64 элементов, так что в качестве внутреннего
 * представления множества используется тип unsigned long long.
 * Если бит с номером i внутреннего представления равен 1,
 * то элемент i принадлежит множеству, иначе --- не принадлежит. */
inline unsigned long long belongs(unsigned long long element,
                                  unsigned long long s){
  return s & (1ULL << element);
}
#endif
