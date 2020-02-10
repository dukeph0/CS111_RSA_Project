/*
    Input:
    a) A public key (e, n) (you need to check whether the input is valid);
    b) Choice of encryption or decryption ("e" for encryption and "d" for decryption)

    Additional input for encryption:
    c1) English text (in a text file). You can use well known quotes.
    Additional input for decryption:
    c2) Cipher text (in a text file).
    Note: in this part, you need to break RSA (follow your homework 2 (problem 2) instructions).

    Output:
    For encryption: cipher text (written into a text file).
    For decryption: decoded message (written into a text file).

    Notice about RSA Project from Chengkuan Hong:
    3. I would use this command to compile your code:
      g++ -std=c++11 RSA.cpp -o RSA
    Then I would run something like
      ./RSA 5 77 e message.txt
    and 
      ./RSA 5 77 d ciphertext.txt.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>
#include<iterator>
#include <cmath>

int calcgcd(int a, int b);

std::vector <int> factors(int x);
std::vector <int> encryption(int E, int N, std::string str, std::map<char, int> m);
std::vector <char> decryption(int a,int b,int c, std::vector<int>cipher, std::map<char, int> m);

int modularInverse(int a, int b);
int calcLargeEx(int a, int b, int mod);


std::string filetoString(std::string a);
std::vector <int> filetoString2(std::string a);


int calcTotient(int a);


int main(int argc, char *argv[]) 
{

	int pkeyE = 0, pkeyN = 0;
	int p = 0, q = 0, Totient = 0;
	char action = ' ';

	std::ofstream myfile;
	std::string str = "";
	std::vector<int>FactsofN, cipher, eMessage, FirstInput, SecondInput;
	std::vector <char> FourthInput, dMessage;
	std::string hold = "", fileName;

	int var = 0;

	std::string FirstCharHold;
	std::string SecondCharHold;
	std::string ThirdCharHold;
	std::string FourthCharHold;
	FirstCharHold = argv[1];
	SecondCharHold = argv[2];
	ThirdCharHold = argv[3];
	FourthCharHold = argv[4];
	pkeyE = std::stoi(FirstCharHold);
	pkeyN = std::stoi(SecondCharHold);
	action = ThirdCharHold[0];
	fileName = FourthCharHold;
	FactsofN = factors(pkeyN);
	p = FactsofN[FactsofN.size() - 2];
	q = FactsofN[FactsofN.size() - 1];
	Totient = calcTotient(p)*calcTotient(q);
	std::map<char, int> m;
	std::map<char, int>::iterator it;

	m.insert(std::pair<char, int>('A', 2));
	m.insert(std::pair<char, int>('B', 3));
	m.insert(std::pair<char, int>('C', 4));
	m.insert(std::pair<char, int>('D', 5));
	m.insert(std::pair<char, int>('E', 6));
	m.insert(std::pair<char, int>('F', 7));
	m.insert(std::pair<char, int>('G', 8));
	m.insert(std::pair<char, int>('H', 9));
	m.insert(std::pair<char, int>('I', 10));
	m.insert(std::pair<char, int>('J', 11));
	m.insert(std::pair<char, int>('K', 12));
	m.insert(std::pair<char, int>('L', 13));
	m.insert(std::pair<char, int>('M', 14));
	m.insert(std::pair<char, int>('N', 15));
	m.insert(std::pair<char, int>('O', 16));
	m.insert(std::pair<char, int>('P', 17));
	m.insert(std::pair<char, int>('Q', 18));
	m.insert(std::pair<char, int>('R', 19));
	m.insert(std::pair<char, int>('S', 20));
	m.insert(std::pair<char, int>('T', 21));
	m.insert(std::pair<char, int>('U', 22));
	m.insert(std::pair<char, int>('V', 23));
	m.insert(std::pair<char, int>('W', 24));
	m.insert(std::pair<char, int>('X', 25));
	m.insert(std::pair<char, int>('Y', 26));
	m.insert(std::pair<char, int>('Z', 27));
	m.insert(std::pair<char, int>(' ', 28));

	if (action == 'e') 
	{

		str = filetoString(fileName);
		eMessage = encryption(pkeyE, pkeyN, str, m);
		std::ofstream outFile("incrypted.txt");
		for (const auto &e : eMessage) outFile << e << " ";

	}


	if (action == 'd')
	{

		cipher = filetoString2(fileName);
		dMessage = decryption(pkeyE, pkeyN, Totient, cipher, m);
		std::ofstream outFile("decrypted.txt");

		for (const auto &e : dMessage) outFile << e;

	}

	return 0;

}

int calcgcd(int a, int b) 
{

	if (b == 0)

		return a;

	return calcgcd(b, a % b);
}

std::vector <int> factors(int x) 
{

	std::vector <int> factvec;

	int i = 1;

	while (i*i <= x) 
	{

		if (x % i == 0) 
		{

			factvec.push_back(i);

			if (x / i != i) 
			{
				factvec.push_back(x / i);
			}
		}
		i++;
	}

	return factvec;

}

std::vector <int> encryption(int E, int N, std::string str, std::map<char, int> m)
{

	int num = 0;

	std::vector <int> vect;

	std::map<char, int>::iterator it;

	for (int i = 0; i < str.size(); i++) 
	{
		for (it = m.begin(); it != m.end(); ++it) 
		{
			if ((*it).first == str[i]) 
			{
				num = (*it).second;
				vect.insert(vect.begin()+i, calcLargeEx(num, E, N));
			}
		}
	}
	return vect;
}

std::vector <char> decryption(int e, int N, int Totient, std::vector<int>cipher, std::map<char, int> m)
{

	int d = 0, hold = 0;

	std::vector <char> vect;

	std::map<char, int>::iterator it;

	d = modularInverse(e, Totient);

	for (int i = 0; i < cipher.size(); i++) 
	{

		hold = calcLargeEx(cipher[i], d, N);

		for (it = m.begin(); it != m.end(); ++it)
		{
			if ((*it).second == hold)
			{
				vect.insert(vect.begin() + i, (*it).first);
			}

		}

	}
	return vect;
}
int modularInverse(int a, int b) 
{
	a = a % b;
	for (int x = 1; x < b; x++) 
	{
		if ((a*x) % b == 1) 
		{
			return x;
		}

	}

}

int calcLargeEx(int a, int b, int mod) 
{
	int result = 1;
	while (b > 0) 
	{
		if (b % 2 == 1) 
		{
			result = (result*a) % mod;
		}
		b = b >> 1;
		a = (a*a) % mod;
	}
	return result;
}
std::string filetoString(std::string a) 
{
	std::ifstream file(a); 
	std::string str;
	if (file) 
	{
		std::ostringstream ss;
		ss << file.rdbuf(); 
		str = ss.str();
	}
	return str;
}

std::vector <int> filetoString2(std::string a)
{
	std::ifstream file(a); 
	std::vector<int> vect;
	if (file) 
	{
		int value;
		while (file >> value) 
		{
			vect.push_back(value);
		}
	}
	return vect;
}
int calcTotient(int a) 
{
	int result = 1;
	for (int i = 2; i < a; i++)
		if (calcgcd(i, a) == 1)
			result++;
	return result;
}