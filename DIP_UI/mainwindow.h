#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "dip.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void NewForm(QWidget *widget, const QString &title, bool floating = true);
    void CreateHistogram(int *histogram, int histW, QPainter &painter);

private slots:
    void on_actionRGB2Gray_triggered();

    void on_actionOpen_triggered();

    void on_actionBinary_triggered();

    void on_actionIntroduction_triggered();

    void on_actionOTSU_triggered();

    void on_actionNegative_triggered();

    void on_actionCustomize_triggered();

    void on_actionScale_triggered();

    void on_actionBitPlane_triggered();

    void on_actionRotate_triggered();

    void on_actionHistogram_triggered();

    void on_actionHistEqualization_triggered();

    void on_actionSobel_triggered();

    void on_actionPrewitt_triggered();

    void on_actionMedian_triggered();

    void on_actionDilation_triggered();

    void on_actionErosion_triggered();

    void on_actionOpen_2_triggered();

    void on_actionClose_triggered();

    void on_actionConnect4_triggered();

    void on_actionConnect8_triggered();

    void on_actionLine_Detect_triggered();

    void on_actionCircle_Detect_triggered();

private:
    Ui::MainWindow *ui;
    DIP DIP;
    QImage orginImage;
    int *imageArray = nullptr;
    int width, height;
};
#endif // MAINWINDOW_H
