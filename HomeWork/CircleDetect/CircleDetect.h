#include <iostream>
#include <cstdlib> // for exit()
#include <cmath>

using namespace std;

// 定義 Point 結構有 (x,y)
struct Point {
    int x, y;
};

struct Intersect {
    double x, y;
};

// pts為圓線上的點數
struct Circle {
    int a, b, r, pts;
};

pair<Intersect, Intersect> FindCircleIntersect(Point pt1, int r1, Point pt2, int r2) {
    int x1 = pt1.x, y1 = pt1.y,
        x2 = pt2.x, y2 = pt2.y;
        
    // 計算圓心距離
    double d = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));

    // 圓交點
    Intersect intersect1 = {-1, -1}, intersect2 = {-1, -1};

    // 判斷是否有交點
    if (d > r1 + r2 || d < abs(r1 - r2) || d == 0) {
        return { intersect1, intersect2 }; // 無交點或圓重合
    }

    // 計算交點的參數
    double a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
    double x = x1 + a * (x2 - x1) / d;
    double y = y1 + a * (y2 - y1) / d;
    double x3 = (y2 - y1) * sqrt(r1 * r1 - a * a) / d;
    double y3 = (x2 - x1) * sqrt(r1 * r1 - a * a) / d;

    // 交點座標
    intersect1 = {x + x3, y - y3};
    intersect2 = {x - x3, y + y3};
    
    return { intersect1, intersect2 };
}



/*
f: 影像
w, h: 長寬
th: 至少要多少個圓型的交點
MinRadius: 能接受最小的圓半徑
RadiusStep: 半徑畫圓檢查的精細度
*/
void CircleDetect(const int *f, int w, int h, int th, int MinRadius, int RadiusStep=1) {
    // 檢查是否為二值化影像
    for (int pt=0; pt<w*h; pt++) {
        if (f[pt]!=0 && f[pt]!=255) {
            cout << "CircleDetect Error: Input Image is not Binary Image, Detect Color " << f[pt] << endl;
            exit(1);
        }
    }

    // 半徑不可能超過半張圖片
    int Max_r = ((w<h) ? (w/2):(h/2)) + 1;
    if (RadiusStep>Max_r) {
        cout << "CircleDetect Error: RadiusStep > Half Image (Max Radius)" << endl;
        exit(1);
    }
    
    // 所有可能存在的圓型
    Circle *circles = new Circle[w*h*Max_r];
    for (int y=0; y<h; y++) { for (int x=0; x<w; x++) {
        for (int r=0; r<Max_r; r++) 
            circles[(y*w + x)*Max_r + r] = {x, y, r, 0};
    }}

    // 兩圓的交點
    pair<Intersect, Intersect> intersects;

    // 圓心 
    Point circ_cent1, circ_cent2; 

    // 兩圓交點
    Intersect intersect1, intersect2;

    for (int r=MinRadius; r<Max_r; r+=RadiusStep) {
        for (int y=0; y<h; y+=1) { for (int x=0; x<w; x+=1) {
            if (f[y*w + x]==0) continue;
            circ_cent1 = {x, y};
            
            // 朝右下方向尋找圓 右下方向點以半徑(r)畫圓找交點
            // 圓上兩點的距離不超過直徑 2*r
            for (int yy=0; yy<(2*r); yy++) { for (int xx=0; xx<(2*r); xx++) {
                if (y+yy>=h || x+xx>=w || f[(y+yy)*w + (x+xx)]==0) continue;
                
                circ_cent2 = {x+xx, y+yy};
                intersects = FindCircleIntersect(circ_cent1, r, circ_cent2, r);
                intersect1 = intersects.first; intersect2 = intersects.second; 

                if ((intersect1.x>=0 && intersect1.x<w) && (intersect1.y>=0 && intersect1.y<h)) 
                    circles[(int)round(intersect1.y*w + intersect1.x)*Max_r + r].pts++;

                if ((intersect2.x>=0 && intersect2.x<w) && (intersect2.y>=0 && intersect2.y<h))
                    circles[(int)round(intersect2.y*w + intersect2.x)*Max_r + r].pts++;
            }}

        }}
    }

    for (int idx=0; idx<w*h*Max_r; idx++) {
        if (circles[idx].pts>th)
            cout << "Circle a=" << circles[idx].a << " b=" << circles[idx].b << " r=" << circles[idx].r << " pts=" << circles[idx].pts << endl;
    } 
}