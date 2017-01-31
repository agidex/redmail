#ifndef VIEWCELL_H
#define VIEWCELL_H

#include <QWidget>
#include <QTimer>

#include <QVBoxLayout>
#include <QWebView>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QLabel>

#include "items/link2go.h"

typedef unsigned int CellID;

class ViewCell : public QWidget
{
    Q_OBJECT
public:
    explicit ViewCell(QWidget *parent = 0, const CellID cellID = 0);
    ~ViewCell();

    bool isDone() const;

    void view(const Link2Go l2g, const LinkID linkID);
signals:
    void viewDone(const CellID cellID, const LinkID linkID);

public slots:
    void loadFinished();
    void viewTimeout();
    void oneSec();

private:
    void makeUI();
    void updateTimeout();

    QUrl checkUrl(QString url);

    CellID _cellID;
    bool _done;
    LinkID _linkID;

    int _interval;
    int _intervalDec;

    QWebView *_browser;
    QVBoxLayout *_vbox;
    QHBoxLayout *_hbox;
    QProgressBar *_viewProgress;
    QLabel *_statLabel;
    QLabel *_urlLabel;

    QTimer *_viewTimer;
    QTimer *_oneSecTimer;
};

#endif // VIEWCELL_H
