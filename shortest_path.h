#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include <QDialog>
#include <QString>
#include <QFile>
#include <QPair>
#include <QVector>

namespace Ui { class shortest_path; }

struct Edge {
    int src, dest, weight;
};



class GraphBellman {
    int V, E;
    QVector<Edge> edge;
public:
    void setGraph(QVector<Edge> edg, int v, int e);
    void discount(QVector<QPair<int, int>>);
    QVector<int> BellmanFord(int);
};



class GraphDij {
    int n;
    int tmp, minind, min;
    int beg_ind = 0;
    int* dis;
    int* been;
    int end;
    QVector < QVector<int> > g;
public:
    void input_graph();
    int* Dijkstra();
    int get_n() {return n;}
    void set_n(int tmp) {n = tmp;}
};



class GraphWarshall {
    int** graph;
    int V;
public:
    void setGraph();
    int** floydWarshall();
    int get_V() {return V;}
};



class shortest_path : public QDialog {
    Q_OBJECT

public:
    explicit shortest_path(QWidget *parent = nullptr);
    ~shortest_path();
private slots:
    void on_Task1Button_clicked();
    void on_Task2Button_clicked();
    void on_Task3Button_clicked();

private:
    Ui::shortest_path *ui;
};

#endif // SHORTEST_PATH_H
