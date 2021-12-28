#include "hashtable.h"
#include "ui_hashtable.h"
#include <QDir>
#include <QMap>
#include <QSet>
#include <QPair>

int HashItem::HashFunc() {
    return key % 13;
}

int HashItem::HashKey() {
    return ((word[0].unicode()) * word.size());
}

hashtable::hashtable(QWidget *parent) : QDialog(parent), ui(new Ui::hashtable) {
    ui->setupUi(this);

    path_in_hash = "//input_hash.txt";
    TABLE_SIZE = 9;
    table = new HashItem * [TABLE_SIZE]();
}

hashtable::~hashtable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashItem* item = table[i];
        while (item != NULL) {
            HashItem* prev = item;
            item = item->get_next();
            delete prev;
        }
        table[i] = NULL;
    }
    delete[] table;
    delete ui;
}

void hashtable::addToTable(HashItem value){
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

    QTableWidgetItem *newItem;

    newItem = new QTableWidgetItem();
    newItem->setText(value.get_word());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(QString::number(value.get_amount()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, newItem);
}

void hashtable::put_item(HashItem value) {
    int key = value.HashFunc();
    HashItem* prev = NULL;
    HashItem* entry = table[key];

    while (entry != NULL) {
        prev = entry;
        entry = entry->get_next();
    }

    entry = new HashItem;
    *entry = value;

    if (prev == NULL)
        table[key] = entry;
    else
        prev->set_next(entry);
}

void hashtable::remove(HashItem value) {
    int key = value.HashFunc();
    HashItem* prev = NULL;
    HashItem* entry = table[key];

    while (entry != NULL && !(*entry == value)) {
        prev = entry;
        entry = entry->get_next();
    }

    if (entry == NULL) {
        qCritical() << "Не удалось удалить элемент";
        return;
    }

    if (prev == NULL)
        table[key] = entry->get_next();
    else
        prev->set_next(entry->get_next());
    delete entry;
}

void hashtable::on_ClearButton_clicked() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashItem* item = table[i];
        while (item != NULL) {
            HashItem* prev = item;
            item = item->get_next();
            delete prev;
        }
        table[i] = NULL;
    }
    delete[] table;

    table = new HashItem * [TABLE_SIZE]();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void hashtable::on_Input_From_File_clicked() {
    QFile file( QDir::toNativeSeparators(QApplication::applicationDirPath()) + path_in_hash);
    QMap<QString, int> m;
    QString s;
    int key_n;
    if(!file.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file.open(QIODevice::ReadWrite)){
        qCritical() << file.errorString();
        return;
    }
    QTextStream fin(&file);

    while (!fin.atEnd()) {
            s = fin.readLine();
            if (s.size() <= 2) continue;
            m[s]++;
        }
    HashItem item;
        for (auto x : m.keys()) {
            item.set_word(x);
            item.set_amount(m.value(x));
            key_n = item.HashKey();
            item.set_key(key_n);

            put_item(item);
            addToTable(item);
        }
    file.close();
}
