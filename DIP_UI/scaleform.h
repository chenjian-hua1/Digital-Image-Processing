#ifndef SCALEFORM_H
#define SCALEFORM_H

#include <QWidget>
#include "dip.h"

namespace Ui {
class ScaleForm;
}

class ScaleForm : public QWidget
{
    Q_OBJECT

public:
    explicit ScaleForm(QImage image, QWidget *parent = nullptr);
    ~ScaleForm();

    void setDIP(const DIP &newDIP);

private slots:
    void on_horizontalScrollBar_sliderMoved(int position);

    void on_linearButton_clicked();

    void on_neighborButton_clicked();

private:
    Ui::ScaleForm *ui;
    DIP DIP;
    QImage image;
    int *imageArray;
};

#endif // SCALEFORM_H
