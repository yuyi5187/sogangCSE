#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdio>
#include<sstream>
#include<bitset>
#include<cmath>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
int dw_size = 0;
int pad = 0;
int cw_size = 0; //전체 문자 개수
int err_num = 0; //오류 개수
int cw_num = 0;
string gen = "";
string dataword = "";
int padding = 0;
//prototype
string asc_bin(unsigned char asc);
int bin_dec(int num);
string mod_gen(string codeword);
void check(string codeword);
string bin_char(string binary);

int main(int argc, char** argv) {

	if (argc == 6) {

		char buff;
		string codeword = "";

		ifstream input;
		ofstream output;
		ofstream result;

		input.open(argv[1], ios::binary);
		if (input.fail()) {
			cout << "input file open error.";
			return 1;
		}
		
		output.open(argv[2], ios::binary); //복원 결과
		if (output.fail()) {
			cout << "output file open error.";
			return 1;
		}

		result.open(argv[3], ios::binary); //오류 개수
		if (result.fail()) {
			cout << "result file open error.";
		}
		gen = argv[4];
		dw_size = stoi(argv[5]);
		cw_size = dw_size + gen.length() - 1;
		if (dw_size != 4 && dw_size != 8) {
			cout << "dataword size must be 4 or 8.";
		}
		
		
		//buff = input.get();
		vector<char>data;
		while (true)
		{
			buff = input.get();
			if (input.fail())
			{
				break;
			}
			data.push_back(buff);
			//string bin = asc_bin(buff);
			//codeword += bin;
			//cout << bin << " ";
		}
				
		int ascii;
		string temp;
		for (vector<char>::iterator i = data.begin(); i !=data.end(); i++)
		{
			ascii = *i;
			temp = bitset<8>(ascii).to_string();
			codeword += temp;
		}


		string pad = codeword.substr(0, 8);
		padding = (bin_dec(stoi(pad)));

		codeword = codeword.substr(8 + padding);

		
		check(codeword);
		//cout << codeword;
		//cout << cw_num << " " << err_num << " ";
		result << cw_num << " " << err_num;

		for (int i = 0;i < dataword.size();i += 8) {
			string tmp = dataword.substr(i, 8);
			output << bin_char(tmp);

		}

		input.close();
		output.close();
		result.close();
	}

	else {
		cout << "usage:./crc_encoder input_file output_file result_file generator dataword_size\n";
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

int bin_dec(int num) {
	int i = 0;
	int res = 0;
	int temp = 0;
	while (num >= 1) {
		temp = num % 10;
		res += temp * pow(2, i);
		num /= 10;
		i++;
	}

	return res;
}

string mod_gen(string code) {
	//나머지가 0이면 오류없음
	string divident=code;
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
	
	return remainder;

}

void check(string codeword) {
	string code;

	int len = dw_size + gen.size() - 1;
	for (int i = 0;i < codeword.length();i+=len) {
		string temp = codeword.substr(i, len);
		string remain = mod_gen(temp);
		//cout << temp << " " << remain << "\n";
		int chk = stoi(remain);
		if (chk != 0) {
			err_num++;
		}
		dataword += temp.substr(0, dw_size);
		cw_num++;
		
	}
	
	return;

}
string bin_char(string binary){
	
	string c;
	stringstream sstream(binary);
	bitset<8> bit;

	sstream >> bit;
	c = char(bit.to_ulong());

	return c;
}