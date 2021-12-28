#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_TreeButton_clicked();
    void on_HashButton_clicked();
    void on_ShortButton_clicked();
    void on_GreedyButton_clicked();
    void on_BDFSButton_clicked();
    void on_DynButton_clicked();
    void on_HuffmanButton_clicked();
    void on_SortButton_clicked();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
