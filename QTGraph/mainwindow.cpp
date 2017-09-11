#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dographicsscene.h"

#include <ctime>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    my_graph = new CGraph(100, false);

    ui->setupUi(this);
    mGraphicsScene = new DoGraphicsScene(this, my_graph, 0, 0, 0);

     ui->graphicsView->setScene(mGraphicsScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() // busqueda heuristica
{
    QString str_a = ui->lineEdit->text();
    QString str_b = ui->lineEdit_2->text();

    int a = str_a.toInt();
    int b = str_b.toInt();;

    unsigned t0, t1;

    t0 = clock();

    DoGraphicsScene *camino = new DoGraphicsScene(this, my_graph, 1, a, b);

    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);

    std::ostringstream s;
    s << time;
    std::string salida = s.str();

    const char* msg = salida.c_str();

    ui->label_3->setText(QString(msg));

    ui->graphicsView->setScene(camino);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->graphicsView->setScene(mGraphicsScene);
}
