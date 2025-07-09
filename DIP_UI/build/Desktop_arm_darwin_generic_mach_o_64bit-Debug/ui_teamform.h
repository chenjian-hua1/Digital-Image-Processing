/********************************************************************************
** Form generated from reading UI file 'teamform.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEAMFORM_H
#define UI_TEAMFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TeamForm
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QWidget *TeamForm)
    {
        if (TeamForm->objectName().isEmpty())
            TeamForm->setObjectName("TeamForm");
        TeamForm->resize(640, 480);
        label = new QLabel(TeamForm);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 30, 131, 51));
        QFont font;
        font.setPointSize(32);
        label->setFont(font);
        label_2 = new QLabel(TeamForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(80, 130, 101, 21));
        QFont font1;
        font1.setPointSize(24);
        label_2->setFont(font1);
        label_3 = new QLabel(TeamForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(80, 160, 91, 21));
        label_3->setFont(font1);
        label_4 = new QLabel(TeamForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(80, 190, 81, 21));
        label_4->setFont(font1);
        label_5 = new QLabel(TeamForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(80, 220, 101, 31));
        label_5->setFont(font1);

        retranslateUi(TeamForm);

        QMetaObject::connectSlotsByName(TeamForm);
    } // setupUi

    void retranslateUi(QWidget *TeamForm)
    {
        TeamForm->setWindowTitle(QCoreApplication::translate("TeamForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("TeamForm", "Team 12", nullptr));
        label_2->setText(QCoreApplication::translate("TeamForm", "\351\220\230\345\256\266\345\207\261", nullptr));
        label_3->setText(QCoreApplication::translate("TeamForm", "\347\216\213\347\226\217\351\240\201", nullptr));
        label_4->setText(QCoreApplication::translate("TeamForm", "\351\231\263\345\273\272\346\250\272", nullptr));
        label_5->setText(QCoreApplication::translate("TeamForm", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TeamForm: public Ui_TeamForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEAMFORM_H
