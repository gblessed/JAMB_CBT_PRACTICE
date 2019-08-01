#include "maindialog.h"
#include "ui_maindialog.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog),
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


    QBoxLayout *widgetLayout = new QVBoxLayout;
    introDisplay= new QVideoWidget;
    introPlayer = new QMediaPlayer;
    introPlayer->setMedia(QUrl("qrc:/new/IntroVideo.mp4"));
    introPlayer->setVideoOutput(introDisplay);
    introPlayer->setVolume(50);
   // connect(introPlayer, &QMediaPlayer::stateChanged, this, &MainDialog::stateChanged);
    introPlayer->play();

    widgetLayout->addWidget(introDisplay);
    widget->setLayout(widgetLayout);
    stackWidget->addWidget(widget);
    stackWidget->setCurrentIndex(0);
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
