/********************************************************************************
** Form generated from reading UI file 'imgform.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMGFORM_H
#define UI_IMGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImgForm
{
public:
    QLabel *imagelabel;

    void setupUi(QWidget *ImgForm)
    {
        if (ImgForm->objectName().isEmpty())
            ImgForm->setObjectName("ImgForm");
        ImgForm->resize(296, 292);
        imagelabel = new QLabel(ImgForm);
        imagelabel->setObjectName("imagelabel");
        imagelabel->setGeometry(QRect(50, 30, 191, 211));
        imagelabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(ImgForm);

        QMetaObject::connectSlotsByName(ImgForm);
    } // setupUi

    void retranslateUi(QWidget *ImgForm)
    {
        ImgForm->setWindowTitle(QCoreApplication::translate("ImgForm", "Form", nullptr));
        imagelabel->setText(QCoreApplication::translate("ImgForm", "Image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImgForm: public Ui_ImgForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMGFORM_H
