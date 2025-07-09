/********************************************************************************
** Form generated from reading UI file 'form2.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM2_H
#define UI_FORM2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_Form2
{
public:
    QCheckBox *checkBox;

    void setupUi(QDialog *Form2)
    {
        if (Form2->objectName().isEmpty())
            Form2->setObjectName("Form2");
        Form2->resize(640, 480);
        Form2->setSizeGripEnabled(false);
        checkBox = new QCheckBox(Form2);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(220, 290, 85, 20));

        retranslateUi(Form2);

        QMetaObject::connectSlotsByName(Form2);
    } // setupUi

    void retranslateUi(QDialog *Form2)
    {
        Form2->setWindowTitle(QCoreApplication::translate("Form2", "Dialog", nullptr));
        checkBox->setText(QCoreApplication::translate("Form2", "CheckBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form2: public Ui_Form2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM2_H
