#include "link2go.h"

Link2Go::Link2Go()
{
    this->init("", -1);
}

Link2Go::Link2Go(const QString link, const int interval)
{
    this->init(link, interval);
}

Link2Go::~Link2Go()
{
}

const QString Link2Go::link()const
{
    return this->link_;
}

void Link2Go::setLink(const QString link)
{
    this->link_ = link;
}

const int Link2Go::interval() const
{
    return this->interval_;
}

void Link2Go::setInterval(const int interval)
{
    this->interval_ = interval;
}

const int Link2Go::status()const
{
    return this->status_;
}

void Link2Go::setStatus(const int status)
{
    this->status_ = status;
}

const int Link2Go::id() const
{
    return this->linkID_;
}

void Link2Go::setID(int id)
{
    this->linkID_ = id;
}

//const int Link2Go::id() const
//{
//    return this->linkID_;
//}

//void Link2Go::setID(int id)
//{
//    this->linkID_ = id;
//}

void Link2Go::init(const QString link, const int interval)
{
    this->setLink(link);
    this->setInterval(interval);

    this->setStatus(link2go::ST_READY);
}

