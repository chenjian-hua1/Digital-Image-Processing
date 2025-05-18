#include <iostream>
#include <cstdlib> // for exit()
#include <cmath>

using namespace std;

#define pt_dist_tolerance 2*sqrt(2.0)

// 定義 Point 結構有 (x,y)
struct Point
{
    int x, y;
};

double CalculateDist(Point pt1, Point pt2) {
    return sqrt( pow(pt2.x-pt1.x, 2) + pow(pt2.y-pt1.x, 2) );
}



/* 
f: 圖片
w, h: 圖片長寬
Pt_th: 判定要通過多少點 才算線
ThetaStep: 要補捉多精細角度的線 (角度 1~45)
PtDistTolerance: 線上通過點容許的最大間距
*/
void LineDetect(const int* f, int w, int h, int Pt_th, int ThetaStep, double PtDistTolerance=pt_dist_tolerance) {
    /* 前置處理 */
    if (ThetaStep<1 || ThetaStep>45) {
        cout << "LineDetect Error: ThetaStep Valid range is (-45, 45)" << endl;
        exit(1);
    }

    // 查看圖片有幾個白點
    int white_pts = 0;
    for (int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            // Color 不是黑0 或 白255
            if (f[x + y*w]!=0 && f[x + y*w]!=255) {
                cout << "LineDetect Error: Detect color is not 0 or 255 (Color is " << f[x + y*w] << ")" << endl;
                exit(1);
            }

            // 如果是白色時加1
            if (f[x + y*w]==255) white_pts++;
        }
    }

    // 全黑 -> 結束程式
    if (white_pts==0) exit(1);


    /* 偵測不 同角度、r值 線是否存在 */
    int max_r = (w > h) ? w:h;
    int r;

    // 記錄上次出現在同一條線的點位置
    Point *LineLastPt = new Point[max_r];

    // r值線上出現的點數
    double *r_pts = new double[max_r];

    // 不同角度下 -> 用每個點計算r值 計數同r值的次數
    for (int theta=-90; theta<=90; theta+=ThetaStep) {
        double radian = theta * M_PI/180;
        double SinTheta = sin(radian), CosTheta = cos(radian);

        // 初始化
        for (int i=0; i<max_r; i++) {
            LineLastPt[i].x = -1; LineLastPt[i].y = -1;
            r_pts[i] = 0;
        }

        for (int x=0; x<w; x++) {
            for (int y=0; y<h; y++) {
                // 黑點跳過
                if (f[x + y*w]==0) continue;

                // 計算r值
                r = (int)round(y*SinTheta + x*CosTheta);
                
                Point now_pt; now_pt.x = x; now_pt.y = y;
                Point last_pt = LineLastPt[r];

                // 不對啊 如果同一條線上 有出現兩點 但兩點距離差很大呢？？？

                // 線上還沒點 或 上點跟當前點距離在接受範圍內
                if (last_pt.x==-1 || CalculateDist(last_pt, now_pt)<=PtDistTolerance)
                    r_pts[r]++;
                else
                    r_pts[r] = 0;
            }
        }
        
        for (int i=0; i<max_r; i++) {
            // 小於設定的最小通過點數
            if (r_pts[i]<Pt_th) continue;

            cout << "Detect Line in theta=" << theta << " r=" << i << " have " << r_pts[i] << " points" << endl;
        }
    }

    
}