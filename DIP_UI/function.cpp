#include "function.h"

namespace DIP {

void QImage2Array(const QImage &image, int *&imageArray) {
    // Clean Mem
    delete[] imageArray;
    imageArray = nullptr;

    // Read Pixels
    int width = image.width(), height = image.height();
    imageArray = new int[width * height];

    for (int y = 0; y < height; ++y) { for (int x = 0; x < width; ++x)
            imageArray[y * width + x] = image.pixelColor(x, y).red(); // 灰階圖片，R=G=B
    }
}

QImage Array2QImage(const int *array, int width, int height) {
    // 檢查陣列是否有效
    if (!array || width <= 0 || height <= 0) {
        return QImage(); // 返回一個空的 QImage
    }

    // 創建一個空的灰階 QImage
    QImage image(width, height, QImage::Format_Grayscale8);

    // 填充圖片數據
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // 將灰階值寫入 QImage
            int grayValue = array[y * width + x] & 0xFF; // 確保灰階值在 0-255 範圍內
            image.setPixel(x, y, qRgb(grayValue, grayValue, grayValue));
        }
    }

    return image;
}

float textEdit2Float(QTextEdit *edit) {
    return edit->toPlainText().toFloat();
}

/* 負片 */
void negative(const int *f, int *&g, int w, int h) {
    g = new int[w*h];

    for (int i=0; i<w*h; i++)
        g[i] = 255-f[i];
}

/* 2D Convolution :
f: 輸入圖片（一維陣列）
width, height: 輸入圖片的寬高
filter: 濾波器（假設為正方形，size為filter_size * filter_size）
filter_size: 濾波器尺寸（必須為奇數，如3x3或5x5）
g: 輸出圖片（一維陣列)
*/
void Conv2D(const int *f, int *&g, int width, int height,
            const float *filter, int filter_size) {
    // 檢查濾波器尺寸是否為奇數
    if (filter_size % 2 == 0)
        throw std::invalid_argument("Filter size must be odd");

    // 計算輸出圖片的尺寸（無padding）
    int newWidth = width - filter_size + 1,
        newHeight = height - filter_size + 1;

    // 初始化輸出陣列
    g = new int[newWidth*newHeight]{0};

    // 執行卷積（stride=1，無padding）
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            float sum = 0.0f;
            // 對濾波器範圍內的每個元素進行卷積
            for (int fy = 0; fy < filter_size; ++fy) {
                for (int fx = 0; fx < filter_size; ++fx) {
                    sum += f[(y + fy) * width + (x + fx)] *
                           filter[fy * filter_size + fx];
                }
            }
            g[y * newWidth + x] = sum;
        }
    }
}

/* OTSU 二值化 */
void otsu(const int *f, int *&g, int w, int h, int &threshold) {
    /* 建立輸出圖片 */
    g = new int[w*h];

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
圓偵測
f: 影像
w, h: 長寬
th: 至少要多少個圓型的交點
MinRadius: 能接受最小的圓半徑
RadiusStep: 半徑畫圓檢查的精細度
*/
void CircleDetect(const int *f, int w, int h, int th, int MinRadius, int RadiusStep) {
    // 檢查是否為二值化影像
    for (int pt=0; pt<w*h; pt++) {
        if (f[pt]!=0 && f[pt]!=255) {
            qDebug() << "CircleDetect Error: Input Image is not Binary Image, Detect Color " << f[pt];
            exit(1);
        }
    }

    // 半徑不可能超過半張圖片
    int Max_r = ((w<h) ? (w/2):(h/2)) + 1;
    if (RadiusStep>Max_r) {
        qDebug() << "CircleDetect Error: RadiusStep > Half Image (Max Radius)";
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
            qDebug() << "Circle a=" << circles[idx].a << " b=" << circles[idx].b << " r=" << circles[idx].r << " pts=" << circles[idx].pts;
    }
}

}
