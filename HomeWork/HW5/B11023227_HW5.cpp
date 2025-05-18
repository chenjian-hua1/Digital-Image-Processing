#include <iostream>
#include <cstring>
#include <iomanip>
#include "rotate.h"
#include "bmp_reader.h"
#include "bmp_writer.h"

using namespace std;

int main()
{
    // int f[5][5]={{1,2,3,4,5},
	// 		{6,7,8,9,10},
	// 		{11,12,13,14,15},
	// 		{16,17,18,19,20},
	// 		{21,22,23,24,25}};
    // int fh = 5, fw = 5;

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

    int gw, gh;
    int* g = rotate_matrix(pixels, 175, height, width, gh, gw);

    cout << "w',h' = " << gw << "," << gh << endl;
    // for (int y=0; y<gh; y++) {
    //     for (int x=0; x<gw; x++)
    //         cout << g[y*gw + x] << " ";
    //     cout << endl;
    // }

    // Save the image as a BMP file
    save_bmp("rotate.bmp", g, gw, gh);

	return 0;
} 