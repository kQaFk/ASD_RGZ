#ifndef HEAPSORT_ADD_H
#define HEAPSORT_ADD_H

#include "heapsort.h"
#include <QDialog>
#include <QString>

namespace Ui { class heapsort_add; }

class heapsort_add : public QDialog {
    Q_OBJECT

public:
    explicit heapsort_add(QWidget *parent = nullptr);
    ~heapsort_add();

    void set_item(TheList::elem*);

signals:
    void itemChanged(TheList::elem* item);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::heapsort_add *ui;

    TheList::elem* new_item;
};
#endif // HEAPSORT_ADD_H
