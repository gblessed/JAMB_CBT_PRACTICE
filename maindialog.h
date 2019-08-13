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
#include "loginwidget.h"
#include "examdetailswidget.h"
#include <QCoreApplication>
#include "examinationwidget.h"
namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = nullptr,QCoreApplication* app = nullptr);
    ~MainDialog();
    IntroWidget *firstPage = new IntroWidget(this);
    LoginWidget *secondPage =  new LoginWidget(this);
    ExamDetailsWidget *thirdPage =  new ExamDetailsWidget(this);
    ExaminationWidget *fourthPage = new ExaminationWidget(this);
public slots:
    void showTime();
    void stateChanged(QMediaPlayer::State state);
    void loginbuttonpushed(QString value);
    void changeuserpressed(bool pressed);
    void beginexam(int subjectId, bool mode,QStringList subjectsSelected);

private:
    Ui::MainDialog *ui;
    QCoreApplication* app;
    QString path;
    QStackedWidget* stackWidget;
    QLabel* timeLabel;
    QVideoWidget *introDisplay;
    QMediaPlayer *introPlayer;
    QString username;

};

#endif // MAINDIALOG_H
