#include "dip.h"
#include <cmath>

void DIP::QImage2Array(const QImage &image, int *&imageArray) {
    // Clean Mem
    delete[] imageArray;
    imageArray = nullptr;

    // Read Pixels
    int width = image.width(), height = image.height();
    imageArray = new int[width * height];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x)
            imageArray[y * width + x] = image.pixelColor(x, y).red(); // 灰階圖片，R=G=B
    }
}

QImage DIP::Array2QImage(const int *array, int width, int height)
{
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

QString DIP::Float2QString(float num)
{
    return QString::number(num, 'f', 3);
}

float DIP::textEdit2Float(QTextEdit *edit) {
    return edit->toPlainText().toFloat();
}

void DIP::RGB2Gray(QImage image, int *&grayImg)
{
    const int width = image.width(), height = image.height();
    grayImg = new int[width*height];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // 讀取 (x, y) 的像素
            QRgb rgb = image.pixel(x, y);
            // Gray = R*0.299 + G*0.587 + B*0.114
            grayImg[y*width + x] = 0.299*qRed(rgb) + 0.587*qGreen(rgb) + 0.114*qBlue(rgb);
        }
    }
}

void DIP::negative(const int *f, int *&g, int w, int h) {
    g = new int[w*h];

    for (int i=0; i<w*h; i++)
        g[i] = 255-f[i];
}

void DIP::histogram(const int *f, int *&hist, int w, int h)
{
    hist = new int[w*h]{0};
    for (int pt=0; pt<w*h; pt++)
        hist[f[pt]]++;
}

void DIP::histEqualization(const int *f, int *&g, int w, int h)
{
    const int totalPixels = w*h;

    int *hist = new int[256]{0};
    for (int pt=0; pt<totalPixels; pt++)
        hist[f[pt]]++;

    // 計算累積分布函數 (CDF)
    double cdf[256] = {0};

    cdf[0] = (double)hist[0]/totalPixels;
    for (int i = 1; i < 256; i++) {
        cdf[i] = cdf[i-1] + (double)hist[i]/totalPixels;
    }

    g = new int[totalPixels];
    // 根據CDF進行直方圖等化
    for (int pt=0; pt<totalPixels; pt++) {
        // 基於CDF的映射
        int newValue = (int)(cdf[f[pt]] * 255);

        // 確保值在0-255範圍內
        if (newValue > 255) newValue = 255;
        if (newValue < 0) newValue = 0;

        g[pt] = newValue;
    }

    delete[] hist;
}

void DIP::Conv2D(const int *f, int *&g, int w, int h, int &newWidth, int &newHeight,
                 const float *filter, int filter_size) {
    // 檢查濾波器尺寸是否為奇數
    if (filter_size % 2 == 0)
        throw std::invalid_argument("Filter size must be odd");

    // 計算輸出圖片的尺寸（無padding）
    newWidth = w - filter_size + 1; newHeight = h - filter_size + 1;

    // 初始化輸出陣列
    // delete[] g; g = nullptr;
    g = new int[newWidth*newHeight]{0};

    // 執行卷積（stride=1，無padding）
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            float sum = 0.0f;
            // 對濾波器範圍內的每個元素進行卷積
            for (int fy = 0; fy < filter_size; ++fy) {
                for (int fx = 0; fx < filter_size; ++fx) {
                    sum += f[(y + fy) * w + (x + fx)] *
                           filter[fy * filter_size + fx];
                }
            }
            g[y * newWidth + x] = sum;
        }
    }
}

void DIP::sobel(const int *f, int *&g, int w, int h, int &gw, int &gh)
{
    const int filterSize = 3;

    float FilterX[9] = {
        -1, 0, 1,
        -2, 0, 2,
        -1, 0, 1
    };

    float FilterY[9] = {
        -1, -2, -1,
        0, 0, 0,
        1, 2, 1
    };

    int *Gx, *Gy;
    Conv2D(f, Gx, w, h, gw, gh, FilterX, filterSize);
    Conv2D(f, Gy, w, h, gw, gh, FilterY, filterSize);

    g = new int[gw*gh]{0};
    for (int i=0; i<gw*gh; i++)
        g[i] = abs(Gy[i])+abs(Gx[i]);

    delete[] Gx;
    delete[] Gy;
}

void DIP::prewitt(const int *f, int *&g, int w, int h, int &gw, int &gh)
{
    const int filterSize = 3;

    float FilterX[9] = {
        -1, 0, 1,
        -1, 0, 1,
        -1, 0, 1
    };

    float FilterY[9] = {
        1, 1, 1,
        0, 0, 0,
        -1, -1, -1
    };

    int *Gx, *Gy;
    Conv2D(f, Gx, w, h, gw, gh, FilterX, filterSize);
    Conv2D(f, Gy, w, h, gw, gh, FilterY, filterSize);

    g = new int[gw*gh]{0};
    for (int i=0; i<gw*gh; i++)
        g[i] = abs(Gy[i])+abs(Gx[i]);

    delete[] Gx;
    delete[] Gy;
}

void DIP::bubbleSort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false; // 優化：如果一趟都沒交換，直接結束
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交換 arr[j] 和 arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break; // 如果已經有序，提早退出
    }
}

void DIP::median(const int *f, int *&g, int w, int h, int &gw, int &gh, int filterSize)
{
    const int kernelSize = filterSize*filterSize;
    const int medianPos = (kernelSize-1)/2;

    int *sortArray = new int[kernelSize];

    gw = w-filterSize+1; gh = h-filterSize+1;
    g = new int[gw*gh];

    for (int y=0; y<gh; y++) {
        for (int x=0; x<gw; x++) {
            // Get Gray Level of Kernel Range
            for (int yy=0; yy<filterSize; yy++) {
                for (int xx=0; xx<filterSize; xx++) {
                    sortArray[yy*filterSize + xx] = f[(y+yy)*w + (x+xx)];
                }
            }

            // Sort Array
            bubbleSort(sortArray, kernelSize);
            // Get Median Value
            g[y*gw + x] = sortArray[medianPos];
        }
    }

    delete[] sortArray;
}

void DIP::binarization(const int *f, int *&g, int w, int h, int th)
{
    g = new int[w*h];
    for (int pt=0; pt<w*h; pt++)
        g[pt] = (f[pt]>=th) ? 255:0;
}

void DIP::otsu(const int *f, int *&g, int w, int h, int &threshold) {
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

pair<Intersect, Intersect> DIP::FindCircleIntersect(Point pt1, int r1, Point pt2, int r2) {
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

void DIP::CircleDetect(const int *f, int w, int h, int th, int MinRadius, int RadiusStep) {
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

    delete[] circles;
}

void DIP::Scale(const int *f, int *&g, int w, int h, double scaleRate, int &newWidth, int &newHeight, bool tolinear)
{
    newWidth = w*scaleRate; newHeight = h*scaleRate;
    g = new int[newWidth*newHeight]{0};

    // 取得對應的原始位置 (會是小數點)
    // newW/w = x'/x , newH/h = y'/y
    // x = x'* w/newW
    // y = y'* h/newH
    const double scaleWeightX = (double)(w-1)/(newWidth-1),
                 scaleWeightY = (double)(h-1)/(newHeight-1);

    // 對到的原始影像位置點
    double oy, ox;

    // linear interpolation
    if (tolinear) {
        // 左上,右上  /  左下,右下  -> 左右先做線性插值
        double linearTop, linearBottom, linearOut;
        double alpha, beta;

        for (int ny=0; ny<newHeight; ny++) {
            oy = ny * scaleWeightY;

            for (int nx=0; nx<newWidth; nx++) {
                ox = nx * scaleWeightX;

                alpha = ox-floor(ox);
                beta = oy-floor(oy);

                // 左上,右上 -> 左右線性插值
                linearTop = (1.0-alpha)* f[(int)floor(oy)*w + (int)floor(ox)]+
                            alpha* f[(int)floor(oy)*w + (int)ceil(ox)];
                // 左下,右下 -> 左右線性插值
                linearBottom = (1.0- alpha)* f[(int)ceil(oy)*w + (int)floor(ox)]+
                               alpha* f[(int)ceil(oy)*w + (int)ceil(ox)];

                // 上下線性插值
                linearOut = (1-beta)*linearTop + beta*linearBottom;
                g[ny*newWidth + nx] = round(linearOut);
            }
        }
    }
    // neighbor interpolation
    else {
        for (int y=0; y<newHeight; y++) {
            oy = y * scaleWeightY;

            for (int x=0; x<newWidth; x++) {
                ox = x * scaleWeightX;

                g[y*newWidth + x] = f[(int)round(oy)*w + (int)round(ox)];
            }
        }
    }
}

void DIP::BitPlane(const int *f, int w, int h, int *&g, int bit)
{
    g = new int[w*h]{0};
    for (int pt=0; pt<w*h; pt++) g[pt] = f[pt];

    const int bits_and = pow(2, bit);
    for (int pt=0; pt<w*h; pt++)
        g[pt] = f[pt] & bits_and;
}

void DIP::rotate_matrix(const int *f, int *&g, int fw, int fh, int &gw, int &gh, double theta, bool inverse)
{

    double sinA = sin(theta * M_PI / 180.0), cosA = cos(theta * M_PI / 180.0);

    gw = fh * abs(sinA) + fw * abs(cosA);
    gh = fh * abs(cosA) + fw * abs(sinA);
    g = new int[gw * gh]{0};

    double new_x, new_y, alpha, beta, a, b, c;
    const double f_centX = fw / 2.0, f_centY = fh / 2.0,
                 g_centX = gw / 2.0, g_centY = gh / 2.0;

    if (inverse) {
        // 內差法 (先將新圖index 反旋轉 看對照的原圖index)
        for (int y = 0; y < gh; y++) {
            for (int x = 0; x < gw; x++) {
                // y = −x'sinθ + y'cosθ 從中心點(cy, cx)旋轉
                new_y = -(x - g_centX) * sinA + (y - g_centY) * cosA + f_centY;
                // x = x'cosθ + y'sinθ
                new_x = (x - g_centX) * cosA + (y - g_centY) * sinA + f_centX;

                // 是否介於旋轉前的長寬範圍內
                if (round(new_x) >= 0 && round(new_x) < fw && round(new_y) >= 0 && round(new_y) < fh) {
                    if (new_x < 0) new_x = 0;
                    else if (new_x > fw - 1) new_x = fw - 1;
                    if (new_y < 0) new_y = 0;
                    else if (new_y > fh - 1) new_y = fh - 1;

                    alpha = new_x - floor(new_x);
                    beta = new_y - floor(new_y);

                    int x_floor = floor(new_x), x_ceil = ceil(new_x);
                    int y_floor = floor(new_y), y_ceil = ceil(new_y);

                    a = (1 - alpha) * f[y_ceil * fw + x_floor] + alpha * f[y_ceil * fw + x_ceil];
                    b = (1 - alpha) * f[y_floor * fw + x_floor] + alpha * f[y_floor * fw + x_ceil];
                    c = (1 - beta) * b + beta * a;

                    g[y * gw + x] = (int)(c + 0.5);
                }
                else {
                    g[y * gw + x] = 0;
                }
            }
        }
    }
    else {
        for (int y=0; y<fh; y++) {
            for (int x=0; x<fw; x++) {
                // x' = x*cosθ - y*sinθ
                new_x = (x-f_centX)*cosA - (y-f_centY)*sinA + g_centX;
                // y' = x*sinθ + y*cosθ
                new_y = (x-f_centX)*sinA + (y-f_centY)*cosA + g_centY;

                if (new_x<0 || new_x>gw-1 || new_y<0 || new_y>gh-1) continue;

                g[(int)round(new_y)*gw + (int)round(new_x)] = f[y*fw + x];
            }
        }
    }
}

void DIP::dilation(const int *f, int *&g, int w, int h)
{
    g = new int[w*h]{0};

    /* Dilation element
    1 0 1
    0 1 0
    1 0 1
    */
    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            if (f[y*w + x]==0) continue;

            // else 255
            if (y>=1 && x>=1) g[(y-1)*w + (x-1)] = 255;
            if (y>=1) g[(y-1)*w + (x+1)] = 255;
            if (x>=1) g[(y+1)*w + (x-1)] = 255;
            g[(y+1)*w + (x+1)] = 255;
        }
    }
}

void DIP::erosion(const int *f, int *&g, int w, int h)
{
    g = new int[w*h]{0};

    /*
    ErosionElement
    0, 1, 0,
    1, 1, 1,
    0, 1, 0
    */
    // 上下左右是否為白色
    bool top, left, right, bottom;

    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            top = (y==0) || (f[(y-1)*w + x]!=0);
            if (!top) continue;

            bottom = (y==h-1) || (f[(y+1)*w + x]!=0);
            if (!bottom) continue;

            left = (x==0) || (f[y*w + (x-1)]!=0);
            if (!left) continue;

            right = (x==w-1) || (f[y*w + (x+1)]!=0);
            if (!right) continue;

            g[y*w + x] = 255;
        }
    }
}

void DIP::open(const int *f, int *&g, int w, int h)
{
    int *erosionImg;
    erosion(f, erosionImg, w, h);
    dilation(erosionImg, g, w, h);

    delete[] erosionImg;
}

void DIP::close(const int *f, int *&g, int w, int h)
{
    int *dilationImg;
    dilation(f, dilationImg, w, h);
    erosion(dilationImg, g, w, h);

    delete[] dilationImg;
}

void DIP::connect4(const int *f, int *&labels, int &totalLabel, int w, int h)
{
    const int maxLabels = 1000;
    labels = new int[w * h]{0};
    int *convTable = new int[maxLabels];
    for (int i = 0; i < maxLabels; i++) convTable[i] = i;

    int nowLabel = 0;

    // Pass 1: 標記並建立等價表
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (f[y * w + x] == 0) continue;

            int top = (y > 0) ? labels[(y - 1) * w + x] : 0;
            int left = (x > 0) ? labels[y * w + (x - 1)] : 0;

            if (top && left) {
                int minLabel = std::min(top, left);
                int maxLabel = std::max(top, left);

                labels[y * w + x] = minLabel;

                // 找根合併 -> 尋找多個連通子區塊的最小、最大標籤
                while (convTable[minLabel] != minLabel)
                    minLabel = convTable[minLabel];
                while (convTable[maxLabel] != maxLabel)
                    maxLabel = convTable[maxLabel];

                if (minLabel != maxLabel)
                    convTable[maxLabel] = minLabel;
            }
            else if (left) {
                labels[y * w + x] = left;
            }
            else if (top) {
                labels[y * w + x] = top;
            }
            else {
                labels[y * w + x] = ++nowLabel;
            }
        }
    }

    // Pass 2: 替換標籤並計算唯一區塊數
    bool used[1000] = {false};
    totalLabel = 0;

    for (int pt = 0; pt < w * h; pt++) {
        int lbl = labels[pt];
        if (lbl != 0) {
            // 壓縮路徑 -> 不斷尋找最終指向的最小標籤值
            while (convTable[lbl] != lbl)
                lbl = convTable[lbl];

            labels[pt] = lbl;

            if (!used[lbl]) {
                used[lbl] = true;
                totalLabel++;
            }
        }
    }

    delete[] convTable;
}

void DIP::connect8(const int *f, int *&labels, int &totalLabel, int w, int h)
{
    const int maxLabels = 1000;
    labels = new int[w*h]{0};
    int *convTable = new int[maxLabels];
    for (int i=0; i<maxLabels; i++) convTable[i] = i;

    int nowLabel = 0;

    // Pass 1: 標記並建立等價表
    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            if (f[y * w + x] == 0) continue;

            // 八連通鄰居
            int q = (y > 0 && x > 0)     ? labels[(y-1)*w + (x-1)] : 0;
            int r = (y > 0)              ? labels[(y-1)*w + x]     : 0;
            int s = (y > 0 && x < w-1)   ? labels[(y-1)*w + (x+1)] : 0;
            int t = (x > 0)              ? labels[y*w + (x-1)]     : 0;

            // 找最小標籤
            int neighbors[4] = {q, r, s, t};
            int minLabel = maxLabels;

            // 尋找周圍四個區塊的最小標籤
            for (int i=0; i<4; i++) {
                if (neighbors[i] != 0 && neighbors[i] < minLabel)
                    minLabel = neighbors[i];
            }

            if (minLabel != maxLabels) {
                labels[y*w + x] = minLabel;

                // 合併等價關係
                for (int i=0; i<4; i++) {
                    int nLabel = neighbors[i];
                    if (nLabel != 0 && nLabel != minLabel) {
                        // 找根 -> 最後指像的最小標籤
                        while (convTable[nLabel] != nLabel)
                            nLabel = convTable[nLabel];
                        // 遍歷所有連接的子區塊 尋找最小標籤
                        while (convTable[minLabel] != minLabel)
                            minLabel = convTable[minLabel];

                        // 當前label指向最小標籤 小於 之前所有子區塊的最小標籤
                        // 更新為 之前子區塊的最小標籤
                        if (nLabel != minLabel)
                            convTable[nLabel] = minLabel;
                    }
                }
            }
            else {
                labels[y*w + x] = ++nowLabel;
            }
        }
    }

    // Pass 2: 替換標籤並計算唯一區塊數
    bool used[1000] = {false};
    totalLabel = 0;

    for (int pt = 0; pt < w * h; pt++) {
        int lbl = labels[pt];
        if (lbl != 0) {
            // 壓縮路徑
            while (convTable[lbl] != lbl)
                lbl = convTable[lbl];

            labels[pt] = lbl;

            if (!used[lbl]) {
                used[lbl] = true;
                totalLabel++;
            }
        }
    }

    delete[] convTable;
}

double DIP::CalculateDist(Point pt1, Point pt2)
{
    return sqrt( pow(pt2.x-pt1.x, 2) + pow(pt2.y-pt1.x, 2) );
}

void DIP::lineDetect(const int *f, int w, int h, int Pt_th, int ThetaStep, double PtDistTolerance)
{
    /* 前置處理 */
    if (ThetaStep<1 || ThetaStep>45) {
        qDebug() << "LineDetect Error: ThetaStep Valid range is (-45, 45)";
        exit(1);
    }

    // 查看圖片有幾個白點
    int white_pts = 0;
    for (int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            // Color 不是黑0 或 白255
            if (f[x + y*w]!=0 && f[x + y*w]!=255) {
                qDebug() << "LineDetect Error: Detect color is not 0 or 255 (Color is " << f[x + y*w] << ")";
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

            qDebug() << "Detect Line in theta=" << theta << " r=" << i << " have " << r_pts[i] << " points";
        }
    }

    delete[] LineLastPt;
    delete[] r_pts;
}
