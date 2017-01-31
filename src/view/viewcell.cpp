#include "viewcell.h"

#include <iostream>
using namespace std;

ViewCell::ViewCell(QWidget *parent, const CellID cellID) :
    QWidget(parent)
{
    this->_cellID = cellID;
    this->_done = true;

    this->makeUI();

    connect(this->_browser, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished()));

    this->_viewTimer = new QTimer(this);
    connect(this->_viewTimer, SIGNAL(timeout()), this, SLOT(viewTimeout()));

    this->_oneSecTimer = new QTimer(this);
    this->_oneSecTimer->setInterval(1000);
    this->_oneSecTimer->setSingleShot(false);

    connect(this->_oneSecTimer, SIGNAL(timeout()), this, SLOT(oneSec()));
}

ViewCell::~ViewCell()
{
    delete this->_browser;
    delete this->_viewProgress;
    delete this->_statLabel;
    delete this->_urlLabel;
    delete this->_hbox;
    delete this->_vbox;
}

bool ViewCell::isDone() const
{
    return this->_done;
}

void ViewCell::makeUI()
{
    // ui
    this->_vbox = new QVBoxLayout(this);

    this->_browser = new QWebView(this);
    this->_browser->setUrl(QUrl("about:blank"));

    this->_vbox->addWidget(this->_browser);

    this->_hbox = new QHBoxLayout(this);

    this->_viewProgress = new QProgressBar(this);
    this->_hbox->addWidget(this->_viewProgress);

    this->_statLabel = new QLabel(this);
    this->_hbox->addWidget(this->_statLabel);

    this->_vbox->addLayout(this->_hbox);

    this->_urlLabel = new QLabel(this);
    this->_vbox->addWidget(this->_urlLabel);

    this->_viewProgress->setMinimum(0);
    this->_viewProgress->setValue(0);
    this->_statLabel->setText("[0/0]");
    this->_urlLabel->setText("http://www.EXAMPLE.com");
}

void ViewCell::updateTimeout()
{
    this->_viewProgress->setValue(this->_interval - this->_intervalDec);
    QString statText = "[" + QString::number(this->_intervalDec) + "/" +
            QString::number(this->_interval) + "]";
    this->_statLabel->setText(statText);
}

//setting up proper header http://www.example.com or https://www.example.com
QUrl ViewCell::checkUrl(QString url)
{
    bool https = false;
    if (url.startsWith("http://")) {
        url.remove(0, 7);
    }
    if (url.startsWith("https://")) {
        url.remove(0,8);
        https = true;
    }
    if (url.startsWith("www.")) {
        url.remove(0, 4);
    }
    if (https) {
        return QUrl("https://www."+url);
    }
    return QUrl("http://www."+url);
}

void ViewCell::view(const Link2Go l2g, const LinkID linkID)
{
    this->_done = false;

    this->_linkID = linkID;

    this->_viewTimer->setInterval(l2g.interval() * 1000);
    this->_viewTimer->setSingleShot(true);

    this->_interval = l2g.interval();
    this->_intervalDec = this->_interval;

    this->updateTimeout();

    this->_viewProgress->setMaximum(this->_interval);
    this->_urlLabel->setText(l2g.link());

    this->_browser->load(checkUrl(l2g.link()));
}

void ViewCell::loadFinished()
{
    cout << "LOAD FINISHED" << endl;

    this->_viewTimer->start();
    this->_oneSecTimer->start();
}

void ViewCell::viewTimeout()
{
    cout << "TIMEOUT" << endl;

    this->_intervalDec = 0;
    this->updateTimeout();

    this->_viewTimer->stop();
    this->_oneSecTimer->stop();
    this->_done = true;

    emit viewDone(this->_cellID, this->_linkID);
}

void ViewCell::oneSec()
{
//    cout << "SECOND" << endl;

    this->_intervalDec--;

    this->updateTimeout();
}
