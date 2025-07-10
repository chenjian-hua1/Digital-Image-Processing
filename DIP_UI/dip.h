#ifndef DIP_H
#define DIP_H

#include <QImage>
#include <QTextEdit>
#include "DIP_Struct.h"

using namespace std;

class DIP
{
public:
    const float *GaussianKernel = new float[9]{0.045, 0.122, 0.045, 0.122, 0.332,
                                               0.122, 0.045, 0.122, 0.045};

    static void QImage2Array(const QImage &image, int *&imageArray);
    static QImage Array2QImage(const int *array, int width, int height);
    static QString Float2QString(float num);
    static float textEdit2Float(QTextEdit *edit);

    static void RGB2Gray(QImage image, int *&grayImg);
    static void negative(const int *f, int *&g, int w, int h);
    static void histogram(const int *f, int *&hist, int w, int h);
    static void histEqualization(const int *f, int *&g, int w, int h);
    static void Conv2D(const int *f, int *&g, int w, int h, int &newWidth,
                       int &newHeight, const float *filter, int filter_size);
    static void sobel(const int *f, int *&g, int w, int h, int &gw, int &gh);
    static void prewitt(const int *f, int *&g, int w, int h, int &gw, int &gh);
    static void bubbleSort(int *arr, int n);
    static void median(const int *f, int *&g, int w, int h, int &gw, int &gh, int filterSize=3);
    static void binarization(const int *f, int *&g, int w, int h, int th=127);
    static void otsu(const int *f, int *&g, int w, int h, int &threshold);
    static pair<Intersect, Intersect> FindCircleIntersect(Point pt1, int r1,
                                                          Point pt2, int r2);
    static void CircleDetect(const int *f, int w, int h, int th, int MinRadius,
                             int RadiusStep = 1);
    static void Scale(const int *f, int *&g, int w, int h, double scaleRate,
                      int &newWidth, int &newHeight, bool tolinear=false);
    static void BitPlane(const int *f, int w, int h, int *&g, int bit=0);
    static void rotate_matrix(const int *f, int *&g, int fw, int fh, int &gw, int &gh, double theta, bool inverse=true);
    static void dilation(const int *f, int *&g, int w, int h);
    static void erosion(const int *f, int *&g, int w, int h);
    static void open(const int *f, int *&g, int w, int h);
    static void close(const int *f, int *&g, int w, int h);
    static void connect4(const int *f, int *&labels, int &totalLabel, int w, int h);
    static void connect8(const int *f, int *&labels, int &totalLabel, int w, int h);
    static double CalculateDist(Point pt1, Point pt2);
    static void lineDetect(const int* f, int w, int h, int Pt_th, int ThetaStep, double PtDistTolerance=2*sqrt(2.0));
};

#endif // DIP_H
