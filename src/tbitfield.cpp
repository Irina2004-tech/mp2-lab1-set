// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Битовое поле

#include <limits>
#include <iostream>
#include "tbitfield.h"

TBitField::TBitField(size_t len)

{
    bitLen = len;
    if (len % (sizeof(uint) * 8) != 0)
        memLen = (len / (sizeof(uint) * 8) + 1);
    else
        memLen = (len / (sizeof(uint) * 8));
    pMem = new uint[memLen];
    for (int i = 0; i < memLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new uint[memLen];
    for (int i = 0; i < memLen; i++)
        pMem[i] = bf.pMem[i];
}

size_t TBitField::getIndex(const size_t n) const  // индекс в pМем для бита n
{
    if ((n <= bitLen) && (n >= 0))
        return (n % (8 * sizeof(uint)));
    else
        throw "error";

}

uint TBitField::getMask(const size_t n) const // битовая маска для бита n
{
    if ((n <= bitLen) && (n >= 0))
        return ~(1 << n);
    else
        throw "error";
}

// доступ к битам битового поля
uint TBitField::getLength() const // получить длину (к-во битов)
{
    return bitLen;
}

size_t TBitField::getNumBytes() const // получить количество байт выделенной памяти
{
    return memLen * sizeof(uint);
}

void TBitField::setBit(const size_t n) // установить бит
{
    if ((n <= bitLen) && (n >= 0))
        pMem[n / (8 * sizeof(uint))] |= ~getMask(getIndex(n));
    else
        throw "error";
}

void TBitField::clrBit(const size_t n) // очистить бит
{
    if ((n <= bitLen) && (n >= 0))
        pMem[n / (8 * sizeof(uint))] &= getMask(getIndex(n));
    else
        throw "error";

}

bool TBitField::getBit(const size_t n) const // получить значение бита
{
    uint tmp1 = pMem[n / (8 * sizeof(uint))];
    uint tmp2 = ~getMask(getIndex(n));
    if (tmp1 & tmp2)
        return true;
    else
        return false;

}

// битовые операции
TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    bitLen = bf.bitLen;
    if (memLen != bf.memLen) {
        memLen = bf.memLen;
        if (pMem != 0)
            delete[]pMem;
        pMem = new uint[memLen];
    }
    for (int i = 0; i < memLen; i++)
        pMem[i] = bf.pMem[i];

    return *this;
}

bool TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (bitLen != bf.bitLen)
        return false;
    else
        for (int i = 0; i < memLen; i++)
            if (pMem[i] != bf.pMem[i]) {
                return false;
                break;
            }
    return true;
}

bool TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return !(*this == bf);

    /*if (bitLen != bf.bitLen)
        return true;
    else
        for (int i = 0; i < memLen; i++)
            if (pMem[i] != bf.pMem[i]) {
                return true;
                break;
            }
    return false;*/
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    int len = bitLen;
    if (bf.bitLen > len)
        len = bf.bitLen;
    TBitField tmp(len);
    for (int i = 0; i < memLen; i++)
        tmp.pMem[i] = pMem[i];
    for (int i = 0; i < bf.memLen; i++)
        tmp.pMem[i] |= bf.pMem[i];
    return tmp;

}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int len = bitLen;
    if (bf.bitLen > len)
        len = bf.bitLen;
    TBitField tmp(len);
    for (int i = 0; i < memLen; i++)
        tmp.pMem[i] = pMem[i];
    for (int i = 0; i < bf.memLen; i++)
        tmp.pMem[i] &= bf.pMem[i];
    return tmp;
}

TBitField TBitField::operator~() // отрицание
{
    TBitField tmp(bitLen);
    for (int i = 0; i < bitLen; i++)
        if (!getBit(i))
            tmp.setBit(i);
        else
            tmp.clrBit(i);
    return tmp;
}

TBitField::~TBitField()
{
    delete[]pMem;
}

// ввод/вывод
std::istream& operator>>(std::istream& istr, TBitField& bf) // ввод
{
    char ch;
    istr >> ch;
    int i = 1;
    while ((ch == '0' || ch == '1') && (i < bf.bitLen)) {
        istr >> ch;
        if (ch == '0')
            bf.clrBit(i);
        else
            bf.setBit(i);
        i++;
        istr >> ch;
    }
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TBitField& bf) // вывод
{
    int len = bf.getLength();
    for (int i = 0; i < len; i++)
        if (bf.getBit(i))
            ostr << "1";
        else
            ostr << "0";
    return ostr;
}
