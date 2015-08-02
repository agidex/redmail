#include "redmail.h"
#include "ui_redmail.h"

RedMail::RedMail(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RedMail)
{
    ui->setupUi(this);
    this->bindButtons();

    this->linksList = new LinksList();
    ui->listTableView->setModel(this->linksList->model());

    ui->listTableView->verticalHeader()->show();

    ui->listTableView->resizeRowsToContents();
    ui->listTableView->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->listTableView->resizeColumnToContents(1);
    ui->listTableView->resizeColumnToContents(2);

    this->linkBrowser = new LinkBrowser(ui->browserWidget);
//    this->linkBrowser_->setWidget(ui->browserWidget);
}

RedMail::~RedMail()
{
    delete ui;

    delete this->linksList;
    delete this->linkBrowser;

//    for (int i = 0; i < NBx*NBy; i++) {
//        delete this->buttons[i];
//    }

//    delete this->gl_;
}

void RedMail::bindButtons()
{
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(doitButtonHandler()));
    connect(ui->nextPushButton, SIGNAL(clicked()), this, SLOT(nextLink()));
    connect(ui->prevPushButton, SIGNAL(clicked()), this, SLOT(prevLink()));
//    fick dich ins Knee!
}

void RedMail::doitButtonHandler()
{
    Link2Go link1;
    link1.setLink("google.com");
    link1.setInterval(10);
    this->linksList->add(link1);
    cout << linksList->size() << endl;


    Link2Go link2;
    link2.setLink("wikipedia.org");
    link2.setInterval(5);
    this->linksList->add(link2);
    cout << linksList->size() << endl;


    Link2Go link3;
    link3.setLink("yahoo.com");
    link3.setInterval(15);
    this->linksList->add(link3);
    cout << linksList->size() << endl;

    ui->listTableView->resizeRowsToContents();
}

void RedMail::nextLink()
{
    cout << "next link" << endl;
    this->linkBrowser->resizeCluster(2,2);
}

void RedMail::prevLink()
{
    cout << "prev link" << endl;
    this->linkBrowser->resizeCluster(3,3);
}