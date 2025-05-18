#include <cmath>
#include <fstream>
#include <cstdlib>
using namespace std;

#pragma pack(push, 2) // 確保結構體對齊方式與 BMP 檔案格式一致
struct BMPHeader {
    char signature[2]; // BM
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
#pragma pack(pop)

int* readGrayscaleBMPToArray(const string& filename, int& width, int& height) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "無法開啟檔案: " << filename << endl;
        return nullptr;
    }

    // 讀取 BMP 檔案頭
    BMPHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    // 檢查是否為有效的 BMP 檔案
    if (header.signature[0] != 'B' || header.signature[1] != 'M') {
        cout << "無效的 BMP 檔案" << endl;
        file.close();
        return nullptr;
    }

    // 檢查是否為 8 位元灰階 BMP
    if (header.bitsPerPixel != 8) {
        cerr << "僅支援 8 位元灰階 BMP" << endl;
        file.close();
        return nullptr;
    }

    // 獲取圖像尺寸
    width = header.width;
    height = header.height;

    // 計算每行像素的填充位元組（每行必須是 4 的倍數）
    int padding = (4 - (width % 4)) % 4;

    // 動態分配一維陣列
    int* pixelArray = new int[width * height];
    if (!pixelArray) {
        cout << "記憶體分配失敗" << endl;
        file.close();
        return nullptr;
    }

    // 移動到像素數據起始位置
    file.seekg(header.dataOffset, ios::beg);

    // 讀取像素數據
    for (int y = height - 1; y >= 0; --y) { // BMP 像素從下到上儲存
        for (int x = 0; x < width; ++x) {
            unsigned char gray;
            file.read(reinterpret_cast<char*>(&gray), 1); // 讀取灰度值
            pixelArray[y * width + x] = static_cast<int>(gray); // 儲存為 int
        }
        // 跳過填充位元組
        file.seekg(padding, ios::cur);
    }

    file.close();
    return pixelArray;
}