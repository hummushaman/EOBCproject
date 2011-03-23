#ifndef ADDBED_H
#define ADDBED_H

#include <QMainWindow>
#include <welcome.h>

namespace Ui {
    class AddBed;
}

class AddBed : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddBed(QWidget *parent = 0);
    ~AddBed();
private slots:
    void clickedOK();

private:
    Ui::AddBed *ui;
};

#endif // ADDBED_H
