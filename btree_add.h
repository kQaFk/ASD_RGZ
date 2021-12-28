#ifndef BTREE_ADD_H
#define BTREE_ADD_H

#include <QDialog>
#include "btree.h"

namespace Ui { class btree_add; }

class btree_add : public QDialog {
    Q_OBJECT

public:
    explicit btree_add(QWidget *parent = nullptr);
    ~btree_add();
    void set_human(BTreeNodeData* human);

signals:
    void workbenchChanged(BTreeNodeData* new_human);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::btree_add *ui;
    BTreeNodeData *new_human;
};


#endif // BTREE_ADD_H
