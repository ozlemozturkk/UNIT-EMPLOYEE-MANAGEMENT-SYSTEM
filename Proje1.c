/*******************************************************************************************************************************
 * @file proje1.c
 * @description Bu dosya, birim ve çalışanlarla ilgili verilerin yönetilmesini sağlayan temel işlevleri içermektedir.
 * Program, birimlerin ve çalışanların oluşturulması, birim ve çalışan bilgileri ekleme, listeleme,
 * maaş ortalamasını hesaplama, maaş güncelleme gibi işlemleri gerçekleştiren fonksiyonları barındırmaktadır. 
 * Ayrıca, dosyadan veri okuma ve yazma işlemleri de yapılmaktadır. Bu dosyada tanımlı olan fonksiyonlar,
 * ana programın işlevlerini yerine getirebilmesi için gerekli olan tüm veri yapılarını ve işlemleri içerir.
 * 
 * @assignment 1.ödev
 * @date 10.12.2024 - 23.12.2024
 * @author Özlem Öztürk , ozlem.ozturk@stu.fsm.edu.tr 

*********************************************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Proje1.h"

//1.MADDE
Birim* birimOlustur(char *birimAdi, unsigned short int birimKodu) {
        // Birim yapısı için heap'te yer ayırdım.
    Birim *yeniBirim = (Birim*)malloc(sizeof(Birim));
    if (yeniBirim==NULL) {
         printf("BELLEK TAHSISI BASARISIZ.\n");// Bellek tahsisi başarısızsa hata mesajı yazdırdım
        return NULL;
    }

    yeniBirim->birimAdi = (char*)malloc(30 * sizeof(char));    // Birim adı için bellek tahsisi yaptım.

    if (yeniBirim->birimAdi==NULL) {
         printf("BIRIM ADI ICIN BELLEK TAHSISI BASARISIZ.\n");
        free(yeniBirim); // Önceden tahsis edilen bellek serbest bırakılır.Eğer serbest bırakılmazsa yeniBirim kullanılamaz.
        return NULL;
    }

    strcpy(yeniBirim->birimAdi, birimAdi);    // Girilen birim adı, tahsis edilen belleğe kopyaladım.

    yeniBirim->birimKodu = birimKodu;    // Birim kodu atadım.

    yeniBirim->birimCalisanlar = (Calisan**)calloc(MAX_CALISAN, sizeof(Calisan*));    // Çalışanlar dizisini dinamik olarak heap'te tuttum

    if (!yeniBirim->birimCalisanlar) {
         printf("CALISANLAR DIZISI ICIN BELLEK TAHSISI BASARISIZ.\n");
        free(yeniBirim->birimAdi);//Önceden tahsis edilen bellek serbest bırakılır.
        free(yeniBirim);//Birim yapısı belleği serbest bırakılır
        return NULL;
    }

    return yeniBirim;    // Başarıyla oluşturulan birim yapısı döndürülüyor

}

//2.MADDE
Calisan* calisanOlustur(char *adi, char *soyadi, unsigned short int birimKodu, float maas, int girisYili) {
    Calisan *yeniCalisan = (Calisan*)malloc(sizeof(Calisan));    // Yeni bir çalışan için bellekte yer ayırdım
    if (yeniCalisan == NULL) {
        printf("BELLEK TAHSİSİ BASARİSİZ.\n");   // Bellek tahsisi başarısız olursa durumu bildiriyorum ve NULL döndürüyorum

        return NULL;
    }

    // Çalışanın adı ve soyadı için 30 karakterlik bellek ayırdım
    yeniCalisan->calisanAdi = (char*)malloc(30 * sizeof(char));
    yeniCalisan->calisanSoyadi = (char*)malloc(30 * sizeof(char));

    // Eğer ad veya soyad için bellek tahsisi başarısız olursa, çalışanı serbest bırakıyorum
    if (yeniCalisan->calisanAdi == NULL || yeniCalisan->calisanSoyadi == NULL) {
         printf("CALISAN ADI VE SOYADI ICIN BELLEK TAHSISI BASARISIZ.\n");
          free(yeniCalisan);// Çalışan yapısını serbest bıraktım
        return NULL;
    }
    // Ad ve soyadı için gelen parametreleri belleğe kopyaladım 
    strcpy(yeniCalisan->calisanAdi, adi);
    strcpy(yeniCalisan->calisanSoyadi, soyadi);
    // Diğer çalışan bilgilerini yapıdaki ilgili değişkenlere atadım
    yeniCalisan->birimKodu = birimKodu;
    yeniCalisan->maas = maas;
    yeniCalisan->girisYili = girisYili;
    // Oluşturduğum yeni çalışanı geri döndürüyorum
    return yeniCalisan;
}

//3.MADDE
int birimDizisineBirimEkle(Birim* yeniBirim, Birim* birimDizisi[]) {
        // Birim dizisini tarıyorum
    for (size_t i = 0; i < MAX_BIRIM; i++) {
        // Eğer boş bir yer bulursam yeni birimi buraya ekliyorum
        if (birimDizisi[i] == NULL) {
            birimDizisi[i] = yeniBirim;
            printf("BIRIM BASARIYLA EKLENDI.\n");
            return 1;  // Eklenme başarılı, 1 döndürüyorum
        }
    }
      // Eğer dizide boş yer yoksa 0 döndürüyorum
    return 0; 
}

//3.MADDE
// Çalışanı birim dizisine ekleyen fonksiyon oluşturdum.
int birimDizisineCalisanEkle(Calisan* yeniCalisan, Birim* birimDizisi[]) {
    // Öncelikle çalışanın geçerli olup olmadığını kontrol ediyorum
    if (yeniCalisan == NULL) {
        printf("GECERSIZ CALISAN.\n");
        return 0;  // Geçersiz çalışan durumu sıfır döndürüyorum.
    }

    // Birim dizisini tarıyorum
    for (size_t i = 0; i < MAX_BIRIM; i++) {
        // Geçerli bir birim olup olmadığını ve birim kodunun eşleşip eşleşmediğini kontrol ediyorum
        if (birimDizisi[i] != NULL && birimDizisi[i]->birimKodu == yeniCalisan->birimKodu) {
            // Eşleşen birim bulunduysa çalışan dizisini tarıyorum
            for (int j = 0; j < MAX_CALISAN; j++) {
                // Eğer dizide boş bir yer bulursam yeni çalışanı buraya ekliyorum
                if (birimDizisi[i]->birimCalisanlar[j] == NULL) {
                    birimDizisi[i]->birimCalisanlar[j] = yeniCalisan;
                    printf("CALISAN BASARIYLA EKLENDI.\n");
                    return 1;  // Eklenme başarılı, 1 döndürüyorum
                }
            }
            // Eğer birim çalışan dizisi doluysa bunu bildiriyorum
            printf("BIRIMIN CALISAN DIZISI DOLU.\n");
            return 0;
        }
    }

    printf("GECERLI BIR BIRIM BULUNAMADI.\n");
    return 0;  // Çalışan eklenemedi
}

//4.MADDE
void printCalisan(Calisan *yeniCalisan) {
    // Eğer çalışan bilgisi NULL ise ekrana bilgi bulunmadığını yazdırıyorum
    if (yeniCalisan == NULL) {
        printf("CALISAN BILGISI MEVCUT DEGIL.\n");
        return;
    }
    // Çalışan bilgilerini düzenli bir formatta ekrana yazdırıyorum
    printf("\n--------------------------- CALISAN BILGISI ----------------------------\n");
    printf("CALISAN ADI: %s\n", yeniCalisan->calisanAdi);
    printf("CALISAN SOYADI: %s\n", yeniCalisan->calisanSoyadi);
    printf("CALISANIN BIRIM KODU: %d\n", yeniCalisan->birimKodu);
    printf("CALISANIN MAASI: %.2f\n", yeniCalisan->maas);
    printf("CALISANIN GIRIS YILI: %d\n", yeniCalisan->girisYili);
    printf("------------------------------------------------------------------------\n\n");

}

//5.MADDE
void printBirim(Birim *yeniBirim) {
    // Eğer birim bilgisi NULL ise ekrana bilgi bulunmadığını yazdırıyorum
    if (yeniBirim == NULL) {
        printf("BIRIM BILGISI MEVCUT DEGIL.\n");
        return;
    }
    // Birim bilgilerini düzenli bir formatta ekrana yazdırıyorum
    printf("\n------------------------ BIRIM BILGISI ----------------------------\n");
    printf("BIRIM ADI: %s\n", yeniBirim->birimAdi);
    printf("BIRIM KODU: %d\n", yeniBirim->birimKodu);

    // Birimdeki çalışanların bilgilerini yazdırıyorum
    printf("BIRIMDEKI CALISANLAR:\n");
    int calisanSayisi = 0; // Çalışan sayısını takip etmek için bir sayaç
    for (size_t i = 0; i < MAX_CALISAN; i++) {
        if (yeniBirim->birimCalisanlar[i] != NULL) {
            // Burada her çalışanın ait olduğu birime göre bilgi yazdırıyorum.
            printf(" - %s %s\n", yeniBirim->birimCalisanlar[i]->calisanAdi, yeniBirim->birimCalisanlar[i]->calisanSoyadi) ;
            calisanSayisi++; // Her çalışan için sayaç bir artırılıyor
        }
    }
     // Eğer çalışan bulunamazsa uygun bir mesaj yazdırıyorum
    if (calisanSayisi == 0) {
        printf("BIRIMDE KAYITLI HIC CALISAN BULUNMAMAKTADIR.\n");
    }

    printf("------------------------------------------------------------------------\n");
}

//6.MADDE
int yazdirilmis[MAX_BIRIM] = {0}; // Başlangıçta tüm elemanları 0 olarak ayarlıyorum; henüz yazdırılmamış.

// Birim dizisinin içeriğini yazdıran fonksiyon
void printBirimDizi(Birim *birimDizisi[]) {
    printf("\nBIRIM DIZISI ICERIGI:\n");
    for (int i = 0; i < MAX_BIRIM; i++) {
        if (birimDizisi[i] != NULL) { // Birim dizisinde geçerli bir birim var mı kontrol ediyorum.
            if (!yazdirilmis[i]) { // Eğer bu birim daha önce yazdırılmadıysa...
                printf("\n------------------------ BIRIM BILGISI ----------------------------\n");
                printf("BIRIM ADI: %s\n", birimDizisi[i]->birimAdi);
                printf("BIRIM KODU: %hu\n", birimDizisi[i]->birimKodu);
            
                printf("\nBIRIMDEKI CALISANLAR:\n");
                int calisanSayisi = 0;
                for (int j = 0; j < MAX_CALISAN; j++) {
                    if (birimDizisi[i]->birimCalisanlar[j] != NULL) { 
                        // Çalışan bilgilerini ekrana yazdırıyorum.
                        calisanSayisi++;
                        printf(" CALISAN ADI : %s %s, MAASI : %.2f, GIRIS YILI: %d\n",
                               birimDizisi[i]->birimCalisanlar[j]->calisanAdi,
                               birimDizisi[i]->birimCalisanlar[j]->calisanSoyadi,
                               birimDizisi[i]->birimCalisanlar[j]->maas,
                               birimDizisi[i]->birimCalisanlar[j]->girisYili);
                    }
                }
                if (calisanSayisi == 0) {
                    // Eğer birimde hiç çalışan yoksa bunu belirtiyorum.
                    printf("BIRIMDE KAYITLI HIC CALISAN BULUNMAMAKTADIR.\n");
                }

                yazdirilmis[i] = 1; // Bu birimi yazdırdığımı işaretliyorum.

                printf("------------------------------------------------------------------------\n");
            }
        }
    }
}


//7.MADDE
float maasOrtalamasiHesapla(Birim *birim) {
        // Eğer birim NULL veya çalışanlar NULL ise geçersiz birim bilgisi uyarısı veriyorum
    if (birim == NULL || birim->birimCalisanlar == NULL) {
        printf("GECERSIZ BIRIM BILGISI.\n");
        return 0.0;
    }

    int toplamCalisan = 0;// Çalışan sayısını takip eden sayaç oluşturdum.
    float toplamMaas = 0.0;// Toplam maaşı takip eden değişken oluşturdum.

    // Birimdeki her çalışanın maaşını topluyorum
    for (int i = 0; i < MAX_CALISAN; i++) {
        if (birim->birimCalisanlar[i] != NULL) {
            toplamCalisan++;// Çalışan sayısını artırıyorum
            toplamMaas += birim->birimCalisanlar[i]->maas;// Çalışanın maaşını ekliyorum
        }
    }
    // Eğer birimde çalışan yoksa mesaj veriyorum
    if (toplamCalisan == 0) {
    printf("%s BIRIMINDE HIC CALISAN BULUNMAMAKTADIR. BU YUZDEN ORTALAMA HESAPLANAMADI...\n", birim->birimAdi);
        return 0.0;
    }
    // Maaş ortalamasını hesaplayıp döndürüyorum
    return toplamMaas / toplamCalisan;
}

//8.MADDE
void ortalamaUstundekiCalisanlariListele(Birim* birim) {
    // Eğer birim NULL veya birimdeki çalışanlar NULL ise geçersiz birim bilgisi uyarısı veriyorum
    if (birim == NULL || birim->birimCalisanlar == NULL) {
        printf("GECERSIZ BIRIM BILGISI.\n");
        return;
    }

    // Birimin maaş ortalamasını hesaplıyorum
    float ortalamaMaas = maasOrtalamasiHesapla(birim);

    // Eğer maaş ortalaması sıfırsa (hiç çalışan yoksa veya maaş bilgisi yoksa), mesaj veriyorum
    if (ortalamaMaas == 0.0) {
        printf("BIRIMDE HIC CALISAN YOK YA DA MAAS BILGISI MEVCUT DEGIL.\n");
        return;
    }

    int found = 0;  // Ortalama maaş üstü çalışan bulunup bulunmadığını kontrol etmek için sayaç

    // Ortalama maaşın üstünde maaş alan çalışanları listelemeye başlıyorum
    printf("\n------------------ ORTALAMA USTU MAAS ALAN CALISANLAR ------------------\n");
    printf("\nBIRIM: %-30s | ORTALAMA MAAS: %.2f\n", birim->birimAdi, ortalamaMaas);
    printf("************************************************************************\n");

    // Maaşı ortalama maaş üstü olan çalışanları arıyorum
    for (int i = 0; i < MAX_CALISAN; i++) {
        if (birim->birimCalisanlar[i] != NULL && birim->birimCalisanlar[i]->maas > ortalamaMaas) {
            // Çalışanın bilgilerini yazdırıyorum
            printf("| %-20s | %-20s | %-10.2f |\n",
                   birim->birimCalisanlar[i]->calisanAdi,
                   birim->birimCalisanlar[i]->calisanSoyadi,
                   birim->birimCalisanlar[i]->maas);
            found = 1; // Ortalama maaş üstü çalışan bulundu
        }
    }

    // Eğer maaşı ortalama maaş üstü çalışan bulunmazsa
    if (!found) {
        printf("\nBU BIRIMDE ORTALAMA MAAS USTU CALISAN BULUNMAMAKTADIR.\n");
    }

    printf("************************************************************************\n\n");
}

//9.MADDE
void enYuksekMaasliCalisaniYazdir(Birim* birim) {
        // Eğer birim NULL ise geçersiz birim bilgisi uyarısı veriyorum
    if (birim == NULL) {
        printf("GECERSIZ BIRIM BILGISI.\n");
        return;
    }

    Calisan* enYuksekMaasli = NULL; // En yüksek maaşlı çalışanı tutacak işaretçi
    float enYuksekMaas = -1; // En yüksek maaş başlangıçta -1 olarak belirliyorum
    
    // Birimdeki tüm çalışanları kontrol ediyorum
    for (size_t i = 0; i < MAX_CALISAN; i++) {
        if (birim->birimCalisanlar[i] != NULL) {
            // Eğer mevcut çalışanın maaşı en yüksek maaştan büyükse, en yüksek maaşlıyı güncelliyorum
            if (birim->birimCalisanlar[i]->maas > enYuksekMaas) {
                enYuksekMaas = birim->birimCalisanlar[i]->maas;
                enYuksekMaasli = birim->birimCalisanlar[i];
            }
        }
    }

    // En yüksek maaşlı çalışan bulunduysa bilgilerini yazdırıyorum
    if (enYuksekMaasli != NULL) {
        printf("\n------------------------ EN YUKSEK MAASLI CALISAN ----------------------\n");
        printf("BIRIM ADI: %s\n", birim->birimAdi);
        printf("CALISAN ADI: %s\n", enYuksekMaasli->calisanAdi);
        printf("CALISAN SOYADI: %s\n", enYuksekMaasli->calisanSoyadi);
        printf("BIRIM KODU: %d\n", birim->birimKodu);
        printf("MAAS: %.2f\n", enYuksekMaasli->maas);
        printf("-------------------------------------------------------------------------\n\n");
            // Eğer birimde çalışan yoksa, bu durumu belirtiyorum
    } else {
        printf("BU BIRIMDE KAYITLI CALISAN BULUNMAMAKTADIR.\n\n");
    }
}

//10.MADDE
void maasGuncelle(Birim *birim, float yeniMaas) {
    // Eğer birim veya birimdeki çalışanlar NULL ise geçersiz birim bilgisi uyarısı veriyorum
    if (birim == NULL || birim->birimCalisanlar == NULL) {
        printf("GECERSIZ BIRIM BILGISI.\n");
        return;
    }

    int maasGuncellendi = 0;  // Maaş güncellenen çalışanın olup olmadığını takip eden değişken
    int calisanVarMi = 0;  // 10 yıldan fazla çalışan var mı kontrolü için değişken

    // Birimdeki her çalışanın maaşını kontrol ediyorum
    for (size_t i = 0; i < MAX_CALISAN; i++) {
        // Eğer çalışan mevcutsa, maaş güncelleme koşulunu kontrol ediyorum
        if (birim->birimCalisanlar[i] != NULL) {
            // Eğer çalışanın işe giriş yılı 10 yıldan fazla ise maaşını güncelliyorum
            if (2024 - birim->birimCalisanlar[i]->girisYili > 10) {
                calisanVarMi = 1;  // Çalışan var
                // Eğer mevcut maaş, yeni maaştan küçükse, maaşı güncelliyorum
                if (birim->birimCalisanlar[i]->maas < yeniMaas) {
                    birim->birimCalisanlar[i]->maas = yeniMaas;
                    // Maaş güncellenen çalışanın bilgilerini yazdırıyorum
                    printf("\nCALISANIN MAASI GUNCELLENDI: %s %s, YENI MAAS: %.2f\n\n",
                           birim->birimCalisanlar[i]->calisanAdi, birim->birimCalisanlar[i]->calisanSoyadi, yeniMaas);
                            maasGuncellendi = 1;
                }
            }
        }
    }

    // Eğer 10 yıldan fazla çalışan yoksa, kullanıcıyı bilgilendiriyoruz
    if (!calisanVarMi) {
        printf("BIRIMDE 10 YILDAN FAZLA CALISAN BULUNMAMAKTADIR.\n");
    }

    // Eğer maaşı güncellenen bir çalışan yoksa, kullanıcıyı bilgilendiriyoruz
    if (calisanVarMi && !maasGuncellendi) {
        printf("VERILEN MAASTAN DUSUK MAASI OLAN CALISAN YOK.\n");
    }
}

//11.MADDE
void tumBirimVeCalisanBilgileriniYazdir(char *birimler, char *calisanlar, Birim* birimDizisi[]) {
    // Birim ve çalışan bilgilerini yazacağımız dosyaları açıyorum
    FILE *birimlerdosyasi = fopen(birimler, "a");
    FILE *calisanlardosyasi = fopen(calisanlar, "a");

    // Dosyalar açılmazsa hata mesajı veriyorum
    if (birimlerdosyasi == NULL || calisanlardosyasi == NULL) {
        printf("DOSYA OLUSTURULAMADI.\n");
        return;  // exit yerine return kullanmak daha iyi olabilir
    }

    // Birim bilgilerini dosyaya yazıyorum
    size_t i = 0;
    while (birimDizisi[i] != NULL) {
        fprintf(birimlerdosyasi, "%s %d\n", birimDizisi[i]->birimAdi , birimDizisi[i]->birimKodu);
        i++;
    }

    // Her birimdeki çalışan bilgilerini dosyaya yazıyorum
    for (size_t j = 0; j < i; j++) {  
        for (size_t k = 0; k < MAX_CALISAN; k++) {
            // Eğer çalışanın bilgileri mevcutsa, çalışan bilgilerini dosyaya yazıyorum
            if (birimDizisi[j]->birimCalisanlar[k] != NULL) {
                fprintf(calisanlardosyasi, "%s %s %d %.2f %d\n", 
                    birimDizisi[j]->birimCalisanlar[k]->calisanAdi,
                    birimDizisi[j]->birimCalisanlar[k]->calisanSoyadi,
                    birimDizisi[j]->birimCalisanlar[k]->birimKodu,
                    birimDizisi[j]->birimCalisanlar[k]->maas,
                    birimDizisi[j]->birimCalisanlar[k]->girisYili);
            }
        }
    }

    // Dosyaları kapatıyorum
    fclose(birimlerdosyasi);
    fclose(calisanlardosyasi);

    // Bilgilerin başarıyla dosyaya yazıldığını bildiriyorum
    printf("\n\nBIRIMLER VE CALISANLAR DOSYAYA YAZILDI.\n\n");
}

//12.MADDE
void tumBirimVeCalisanBilgileriniOku(char *birimler, char *calisanlar, Birim *birimDizisi[]) {
    // Birim ve çalışan dosyalarını açıyorum
    FILE *birimlerFile = fopen(birimler, "r");
    FILE *calisanlarFile = fopen(calisanlar, "r");

    // Dosya açılamazsa hata mesajı veriyorum ve fonksiyondan çıkıyorum
    if (birimlerFile == NULL || calisanlarFile == NULL) {
        printf("DOSYA ACILAMADI! BIRIM DOSYASI: %s, CALISAN DOSYASI: %s\n", birimler, calisanlar);
        return;
    }

    // Dosyaların başarıyla açıldığını bildiriyorum
    printf("\nBIRIMLER DOSYASI '%s' VE CALISANLAR DOSYASI '%s' BASARIYLA ACILDI.\n", birimler, calisanlar);
    printf("-----------------------------------------------------------------------------------------------------\n");

    char birimAdi[30];
    unsigned short birimKodu;

    // Birimler dosyasını okurken döngü başlatıyorum
    while (fscanf(birimlerFile, "%s %hu", birimAdi, &birimKodu) == 2) {
        // Okunan birimi ekrana yazdırıyorum
        printf("BIRIM OKUNUYOR: ADI = %s, KODU = %hu\n", birimAdi, birimKodu);

        // Yeni bir Birim nesnesi oluşturuyorum
        Birim *newBirim = birimOlustur(birimAdi, birimKodu);
        if (newBirim == NULL) {
            // Bellek tahsisi başarısız olursa dosyaları kapatıp çıkıyorum
            printf("BELLEK TAHSISI BASARISIZ.");
            fclose(birimlerFile);
            fclose(calisanlarFile);
            return;
        }

        // Çalışanları eklemek için çalışan dosyasını baştan okuma
        fseek(calisanlarFile, 0, SEEK_SET);

        char calisanAdi[30], calisanSoyadi[30];
        unsigned short int calisanBirimKodu;
        float calisanMaasi;
        int calisanGirisYili;

        int calisanSayisi = 0;
        // Çalışanlar dosyasını okurken döngü başlatıyorum
        while (fscanf(calisanlarFile, "%s %s %hu %f %d", calisanAdi, calisanSoyadi, &calisanBirimKodu, &calisanMaasi, &calisanGirisYili) == 5) {
            // Çalışan, doğru birime aitse ekliyorum
            if (calisanBirimKodu == newBirim->birimKodu) {
                printf("CALISAN OKUNUYOR: ADI = %s , SOYADI = %s, BIRIM KODU = %hu, MAAS = %.2f, GIRIS YILI = %d\n", 
                    calisanAdi, calisanSoyadi, calisanBirimKodu, calisanMaasi, calisanGirisYili);
                
                // Yeni bir Calisan nesnesi oluşturuyorum
                Calisan *newCalisan = calisanOlustur(calisanAdi, calisanSoyadi, calisanBirimKodu, calisanMaasi, calisanGirisYili);
                if (newCalisan == NULL) {
                    // Bellek tahsisi başarısız olursa dosyaları kapatıp çıkıyorum
                    printf("BELLEK TAHSISI BASARISIZ.");
                    fclose(birimlerFile);
                    fclose(calisanlarFile);
                    return;
                }

                // Birimdeki çalışan sayısı kontrol ediyorum ve çalışanı ekliyorum
                if (calisanSayisi < MAX_CALISAN) {
                    newBirim->birimCalisanlar[calisanSayisi++] = newCalisan;
                } else {
                    // Birimdeki çalışan kapasitesi dolmuşsa uyarı veriyorum
                    printf("BIRIMDEKI CALISANLARIN KAPASITESI DOLDU!\n");
                    free(newCalisan);  // Belleği serbest bırak
                }
            }
        }

        // Yeni birimi, birim dizisine ekliyorum
        for (int i = 0; i < MAX_BIRIM; i++) {
            if (birimDizisi[i] == NULL) {  // Eğer bu index boşsa
                birimDizisi[i] = newBirim;  // Yeni birimi ekle
                printf("BIRIM DIZISINE EKLENDI.\n");
                break;  // Döngüden çık
            }
        }

        printf("-----------------------------------------------------------------------------------------------------\n");
    }

    // Dosyaları kapatıyorum
    fclose(birimlerFile);
    fclose(calisanlarFile);
}
