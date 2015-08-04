#include "linkbrowser.h"

LinkBrowser::LinkBrowser(GridWidget *widget, QObject *parent) :
    QObject(parent)
{
    this->widget = widget;
    connect(this->widget, SIGNAL(onResize()), this, SLOT(onWidgetResize()));

    this->resizeCluster(2, 3);
}

LinkBrowser::~LinkBrowser()
{
}

void LinkBrowser::resizeCluster(unsigned const int rows, unsigned const int cols)
{
    if (rows < 1) {
        this->rows = 1;
    }
    else {
        this->rows = rows;
    }

    if (cols < 1) {
        this->cols = 1;
    }
    else {
        this->cols = cols;
    }

    for (int i = 0; i < this->cluster.size(); i++) {
        delete this->cluster[i];
    }
    this->cluster.clear();

    int i = 0;
    for (unsigned int r = 0; r < this->rows; r++) {
        for (unsigned int c = 0; c < this->cols; c++) {

            QPushButton *b = new QPushButton(this->widget);
            cluster.append(b);

            cluster[i]->setText(QString::number(i+1));
            cluster[i]->show();
            i++;
        }
    }

    onWidgetResize();
}

void LinkBrowser::onWidgetResize()
{
    unsigned int width = floor(this->widget->width() / this->cols);
    unsigned int heigth = floor(this->widget->height() / this->rows);

    unsigned int row = 0;
    unsigned int col = 0;
    for (int i = 0; i < cluster.size(); i++) {
        int x = col * width;
        int y = row * heigth;

        this->cluster[i]->setGeometry(x, y, width, heigth);

        col++;
        if (col == this->cols) {
            col = 0;
            row++;
        }
    }
}

void LinkBrowser::clusterSize(unsigned int *rows, unsigned int *cols) const
{
    *rows = this->rows;
    *cols = this->cols;
}







