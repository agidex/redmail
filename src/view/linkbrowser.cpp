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
        QPushButton *b = new QPushButton(QString::number(i+1), this->gridWidget);
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







