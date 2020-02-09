#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;

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

char input;

int calcgcd(int a, int b);

std::vector <int> factors(int x);

void encryption();

void decryption();

int main() 
{
	int pkeyE = 0, pkeyN = 0;

	int p = 0, q = 0, Totient = 0;

	int holdgcd = 0;

	char action = ' ';

	std::ofstream myfile;

	std::string filename = "";

	std::vector<int>FactsofN;

	while (holdgcd != 1) 
	{
		std::cout << "\nPlease input a number for e: ";

		std::cin >> pkeyE;

		std::cout << std::endl << "Please input a number for n: ";

		std::cin >> pkeyN;

		FactsofN = factors(pkeyN);

		p = FactsofN[FactsofN.size() - 2];

		q = FactsofN[FactsofN.size() - 1];

		Totient = (p - 1)*(q - 1);

		holdgcd = calcgcd(pkeyE, Totient);
	}

	std::cout << std::endl << "Please input choice of action. e for encryption or d for decryption: ";

	std::cin >> action;

	if (action == 'e') 
	{
		encryption();
	}

	if (action == 'd')
	{
		decryption();
	}

	std::cout << std::endl << "Please input a filename: ";

	std::cin >> filename;

	myfile.open(filename);

	myfile << "Writing this to a file.\n";

	myfile.close();

	return 0;
}

int calcgcd(int a, int b) 
{
	int temp = 0;
	if (a == b) 
	{
		return a;
	}
	if (a < b) 
	{
		temp = b;
		b = a;
		a = temp;
	}
	return calcgcd(a - b, b);
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

void encryption() 
{
  std::cout << "Running Encryption\n";
}

void decryption()
{
  std::cout << "Running Decryption\n";
}