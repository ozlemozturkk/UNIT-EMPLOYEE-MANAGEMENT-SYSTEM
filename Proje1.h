/*******************************************************************************************************************************
 * @file Proje1.h
 * @description Bu başlık dosyası, birimler ve çalışanlar ile ilgili veri yapılarını ve işlev prototiplerini tanımlar.
 * Programda kullanılan veri yapıları, çalışan ve birim bilgilerini saklamak için `Calisan` ve `Birim` yapılarını içerir.
 * Ayrıca, bu dosyada yer alan işlev prototipleri, `proje1.c` dosyasındaki fonksiyonlarla bağlantılıdır 
 * ve ana programın işlevlerini yerine getirebilmesi için gerekli fonksiyonların imzalarını içerir.
 * Bu başlık dosyası, programın işlevsel modüllerinin birbirleriyle uyumlu çalışabilmesi için gereklidir.
 * 
 * @assignment 1.ödev
 * @date 10.12.2024 - 23.12.2024
 * @author Özlem Öztürk 
*********************************************************************************************************************************/

#include <stdlib.h>
#define MAX_CALISAN 20
#define MAX_BIRIM 15

typedef struct 
{
char *calisanAdi ;
char *calisanSoyadi ;
unsigned short int birimKodu ;
float maas ;
int girisYili ;

}Calisan;

typedef struct
{
char *birimAdi ;
unsigned short int birimKodu ;
Calisan **birimCalisanlar ;

}Birim;

// Yeni bir çalışan oluşturur ve bilgilerini yerleştirir
Calisan* calisanOlustur(char *adi, char *soyadi, unsigned short int birimKodu, float maas, int girisYili) ;
// Yeni bir birim oluşturur ve bilgilerini yerleştirir
Birim* birimOlustur(char *birimAdi, unsigned short int birimKodu) ;
// Yeni bir birimi birim dizisine ekler
int birimDizisineBirimEkle(Birim* yeniBirim, Birim* birimDizisi[]);
// Yeni bir çalışanı ilgili birime ekler
int birimDizisineCalisanEkle(Calisan* yeniCalisan, Birim* birimDizisi[]);
// Çalışanın bilgilerini ekrana yazdırır
void printCalisan(Calisan *yeniCalisan);
// Birim bilgilerini ekrana yazdırır
void printBirim(Birim *yeniBirim);
// Birimler dizisini ekrana yazdırır
void printBirimDizi(Birim* birimDizisi[]);
// Birimdeki çalışanların maaşlarının ortalamasını hesaplar
float maasOrtalamasiHesapla(Birim *birim);
// Ortalama maaşın üzerinde maaş alan çalışanları listeye yazdırır
void ortalamaUstundekiCalisanlariListele(Birim *birim);
// Birimdeki en yüksek maaşı alan çalışanı ekrana yazdırır
void enYuksekMaasliCalisaniYazdir(Birim* birim);
// Çalışanların maaşını günceller (10 yıldan uzun süre çalışanlar için)
void maasGuncelle(Birim *birim, float yeniMaas);
// Birim ve çalışan bilgilerini dosyaya yazdırır
void tumBirimVeCalisanBilgileriniYazdir(char *birimler, char *calisanlar, Birim* birimDizisi[]);
// Birim ve çalışan bilgilerini dosyadan okur
void tumBirimVeCalisanBilgileriniOku(char *birimler, char *calisanlar, Birim *birimDizisi[]);
