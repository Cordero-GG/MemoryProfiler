#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "profiler.h" 
#include <QTimer> 

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
   , Profiler(new class Profiler()) // Inicializar el profiler con el especificador de tipo
{
   ui->setupUi(this);

   //timer = new QTimer(this); // Timer
   //connect(timer, &QTimer::timeout, this, &MainWindow::actualizarMetricasGenerales);
   //timer->start(1000); // Actualiza cada segundo
}

MainWindow::~MainWindow()
{
   //delete timer; // Eliminar el timer
   delete Profiler; // Eliminar el profiler
   delete ui; // Eliminar la interfaz de usuario
}
