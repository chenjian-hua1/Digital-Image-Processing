#ifndef IMGFORM_H
#define IMGFORM_H

#include <QWidget>

namespace Ui {
class ImgForm;
}

class ImgForm : public QWidget
{
    Q_OBJECT

public:
    explicit ImgForm(const QImage &image, QWidget *parent = nullptr);
    ~ImgForm();

private:
    Ui::ImgForm *ui;
    QImage Image;
};

#endif // IMGFORM_H
