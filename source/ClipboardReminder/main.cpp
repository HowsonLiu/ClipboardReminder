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
#include "mainwindow.h"
#include "singleapplication.h"

int main(int argc, char *argv[])
{
    SingleApplication app(argc, argv,"Single");
    if(app.get_isrunning()){
        return 0;
    }
    MainWindow d;
    d.show();
    return app.exec();
}
