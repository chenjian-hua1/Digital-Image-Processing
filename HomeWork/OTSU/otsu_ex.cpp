#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    vector<int> hist = {15, 0, 0, 0, 0, 0, 0, 0, 70, 110, 45, 80, 40, 0, 0, 0};
    int total = accumulate(hist.begin(), hist.end(), 0);

    vector<double> prob(16), levels(16);
    for (int i = 0; i < 16; ++i) {
        prob[i] = static_cast<double>(hist[i]) / total;
        levels[i] = i;
    }

    // 方法一：最大類間變異（Otsu）
    double max_between_var = 0, min_within_var = 1e9, max_avg_diff = 0;
    int best_thresh_otsu = 0, best_thresh_within = 0, best_thresh_avg = 0;

    for (int t = 1; t < 16; ++t) {
        double w0 = 0, mu0 = 0;
        for (int i = 0; i < t; ++i) {
            w0 += prob[i];
            mu0 += levels[i] * prob[i];
        }
        if (w0 == 0) continue;
        mu0 /= w0;

        double w1 = 1 - w0;
        if (w1 == 0) continue;

        double mu1 = 0;
        for (int i = t; i < 16; ++i) {
            mu1 += levels[i] * prob[i];
        }
        mu1 /= w1;

        // 類間變異
        double between_var = w0 * w1 * (mu0 - mu1) * (mu0 - mu1);
        if (between_var > max_between_var) {
            max_between_var = between_var;
            best_thresh_otsu = t;
        }

        // 類內變異
        double sigma0 = 0, sigma1 = 0;
        for (int i = 0; i < t; ++i) {
            sigma0 += prob[i] * (levels[i] - mu0) * (levels[i] - mu0);
        }
        sigma0 /= w0;

        for (int i = t; i < 16; ++i) {
            sigma1 += prob[i] * (levels[i] - mu1) * (levels[i] - mu1);
        }
        sigma1 /= w1;

        double within_var = w0 * sigma0 + w1 * sigma1;
        if (within_var < min_within_var) {
            min_within_var = within_var;
            best_thresh_within = t;
        }

        // 平均最大差（僅考慮 |mu0 - mu1|）
        double avg_diff = abs(mu0 - mu1);
        if (avg_diff > max_avg_diff) {
            max_avg_diff = avg_diff;
            best_thresh_avg = t;
        }
    }

    cout << "Otsu (最大類間變異) Threshold: " << best_thresh_otsu << endl;
    cout << "最小類內變異 Threshold: " << best_thresh_within << endl;
    cout << "最大平均差 Threshold: " << best_thresh_avg << endl;

    return 0;
}
