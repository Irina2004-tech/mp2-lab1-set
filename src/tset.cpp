// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Множество - реализация через битовые поля

#include <iostream>
#include "tbitfield.h"
#include "tset.h"

TSet::TSet(size_t mp) : bitField(1) {
    maxPower = mp;
    bitField = TBitField(mp);
}

// конструктор копирования
TSet::TSet(const TSet& s) : bitField(s.bitField) {
    maxPower = s.maxPower;
    bitField = s.bitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : bitField(bf) {
    maxPower = bf.getLength();
}

TSet::operator TBitField()
{
    return bitField;
}

size_t TSet::getMaxPower() const // получить макс. к-во эл-тов
{
    return maxPower;
}

bool TSet::isMember(const myUint elem) const // элемент множества?
{
    return bitField.getBit(elem);
}

void TSet::insElem(const myUint elem) // включение элемента множества
{
    bitField.setBit(elem);
}

void TSet::delElem(const myUint elem) // исключение элемента множества
{
    bitField.clrBit(elem);
}

// теоретико-множественные операции
TSet& TSet::operator=(const TSet& s) // присваивание
{
    maxPower = s.maxPower;
    bitField = s.bitField;
    return *this;
}

bool TSet::operator==(const TSet& s) const // сравнение
{
    if (maxPower == s.maxPower && bitField == s.bitField)
        return true;
    else
        return false;
}

bool TSet::operator!=(const TSet& s) const // сравнение
{
    if (maxPower != s.maxPower || bitField != s.bitField)
        return true;
    else
        return false;
}

TSet TSet::operator+(const TSet& s) // объединение
{
    TSet tmp(bitField | s.bitField);
    return tmp;
}

TSet TSet::operator+(const myUint elem) // объединение с элементом
{
    TSet tmp(maxPower);
    tmp.bitField.setBit(elem);
    return tmp;
}

TSet TSet::operator-(const myUint elem) // разность с элементом
{
    TSet tmp(maxPower);
    tmp.bitField.clrBit(elem);
    return tmp;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    TSet tmp(bitField & s.bitField);
    return tmp;
}

TSet TSet::operator~() // дополнение
{
    TSet tmp(maxPower);
    tmp.bitField = ~bitField;;
    return tmp;
}

// перегрузка ввода/вывода
std::istream& operator>>(std::istream& istr, TSet& s) // ввод
{
    istr >> s.bitField;
    s.maxPower = s.bitField.getLength();
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TSet& s) // вывод
{
    for (int i = 0; i < s.maxPower; i++) {
        if (s.isMember(i))
            ostr << i << " ";
    }
    return ostr;
}