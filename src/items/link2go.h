#ifndef LINK2GO_H
#define LINK2GO_H

#include <string>
#include <vector>

#include <iostream>
using namespace std;

namespace link2go {
    const int ST_READY = 0;
    const int ST_VIEW = 1;
    const int ST_DONE = 2;
}

class Link2Go
{
public:
    Link2Go();
    Link2Go(const std::string link, const int interval);

    ~Link2Go();

    const std::string link() const;
    void setLink(const std::string link);

    const int interval() const;
    void setInterval(const int interval);

    const int status() const;
    void setStatus(const int status);

//    const int sponsor() const;
//    void setSponsor(const int sposorID);
private:
    void init(const std::string link, const int interval);

    std::string link_;
    int interval_;
    int status_;

//    int sponsor_;
};

typedef std::vector<Link2Go> Link2GoList;

#endif // LINK2GO_H
