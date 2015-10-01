#include "linkbrowser.h"

LinkBrowser::LinkBrowser(GridWidget *widget, LinksList *list, QObject *parent) :
    QObject(parent)
{
    this->_gridWidget = widget;
    this->_linksList = list;

    this->resizeCluster(CLUSTER_SIZE_INITIAL);

    this->_autoView = false;
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
    this->_gridWidget->clearAll();

    for (int i = 0; i < _cluster.size(); i++) {
        delete _cluster[i];
    }
    _cluster.clear();

    int rows, cols;
    this->genRowsCols(size, &rows, &cols);

    int row = 0;
    int col = 0;
    for (int i = 0; i < size; i++) {

        // testing lol
//        ViewCell *b = new ViewCell(QString::number(i+1), this->gridWidget);
        int cellID = i;
        ViewCell *b = new ViewCell(this->_gridWidget, cellID);

        connect(b, SIGNAL(viewDone(CellID, LinkID)), this, SLOT(cellDone(CellID, LinkID)));
        _cluster.append(b);

        this->_gridWidget->addWidget(b, row, col);

        col++;
        if (col == cols) {
            col = 0;
            row++;
        }
    }
}

const int LinkBrowser::clusterSize() const
{
    return _cluster.size();
}

void LinkBrowser::setAuto(const bool status)
{
    this->_autoView = status;
    if (status) {
        this->forceStart();
    }
}

bool LinkBrowser::autoView() const
{
    return this->_autoView;
}

void LinkBrowser::cellDone(CellID cellID, LinkID linkID)
{
    cout << "DONE: CELL_ID: " << cellID << " LINK_ID: "  << linkID << endl;

    if (linkID != LINK_ID_UNDEF) {
        this->_linksList->done(linkID);
    }
    if (this->_autoView) {
        viewNewLink(cellID);
    }
}

void LinkBrowser::forceStart()
{
    for (int i = 0; i < clusterSize(); i++) {
        if (_cluster[i]->isDone()) {
            cellDone(i, LINK_ID_UNDEF);
        }
    }
}

bool LinkBrowser::checkConditions(Link2Go l2g)
{
    bool conditions = true;

    return conditions;
}

void LinkBrowser::viewNewLink(CellID cellID)
{
    bool chozen = false;

    while(_linksList->canNext() and !chozen) {
//        cout << "CAN NEXT" << endl;
        LinkID linkID;
        Link2Go l2g = _linksList->next(&linkID);
        if (this->checkConditions(l2g)) {
            chozen = true;
            this->_linksList->ok(linkID);
            _cluster[cellID]->view(l2g, linkID);
            cout << "VIEW: CELL_ID: " << cellID << " LINK_ID: "  << linkID << endl;
        }
    }
}








