#ifndef LIST_H
#define LIST_H
#include <QString>
#include <QTextStream>
#include <iostream>
namespace TheList{

struct elem{
    QString name;
    QString human;
    int amount;
    int value;
    int tot_value;
    QString data;

    elem* next;
    elem* prev;
    elem(){
        amount = 0;
        value = 0;
        tot_value = 0;
    }
};
class list {
    elem* head;
    elem* tail;
    int count;
public:
    list();
    ~list();

    int get_data(int index);
    int get_count();
    elem* get_item(int index);

    void add_head(elem* tmp);
    void add_tail(elem* tmp);
    void insert_after(int index, elem* new_node);

    void remove(int index);
    void clear();

    void swap(int first, int second);
    int search(int A);

    void print_from_head();
    void print_from_tail();

    void solve();
};
}
#endif // LIST_H
