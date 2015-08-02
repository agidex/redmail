#ifndef LINKBROWSER_H
#define LINKBROWSER_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>

#include <iostream>

#include <cmath>

#include "view/gridwidget.h"

using namespace std;

#include <QPushButton>

class LinkBrowser : public QObject
{
    Q_OBJECT
public:
    explicit LinkBrowser(GridWidget *widget, QObject *parent = 0);
    ~LinkBrowser();

    void resizeCluster(const int rows, const int cols);
signals:

public slots:
    void onWidgetResize(int w, int h);

private:
    void setGeo(QPushButton *button, int row, int col);

    GridWidget *widget;

    QList<QPushButton*> blist;

    int rows;
    int cols;
};

#endif // LINKBROWSER_H
