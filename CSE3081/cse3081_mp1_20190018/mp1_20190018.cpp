#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<cstdio>
#include<time.h>
#include<stdlib.h>

using namespace std;
int n, m;
int** arr;
int** dp1;
int** dp2;

ifstream input;
ofstream output;
int i, j,k,s;
int space = -16;

clock_t start, ending;

void init() {
	string str;
	int tmp = 0;
	j = -1;
	string s="";
	vector<int>num;
	
	while (!input.eof()) {
		getline(input, str);
		if (j == -1) {
			for (i = 0;i < str.size();i++) {
				if (str[i] - '0' != space) {
					s += str[i];
				}
				else {
					n = stoi(s);
					s = "";
				}
			}
			m = stoi(s);
			arr = new int* [n];
			for (i = 0;i < n;i++) {
				arr[i] = new int[m];
			}
			
		}
		else {
			s = "";
			for (i = 0;i < str.size();i++) {
				if (str[i] - '0' != space) {
					s += str[i];
				}
				else {
					tmp = stoi(s);
					num.push_back(tmp);
					s = "";
				}
				
			}
			if (s != "") {
				tmp = stoi(s);
				num.push_back(tmp);
				s = "";
			}
			
			
		}
		
		j++;
	}
	/*for (i = 0;i < num.size();i++) {
		cout << num[i] << " ";
	}*/
	for (i = 0;i < n;i++) {
		for (j = 0;j < m;j++) {
			arr[i][j] = num[k++];
			//cout << arr[i][j] << " ";
		}
		//cout << "\n";
	}
	
	return;
}
int N6() {
	//������ n**2
	//������~���γ���, ���γ��� ���ؼ� ->n**2
	//������~�������� ���ϴµ� ->n**2
	
	int sx=0, sy =0;
	int ex = 0, ey = 0;
	int res = -1;
	for (i = 0;i < n;i++) {
		for (j = 0;j < m;j++) {
			sx = i; sy = j;

			for (k = 0;k < n;k++) {
				for (s = 0;s < m;s++) {
					ex = k;ey = s;

					int sum = 0;
					for (int x = sx;x <= ex;x++) {
						for (int y = sy;y <= ey;y++) {
							//cout << arr[x][y] << " ";
							sum += arr[x][y];
						}
					}
					//cout << sum << "\n";
					res = max(res, sum);
				}
			}
		}
	}
	//cout << res << "\n";
	return res;
}




int N3() {
	//i=0~M
	//  j=i~M  
	//    k=0~N(���پ� ���ϱ� tmp[i]+=arr[k][j] -> MSSS ȣ��
	int ThisSum, CurSum,MaxSum;
	ThisSum=CurSum = MaxSum = 0;
	//MaxLeft = MaxRight = MaxTop = MaxBottom = 0;

	vector<int>v(m, 0);
	int flag = 0;
	for (i = 0;i < m;i++) {
		// �� row�� 0~m-1, 1~m-1 .... ���� �� ����
		v.assign(m, 0);
		for (j = i;j < m;j++) {
			for (k = 0;k < n;k++) {
				v[k]+= arr[k][j];
				
			}
			CurSum = 0;
			ThisSum = 0;
			for (s = 0;s < n;s++) {
				ThisSum += v[s];
				//MaxSum = max(ThisSum, MaxSum);
				if (ThisSum > CurSum) {
					CurSum = ThisSum;
					flag = 1;
				}
				else if (ThisSum < 0) {
					ThisSum = 0;
				}
			}

			if (!flag) {
				CurSum = v[0];
				for (int i = 1;i < n;i++) {
					if (v[i] > CurSum) {
						CurSum = v[i];
					}
				}
			}
			
			if (CurSum > MaxSum) {
				MaxSum = CurSum;

			}
			
		}
	}
	//cout << MaxSum;
	return MaxSum;
	
}


int N4() {
	int MaxSum = -1, ThisSum = 0;
	int MaxLeft, MaxRight, MaxTop, MaxBottom;
	MaxLeft = MaxRight = MaxTop = MaxBottom = 0;

	
	dp1 = new int* [n+1];
	for (i = 0;i <= n;i++) {
		dp1[i] = new int[m+1];
		//dp2[i] = new int[m + 1];
		for (j = 0;j <= m;j++) {
			dp1[i][j] = 0;
		}
	}
	
	for (i = 1; i <= n; i++) {
		for (j = 1;j <= m; j++) {
			dp1[i][j] = dp1[i - 1][j] + dp1[i][j - 1] - dp1[i - 1][j - 1] + arr[i-1][j-1];
			//cout << dp1[i][j] << " ";
		}
		//cout << "\n";
	}
	
	//0,0 ~n-1,m-1
	for (i = 1;i <= n;i++) {
		for (j = i;j <= n;j++) {
			
			for (k = 1;k <= m;k++) {

				for (s = k;s <= m;s++) {
					ThisSum = dp1[j][s] - dp1[j][k - 1] - dp1[i - 1][s] + dp1[i - 1][k - 1];
				
					//cout << ThisSum << " ";
					if (ThisSum > MaxSum) {
						MaxSum = ThisSum;
					}
					//cout << ThisSum << " ";
				}
				//cout << "\n";
				
			}
		}
	}
	
	//cout << MaxSum;
	return MaxSum;
}



int main(int argc, char*argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	if (argc != 3) {
		cout << "Error!";
		exit(1);
	}
	input.open(argv[1]);
	if (input.fail()) {
		cout << "File not Found";
		exit(1);
	}
	
	init();
	input.close();
	string t = argv[2];

	string str = argv[1];
	string fileName = "result_"+str;
	//N4();
	
	output.open(fileName);
	output<<str<<"\n";
	output << t << "\n" << n << "\n" << m << "\n";
	if (t == "3") {
		
		start = clock();
		int n3 = N3();
		ending = clock();
		output << n3 << "\n" << 1000* (double)(ending-start)/CLOCKS_PER_SEC;
	}
	else if (t == "2") {
		//output << 4 << "\n" << n << "\n" << m << "\n";
		start = clock();
		int n4 = N4();
		ending = clock();
		output<< n4 << "\n" << 1000* (double)(ending-start)/CLOCKS_PER_SEC;
	}
	else if (t == "1") {
		//output << 6 << "\n" << n << "\n" << m << "\n";
		start = clock();
		int n6 = N6();
		ending = clock();
		output << n6<<"\n" << 1000* (double)(ending-start)/CLOCKS_PER_SEC;
	}
	else {
		output << "errorrrr";
	}
	output.close();
	/*
	
	cout << n3 << "\n" << n6;*/
	
	return 0;
}