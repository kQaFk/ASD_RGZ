#ifndef HEAPSORT_H
#define HEAPSORT_H
#include <QString>
#include <QTextStream>
#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include "list.h"

namespace Ui { class HeapSort; }

class HeapSort : public QDialog {
    Q_OBJECT

public:
    explicit HeapSort(QWidget *parent = nullptr);
    ~HeapSort();

private slots:
    void on_Add_to_tail_Button_clicked();
    void on_Input_From_File_clicked();
    void on_SortButton_clicked();
    void on_ClearButton_clicked();
    void on_DeleteButton_clicked();

    void onItemChanged(TheList::elem* item);

private:
    Ui::HeapSort *ui;

    TheList::list arr;
    QString input_file_name;

    void sift(TheList::list& arr, int n, int i);
    void heapSort(TheList::list& arr);
    void populateTable();
    void addToTable(TheList::elem* book);
};

#endif
