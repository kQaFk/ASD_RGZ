#include "heapsort.h"
#include "ui_heapsort.h"
#include "heapsort_add.h"

QTextStream & operator>> (QTextStream&fin, TheList::elem* elem) {
    elem->name = fin.readLine();
    elem->human = fin.readLine();
    fin >> elem->amount;
    fin >> elem->value;
    elem->tot_value = elem->amount * elem->value;
    elem->data = fin.readLine();
    QString garbage = fin.readLine();
    return fin;
}

HeapSort::HeapSort(QWidget *parent) : QDialog(parent), ui(new Ui::HeapSort) {
    ui->setupUi(this);
    input_file_name = "heapsort_input.txt";
}
HeapSort::~HeapSort() {
    delete ui;
}

void HeapSort::sift(TheList::list& arr, int n, int i) {
    int max = i;

    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr.get_data(l+1) > arr.get_data(max + 1)) max = l;

    if (r < n && arr.get_data(r + 1) > arr.get_data(max + 1)) max = r;

    if (max != i) {
        arr.swap(i, max);
        sift(arr, n, max);
    }
}
void HeapSort::heapSort(TheList::list& arr) {
    int n = arr.get_count();
    for (int i = n / 2 - 1; i >= 0; i--) sift(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        arr.swap(0, i);
        sift(arr, i, 0);
    }
}

void HeapSort::populateTable(){
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    for(int i = 1; i <= arr.get_count(); i++)
        addToTable(arr.get_item(i));
}
void HeapSort::addToTable(TheList::elem* bench){
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

    QTableWidgetItem *newItem;

    newItem = new QTableWidgetItem();
    newItem->setText(bench->name);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(bench->human);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(QString::number(bench->amount));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(QString::number(bench->value));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(QString::number(bench->tot_value));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(bench->data);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 5, newItem);
}

void HeapSort::on_Add_to_tail_Button_clicked() {
    heapsort_add *window = new heapsort_add;
    window->set_item(new TheList::elem);
    connect(window, SIGNAL(itemChanged(TheList::elem*)), this, SLOT(onItemChanged(TheList::elem*)));
    window->show();
}
void HeapSort::on_Input_From_File_clicked() {
    QFile file( QDir::toNativeSeparators(QApplication::applicationDirPath()) + "//" + input_file_name );
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
        TheList::elem* new_node = new TheList::elem;
        fin >> new_node;
        arr.add_tail(new_node);
        addToTable(new_node);
    }
    file.close();
}
void HeapSort::on_SortButton_clicked() {
    heapSort(arr);
    populateTable();
}
void HeapSort::on_DeleteButton_clicked() {
    if(arr.get_count() == 1)
        return;
    int index = ui->tableWidget->currentRow();
    arr.remove(index + 1);
    ui->tableWidget->removeRow(index);
}
void HeapSort::on_ClearButton_clicked() {
    arr.clear();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void HeapSort::onItemChanged(TheList::elem* item){
    arr.add_tail(item);
    addToTable(item);
}
