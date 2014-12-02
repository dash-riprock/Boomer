#include "doubleclickbutton.h"
#include "mainwindow.h"
#include <iostream>
using std::cout; using std::endl;

QDoubleClickButton::QDoubleClickButton(QWidget *parent) :
    QPushButton(parent)
{
}

void QDoubleClickButton::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
        emit doubleClicked();
}

