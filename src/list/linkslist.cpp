#include "linkslist.h"

LinksList::LinksList(QObject *parent) :
    QObject(parent)
{
    this->model_ = new ListModel(&this->list_);
}

LinksList::~LinksList()
{
    delete this->model_;
}

void LinksList::add(const Link2Go link, const int pos)
{
    this->list_.insert(this->list_.end(), link);
    this->update();
}

void LinksList::addAll(const Link2GoList list)
{
    //    add all
    this->update();
}

void LinksList::del(const int pos)
{
    this->list_.erase(this->list_.begin()+pos);
    this->update();
}

void LinksList::delAll(const int posStart, const int posFinish)
{
}

const int LinksList::size() const
{
    return this->list_.size();
}

const Link2GoList LinksList::list()
{
    return this->list_;
}

ListModel* LinksList::model() const
{
    return this->model_;
}

void LinksList::update()
{
    this->model_->update();
}


