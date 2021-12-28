#include "dfs_bfs.h"
#include "ui_dfs_bfs.h"
#include <QQueue>
#include <QDir>
dfs_bfs::dfs_bfs(QWidget *parent) : QDialog(parent), ui(new Ui::dfs_bfs) {
    ui->setupUi(this);
}
dfs_bfs::~dfs_bfs() {
    delete ui;
}

int n, m, a, b;
int countr = 0;
QVector<QVector<int> > graf;
QVector<int> ver;
QVector<int> family;
bool ok = false;
QVector<int> ans;
QVector<bool> der;
QVector<bool> visited;

void dfs_bfs::DFS(int st, int n_1, QVector<QVector<int>> graph) {
    int r;
    visited[st] = true;
    ui->AnswearLabel->append(QString::number(st) + " ");
    for (r = 0; r <= n_1; r++){
         if ((r != n_1) && (graph[st][r] != 0) && (!visited[r])){
            DFS(r, n_1, graph);
         }
    }
}

int bfs(int beg, int end) {
    countr++;
    if (beg == end) {
        ok = true;
        return 1;
    }
    else {
        for (int i = graf[beg].size() - 1; i >= 0; i--) {
            if (!der[graf[beg][i]]) {
                ver.push_back(graf[beg][i]);
                family.push_back(beg);
                der[graf[beg][i]] = true;
            }
        }
    }
    return 0;
}

void find_path(int n_1, int row, int col, QChar** lab, int** visited, int** path, QQueue<int>& plan) {
    if (!visited[row][col]) {
        if ((row + 1) < n_1 && (row + 1) >= 0 && !visited[row + 1][col] &&
            (lab[row + 1][col] == '.' || lab[row + 1][col] == 'X')) {
            path[row + 1][col] = path[row][col] + 1;
            plan.enqueue(row + 1);
            plan.enqueue(col);
        }
        if ((row - 1) < n_1 && (row - 1) >= 0 && !visited[row - 1][col] &&
            (lab[row - 1][col] == '.' || lab[row - 1][col] == 'X')) {
            path[row - 1][col] = path[row][col] + 1;
            plan.enqueue(row - 1);
            plan.enqueue(col);
        }
        if ((col + 1) < n_1 && (col + 1) >= 0 && !visited[row][col + 1] &&
            (lab[row][col + 1] == '.' || lab[row][col + 1] == 'X')) {
            path[row][col + 1] = path[row][col] + 1;
            plan.enqueue(row);
            plan.enqueue(col + 1);
        }
        if ((col - 1) < n_1 && (col - 1) >= 0 && !visited[row][col - 1] &&
            (lab[row][col - 1] == '.' || lab[row][col - 1] == 'X')) {
            path[row][col - 1] = path[row][col] + 1;
            plan.enqueue(row);
            plan.enqueue(col - 1);
        }
        visited[row][col] = 1;
    }
}

void dfs_bfs::on_Task1Button_clicked() {
    int tmp;
    int n_1;

    QVector<int> temp_v;
    QString file_name = "//DFS.txt";
    QFile file (QDir::toNativeSeparators(QApplication::applicationDirPath()) + file_name);
    if(!file.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file.open(QIODevice::ReadWrite)){
        qCritical() << file.errorString();
        return;
    }
    QTextStream fin(&file);
    fin >> n_1;
    QVector<QVector<int>> graph;

    for (int i = 0; i < n_1; i++) {
        for (int j = 0; j < n_1; j++) {
                fin >> tmp;
                temp_v.push_back(tmp);
        }
        graph.push_back(temp_v);
        temp_v.clear();
    }
    for (int i = 0; i < n_1; i++) visited.push_back(false);
    int start;
    fin >> start;
    ui->AnswearLabel->append("Обход графа: ");
    DFS(start, n_1, graph);
}

void dfs_bfs::on_Task2Button_clicked() {
    QString result_string;
    int n_2, x_start, y_start, x_end, y_end, x, y;
    QQueue <int> plan;
    QString file_name = "//Labyrinth.txt";
    QFile file (QDir::toNativeSeparators(QApplication::applicationDirPath()) + file_name);
    if(!file.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file.open(QIODevice::ReadWrite)){
        qCritical() << file.errorString();
        return;
    }
    QTextStream fin(&file);

    fin >> n_2;
        QChar** lab = new QChar* [n_2];
        int** visited = new int* [n_2];
        int** path = new int* [n_2];
        for (int i = 0; i < n_2; i++) {
            lab[i] = new QChar[n_2];
            visited[i] = new int[n_2];
            path[i] = new int[n_2];
            for (int j = 0; j < n_2; j++) {
                visited[i][j] = 0;
                path[i][j] = -1;
                fin >> lab[i][j];
                if (lab[i][j] == '@') {
                    x_start = i;
                    y_start = j;
                    plan.enqueue(i);
                    plan.enqueue(j);
                    path[i][j] = 1;
                }
                else if (lab[i][j] == 'X') {
                    x_end = i;
                    y_end = j;
                }
            }
        }
        while (!plan.empty()) {
            x = plan.front();
            plan.dequeue();
            y = plan.front();
            plan.dequeue();
            find_path(n_2, x, y, lab, visited, path, plan);
        }
        if (!visited[x_end][y_end]) {
                ui->Task2AnswearTextEdit->append( "N\n");
        }
        else {
            x = x_end;
            y = y_end;
            lab[x][y] = '+';
            while (path[x][y] != 2) {
                if ((x - 1) >= 0 && (x - 1) < n_2 && (path[x - 1][y] == path[x][y] - 1)) {
                    x = x - 1;
                    lab[x][y] = '+';
                }
                else if ((x + 1) >= 0 && (x + 1) < n_2 && (path[x + 1][y] == path[x][y] - 1)) {
                    x = x + 1;
                    lab[x][y] = '+';
                }
                else if ((y - 1) >= 0 && (y - 1) < n_2 && (path[x][y - 1] == path[x][y] - 1)) {
                    y = y - 1;
                    lab[x][y] = '+';
                }
                else if ((y + 1) >= 0 && (y + 1) < n_2 && (path[x][y + 1] == path[x][y] - 1)) {
                    y = y + 1;
                    lab[x][y] = '+';
                }
            }
            for (int i = 0; i < n_2; i++) {
                for (int j = 0; j < n_2; j++) {
                    result_string.append(lab[i][j]);
                    result_string.append(" ");
                }
                result_string.append("\n");
            }
            ui->Task2AnswearTextEdit->append(result_string);
}
}

void dfs_bfs::on_Task3Button_clicked() {
    QString file_name = "//BFS.txt";
    QFile file (QDir::toNativeSeparators(QApplication::applicationDirPath()) + file_name);
    if(!file.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file.open(QIODevice::ReadWrite)){
        qCritical() << file.errorString();
        return;
    }
    QTextStream fin(&file);
    fin >> n >> m;
        fin >> a >> b;
        for (int i = 0; i <= n; i++) {
            graf.push_back(ans);
            der.push_back(false);
        }
        ver.push_back(a); family.push_back(a);
        for (int i = 0; i < m; i++) {
            int x, y;
            fin >> x >> y;
            if (x != y) {
                graf[x].push_back(y);
                graf[y].push_back(x);
            }
        }
        if (!graf[a].empty()) {
            while (!ok && countr < ver.size()) {
                if (bfs(ver[countr], b)) {
                    countr--;
                    int p = 1;
                    ans.push_back(b);
                    while (ver[countr] != a) {
                        while (ver[p] != family[countr]) {
                            p++;
                        }
                        ans.push_back(ver[p]);
                        countr = p;
                        p = 1;
                    }
                }
            }
            if (ans.size() > 0) {
                ui->Task3AnswearTextEdit->append( QString::number(ans.size() - 1) + "\n");
                for (int i = ans.size() - 1; i >= 0; i--) {
                   ui->Task3AnswearTextEdit->append( QString::number( ans[i] - 1) + " ");
                }
            }
            else {
                ui->Task3AnswearTextEdit->append( "-1\n");
            }
        }
        else {
            ui->Task3AnswearTextEdit->append( "-1\n");
        }
}


