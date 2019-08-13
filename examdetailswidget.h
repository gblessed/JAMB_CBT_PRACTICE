#ifndef EXAMDETAILSWIDGET_H
#define EXAMDETAILSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
class ExamDetailsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExamDetailsWidget(QWidget *parent = nullptr);
private:
    QLabel *examModeLabel = new QLabel("<font color=#ffffff>EXAM MODE</font>");
    QBoxLayout *hlayout2 = new QHBoxLayout;
    QLabel *examDuration =new  QLabel("EXAM TIMER :: 2hrs 45mins 00secs and 1hr for Mock Mode");
    QPushButton *changeUser =  new QPushButton("Change User");
    QPushButton *addSubject = new QPushButton("Add Subject");
    QVBoxLayout *page3Layout= new QVBoxLayout;
    QLabel *trainingLabel = new QLabel("<font color =""yellow""> TRAINING MODE </font>");
    QPushButton *jambModeButton = new QPushButton("JAMB MODE");
    QPushButton *mockModeButton = new QPushButton("MOCK MODE");
    QLabel *selectionLabel = new QLabel("<font color =""white""> SUBJECTS SELECTION</font>");
    QComboBox *subjectList = new QComboBox;
        QLabel *subject1 = new QLabel("No Subject Inserted");
        QLabel *subject2 = new QLabel("No Subject Inserted")  ;
        QLabel *subject3 = new QLabel("No Subject Inserted") ;
        QLabel *subject4 = new QLabel("No Subject Inserted");
    QGroupBox *subjectBox = new QGroupBox;
    QGroupBox *examGroup = new QGroupBox;
    QStringList subjectsSelected;
    QPushButton *startExam = new QPushButton("Start Exam");
      QHBoxLayout *hlayout6 = new QHBoxLayout;
    int subjectId=1;
    QString currentSelection;
    bool mode=1;



signals:
    void changeuserpressed(bool clicked);
    void beginexam(int subjectId, bool mode, QStringList subjectSelected);


public slots:
    void addSubjectSlot();
    void mockMode();
    void jambMode();
    void changeUserClicked();
    void beginExam();

};

#endif // EXAMDETAILSWIDGET_H
