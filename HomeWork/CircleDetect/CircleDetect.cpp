#include <iostream>
#include <cstdlib> // for exit()
#include "CircleDetect.h"

using namespace std;

int main() {
    const int Width = 5, Height = 5;
    // int *f = new int[25]{
    //       0, 255, 255, 255,   0,
    //     255, 255, 255, 255, 255,
    //     255, 255, 255, 255, 255,
    //     255, 255, 255, 255, 255,
    //       0, 255, 255, 255,   0,
    // };
    int *f = new int[Width*Height] {
          0, 255, 255, 255,   0,
        255,   0,   0,   0, 255,
        255,   0, 255,  255, 255,
        255,   0, 255,   0, 255,
          0, 255, 255, 255,   0,
    };

    CircleDetect(f, Width, Height, 5, 1);
    return 0;
}