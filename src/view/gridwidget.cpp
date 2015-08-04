#include "gridwidget.h"

GridWidget::GridWidget(QWidget *parent) :
    QWidget(parent)
{
    maxRows = 1;
    maxCols = 1;

    widgetList = new QList<QWidget*>();
    rowsList = new QList<int>();
    colsList = new QList<int>();
}

GridWidget::~GridWidget()
{
    delete widgetList;
    delete rowsList;
    delete colsList;
}

void GridWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    unsigned int width = floor(this->width() / maxCols);
    unsigned int heigth = floor(this->height() / maxRows);

    for (int i = 0; i < widgetList->size(); i++) {

        unsigned int x = colsList->at(i) * width;
        unsigned int y = rowsList->at(i) * heigth;

        widgetList->at(i)->setGeometry(x, y, width, heigth);
    }
}

void GridWidget::getGridSize(unsigned int *rows, unsigned int *cols) const
{
    *rows = maxRows;
    *cols = maxCols;
}

void GridWidget::addWidget(QWidget *widget, unsigned int row, unsigned int col)
{
    widgetList->append(widget);
    widget->show();

    rowsList->append(row);
    if (row+1 > maxRows) {
        maxRows = row+1;
    }

    colsList->append(col);
    if (col+1 > maxCols) {
        maxCols = col+1;
    }
    resizeEvent(0);
}

void GridWidget::clearAll()
{
    maxRows = 1;
    maxCols = 1;

    for (int i = 0; i < widgetList->size(); i++) {
        widgetList->at(i)->hide();
    }

    widgetList->clear();
    rowsList->clear();
    colsList->clear();

    resizeEvent(0);
}


