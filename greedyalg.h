#ifndef GREEDYALG_H
#define GREEDYALG_H
#include <QVector>
#include <QDialog>
#include <QRegularExpression>

namespace Ui { class greedyalg; }

class Project {
    int beg;
    int end;
    int value;
    double duration;
public:
    Project& operator= (const Project& p) {
        this->beg = p.beg;
        this->end = p.end;
        this->value = p.value;
        this->duration = p.duration;
        return *this;
    }

    bool operator> (const Project& p) {
        return (duration > p.duration);
    }
    bool operator< (const Project& p) {
        return (value > p.value);
    }

    void setBegTime(int dd2){
        beg = dd2;
    }
    void setEndTime(int dd2){
        end = dd2;
    }
    void setValue(int val) {
        value = val;
    }

    void setDuration(int dur) {
        duration = dur;
    }

    int getBeg() { return beg; }

    int getEnd() { return end; }

    int get_value() { return value; }

    double get_duration() { return duration; }

    int CalcDur(int data1, int data2) {return (data2 - data1);}

    void printData(int);
};
class greedyalg : public QDialog {
    Q_OBJECT

public:
    explicit greedyalg(QWidget *parent = nullptr);

    ~greedyalg();
private slots:
    void on_StartButton_clicked();

private:
    Ui::greedyalg *ui;
};

#endif // GREEDYALG_H
