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

class ViewCell : public QWidget
{
    Q_OBJECT
public:
    explicit ViewCell(QWidget *parent = 0, int cellID = -1);
    ~ViewCell();

    void setID(int id);
    bool isDone() const;

    void view(Link2Go l2g, int linkID);
signals:
    void viewDone(int cellID, int linkID);

public slots:
    void loadFinished();
    void viewTimeout();
    void oneSec();

private:
    void makeUI();
    void updateTimeout();

    int cellID_;
    bool done_;
    int linkID_;

    int interval_;
    int intervalDec_;

    QWebView *browser;
    QVBoxLayout *vbox;
    QHBoxLayout *hbox;
    QProgressBar *viewProgress;
    QLabel *statLabel;
    QLabel *urlLabel;

    QTimer *viewTimer;
    QTimer *oneSecTimer;
};

#endif // VIEWCELL_H
