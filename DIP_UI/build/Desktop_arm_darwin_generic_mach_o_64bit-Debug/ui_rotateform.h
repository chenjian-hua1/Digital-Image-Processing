/********************************************************************************
** Form generated from reading UI file 'rotateform.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROTATEFORM_H
#define UI_ROTATEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RotateForm
{
public:
    QLabel *ImageBox;
    QCheckBox *checkBox;
    QSpinBox *spinBox;
    QLabel *label;

    void setupUi(QWidget *RotateForm)
    {
        if (RotateForm->objectName().isEmpty())
            RotateForm->setObjectName("RotateForm");
        RotateForm->resize(675, 474);
        ImageBox = new QLabel(RotateForm);
        ImageBox->setObjectName("ImageBox");
        ImageBox->setGeometry(QRect(350, 60, 271, 331));
        ImageBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        checkBox = new QCheckBox(RotateForm);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(100, 240, 191, 20));
        QFont font;
        font.setPointSize(20);
        checkBox->setFont(font);
        spinBox = new QSpinBox(RotateForm);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(100, 290, 81, 41));
        spinBox->setFont(font);
        spinBox->setMinimum(-360);
        spinBox->setMaximum(360);
        spinBox->setValue(0);
        label = new QLabel(RotateForm);
        label->setObjectName("label");
        label->setGeometry(QRect(200, 310, 91, 16));
        QFont font1;
        font1.setPointSize(16);
        label->setFont(font1);

        retranslateUi(RotateForm);

        QMetaObject::connectSlotsByName(RotateForm);
    } // setupUi

    void retranslateUi(QWidget *RotateForm)
    {
        RotateForm->setWindowTitle(QCoreApplication::translate("RotateForm", "Form", nullptr));
        ImageBox->setText(QCoreApplication::translate("RotateForm", "Image", nullptr));
        checkBox->setText(QCoreApplication::translate("RotateForm", "Inverse Rotate", nullptr));
        label->setText(QCoreApplication::translate("RotateForm", "N x M", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RotateForm: public Ui_RotateForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROTATEFORM_H
