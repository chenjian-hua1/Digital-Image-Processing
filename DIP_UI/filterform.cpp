#include "filterform.h"
#include "ui_filterform.h"

void FilterForm::NormalFilter()
{
    ui->textEdit->setText("0");
    ui->textEdit_2->setText("0");
    ui->textEdit_3->setText("0");
    ui->textEdit_4->setText("0");
    ui->textEdit_5->setText("0");

    ui->textEdit_6->setText("0");
    ui->textEdit_7->setText("0");
    ui->textEdit_8->setText("0");
    ui->textEdit_9->setText("0");
    ui->textEdit_10->setText("0");

    ui->textEdit_11->setText("0");
    ui->textEdit_12->setText("0");
    ui->textEdit_13->setText("1");
    ui->textEdit_14->setText("0");
    ui->textEdit_15->setText("0");

    ui->textEdit_16->setText("0");
    ui->textEdit_17->setText("0");
    ui->textEdit_18->setText("0");
    ui->textEdit_19->setText("0");
    ui->textEdit_20->setText("0");

    ui->textEdit_21->setText("0");
    ui->textEdit_22->setText("0");
    ui->textEdit_23->setText("0");
    ui->textEdit_24->setText("0");
    ui->textEdit_25->setText("0");
}

void FilterForm::AvgFilter(int filterSize)
{
    QString avgVal = DIP.Float2QString(1.0/(filterSize*filterSize));

    ui->textEdit->setText(avgVal);
    ui->textEdit_2->setText(avgVal);
    ui->textEdit_3->setText(avgVal);

    ui->textEdit_6->setText(avgVal);
    ui->textEdit_7->setText(avgVal);
    ui->textEdit_8->setText(avgVal);

    ui->textEdit_11->setText(avgVal);
    ui->textEdit_12->setText(avgVal);
    ui->textEdit_13->setText(avgVal);

    // not 5 -> finish
    if (filterSize==3) return;

    ui->textEdit_4->setText(avgVal);
    ui->textEdit_5->setText(avgVal);

    ui->textEdit_9->setText(avgVal);
    ui->textEdit_10->setText(avgVal);

    ui->textEdit_14->setText(avgVal);
    ui->textEdit_15->setText(avgVal);
}

void FilterForm::GaussianFilter()
{
    ui->textEdit->setText(DIP.Float2QString(DIP.GaussianKernel[0]));
    ui->textEdit_2->setText(DIP.Float2QString(DIP.GaussianKernel[1]));
    ui->textEdit_3->setText(DIP.Float2QString(DIP.GaussianKernel[2]));

    ui->textEdit_6->setText(DIP.Float2QString(DIP.GaussianKernel[3]));
    ui->textEdit_7->setText(DIP.Float2QString(DIP.GaussianKernel[4]));
    ui->textEdit_8->setText(DIP.Float2QString(DIP.GaussianKernel[5]));

    ui->textEdit_11->setText(DIP.Float2QString(DIP.GaussianKernel[6]));
    ui->textEdit_12->setText(DIP.Float2QString(DIP.GaussianKernel[7]));
    ui->textEdit_13->setText(DIP.Float2QString(DIP.GaussianKernel[8]));
}

void FilterForm::ReadFilterVal()
{
    // 清除之前的記憶體
    delete[] filterVal; filterVal = nullptr;
    // 創建新空間
    filterVal = new float[filterSize*filterSize];

    filterVal[0]  = DIP.textEdit2Float(ui->textEdit);
    filterVal[1]  = DIP.textEdit2Float(ui->textEdit_2);
    filterVal[2]  = DIP.textEdit2Float(ui->textEdit_3);
    filterVal[3]  = DIP.textEdit2Float(ui->textEdit_4);
    filterVal[4]  = DIP.textEdit2Float(ui->textEdit_5);
    filterVal[5]  = DIP.textEdit2Float(ui->textEdit_6);
    filterVal[6]  = DIP.textEdit2Float(ui->textEdit_7);
    filterVal[7]  = DIP.textEdit2Float(ui->textEdit_8);
    filterVal[8]  = DIP.textEdit2Float(ui->textEdit_9);
    filterVal[9]  = DIP.textEdit2Float(ui->textEdit_10);
    filterVal[10] = DIP.textEdit2Float(ui->textEdit_11);
    filterVal[11] = DIP.textEdit2Float(ui->textEdit_12);
    filterVal[12] = DIP.textEdit2Float(ui->textEdit_13);
    filterVal[13] = DIP.textEdit2Float(ui->textEdit_14);
    filterVal[14] = DIP.textEdit2Float(ui->textEdit_15);
    filterVal[15] = DIP.textEdit2Float(ui->textEdit_16);
    filterVal[16] = DIP.textEdit2Float(ui->textEdit_17);
    filterVal[17] = DIP.textEdit2Float(ui->textEdit_18);
    filterVal[18] = DIP.textEdit2Float(ui->textEdit_19);
    filterVal[19] = DIP.textEdit2Float(ui->textEdit_20);
    filterVal[20] = DIP.textEdit2Float(ui->textEdit_21);
    filterVal[21] = DIP.textEdit2Float(ui->textEdit_22);
    filterVal[22] = DIP.textEdit2Float(ui->textEdit_23);
    filterVal[23] = DIP.textEdit2Float(ui->textEdit_24);
    filterVal[24] = DIP.textEdit2Float(ui->textEdit_25);
}

FilterForm::FilterForm(QImage image, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FilterForm)
{
    ui->setupUi(this);

    // 檢查圖片是否有效
    if (!image.isNull()) {
        qDebug() << "Image received with size:" << image.size();

        // 將 QImage 轉換為 QPixmap 並設置到 QLabel
        QPixmap pixmap = QPixmap::fromImage(image);
        ui->ImageBox->setPixmap(pixmap);
        ui->ImageBox->resize(pixmap.size()); // 調整 QLabel 的大小與圖片匹配
        this->adjustSize(); // 調整窗口大小以適應 QLabel

        this->image = image;
        DIP.QImage2Array(image, imageArray);
    } else {
        qDebug() << "Image is null, cannot display.";
    }
}

FilterForm::~FilterForm()
{
    delete ui;
}

void FilterForm::on_pushButton_clicked()
{
    int *outImgArray, width = image.width(), height = image.height(),
        newWidth, newHeight;
    ReadFilterVal();
    DIP.Conv2D(imageArray, outImgArray, width, height, newWidth, newHeight, filterVal, filterSize);

    // 將 QImage 轉換為 QPixmap 並設置到 QLabel
    QPixmap pixmap = QPixmap::fromImage(DIP.Array2QImage(outImgArray, newWidth, newHeight));
    ui->ImageBox->setPixmap(pixmap);
    ui->ImageBox->resize(pixmap.size()); // 調整 QLabel 的大小與圖片匹配
    this->adjustSize(); // 調整窗口大小以適應 QLabel
}


void FilterForm::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1=="normal") NormalFilter();
    else if (arg1=="average") AvgFilter();
    else if (arg1=="gaussian") GaussianFilter();
}


