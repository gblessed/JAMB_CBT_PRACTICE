#include "introwidget.h"

IntroWidget::IntroWidget(QWidget *parent) : QWidget(parent)
{
    introDisplay = new QVideoWidget();
        introPlayer = new QMediaPlayer();
        introPlayer->setMedia(QUrl("qrc:/new/IntroVideo.mp4"));
       introPlayer->setVideoOutput(introDisplay);
       introPlayer->setVolume(50);
//connect(introPlayer, &QMediaPlayer::stateChanged, this, &IntroWidget::stateChanged);
        introPlayer->play();

        widgetLayout->addWidget(introDisplay);
        setLayout(widgetLayout);


}
