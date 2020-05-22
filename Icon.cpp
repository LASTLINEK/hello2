#include "Icon.h"

Icon::Icon(QWidget * parent, Data d):QLabel(parent)
{
    this->setGeometry(d.x, d.y, ICON_WIDTH, ICON_HEIGHT);
    QPixmap pix(pixFileName[d.kind]);
    originX = 0;
    originY = 0;
    status = d.kind;  //初始化状态
    swapping = false;
    this->setPixmap(pix);
    this->setScaledContents(true);
    this->show();
}

void Icon::swapWith(Icon * i)
{
    int tempCol = i->column;
    int tempRow = i->row;
    i->column = this->column;
    i->row = this->row;
    this->column = tempCol;
    this->row = tempRow;
    QPropertyAnimation* aniThis = new QPropertyAnimation(this, "geometry");
    QPropertyAnimation* aniThat = new QPropertyAnimation(i, "geometry");

    aniThis->setStartValue(this->geometry());
    aniThat->setStartValue(i->geometry());
    aniThis->setEndValue(i->geometry());
    aniThat->setEndValue(this->geometry());

    aniThis->setDuration(400);
    aniThat->setDuration(400);
    aniThis->start();
    aniThat->start();
}

void Icon::drop(int blocks)
{
    QPropertyAnimation* ani = new QPropertyAnimation(this, "geometry");
    ani->setDuration(500);
    ani->setStartValue(this->geometry());
    int endX = this->x();
    int endY = this->y() + blocks * ICON_HEIGHT;
    ani->setKeyValueAt(0.75, QRect(endX, endY, ICON_WIDTH, ICON_HEIGHT));
    ani->setKeyValueAt(0.9, QRect(endX, endY - 15, ICON_WIDTH, ICON_HEIGHT));
    ani->setEndValue(QRect(endX, endY, ICON_HEIGHT, ICON_HEIGHT));
    ani->start();
}

void Icon::mouseMoveEvent(QMouseEvent * event)
{
    if (swapping) {
        return;
    }
    int endX = event->globalX();
    int endY = event->globalY();
    bool shouldSwap = false;
    if (endX > originX + ICON_WIDTH) {
        shouldSwap = true;
        emit Swap(RIGHT);
    }
    else if (endX < originX - ICON_WIDTH) {
        shouldSwap = true;
        emit Swap(LEFT);
    }
    else if (endY > originY + ICON_HEIGHT) {
        shouldSwap = true;
        emit Swap(DOWN);
    }
    else if (endY < originY - ICON_WIDTH) {
        shouldSwap = true;
        emit Swap(UP);
    }
    if (shouldSwap) {
        swapping = true;
        originX = endX;
        originY = endY;
    }
}

void Icon::mousePressEvent(QMouseEvent * e)
{
    originX = e->globalX();
    originY = e->globalY();
    emit Clicked();
}

void Icon::mouseReleaseEvent(QMouseEvent * event)
{
    swapping = false;
    emit Released();
}
//写一些修改进行测试
