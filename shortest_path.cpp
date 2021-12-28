#include "shortest_path.h"
#include "ui_shortest_path.h"
#include <QDir>
#define INF 99999

shortest_path::shortest_path(QWidget *parent) : QDialog(parent), ui(new Ui::shortest_path) {
    ui->setupUi(this);
}
shortest_path::~shortest_path() {
    delete ui;
}

void GraphBellman::setGraph(QVector<Edge> edg, int v, int e) {
    V = v;
    E = e;
    edge = edg;
}

void GraphBellman::discount(QVector<QPair<int, int>> discounts) {
    for (int i = 0; i < E; i++)
        for (int j = 0; j < discounts.size(); j++)
            if (edge[i].src == discounts[j].first)
                edge[i].weight -= discounts[j].second;
}

QVector<int> GraphBellman::BellmanFord(int u) {
    int v = this->V;
    int e = this->E;

    QVector<int> dist;

    for (int i = 0; i < v; i++)
        dist.push_back(INT_MAX);
    dist[u] = 0;
    for (int i = 1; i <= v - 1; i++) {
        for (int j = 0; j < e; j++) {
            int u = edge[j].src;
            int v = edge[j].dest;
            int w = edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }
    return dist;
}

void GraphDij::input_graph() {
    QVector<int> input;
    QString file_name = "//Dijkstra.txt";
    QFile file(QDir::toNativeSeparators(QApplication::applicationDirPath()) + file_name);
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
    dis = new int[n];
    been = new int[n];

    fin >> end;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> tmp;
            input.push_back(tmp);
        }
        g.push_back(input);
        input.clear();
    }
    for (int i = 0; i < n; i++) {
        dis[i] = 10000;
        been[i] = 1;
    }

    dis[beg_ind] = 0;
    file.close();
}

int* GraphDij::Dijkstra() {
    do {
        minind = 10000;
        min = 10000;
        for (int i = 0; i < n; i++) {
            if ((been[i] == 1) && (dis[i] < min)) {
                min = dis[i];
                minind = i;
            }
        }

        if (minind != 10000) {
            for (int i = 0; i < n; i++) {
                if (g[minind][i] > 0) {
                    tmp = min + g[minind][i];
                    if (tmp < dis[i]) {
                        dis[i] = tmp;
                    }
                }
            }
            been[minind] = 0;
        }
    } while (minind < 10000);

    int* ver = new int[n];
    ver[0] = end + 1;
    int k = 1;
    int weight = dis[end];

    while (end != beg_ind) {
        for (int i = 0; i < n; i++)
            if (g[i][end] != 0) {
                int temp = weight - g[i][end];
                if (temp == dis[i]) {
                    weight = temp;
                    end = i;
                    ver[k] = i + 1;
                    k++;
                }
            }
    }
    n = k - 1;
    return ver;
}

void GraphWarshall::setGraph() {
    QString file_path = "//Warshall.txt";
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
    fin >> V;
    graph = new int*[V];
    for (int i = 0; i < V; i++) {
        graph[i] = new int[V];
    }
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            fin >> graph[i][j];
        }
    }
}

int** GraphWarshall::floydWarshall() {
    int i, j, k;
    int** dist = new int*[V];
    for (int i = 0; i < V; i++) {
        dist[i] = new int[V];
    }
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j])
                    && (dist[k][j] != INF
                        && dist[i][k] != INF))
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    return dist;
}


void shortest_path::on_Task1Button_clicked(){
    Edge tmp_edge;
    int tmp_int;
    QVector<Edge> edge;
    QVector<int> result;
    int V, E, destination;
    QVector<QPair<int, int>> discounts;
    QPair<int, int> tmp;
    int numb_disc;
    QString file_path = "//Bellman.txt";
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
    fin >> V >> E;
        destination = ui->StartVertexEditT_1->text().toInt();
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++) {
                fin >> tmp_int;
                if (tmp_int != 0)
                {
                    tmp_edge.src = i;
                    tmp_edge.dest = j;
                    tmp_edge.weight = tmp_int;
                    edge.push_back(tmp_edge);
                }
            }
        fin >> numb_disc;

        for (int i = 0; i < numb_disc; i++) {
            fin >> tmp.first >> tmp.second;
            discounts.push_back(tmp);
        }

        GraphBellman g;
        g.setGraph(edge, V, E);
        g.discount(discounts);
        result = g.BellmanFord(destination);
        ui->AnswearEditT_1->clear();
        for (int i = 0; i < V; i++)
            ui->AnswearEditT_1->append("[" + QString::number(i) + "]: " + QString::number(result[i]));
     file.close();
}

void shortest_path::on_Task2Button_clicked(){
    GraphDij g;
    g.input_graph();
    int* result = g.Dijkstra();
    for (int i = g.get_n(); i >= 0; i--)
        ui->AnswearEditT_2->append(QString::number(result[i]));
}

void shortest_path::on_Task3Button_clicked(){
    int** result;
    GraphWarshall g;
    g.setGraph();
    result = g.floydWarshall();
    int inf_value = 9999;
    ui->AnswearEditT_3->clear();
    for (int i = 0; i < g.get_V(); i++) {
        QString tmp_str;
        for (int j = 0; j < g.get_V(); j++) {
            if (result[i][j] == inf_value)
                tmp_str.append("INF ");
            else
                tmp_str.append(QString::number(result[i][j]) + ' ');
        }
        ui->AnswearEditT_3->append(tmp_str);
    }
}
