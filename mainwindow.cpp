#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>


#include "kart.h"
#include <QDebug>  //Konsola veri yazdırmak için


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    kartclass = new kart(this);
    showMaximized();   //Formu tam ekran aç
    //Kart_Olustur();

    yaziLabel=new QLabel(this);
    QFont font = yaziLabel->font();
    font.setPointSize(16);
    yaziLabel->setFont(font);
    yaziLabel->setGeometry(280, 1010, 400, 50);
    yaziLabel->setText("Başarısız Tahmin Sayısı:");
    yaziLabel->setStyleSheet("color : purple");
    yaziLabel->show();

    hataSayisiLabel=new QLabel(this);
    font.setPointSize(16);
    hataSayisiLabel->setFont(font);
    hataSayisiLabel->setGeometry(850, 1010, 400, 50);
    hataSayisiLabel->setText("0");
    hataSayisiLabel->setStyleSheet("color : red");
    hataSayisiLabel->show();

    kartclass->Kart_Olustur(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

