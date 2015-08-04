#include "gridwidget.h"

GridWidget::GridWidget(QWidget *parent) :
    QWidget(parent)
{
}

GridWidget::~GridWidget()
{
}

void GridWidget::resizeEvent(QResizeEvent *event)
{
    emit onResize();
}


