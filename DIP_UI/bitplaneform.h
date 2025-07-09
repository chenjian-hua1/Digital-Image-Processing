#ifndef BITPLANEFORM_H
#define BITPLANEFORM_H

#include <QWidget>
#include "dip.h"

namespace Ui {
class BitPlaneForm;
}

class BitPlaneForm : public QWidget
{
    Q_OBJECT

public:
    explicit BitPlaneForm(QImage image, QWidget *parent = nullptr);
    ~BitPlaneForm();

private slots:
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::BitPlaneForm *ui;
    DIP DIP;
    QImage image;
    int *imageArray;
};

#endif // BITPLANEFORM_H
