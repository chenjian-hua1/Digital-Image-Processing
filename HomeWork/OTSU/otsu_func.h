#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

/* OTSU 二值化 */ 
void otsu(const int *f, int *g, int w, int h, int &threshold) {
    /* 計算直方分佈 */
    int hist[256] = {0};
    for (int px=0; px<w*h; px++)
        hist[f[px]]++;
    // for (int val=0; val<256; val++) cout << "hist[" << val << "]=" << hist[val] << endl;

    /* 計算切分後左右兩部分的標準差 求argmin(w1*σ1 + w2*σ2) */
    // 像素點數量
    int total_pxs, forward_pxs, bg_pxs;
    // 背景 前景權重
    double w1, w2;
    // 背景、前景所有亮度值的加權平均
    double u1, u2;
    // 背景、前景的標準差平方(變異數) 和 兩變異數的加權平均
    double std_dev1_sq, std_dev2_sq, std_dev_w_sq;
    // 兩變異數的加權平均 最小值
    double min_std_dev_sq;
    // 兩變異數的加權平均最小值 索引值
    int argmin_std_dev_sq = 0;

    total_pxs = w*h;
    // 設定閾值為0~256 找 argmin(w1*σ1 + w2*σ2)
    for (int th=1; th<256; th++) {
        forward_pxs = 0; bg_pxs = 0;
        // 背景像素點數量 (左側總和)
        for (int val=0; val<th; val++)
            bg_pxs+=hist[val];
        // 避免後面處理時除0
        if (bg_pxs==0) continue;

        // 大於等於嗎 如果那條線的亮度值出現較多次呢？
        // 前景像素點數量 (右側總和)
        for (int val=th; val<256; val++)
            forward_pxs+=hist[val];
        if (forward_pxs==0) continue;
        
        // cout << "background pixels=" << bg_pxs << ", forward pixels=" << forward_pxs << endl;

        w1 = (double)bg_pxs/total_pxs;
        w2 = (double)forward_pxs/total_pxs;
        // cout << "w1=" << w1 << ", w2=" << w2 << ", w1+w2=" << w1+w2 << endl;

        u1 = 0; u2 = 0;
        // 背景所有亮度值的加權平均
        for (int val=0; val<th; val++)
            u1 += ((double)val * (double)hist[val]/bg_pxs);

        // 前景所有亮度值的加權平均
        for (int val=th; val<256; val++)
            u2 += ((double)val * (double)hist[val]/forward_pxs);
        // cout << "u1=" << u1 << ", " << "u2=" << u2 << endl;

        std_dev1_sq = 0; std_dev2_sq = 0;
        // 計算背景的變異數 (標準差平方)
        for (int val=0; val<th; val++)
            // square(i-u1) * (p[i] / w1)
            // std_dev1_sq += ( (val-u1) * ((hist[val]/total_pxs) / (bg_pxs/total_pxs)) );
            std_dev1_sq += (pow(val-u1, 2) * hist[val]/bg_pxs);

        // 計算前景的變異數(標準差平方)
        for (int val=th; val<256; val++)
            std_dev2_sq += (pow(val-u2, 2) * hist[val]/forward_pxs);
        // cout << "σ1_squared=" << std_dev1_sq << ", σ2_squared=" << std_dev2_sq << endl;

        // 計算兩變異數的加權平均
        std_dev_w_sq = (w1*std_dev1_sq) + (w2*std_dev2_sq);
        // 還沒有最小值
        if (argmin_std_dev_sq==0) {
            min_std_dev_sq = std_dev_w_sq;
            argmin_std_dev_sq = th;
            continue;
        }
        // 更新 兩變異數的加權平均 最小值
        if (std_dev_w_sq<min_std_dev_sq) {
            min_std_dev_sq = std_dev_w_sq;
            argmin_std_dev_sq = th;
        }
    }
    // cout << "argmin(w1*σ1 + w2+σ2)=" << argmin_std_dev_sq << endl;

    threshold = argmin_std_dev_sq;
    /* 根據算出來的閾值 argmin(w1*σ1 + w2+σ2) 進行二值化 */
    for (int px=0; px<w*h; px++)
        g[px] = (f[px] < argmin_std_dev_sq) ? 0:255;
}