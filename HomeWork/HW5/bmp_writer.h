#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct {
    unsigned short bfType;      // BMP signature "BM"
    unsigned int bfSize;        // File size in bytes
    unsigned short bfReserved1; // Reserved, must be 0
    unsigned short bfReserved2; // Reserved, must be 0
    unsigned int bfOffBits;     // Offset to pixel data
} BITMAPFILEHEADER;

typedef struct {
    unsigned int biSize;        // Size of this header (40)
    int biWidth;               // Image width
    int biHeight;              // Image height
    unsigned short biPlanes;    // Number of color planes (1)
    unsigned short biBitCount;  // Bits per pixel (8)
    unsigned int biCompression; // Compression method (0)
    unsigned int biSizeImage;   // Image size
    int biXPelsPerMeter;       // Horizontal resolution
    int biYPelsPerMeter;       // Vertical resolution
    unsigned int biClrUsed;     // Colors used (256)
    unsigned int biClrImportant;// Important colors (0)
} BITMAPINFOHEADER;

typedef struct {
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
    unsigned char rgbReserved;
} RGBQUAD;
#pragma pack(pop)

void save_bmp(const char* filename, int* pixels, int width, int height) {
    BITMAPFILEHEADER fileHeader = {0};
    BITMAPINFOHEADER infoHeader = {0};
    RGBQUAD palette[256] = {0};
    
    // Calculate padding (each row must be multiple of 4 bytes)
    int padding = (4 - width % 4) % 4;
    int rowSize = width + padding;
    int imageSize = rowSize * height;
    
    // Fill file header
    fileHeader.bfType = 0x4D42; // "BM"
    fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
    fileHeader.bfSize = fileHeader.bfOffBits + imageSize;
    
    // Fill info header
    infoHeader.biSize = sizeof(BITMAPINFOHEADER);
    infoHeader.biWidth = width;
    infoHeader.biHeight = height;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 8;
    infoHeader.biCompression = 0;
    infoHeader.biSizeImage = imageSize;
    infoHeader.biXPelsPerMeter = 0;
    infoHeader.biYPelsPerMeter = 0;
    infoHeader.biClrUsed = 256;
    infoHeader.biClrImportant = 0;
    
    // Create grayscale palette
    for (int i = 0; i < 256; i++) {
        palette[i].rgbBlue = i;
        palette[i].rgbGreen = i;
        palette[i].rgbRed = i;
        palette[i].rgbReserved = 0;
    }
    
    // Open file
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    
    // Write headers
    fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
    fwrite(palette, sizeof(RGBQUAD), 256, fp);
    
    // Write pixel data (bottom-up order)
    unsigned char* row = (unsigned char*)malloc(rowSize);
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            // Extract 8-bit grayscale value (0-255)
            row[x] = (unsigned char)(pixels[y * width + x] & 0xFF);
        }
        // Add padding
        for (int i = 0; i < padding; i++) {
            row[width + i] = 0;
        }
        fwrite(row, rowSize, 1, fp);
    }
    
    free(row);
    fclose(fp);
}