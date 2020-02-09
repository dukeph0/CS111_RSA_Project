/*
    Input:
    a) A public key (e, d) (you need to check whether the input is valid);
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

int calcgcd(int a, int b);

std::vector <int> factors(int x);

std::vector <int> encryption(int E, int N, std::string str, std::map<char, int> m);

std::vector <char> decryption(int a,int b,int c, std::vector<int>cipher, std::map<char, int> m);

int modularInverse(int a, int b);

int calcLargeEx(int a, int b, int mod);

std::string filetoString();

int calcTotient(int a);

int main() 
{
	int pkeyE = 0, pkeyN = 0;

	int p = 0, q = 0, Totient = 0;

	int holdgcd = 0;

	char action = ' ';

	std::ofstream myfile;

	std::string str = "";

	std::vector<int>FactsofN;

	std::vector<int>cipher = { 10, 7, 58, 30, 23, 62, 7, 64,
		62, 23, 62, 61, 7, 41, 62, 21, 7, 49, 75, 7, 69, 53, 58,
		37, 37, 41, 10, 64, 50, 7, 10, 64, 21, 62, 61, 35, 62, 61, 62,
		7, 52, 10, 21, 58, 7, 49, 75, 7, 62, 26, 22, 53, 30, 21, 10, 37, 64 }; //Test Messages

	std::vector<char>message = {'i', ' ', 'h', 'a','v','e',' ','n','e','v','e','r',' ','l','e','t',' ','m','y'}; //Test Messages

	std::vector<int>eMessage;

	std::vector<char>dMessage;

	std::cout << "\nPlease input a number for e: ";

	std::cin >> pkeyE;

	std::cout << std::endl << "Please input a number for n: ";

	std::cin >> pkeyN;

	FactsofN = factors(pkeyN);

	p = FactsofN[FactsofN.size() - 2];

	q = FactsofN[FactsofN.size() - 1];

	Totient = calcTotient(p)*calcTotient(q);

	std::cout << std::endl << "Please input choice of action. e for encryption or d for decryption: ";

	std::cin >> action;

	str = filetoString();

	std::map<char, int> m;
	std::map<char, int>::iterator it;
	m.insert(std::pair<char, int>('a', 2));
	m.insert(std::pair<char, int>('b', 3));
	m.insert(std::pair<char, int>('c', 4));
	m.insert(std::pair<char, int>('d', 5));
	m.insert(std::pair<char, int>('e', 6));
	m.insert(std::pair<char, int>('f', 7));
	m.insert(std::pair<char, int>('g', 8));
	m.insert(std::pair<char, int>('h', 9));
	m.insert(std::pair<char, int>('i', 10));
	m.insert(std::pair<char, int>('j', 11));
	m.insert(std::pair<char, int>('k', 12));
	m.insert(std::pair<char, int>('l', 13));
	m.insert(std::pair<char, int>('m', 14));
	m.insert(std::pair<char, int>('n', 15));
	m.insert(std::pair<char, int>('o', 16));
	m.insert(std::pair<char, int>('p', 17));
	m.insert(std::pair<char, int>('q', 18));
	m.insert(std::pair<char, int>('r', 19));
	m.insert(std::pair<char, int>('s', 20));
	m.insert(std::pair<char, int>('t', 21));
	m.insert(std::pair<char, int>('u', 22));
	m.insert(std::pair<char, int>('v', 23));
	m.insert(std::pair<char, int>('w', 24));
	m.insert(std::pair<char, int>('x', 25));
	m.insert(std::pair<char, int>('y', 26));
	m.insert(std::pair<char, int>('z', 27));
	m.insert(std::pair<char, int>(' ', 28));
	
	if (action == 'e') 
	{
		eMessage = encryption(pkeyE, pkeyN, str, m);
		for (int i = 0; i < eMessage.size(); i++)
		{
			std::cout << eMessage[i] << ' ';
		}
	}

	if (action == 'd')
	{
		dMessage = decryption(pkeyE, pkeyN, Totient, cipher, m);
		for (int i = 0; i < dMessage.size(); i++)
		{
			std::cout << dMessage[i];
		}
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

std::string filetoString() 
{
	std::ifstream file("message.txt"); //taking file as inputstream

	std::string str;

	if (file) 
	{
		std::ostringstream ss;

		ss << file.rdbuf(); // reading data

		str = ss.str();
	}

	return str;
}

int calcTotient(int a) 
{
	int result = 1;
	for (int i = 2; i < a; i++)
		if (calcgcd(i, a) == 1)
			result++;
	return result;
}