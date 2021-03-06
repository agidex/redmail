#include "listmodel.h"

ListModel::ListModel(Link2GoHash *hash, QObject *parent) :
    QAbstractTableModel(parent)
{
    this->_hash = hash;
}

ListModel::~ListModel()
{
}

void ListModel::update()
{
    this->reset();
}

int ListModel::rowCount(const QModelIndex &parent) const
{
    return this->_hash->size();
}

int ListModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant ListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QList<QString> headData;
    headData << "Link" << "Interval" << "Status";

    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            return headData.at(section);
        }
        else if (orientation == Qt::Vertical) {
            return QString::number(section + 1);
        }
    }
    else {
        return QVariant();
    }

    return QVariant();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        LinkID key = this->_hash->keys().at(index.row());
        Link2Go l2g = this->_hash->value(key);

        switch (index.column()) {
            case 0 : {
                return QVariant(l2g.link());
            }
            case 1 : {
                return QVariant(QString::number(l2g.interval()));
            }
            case 2 : {
                switch (l2g.status()) {
                    case link2go::ST_READY : {
                        return QVariant(QString("Ready"));
                    }
                    case link2go::ST_VIEW : {
                        return QVariant(QString("View"));
                    }
                    case link2go::ST_DONE : {
                        return QVariant(QString("Done"));
                    }
                }
            }
            default : {
                return QVariant();
            }
        }
    }
    return QVariant();
}



