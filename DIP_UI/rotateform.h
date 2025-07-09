#ifndef ROTATEFORM_H
#define ROTATEFORM_H

#include <QWidget>
#include "dip.h"

namespace Ui {
class RotateForm;
}

class RotateForm : public QWidget
{
    Q_OBJECT

public:
    explicit RotateForm(QImage image, QWidget *parent = nullptr);
    ~RotateForm();

private slots:
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::RotateForm *ui;
    DIP DIP;
    QImage image;
    int *imageArray;
};

#endif // ROTATEFORM_H
