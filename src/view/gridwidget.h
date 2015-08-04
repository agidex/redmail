#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>

#include <iostream>
using namespace std;

class GridWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GridWidget(QWidget *parent = 0);
    ~GridWidget();
    void resizeEvent(QResizeEvent *event);

signals:
    void onResize();

public slots:

private:
//    QList<QPushButton*> *blist;

};

#endif // GRIDWIDGET_H
