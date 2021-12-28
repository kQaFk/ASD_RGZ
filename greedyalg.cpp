#include "greedyalg.h"
#include "ui_greedyalg.h"
#include <QDir>
#include <QFile>
greedyalg::greedyalg(QWidget *parent) : QDialog(parent), ui(new Ui::greedyalg) {
    ui->setupUi(this);
}
greedyalg::~greedyalg() {
    delete ui;
}

QVector<Project> GreedyAlg(int n, QVector<Project> v, int end_gap){
    QVector<Project> res_v;
    int res = 0;
    std::sort(v.begin(), v.end());
    while (!v.empty() && end_gap > 0) {
        res += v[0].get_value();
        end_gap -= v[0].get_duration();
        if (end_gap <= 0) {
             res -= v[0].get_value();
             continue;
            }
        res_v.push_back(v[0]);
        v.erase(v.begin());
        }
    return res_v;
}

void greedyalg::on_StartButton_clicked() {
    QVector<Project> result;
    int n, tmp, end_gap;
    QString file_path = "//Greedy_input.txt";
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
    Project list;
    QVector<Project> v;
    for (int i = 0; i < n; i++) {
        fin >> tmp;
        list.setBegTime(tmp);
        fin >> tmp;
        list.setEndTime(tmp);
        fin >> tmp;
        list.setValue(tmp);
        list.setDuration(list.CalcDur(list.getBeg(), list.getEnd()));
        v.push_back(list);
    }
    fin >> end_gap;
    QString result_string;
    result = GreedyAlg(n, v, end_gap);
    for (int i = 0; i < result.size(); i++)
        result_string.append("\n[Проект " + QString::number(i + 1) + " ]: " + "Дата начала проекта: " + QString::number(result[i].getBeg()) +
            "\nДата конца проекта: " + QString::number(result[i].getEnd()) + "\nПрибыль: " + QString::number(result[i].get_value()) +
                                     "\nПродолжительность проекта (в днях): " + QString::number(result[i].get_duration()));
    ui->AnswearLabel->clear();
    ui->AnswearLabel->setText(result_string);
}
