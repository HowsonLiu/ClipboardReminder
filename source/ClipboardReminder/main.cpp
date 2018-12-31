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
