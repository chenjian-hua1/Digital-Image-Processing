#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double m[3][3]= {
		{-1,0,1},
		{-1,0,1},
		{-1,0,1}
	};
	double f[5][5]= {
		{255,128,255,50,255},
		{255,128,255,50,255},
		{255,128,255,50,255},
		{255,128,255,50,255},
		{255,128,255,50,255}
	};
	double f_temp[7][7]={0};	
	double g1[3][3]={0};
	double g2[5][5]={0};

	// for(int i=0;i<=4;i++)
	// { 
	// 	for(int j=0;j<=4;j++)
	// 		cout << f[i][j] << " ";
	// 	cout << endl;	
	// }	

	for(int i=1;i<6;i++)
	{ 
		for(int j=1;j<6;j++)
			f_temp[i][j] = f[i-1][j-1];
	}
	
	// g1 conv
	for (int y=0; y<3; y++) {
		for (int x=0; x<3; x++) {
			for (int yk=0; yk<3; yk++) {
				for (int xk=0; xk<3; xk++)
					g1[y][x]+=(f[y+yk][x+xk]*m[yk][xk]);
			}
		}
	}
	
	cout << "g1正規化前" << endl;
	//show g1 3x3
	for(int y=0;y<3;y++)
	{ 
		for(int x=0;x<3;x++)
			cout << g1[y][x] << " ";
		cout << endl;	
	}
	cout << endl;

	// g2 conv
	for (int y=0; y<5; y++) {
		for (int x=0; x<5; x++) {
			for (int yk=0; yk<3; yk++) {
				for (int xk=0; xk<3; xk++)
					g2[y][x]+=(f_temp[y+yk][x+xk]*m[yk][xk]);
			}
		}
	}

	cout << "g2正規化前" << endl;
	//show g2 5x5
	for(int y=0; y<5; y++)
	{ 
		for(int x=0;x<5;x++)
			cout << g2[y][x] << " ";
		cout << endl;	
	}	
	cout << endl;

	// Normalize g1
    double min_val1 = g1[0][0], max_val1 = g1[0][0];
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(g1[i][j] < min_val1) min_val1 = g1[i][j];
            if(g1[i][j] > max_val1) max_val1 = g1[i][j];
        }
    }
    
    // Normalize g2
    double min_val2 = g2[0][0], max_val2 = g2[0][0];
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            if(g2[i][j] < min_val2) min_val2 = g2[i][j];
            if(g2[i][j] > max_val2) max_val2 = g2[i][j];
        }
    }

    // Print g1 (3x3) normalized to 0-255
    cout << "g1正規化後:" << endl;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(max_val1 != min_val1)
                g1[i][j] = round(((g1[i][j] - min_val1) * 255) / (max_val1 - min_val1));
            cout << g1[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Print g2 (5x5) normalized to 0-255
    cout << "g2正規化後:" << endl;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            if(max_val2 != min_val2)
                g2[i][j] = round(((g2[i][j] - min_val2) * 255) / (max_val2 - min_val2));
            cout << g2[i][j] << " ";
        }
        cout << endl;
    }

	return 0;
 } 