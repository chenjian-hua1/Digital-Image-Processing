/********************************************************************************
** Form generated from reading UI file 'scaleform.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCALEFORM_H
#define UI_SCALEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScaleForm
{
public:
    QLabel *ImageBox;
    QScrollBar *horizontalScrollBar;
    QLabel *label;
    QRadioButton *linearButton;
    QRadioButton *neighborButton;

    void setupUi(QWidget *ScaleForm)
    {
        if (ScaleForm->objectName().isEmpty())
            ScaleForm->setObjectName("ScaleForm");
        ScaleForm->resize(640, 480);
        ImageBox = new QLabel(ScaleForm);
        ImageBox->setObjectName("ImageBox");
        ImageBox->setGeometry(QRect(300, 70, 311, 311));
        ImageBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        horizontalScrollBar = new QScrollBar(ScaleForm);
        horizontalScrollBar->setObjectName("horizontalScrollBar");
        horizontalScrollBar->setGeometry(QRect(60, 300, 160, 16));
        horizontalScrollBar->setMinimum(30);
        horizontalScrollBar->setMaximum(300);
        horizontalScrollBar->setValue(100);
        horizontalScrollBar->setOrientation(Qt::Orientation::Horizontal);
        label = new QLabel(ScaleForm);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 270, 161, 20));
        linearButton = new QRadioButton(ScaleForm);
        linearButton->setObjectName("linearButton");
        linearButton->setGeometry(QRect(80, 160, 99, 20));
        neighborButton = new QRadioButton(ScaleForm);
        neighborButton->setObjectName("neighborButton");
        neighborButton->setGeometry(QRect(80, 190, 99, 20));

        retranslateUi(ScaleForm);

        QMetaObject::connectSlotsByName(ScaleForm);
    } // setupUi

    void retranslateUi(QWidget *ScaleForm)
    {
        ScaleForm->setWindowTitle(QCoreApplication::translate("ScaleForm", "Form", nullptr));
        ImageBox->setText(QCoreApplication::translate("ScaleForm", "Image", nullptr));
        label->setText(QCoreApplication::translate("ScaleForm", "Scale Rate: 1.0", nullptr));
        linearButton->setText(QCoreApplication::translate("ScaleForm", "Linear", nullptr));
        neighborButton->setText(QCoreApplication::translate("ScaleForm", "Neighbor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScaleForm: public Ui_ScaleForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCALEFORM_H
