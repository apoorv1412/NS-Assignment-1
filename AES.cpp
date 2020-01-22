#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

int binaryToInt(string s) {
	int num = 0;
	int curr_pow = 1;
	for (int i = s.size()-1; i >= 0; --i) {
		num += (s[i]-'0')*curr_pow;
		curr_pow *= 2;
	}
	return num;
}

string intToBinary(int n) {
	string num = "";
	while (n) {
		if (n&1) num += '1';
		else num += '0';
		n /= 2;
	}
	reverse(num.begin(), num.end());
	return num;
}

int GTable[16][16];

void substituteBytes(int intermediate[4][4]) {
	int A = (1 << 4);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			int num = intermediate[i][j];
			int x = num%A;
			int y = num/A;
			intermediate[i][j] = GTable[x][y];
		}
	}
}

void shiftRows(int intermediate[4][4]) {
	int modified[4][4];
	for (int i = 0; i < 4; ++i) {
		// modified[i][j] = intermediate[i][(j+i)%4];
		if (i == 0) {
			for (int j = 0; j < 4; ++j) 
				modified[i][j] = intermediate[i][(j+0)%4];
		}
		else if (i == 1) {
			for (int j = 0; j < 4; ++j) 
				modified[i][j] = intermediate[i][(j+1)%4];
		}
		else if (i == 2) {
			for (int j = 0; j < 4; ++j)
				modified[i][j] = intermediate[i][(j+2)%4];
		}
		else {
			for (int j = 0; j < 4; ++j) 
				modified[i][j] = intermediate[i][(j+3)%4];
		}
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j)
			intermediate[i][j] = modified[i][j];
	}
}

void mixColumns(int intermediate[4][4]) {
	int MCMatrix[4][4] = {{2,3,1,1},{1,2,3,1},{1,1,2,3},{3,1,1,2}};
	for (int j = 0; j < 4; ++j) {
		int column[4];
		for (int i = 0; i < 4; ++i)
			column[i] = intermediate[i][j];
		int multiplied[] = matrixMultiplication(MCMatrix ,column);
		for (int i = 0; i < 4; ++i)
			intermediate[i][j] = multiplied[j]; 
	}
}

void addRoundKey(int intermediate[4][4], int key[4][4]) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) 
			intermediate[i][j] ^= key[i][j];
	}
}

void SBox(int intermediate[4][4], int round) {
	if (round >= 1) substituteBytes(intermediate);
	if (round >= 1) shiftRows(intermediate);
	if (round >= 1 and round <= 9) mixColumns(intermediate);
	int key[4][4];
	addRoundKey(intermediate,key);
}

int main() {
	freopen("plaintext.txt","r",stdin);
	string plainText; cin >> plainText;
	int block[4][4], size = 128, ptr = 0;
	for (int j = 0; j < 4; ++j) {
		for (int i = 0; i < 4; ++i) {
			string dword = plainText.substr(ptr, 8);
			block[i][j] = binaryToInt(dword);	
			ptr += 8;
		}
	}
	
	int num_rounds = 10;
	int intermediate[4][4];

	for (int round = 0; round <= num_rounds; ++round) 
		SBox(intermediate,round);

	string cipherText = "";
	for (int j = 0; j < 4; ++j) {
		for (int i = 0; i < 4; ++i)
			cipherText += intToBinary(intermediate[i][j]);
	}

	cout << cipherText << endl;
}