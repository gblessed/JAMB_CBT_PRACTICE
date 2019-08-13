#include "examdetailswidget.h"
#include <QMessageBox>
#include <QDebug>
ExamDetailsWidget::ExamDetailsWidget(QWidget *parent) : QWidget(parent)
{   QFont serifFont("Times", 10, QFont::StyleItalic);
    serifFont.setItalic(true);
    examDuration->setFont(serifFont);

    QFont examModeFont("Berlin Sans FB",20,QFont::Bold);
    examModeLabel->setFont(examModeFont);
    changeUser->setFixedWidth(80);
    changeUser->setStyleSheet("background-color: rgb(100, 100, 100)");

    QHBoxLayout *timeAndChange = new QHBoxLayout;

    timeAndChange->addWidget(examDuration);
    timeAndChange->setSpacing(80);
    timeAndChange->addWidget(changeUser);

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->addWidget(examModeLabel);

    hlayout2->setAlignment(Qt::AlignCenter);
    page3Layout->addLayout(timeAndChange);
    page3Layout->addLayout(hlayout2);

    jambModeButton->setCheckable(true);
    mockModeButton->setCheckable(true);
    jambModeButton->setAutoExclusive(true);
    mockModeButton->setAutoExclusive(true);
    QPalette palb(QPalette::Button,Qt::white);
    jambModeButton->setPalette(palb);
    mockModeButton->setPalette(palb);
    jambModeButton->setChecked(true);

    QFont trainingFont("Sanserif",20);
    trainingLabel->setFont(trainingFont);

    QHBoxLayout *hlayout3 = new QHBoxLayout;
    hlayout3->addWidget(mockModeButton);
    hlayout3->addWidget(trainingLabel);
    hlayout3->addWidget(jambModeButton);
    hlayout3->setAlignment(Qt::AlignCenter);
    page3Layout->addLayout(hlayout3);

    QHBoxLayout *hlayout4 = new  QHBoxLayout;
    hlayout4->addWidget(selectionLabel);
    hlayout4->setAlignment(Qt::AlignCenter);
    page3Layout->addLayout(hlayout4);

    QHBoxLayout *hlayout5 = new QHBoxLayout;
    subjectList ->addItem("PLEASE SELECT A SUBJECT");
    subjectList->addItem("biology");
    subjectList->addItem("chemistry");
    subjectList->addItem("commerce");
    subjectList->addItem("crs");
    subjectList->addItem("economics");
    subjectList->addItem("english");
    subjectList->addItem("geography");
    subjectList->addItem("government");
    subjectList->addItem("mathematics");
    subjectList->addItem("physics");

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



    setStyleSheet("QWidget {background-color: rgb(64,  125, 155,150);}");
    page3Layout->addWidget(startExam);
    startExam->setFixedWidth(80);
    startExam->setStyleSheet("background-color: rgb(255, 255, 127)");
    startExam->setDisabled(true);
    page3Layout->addWidget(startExam);

    setLayout(page3Layout);

    connect(addSubject,SIGNAL(clicked(bool)),this,SLOT(addSubjectSlot()));
    connect(mockModeButton,SIGNAL(clicked(bool)),this,SLOT(mockMode()));
    connect(jambModeButton,SIGNAL(clicked(bool)),this,SLOT(jambMode()));
    connect(changeUser,SIGNAL(clicked(bool)),this,SLOT(changeUserClicked()));
    connect(startExam,SIGNAL(clicked()),this,SLOT(beginExam()));

    connect(subjectList, QOverload<const QString &>::of(&QComboBox::activated),
          [=](const QString &text){  currentSelection = text;});
   subjectsSelected<<"";



}

void ExamDetailsWidget::addSubjectSlot(){

    subjectsSelected<<currentSelection;
    qDebug()<<currentSelection;

    if(subjectList->currentIndex() > 0 && mode == 1)
    {
        startExam->setDisabled(false);

        if (subjectId == 1)
        {
            subject1->setText(currentSelection);

        }
        if (subjectId == 2)
        {
            subject2->setText(currentSelection);

        }
        if (subjectId == 3)
        {
            subject3->setText(currentSelection);
        }
        if (subjectId == 4)
        {
            subject4->setText(currentSelection);

        }
        if(subjectId < 4)
 subjectId++;

    }
    else if(subjectList->currentIndex() > 0 && mode == 0)
       { subject1->setText(currentSelection);
         startExam->setDisabled(false);
    }

   if(subjectList->currentIndex() == 0)
    {
      QMessageBox::warning(this, "Invalid", "Select a Subject efrom the list ")  ;
    }




}
void ExamDetailsWidget::mockMode(){

    mode= 0;


    delete subject2;
    delete subject3;
    delete subject4;


}

void ExamDetailsWidget::jambMode(){
    mode =1;
    subject2 = new QLabel("No Subject Inserted");
    subject3 = new QLabel("No Subject Inserted");
    subject4 = new QLabel("No Subject Inserted");

    hlayout6->addWidget(subject2);
    hlayout6->addWidget(subject3);
    hlayout6->addWidget(subject4);


}

void ExamDetailsWidget::changeUserClicked(){

    emit changeuserpressed(true);

}

void ExamDetailsWidget::beginExam(){

    emit beginexam(subjectId, mode,subjectsSelected);
}

