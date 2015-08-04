#ifndef LINKBROWSER_H
#define LINKBROWSER_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

#include "view/gridwidget.h"

#include <iostream>
using namespace std;

#define CLUSTER_SIZE_INITIAL 5

typedef QPushButton ViewCell;

class LinkBrowser : public QObject
{
    Q_OBJECT
public:
    explicit LinkBrowser(GridWidget *gridWidget, QObject *parent = 0);
    ~LinkBrowser();

    void resizeCluster(const int size);
    const int clusterSize() const;

signals:

public slots:

private:
    void genRowsCols(int count, int *rows, int *cols);

    GridWidget *gridWidget;
    QList<ViewCell*> cluster;
};

#endif // LINKBROWSER_H
