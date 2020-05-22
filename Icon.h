#pragma once

#include <QLabel>
#include <QWidget>
#include <qevent.h>
#include <qdebug.h>
#include <qpropertyanimation.h>
constexpr auto ICON_WIDTH = 60;			//ͼ������
constexpr auto ICON_HEIGHT = 60;		//ͼ���߶�
constexpr auto UP = 8;                  //ͼ���߶�
constexpr auto DOWN = 2;                //ͼ���߶�
constexpr auto LEFT = 4;                //ͼ���߶�
constexpr auto RIGHT = 6;               //ͼ���߶�
static QString pixFileName[5] = { ":/back/k1.png", ":/back/k2.png" , ":/back/k3.png" , ":/back/k4.png" , ":/back/k5.png" };
struct Data {
    int x;
    int y;
    int kind;							//元素的种类
};

enum UnitStatus{  //单元样式枚举
    status_init = 0 , //初始状态
    status_deleted = -1, //被删除状态
    status_blue = 1, //样式例子 （待补充）
};

class Icon : public QLabel
{
    Q_OBJECT

signals:
    void Clicked();
    void Released();
    void Swap(int direction);
public:
    int column;
    int row;
    int status;
    int iconkind;
    Icon(QWidget * parent, Data d);
    ~Icon() {};
    void swapWith(Icon* i);
    void drop(int blocks);
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
private:
    //QString m_str;
    int originX;
    int originY;
    bool swapping;
};
