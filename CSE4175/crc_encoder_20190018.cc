#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdio>
#include<sstream>
#include<bitset>

using namespace std;

//#define _CRT_SECURE_NO_WARNINGS
#define BUFSIZE 1000


int dw_size=0;
int padding = 0;
string pad_bin = "";
string gen = "";
string aug = "";
string codeword = "";
string dataword = "";


vector<char> v; //input file string


//prototype
string dec_bin(int pad);
string asc_bin(unsigned char asc);
string bin_char(string bin);
string mod_gen(string bina);
//string oct_decimal_converter(unsigned char value);

int main(int argc, char** argv) {
	//ios_base::sync_with_stdio(false);
	
	
	if (argc == 5) {
		
		unsigned char buff;
		string str="";
		ifstream input;
		ofstream output;
		//FILE* fp = fopen(argv[1], "rb");
		//FILE* fp2 = fopen(argv[2], "wb");
		input.open(argv[1], ios::binary);
		if (input.fail()) {
			cout << "input file open error.";
			return 1;
		}
		output.open(argv[2], ios::binary);
		if (output.fail()) {
			cout << "output file open error.";
			return 1;
		}

		gen = argv[3];
		for (int i = 0;i < gen.size() - 1;i++) {
			aug += "0";
		}

		dw_size = stoi(argv[4]);
		if (dw_size != 4 && dw_size != 8) {
			cout << "dataword size must be 4 or 8.";
		}
		
		//buff = fgetc(fp);
		
		string res = "";
		//int a = 0; //byte개수확인 
		vector<char>v;
		while (true) {
			buff = input.get();
			v.push_back(buff);
			if (input.fail()) {
				break;
			}
			
			string bin = asc_bin(buff);

			//cout << buff<<" "<<bin << "\n";
			
			if (dw_size == 4) {
				string tmp1 = mod_gen(bin.substr(0, 4));
				string tmp2 = mod_gen(bin.substr(4, 4));
				//cout << tmp1 << "\n";
				//cout << tmp2 << "\n";
				res = tmp1 + tmp2;

			}
			else {
				res = mod_gen(bin);
			}
			//cout << res << "\n";

			codeword += res;
			//a++;
		}
		//cout << a;
		/*while (feof(fp) == 0) {
			
			
			buff = fgetc(fp);
		}*/
		
		
		padding = 8 - (codeword.length() % 8);
		pad_bin = dec_bin(padding);
		int p = padding;
		while (p--) {
			codeword = "0" + codeword;
		}

		//cout << codeword << " ";
		//cout << codeword.length() << "\n";

		string pad=bin_char(pad_bin);
		output << pad;
		for (int i = 0;i < codeword.length();i += 8) {
			string result=bin_char(codeword.substr(i, 8));
			//cout << codeword.substr(i, 8) << " " << result << "\n";
			output << result;
		}

	}

	else {
		//cout << "인자가 부족합니다.\n";
		cout << "usage:./crc_encoder input_file output_file generator dataword_size\n";
		return 1;
	}
	
	
	
	return 0;
}





string asc_bin(unsigned char asc) { //아스키코드를 이진수로
	int tmp = asc;
	int remain = 0;

	//cout << tmp << " ";
	string res = "";
	string remain2 = "";
	while (tmp > 0) {
		remain = tmp % 2;
		tmp = int(tmp / 2);
		remain2 = to_string(remain);
		res = remain2 + res;
	}

	int len = res.size();
	if (len % 8 != 0) {
		int pl = 8 - (len % 8);
		while (pl--) {
			res = "0" + res;
		}
	}

	return res;
}


string mod_gen(string bina) {
	//이진수화된 dataword가 들어옴
	string divident = bina;
	divident += aug;
	//붙일나머지 계산하기
	//cout << divident << "\n";
	for (int i = 0;i <= divident.length() - gen.size();i++) {
		if (divident[i] == '1') {
			for (int j = 0;j < gen.size();j++) {
				if (divident[i + j] == gen[j]) {
					divident[i + j] = '0';
				}
				else {
					divident[i + j] = '1';
				}
			}
		}
	}
	string remainder = divident.substr(dw_size);
	remainder = bina + remainder;

	return remainder;
}




string dec_bin(int pad) { //10진수를 이진수로
	int tmp = pad;
	int remain = 0;
	string res = "";
	string remain2 = "";
	while (tmp > 0) {
		remain = tmp % 2;
		tmp = int(tmp / 2);
		remain2 = to_string(remain);
		res = remain2 + res;
	}

	int len = res.size();
	if (len % 8 != 0) {
		int pl = 8 - (len % 8);
		while (pl--) {
			res = "0" + res;
		}
	}

	return res;
}


string bin_char(string bin) {
	
	string c;
	stringstream sstream(bin);
	bitset<8> bit;

	sstream >> bit;
	c = char(bit.to_ulong());

	return c;
}