#include "kart.h"
#include "mainwindow.h"

#include <QDebug>  //Konsola veri yazdırmak için
#include <QRandomGenerator>

#include <QTimer>
#include <QEventLoop>

int oncekilabelindex;
int durumSayisi = 0;
int hataSayisi = 0;
int kontrol = 0;

kart::kart(int x,int y,MainWindow *frm,QWidget *parent) : QLabel(parent)
{
    setGeometry(x, y, 180, 275);
    setFrameShape(QFrame::Box);   //Labelin çizgileri gözüksün diye
    setMouseTracking(true);   //Etiketi tıklanabilir yapın
    QImage resim(":/res/kapak.png");
    setPixmap(QPixmap::fromImage(resim));
    show();
    connect(this, SIGNAL(labelClicked()), this, SLOT(onLabelClicked()));
}

kart::kart(QWidget *parent) : QLabel(parent)
{

}


void kart::Kart_Olustur(MainWindow *frm)
{
    anaFrm = frm;
    int sira = 0;
    int x = 0;
    for(int i=0; i<10; i++)
    {
        kart*kartOlusturma;
        if(sira < 5)
        {
            kartOlusturma = new kart((120+x),200,frm,frm);
            //kartOlusturma->setGeometry((120+x), 200, 180, 275);
            //kartOlusturma->show();
            sira++;
        }
        else
        {
            kartOlusturma = new kart((120+x-1250), 600,frm,frm);
            //kartOlusturma->setGeometry((120+x-1250), 600, 180, 275);
            //kartOlusturma->show();
            sira++;
        }
        kartliste.push_back(kartOlusturma);
        x += 250;
    }
    kartDagitilsin();

    qDebug() << "AAAAAAAAAA";
    qDebug() << kartliste.length();

    // Bağlantıyı kurma
    for (int i=0;i<kartliste.length();i++) {
        QObject::connect(kartliste[i], &kart::labelClicked, [=]() {
            // Kart tıklandığında yapılacak işlemler
            qDebug() << "Tıklandı: " << kartResimList.length();
            // Diğer kartlarla karşılaştırma işlemleri burada yapılabilir

            QImage resim(":/res/"+QString::number(kartResimList[i])+".png");      //resource prefixi olduğunu belirtmek için 2 nokta koyduk
            kartliste[i]->setPixmap(QPixmap::fromImage(resim));//resim label a göre yyeniden düzenlendi

            qDebug() << "kontrolll" <<acilmisKartList.length();

            for(int j=0;j<acilmisKartList.length();j++)
            {
                if(acilmisKartList[j] == kartliste[i])
                {
                    kontrol++;
                    qDebug() << "kontrolll" <<kontrol;
                }
            }

            if(kontrol == 0)
            {
                if(durumSayisi == 0)
                {
                    qDebug() << "kartResimList";
                    qDebug() << kartResimList[i];
                    qDebug() << durumSayisi;
                    oncekilabel = kartliste[i];
                    oncekilabelindex = i;
                    durumSayisi++;
                }
                else if(durumSayisi ==1)
                {
                    QEventLoop loop;
                    QTimer timer;
                    timer.setSingleShot(true);

                    QObject::connect(&timer, &QTimer::timeout, [&]() {
                        qDebug() << "Duraklama süresi bitti, işlemlere devam ediliyor...";

                        // İkinci işlemler

                        loop.quit(); // Event loop'u sonlandır
                    });

                    // İlk işlemlerden sonra duraklama süresi (örneğin, 2 saniye)
                    int duraklamaSuresi = 500;
                    timer.start(duraklamaSuresi);

                    loop.exec(); // Event loop'u başlat

                    // Event loop'u başlat
                    qDebug() << durumSayisi;
                    suankilabel = kartliste[i];;
                    if(kartResimList[oncekilabelindex] != kartResimList[i])
                    {
                        QImage resim(":/res/kapak.png");
                        kartliste[oncekilabelindex]->setPixmap(QPixmap::fromImage(resim));
                        kartliste[i]->setPixmap(QPixmap::fromImage(resim));
                        hataSayisi++;
                        qDebug() << durumSayisi;
                        anaFrm->hataSayisiLabel->setText(QString::number(hataSayisi));
                        qDebug() << durumSayisi;
                    }
                    else
                    {
                        acilmisKartList.push_back(oncekilabel);
                        acilmisKartList.push_back(suankilabel);
                        qDebug() << "kkkkkkkkkkk" << kartliste.length();
                    }
                    durumSayisi = 0;
                }
            }
            else
            {
                kontrol = 0;
            }

        });
    }
}

void kart::kartDagitilsin()
{
    int deger = 0;
    //qDebug() <<durumSayisi;
    for(int i=0 ;i<10 ;i++){
        int sayi=QRandomGenerator::global()->bounded(5);
        for(int j=0; j<kartResimList.length(); j++){
            if(sayi == kartResimList[j]){
                deger++;
            }
        }
        if(deger == 2){
            i--;
        }
        else{
            kartResimList.push_back(sayi);
        }
        deger = 0;
    }
    for(int i=0; i<kartResimList.length();i++){
       qDebug() << kartResimList[i];
    }
    qDebug() << "KartList";
    qDebug() << kartResimList.length();
}

void kart::onLabelClicked()
{
    qDebug() << "onLabelClicked";
}


void kart:: mousePressEvent(QMouseEvent *event)
{
    emit labelClicked();
}

