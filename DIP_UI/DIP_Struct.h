#ifndef DIP_STRUCT_H
#define DIP_STRUCT_H

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

#endif // DIP_STRUCT_H
