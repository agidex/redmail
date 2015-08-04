#include "email.h"

Email::Email()
{
}

const std::string Email::name() const
{
    return this->name_;
}

void Email::setName(const std::string name)
{
    this->name_ = name;
}

const std::string Email::host() const
{
    return this->host_;
}

void Email::setHost(const std::string host)
{
    this->host_ = host;
}

const int Email::port() const
{
    return this->port_;
}

void Email::setPort(const int port)
{
    this->port_ = port;
}

const std::string Email::username() const
{
    return this->username_;
}

void Email::setUsername(const std::string username)
{
    this->username_ = username;
}

const std::string Email::password() const
{
    return this->pass_;
}

void Email::setPassword(const std::string password)
{
    this->pass_ = password;
}
