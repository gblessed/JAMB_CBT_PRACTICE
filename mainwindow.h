 #ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QString>
#include <QMainWindow>
#include <QLabel>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QGroupBox>
#include <QtWidgets>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql>
#include <QTime>
#include <QRegularExpression>
#include <QFile>
#include <QProcess>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
       int calculateScore();
private:
     QVideoWidget *introDisplay;
     QMediaPlayer *introPlayer;
    QLabel *login = new QLabel("Login With : ");
    Ui::MainWindow *ui;
      QGroupBox *loginDetails;
       QComboBox *loginCombo;
       QPushButton *loginButton;
       QGroupBox *createDetails;
       QPushButton *male;
       QPushButton *female;
       QToolButton *hideButton = new QToolButton();
       QLabel *create = new QLabel("Register New User");
       QPushButton *createButton = new QPushButton("Save");
           bool showit= true;
             QLineEdit *name = new QLineEdit();
             QLabel *nameLabel = new QLabel("Name :");
              QLabel *examTimerLabel = new QLabel("Name :");
             int indexed=0;
QSqlDatabase db;
void populateUsers();
QLabel *examTimerLabel2 =new  QLabel("EXAM TIMER ::  03hrs 45mins 00secs");
QPushButton *changeUser =  new QPushButton("Change User");
QPushButton *addSubject = new QPushButton("Add Subject");
QStringList subjects;


    QLabel *subject1 = new QLabel("No Subject Inserted");
    QLabel *subject2 = new QLabel("No Subject Inserted")  ;
    QLabel *subject3 = new QLabel("No Subject Inserted") ;
    QLabel *subject4 = new QLabel("No Subject Inserted");
int subjectId=1;


QHBoxLayout *hlayout6 = new QHBoxLayout;

QPushButton *historyButton;
 QString sex1,name1;

    QGroupBox *examGroup = new QGroupBox;
    QGroupBox *subjectBox = new QGroupBox;
    QComboBox *subjectList = new QComboBox;
    QVBoxLayout *page3Layout = new QVBoxLayout;

QPushButton *jambModeButton = new QPushButton("JAMB MODE");

QTimer *startSecondTimer = new QTimer();
//..//../../..
QPushButton *mockModeButton = new QPushButton("MOCK MODE");
QPushButton *startExam = new QPushButton("Start Exam");

QGroupBox *headBar = new QGroupBox();
QHBoxLayout *firstRow = new QHBoxLayout;
QLabel *text1 = new QLabel("<font color =""white"">Exam Timer</font>");
QLabel *text2 = new QLabel("<font color =""white"">Question</font>");
QLabel *text3 = new QLabel("<font color =""white"">Chemistry</font>");
int mode =1;
//QTime counter;
QLabel *questionLabel = new QLabel("") ;
QLabel *ii =  new QLabel("");
QRadioButton *optionA[51];
QRadioButton *optionB = new QRadioButton();
QRadioButton *optionC = new QRadioButton();
QRadioButton *optionD = new QRadioButton();
QVBoxLayout *questionAreaLayout = new QVBoxLayout;
QScrollArea *questionArea = new QScrollArea;
QRadioButton *A = new QRadioButton();
QLabel *examTime = new QLabel();
int questionID =0;
void read(QString);
QStringList Chemistryquestions;
QStringList displayQuestions;

QPushButton *right = new QPushButton();

QPushButton *left = new QPushButton();

QPushButton *calculator = new QPushButton("Calculator");
QButtonGroup *options = new QButtonGroup;

QPushButton *submit = new QPushButton("SUBMIT");
//..//..//..//../
int questionWhat =1;


QLabel *questionWhatLabel = new QLabel("");
QVBoxLayout *questionAreaL = new QVBoxLayout();
QWidget *wiggy[50];
QVBoxLayout *pagedL[50];
QRadioButton *optA[200];
    QLabel *questionL[50];
    QStackedWidget *qnopt = new QStackedWidget();
    QStringList answers;
    QStringList chosen;
    int optionsA[50];
      int optionsB[50];
        int optionsC[50];
        int optionsD[50];
     int    score=0;
   private slots:
    void showtime();
    void stateChanged(QMediaPlayer::State newState);
//     void on_pushButton_clicked1();
     void createClicked();
     void loginClicked();
     void clickedSave();
     void next();
     void previous();
     void changeUserClicked();
     void addSubjectSlot();
     void mockMode();
     void jambMode();
    void beginExam();
    void updateLabel();
    void nextQuestion();
    void previousQuestion();
    void openCalculator();
    void submitted();


};

#endif // MAINWINDOW_H
