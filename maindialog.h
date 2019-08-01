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
namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = nullptr);
    ~MainDialog();

public slots:
    void showTime();


private:
    Ui::MainDialog *ui;

    QStackedWidget* stackWidget;
    QLabel* timeLabel;
    QVideoWidget *introDisplay;
        QMediaPlayer *introPlayer;

};

#endif // MAINDIALOG_H
