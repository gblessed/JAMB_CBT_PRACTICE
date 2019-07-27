#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QTimer>
#include <QVideoWidget>
inline QTime counter(1,0,0);


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
        QPixmap background(":/new/CBT-Lab1.jpg");
        QPalette pal;
        pal.setBrush(QPalette::Background,background);
        setPalette(pal);



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
{     QRegularExpressionMatch match = reg.match(Chemistryquestions.at(i));
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
