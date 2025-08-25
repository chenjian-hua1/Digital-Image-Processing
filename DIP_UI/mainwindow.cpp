#include <QDockWidget>
#include <QFileDialog>
#include <QtCharts>
#include <QPainter>
#include <QFont>
#include <QColor>
#include <QPoint>

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

void MainWindow::addTextToImageAndSave(QImage &image, const QString &outputImagePath, const QString &text, const QPoint &position, const QFont &font, const QColor &textColor)
{
    if (image.isNull()) {
        qDebug() << "Failed to load image:";
        return;
    }

    // 創建 QPainter 對象並綁定到 QImage
    QPainter painter(&image);
    if (!painter.isActive()) {
        qDebug() << "Painter is not active";
        return;
    }

    // 設置文字屬性
    painter.setFont(font); // 設置字體
    painter.setPen(textColor); // 設置文字顏色

    // 在指定位置繪製文字
    painter.drawText(position, text);

    // 結束繪製
    painter.end();

    // 保存圖片
    if (!image.save(outputImagePath)) {
        qDebug() << "Failed to save image:" << outputImagePath;
        return;
    }
    qDebug() << "Image saved successfully:" << outputImagePath;
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
    orginImage = QImage(fileName);
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
    else {
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

void MainWindow::on_actionAutoFocus_triggered()
{
    QDir dir("/Users/chenjianhua/Downloads/DIP_UI/AutoFocus");
    QStringList nameFilters;
    nameFilters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp";

    QFileInfoList fileList = dir.entryInfoList(nameFilters, QDir::Files);
    int numImages = fileList.size();

    if (numImages == 0) {
        qDebug() << "No images found!";
        return;
    }

    // Load first image to determine size
    QImage firstImage(fileList[0].absoluteFilePath());
    int width = firstImage.width(), height = firstImage.height();

    // Allocate 2D array
    int **images = new int*[numImages];
    int *edgeIntensitys = new int[numImages];
    QImage *qimg = new QImage[numImages];

    for (int i = 0; i < numImages; ++i) {
        images[i] = new int[width * height];
    }

    // Load each image
    for (int i = 0; i < numImages; ++i) {
        qimg[i] = QImage(fileList[i].absoluteFilePath());
        if (qimg[i].isNull()) {
            qDebug() << "Failed to load" << fileList[i].absoluteFilePath();
            continue;
        }

        // image.resize
        if (qimg[i].width() != width || qimg[i].height() != height) {
            qimg[i] = qimg[i].scaled(width, height, Qt::IgnoreAspectRatio);
        }

        QImage qimg_gray = qimg[i].convertToFormat(QImage::Format_Grayscale8);
        DIP.QImage2Array(qimg_gray, images[i]);
        DIP.calEdgeIntensity(images[i], edgeIntensitys[i], width, height);
    }

    // 最大邊緣總值 - 最清晰圖片
    int edgeArgmax = 0;

    // 繪圖
    QPoint position(50, 50); // 文字的左上角位置 (x, y)
    QFont font("Arial", 30, QFont::Bold); // 字體：Arial，大小 20，加粗
    QColor textColor(Qt::blue); // 文字顏色：藍色

    for (int i = 0; i < numImages; ++i) {
        QString outputPath = QString("/Users/chenjianhua/Downloads/DIP_UI/FocusOut/output%1.jpg").arg(i);
        QString text = QString("Edge - %1").arg(edgeIntensitys[i]); // 要添加的文字

        addTextToImageAndSave(qimg[i], outputPath, text, position, font, textColor);

        if (edgeIntensitys[i]>edgeIntensitys[edgeArgmax])
            edgeArgmax = i;
    }

    // 保存最清晰圖片
    QString outputPath = QString("/Users/chenjianhua/Downloads/DIP_UI/FocusOut/best.jpg");
    QString text = QString("Edge - %1").arg(edgeIntensitys[edgeArgmax]); // 要添加的文字
    addTextToImageAndSave(qimg[edgeArgmax], outputPath, text, position, font, textColor);

    delete[] images;
    delete[] qimg;
    delete[] edgeIntensitys;
}
