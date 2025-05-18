#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

const int WIDTH = 100;
const int HEIGHT = 100;
const int R_MIN = 5;
const int R_MAX = 50;

const int ACCUM_A = WIDTH;
const int ACCUM_B = HEIGHT;
const int ACCUM_R = R_MAX + 1;

int accumulator[ACCUM_A][ACCUM_B][ACCUM_R] = {{{0}}};

struct Point {
    int x;
    int y;
};

void hough_circle_transform(const vector<Point>& points) {
    int i, a, b, r, angle_step;
    double theta;

    for (i = 0; i < points.size(); ++i) {
        int x = points[i].x;
        int y = points[i].y;

        for (r = R_MIN; r <= R_MAX; ++r) {
            for (angle_step = 0; angle_step < 360; angle_step += 10) {
                theta = angle_step * M_PI / 180.0;
                a = static_cast<int>(round(x - r * cos(theta)));
                b = static_cast<int>(round(y - r * sin(theta)));

                if (a >= 0 && a < ACCUM_A && b >= 0 && b < ACCUM_B) {
                    accumulator[a][b][r]++;
                }
            }
        }
    }
}

void find_circles(int threshold) {
    int a, b, r;
    for (a = 0; a < ACCUM_A; ++a) {
        for (b = 0; b < ACCUM_B; ++b) {
            for (r = R_MIN; r <= R_MAX; ++r) {
                if (accumulator[a][b][r] >= threshold) {
                    cout << "Circle detected: center=(" << a << ", " << b
                         << "), radius=" << r
                         << ", votes=" << accumulator[a][b][r] << endl;
                }
            }
        }
    }
}

int main() {
    vector<Point> points;
    Point p;

    // �����b��W�����I (���߬��b 50, 50�A�b�| 20)
    for (int angle = 0; angle < 360; angle += 30) {
        double rad = angle * M_PI / 180.0;
        p.x = static_cast<int>(round(50 + 20 * cos(rad)));
        p.y = static_cast<int>(round(50 + 20 * sin(rad)));
        points.push_back(p);
    }

    // �K�[�@�����T�I
    p.x = 10; p.y = 80; points.push_back(p);
    p.x = 70; p.y = 90; points.push_back(p);

    hough_circle_transform(points);

    cout << "Detected circles with votes >= 6:\n";
    find_circles(6);

    return 0;
}

