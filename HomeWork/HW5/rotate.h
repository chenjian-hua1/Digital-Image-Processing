#include <cmath>
using namespace std;

int* rotate_matrix(const int *f, double theta, int fh, int fw, int &gh, int &gw) {
    double f_centX = (fw-1.0)/2, f_centY = (fh-1.0)/2;
    double sinA = sin(theta*M_PI/180.0), cosA = cos(theta*M_PI/180.0);

    gw = fh * abs(sinA) + fw * abs(cosA);
    gh = fh * abs(cosA) + fw * abs(sinA);
    int* g = new int[gw*gh];

    double new_x, new_y, alpha, beta, a, b, c;
    double g_centX = (gw-1.0)/2, g_centY = (gh-1.0)/2;
    
    // 內差法 (先將新圖index 反旋轉 看對照的原圖index)
    for (int y=0; y<gh; y++) {
        for (int x=0; x<gw; x++) {
            // y = −x'sinθ + y'cosθ 從中心點(cy, cx)旋轉
            new_y = -(x-g_centX)*sinA + (y-g_centY)*cosA + f_centY;
            // x = x'cosθ + y'sinθ
            new_x = (x-g_centX)*cosA + (y-g_centY)*sinA + f_centX;

            // 是否介於旋轉前的長寬範圍內
            if (round(new_x)>=0 && round(new_x)<fw && round(new_y)>=0 && round(new_y)<fh) {
                if (new_x<0) new_x = 0;
                else if (new_x>fw-1) new_x = fw-1;
                if (new_y<0) new_y = 0;
                else if (new_y>fh-1) new_y = fh-1;

                alpha = new_x - floor(new_x);
                beta = new_y - floor(new_y);
                
                int x_floor = floor(new_x), x_ceil = ceil(new_x); 
                int y_floor = floor(new_y), y_ceil = ceil(new_y);

                a = (1-alpha)*f[y_ceil*fw + x_floor] + alpha*f[y_ceil*fw + x_ceil];
                b = (1-alpha)*f[y_floor*fw + x_floor] + alpha*f[y_floor*fw + x_ceil];
                c = (1-beta)*b + beta*a;

                g[y*gw + x] = (int)(c+0.5);
            }
            else {
                g[y*gw + x] = 0;
            }
        }

    }

    return g;
}