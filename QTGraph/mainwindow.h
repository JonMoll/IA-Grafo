#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CGraph.h"

namespace Ui {
class MainWindow;
}

class DoGraphicsScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CGraph *my_graph;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    DoGraphicsScene *mGraphicsScene;
};

#endif // MAINWINDOW_H
