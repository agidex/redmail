#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractTableModel>
#include <QVariant>

#include "items/link2go.h"

class ListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ListModel(Link2GoList *lst, QObject *parent = 0);
    ~ListModel();
    void update();
signals:

public slots:

private:
    Link2GoList *list_;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // LISTMODEL_H
