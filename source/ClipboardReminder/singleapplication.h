/**
 *		__  __                               __    _      
 *	   / / / /___ _      ___________  ____  / /   (_)_  __
 *	  / /_/ / __ \ | /| / / ___/ __ \/ __ \/ /   / / / / /
 *	 / __  / /_/ / |/ |/ (__  ) /_/ / / / / /___/ / /_/ / 
 *	/_/ /_/\____/|__/|__/____/\____/_/ /_/_____/_/\__,_/  
 *														  
 *github: https://github.com/HowsonLiu
 */

/*Add by CopyrightAppender*/
#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <QApplication>
#include <QSharedMemory>
#include <QLocalServer>

class SingleApplication : public QApplication
{
    Q_OBJECT

public:
    SingleApplication(int& argc, char* argv[], const QString uniquekey);
    bool get_isrunning();
    bool SendMessage(const QString& message);

public slots:
    void ReceiveMessage_Slot();

signals:
    void MessageAvailable_Signal(QString message);

private:
    bool isrunning_;
    QString uniquekey_;
    QSharedMemory sharememory_;
    QLocalServer* localserver_;
    static const int k_timeout_ = 1000;
};

#endif // SINGLEAPPLICATION_H
