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
}