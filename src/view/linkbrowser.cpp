#include "linkbrowser.h"

LinkBrowser::LinkBrowser(GridWidget *widget, QObject *parent) :
    QObject(parent)
{
    this->widget = widget;
    connect(this->widget, SIGNAL(onResize(int,int)), this, SLOT(onWidgetResize(int,int)));

    this->resizeCluster(2, 3);
}

LinkBrowser::~LinkBrowser()
{
}

void LinkBrowser::resizeCluster(const int rows, const int cols)
{
    this->rows = rows;
    this->cols = cols;

    for (int i = 0; i < this->blist.size(); i++) {
        delete this->blist[i];
    }
    this->blist.clear();

    int i = 0;
    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++) {
            QPushButton *b = new QPushButton(this->widget);
            blist.append(b);
            blist[i]->setText(QString::number(i+1));
            blist[i]->show();
            i++;
        }
    }
    onWidgetResize(0,0);
}

void LinkBrowser::onWidgetResize(int w, int h)
{
    int i = 0;
    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++) {
            setGeo(this->blist[i], r, c);
            i++;
        }
    }
}

void LinkBrowser::setGeo(QPushButton *button, int row, int col)
{
    int W = this->widget->width();
    int H = this->widget->height();

    int width = floor(W / this->cols);
    int heigth = floor(H / this->rows);

    int x = col * width;
    int y = row * heigth;

    button->setGeometry(x, y, width, heigth);
}






