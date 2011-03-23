#ifndef ASSIGNBED_H
#define ASSIGNBED_H

#include <QMainWindow>

namespace Ui {
    class AssignBed;
}

class AssignBed : public QMainWindow
{
    Q_OBJECT

public:
    explicit AssignBed(QWidget *parent = 0);
    ~AssignBed();

private slots:
    void clickedOK();

private:
    Ui::AssignBed *ui;
};

#endif // ASSIGNBED_H
