#include <QDockWidget>
#include <QFileDialog>
#include <QtCharts>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "teamform.h"
#include "imgform.h"
#include "videoform.h"
#include "filterform.h"
#include "scaleform.h"
#include "bitplaneform.h"
#include "rotateform.h"


void MainWindow::NewForm(QWidget *widget, const QString &title, bool floating)
{
    QDockWidget *dock = new QDockWidget(title, this);
    widget->setParent(dock);

    dock->setWidget(widget);
    dock->setFloating(floating);

    dock->setAllowedAreas(Qt::AllDockWidgetAreas);
    dock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

    dock->resize(widget->size());

    dock->show();
}

void MainWindow::CreateHistogram(int *histogram, int histW, QPainter &painter)
{
    const int paintWidth = 600, paintHeight = 400;
    painter.fillRect(rect(), Qt::white); // 背景

    if (!histogram || histW <= 0)
        return;

    // 找最大值
    int maxValue = 0;
    for (int i = 0; i < histW; ++i) {
        if (histogram[i] > maxValue)
            maxValue = histogram[i];
    }

    int barWidth = paintWidth / histW;

    painter.setBrush(Qt::black);
    painter.setPen(Qt::NoPen);

    // 繪製每一條長條
    for (int i = 0; i < histW; ++i) {
        double ratio = static_cast<double>(histogram[i]) / maxValue;
        int barHeight = ratio * paintHeight;

        QRect barRect(i * barWidth, paintHeight - barHeight, barWidth, barHeight);
        painter.drawRect(barRect);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRGB2Gray_triggered()
{
    int *outImgArray;
    DIP.RGB2Gray(orginImage, outImgArray);

    ImgForm *imgform = new ImgForm(DIP.Array2QImage(outImgArray, width, height), this);
    NewForm(imgform, "RGB2Gray");

    delete[] outImgArray;
}


void MainWindow::on_actionOpen_triggered()
{
    // Open File Manager
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        QDir::homePath(),
        tr("All Files (*);;Image Files (*.bmp *.png *.jpg *.jpeg);;Video Files (*.mp4 *.avi *.mov *.mkv)")
        );

    // NonSelect
    if (fileName.isEmpty()) {
        qDebug() << "No file selected.";
        return;
    }
    qDebug() << "Selected file:" << fileName;

    // 嘗試載入圖片
    QImage orginImage(fileName);
    if (!orginImage.isNull()) {
        // 成功讀取圖片
        DIP.QImage2Array(orginImage, imageArray);
        width = orginImage.width();
        height = orginImage.height();
        qDebug() << "Image size:" << width << "x" << height;

        // 顯示圖片
        ImgForm *imgform = new ImgForm(orginImage);
        NewForm(imgform, "Image");
        return;
    }

    // 檢查是否是影片檔案（副檔名）
    QString ext = QFileInfo(fileName).suffix().toLower();
    QStringList videoExtensions = {"mp4", "avi", "mov", "mkv", "wmv"};
    if (videoExtensions.contains(ext)) {
        // 顯示影片
        VideoForm *videoform = new VideoForm(fileName, this);
        NewForm(videoform, "Video");
        return;
    }

    // 既不是圖片也不是影片
    qDebug() << "Error: Unsupported file type";
    QMessageBox::warning(this, tr("Unsupported File"), tr("This file type is not supported."));
}


void MainWindow::on_actionBinary_triggered()
{

}


void MainWindow::on_actionIntroduction_triggered()
{
    TeamForm *teamForm = new TeamForm();
    NewForm(teamForm, "Team");
}


void MainWindow::on_actionOTSU_triggered()
{
    int *otsuImage, ostuThreshold;
    DIP.otsu(imageArray, otsuImage, width, height, ostuThreshold);

    ImgForm *imgform = new ImgForm(DIP.Array2QImage(otsuImage, width, height));
    NewForm(imgform, "OTSU");

    delete[] otsuImage;
}


void MainWindow::on_actionNegative_triggered()
{
    int *negativeImg;
    DIP.negative(imageArray, negativeImg, width, height);

    ImgForm *imgform = new ImgForm(DIP.Array2QImage(negativeImg, width, height));
    NewForm(imgform, "Negative");
}


void MainWindow::on_actionCustomize_triggered()
{
    FilterForm *filterform = new FilterForm(orginImage, this);
    NewForm(filterform, "Filter");
}


void MainWindow::on_actionScale_triggered()
{
    ScaleForm *scaleform = new ScaleForm(orginImage, this);
    NewForm(scaleform, "Scale");
}


void MainWindow::on_actionBitPlane_triggered()
{
    BitPlaneForm *bitplaneform = new BitPlaneForm(orginImage, this);
    NewForm(bitplaneform, "BitPlane");
}


void MainWindow::on_actionRotate_triggered()
{
    RotateForm *rotateform = new RotateForm(orginImage, this);
    NewForm(rotateform, "Rotate");
}


void MainWindow::on_actionHistogram_triggered()
{
    int *hist, max_hist = 0;
    DIP.histogram(imageArray, hist, width, height);

    // 建立直方圖資料
    QBarSet *set0 = new QBarSet("Count");
    for (int i=0; i<256; i++) {
        *set0 << hist[i];
        if (hist[i]>max_hist)
            max_hist = hist[i];
    }

    // 建立 bar series
    QBarSeries *series = new QBarSeries();
    series->append(set0);

    // 建立 chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Histogram");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Y 軸
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, max_hist);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 用 QChartView 顯示
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    NewForm(chartView, "Histogram");
    delete[] hist;
}


void MainWindow::on_actionHistEqualization_triggered()
{
    /* 直方等化 */
    int *outImgArray;
    DIP.histEqualization(imageArray, outImgArray, width, height);

    ImgForm *imgform = new ImgForm(DIP.Array2QImage(outImgArray, width, height));
    NewForm(imgform, "HistEqualization");
    delete[] outImgArray;
}


void MainWindow::on_actionSobel_triggered()
{
    int *outImgArray, outW, outH;
    DIP.sobel(imageArray, outImgArray, width, height, outW, outH);

    ImgForm *imgform = new ImgForm(DIP.Array2QImage(outImgArray, outW, outH));
    NewForm(imgform, "Sobel");

    delete[] outImgArray;
}


void MainWindow::on_actionPrewitt_triggered()
{
    int *outImgArray, outW, outH;
    DIP.prewitt(imageArray, outImgArray, width, height, outW, outH);

    ImgForm *imgform = new ImgForm(DIP.Array2QImage(outImgArray, outW, outH));
    NewForm(imgform, "Prewitt");

    delete[] outImgArray;
}


void MainWindow::on_actionMedian_triggered()
{
    int *outImgArray, outW, outH;
    DIP.median(imageArray, outImgArray, width, height, outW, outH, 3);

    ImgForm *imgform = new ImgForm(DIP.Array2QImage(outImgArray, outW, outH));
    NewForm(imgform, "Median");

    delete[] outImgArray;
}


void MainWindow::on_actionDilation_triggered()
{

}


void MainWindow::on_actionErosion_triggered()
{

}


void MainWindow::on_actionOpen_2_triggered()
{

}


void MainWindow::on_actionClose_triggered()
{

}

void MainWindow::on_actionConnect4_triggered()
{
    int *binzImage, *labelArray, totalLabel;
    DIP.binarization(imageArray, binzImage, width, height);
    DIP.connect4(binzImage, labelArray, totalLabel, width, height);

    ImgForm *imgform = new ImgForm(DIP.Array2QImage(labelArray, width, height));
    NewForm(imgform, "Connect 4");
    qDebug() << "Connect 4 total comp: " << totalLabel;

    delete[] labelArray;
    delete[] binzImage;
}


void MainWindow::on_actionConnect8_triggered()
{
    int *binzImage, *labelArray, totalLabel;
    DIP.binarization(imageArray, binzImage, width, height);
    DIP.connect8(binzImage, labelArray, totalLabel, width, height);

    ImgForm *imgform = new ImgForm(DIP.Array2QImage(labelArray, width, height));
    NewForm(imgform, "Connect 8");
    qDebug() << "Connect 8 total comp: " << totalLabel;

    delete[] labelArray;
    delete[] binzImage;
}


void MainWindow::on_actionLine_Detect_triggered()
{
    DIP.lineDetect(imageArray, width, height, 4, 1, 3);
}


void MainWindow::on_actionCircle_Detect_triggered()
{
    DIP.CircleDetect(imageArray, width, height, 5, 2);
}
