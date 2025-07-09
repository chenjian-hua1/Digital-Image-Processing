#include "teamform.h"
#include "ui_teamform.h"

TeamForm::TeamForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TeamForm)
{
    ui->setupUi(this);
}

TeamForm::~TeamForm()
{
    delete ui;
}
