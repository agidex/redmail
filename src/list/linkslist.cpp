#include "linkslist.h"

LinksList::LinksList(QObject *parent) :
    QObject(parent)
{
    _linkIDcounter = 0;
    _lastReady = 0;

    this->_model = new ListModel(&this->_hash);
}

LinksList::~LinksList()
{
    delete this->_model;
}

void LinksList::add(const Link2Go l2g)
{
    _hash[_linkIDcounter] = l2g;
    _readyList[_linkIDcounter] = 1337;

    _linkIDcounter++;
    this->update();
}

void LinksList::addAll(const Link2GoList l2g_list)
{
    for (unsigned int i = 0; i < l2g_list.size(); i++) {
        this->add(l2g_list.at(i));
//        _linkIDcounter++;
//        _hash[_linkIDcounter] = l2g_list.at(i);
    }
    this->update();
}

void LinksList::del(const LinkID link_ID)
{
    _hash.remove(link_ID);
    this->update();
}

bool LinksList::canNext()
{
    if (_readyList.empty()) {
        return false;
    }
    if (_lastReady >= _readyList.size()) {
        _lastReady = 0;
        return false;
    }
    return true;
}

Link2Go LinksList::next(LinkID *linkID)
{
    cout << "NEXT" << endl;
    QList<LinkID> keys = _readyList.keys();


    LinkID link_id = keys.at(_lastReady);
    *linkID = link_id;

    _lastReady++;
    return _hash.value(link_id);
}

void LinksList::ok(LinkID linkID)
{
    _readyList.remove(linkID);
    _nowList[linkID] = 1337;
    _hash[linkID].setStatus(link2go::ST_VIEW);
    this->update();
}

void LinksList::done(LinkID linkID)
{
    _nowList.remove(linkID);
    _doneList.append(linkID);
    _hash[linkID].setStatus(link2go::ST_DONE);
    this->update();
}

ListModel* LinksList::model() const
{
    return this->_model;
}

void LinksList::update()
{
    this->_model->update();
}


