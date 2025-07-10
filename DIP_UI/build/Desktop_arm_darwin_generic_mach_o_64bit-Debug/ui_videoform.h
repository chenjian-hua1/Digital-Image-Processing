/********************************************************************************
** Form generated from reading UI file 'videoform.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOFORM_H
#define UI_VIDEOFORM_H

#include <QtCore/QVariant>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoForm
{
public:
    QPushButton *pushButton;
    QSlider *horizontalSlider;
    QVideoWidget *videoWidget;

    void setupUi(QWidget *VideoForm)
    {
        if (VideoForm->objectName().isEmpty())
            VideoForm->setObjectName("VideoForm");
        VideoForm->resize(640, 480);
        pushButton = new QPushButton(VideoForm);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(480, 420, 100, 32));
        horizontalSlider = new QSlider(VideoForm);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(100, 420, 321, 31));
        horizontalSlider->setOrientation(Qt::Orientation::Horizontal);
        videoWidget = new QVideoWidget(VideoForm);
        videoWidget->setObjectName("videoWidget");
        videoWidget->setGeometry(QRect(80, 40, 481, 331));

        retranslateUi(VideoForm);

        QMetaObject::connectSlotsByName(VideoForm);
    } // setupUi

    void retranslateUi(QWidget *VideoForm)
    {
        VideoForm->setWindowTitle(QCoreApplication::translate("VideoForm", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("VideoForm", "\346\232\253\345\201\234/\346\222\255\346\224\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoForm: public Ui_VideoForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOFORM_H
