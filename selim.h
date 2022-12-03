#ifndef SELIM_H
#define SELIM_H
#include <QDialog>

namespace Ui {
class selim;
}

class selim : public selim
{
    Q_OBJECT

public:
    explicit selim(QWidget *parent = nullptr);
    ~selim();
    void stats();

private:
    Ui::selim *ui;
};


#endif // SELIM_H
