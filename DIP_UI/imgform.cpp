#include "imgform.h"
#include "ui_imgform.h"

ImgForm::ImgForm(const QImage &image, QWidget *parent)
    : QWidget(parent), ui(new Ui::ImgForm), Image(image) // 初始化 QImage
{
    ui->setupUi(this);

    // 檢查圖片是否有效
    if (!Image.isNull()) {
        qDebug() << "Image received with size:" << Image.size();

        // 將 QImage 轉換為 QPixmap 並設置到 QLabel
        QPixmap pixmap = QPixmap::fromImage(Image);
        ui->imagelabel->setPixmap(pixmap);
        ui->imagelabel->resize(pixmap.size()); // 調整 QLabel 的大小與圖片匹配
        this->adjustSize(); // 調整窗口大小以適應 QLabel
    } else {
        qDebug() << "Image is null, cannot display.";
    }
}

ImgForm::~ImgForm()
{
    delete ui;
}
