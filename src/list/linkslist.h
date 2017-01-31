#ifndef LINKSLIST_H
#define LINKSLIST_H

#include <QObject>

#include <QtSql>

#include "items/link2go.h"
//#include "list/listmodel.h"

const QString DB_PATH = "e:\\PROG\\c++\\QtProjects\\redmail\\links.db";

class LinksList : public QObject
{
    Q_OBJECT
public:
    explicit LinksList(QObject *parent = 0);
    ~LinksList();

    void add(const Link2Go l2g);
    void addAll(const Link2GoList l2g_list);
    void del(const LinkID link_ID);

    const bool canNext();
    Link2Go next();
    void ok(const LinkID linkID);
    void done(const LinkID linkID);


    QSqlTableModel* dbModel() const;
signals:

public slots:

private:
    QSqlDatabase _linksDb;

    QSqlTableModel *_dbModel;

    void updateStatus(LinkID linkID, int status);
};

#endif // LINKSLIST_H
