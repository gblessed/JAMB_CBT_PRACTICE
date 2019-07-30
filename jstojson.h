#ifndef JSTOJSON_H
#define JSTOJSON_H

#include <QObject>
#include <QCoreApplication>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

class JSToJson : public QObject
{
    Q_OBJECT
public:
    JSToJson(QCoreApplication* app = nullptr, QObject* parent = nullptr): QObject(parent),
        app(app)
    {
        //Next few lines of code will be able to navigate to your project directory.
        QDir myDir;
        QString path;
        Q_UNUSED(myDir.cd(app->applicationDirPath()));
        path = myDir.currentPath();
        path = path.replace(path.section("/", -1), app->applicationName());
        Q_UNUSED(myDir.setCurrent(path));

        //Next few lines of code will setup your db file path and the subject path.
        QString dataPath(myDir.currentPath() + "/data.json");
        QString subjectPath(myDir.currentPath() + "/phy-2-ask.txt"); //Change the subject file name and file extension for other subjects.
        myFile.setFileName(dataPath);
        subjectFile.setFileName(subjectPath);
        if(!myFile.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            qDebug().noquote() << "Why not?";
        }

        //Assigning db objects.
        root = QJsonDocument::fromJson(myFile.readAll()).array();
        questionList = root.operator[](1).toObject();

        //Change the Subject in the constructor below to add new subject, then uncomment the nextline if not in use!
        subject = QString("physics");
        questionList.insert(subject, QJsonValue(QJsonArray()).toArray());
        questions = questionList.operator[](subject).toArray();

        //Uncomment this section of lines to perform a new subject operation
//        Q_UNUSED(getQuestionFromFile());
//        Q_UNUSED(getOptionsFromFile());
//        Q_UNUSED(getAnswerFromFile());


        //Cleanup to update all changes made.
        root.replace(1, QJsonValue(questionList));
        Q_UNUSED(myFile.resize(0));
        myFile.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
        myFile.close();
    }

    inline bool getQuestionFromFile()
    {
        int i = 1;
        int j = 1;
        QRegularExpression reg("(\")(.*)(\")");
        QString line;
        if(questionList.contains(subject))
        {
            if(!subjectFile.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                qDebug().noquote() << "Why now?";
            }
            while(!subjectFile.atEnd() && j <= 250)
            {
                line = QString(subjectFile.readLine());
                quest.insert("id", QJsonValue(i));
                QRegularExpressionMatch match = reg.match(line);
                if(match.hasMatch() && (j % 10 == 6 || j % 10 == 1))
                {
                    line = match.captured(2);
                    quest.insert("question", QJsonValue(line));
                    questions.append(QJsonValue(quest));
                    i++;
                }
                j++;
            }
            questionList.insert(subject, QJsonValue(questions));
            subjectFile.close();
            return true;
        }
        else
        {
            return false;
        }
    }

    inline bool getOptionsFromFile()
    {
        int i = 0;
        int j = 1;
        QRegularExpression reg("(\")(.*)(\")");
        QString line;
        if(questionList.contains(subject))
        {
            if(!subjectFile.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                qDebug().noquote() << "Why now?";
            }
            QJsonArray options;
            while(!subjectFile.atEnd() && j <= 250)
            {
                line = QString(subjectFile.readLine());
                quest = questions.operator[](i).toObject();
                if(!quest.contains("options"))
                {
                    quest.insert("options", QJsonValue(QJsonArray()).toArray());
                }
                options = quest.operator[]("options").toArray();
                QRegularExpressionMatch match = reg.match(line);
                if(match.hasMatch() && !((j % 10 == 1) || (j % 10 == 6)))
                {
                    line = match.captured(2);
                    options.append(QJsonValue(line));
                    quest.insert("options", QJsonValue(options));
                    questions.replace(i, QJsonValue(quest));
                }
                if((j % 10 == 5) || (j % 10 == 0))
                {
                    i++;
                }
                j++;
            }
            questionList.insert(subject, QJsonValue(questions));
            subjectFile.close();
            return true;
        }
        else
        {
            return false;
        }
    }

    inline bool getAnswerFromFile()
    {
        int i = 0;
        int j = 1;
        QChar ch('\0');
        int val = -1;
        QRegularExpression reg("(\")(\\d\\d\\w)(\")");
        QString line;
        if(questionList.contains(subject))
        {
            if(!subjectFile.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                qDebug().noquote() << "Why now?";
            }
            while(!subjectFile.atEnd() && j <= 300)
            {
                line = QString(subjectFile.readLine());
                quest = questions.operator[](i).toObject();
                quest.insert("answer", QJsonValue(QJsonValue::Null));
                QRegularExpressionMatch match = reg.match(line);
                if(match.hasMatch() && j > 250)
                {
                    line = match.captured(2);
                    ch = line.back();
                    if(ch == 'a')
                    {
                        val = 0;
                    }
                    else if(ch == 'b')
                    {
                        val = 1;
                    }
                    else if(ch == 'c')
                    {
                        val = 2;
                    }
                    else if(ch == 'd')
                    {
                        val = 3;
                    }
                    quest.insert("answer", QJsonValue(val));
                    questions.replace(i, QJsonValue(quest));
                    i++;
                }
                j++;
            }
            questionList.insert(subject, QJsonValue(questions));
            subjectFile.close();
            return true;
        }
        else
        {
            return false;
        }
    }

private:
    QCoreApplication* app;
    QJsonArray root;
    QJsonObject questionList;
    QJsonArray questions;
    QJsonObject quest;
    QFile myFile;
    QFile subjectFile;
    QString subject;
};

#endif // JSTOJSON_H
