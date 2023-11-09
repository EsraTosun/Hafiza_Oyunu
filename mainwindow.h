#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "kart.h"   //Kart sınıfından kart listesine Mainde erişeceğim için burada tanımlarım

class kart;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *zaman;
    QLabel *hataSayisiLabel;
    QLabel *yaziLabel;

private:
    Ui::MainWindow *ui;
    void Kart_Olustur();
    void Kart_Dagitilsin();
    QVector<kart*> acilmisKartMain;
    kart *kartclass;
    QLabel *textLabel;

};
#endif // MAINWINDOW_H
