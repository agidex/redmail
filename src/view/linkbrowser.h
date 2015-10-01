#ifndef LINKBROWSER_H
#define LINKBROWSER_H

#include <QObject>
#include <QWidget>
//#include <QPushButton>

#include "view/gridwidget.h"
#include "view/viewcell.h"

#include "list/linkslist.h"

#include <iostream>
using namespace std;

#define CLUSTER_SIZE_INITIAL 2
#define LINK_ID_UNDEF 0

//typedef QPushButton ViewCell;

class LinkBrowser : public QObject
{
    Q_OBJECT
public:
    explicit LinkBrowser(GridWidget *_gridWidget, LinksList *list, QObject *parent = 0);
    ~LinkBrowser();

    void resizeCluster(const int size);
    const int clusterSize() const;

    void setAuto(const bool status);
    bool autoView() const;

signals:

public slots:
    void cellDone(CellID cellID, LinkID linkID);
    void forceStart();

private:
    void genRowsCols(int count, int *rows, int *cols);

    bool checkConditions(Link2Go l2g);
    void viewNewLink(CellID cellID);

    LinksList *_linksList;

    GridWidget *_gridWidget;
    QVector<ViewCell*> _cluster;

    bool _autoView;
};

#endif // LINKBROWSER_H
