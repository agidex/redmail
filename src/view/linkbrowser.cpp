#include "linkbrowser.h"

LinkBrowser::LinkBrowser(GridWidget *widget, QObject *parent) :
    QObject(parent)
{
    this->gridWidget = widget;

    this->resizeCluster(CLUSTER_SIZE_INITIAL);
}

LinkBrowser::~LinkBrowser()
{
}

void LinkBrowser::genRowsCols(int count, int *rows, int *cols)
{
    int rows_ = 0;
    int cols_ = 0;

    while (rows_ * cols_ < count) {
        cols_++;
        if (rows_ * cols_ >= count) {
            break;
        }
        rows_++;
    }
    *rows = rows_;
    *cols = cols_;
}

void LinkBrowser::resizeCluster(const int size)
{
    this->gridWidget->clearAll();

    for (int i = 0; i < cluster.size(); i++) {
        delete cluster[i];
    }
    cluster.clear();

    int rows, cols;
    this->genRowsCols(size, &rows, &cols);

    int row = 0;
    int col = 0;
    for (int i = 0; i < size; i++) {

        // testing lol
//        ViewCell *b = new ViewCell(QString::number(i+1), this->gridWidget);
        int cellID = i;
        ViewCell *b = new ViewCell(this->gridWidget, cellID);
        connect(b, SIGNAL(viewDone(int,int)), this, SLOT(cellDone(int, int)));

        cluster.append(b);
        this->gridWidget->addWidget(b, row, col);

        col++;
        if (col == cols) {
            col = 0;
            row++;
        }
    }
}

const int LinkBrowser::clusterSize() const
{
    return cluster.size();
}

void LinkBrowser::doit()
{
    Link2Go l2g;
    l2g.setLink("http://www.google.com");
    l2g.setInterval(15);
    l2g.setID(9009);

    cluster[1]->view(l2g);

    Link2Go l2g_;
    l2g_.setLink("http://www.dobrochan.com");
    l2g_.setInterval(10);

    cluster[4]->view(l2g_, 5151);
}

void LinkBrowser::setAuto(bool status)
{
    this->autoView = status;
    if (status) {
        this->forceStart();
    }
}

void LinkBrowser::cellDone(int cellID, int linkID)
{
    cout << "DONE: CELL_ID: " << cellID << " LINK_ID: "  << linkID << endl;

    if (this->autoView) {
        this->cluster[cellID]->view();
    }
}

void LinkBrowser::forceStart()
{
    for (int i = 0; i < clusterSize(); i++) {
        if (cluster[i]->isDone()) {
            cellDone(i, -1);
        }
    }
}








