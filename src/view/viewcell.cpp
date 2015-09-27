#include "viewcell.h"

#include <iostream>
using namespace std;

ViewCell::ViewCell(QWidget *parent, int cellID) :
    QWidget(parent)
{
    this->cellID_ = cellID;
    this->done_ = false;

    this->makeUI();

    connect(this->browser, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished()));

    this->viewTimer = new QTimer(this);
    connect(this->viewTimer, SIGNAL(timeout()), this, SLOT(viewTimeout()));

    this->oneSecTimer = new QTimer(this);
    this->oneSecTimer->setInterval(1000);
    this->oneSecTimer->setSingleShot(false);

    connect(this->oneSecTimer, SIGNAL(timeout()), this, SLOT(oneSec()));
}

ViewCell::~ViewCell()
{
    delete this->browser;
    delete this->viewProgress;
    delete this->statLabel;
    delete this->urlLabel;
    delete this->hbox;
    delete this->vbox;
}

void ViewCell::setID(int id)
{
    this->cellID_ = id;
}

bool ViewCell::isDone() const
{
    return this->done_;
}

void ViewCell::makeUI()
{
    // ui
    this->vbox = new QVBoxLayout(this);

    this->browser = new QWebView(this);
    this->browser->setUrl(QUrl("about:blank"));

    this->vbox->addWidget(this->browser);

    this->hbox = new QHBoxLayout(this);

    this->viewProgress = new QProgressBar(this);
    this->hbox->addWidget(this->viewProgress);

    this->statLabel = new QLabel(this);
    this->hbox->addWidget(this->statLabel);

    this->vbox->addLayout(this->hbox);

    this->urlLabel = new QLabel(this);
    this->vbox->addWidget(this->urlLabel);

    this->viewProgress->setMinimum(0);
    this->viewProgress->setValue(0);
    this->statLabel->setText("[0/0]");
    this->urlLabel->setText("http://www.google.com");
}

void ViewCell::updateTimeout()
{
    this->viewProgress->setValue(this->interval_ - this->intervalDec_);
    QString statText = "[" + QString::number(this->intervalDec_) + "/" +
            QString::number(this->interval_) + "]";
    this->statLabel->setText(statText);
}

void ViewCell::view(Link2Go l2g, int linkID)
{
    this->done_ = false;

    this->linkID_ = linkID;

    this->viewTimer->setInterval(l2g.interval() * 1000);
    this->viewTimer->setSingleShot(true);

    this->interval_ = l2g.interval();
    this->intervalDec_ = this->interval_;

    this->updateTimeout();

    this->viewProgress->setMaximum(this->interval_);
    this->urlLabel->setText(QString::fromStdString(l2g.link()));

    this->browser->load(QUrl(QString::fromStdString(l2g.link())));
}

void ViewCell::loadFinished()
{
    cout << "LOAD FINISHED" << endl;

    this->viewTimer->start();
    this->oneSecTimer->start();
}

void ViewCell::viewTimeout()
{
    cout << "TIMEOUT" << endl;

    this->intervalDec_ = 0;
    this->updateTimeout();

    this->viewTimer->stop();
    this->oneSecTimer->stop();
    this->done_ = true;

    emit viewDone(this->cellID_, this->linkID_);
}

void ViewCell::oneSec()
{
    cout << "SECOND" << endl;

    this->intervalDec_--;

    this->updateTimeout();
}
