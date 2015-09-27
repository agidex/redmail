#ifndef LINKBROWSER_H
#define LINKBROWSER_H

#include <QObject>
#include <QWidget>
//#include <QPushButton>

#include "view/gridwidget.h"
#include "view/viewcell.h"

#include <iostream>
using namespace std;

#define CLUSTER_SIZE_INITIAL 5

//typedef QPushButton ViewCell;

class LinkBrowser : public QObject
{
    Q_OBJECT
public:
    explicit LinkBrowser(GridWidget *gridWidget, QObject *parent = 0);
    ~LinkBrowser();

    void resizeCluster(const int size);
    const int clusterSize() const;

    void doit();

    void setAuto(bool status);
signals:

public slots:
    void cellDone(int cellID, int linkID);

private:
    void genRowsCols(int count, int *rows, int *cols);

    GridWidget *gridWidget;
    QVector<ViewCell*> cluster;

    bool autoView;
};

#endif // LINKBROWSER_H
