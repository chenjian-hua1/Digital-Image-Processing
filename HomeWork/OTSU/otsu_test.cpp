#include <iostream>
#include <format>
#include <vector>
#include <numeric>
#include <cmath>
#include "otsu_func.h"
#include "bmp_reader.h"
#include "bmp_writer.h"

using namespace std;

// void otsu(const int *f, int *g, int w, int h);

int main() {
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

    // int img[14] = {1, 0, 3, 4, 5, 5, 2, 190, 200, 200, 255, 242, 233, 233};
    // int out_img[14];

    int *out_img = new int[width*height];
    int threshold;

    otsu(pixels, out_img, width, height, threshold);
    cout << "閾值: " <<  threshold << endl;
    
    save_bmp("OTSU.bmp", out_img, width, height);

    return 0;
}