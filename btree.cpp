#include "btree.h"
#include "ui_btree.h"
#include "btree_add.h"
#include <QDir>
BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    keys = new BTreeNodeData[2 * t - 1]();
    C = new BTreeNode* [2 * t];

    n = 0;
}
void BTreeNode::insertNonFull(BTreeNodeData k) {
    int i = n - 1;

    if (leaf == true) {
        while (i >= 0 && keys[i].invent_number > k.invent_number) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        n = n + 1;
    }
    else
    {
        while (i >= 0 && keys[i].invent_number > k.invent_number)
            i--;

        if (C[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1].invent_number < k.invent_number)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}
void BTreeNode::splitChild(int i, BTreeNode* y)
{
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];

    n = n + 1;
}
BTreeNodeData BTreeNode::search(int k)
{
    int i = 0;
    while (i < n && k > keys[i].invent_number)
        i++;

    if (keys[i].invent_number == k)
        return keys[i];

    if (leaf == true) {
        BTreeNodeData garbage;
        return garbage;
    }

    return C[i]->search(k);
}

BTreeNodeData BTreeNode::search_max(int k)
{
    int i = 0;
    while (i < n && k > keys[i].work_time)
        i++;

    if (keys[i].work_time == k)
        return keys[i];

    if (leaf == true) {
        BTreeNodeData garbage;
        return garbage;
    }

    return C[i]->search(k);
}

btree::btree(QWidget *parent) : QDialog(parent), ui(new Ui::btree) {
    ui->setupUi(this);

    path_in_b_tree = "\\btree_input.txt";
    root = NULL;
    set_t(3);
}
btree::~btree() {
    delete ui;
}

void btree::set_t(int _t) { t = _t; }
BTreeNodeData btree::search(int k) { return root->search(k); }

void btree::insert(BTreeNodeData k) {
    if (root == NULL) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else {
        if (root->n == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);

            s->C[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0].invent_number < k.invent_number)
                i++;
            s->C[i]->insertNonFull(k);

            root = s;
        }
        else
            root->insertNonFull(k);
    }
}

void btree::addToTable(BTreeNodeData new_node){
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

    QTableWidgetItem *newItem;
    newItem = new QTableWidgetItem();
    newItem->setText(QString::number(new_node.invent_number));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(new_node.name);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(new_node.type);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(QString::number(new_node.overwork_time));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(QString::number(new_node.work_time));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, newItem);

}

void btree::on_Input_From_File_clicked() {
    QFile file( QDir::toNativeSeparators(QApplication::applicationDirPath()) + path_in_b_tree);
    int temp_max = 0;
    if(!file.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file.open(QIODevice::ReadWrite)){
        qCritical() << file.errorString();
        return;
    }
    QTextStream fin(&file);

    while(!fin.atEnd()) {
        BTreeNodeData new_node;
        new_node.name = fin.readLine();
        new_node.type = fin.readLine();
        new_node.invent_number = fin.readLine().toInt();
        new_node.work_time = fin.readLine().toInt();
        new_node.overwork_time = fin.readLine().toInt();
        if(temp_max <= new_node.work_time) temp_max = new_node.work_time;
        insert(new_node);
        addToTable(new_node);
    }
    max = temp_max;
    file.close();

}
void btree::on_Add_Button_clicked() {
    btree_add *window = new btree_add;
    window->set_human(new BTreeNodeData);
    connect(window, SIGNAL(workbenchChanged(BTreeNodeData*)), this, SLOT(onWorkbenchChanged(BTreeNodeData*)));
    window->show();
}
void btree::on_SearchButton_clicked() {
    int search = ui->editSearch->text().toInt();
    BTreeNodeData search_key = root->search(search);

    QString result = "Имя: " + search_key.name
            + "\nТип: " + search_key.type
            + "\nВремя работы: " + QString::number(search_key.work_time)
            + "\nВремя переработки: " + QString::number(search_key.overwork_time);
    QMessageBox::about(this, "Искомый верстак", result);
}

void btree::onWorkbenchChanged(BTreeNodeData* new_bench){
    BTreeNodeData tmp;
    tmp.invent_number = new_bench->invent_number;
    tmp.name = new_bench->name;
    tmp.type = new_bench->type;
    tmp.overwork_time = new_bench->overwork_time;
    tmp.work_time = new_bench->work_time;
    insert(tmp);
    addToTable(tmp);
}

void btree::on_PopularButton_clicked() {
    int search = max;
    BTreeNodeData search_key = root->search_max(search);

    QString result = "Имя: " + search_key.name
            + "\nТип: " + search_key.type
            + "\nВремя работы: " + QString::number(search_key.work_time)
            + "\nВремя переработки: " + QString::number(search_key.overwork_time);
    QMessageBox::about(this, "Самый популярный верстак", result);
}

