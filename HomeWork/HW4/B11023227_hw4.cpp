#include <iostream>
#include <cstring>
#include "scale.h"
#include "bmp_reader.h"

using namespace std;

#define w 5
#define h 5
#define scale 2.6

#define NewWidth (int)(w * scale)
#define NewHeight (int)(h * scale)

int main()
{
	int f[NewHeight][NewWidth];
	// int f[h][w]={
	// 	{1,2,3,4,5},
	// 	{6,7,8,9,10},
	// 	{11,12,13,14,15},
	// 	{16,17,18,19,20},
	// 	{21,22,23,24,25}
	// };

	string filename = "Lena.bmp"; // 替換為你的灰階 BMP 檔案路徑
    int width, height;

    // 讀取灰階 BMP 並轉為一維陣列
    int* pixels = readGrayscaleBMPToArray(filename, width, height);
    if (pixels) {
        cout << "圖像尺寸: " << width << " x " << height << endl;
        // 範例：輸出第一個像素的灰度值
        cout << "第一個像素灰度值: " << pixels[0] << endl;

        // 釋放動態分配的記憶體
        // delete[] pixels;
        // pixels = nullptr;
    }

	int* g;
	int gw, gh;
	g = scaling(pixels, width, height, scale, true, gw, gh);

	for (int y=0; y<10; y++) {
		for (int x=0; x<10; x++) 
			cout << g[y*gw + x] << " ";

		cout << endl;
	}

	return 0;
} 

