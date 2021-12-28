#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <QDialog>
#include <QFile>
#include <QtAlgorithms>
#include <QString>

#include <QVector>
#include <QMap>
#include <QList>

namespace Ui { class huffman; }

struct huff_node {
    QChar data;
    int freq;
    huff_node* left, * right;
    huff_node() : data('\0'), freq(0), left(NULL), right(NULL) {};
    huff_node(huff_node* l, huff_node* r) :  data('\0'), left(l), right(r) {
        freq = l->freq + r->freq;
    };
};
class Huffman {
    QString str;
    huff_node* root;

    QString input_file_name;
    QString output_file_name;

    QVector<bool> code;
    QMap<int, int> a;
    QMap<QChar, QVector<bool> > table;
public:
    Huffman(): input_file_name("input.txt"), output_file_name("output.txt") {}
    Huffman(QMap<QChar, QVector<bool> > a, huff_node* b) : root(b), table(a) {}
    void BuildTable(huff_node* root);

    void compress(QString text);
    QString decompress(QByteArray byte_array);

    QMap<QChar, QVector<bool> > get_table();
    huff_node* get_root();
};


class huffman : public QDialog {
    Q_OBJECT

public:
    explicit huffman(QWidget *parent = nullptr);
    ~huffman();

private slots:
    void on_CompressButton_clicked();
    void on_DecompressButton_clicked();

private:
    Ui::huffman *ui;

    QMap<QChar, QVector<bool> > table;
    huff_node* root;
};

#endif // HUFFMAN_H
