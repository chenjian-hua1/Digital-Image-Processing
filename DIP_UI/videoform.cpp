#include "videoform.h"
#include "ui_videoform.h"

VideoForm::VideoForm(QString &video_path, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VideoForm)
{
    ui->setupUi(this);

    // 建立播放器
    player = new QMediaPlayer(this);
    player->setVideoOutput(ui->videoWidget); // 將影片畫面輸出到 UI 上的 QVideoWidget

    // 設定影片路徑
    player->setSource(QUrl::fromLocalFile(video_path));

    // 自動播放
    player->play();
}

VideoForm::~VideoForm()
{
    delete ui;
}
