#ifndef VIEWWAITINGLIST_H
#define VIEWWAITINGLIST_H

#include <QMainWindow>

namespace Ui {
    class ViewWaitingList;
}

class ViewWaitingList : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewWaitingList(QWidget *parent = 0);
    ~ViewWaitingList();

private:
    Ui::ViewWaitingList *ui;
};

#endif // VIEWWAITINGLIST_H



