#ifndef EMAIL_H
#define EMAIL_H

#include <string>
#include <vector>

class Email
{
public:
    Email();

    const std::string name() const;
    void setName(const std::string name);

    const std::string host() const;
    void setHost(const std::string host);

    const int port() const;
    void setPort(const int port);

    const std::string username() const;
    void setUsername(const std::string username);

    const std::string password() const;
    void setPassword(const std::string password);


private:
    std::string name_;
    std::string host_;
    int port_;
    std::string username_;
    std::string pass_;
};

typedef std::vector<Email> EmailList;

#endif // EMAIL_H
