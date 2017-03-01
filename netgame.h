#ifndef NETGAME_H
#define NETGAME_H
#include<QTcpServer>
//#include<QtNetwork/QTcpSocket>
#include<QTcpSocket>
#include "board.h"
class NetGame : public Board
{
    Q_OBJECT
public:
    NetGame(bool server);

    QTcpServer *_server;
    QTcpSocket *_socket;

    void click(int id,int row,int col);

public slots:
    void slotNewConnection();
    void slotRecv();
};

#endif // NETGAME_H
