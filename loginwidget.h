#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QGroupBox>
#include <QLineEdit>
#include <QStackedWidget>
class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);
    void setPath(QString Path);
    void setStack(QStackedWidget *);

private:
QLabel *loginlab = new QLabel("Login With:");
QComboBox *userSelect =  new QComboBox();
QPushButton *loginButton = new QPushButton("Login");
  QPushButton *hideButton  = new QPushButton();
   QVBoxLayout *pageLayout = new QVBoxLayout;
   QJsonArray root;
    QString dbPath;
      QJsonObject userList;
    bool showit= true;
      QLineEdit *name = new QLineEdit();
      QLabel *nameLabel = new QLabel("Name :");
      QGroupBox *loginDetails = new QGroupBox();
      QGroupBox *createDetails = new QGroupBox();
      QPushButton *createButton =  new QPushButton("Save");
      QLabel *newUser =  new QLabel("Register your name");
      int indexed;
      void populateUsers();
      QString username;
signals:
         void loginbuttonpushed(QString value);

public slots:
   void saveUser();
   void createDetailsShow();
   void loginClicked();

};

#endif // LOGINWIDGET_H
