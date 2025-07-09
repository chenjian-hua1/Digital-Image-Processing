#include "scaleform.h"
#include "ui_scaleform.h"

ScaleForm::ScaleForm(QImage image, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScaleForm)
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

ScaleForm::~ScaleForm()
{
    delete ui;
}

void ScaleForm::on_horizontalScrollBar_sliderMoved(int position)
{
    double scaleRate = (double)position/100;
    ui->label->setText("Scale Rate:"+DIP.Float2QString(scaleRate));

    int *outImgArray, outImgW, outImgH;
    DIP.Scale(imageArray, outImgArray, image.width(), image.height(),
              scaleRate, outImgW, outImgH, ui->linearButton->isChecked());

    QPixmap pixmap = QPixmap::fromImage(DIP.Array2QImage(outImgArray, outImgW, outImgH));
    ui->ImageBox->setPixmap(pixmap);
    ui->ImageBox->resize(pixmap.size());
    this->adjustSize();

    delete[] outImgArray;
}


void ScaleForm::on_linearButton_clicked()
{
    ui->neighborButton->setChecked(false);
}


void ScaleForm::on_neighborButton_clicked()
{
    ui->linearButton->setChecked(false);
}

