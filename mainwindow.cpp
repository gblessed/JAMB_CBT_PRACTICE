#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QTimer>
#include <QVideoWidget>
QTime counter(1,0,0);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
this->setWindowState(Qt::WindowMaximized);

    setWindowFlag(Qt::WindowMaximizeButtonHint,false);
    //..================================================================
    //this->setWindowOpacity();
    QTimer *timer = new QTimer(this);
      connect(timer, SIGNAL(timeout()), this, SLOT(showtime()));
       timer->start(500);
//aassdddbbnnnmmmvvvvcccxxxcccxxxxswwdqwdawfwfwfwfwfwf.asdfghjkllqwerqwertyuiosdfghjkl.
       QPixmap background(":/new/CBT-Lab1.jpg");
       QPalette pal;
       pal.setBrush(QPalette::Background,background);
       setPalette(pal);

       introDisplay= new QVideoWidget;

         //ui->verticalacaclaclaclacla
        introPlayer = new QMediaPlayer;
        introPlayer->setMedia(QUrl("qrc:/new/IntroVideo.mp4"));
        introPlayer->setVideoOutput(introDisplay);
        introPlayer->setVolume(50);
        connect(introPlayer, &QMediaPlayer::stateChanged, this, &MainWindow::stateChanged);
        introPlayer->play();
        QPushButton *pushButton = new QPushButton("SKIP");

        QVBoxLayout *firstPageLayout = new QVBoxLayout;
        firstPageLayout->addWidget(introDisplay);
        firstPageLayout->addWidget(pushButton);

ui->page_5->setLayout(firstPageLayout);
loginCombo = new QComboBox();

loginCombo->addItem("Select a User");
loginButton = new QPushButton("Login");
QVBoxLayout *secondPage = new QVBoxLayout;
QGroupBox *createDetails = new QGroupBox;
createDetails->setFixedWidth(this->width()/0.8);
createDetails->setFixedHeight(this->height()/0.8);
createDetails->setAlignment(Qt::AlignCenter);
createDetails->setTitle("Create New User");
createDetails->setFixedHeight(150);
QHBoxLayout *row1 = new QHBoxLayout;
row1->addWidget(login);
row1->addWidget(loginCombo);
row1->addWidget(loginButton);
row1->setAlignment(Qt::AlignCenter);
createDetails->setLayout(row1);

populateUsers();

      db = QSqlDatabase::addDatabase("QSQLITE");
//db.setHostName("acidalia");
      QString homeLoation = (QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append("db.sqlite"));

      //QStandardPaths::l
     // homeLoation.append("logindb.sqlite");

      qDebug()<<homeLoation;

//  if ( !QFile::exists(homeLoation))
//       QFile::copy(":/new/logindb.sqlite",homeLoation);
db.setDatabaseName(homeLoation);
if(db.open())
    qDebug()<<"db  open";
else
{qDebug()<<"DB NOT OPEN";}


connect(loginButton,SIGNAL(clicked()),this,SLOT(loginClicked()));

secondPage->addWidget(createDetails);
secondPage->setAlignment(Qt::AlignCenter);
QHBoxLayout *hlayout = new QHBoxLayout;
hlayout->addWidget(hideButton);
hlayout->addWidget(create);
create->setBuddy(hideButton);

hideButton->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));
connect(hideButton, SIGNAL(clicked()),this,SLOT(createClicked()));

secondPage->addLayout(hlayout);


loginDetails = new QGroupBox();
loginDetails->setAlignment(Qt::AlignCenter);

loginDetails->setFixedWidth(this->width()/1.5);
loginDetails->setFixedHeight(this->height()/1.5);
loginDetails->setTitle("CBT USER LOGIN");
loginDetails->setWindowOpacity(0);
createDetails->setWindowOpacity(0);
loginDetails->setStyleSheet("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.494, fy:0.505273, stop:0 rgba(71, 47, 90, 75), stop:1 rgba(255, 255, 255, 75))");
createDetails->setStyleSheet("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.494, fy:0.505273, stop:0 rgba(71, 47, 90, 75), stop:1 rgba(255, 255, 255, 75))");

QHBoxLayout *createLayout = new QHBoxLayout;
male = new QPushButton("M");
female = new QPushButton("F");
male->setCheckable(true);
female->setCheckable(true);
male->setAutoExclusive(true);
female->setAutoExclusive(true);
male->setFixedWidth(20);



createLayout->addWidget(male);
createLayout->addWidget(female);


female->setFixedWidth(20);
male->setChecked(true);
createLayout->addWidget(male);
createLayout->addWidget(female);

nameLabel->setBuddy(name);

//createDetails->setStyleSheet();

createLayout->addWidget(nameLabel);
createLayout->addWidget(name);

QVBoxLayout *vlayout = new QVBoxLayout;
vlayout->addLayout(createLayout);
vlayout->addWidget(createButton);

loginDetails->setLayout(vlayout);

secondPage->addWidget(loginDetails);


connect(createButton, SIGNAL(clicked()),this,SLOT(clickedSave()));
populateUsers();
loginDetails->hide();

ui->page_6->setLayout(secondPage);
connect(loginCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
      [=](int index){ indexed = index; });

//abcdefghijklmnop---------=-------------
setPalette(pal);

changeUser->setFixedWidth(80);
changeUser->setStyleSheet("background-color: rgb(100, 100, 100)");

QHBoxLayout *timeAndChange = new QHBoxLayout;
timeAndChange->addWidget(examTimerLabel2);

timeAndChange->setSpacing(80);
timeAndChange->addWidget(changeUser);

QFont serifFont("Times", 10, QFont::StyleItalic);
serifFont.setItalic(true);
examTimerLabel2->setFont(serifFont);


connect(changeUser,SIGNAL(clicked(bool)),this,SLOT(changeUserClicked()));

QLabel *examModeLabel = new QLabel("<font color=#ffffff>EXAM MODE</font>");
QFont examModeFont("Berlin Sans FB",20,QFont::Bold);

examModeLabel->setFont(examModeFont);

QHBoxLayout *hlayout2 = new QHBoxLayout;
hlayout2->addWidget(examModeLabel);


int x = page3Layout->spacing();
qDebug()<<x;
hlayout2->setAlignment(Qt::AlignCenter);
page3Layout->addLayout(timeAndChange);
page3Layout->addLayout(hlayout2);

jambModeButton->setCheckable(true);
mockModeButton->setCheckable(true);
jambModeButton->setAutoExclusive(true);
mockModeButton->setAutoExclusive(true);

QHBoxLayout *hlayout3 = new QHBoxLayout;
hlayout3->addWidget(mockModeButton);
QLabel *trainingLabel = new QLabel("<font color =""yellow""> TRAINING MODE </font>");

QFont trainingFont("Sanserif",20);
trainingLabel->setFont(trainingFont);
hlayout3->addWidget(trainingLabel);

hlayout3->addWidget(jambModeButton);
//{{{{{}
hlayout3->setAlignment(Qt::AlignCenter);
page3Layout->addLayout(hlayout3);

QLabel *selectionLabel = new QLabel("<font color =""white""> SUBJECTS SELECTION</font>");
QHBoxLayout *hlayout4 = new  QHBoxLayout;
hlayout4->addWidget(selectionLabel);
page3Layout->addLayout(hlayout4);
hlayout4->setAlignment(Qt::AlignCenter);

QPalette palb(QPalette::Button,Qt::white);
jambModeButton->setPalette(palb);
mockModeButton->setPalette(palb);
jambModeButton->setChecked(true);
QHBoxLayout *hlayout5 = new QHBoxLayout;
subjectList ->addItem("PLEASE SELECT A SUBJECT");
subjectList->addItem("Chemistry");
hlayout5->addWidget(subjectList);
hlayout5->addWidget(addSubject);

QVBoxLayout *vlayoutx = new QVBoxLayout;

hlayout6->addWidget(subject1);
hlayout6->addWidget(subject2);
hlayout6->addWidget(subject3);
hlayout6->addWidget(subject4);
subjectBox->setLayout(hlayout6);
vlayoutx->addLayout(hlayout5);
vlayoutx->addWidget(subjectBox);



examGroup->setLayout(vlayoutx);

page3Layout->addWidget(examGroup);

//===================================================================================

//page3Layout->addWidget(historyButton);

//=---------->>>>>>>>>>>>>>>>>>>>>>>>>>






ui->page->setLayout(page3Layout);
ui->page->setStyleSheet("QWidget {background-color: rgb(64,  125, 155,150);}");

connect(addSubject,SIGNAL(clicked(bool)),this,SLOT(addSubjectSlot()));

connect(mockModeButton,SIGNAL(clicked(bool)),this,SLOT(mockMode()));

connect(jambModeButton,SIGNAL(clicked(bool)),this,SLOT(jambMode()));

connect(startExam,SIGNAL(clicked()),this,SLOT(beginExam()));
startExam->setDisabled(true);



//--- ---  ---  ---  ---  --- --- --- --- ---  ----  ----  ---  ---
headBar->setStyleSheet("QWidget {background-color: rgb(0,  0, 0,255);}");
headBar->setFixedHeight(90);
firstRow->addWidget(text1);
firstRow->addWidget(text2);
firstRow->addWidget(text3);
QVBoxLayout *headBarLayout= new QVBoxLayout;
headBarLayout->addLayout(firstRow);

QHBoxLayout *hlayout9 = new QHBoxLayout;
hlayout9->addWidget(examTime);
hlayout9->addWidget(questionWhatLabel);

hlayout9->addWidget(calculator);
QFont calcFont("Britannic Bold",15);
calculator->setStyleSheet("background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 255, 255), stop:1 rgba(255, 255, 255, 255));");
connect(calculator,SIGNAL(clicked()),this,SLOT(openCalculator()));
calculator->setFont(calcFont);

//hlayout9->setSpacing();
headBarLayout->addLayout(hlayout9);

QFont examTimeFont("Berlin Sans FB",20,QFont::Bold);

examTime->setFont(examTimeFont);
examTime->setStyleSheet("QLabel {color:red}");
headBar->setLayout(headBarLayout);
//questionArea->setWidgetResizable(true);

//questionArea->setLayout(questionAreaLayout);
//..//..//..////....///...//..//..//..//..//..//..//..//..;;

QVBoxLayout *page4Layout = new QVBoxLayout;
page4Layout->addWidget(headBar);
page4Layout->addWidget(qnopt);
//page4Layout->addWidget(questionArea);
//questionArea->setStyleSheet("background-color: rgb(255, 255, 255)");

//questionAreaLayout->addWidget(qnopt);
//



//...//...//...//...//...//...///...//...//...///...




right->setIcon(style()->standardIcon(QStyle::SP_ArrowRight)); left->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));


connect(right,SIGNAL(clicked(bool)),this,SLOT(nextQuestion()));

connect(left,SIGNAL(clicked(bool)),this,SLOT(previousQuestion()));

connect(submit,SIGNAL(clicked(bool)),this,SLOT(submitted()));

right->setFixedWidth(150);
left->setFixedWidth(150);
submit->setFixedWidth(200);
questionWhatLabel->setStyleSheet("QLabel {color:red}");
QFont questionfont("Sanserif",12);

questionWhatLabel->setFont(examTimeFont);
//..//..//..//..//..//..//..//..///..//.//..//..//..//..//..//...///..//..//..//..//..//...//..//../..//..//..//..
QHBoxLayout *rowx = new QHBoxLayout;
rowx->addWidget(left);
submit->setStyleSheet("background-color: rgb(194, 0, 0)");
rowx->addWidget(submit);
rowx->addWidget(right);

page4Layout->addLayout(rowx);
QFont ff("Sanserif",11);



int j =0;
for(int i = 0; i<200; i+=4)
{
    optionsA[j] = i;
    optionsB[j] = i+1;
    optionsC[j] = i+2;
    optionsD[j] = i+3;
    j++;
}



ui->page_2->setLayout(page4Layout);
//


for(int i =0; i<50; i++){
    chosen<<" ";
     }

QString name = ":/new/chemistry.txt";
read(name);


for (int i=0; i<50; i++)
{   int kj =0;

    wiggy[i]= new QWidget();
    pagedL[i] = new QVBoxLayout;
    questionL[i] = new QLabel(displayQuestions.at(questionID));

    questionID++;
    questionL[i]->setWordWrap(true);
    wiggy[i]->setLayout(pagedL[i]);
    pagedL[i]->addWidget(questionL[i]);
qnopt->addWidget(wiggy[i]);
    for(int k=0; k<4; k++){
          optA[kj] = new QRadioButton(displayQuestions.at(questionID),this);
           questionID++;
          pagedL[i]->addWidget(optA[kj]);

          kj++;
                         }


}









}




MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::showtime(){

    QTime today = QTime::currentTime();

    QString date = today.toString("hh:mm:ss");
     QFont loginFont("SansSerif",15);
    ui->label->setAlignment(Qt::AlignRight);
    ui->label->setFont(loginFont);
    ui->label->setText("[" +date+  "]");

}

void MainWindow::stateChanged(QMediaPlayer::State newState)
{
    if (newState == QMediaPlayer::StoppedState)
   next();
        //QMessageBox::information(this,"Virus Notification","Trojan detected");


}

//void MainWindow::on_pushButton_clicked1()
//{
//    introPlayer->stop();
//}


void MainWindow::createClicked(){

    if(showit)
    {
        loginDetails->show();
        hideButton->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
    }
    else
    {

        loginDetails->hide();
        hideButton->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));

    }
    showit = !showit;
}




void MainWindow::loginClicked(){

    qDebug()<<indexed;

    QString id =  QString::number(indexed);
if (indexed == 0)
    QMessageBox::information(this,"Invalid Selection","Invalid Selection!!!\nPlease Select a User");
else if(indexed > 0)
{ { QSqlQuery qruy("SELECT * FROM loginData WHERE rowid ='"+id +"'");
        if(qruy.next())
         {
            name1 = qruy.value(0).toString();
           sex1  = qruy.value(1).toString();}
}

    QString historyText =  name1;
    historyText.append(" History");
   historyButton = new QPushButton(historyText);
page3Layout->addWidget(historyButton);
page3Layout->addWidget(startExam);
startExam->setFixedWidth(80);
startExam->setStyleSheet("background-color: rgb(255, 255, 127)");
  qDebug()<<name1;
  qDebug()<<sex1;
next();


}
else
{

   QMessageBox::warning(this,"Invalid Selection","User Selection is Invalid, Please Select again");



}

}



void MainWindow::populateUsers(){
    QSqlQuery qruy("SELECT * FROM loginData");
    QString sex,name;


    while(qruy.next()){
       name = qruy.value(0).toString();
       loginCombo->addItem(name);
    }






}



void MainWindow::clickedSave(){
    QSqlQuery qruy;
    QString username = name->text();
    QString sex;
    if(male->isChecked())
        sex = "M";
    else
        sex = "F";

    if (qruy.exec("INSERT INTO loginData(name,sex) VALUES('"+username +"','"+sex +"')"))
   { //qDebug()<<"testing purpose "+username+" ";
     loginCombo->addItem(username);  }





}

void MainWindow::next(){


     ui->stackedWidget->setCurrentIndex((ui->stackedWidget->currentIndex())+1);

}


void MainWindow::previous(){


     ui->stackedWidget->setCurrentIndex((ui->stackedWidget->currentIndex())-1);

}

void MainWindow::changeUserClicked(){

    ui->stackedWidget->setCurrentIndex((ui->stackedWidget->currentIndex())-1);




}

void MainWindow::addSubjectSlot(){
subjects<<""<<"Chemistry";
qDebug()<<subjectList->currentIndex();

if(subjectList->currentIndex() > 0)
{
    startExam->setDisabled(false);

    if (subjectId == 1)
    {
        subject1->setText(subjects.at(subjectList->currentIndex()));

    }
 subjectId++;

}
if(subjectList->currentIndex() == 0)
{
  QMessageBox::warning(this, "Invalid", "Select a Subject from the list ")  ;
}

}

void MainWindow::mockMode(){




    delete subject2;
    delete subject3;
    delete subject4;


}
void MainWindow::jambMode(){
    subject2 = new QLabel("No Subject Inserted");
    subject3 = new QLabel("No Subject Inserted");
    subject4 = new QLabel("No Subject Inserted");

    hlayout6->addWidget(subject2);
    hlayout6->addWidget(subject3);
    hlayout6->addWidget(subject4);

}

void MainWindow::beginExam(){

   QMessageBox::StandardButtons reply;
if(mockModeButton->isChecked())
 { reply =  QMessageBox::question(this,"Confirm Login Details",
   "Hello "+name1+", you have selected\nTYPE:MOCK MODE\nand the following subject:"+subjects.at(subjectList->currentIndex())+"\nDo you still want to proceed?");
mode =1;
}
if (reply == QMessageBox::Yes)
{   next();
    if(mode == 1)
    {
        if(subjects.at(subjectList->currentIndex()) == "Chemistry")
        {
                QString name = ":/new/chemistry.txt";
            read(name);
        }
    connect(startSecondTimer,SIGNAL(timeout()),this,SLOT(updateLabel()));
    startSecondTimer->start(1000);
    QString num = QString::number(questionWhat);
questionWhatLabel->setText(" "+num+"");






    }
}








}



void MainWindow::updateLabel(){

   examTime->setText(counter.toString());
   counter =  counter.addSecs(-1);
}


void MainWindow::read(QString filename)
{   QFile myfile(filename);
    if(!myfile.open(QFile::ReadOnly | QFile::Text))
      {
      qDebug()<<"File did not create successfully";
               return;
       }
    QTextStream a(&myfile);
    while(!a.atEnd())
    {
Chemistryquestions += a.readLine();

}

    QRegularExpression reg("([\"])(.*)([\"])");


    for(int i =0; i<Chemistryquestions.size(); i++)
{     QRegularExpressionMatch match = reg.match(Chemistryquestions.at(i),3);
        if(match.hasMatch())
            { QString x = match.captured(2);
            displayQuestions<<x;
             qDebug()<<x;
            }
}
}

void MainWindow::nextQuestion(){
    questionWhat++;
    questionWhat = (questionWhat <= 50) ? questionWhat : 50;
    QString num = QString::number(questionWhat);

questionWhatLabel->setText( ""+num+"");
if(optA[0]->isChecked())
    qDebug()<<"seen 1";
if(optA[1]->isChecked())
    qDebug()<<"seen 1";

    qnopt->setCurrentIndex(qnopt->currentIndex()+1);


}

void MainWindow::previousQuestion(){
    questionWhat--;
     questionWhat = (questionWhat > 0) ? questionWhat : 1;
    QString num = QString::number(questionWhat);
questionWhatLabel->setText(""+num+"");

    qnopt->setCurrentIndex(qnopt->currentIndex()-1);

}

void MainWindow::openCalculator(){

    QProcess *proc =  new QProcess();
    proc->start("calc.exe");
}

void MainWindow::submitted(){
    if(optA[0]->isChecked())
        qDebug()<<"0 is checked";
    QMessageBox::StandardButtons reply ;
    reply = QMessageBox::question(this,"CONFIRM SUBMISSION", "Are you Sure that you want to Submit?");
    if(reply == QMessageBox::Yes){
if(optA[0]->isChecked())
        qDebug()<<"0 is checked";

  score = calculateScore();

         }




}

int MainWindow::calculateScore(){
    if (mode==1){
        qDebug()<<questionID;

        QRegularExpression reg("([\\d]*)([\\w])");

        for (int i=0; i<50; i++)
        {  QRegularExpressionMatch match = reg.match(displayQuestions.at(questionID));
            if(match.hasMatch())
            { QString x =match.captured(2);
            answers<< x;
            qDebug()<<x;
            questionID++;}

        }

        qDebug()<<"started checking";

    for(int i=0; i<200; i++) {
        qnopt->setCurrentWidget(wiggy[0]);
              if(optA[199]->isChecked())
            qDebug()<<"0 is checked";
//           if(optA[i]->isChecked())
//               qDebug()<<"1 checked";
//             {
//                for(int j = 0; j<50; j++){

//              if(i == optionsA[j])
//                  chosen<<"a";
//                else if(i == optionsB[j])
//                  chosen<<"b";
//                else if(i == optionsC[j])
//                chosen<<"c";
//               else  if(i == optionsD[j])
//                chosen<<"d";
//                 }

//                  }

  }
qDebug()<<"done checking";

    for(int i =0; i<50; i++)
    {
        if(chosen.at(i)==answers.at(i))
            score++;

    }

   qDebug()<<score;

}

 return score;}
