#include "heapsort_add.h"
#include "ui_heapsort_add.h"

heapsort_add::heapsort_add(QWidget *parent) : QDialog(parent), ui(new Ui::heapsort_add) {
    ui->setupUi(this);
}
heapsort_add::~heapsort_add() {
    delete ui;
}

void heapsort_add::set_item(TheList::elem* book){
    new_item = book;
    ui->editName->setText(new_item->name);
    ui->editHuman->setText(new_item->human);
    ui->editAmount->setText(QString::number(new_item->amount));
    ui->editValue->setText(QString::number(new_item->value));
    ui->editData->setText(new_item->data);
}
void heapsort_add::on_buttonBox_accepted() {
    new_item->name = ui->editName->text();
    new_item->human = ui->editHuman->text();
    new_item->amount = ui->editAmount->text().toInt();
    new_item->value = ui->editValue->text().toInt();
    new_item->tot_value = new_item->amount * new_item->value;
    new_item->data = ui->editData->text();
    emit itemChanged(new_item);
    close();
}
void heapsort_add::on_buttonBox_rejected() {
    close();
}
