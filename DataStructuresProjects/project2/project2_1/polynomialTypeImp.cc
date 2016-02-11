#include "polynomialType.h"
#include <cmath>
using namespace std;

polynomialType::polynomialType(int size)
          : arrayListType<double>(size)
{
	length = size;
	for (int i = 0; i < size; i++)
		list[i] = 0;
}

double polynomialType::operator() (double x)
{
	double value = 0.0;

	for (int i = 0; i < length; i++)
	{
		if (list[i] != 0.0)
			value = value + list[i] * pow(x,i);
	}

	return value;

}

polynomialType polynomialType::operator+
               (const polynomialType& right)
{
	int size = max(length, right.length);

	polynomialType temp(size);

	for (int i = 0; i < min(length, right.length); i++)
		temp.list[i] = list[i] + right.list[i];

	if (size == length)
		for (int i = min(length, right.length); i < length; i++)
			temp.list[i] = list[i];
	else
		for (int i = min(length, right.length); i < right.length; i++)
			temp.list[i] = right.list[i];

	return temp;

}

polynomialType polynomialType::operator-
               (const polynomialType& right)
{
	int size = max(length, right.length);

	polynomialType temp(size);

	for (int i = 0; i < min(length, right.length); i++)
		temp.list[i] = list[i] - right.list[i];

	if (size == length)
		for(int i = min(length, right.length); i < length; i++)
			temp.list[i] = list[i];
	else
		for (int i = min(length, right.length); i < right.length; i++)
			temp.list[i] = -right.list[i];

	return temp;

}

polynomialType polynomialType::operator*
               (const polynomialType& right)
{
	int len = length + right.length;
	polynomialType temp(len);
	int i, j;
	for(int k = 0; k <= len; k++)
    {
        temp.list[k] = 0;
    }
    for(int c = 0; c <= len; c++)
    {
        i = 0;
        j = c;
        while((i+j)==c)
        {
           if(j != 0)
            {
              temp.list[c] = temp.list[c] + list[i] * right.list[j];
              i++;
              j--;
            }
           else
              i++;
        }
    }
 return temp;
}

int polynomialType::min(int x, int y) const
{
	if (x <= y)
		return x;
	else
		return y;
}

int polynomialType::max(int x, int y) const
{
	if (x >= y)
		return x;
	else
		return y;
}

ostream& operator<<(ostream& os, const polynomialType& p)
{
	int indexFirstNonzeroCoeff = 0;

	for (int i = 0; i < p.length; i++)
		if (p.list[i] != 0.0)
		{
			indexFirstNonzeroCoeff = i;
			break;
		}

	if (indexFirstNonzeroCoeff < p.length)
	{
		if(indexFirstNonzeroCoeff == 0)
			os << p.list[indexFirstNonzeroCoeff] << " ";
		else
			os << p.list[indexFirstNonzeroCoeff] << "x^"
			   << indexFirstNonzeroCoeff << " ";

		for (int i = indexFirstNonzeroCoeff + 1; i < p.length; i++)
		{
			if (p.list[i] != 0.0)
				if (p.list[i] >= 0.0)
					os << "+ " << p.list[i]
					   << "x^" << i << " ";
				else
					os << "- " << -p.list[i]
					   << "x^" << i << " ";
		}
	}
    else
		os << "0";

	return os;
}

istream& operator>>(istream& is, polynomialType& p)
{
	cout << "The degree of this polynomial is: "
		 << p.length - 1 << endl;
	for (int i = 0; i < p.length; i++)
	{
		cout << "Enter the coefficient of x^" << i << ": ";
		is >> p.list[i];
	}

	return is;
}
