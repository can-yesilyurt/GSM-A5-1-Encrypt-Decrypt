/* C:B**************************************************************************
This software is Copyright 2024 Can Yesilyurt <can--yesilyurt@hotmail.com>

encrypt_GSM_A5-1 is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

encrypt_GSM_A5-1 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
<http://www.gnu.org/licenses/>.

* C:E********************************************************************** */

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <bitset>

using namespace std;

string hextobin(const string &s){
	string out;
	for(auto i: s) {
		uint8_t n;
		if(i <= '9' and i >= '0')
		n = i - '0';
		else
		n = 10 + i - 'A';
		for(int8_t j = 3; j >= 0; --j){
			out.push_back((n & (1<<j))? '1':'0');
		}
	}
	return out;
}

char Xor(const char in1, const char in2){
	if (in1 != in2){
		return '1';
	}
	else {
		return '0';
	}
}

void xRun(char* input){
	
	char tx = Xor(input[13], input[16]);
	tx = Xor(tx, input[17]);
	tx = Xor(tx, input[18]);
	
	char Tx[19];
	
	for (int i = 0; i < 18; i++)
		Tx[i+1]=input[i];
	
	Tx[0] = tx;
	
	for (int i = 0; i < 19; i++)
	input[i] = Tx[i];
}

void yRun(char* input){
	
	char ty = Xor(input[20], input[21]);
	
	char Ty[22];
	
	for (int i = 0; i < 21; i++)
		Ty[i+1]=input[i];
	
	Ty[0] = ty;
	
	for (int i = 0; i < 22; i++)
		input[i] = Ty[i];
}

void zRun(char* input){
	
	char tz = Xor(input[7], input[20]);
	tz = Xor(tz, input[21]);
	tz = Xor(tz, input[22]);
	
	char Tz[23];
	
	for (int i = 0; i < 22; i++)
		Tz[i+1]=input[i];
	
	Tz[0] = tz;
	
	for (int i = 0; i < 23; i++)
		input[i] = Tz[i];
}

char burst(char* xin, char* yin, char* zin){
	char s;
	
	char x = xin[8];
	char y = yin[10];
	char z = zin[10];
	
	int xx = x - '0';
	int yy = y - '0';
	int zz = z - '0';
	
	int m = xx + yy + zz;
	
	int maj;
	if (m > 1) {
		maj = 1;
	}
	else {
		maj = 0;
	}
	
	if (xx == maj) {
		xRun(xin);
	}
	if (yy == maj) {
		yRun(yin);
	}
	if (zz == maj) {
		zRun(zin);
	}
	
	s = Xor(xin[18], yin[21]);
	s = Xor(s, zin[22]);
	
	return s;
}

string to_binary_str(const string &words) {
	string binaryString = "";
	
	for (char c : words) {
		binaryString += bitset<8>(c).to_string();
	}
	return binaryString;
}

void getBitStream(const string &pth, string &bitStream) {
	
	ifstream f(pth);
	
	if (!f.is_open()) {
		cout << "Can't read input file";
	}
	
	string s = "";
	char ch;
	while (f.get(ch)) {
		s += ch;
	}
	
	f.close();
	
	bitStream = to_binary_str(s);
}

void writeCipherText(const string &pth, const string &cipher){
	
	string s = cipher;
	
	ofstream output(pth);
	
	for (int i = 0; i < s.length(); i=i+8)
		{
			string byte_str = s.substr(i, 8);
			bitset<8> b(byte_str);
			unsigned char c = ( b.to_ulong() & 0xFF);
			output << c;
		}
	
	output.close();
	
}

int main(int numargs, char *arg[]) {
	
	if (numargs != 4) {
		cout << "Wrong or missing arguments.\n";
		cout << "Usage: ";
		cout << "encrypt_GSM_A5-1 [ki] [input path] [output path]\n";
		cout << "                  ki: 64 bit in HexString example: \"5510604b39648df9\"\n";
		return EXIT_FAILURE;
	}
	
	string s = arg[1];
	
	string b = hextobin(s);
	
	char xreg[19];
	char yreg[22];
	char zreg[23];

	
	for (int i = 0; i < 19; i++)
		xreg[i] = b[i];
	for (int i = 19; i < 41; i++)
		yreg[i-19] = b[i];
	for (int i = 41; i < 64; i++)
		zreg[i-41] = b[i];
	

	//for (int i = 0; i < 19; i++)
	//	cout << xreg[i];
	//cout << "\n";
	//for (int i = 0; i < 22; i++)
	//	cout << yreg[i];
	//cout << "\n";
	//for (int i = 0; i < 23; i++)
	//	cout << zreg[i];
	//cout << "\n";
	
	cout << "(*) Registers are loaded";
	
	string bitstrm = "";
	getBitStream(arg[2], bitstrm);
	

	string keyStream = "";
	for (int i = 0; i < bitstrm.length(); i++){
		char o = burst(xreg, yreg, zreg);
		keyStream += o;
	}
	
	cout << "\n(*)Key Stream generated";
	
//	cout << keyStream << "\n";
	
	string cipherText = "";
	for (int i = 0; i < bitstrm.length(); i++){
		char sss = Xor(bitstrm[i], keyStream[i]);
		cipherText += sss;
	}
	
	cout << "\n(*)Encryption completed";
	cout << "\n(*)Creating the output file";
	
	writeCipherText(arg[3], cipherText);
	
	cout << "\n";
	cout << arg[3];
	cout << "\n";
	
	return EXIT_SUCCESS;
}