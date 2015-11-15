// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) //: BitField(-1)
{
	MaxPower=mp;
	BitField=TBitField(mp);
}

// конструктор копирования
TSet::TSet(const TSet &s) // : BitField(-1)
{
	MaxPower=s.MaxPower;
	BitField=TBitField(MaxPower);
	for (int i=0;i<MaxPower;i++)
	{
		if (s.BitField.GetBit(i))
		{
			BitField.SetBit(i);
		}
	}
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) //: BitField(-1)
{
	MaxPower=bf.GetLength();
	BitField=TBitField(bf);
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
    if (Elem<0 || Elem>MaxPower)
		return 0;
	else 
		return BitField.GetBit(Elem);
}
///////////////////////////////////////////////////////// ВОПРОС!!!
void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem<0 || Elem>MaxPower)
	{
	cout << "can't add" << endl;  //задать вопросик
	throw "error!";
	}
	else 
		BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem<0 || Elem>MaxPower)
		cout<<"can't delete"<<endl;
	else 
		BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower=s.MaxPower;
	BitField=TBitField(MaxPower);
	for (int i=0;i<MaxPower;i++)
	{
		if (s.BitField.GetBit(i))
		{
			BitField.SetBit(i);
		}
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower!=s.MaxPower)
		return 0;
	for (int i=0;i<MaxPower;i++)
	{
		if (BitField.GetBit(i)!=s.BitField.GetBit(i))
			return 0;
	}
	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower!=s.MaxPower)
		return 1;
	for (int i=0;i<MaxPower;i++)
	{
		if (BitField.GetBit(i)!=s.BitField.GetBit(i))
			return 1;
	}
	return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int max=MaxPower>s.MaxPower?MaxPower:s.MaxPower;
	TSet result(max);
	for (int i=0;i<MaxPower;i++)
	{
		if (BitField.GetBit(i))
			result.InsElem(i);
	}
	for (int i=0;i<s.MaxPower;i++)
	{
		if (s.BitField.GetBit(i))
			result.InsElem(i);
	}
	return result;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet result(*this);
	result.InsElem(Elem);
	return result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet result(*this);
	result.DelElem(Elem);
	return result;
}
//////////////////////////////////////вопрос!!!
TSet TSet::operator*(const TSet &s) // пересечение
{
	/*int min=MaxPower<s.MaxPower?MaxPower:s.MaxPower;
	TSet result(min);
		for (int i=0;i<min;i++)
		{
			if (BitField.GetBit(i) && s.BitField.GetBit(i))
			{
				result.InsElem(i);
			}
		}
		return result;*/
	//TSet result(BitField & s.BitField);
	return (BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
	TSet result(MaxPower);
	for (int i=0;i<MaxPower;i++)
	{
		if (!BitField.GetBit(i))
		{
			result.InsElem(i);
		}
	}
	return result;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	cout<<"enter maxpower ";
	istr>>s.MaxPower;
	s.BitField=TBitField(s.MaxPower);
	while (1)
	{
		int x;
		istr>>x;
		if (x<0) break;
		s.InsElem(x);
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i=0;i<s.MaxPower;i++)
	{
		if (s.BitField.GetBit(i))
			ostr<<i<<" ";
	}
	ostr<<endl;
	return ostr;
}
