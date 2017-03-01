#ifndef STONE_H
#define STONE_H
#include <QString>
/****************
 *此文件用于定义棋子
 *棋子的行走规则等
 ***************/
class Stone
{
public:
    Stone();
    enum TYPE{
        JIANG,CHE,PAO,MA,BING,SHI,XIANG
    };//棋子的类别
    int  _row;
    int  _col;
    TYPE _type;
    int  _id;
    bool _dead;
    bool _red;

    QString getText();
    void init(int id);//根据id进行初始化棋子。

};

#endif // STONE_H
