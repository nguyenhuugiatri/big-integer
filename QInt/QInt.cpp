#include "QInt.h"

QInt::QInt()
{
	for (int i = 0; i < 4; i++)
		arrayBits[i] = 0;
}

QInt::QInt(string input, string base) :QInt()
{
	if (base == "2")
		createFromBin(input);
	else if (base == "10")
		createFromDec(input);
	else if (base == "16")
		createFromHex(input);
}

void QInt::createFromBin(string & input)
{
	for (int i = input.length() - 1; i >= 0; i--)
	{
		if (input[i] == '1')
			setBit(input.length() - 1 - i, 1);
	}
}

void QInt::createFromDec(string & input)
{
	string temp = decToBin(input);
	createFromBin(temp);
}

void QInt::createFromHex(string & input)
{
	string temp = hexToBin(input);
	createFromBin(temp);
}

bool QInt::setBit(int index, bool bit)
{
	if (index<0 || index>MAX_SIZE - 1)
		return false;
	else
	{
		int pos = 3;
		while ((index - BIT_PER_INT) >= 0)
		{
			index -= BIT_PER_INT;
			pos--;
		}
		if (bit == 1)
			turnOnBit(arrayBits[pos], index);
		else
			turnOffBit(arrayBits[pos], index);
		return true;
	}
}

bool QInt::getBit(int index)
{
	if (index<0 || index>MAX_SIZE - 1)
		return false;
	else
	{
		int pos = 3;
		while ((index - BIT_PER_INT) >= 0)
		{
			index -= BIT_PER_INT;
			pos--;
		}
		return getBitFromInt(arrayBits[pos], index);
	}
}

QInt QInt::operator+(QInt &other)
{
	QInt sum;
	int mark = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		//Cộng từng bit
		int s = getBit(i) + other.getBit(i) + mark;

		if (s == 1)
		{

			mark = 0;
			//Chuyển bit thứ i thành 1
			sum.setBit(i, 1);
		}
		//Nếu tổng là 2
		else if (s == 2)
		{
			//Nhớ 1
			mark = 1;
			//Chuyển bit thứ i thành 0
			sum.setBit(i, 0);
		}
		//Nếu tổng là 3
		else if (s == 3)
		{
			//Nhớ 1
			mark = 1;
			//Chuyển bit thứ i thành 1
			sum.setBit(i, 1);
		}
		//Nếu tổng là 0
		else if (s == 0)
		{
			//Nhớ 0
			mark = 0;
			//Chuyển bit thứ i thành 0
			sum.setBit(i, 0);
		}
	}
	return sum;
}

QInt QInt::operator-(QInt &other)
{
	QInt negativeOther = ~other;
	QInt one("1", "10");
	negativeOther = negativeOther + one;
	return (*this) + negativeOther;
}

QInt QInt::operator*(QInt &other)
{
	QInt mul;
	QInt A;
	int k = 128;
	int bitQ1 = 0;
	int vitri = 0;  // tim bit đầu trong this
	while (k > 0)
	{
		// This là số nhân thứ 1
		if (this->getBit(0) == 1 && bitQ1 == 0) // Nếu bit cuối của số nhân 1 và Q1 là 10 
			A = A - other;
		if (this->getBit(0) == 0 && bitQ1 == 1) // Nếu bit cuối của số nhân 1 và Q1 là 01 
			A = A + other;
		// Nếu bit cuối của số nhân 1 và Q1 là 11, 00 thì A giữ nguyên 

		// SHR 1 bit [ A ,This, Q1 ]

		// Dịch phải A 1 bit
		for (int i = 126; i >= 0; i--)
		{
			int bit = A.getBit(i + 1);
			A.setBit(i, bit);
		}
		// Bit cuối của A
		int bitcuoiA = A.getBit(0);
		// Dịch This 1 bit
			// tìm vị trí bit đầu trong this
		for (int i = 127; i >= 0; i--)
		{
			if (this->getBit(i) == 1)
				vitri = i;
		}
		// dịch this sang phải 1 bit
		for (int i = 126; i >= 0; i--)
		{
			int bit = A.getBit(i + 1);
			A.setBit(i, bit);
		}
		this->setBit(vitri, bitcuoiA);
		//
		int bitcuoiQ = this->getBit(0);
		bitQ1 = bitcuoiQ;

		k--;
	}
	// Kết quả là A nối với Q ;
	return (*this);
}

QInt QInt::operator/(QInt &other)
{
	QInt div;
	int k = 128;
	QInt A;
	int q1 = 0;
	if (this->getBit(127) == 1)
	{
		for (int i = 127; i >= 0; i--)
			A.setBit(i, 1);
	}
	while (k > 0)
	{
		// dịch trái 1 bit [A , This]
		for (int i = 127; i > 0; i--)
		{
			int bit = A.getBit(i - 1);
			A.setBit(i, bit);
		}
		A.setBit(0, this->getBit(127));
		// dịch trái 1 bit This
		for (int i = 127; i > 0; i--)
		{
			int bit = this->getBit(i - 1);
			this->setBit(i, bit);
		}
		this->setBit(0, q1);

		A = A - other;
		// Nếu A<0 : A=A+M and q1=0
		if (A.getBit(127) == 1)
		{
			q1 = 0;
			A = A + other;
		}
		else // ngược lại q1=1
		{
			q1 = 1;
			this->setBit(0, q1);
		}

		k--;
	}
	// Kết quả : This là thương , A là số dư
	return (*this);
}

QInt QInt::operator&(QInt &other)
{
	for (int i = 0; i < 4; i++)
		this->arrayBits[i] &= other.arrayBits[i];
	return (*this);
}

QInt QInt::operator|(QInt &other)
{
	for (int i = 0; i < 4; i++)
		this->arrayBits[i] |= other.arrayBits[i];
	return (*this);
}

QInt QInt::operator^(QInt &other)
{
	for (int i = 0; i < 4; i++)
		this->arrayBits[i] ^= other.arrayBits[i];
	return (*this);
}

QInt QInt::operator~()
{
	for (int i = 0; i < 4; i++)
		this->arrayBits[i] = ~this->arrayBits[i];
	return (*this);
}

QInt QInt::operator<<(int dis)
{
	QInt result;
	if (dis <= 0 || dis >= 128)
		return(*this);
	string temp = this->toString("2");
	for (int i = 0; i < dis; i++)
	{
		temp.insert(temp.end(), 1, '0');
		temp.erase(temp.begin());
	}

	result.createFromBin(temp);
	return result;
}

QInt QInt::operator>>(int dis)
{
	QInt result;
	if (dis <= 0 || dis >= 128)
		return(*this);
	string temp = this->toString("2");
	for (int i = MAX_SIZE - 1; i > MAX_SIZE - 1 - dis; i--)
	{
		temp.erase(temp.length() - 1, 1);
		temp.insert(temp.begin(), temp[0]);
	}

	result.createFromBin(temp);
	return result;
}

QInt QInt::rol()
{
	QInt result;
	string temp = this->toString("2");
	char mark = temp[0];
	temp.erase(temp.begin());
	temp.insert(temp.length(), 1,mark);

	result.createFromBin(temp);
	return result;
}

QInt QInt::ror()
{
	QInt result;
	string temp = this->toString("2");

	char mark = temp[temp.length() - 1];
	temp.erase(temp.length() - 1,1);
	temp.insert(temp.begin(), mark);

	result.createFromBin(temp);
	return result;
}

string QInt::toString(string base)
{
	string temp;
	temp.resize(MAX_SIZE);
	for (int i = 0; i < MAX_SIZE; i++)
		temp[i] = getBit(MAX_SIZE - 1 - i) + '0';

	string result;
	if (base == "2")
		result = temp;
	if (base == "10")
		result = binToDec(temp);
	if (base == "16")
		result = binToHex(temp);

	return result;
}