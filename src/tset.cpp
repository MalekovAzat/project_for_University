// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (this != &s)
	{
		MaxPower = s.MaxPower;
		BitField = s.BitField;

	}
	return *this;}

int TSet::operator==(const TSet &s) const // сравнение
{
	int n = BitField.operator==(s.BitField);

	return n;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet tmp(s.MaxPower);

	tmp.BitField = BitField | s.BitField;

	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	InsElem(Elem);

	return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	DelElem(Elem);

	return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet tmp(s.MaxPower);

	tmp.BitField = BitField & s.BitField;

	return tmp;
}

TSet TSet::operator~(void) // дополнение
{
	BitField = ~BitField;

	return *this;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int x;

	for (int i = 0; i < s.MaxPower; i++)
	{
		cin >> x;

		s.InsElem(x);
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.MaxPower; i++)
		if (s.IsMember(i) == 1)
			cout << i;

	return ostr;
}
