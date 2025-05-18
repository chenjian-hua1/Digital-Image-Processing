#include <iostream>
#include "LineDetect.h"

using namespace std;

int main() {
    const int Width = 5, Height = 5;
    int *f = new int[Width*Height] {
        255,   0, 255,   0, 255,
          0, 255, 255, 255,   0,
          0,   0, 255,   0,   0,
          0, 255, 255, 255,   0,
        255,   0, 255,   0, 255
    };

    LineDetect(f, Width, Height, 5, 45);
    return 0;
}