#include "rotateform.h"
#include "ui_rotateform.h"

RotateForm::RotateForm(QImage image, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RotateForm)
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

RotateForm::~RotateForm()
{
    delete ui;
}

void RotateForm::on_spinBox_valueChanged(int arg1)
{
    int *outImgArray, outImgW, outImgH;
    DIP.rotate_matrix(imageArray, outImgArray, image.width(), image.height(),
                      outImgW, outImgH, arg1, ui->checkBox->isChecked());

    ui->label->setText(QString::asprintf("%dx%d", outImgW, outImgH));

    QPixmap pixmap = QPixmap::fromImage(DIP.Array2QImage(outImgArray, outImgW, outImgH));
    ui->ImageBox->setPixmap(pixmap);
    ui->ImageBox->resize(pixmap.size());
    this->adjustSize();

    delete[] outImgArray;
}

