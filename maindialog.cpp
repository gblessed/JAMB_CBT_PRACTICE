#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDir>
#include <QMessageBox>
MainDialog::MainDialog(QWidget *parent,QCoreApplication* app) :
    QDialog(parent),
    ui(new Ui::MainDialog),
      app(app),
    stackWidget(new QStackedWidget()),
    timeLabel(new QLabel("[00:00:00]"))
  {
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    setWindowFlag(Qt::WindowMaximizeButtonHint, false);

    QFont timeFont = QFont("Lucida Sans Unicode", 16);
    timeLabel->setFont(timeFont);
    QSpacerItem* spacerItem = new QSpacerItem(0, 0, QSizePolicy::Maximum, QSizePolicy::Minimum);

    QBoxLayout* mainLayout = new QVBoxLayout();
    QBoxLayout* timeLayout = new QHBoxLayout();
    timeLayout->insertSpacerItem(0, spacerItem);
    timeLayout->addWidget(timeLabel, 0, Qt::AlignRight);
    mainLayout->addWidget(stackWidget);
    mainLayout->addLayout(timeLayout);
    setLayout(mainLayout);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(500);

    QPalette pal;
    pal.setBrush(QPalette::Background, QPixmap(":/new/CBT-Lab1.jpg"));
    setPalette(pal);

    QWidget* widget = new QWidget();
    QPalette widgetPalette;
    widgetPalette.setBrush(QPalette::Window, QBrush(QColor("darkslateblue"), Qt::SolidPattern));
    widget->setPalette(widgetPalette);
    widget->setGeometry(0, 0, this->width(), this->width());





    stackWidget->addWidget(firstPage);
    connect(firstPage->introPlayer, &QMediaPlayer::stateChanged,this, &MainDialog::stateChanged);
    stackWidget->addWidget(secondPage);
    stackWidget->addWidget(thirdPage);

    stackWidget->setCurrentIndex(0);

    QDir myDir;

    Q_UNUSED(myDir.cd(app->applicationDirPath())); // cd returns a bool that is not used.
    path = myDir.currentPath();
    path = path.replace(path.section("/", -1), app->applicationName());
    Q_UNUSED(myDir.setCurrent(path));

    //Next few lines of code will setup your db file path and the subject path.
    path = myDir.currentPath() + "/data.json";
    QString dataPath(myDir.currentPath() + "/data.json");

    secondPage->setPath(dataPath);
    connect(secondPage, &LoginWidget::loginbuttonpushed,this, &MainDialog::loginbuttonpushed);

   connect(thirdPage, &ExamDetailsWidget::changeuserpressed, this, &MainDialog::changeuserpressed);
   connect(thirdPage, &ExamDetailsWidget::beginexam, this, &MainDialog::beginexam);

}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::showTime()
{
    QTime presentTime = QTime::currentTime();
    timeLabel->setText("[" + presentTime.toString("hh:mm:ss") + "]");
}

void MainDialog::stateChanged(QMediaPlayer::State state){
    if (state == QMediaPlayer::StoppedState){
        stackWidget->removeWidget(firstPage);
        delete firstPage;
    }
}

void MainDialog::loginbuttonpushed(QString value){
    username = value;

    stackWidget->setCurrentIndex(1);
    qDebug()<<"ssss"+QString::number(stackWidget->currentIndex());


}

void MainDialog::changeuserpressed(bool pressed){

    if (pressed == true)
    {stackWidget->setCurrentIndex(stackWidget->currentIndex()-1);
        delete  thirdPage;
    }
    thirdPage =  new ExamDetailsWidget(this);
    stackWidget->addWidget(thirdPage);

}

void MainDialog::beginexam(int subjectId, bool mode, QStringList subjectsSelected){

      if( (mode==1 && subjectId== 4) )
    { QMessageBox::StandardButtons reply;

            reply =  QMessageBox::question(this,"Confirm Login Details",
             "Hello "+username+", you have selected\nTYPE:MOCK MODE\nand the following subject"
                               ":"+subjectsSelected.at(1)+
                            ","+subjectsSelected.at(2)+","+subjectsSelected.at(3)+","+subjectsSelected.at(4)+"\nDo you still want to proceed?");

          if (reply == QMessageBox::Yes)
             { stackWidget->addWidget(fourthPage);
      stackWidget->setCurrentIndex(stackWidget->currentIndex()+1);}

    }

      if((mode == 0 && subjectId ==1))
    { QMessageBox::StandardButtons reply;

            reply =  QMessageBox::question(this,"Confirm Login Details",
             "Hello "+username+", you have selected\nTYPE:MOCK MODE\nand the following subject"
                               ":"+subjectsSelected.at(1)+
                            "\nDo you still want to proceed?");

          if (reply == QMessageBox::Yes)
             { stackWidget->addWidget(fourthPage);
      stackWidget->setCurrentIndex(stackWidget->currentIndex()+1);}

    }





}
