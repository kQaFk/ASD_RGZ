#include "dynamicprogramming.h"
#include "ui_dynamicprogramming.h"
#include <QDir>
dynamicprogramming::dynamicprogramming(QWidget *parent) : QDialog(parent), ui(new Ui::dynamicprogramming) {
    ui->setupUi(this);
}
dynamicprogramming::~dynamicprogramming() {
    delete ui;
}

Words::Words() {
    int tmp;
    int pred;
    QString s;
    QString file_path = "//DP_input1.txt";
    QFile file (QDir::toNativeSeparators(QApplication::applicationDirPath()) + file_path);
    if(!file.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file.open(QIODevice::ReadWrite)){
        qCritical() << file.errorString();
        return;
    }
    QTextStream fin(&file);
    fin >> n;
    fin >> s;
    fin >> pred;
    for (int i = 0; i < pred; i++){
        fin >> tmp;
        pars.push_back(tmp);
    }
    sec = s;
    res1 = n;
    res2 = res1;
}

void Words::split() {
    int n1 = res1;
    int n2 = res2;
    for (int i = 0; i < pars.size() - 1; i++) {
        n1 -= pars[i];
        res1 += n1;
    }
    for (int i = pars.size() - 1; i > 0; i--){
        n2 -= pars[i];
        res2 += pars[i];
    }
}

QVector<QString> Words::solve_dir() {
    int mover = 0;
    QString tmp;
    for (int i = 0; i < n; i++) {
        tmp.push_back(sec[i]);
        if (mover < pars.size() && i == pars[mover] - 1) {
            res_words.push_back(tmp);
            mover++;
            tmp.clear();
        }
    }
    res_words.push_back(tmp);
    return res_words;
}

QVector<QString> Words::solve_rev() {
    int mover = pars.size() - 1;
    QString tmp;
    for (int i = sec.size()-1; i >=0; i--) {
        tmp.push_back(sec[i]);
        if (mover >= 0 && i == pars[mover] ) {
            res_words.push_back(tmp);
            mover--;
            tmp.clear();
        }
    }
    res_words.push_back(tmp);
    return res_words;
}

QMap<QString, int> Town::solve() {
    QString tmp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i; j < n; j++) {
            if (j != i) {
                tmp += matrix[i][j];
                tmp += matrix[i + 1][j];
                std::sort(tmp.begin(), tmp.end());
                results[tmp]++;
                tmp.clear();
            }
            if(j!=n-1) {
                tmp += matrix[i][j];
                tmp += matrix[i][j+1];
                std::sort(tmp.begin(), tmp.end());
                results[tmp]++;
                tmp.clear();
            }
        }
    QMap<QString, int>::iterator i;
    for (i = results.begin(); i != results.end(); i++)
        i.value() *= 2;
    return results;
}

void dynamicprogramming::on_FirstTaskButton_clicked() {
    QVector<QString> result;
    Words word;
    word.split();
    if (word.get_res1() <= word.get_res2()) result = word.solve_dir();
    else result = word.solve_rev();
    for (int i = 0; i<result.size(); i++)
     ui->ElementsEdit->append(result[i]);

}

void dynamicprogramming::on_InputFromFileMatrixButton_clicked() {
    QFile file( QDir::toNativeSeparators(QApplication::applicationDirPath()) + "//DP_input2.txt");
    if(!file.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file.open(QIODevice::ReadWrite)){
        qCritical() << file.errorString();
        return;
    }

    QVector<QString> cells;
    QString text = file.readAll();
    QStringList list = text.split(QRegularExpression("\\s+"));

    for (int i = 0; i < list.count(); i++)
        cells.push_back(list[i]);
    int n = sqrt(list.size());

    QVector<QVector<QString>> matrix;
    QVector<QString> tmp_line; QString tmp_str;
    for (int i = 0; i < cells.size(); i++){
        tmp_line.push_back(cells[i]);
        if(tmp_line.size() == n){
            matrix.push_back(tmp_line);
            tmp_line.clear();
        }
    }

    matr.clear();
    matr = matrix;
    file.close();
}

void dynamicprogramming::on_SecondTaskButton_clicked() {
    QVector<QVector<QString>> matrix = matr;
    int n = matr[0].size();

    Town twn(matrix, n);
    QMap<QString, int> result = twn.solve();
    QString result_string("Результат: \n");
    QMap<QString, int>::iterator i;
    for (i = result.begin(); i != result.end(); i++)
        result_string.append("[" + i.key() + "]: " + QString::number(i.value()) + '\n');
    ui->SecondTaskAnswearEdit->setPlainText(result_string);
}
