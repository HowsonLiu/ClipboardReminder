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
