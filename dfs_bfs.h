#ifndef DFS_BFS_H
#define DFS_BFS_H

#include <QDialog>
#include <QFile>
#include <QString>
#include <QRegularExpression>

namespace Ui { class dfs_bfs; }

class dfs_bfs : public QDialog {
    Q_OBJECT

public:
    explicit dfs_bfs(QWidget *parent = nullptr);
    ~dfs_bfs();
    void DFS(int st, int n_1, QVector<QVector<int>> graph);

private slots:
    void on_Task1Button_clicked();
    void on_Task2Button_clicked();
    void on_Task3Button_clicked();

private:
    Ui::dfs_bfs *ui;
};
#endif // DFS_BFS_H
