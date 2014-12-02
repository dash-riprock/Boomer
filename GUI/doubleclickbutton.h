#ifndef DOUBLECLICKBUTTON_H
#define DOUBLECLICKBUTTON_H

#include <ui_mainwindow.h>
#include <QPushButton>
#include <QMouseEvent>

class QDoubleClickButton : public QPushButton
{
    Q_OBJECT

public:
    QDoubleClickButton(QWidget *parent = 0);

public slots:
    void mouseDoubleClickEvent(QMouseEvent *e);

signals:
    void doubleClicked();

};

#endif // DOUBLECLICKBUTTON_H
