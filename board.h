#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPoint>
#include <QPaintEvent>
#include <stone.h>

/*********************
 * 此文件用于绘制
 * 控制棋子行走
 *********************/

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);
    //in inet
    void init(bool bRedRide);

    bool _bSide;
    //棋子属性
    Stone _s[32];//棋子
    int   _r;//棋子半径
    int   _selectid;//被选中的棋子id
    bool  _bRedTurn;//控制权的转换标志

    //获得棋子的中心点坐标
    QPoint getcenter(int row,int col);
    QPoint getcenter(int id);

    //判断点pt是否在棋盘上。
    bool getRowCol(QPoint pt,int &row,int &col);
    void click(int id,int row,int col);
    void trySelectStone(int id);
    bool canSelect(int id);
    void tryMoveStone(int killid,int row,int col);

    //判断鼠标点击的棋子是否移动。
    void mouseReleaseEvent(QMouseEvent *event);

    //绘制
    void paintEvent(QPaintEvent *event);//棋盘 绘制
    void drawStone(QPainter& paint,int id);//棋子 绘制

    //棋子移动规则
    bool couldMove(int moveid,int row,int col,int killid);
    bool couldMove1(int moveid,int row,int col);//JIANG
    bool couldMove2(int moveid,int row,int col);//SHI
    bool couldMove3(int moveid,int row,int col);//XIANG
    bool couldMove4(int moveid,int row,int col);//CHE
    bool couldMove5(int moveid,int row,int col);//MA
    bool couldMove6(int moveid,int row,int col);//PAO
    bool couldMove7(int moveid,int row,int col);//BING
signals:

public slots:
};

#endif // BOARD_H
