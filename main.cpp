/**
 *      ___           ___           ___           ___           ___           ___           ___                   ___     
 *     /\__\         /\  \         /\__\         /\  \         /\  \         /\__\         /\__\      ___        /\__\    
 *    /:/  /        /::\  \       /:/ _/_       /::\  \       /::\  \       /::|  |       /:/  /     /\  \      /:/  /    
 *   /:/__/        /:/\:\  \     /:/ /\__\     /:/\ \  \     /:/\:\  \     /:|:|  |      /:/  /      \:\  \    /:/  /     
 *  /::\  \ ___   /:/  \:\  \   /:/ /:/ _/_   _\:\~\ \  \   /:/  \:\  \   /:/|:|  |__   /:/  /       /::\__\  /:/  /  ___ 
 * /:/\:\  /\__\ /:/__/ \:\__\ /:/_/:/ /\__\ /\ \:\ \ \__\ /:/__/ \:\__\ /:/ |:| /\__\ /:/__/     __/:/\/__/ /:/__/  /\__\
 * \/__\:\/:/  / \:\  \ /:/  / \:\/:/ /:/  / \:\ \:\ \/__/ \:\  \ /:/  / \/__|:|/:/  / \:\  \    /\/:/  /    \:\  \ /:/  /
 *      \::/  /   \:\  /:/  /   \::/_/:/  /   \:\ \:\__\    \:\  /:/  /      |:/:/  /   \:\  \   \::/__/      \:\  /:/  / 
 *      /:/  /     \:\/:/  /     \:\/:/  /     \:\/:/  /     \:\/:/  /       |::/  /     \:\  \   \:\__\       \:\/:/  /  
 *     /:/  /       \::/  /       \::/  /       \::/  /       \::/  /        /:/  /       \:\__\   \/__/        \::/  /   
 *     \/__/         \/__/         \/__/         \/__/         \/__/         \/__/         \/__/                 \/__/    
 *	 
 *	 github: https://github.com/HowsonLiu
 */

/*Add by CopyrightAppender*/
#include "mainwindow.h"
#include "singleapplication.h"
#include <QSettings>

int main(int argc, char *argv[])
{
    SingleApplication app(argc, argv,"Single");
    if(app.get_isrunning()){
        return 0;
    }
    QString appName = app.applicationName();
    QString appPath = app.applicationFilePath();
    appPath = appPath.replace("/","\\");
    QSettings *reg=new QSettings(
                "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                QSettings::NativeFormat);
    QString val = reg->value(appName).toString();
    if(val != appPath)
        reg->setValue(appName,appPath);
    reg->deleteLater();
    MainWindow d;
    d.show();
    return app.exec();
}
