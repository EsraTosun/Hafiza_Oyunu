#ifndef KART_H
#define KART_H

#include <QLabel>
#include <QMouseEvent>

namespace Ui { class kart; }

class MainWindow;


class kart : public QLabel
{
    Q_OBJECT
public:
    //kart();
    QVector<int> kartResimList;
    QVector<kart*> acilmisKartList;
    kart(int x,int y,MainWindow *frm,QWidget *parent = nullptr);
    kart(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void kartDagitilsin();
    void Kart_Olustur(MainWindow *frm);
    QVector<kart*> kartliste;
    MainWindow *anaFrm;
    kart *suankilabel;
    kart *oncekilabel;



private:
    Ui::kart *ui;

public slots:
    void onLabelClicked();


signals:
    void labelClicked();

};

#endif // KART_H
