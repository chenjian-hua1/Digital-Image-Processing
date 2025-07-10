#ifndef VIDEOFORM_H
#define VIDEOFORM_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>

namespace Ui {
class VideoForm;
}

class VideoForm : public QWidget
{
    Q_OBJECT

public:
    explicit VideoForm(QString &video_path, QWidget *parent = nullptr);
    ~VideoForm();

private:
    Ui::VideoForm *ui;
    QMediaPlayer *player;
};

#endif // VIDEOFORM_H
