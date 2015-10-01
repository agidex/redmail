#ifndef LINKSLIST_H
#define LINKSLIST_H

#include <QObject>

#include "items/link2go.h"
#include "list/listmodel.h"

class LinksList : public QObject
{
    Q_OBJECT
public:
    explicit LinksList(QObject *parent = 0);
    ~LinksList();

    void add(const Link2Go l2g);
    void addAll(const Link2GoList l2g_list);
    void del(const LinkID link_ID);

    bool canNext();
    Link2Go next(LinkID *linkID);
    void ok(LinkID linkID);
    void done(LinkID linkID);

    ListModel* model() const;
signals:

public slots:

private:
    Link2GoHash _hash;
    LinkID _linkIDcounter;

    QHash<LinkID, int> _readyList;
    int _lastReady;

    QHash<LinkID, int> _nowList;
    QList<LinkID> _doneList;

    ListModel *_model;

    void update();
};

#endif // LINKSLIST_H
