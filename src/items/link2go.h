#ifndef LINK2GO_H
#define LINK2GO_H

#include <string>
#include <vector>

#include <QHash>

#include <iostream>
using namespace std;

typedef int LinkID;

namespace link2go {
    const int ST_READY = 0;
    const int ST_VIEW = 1;
    const int ST_DONE = 2;
}

class Link2Go
{
public:
    Link2Go();
    Link2Go(const QString link, const int interval);

    ~Link2Go();

    const QString link() const;
    void setLink(QString link);

    const int interval() const;
    void setInterval(const int interval);

    const int status() const;
    void setStatus(const int status);

//    const int id() const;
//    void setID(int id);

//    const int sponsor() const;
//    void setSponsor(const int sposorID);
private:
    void init(const QString link, const int interval);

    QString link_;
    int interval_;
    int status_;

//    int linkID_;

//    int sponsor_;
};

typedef std::vector<Link2Go> Link2GoList;
typedef QHash<LinkID, Link2Go> Link2GoHash;

#endif // LINK2GO_H
