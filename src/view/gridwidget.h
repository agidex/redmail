#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>
#include <cmath>


class GridWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GridWidget(QWidget *parent = 0);
    ~GridWidget();
    void resizeEvent(QResizeEvent *event);

    void addWidget(QWidget *widget, unsigned int row, unsigned int col);
    void clearAll();

    void getGridSize(unsigned int *rows, unsigned int *cols) const;

private:
    int unsigned maxRows;
    int unsigned maxCols;

    QList<QWidget*> *widgetList;
    QList<int> *rowsList;
    QList<int> *colsList;
};

#endif // GRIDWIDGET_H
