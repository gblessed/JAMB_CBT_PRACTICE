#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QStackedWidget>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVideoWidget>
#include <QMediaPlayer>
#include "introwidget.h"
namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = nullptr);
    ~MainDialog();
    IntroWidget *firstPage = new IntroWidget(this);
public slots:
    void showTime();
    void stateChanged(QMediaPlayer::State state);

private:
    Ui::MainDialog *ui;

    QStackedWidget* stackWidget;
    QLabel* timeLabel;
    QVideoWidget *introDisplay;
    QMediaPlayer *introPlayer;

};

#endif // MAINDIALOG_H
