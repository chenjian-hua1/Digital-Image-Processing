/********************************************************************************
** Form generated from reading UI file 'bitplaneform.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BITPLANEFORM_H
#define UI_BITPLANEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BitPlaneForm
{
public:
    QSpinBox *spinBox;
    QLabel *ImageBox;

    void setupUi(QWidget *BitPlaneForm)
    {
        if (BitPlaneForm->objectName().isEmpty())
            BitPlaneForm->setObjectName("BitPlaneForm");
        BitPlaneForm->resize(409, 413);
        spinBox = new QSpinBox(BitPlaneForm);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(170, 340, 71, 41));
        QFont font;
        font.setPointSize(24);
        spinBox->setFont(font);
        spinBox->setMinimum(-1);
        spinBox->setMaximum(7);
        spinBox->setValue(-1);
        ImageBox = new QLabel(BitPlaneForm);
        ImageBox->setObjectName("ImageBox");
        ImageBox->setGeometry(QRect(60, 30, 301, 291));
        ImageBox->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(BitPlaneForm);

        QMetaObject::connectSlotsByName(BitPlaneForm);
    } // setupUi

    void retranslateUi(QWidget *BitPlaneForm)
    {
        BitPlaneForm->setWindowTitle(QCoreApplication::translate("BitPlaneForm", "Form", nullptr));
        ImageBox->setText(QCoreApplication::translate("BitPlaneForm", "Image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BitPlaneForm: public Ui_BitPlaneForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BITPLANEFORM_H
