#include "redmail.h"
#include "ui_redmail.h"


#include <QtSql>
using namespace std;

#include <QHash>

RedMail::RedMail(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RedMail)
{
    ui->setupUi(this);
    this->bindButtons();

    this->linksList = new LinksList();
    ui->listTableView->setModel(this->linksList->dbModel());

    ui->listTableView->verticalHeader()->show();

//    ui->listTableView->setColumnHidden(0, true);

    ui->listTableView->resizeRowsToContents();
    ui->listTableView->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    ui->listTableView->resizeColumnToContents(0);
    ui->listTableView->resizeColumnToContents(2);
    ui->listTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listTableView->verticalHeader()->hide();

    this->linkBrowser = new LinkBrowser(ui->browserWidget, this->linksList);
}

RedMail::~RedMail()
{
    delete ui;

    delete this->linksList;
    delete this->linkBrowser;
}

void RedMail::bindButtons()
{
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(doitButtonHandler()));
    connect(ui->nextPushButton, SIGNAL(clicked()), this, SLOT(nextLink()));
    connect(ui->prevPushButton, SIGNAL(clicked()), this, SLOT(prevLink()));
//    fick dich ins Knee!
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(toogleAutoButtonHandler()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(addLinksButtonHandler()));
//    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(addLinksButtonHandler()));
}

void RedMail::doitButtonHandler()
{
    linksList->canNext();
    Link2Go nxt = linksList->next();
    cout << nxt.id() << "\t" << nxt.link().toStdString() << "\t" << nxt.interval() << endl;


//    QString dbPath = "e:\\PROG\\links.db";
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName(dbPath);
//    if (!db.open()) {
//        qDebug() << "Cant open database";
//    }

//    QSqlQuery db_query;
//    bool query_result;
//    QString str;

//    QString str_insert = "INSERT INTO links(url, time, done) VALUES ('%1', %2, %3)";

//    str = str_insert.arg("pikabu.ru").arg(5).arg(0);
//    query_result = db_query.exec(str);
//    str = str_insert.arg("habrahabr.ru").arg(17).arg(0);

//    QString str_select = "SELECT * FROM links";
//    query_result = db_query.exec(str_select);

//    if (!query_result) {
//        qDebug() << "Something go wrong";
//    }

//    QSqlRecord rec = db_query.record();
//    int id, time, done = 0;
//    QString url;
//    while (db_query.next()) {
//        id = db_query.value(rec.indexOf("LinkID")).toInt();
//        url = db_query.value(rec.indexOf("url")).toString();
//        time = db_query.value(rec.indexOf("time")).toInt();
//        done = db_query.value(rec.indexOf("done")).toInt();

//        cout << id << "\t"
//             << url.toStdString() << "\t"
//             << time << "\t"
//             << done << endl;
//    }


//    ui->webView->load(QUrl("http://google.com"));
//    this->linkBrowser->doit();
//    Link2Go link1;
//    link1.setLink("google.com");
//    link1.setInterval(10);
//    this->linksList->add(link1);
//    cout << linksList->size() << endl;


//    Link2Go link2;
//    link2.setLink("wikipedia.org");
//    link2.setInterval(5);
//    this->linksList->add(link2);
//    cout << linksList->size() << endl;


//    Link2Go link3;
//    link3.setLink("yahoo.com");
//    link3.setInterval(15);
//    this->linksList->add(link3);5
//    cout << linksList->size() << endl;

    //ui->listTableView->resizeRowsToContents();
}

void RedMail::addLinksButtonHandler()
{
    Link2Go l1 = Link2Go("http://www.google.com", 9);
    this->linksList->add(l1);

    Link2Go l2 = Link2Go("http://stackoverflow.com", 7);
    this->linksList->add(l2);

    Link2Go l3 = Link2Go("lurkmore.to", 5);
    this->linksList->add(l3);

    ui->listTableView->resizeRowsToContents();
}

void RedMail::toogleAutoButtonHandler()
{
    bool status = this->linkBrowser->autoView();
    status = !status;
    if (status) {
        ui->pushButton_2->setText("Auto: ON");
    }
    else {
        ui->pushButton_2->setText("Auto: OFF");
    }
    this->linkBrowser->setAuto(status);
}

void RedMail::nextLink()
{
    int size = this->linkBrowser->clusterSize();
    size++;
    this->linkBrowser->resizeCluster(size);
}

void RedMail::prevLink()
{
    int size = this->linkBrowser->clusterSize();
    size--;
    this->linkBrowser->resizeCluster(size);
}
