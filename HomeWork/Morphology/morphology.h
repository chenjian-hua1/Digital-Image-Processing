#include <iostream>
#include <cstdlib> // for exit()
#include <cmath>

using namespace std;

#define ElementSize 3
#define DilationElement {1, 0, 1, \
                         0, 1, 0, \
                         1, 0, 1}
#define ErosionElement {0, 1, 0, \
                        1, 1, 1, \
                        0, 1, 0}

/* 膨脹 */
int *Dilation(const int *f, int w, int h, int *element=nullptr, int size=ElementSize) {
    if (element==nullptr) element = new int[size*size]DilationElement;

    int *g = new int[w*h]{0};
    int start_idx = -(size-1)/2, end_idx = (size-1)/2;
    
    for (int y=0; y<h; y++) { for (int x=0; x<w; x++) {
        // 黑點跳過
        if (f[y*w + x]==0) continue;
        
        for (int yy=start_idx; yy<=end_idx; yy++) { for (int xx=start_idx; xx<=end_idx; xx++) {
            int kernel_val = element[(yy-start_idx)*size + (xx-start_idx)];
            // kernel數值為0 或 超出圖片邊界
            if (kernel_val==0 || (y+yy<0) || (y+yy>h-1) || (x+xx<0) || (x+xx>w-1)) continue;

            g[(y+yy)*w + x+xx] = 255;
        }}
    }}
    
    return g;
}



/* 侵蝕 */
int *Erosion(const int *f, int w, int h, int *element=nullptr, int size=ElementSize) {
    if (element==nullptr) element = new int[size*size]ErosionElement;

    int *g = new int[w*h]{0};
    int start_idx = -(size-1)/2, end_idx = (size-1)/2;
    
    for (int y=0; y<h; y++) { for (int x=0; x<w; x++) {
        // 黑點跳過
        if (f[y*w + x]==0) continue;
        
        // 白點是否保留
        bool iskeep = true;

        for (int yy=start_idx; yy<=end_idx; yy++) { for (int xx=start_idx; xx<=end_idx; xx++) {
            int kernel_val = element[(yy-start_idx)*size + (xx-start_idx)];
            // kernel數值為0 或 超出圖片邊界
            if (kernel_val==0 || (y+yy<0) || (y+yy>h-1) || (x+xx<0) || (x+xx>w-1)) continue;

            // kernel和像素重合
            iskeep = f[(y+yy)*w + (x+xx)]!=0;

            // 如果不保留 -> 像素直接給黑色
            if (!iskeep) goto exit_loop;
        }}
        exit_loop:
            g[y*w + x] = iskeep ? 255:0;
    }}
    
    return g;
}



/* Open : 侵蝕 -> 膨脹 */
int *Open(
    const int *f, int w, int h, int *erosion_element=nullptr, 
    int *dilation_element=nullptr, int size=ElementSize
) {
    int *g;

    // Step1 -> 侵蝕
    g = Erosion(f, w, h, erosion_element, size);

    // Step2 -> 膨脹
    g = Dilation(g, w, h, dilation_element, size);

    return g;
}



/* Close : 膨脹 -> 侵蝕 */
int *Close(
    const int *f, int w, int h, int *dilation_element=nullptr, 
    int *erosion_element=nullptr, int size=ElementSize
) {
    int *g;

    // Step1 -> 膨脹
    g = Dilation(f, w, h, erosion_element, size);

    // Step2 -> 侵蝕
    g = Erosion(g, w, h, dilation_element, size);

    return g;
}