#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

const int THETA_STEPS = 180;     // Angle resolution
const int RHO_BINS = 500;        // Number of rho bins
int accumulator[THETA_STEPS][RHO_BINS] = {0};  // Hough accumulator

struct Point {
    int x;
    int y;
};

void hough_transform(const vector<Point>& points) {
    int i;
    int t;
    int r;
    double theta;
    double rho;
    int max_rho = RHO_BINS / 2;

    for (i = 0; i < points.size(); ++i) {
        int px = points[i].x;
        int py = points[i].y;

        for (t = 0; t < THETA_STEPS; ++t) {
            theta = t * M_PI / 180.0;
            rho = px * cos(theta) + py * sin(theta);
            r = static_cast<int>(round(rho)) + max_rho;

            if (r >= 0 && r < RHO_BINS) {
                accumulator[t][r]++;
            }
        }
    }
}

void find_lines(int threshold) {
    int t;
    int r;

    for (t = 0; t < THETA_STEPS; ++t) {
        for (r = 0; r < RHO_BINS; ++r) {
            if (accumulator[t][r] >= threshold) {
                double theta = t * M_PI / 180.0;
                double rho = r - (RHO_BINS / 2);

                cout << fixed << setprecision(2);
                cout << "Line detected: £c = " << t << "¢X, £l = " << rho
                     << ", votes = " << accumulator[t][r] << endl;
            }
        }
    }
}

int main() {
    vector<Point> points;

    Point p;

    p.x = 10; p.y = 10; points.push_back(p);
    p.x = 20; p.y = 20; points.push_back(p);
    p.x = 30; p.y = 30; points.push_back(p);
    p.x = 40; p.y = 40; points.push_back(p);
    p.x = 50; p.y = 50; points.push_back(p);
    p.x = 15; p.y = 30; points.push_back(p);
    p.x = 35; p.y = 60; points.push_back(p);
    p.x = 60; p.y = 20; points.push_back(p);
    p.x = 70; p.y = 25; points.push_back(p);
    p.x = 80; p.y = 10; points.push_back(p);

    hough_transform(points);

    cout << "Detected lines with votes >= 4:\n";
    find_lines(4);

    return 0;
}

