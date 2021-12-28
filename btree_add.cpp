#include "btree_add.h"
#include "ui_btree_add.h"

btree_add::btree_add(QWidget *parent) : QDialog(parent), ui(new Ui::btree_add) {
    ui->setupUi(this);
}
btree_add::~btree_add() {
    delete ui;
}

void btree_add::set_human(BTreeNodeData *human) {
    new_human = human;
    ui->editNumber->setText(QString::number(new_human->invent_number));
    ui->editName->setText(new_human->name);
    ui->editType->setText(new_human->type);
    ui->editOverwork->setText(QString::number(new_human->overwork_time));
    ui->editWork->setText(QString::number(new_human->work_time));
}

void btree_add::on_buttonBox_accepted() {
    new_human->invent_number = ui->editNumber->text().toInt();
    new_human->name = ui->editName->text();
    new_human->type = ui->editType->text();
    new_human->overwork_time = ui->editOverwork->text().toInt();
    new_human->work_time = ui->editWork->text().toInt();
    emit workbenchChanged(new_human);
    close();
}
void btree_add::on_buttonBox_rejected() {
    close();
}
