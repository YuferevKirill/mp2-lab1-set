// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(void)
{
	MemLen=0;
	BitLen=0;
	pMem=0;
}

TBitField::TBitField(int len)
{
	BitLen = len;
	if (BitLen<0)
	{
		throw "ERROR!";
	} 
	else
	MemLen = (len + 31) >> 5;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i]<0){
			throw "ERROR!";
		}else

		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen=bf.MemLen;
	BitLen=bf.BitLen;
	pMem= new TELEM[MemLen];
	for(int i=0;i<MemLen;i++)
		pMem[i]=bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n>>5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n & 31); 
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n>BitLen))
	{
		throw "Error!";
	} else
	//if ((n >= 0) && (n <= BitLen))
		pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n>BitLen))
	{
		throw "Error!";
	}
	else
	//if((n>=0)&&(n<=BitLen))
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}
//////////////////////////////////////////ВОПРОС!!!
int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n>BitLen))
	{
		throw "Error!";
		return 0;
	}
	else
    //if((n>=0)&&(n<=BitLen))
	return	pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen=bf.BitLen;
	if(MemLen!=bf.MemLen)
	{
		delete[] pMem;
		MemLen=bf.MemLen;
		pMem=new TELEM[MemLen];
	}
	for(int i=0;i<MemLen;i++)
	{
		pMem[i]=bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  int res = 1;
  if ( BitLen != bf.BitLen ) res = 0;
  else
    for ( int i=0; i < MemLen; i++ )
      if ( pMem[i] != bf.pMem[i] ) 
	  {	  
		  res = 0;
		  break;
	  }	
  return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if(BitLen!=bf.BitLen)
    return 1;
	else
    for ( int i=0; i < MemLen; i++ )
      if ( pMem[i] != bf.pMem[i] ) 
	  {	  
		  return 1;
	  }	
	  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int MaxMem;
	if(BitLen>bf.BitLen)
		MaxMem=BitLen;
	else
		MaxMem=bf.BitLen;
	TBitField res(MaxMem);
	int min; 
	if (MemLen > res.MemLen)
		{
			min=res.MemLen;
	}
	else
		min=MemLen;

	for(int i=0;i<min;i++)
		res.pMem[i]=bf.pMem[i];

	for(int i=0;i<min;i++)
		res.pMem[i]|=pMem[i];

	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int MaxMem;
	if(BitLen>bf.BitLen)
		MaxMem=BitLen;
	else
		MaxMem=bf.BitLen;

	TBitField res(MaxMem);

	int min; 
	if (MemLen > res.MemLen)
		{
			min=res.MemLen;
	}
	else
		min=MemLen;

	for(int i=0;i<min;i++)
		res.pMem[i]=bf.pMem[i];

	for(int i=0;i<min;i++)
		res.pMem[i]&=pMem[i];

	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
		TBitField res(BitLen);
		for (int i=0;i<BitLen;i++)
		{
			if(GetBit(i))
			{
				res.ClrBit(i);
			}
			else
				res.SetBit(i);
		}
		return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i=0; 
  char ch; 
  do 
  {
	  istr.get(ch); 
  } 
  while (ch != ' ' && ch!='\n');
  while (1) 
  {
	  istr.get(ch);
    if ( ch == '0' ) 
	{
		bf.ClrBit(i);
		i++;
	}
      else
			  if ( ch == '1' )
			  {
				  bf.SetBit(i);
				i++;
			  }
		  else
			break;
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len=bf.BitLen;
	for(int i=0; i < len; i++)
		
		if(bf.GetBit(i))
			ostr<<"1";
		else
			ostr<<"0";
	return ostr;
}
