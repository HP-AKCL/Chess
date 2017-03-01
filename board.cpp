#include "board.h"
#include<QPainter>
Board::Board(QWidget *parent) : QWidget(parent)
{
    int i = 0;
    for( i = 0 ; i < 32 ; i++)
    {
        _s[i].init(i);//将32棋子进行初始化
    }
    _selectid = -1;
    _bRedTurn = true;//红先行。

}

void Board::init(bool bRedRide)
{
    if(bRedRide)
    {
        update();
    }
    else
    {
        int i;
        for( i = 0; i < 32; i++)
        {
            _s[i]._red = !_s[i]._red;
        }
        update();
    }
}
void Board::trySelectStone(int id)
{
    if( id = -1) return;
    if(!canSelect(id))  return;
    _selectid = id;
    update();
}

bool Board::canSelect(int id)
{
    return _bRedTurn == _s[id]._red;
}

void Board::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int line = 0;
    int d = 40; //间距大小
    _r = d/2;//设置棋子半径

    //开始划线  10横9竖  九宫格
    for( line = 1 ; line < 11; line++)
    {
        painter.drawLine(QPoint(d,line*d),QPoint(9*d,line*d));
    }
    for(line = 1; line < 10; line++)
    {
        if( line == 1 || line == 9)
           painter.drawLine(QPoint(line*d, d), QPoint(line*d, 10*d));
        else
        {
            painter.drawLine(QPoint(line*d, d), QPoint(line*d, 5*d));
            painter.drawLine(QPoint(line*d, 6*d), QPoint(line*d, 10*d));
        }
    }
    painter.drawLine(QPoint(4*d, 1*d), QPoint(6*d, 3*d));
    painter.drawLine(QPoint(6*d, 1*d), QPoint(4*d, 3*d));
    painter.drawLine(QPoint(4*d, 8*d), QPoint(6*d, 10*d));
    painter.drawLine(QPoint(6*d, 8*d), QPoint(4*d, 10*d));
    //划线结束

    //绘制棋子
    for( line = 0; line < 32; line++)
    {
        drawStone(painter,line);
    }
}

void Board::drawStone(QPainter &paint, int id)
{
    if(_s[id]._dead)    return;//棋子死亡则不显示。

    QPoint c = getcenter(id);
    QRect rect = QRect(c.x()-_r,c.y()-_r,_r*2,_r*2);

    if(id == _selectid)
        paint.setBrush(QBrush(Qt::gray));//选中则改变颜色
    else
        paint.setBrush(QBrush(Qt::yellow));

    paint.setPen(Qt::black);
    paint.drawEllipse(getcenter(id),_r,_r);//画出棋子形状

    if(_s[id]._red)
        paint.setPen(Qt::red);
    paint.setFont(QFont("system",_r,700));//设置棋子的字
    paint.drawText(rect,_s[id].getText(),QTextOption(Qt::AlignCenter));//写上棋子的字
}

bool Board::couldMove(int moveid, int row, int col, int killid)
{
    if( _s[moveid]._red == _s[killid]._red )//若两个棋子同一颜色，则改变选中的棋子
    {
        _selectid = killid;
        update();
        return false;
    }

    switch(_s[moveid]._type)//按棋子类型选择行动规则
    {
    case Stone::JIANG:
        return couldMove1(moveid,row,col);
    case Stone::SHI:
        return couldMove2(moveid,row,col);
    case Stone::XIANG:
        return couldMove3(moveid,row,col);
    case Stone::CHE:
        return couldMove4(moveid,row,col);
    case Stone::MA:
        return couldMove5(moveid,row,col);
    case Stone::PAO:
        return couldMove6(moveid,row,col);
    case Stone::BING:
        return couldMove7(moveid,row,col);
    }
}

bool Board::couldMove1(int moveid, int row, int col)
{//JIANG
    int r,c,d;
    if( _s[moveid]._red )
    {
        if( row > 2 ) return false;
    }
    else
    {
        if( row < 7 ) return false;
    }

    if( col < 3 || col > 5) return false;

    r = _s[moveid]._row - row;
    c = _s[moveid]._col - col;
    d = abs(r)*10 + abs(c);
    if( d == 10 || d == 1 )
        return true;
    else
        return false;

}

bool Board::couldMove2(int moveid, int row, int col)
{//SHI
    int r,c,d;
    if( _s[moveid]._red )
    {
        if( row > 2 ) return false;
    }
    else
    {
        if( row < 7 ) return false;
    }
    if( col < 3 || col > 5) return false;

    r = _s[moveid]._row - row;
    c = _s[moveid]._col - col;
    d = abs(r)*10 + abs(c);
    if( d == 11 )
        return true;
    else
        return false;
}

bool Board::couldMove3(int moveid, int row, int col)
{//XIANG
    int r,c,d;
    if( _s[moveid]._red )
    {
        if( row > 5 ) return false;
    }
    else
    {
        if( row < 5 ) return false;
    }
    r = _s[moveid]._row - row;
    c = _s[moveid]._col - col;
    d = abs(r)*10 + abs(c);
    if( d == 22 )
        return true;
    else
        return false;
}

bool Board::couldMove4(int moveid, int row, int col)
{//CHE
    int r,c,d;
    r = _s[moveid]._row - row;
    c = _s[moveid]._col - col;
    d = abs(r)*10 + abs(c);
    if( d%10 == 0 || d/10 == 0 )
        return true;
    else
        return false;
}

bool Board::couldMove5(int moveid, int row, int col)
{//MA
    int r,c,d;
    r = _s[moveid]._row - row;
    c = _s[moveid]._col - col;
    d = abs(r)*10 + abs(c);
    if( d == 12 || d == 21 )
        return true;
    else
        return false;
}

bool Board::couldMove6(int moveid, int row, int col)
{//PAO
    int r,c,d;
    r = _s[moveid]._row - row;
    c = _s[moveid]._col - col;
    d = abs(r)*10 + abs(c);
    if( d%10 == 0 || d/10 == 0 )
        return true;
    else
        return false;
}

bool Board::couldMove7(int moveid, int row, int col)
{//BING
    int r,c,d;
    r = _s[moveid]._row - row;
    c = _s[moveid]._col - col;
    d = abs(r)*10 + abs(c);
    if( d == 10 || d == 1 )
        return true;
    else
        return false;
}

QPoint Board::getcenter(int row, int col)
{
    QPoint ret;
    ret.rx() = (col + 1) * _r * 2;//col*2取得离当前位置少去一个格子的距离
    ret.ry() = (row + 1) * _r * 2;
    return ret;
}

QPoint Board::getcenter(int id)
{
    return getcenter(_s[id]._row,_s[id]._col);
}

bool Board::getRowCol(QPoint pt, int &row, int &col)
{
    QPoint c;
    int x,y,dis;
    for( row = 0; row < 10; row++)
    {
        for(col = 0; col < 9; col++)
        {
            c   = getcenter(row,col);
            x   = c.x() - pt.rx();
            y   = c.y() - pt.ry();
            dis = x*x + y*y;
            if(dis < _r*_r)
                return true;
        }
    }
    return false;
}

void Board::click(int id, int row, int col)
{
    {
        if(this->_selectid == -1)
        {
            trySelectStone(id);
        }
        else
        {
            //tryMoveStone(id, row, col);
        }
    }
}
/*
void Board::tryMoveStone(int killid, int row, int col)
{
    if(killid != -1 && sameColor(killid,_selectid))
    {
        trySelectStone(killid);
        return;
    }
    bool ret = canMove(_selectid,killid,row,col);
    if(ret)
    {
        moveStone(_selectid,killid,row,col);
        _selectid = -1;
        update();
    }
}
*/
void Board::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pt = event->pos();//获得鼠标点击的点
    int row,col,i,clickid;
    bool ret  = getRowCol(pt,row,col);//确定是否点击在棋盘上

    if(ret == false)
        return;
    clickid = -1;
    for( i = 0; i < 32; i++)
    {
        if(_s[i]._col == col && _s[i]._row == row && _s[i]._dead == false)
                break;
    }
    if( i < 32 )
        clickid = i;//选中棋子时，将选中时的i值赋予
    if(_selectid == -1)
    {
        if(_bRedTurn == _s[clickid]._red)
        {
            _selectid = clickid;
            update();
        }
    }
    else
    {
        if(couldMove(_selectid,row,col,clickid))
        {
            _s[_selectid]._row = row;
            _s[_selectid]._col = col;
            if(clickid != -1)
                _s[clickid]._dead = true;
            _selectid = -1;
            _bRedTurn = !_bRedTurn;//转换控制权
            update();
        }
    }
}
