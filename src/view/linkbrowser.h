#ifndef LINKBROWSER_H
#define LINKBROWSER_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

#include <cmath>

#include "view/gridwidget.h"

#include <iostream>
using namespace std;

typedef QPushButton ViewCell;

class LinkBrowser : public QObject
{
    Q_OBJECT
public:
    explicit LinkBrowser(GridWidget *widget, QObject *parent = 0);
    ~LinkBrowser();

    void resizeCluster(unsigned const int rows, unsigned const int cols);
    void clusterSize(unsigned int *rows, unsigned int *cols) const;

//    void resizeCluster(unsigned const int size);
//    unsigned const int clusterSize() const;
signals:

public slots:
    void onWidgetResize();

private:
    GridWidget *widget;

    QList<ViewCell*> cluster;

    unsigned int rows;
    unsigned int cols;
};

#endif // LINKBROWSER_H
