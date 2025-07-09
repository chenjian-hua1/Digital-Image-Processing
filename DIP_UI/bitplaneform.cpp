#include "bitplaneform.h"
#include "ui_bitplaneform.h"

BitPlaneForm::BitPlaneForm(QImage image, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BitPlaneForm)
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

BitPlaneForm::~BitPlaneForm()
{
    delete ui;
}

void BitPlaneForm::on_spinBox_valueChanged(int arg1)
{
    if (arg1==-1) return;

    int *outImgArray;
    DIP.BitPlane(imageArray, image.width(), image.height(), outImgArray, arg1);

    QPixmap pixmap = QPixmap::fromImage(DIP.Array2QImage(outImgArray, image.width(), image.height()));
    ui->ImageBox->setPixmap(pixmap);
    ui->ImageBox->resize(pixmap.size());
    this->adjustSize();

    delete[] outImgArray;
}

