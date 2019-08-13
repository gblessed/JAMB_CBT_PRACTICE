#include "loginwidget.h"
#include <QIODevice>
#include<QDebug>
#include <QMessageBox>
LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent)
{userSelect->addItem("Select User");
QHBoxLayout *login1 = new QHBoxLayout;

loginDetails->setFixedWidth(static_cast<int>(this->width()/0.2));
loginDetails->setFixedHeight(static_cast<int>(this->height()/0.2));
loginDetails->setTitle("CBT USER LOGIN");
loginDetails->setWindowOpacity(0);
loginDetails->setAlignment(Qt::AlignCenter);
loginDetails->setStyleSheet("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.494, fy:0.505273, stop:0 rgba(71, 47, 90, 75), stop:1 rgba(255, 255, 255, 75))");


login1->addWidget(loginlab);
login1->addWidget(userSelect);
login1->addWidget(loginButton);

login1->setAlignment(Qt::AlignCenter);
loginDetails->setLayout(login1);

QVBoxLayout *innerLayout =  new QVBoxLayout;

innerLayout->addWidget(loginDetails);

QHBoxLayout *login2 =  new QHBoxLayout;

newUser->setBuddy(hideButton);
login2->addWidget(hideButton);
login2->addWidget(newUser);

innerLayout->addLayout(login2);

qDebug()<<"Width "+QString::number(this->width());
qDebug()<<"Height "+QString::number(this->height());

hideButton->setFixedWidth(this->width()/2);

createDetails->setFixedWidth(static_cast<int>(this->width()/0.2));
createDetails->setFixedHeight(static_cast<int>(this->height()/0.2));
createDetails->setAlignment(Qt::AlignCenter);
createDetails->setTitle("Create New User");
createDetails->setFixedHeight(150);
createDetails->setStyleSheet("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.494, fy:0.505273, stop:0 rgba(71, 47, 90, 75), stop:1 rgba(255, 255, 255, 75))");
createDetails->setWindowOpacity(0);


//innerLayout->addWidget(createDetails);

nameLabel->setBuddy(name);
QHBoxLayout *createLayout =  new QHBoxLayout;

createLayout->addWidget(nameLabel);
createLayout->addWidget(name);
createLayout->addWidget(createButton);

createDetails->setLayout(createLayout);

innerLayout->addWidget(createDetails);

createDetails->hide();

hideButton->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));
connect(hideButton, SIGNAL(clicked()),this,SLOT(createDetailsShow()));

connect(loginButton, SIGNAL(clicked()),this,SLOT(loginClicked()));

connect(createButton, SIGNAL(clicked()), this, SLOT(saveUser()));



connect(userSelect, QOverload<int>::of(&QComboBox::currentIndexChanged),
      [=](int index){ indexed = index; });






pageLayout->addLayout(innerLayout);



pageLayout->setAlignment(Qt::AlignCenter);
setLayout(pageLayout);




}

void LoginWidget::saveUser(){

    QFile db;
    db.setFileName(dbPath);

   if((db.open(QIODevice::ReadWrite | QIODevice::Text)))
                 qDebug()<<"open";


    root = QJsonDocument::fromJson(db.readAll()).array();
  userList = root.operator[](0).toObject();
   QJsonArray k =  userList.operator[]("users").toArray();
   k.append(QJsonValue(name->text()));

   userList.insert("users",QJsonValue(k));
   userSelect->addItem(name->text());
   root.replace(0, QJsonValue(userList));

   Q_UNUSED(db.resize(0));
   db.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
   db.close();



}

void LoginWidget::setPath(QString Path){

    dbPath  = Path;
   populateUsers();

}

void LoginWidget::createDetailsShow(){

    if(showit)
        {
            createDetails->show();
            hideButton->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
        }
        else
        {

            createDetails->hide();
            hideButton->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));

        }
        showit = !showit;

   }

void LoginWidget::loginClicked(){
    QFile db;
    db.setFileName(dbPath);
    if (indexed == 0)
        QMessageBox::information(this,"Invalid Selection","Invalid Selection!!!\nPlease Select a User");
    if (indexed>0){
Q_UNUSED(db.open(QIODevice::ReadOnly));
        root = QJsonDocument::fromJson(db.readAll()).array();
      userList = root.operator[](0).toObject();
       QJsonArray k =  userList.operator[]("users").toArray();
       username = k.operator[](indexed).toString();
       qDebug()<<username;

        emit loginbuttonpushed(username);
         }

db.close();
}


void LoginWidget::populateUsers(){
            QFile db;
            db.setFileName(dbPath);
          if(db.open(QIODevice::ReadOnly | QIODevice::Text))
                qDebug()<<dbPath;

            root = QJsonDocument::fromJson(db.readAll()).array();
            qDebug()<<"here";
          userList = root.operator[](0).toObject();
          QJsonArray k =  userList.operator[]("users").toArray();
           qDebug()<<QString::number(k.size());
          for(int i=0; i<k.size(); i++)
           userSelect->addItem(k.operator[](i).toString());

  db.close();
}
