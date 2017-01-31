#include "linkslist.h"

LinksList::LinksList(QObject *parent) :
    QObject(parent)
{
    // neue scheisse

    this->_linksDb = QSqlDatabase::addDatabase("QSQLITE");
    this->_linksDb.setDatabaseName(DB_PATH);
    this->_linksDb.open();

    this->_dbModel = new QSqlTableModel();
    this->_dbModel->setTable("links");
    this->_dbModel->select();
}

LinksList::~LinksList()
{
    this->_linksDb.close();

    delete this->_dbModel;
}

void LinksList::add(const Link2Go l2g)
{
    cout << "ADD" << endl;

    QSqlQuery a_query(QSqlDatabase::database());

    QString url = l2g.link();
    int time = l2g.interval();
    int done = l2g.status();

    QString insertString = "INSERT INTO links(url, time, status) "
            "VALUES ('%1', %2, %3);";
    QString str = insertString.arg(url).arg(time).arg(done);
    cout << str.toStdString() << endl;
    a_query.exec(str);

    this->_dbModel->select();
}

void LinksList::addAll(const Link2GoList l2g_list)
{
    for (unsigned int i = 0; i < l2g_list.size(); i++) {
        this->add(l2g_list.at(i));
    }
}

void LinksList::del(const LinkID link_ID)
{
    QSqlQuery d_query(QSqlDatabase::database());
    QString deleteString = "DELETE FROM links WHERE LinkID = %1";
    QString delete_str = deleteString.arg(link_ID);

    d_query.exec(delete_str);
}

// are there links to view?
const bool LinksList::canNext()
{
    QSqlQuery s_query(QSqlDatabase::database());
    QString selectString = "SELECT COUNT(url) FROM links WHERE status = %1";
    QString select_str = selectString.arg(link2go::ST_READY);

    s_query.exec(select_str);

    int count = 0;
    while (s_query.next()) {
        count = s_query.value(0).toInt();
    }

    if (count > 0) {
        return true;
    }
    return false;
}

//gimme next link
Link2Go LinksList::next()
{
    QSqlQuery s_query(QSqlDatabase::database());
    QString selectString = "SELECT * FROM links WHERE status = %1 LIMIT 1";
    QString select_str = selectString.arg(link2go::ST_READY);

    s_query.exec(select_str);

    QSqlRecord rec = s_query.record();
    Link2Go nextLink;
    while (s_query.next()) {
        int id = s_query.value(rec.indexOf("LinkID")).toInt();
        QString url = s_query.value(rec.indexOf("url")).toString();
        int time = s_query.value(rec.indexOf("time")).toInt();
        int done = s_query.value(rec.indexOf("status")).toInt();

        nextLink.setID(id);
        nextLink.setLink(url);
        nextLink.setInterval(time);
        nextLink.setStatus(done);
    }

    return nextLink;
}

//confirm link to view
void LinksList::ok(const LinkID linkID)
{
    this->updateStatus(linkID, link2go::ST_VIEW);
}

//mark link as viewed
void LinksList::done(const LinkID linkID)
{
    this->updateStatus(linkID, link2go::ST_DONE);
}

//ListModel* LinksList::model() const
//{
//    return this->_model;
//}

QSqlTableModel *LinksList::dbModel() const
{
    return this->_dbModel;
}

void LinksList::updateStatus(LinkID linkID, int status)
{
    QSqlQuery u_query(QSqlDatabase::database());
    QString updateString = "UPDATE links SET status = %1 WHERE LinkID = %2";
    QString update_str = updateString.arg(status).arg(linkID);

    u_query.exec(update_str);

    this->_dbModel->select();
}

//void LinksList::update()
//{
//    this->_model->update();
//}


