/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartView>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabGeneral;
    QVBoxLayout *verticalLayoutGeneral;
    QGroupBox *groupBoxMetrics;
    QGridLayout *gridLayoutMetrics;
    QLabel *labelUsoActual;
    QLabel *labelAsignaciones;
    QLabel *labelLeaks;
    QLabel *labelMaximo;
    QLabel *labelTotalAsignaciones;
    QGroupBox *groupBoxTimeline;
    QVBoxLayout *layoutTimeline;
    QtCharts::QChartView *timelineGraph;
    QGroupBox *groupBoxResumen;
    QVBoxLayout *layoutResumen;
    QTableWidget *tableTopArchivos;
    QWidget *tabMapaMemoria;
    QVBoxLayout *verticalLayoutMapa;
    QGroupBox *groupBoxMapaMemoria;
    QVBoxLayout *layoutTablaMapa;
    QTableWidget *tableMapaMemoria;
    QWidget *tabAsignacionArchivo;
    QVBoxLayout *verticalLayoutAsignacionArchivo;
    QGroupBox *groupBoxTablaArchivos;
    QVBoxLayout *layoutTablaArchivos;
    QTableWidget *tableAsignacionesArchivo;
    QGroupBox *groupBoxGraficaArchivos;
    QVBoxLayout *layoutGraficaArchivos;
    QtCharts::QChartView *graphAsignacionesArchivo;
    QWidget *tabMemoryLeaks;
    QVBoxLayout *verticalLayoutLeaks;
    QGroupBox *groupBoxLeaksDatos;
    QGridLayout *gridLayoutLeaks;
    QLabel *labelTotalLeaks;
    QLabel *labelLeakGrande;
    QLabel *labelArchivoFrecuente;
    QLabel *labelTasaLeaks;
    QGroupBox *groupBoxLeaksGraficas;
    QHBoxLayout *layoutLeaksGraficas;
    QtCharts::QChartView *graphLeaksBarras;
    QtCharts::QChartView *graphLeaksPie;
    QtCharts::QChartView *graphLeaksTemporal;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabGeneral = new QWidget();
        tabGeneral->setObjectName("tabGeneral");
        verticalLayoutGeneral = new QVBoxLayout(tabGeneral);
        verticalLayoutGeneral->setObjectName("verticalLayoutGeneral");
        groupBoxMetrics = new QGroupBox(tabGeneral);
        groupBoxMetrics->setObjectName("groupBoxMetrics");
        gridLayoutMetrics = new QGridLayout(groupBoxMetrics);
        gridLayoutMetrics->setObjectName("gridLayoutMetrics");
        labelUsoActual = new QLabel(groupBoxMetrics);
        labelUsoActual->setObjectName("labelUsoActual");

        gridLayoutMetrics->addWidget(labelUsoActual, 0, 0, 1, 1);

        labelAsignaciones = new QLabel(groupBoxMetrics);
        labelAsignaciones->setObjectName("labelAsignaciones");

        gridLayoutMetrics->addWidget(labelAsignaciones, 1, 0, 1, 1);

        labelLeaks = new QLabel(groupBoxMetrics);
        labelLeaks->setObjectName("labelLeaks");

        gridLayoutMetrics->addWidget(labelLeaks, 2, 0, 1, 1);

        labelMaximo = new QLabel(groupBoxMetrics);
        labelMaximo->setObjectName("labelMaximo");

        gridLayoutMetrics->addWidget(labelMaximo, 3, 0, 1, 1);

        labelTotalAsignaciones = new QLabel(groupBoxMetrics);
        labelTotalAsignaciones->setObjectName("labelTotalAsignaciones");

        gridLayoutMetrics->addWidget(labelTotalAsignaciones, 4, 0, 1, 1);


        verticalLayoutGeneral->addWidget(groupBoxMetrics);

        groupBoxTimeline = new QGroupBox(tabGeneral);
        groupBoxTimeline->setObjectName("groupBoxTimeline");
        layoutTimeline = new QVBoxLayout(groupBoxTimeline);
        layoutTimeline->setObjectName("layoutTimeline");
        timelineGraph = new QtCharts::QChartView(groupBoxTimeline);
        timelineGraph->setObjectName("timelineGraph");

        layoutTimeline->addWidget(timelineGraph);


        verticalLayoutGeneral->addWidget(groupBoxTimeline);

        groupBoxResumen = new QGroupBox(tabGeneral);
        groupBoxResumen->setObjectName("groupBoxResumen");
        layoutResumen = new QVBoxLayout(groupBoxResumen);
        layoutResumen->setObjectName("layoutResumen");
        tableTopArchivos = new QTableWidget(groupBoxResumen);
        if (tableTopArchivos->columnCount() < 3)
            tableTopArchivos->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableTopArchivos->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableTopArchivos->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableTopArchivos->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableTopArchivos->setObjectName("tableTopArchivos");

        layoutResumen->addWidget(tableTopArchivos);


        verticalLayoutGeneral->addWidget(groupBoxResumen);

        tabWidget->addTab(tabGeneral, QString());
        tabMapaMemoria = new QWidget();
        tabMapaMemoria->setObjectName("tabMapaMemoria");
        verticalLayoutMapa = new QVBoxLayout(tabMapaMemoria);
        verticalLayoutMapa->setObjectName("verticalLayoutMapa");
        groupBoxMapaMemoria = new QGroupBox(tabMapaMemoria);
        groupBoxMapaMemoria->setObjectName("groupBoxMapaMemoria");
        layoutTablaMapa = new QVBoxLayout(groupBoxMapaMemoria);
        layoutTablaMapa->setObjectName("layoutTablaMapa");
        tableMapaMemoria = new QTableWidget(groupBoxMapaMemoria);
        if (tableMapaMemoria->columnCount() < 4)
            tableMapaMemoria->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableMapaMemoria->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableMapaMemoria->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableMapaMemoria->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableMapaMemoria->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        tableMapaMemoria->setObjectName("tableMapaMemoria");

        layoutTablaMapa->addWidget(tableMapaMemoria);


        verticalLayoutMapa->addWidget(groupBoxMapaMemoria);

        tabWidget->addTab(tabMapaMemoria, QString());
        tabAsignacionArchivo = new QWidget();
        tabAsignacionArchivo->setObjectName("tabAsignacionArchivo");
        verticalLayoutAsignacionArchivo = new QVBoxLayout(tabAsignacionArchivo);
        verticalLayoutAsignacionArchivo->setObjectName("verticalLayoutAsignacionArchivo");
        groupBoxTablaArchivos = new QGroupBox(tabAsignacionArchivo);
        groupBoxTablaArchivos->setObjectName("groupBoxTablaArchivos");
        layoutTablaArchivos = new QVBoxLayout(groupBoxTablaArchivos);
        layoutTablaArchivos->setObjectName("layoutTablaArchivos");
        tableAsignacionesArchivo = new QTableWidget(groupBoxTablaArchivos);
        if (tableAsignacionesArchivo->columnCount() < 3)
            tableAsignacionesArchivo->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableAsignacionesArchivo->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableAsignacionesArchivo->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableAsignacionesArchivo->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        tableAsignacionesArchivo->setObjectName("tableAsignacionesArchivo");

        layoutTablaArchivos->addWidget(tableAsignacionesArchivo);


        verticalLayoutAsignacionArchivo->addWidget(groupBoxTablaArchivos);

        groupBoxGraficaArchivos = new QGroupBox(tabAsignacionArchivo);
        groupBoxGraficaArchivos->setObjectName("groupBoxGraficaArchivos");
        layoutGraficaArchivos = new QVBoxLayout(groupBoxGraficaArchivos);
        layoutGraficaArchivos->setObjectName("layoutGraficaArchivos");
        graphAsignacionesArchivo = new QtCharts::QChartView(groupBoxGraficaArchivos);
        graphAsignacionesArchivo->setObjectName("graphAsignacionesArchivo");

        layoutGraficaArchivos->addWidget(graphAsignacionesArchivo);


        verticalLayoutAsignacionArchivo->addWidget(groupBoxGraficaArchivos);

        tabWidget->addTab(tabAsignacionArchivo, QString());
        tabMemoryLeaks = new QWidget();
        tabMemoryLeaks->setObjectName("tabMemoryLeaks");
        verticalLayoutLeaks = new QVBoxLayout(tabMemoryLeaks);
        verticalLayoutLeaks->setObjectName("verticalLayoutLeaks");
        groupBoxLeaksDatos = new QGroupBox(tabMemoryLeaks);
        groupBoxLeaksDatos->setObjectName("groupBoxLeaksDatos");
        gridLayoutLeaks = new QGridLayout(groupBoxLeaksDatos);
        gridLayoutLeaks->setObjectName("gridLayoutLeaks");
        labelTotalLeaks = new QLabel(groupBoxLeaksDatos);
        labelTotalLeaks->setObjectName("labelTotalLeaks");

        gridLayoutLeaks->addWidget(labelTotalLeaks, 0, 0, 1, 1);

        labelLeakGrande = new QLabel(groupBoxLeaksDatos);
        labelLeakGrande->setObjectName("labelLeakGrande");

        gridLayoutLeaks->addWidget(labelLeakGrande, 1, 0, 1, 1);

        labelArchivoFrecuente = new QLabel(groupBoxLeaksDatos);
        labelArchivoFrecuente->setObjectName("labelArchivoFrecuente");

        gridLayoutLeaks->addWidget(labelArchivoFrecuente, 2, 0, 1, 1);

        labelTasaLeaks = new QLabel(groupBoxLeaksDatos);
        labelTasaLeaks->setObjectName("labelTasaLeaks");

        gridLayoutLeaks->addWidget(labelTasaLeaks, 3, 0, 1, 1);


        verticalLayoutLeaks->addWidget(groupBoxLeaksDatos);

        groupBoxLeaksGraficas = new QGroupBox(tabMemoryLeaks);
        groupBoxLeaksGraficas->setObjectName("groupBoxLeaksGraficas");
        layoutLeaksGraficas = new QHBoxLayout(groupBoxLeaksGraficas);
        layoutLeaksGraficas->setObjectName("layoutLeaksGraficas");
        graphLeaksBarras = new QtCharts::QChartView(groupBoxLeaksGraficas);
        graphLeaksBarras->setObjectName("graphLeaksBarras");

        layoutLeaksGraficas->addWidget(graphLeaksBarras);

        graphLeaksPie = new QtCharts::QChartView(groupBoxLeaksGraficas);
        graphLeaksPie->setObjectName("graphLeaksPie");

        layoutLeaksGraficas->addWidget(graphLeaksPie);

        graphLeaksTemporal = new QtCharts::QChartView(groupBoxLeaksGraficas);
        graphLeaksTemporal->setObjectName("graphLeaksTemporal");

        layoutLeaksGraficas->addWidget(graphLeaksTemporal);


        verticalLayoutLeaks->addWidget(groupBoxLeaksGraficas);

        tabWidget->addTab(tabMemoryLeaks, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Memory Profiler", nullptr));
        groupBoxMetrics->setTitle(QCoreApplication::translate("MainWindow", "M\303\251tricas Generales", nullptr));
        labelUsoActual->setText(QCoreApplication::translate("MainWindow", "Uso actual de memoria: 0 MB", nullptr));
        labelAsignaciones->setText(QCoreApplication::translate("MainWindow", "Asignaciones activas: 0", nullptr));
        labelLeaks->setText(QCoreApplication::translate("MainWindow", "Memory leaks: 0 MB", nullptr));
        labelMaximo->setText(QCoreApplication::translate("MainWindow", "Uso m\303\241ximo: 0 MB", nullptr));
        labelTotalAsignaciones->setText(QCoreApplication::translate("MainWindow", "Total asignaciones: 0", nullptr));
        groupBoxTimeline->setTitle(QCoreApplication::translate("MainWindow", "L\303\255nea de Tiempo", nullptr));
        groupBoxResumen->setTitle(QCoreApplication::translate("MainWindow", "Resumen (Top 3 archivos con mayores asignaciones)", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableTopArchivos->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Archivo", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableTopArchivos->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Asignaciones", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableTopArchivos->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Memoria (MB)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabGeneral), QCoreApplication::translate("MainWindow", "General", nullptr));
        groupBoxMapaMemoria->setTitle(QCoreApplication::translate("MainWindow", "Bloques de Memoria Asignados", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableMapaMemoria->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Direcci\303\263n", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableMapaMemoria->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Tipo de Dato", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableMapaMemoria->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Tama\303\261o (Bytes)", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableMapaMemoria->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Estado", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabMapaMemoria), QCoreApplication::translate("MainWindow", "Mapa de Memoria", nullptr));
        groupBoxTablaArchivos->setTitle(QCoreApplication::translate("MainWindow", "Asignaciones por Archivo Fuente", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableAsignacionesArchivo->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Archivo", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableAsignacionesArchivo->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Conteo de Asignaciones", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableAsignacionesArchivo->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Total Memoria (MB)", nullptr));
        groupBoxGraficaArchivos->setTitle(QCoreApplication::translate("MainWindow", "Gr\303\241fica de Asignaciones", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabAsignacionArchivo), QCoreApplication::translate("MainWindow", "Asignaci\303\263n por Archivo", nullptr));
        groupBoxLeaksDatos->setTitle(QCoreApplication::translate("MainWindow", "Resumen de Memory Leaks", nullptr));
        labelTotalLeaks->setText(QCoreApplication::translate("MainWindow", "Total memoria fugada: 0 MB", nullptr));
        labelLeakGrande->setText(QCoreApplication::translate("MainWindow", "Leak m\303\241s grande: 0 MB (archivo: ---)", nullptr));
        labelArchivoFrecuente->setText(QCoreApplication::translate("MainWindow", "Archivo con m\303\241s leaks: ---", nullptr));
        labelTasaLeaks->setText(QCoreApplication::translate("MainWindow", "Tasa de leaks: 0%", nullptr));
        groupBoxLeaksGraficas->setTitle(QCoreApplication::translate("MainWindow", "Visualizaci\303\263n de Leaks", nullptr));
#if QT_CONFIG(tooltip)
        graphLeaksBarras->setToolTip(QCoreApplication::translate("MainWindow", "Gr\303\241fico de barras por archivo", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        graphLeaksPie->setToolTip(QCoreApplication::translate("MainWindow", "Gr\303\241fico de pastel distribuci\303\263n de leaks", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        graphLeaksTemporal->setToolTip(QCoreApplication::translate("MainWindow", "Gr\303\241fico temporal detecci\303\263n de leaks", nullptr));
#endif // QT_CONFIG(tooltip)
        tabWidget->setTabText(tabWidget->indexOf(tabMemoryLeaks), QCoreApplication::translate("MainWindow", "Memory Leaks", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
