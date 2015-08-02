#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>

#include <QPushButton>

#include <cmath>
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
    void onResize(int w, int h);

public slots:

private:
};

#endif // GRIDWIDGET_H
