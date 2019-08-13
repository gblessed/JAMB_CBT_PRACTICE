#ifndef INTROWIDGET_H
#define INTROWIDGET_H

#include <QObject>
#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QVBoxLayout>

class IntroWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IntroWidget(QWidget *parent = nullptr);
     QMediaPlayer *introPlayer;
private:

    QVideoWidget *introDisplay;
    QVBoxLayout *widgetLayout = new QVBoxLayout;


signals:

public slots:
};

#endif // INTROWIDGET_H
