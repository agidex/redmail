#ifndef REDMAIL_H
#define REDMAIL_H

#include <QMainWindow>

//------GRID TEST--------
#include <QPushButton>
#include <QGridLayout>
const int NBx = 3;
const int NBy = 3;
//-----------------------

#include "list/linkslist.h"
#include "view/linkbrowser.h"

#include <iostream>

using namespace std;

namespace Ui {
    class RedMail;
}

class RedMail : public QMainWindow
{
    Q_OBJECT

public:
    explicit RedMail(QWidget *parent = 0);
    ~RedMail();
public slots:
    void doitButtonHandler();

    void nextLink();
    void prevLink();

private:
    void bindButtons();

    Ui::RedMail *ui;

    LinksList *linksList;
    LinkBrowser *linkBrowser;
};

#endif // REDMAIL_H
