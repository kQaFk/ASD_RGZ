#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "btree.h"
#include "heapsort.h"
#include "dynamicprogramming.h"
#include "dfs_bfs.h"
#include "huffman.h"
#include "greedyalg.h"
#include "hashtable.h"
#include "shortest_path.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_TreeButton_clicked() {
    btree *BTreeWindow = new btree;
    BTreeWindow->show();
}

void MainWindow::on_HashButton_clicked() {
    hashtable *HashTableWindow = new hashtable;
    HashTableWindow->show();
}

void MainWindow::on_ShortButton_clicked() {
    shortest_path *SPWindow = new shortest_path;
    SPWindow->show();
}

void MainWindow::on_GreedyButton_clicked(){
    greedyalg *GreedyAlgWindow = new greedyalg;
    GreedyAlgWindow->show();
}

void MainWindow::on_BDFSButton_clicked(){
    dfs_bfs *DFS_BFSWindow = new dfs_bfs;
    DFS_BFSWindow->show();
}

void MainWindow::on_DynButton_clicked(){
    dynamicprogramming *DPWindow = new dynamicprogramming;
    DPWindow->show();
}

void MainWindow::on_HuffmanButton_clicked() {
    huffman *HuffmanWindow = new huffman;
    HuffmanWindow->show();
}

void MainWindow::on_SortButton_clicked() {
HeapSort *HeapSortWindow = new HeapSort;
HeapSortWindow->show();
}
