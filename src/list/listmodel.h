#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractTableModel>
#include <QVariant>

#include "items/link2go.h"

class ListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ListModel(Link2GoHash *hash, QObject *parent = 0);
    ~ListModel();
    void update();
signals:

public slots:

private:
    Link2GoHash *_hash;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // LISTMODEL_H
