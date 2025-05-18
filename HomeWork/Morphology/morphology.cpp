#include <iostream>
#include <cstdlib> // for exit()
#include "morphology.h"

using namespace std;

int main() {
    const int Width = 3, Height = 3;
    int *f = new int[Width*Height]{0, 255, 0, 
                                   255, 255, 255, 
                                   0, 255, 0};
    
    int *g = Dilation(f, Width, Height);
    cout << "Dilation" << endl;
    for (int y=0; y<Height; y++) { 
        for (int x=0; x<Width; x++) {
            cout << g[y*Width+x] << " ";
        }
        cout << endl;
    }
    cout << endl;

    g = Erosion(f, Width, Height);
    cout << "Erosion" << endl;
    for (int y=0; y<Height; y++) { 
        for (int x=0; x<Width; x++) {
            cout << g[y*Width+x] << " ";
        }
        cout << endl;
    }
    cout << endl;

    g = Open(f, Width, Height);
    cout << "Open" << endl;
    for (int y=0; y<Height; y++) { 
        for (int x=0; x<Width; x++) {
            cout << g[y*Width+x] << " ";
        }
        cout << endl;
    }
    cout << endl;

    g = Close(f, Width, Height);
    cout << "Close" << endl;
    for (int y=0; y<Height; y++) { 
        for (int x=0; x<Width; x++) 
            cout << g[y*Width+x] << " ";
        cout << endl;
    }
    cout << endl;

    return 0;
}