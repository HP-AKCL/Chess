#include "widget.h"
#include <QApplication>
#include <QMessageBox>
#include "netgame.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMessageBox::StandardButton ret;
    ret = QMessageBox::question(NULL,"server or client","server");

    bool bServer = false;
    if( ret == QMessageBox::Yes )
    {
        bServer = true;
    }

    NetGame game(bServer);
    game.show();
    return a.exec();
}
