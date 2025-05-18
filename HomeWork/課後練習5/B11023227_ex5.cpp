#include <iostream>
#include <iomanip> // 用於 std::setprecision, std::setfill, std::setw

using namespace std;

int main()
{
	double m[3][3] = {
		{1.0/9, 1.0/9, 1.0/9},
		{1.0/9, 1.0/9, 1.0/9},
		{1.0/9, 1.0/9, 1.0/9}	
	};
	double f[5][5]={{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,24,25}};
	double f_padding[7][7] = {0};
	double g1[3][3] = {0};
	double g2[5][5] = {0};
		
//	for(int k=0;k<=2;k++)
//	{ 
//		for(int p=0;p<=2;p++)
//			cout << m[k][p] << " ";
//		cout << endl;	
//	}
//
//	for(int k=-1;k<=1;k++)
//	{ 
//		for(int p=-1;p<=1;p++)
//			cout << m[k+1][p+1] << " ";
//		cout << endl;	
//	}	
//
//	for(int i=0;i<=4;i++)
//	{ 
//		for(int j=0;j<=4;j++)
//			cout << f[i][j] << " ";
//		cout << endl;	
//	}	

	for(int i=1;i<=5;i++)
	{ 
		for(int j=1;j<=5;j++) 
			f_padding[i][j] = f[i-1][j-1];
	}
	
	for (int i=0; i<3; i++) {
		for (int j=0;j<3;j++) {
			for (int ii=0; ii<3; ii++) {
				for (int jj=0; jj<3; jj++)
					g1[i][j]+=(f[i+ii][j+jj]*m[ii][jj]);
			}
		}
	}
	
	for (int i=0; i<5; i++) {
		for (int j=0;j<5;j++) {
			for (int ii=0; ii<3; ii++) {
				for (int jj=0; jj<3; jj++)
					g2[i][j]+=(f_padding[i+ii][j+jj]*m[ii][jj]);
			}
		}
	}
	
	// 設定固定小數點格式，並保留小數2位
    // cout << fixed << setprecision(2);

    // 若需保證整數部分有3位，可以用 std::setw 和 std::setfill 填充
    // cout << setfill('0') << setw(6) << number << endl;
	
	//show g1 3x3
	cout << "3x3" << "----------------------------------" << endl;
	for (int i=0; i<3; i++) {
		for (int j=0;j<3;j++)
			cout << setfill(' ') << setw(8) << g1[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	
	//show g2 5x5
	cout << "5x5" << "----------------------------------" << endl;
	for (int i=0; i<5; i++) {
		for (int j=0;j<5;j++)
			cout << setfill(' ') << setw(8) << g2[i][j] << " ";
			// cout << g2[i][j] << " ";
		cout << endl;
	}
	
	return 0;
 } 
