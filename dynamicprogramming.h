#ifndef DYNAMICPROGRAMMING_H
#define DYNAMICPROGRAMMING_H
#include <QDialog>
#include <QFile>
#include <QtAlgorithms>
#include <QRegularExpression>
#include <QString>
#include <cmath>

#include <QMap>
#include <QVector>

namespace Ui { class dynamicprogramming; }

class Words {
    int n;
    int res1, res2;
    QVector<QString> res_words;
    QVector<int> pars;
    QString sec;
public:
    Words();
    void split();
    QVector<QString> solve_dir();
    QVector<QString> solve_rev();
    int get_res1() { return res1; }
    int get_res2() { return res2; }
    int get_n() { return n; }
    int get_pars_size() { return pars.size(); }
    QString get_sec() { return sec; }
};

class Town {
    QMap<QString, int> results;

    int n;
    QVector<QVector<QString>> matrix;
public:
    Town(QVector<QVector<QString>> matr, int a): n(a), matrix(matr){}
    QMap<QString, int> solve();
};

class dynamicprogramming : public QDialog {
    Q_OBJECT

public:
    explicit dynamicprogramming(QWidget *parent = nullptr);
    ~dynamicprogramming();

private slots:
    void on_FirstTaskButton_clicked();
    void on_SecondTaskButton_clicked();
    void on_InputFromFileMatrixButton_clicked();

private:
    Ui::dynamicprogramming *ui;
    QVector<QVector<QString>> matr;
};

#endif // DYNAMICPROGRAMMING_H
