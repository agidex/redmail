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
    void add(const Link2Go link, const int pos = -1);
    void addAll(const Link2GoList list);
    void del(const int pos);
    void delAll(const int posStart, const int posFinish);

    const Link2GoList list();
    const int size() const;

    ListModel* model() const;
signals:

public slots:

private:
    Link2GoList list_;
    ListModel *model_;

    void update();
};

#endif // LINKSLIST_H
