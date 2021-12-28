#ifndef BTREE_H
#define BTREE_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QTextStream>

namespace Ui { class btree; }

struct BTreeNodeData {
    int invent_number;
    QString name;
    QString type;
    int overwork_time;
    int work_time;
    BTreeNodeData() : invent_number(0){};
};
class BTreeNode {
    BTreeNodeData* keys;
    int n;

    BTreeNode** C;
    int t;
    bool leaf;
public:
    BTreeNode(int t1, bool leaf1);

    void insertNonFull(BTreeNodeData k);
    void splitChild(int i, BTreeNode* y);
    BTreeNodeData search(int k);
    BTreeNodeData search_max(int k);

    friend class btree;
};

class btree : public QDialog {
    Q_OBJECT

public:
    explicit btree(QWidget *parent = nullptr);
    ~btree();

    void set_t(int _t);
    void traverse();
    BTreeNodeData search(int k);
    void insert(BTreeNodeData k);

private slots:
    void on_Input_From_File_clicked();
    void on_Add_Button_clicked();
    void on_SearchButton_clicked();

    void onWorkbenchChanged(BTreeNodeData* new_bench);

    void on_PopularButton_clicked();

private:
    Ui::btree *ui;

    QString path_in_b_tree;
    BTreeNode* root;
    int t;
    int max;

    void addToTable(BTreeNodeData new_node);
};

#endif // BTREE_H
