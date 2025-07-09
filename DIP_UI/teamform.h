#ifndef TEAMFORM_H
#define TEAMFORM_H

#include <QWidget>

namespace Ui {
class TeamForm;
}

class TeamForm : public QWidget
{
    Q_OBJECT

public:
    explicit TeamForm(QWidget *parent = nullptr);
    ~TeamForm();

private:
    Ui::TeamForm *ui;
};

#endif // TEAMFORM_H
