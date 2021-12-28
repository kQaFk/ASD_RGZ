#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QFile>

namespace Ui { class hashtable; }

class HashItem {
    int key;
    QString word;
    int amount;
    HashItem* next = NULL;
public:
    int get_key() { return key; };
    void set_key(int k) { key = k; }

    QString get_word() { return word; }
    void set_word(QString str) { word = str; }

    int get_amount() { return amount; };
    void set_amount(int n) { amount = n; }

    HashItem* get_next() { return next; }
    void set_next(HashItem* n) { next = n; }

    void output_item();

    int HashFunc();
    int HashKey();

    bool operator==(HashItem& b) {
        if (word == b.get_word()) return true;
        else return false;
    }

    bool operator<(HashItem& b) {
        if (amount < b.get_amount()) return true;
        else return false;
    }
};

class hashtable : public QDialog {
    Q_OBJECT
public:
    explicit hashtable(QWidget *parent = nullptr);
    ~hashtable();

    void put_item(HashItem value);
    void remove(HashItem value);
private:
    Ui::hashtable *ui;
    QString path_in_hash;
    HashItem** table;
    int TABLE_SIZE;

    void addToTable(HashItem new_node);

private slots:
    void on_Input_From_File_clicked();
    void on_ClearButton_clicked();

};

#endif // HASHTABLE_H
