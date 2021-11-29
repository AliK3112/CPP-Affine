#include<iostream>
#include<fstream>
#include<string>
#include<string.h>

using namespace std;

// Reference: https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
int modInverse(int a, int m)
{
    for (int x = 1; x < m; x++)
        if (((a%m) * (x%m)) % m == 1)
            return x;
}

bool isAlpha(char x)
{
	return (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z');
}

string encrypt(string input, int a, int b)
{
	string value = "\0";
	for (int i = 0; input[i] != '\0'; i++)
	{
		if (isAlpha(input[i]))
			value += ((a * input[i] + b) % 26) + 'A';
		else
			value += input[i];
	}
	return value;
}

string decrypt(string input, int a, int b)
{
	int inv = modInverse(a, 26);
	string value = "\0";
	for (int i = 0; input[i] != '\0'; i++)
	{
		if (isAlpha(input[i]))
			value += ((inv * (input[i] - b)) % 26) + 'A';
		else
			value += input[i];
	}
	return value;
}

int main(int argc, char** argv)
{
	// Arguments
	// 1 - Input Filename
	// 2 - Output Filename
	// 3 - Value of a
    // 4 - Value of b
	if (argc < 5) {
		cout << "Arguments\n1 - Input Filename\n2 - Output Filename\n3 - Value of a\n4 - Value of b\n";
	}

	char *input = argv[1];
	char *output = argv[2];
	int a = -1;
  	int b = -1;

  	try {
		a = stoi(argv[3]);
    	b = stoi(argv[4]);
	} 
	catch(exception e)
	{
		cout << "Invalid value of k\nProgram closing!\n";
		return 0;
	}

	// Opening file
	ifstream read(input, ios::in);
	if (!read.is_open()) {
		cout << "File not found!\nProgram closing!\n";
		return 0;
	}

	// Reading from file
	string inp = "\0";
	getline(read, inp);
	read.close();
	string out = encrypt(inp, a, b);

	// Write to file
	ofstream write(output, ios::out);
	write << out;
	write.close();

	string dec = decrypt(out, a, b);
	cout << "Encrypted: " << out << endl;
	cout << "Decrypted: " << dec << endl;
	// Testing
	if (inp.compare(dec) == 0) {
		cout << "Encryption/Decryption successful" << endl;
	}
	return 0;
}