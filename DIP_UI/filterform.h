#ifndef FILTERFORM_H
#define FILTERFORM_H

#include <QWidget>
#include "dip.h"

namespace Ui {
class FilterForm;
}

class FilterForm : public QWidget
{
    Q_OBJECT

public:
    explicit FilterForm(QImage image, QWidget *parent = nullptr);
    ~FilterForm();
    void ReadFilterVal();
    void NormalFilter();
    void AvgFilter(int filterSize = 3);
    void GaussianFilter();

private slots:
    void on_pushButton_clicked();
    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::FilterForm *ui;
    DIP DIP;
    QImage image;
    int *imageArray, filterSize = 5;
    float *filterVal;
};

#endif // FILTERFORM_H
