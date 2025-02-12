/*******************************************************************************************************************************
 * @file main.c
 * @description Bu dosya, birimler ve çalışanlarla ilgili işlemleri gerçekleştiren bir C programını içermektedir.
 * Program, kullanıcıya birimler ekleme, çalışanlar ekleme, listeleme, maaş hesaplama ve güncelleme,
 * en yüksek maaşlı çalışanları listeleme gibi çeşitli işlemler sunmaktadır. 
 * Ayrıca, kullanıcıdan aldığı verilerle bu işlemleri gerçekleştirdikten sonra, birimler ve çalışanlarla 
 * ilgili bilgileri dosyaya yazdırabilir veya dosyadan okuyabilir.
 * 
 * @assignment 1.ödev
 * @date 10.12.2024 - 23.12.2024
 * @author Özlem Öztürk , ozlem.ozturk@stu.fsm.edu.tr 
 *********************************************************************************************************************************/



#include "Proje1.h"
#include <stdio.h>


int main(int argc, char *argv[]) {
        // Komut satırından dosya adlarının alındığını kontrol ettim
    if (argc != 3) {
        printf("LUTFEN DOSYA ADLARINI KOMUT SATIRINDAN GIRIN: birimler.txt calisanlar.txt\n");
        return 1;// Yanlış parametre sayısı ile programı sonlandırmasını sağladım.
    }
    // Komut satırından alınan dosya isimlerini değişkenlere atadım.
    char *birimlerDosyaAdi = argv[1];
    char *calisanlarDosyaAdi = argv[2]; 

    printf("\nBIRIMLER DOSYASI: %s\n", birimlerDosyaAdi);
    printf("CALISANLAR DOSYASI: %s\n", calisanlarDosyaAdi);

    // Birim dizisi için dinamik bir dizi olarak heap'te tuttum.
     Birim** birimDizisi = (Birim**)malloc(MAX_BIRIM * sizeof(Birim*));
    if (birimDizisi == NULL) {
        printf("BIRIM DIZISI ICIN BELLEK TAHSISI BASARISIZ.\n");
        return 1;// Bellek tahsisi başarısızsa programı sonlandırmasını sağladım.
    }
    // Birim dizisini başta NULL olarak doldurdum .
    for (int i = 0; i < MAX_BIRIM; i++) {
        birimDizisi[i] = NULL;
    }
        // Ana menü ve işlem seçim döngüsüne başlıyoruz
    int secim;
    while (1) {
                // Menü seçeneklerini yazdırdım.
        printf("\n");
        printf("1.  BIRIM EKLE\n");
        printf("2.  CALISAN EKLE\n");
        printf("3.  BIRIMLERI YAZDIR\n");
        printf("4.  TUM BIRIMLERI YAZDIR\n");
        printf("5.  CALISANLARI YAZDIR\n");
        printf("6.  MAAS ORTALAMASINI HESAPLA\n");
        printf("7.  ORTALAMA USTUNDEKI CALISANLARI LISTELE\n");
        printf("8.  EN YUKSEK MAASLI CALISANI YAZDIR\n");
        printf("9.  MAAS GUNCELLE \n");
        printf("10. BIRIM VE CALISANLARI DOSYAYA YAZDIR\n");
        printf("11. BIRIM VE CALISANLARI DOSYADAN OKU\n");
        printf("12. CIKIS\n");
        printf("\nSECIMINIZI YAPIN: ");
        scanf("%d", &secim);
       


        // Kullanıcının seçimine göre işlemleri gerçekleştiren switch-case yapısı oluşturdum.

        switch (secim) {
            case 1: {
                // Birim ekleme işlemi için gerekli değişkenleri alıyorum.
                char birimAdi[30];
                unsigned short int birimKodu;

                // Kullanıcıdan birim adı ve kodu aldım.
                printf("\n\nBIRIM ADI: ");
                scanf("%s", birimAdi);
                printf("BIRIM KODU: ");
                scanf("%hu", &birimKodu);

                // Yeni bir birim oluşturdum.
                Birim* yeniBirim = birimOlustur(birimAdi, birimKodu);
                // Eğer birim başarıyla oluşturulmuşsa, dizimize eklemeyi denedim.
                if (yeniBirim != NULL) {
                    if (birimDizisineBirimEkle(yeniBirim, birimDizisi)) {// Başarılı ekleme işlemi     
                    } else {
                        // Eğer birim eklenemezse, maksimum birim sayısına ulaştığımı belirtiyorum
                        printf("BIRIM EKLENEMEDI.MAKSIMUM BIRIM SAYISINA ULASTINIZ.\n");
                    }
                }
                break;
            }
            case 2: {
                // Çalışan eklemek için gerekli bilgileri alıyorum
                char adi[30], soyadi[30];
                unsigned short int birimKodu;
                float maas;
                int girisYili;

                printf("CALISAN ADI: ");
                scanf("%s", adi);
                printf("CALISAN SOYADI: ");
                scanf("%s", soyadi);
                printf("BIRIM KODU: ");
                scanf("%hu", &birimKodu);
                printf("MAAS: ");
                scanf("%f", &maas);
                printf("GIRIS YILI: ");
                scanf("%d", &girisYili);

                // Yeni bir çalışan oluşturuyorum
                Calisan* yeniCalisan = calisanOlustur(adi, soyadi, birimKodu, maas, girisYili);
                
                // Çalışan başarıyla oluşturulduysa, dizime eklemeye çalışıyorum
                if (yeniCalisan != NULL) {
                    if (birimDizisineCalisanEkle(yeniCalisan, birimDizisi)) {  // Başarıyla çalışanın dizime eklendiğini kontrol ediyorum
                    } else {
                        // Eğer çalışan eklenemezse, maksimum çalışan sayısına ulaştığımı belirtiyorum
                        printf("CALISAN EKLENEMEDI.\n");
                    }
                }
                break;
            }
            case 3: {
                // Birimlerin bilgilerini yazdırmaya başlıyorum
                for (size_t i = 0; i < MAX_BIRIM; i++) {
                    // Eğer birim dizisinde birim varsa, bilgilerini yazdırıyorum
                    if (birimDizisi[i] != NULL) {
                        printBirim(birimDizisi[i]);
                    }
                }
                break;
            }
             case 4: {
                printBirimDizi(birimDizisi);     // Tüm birimlerin bilgilerini yazdırmak için fonksiyonu çağırıyorum

                break;
            }

            case 5: {
                // Çalışanları yazdırıyorum.
                for (size_t i = 0; i < MAX_BIRIM; i++) {
                    // Eğer birim dizisinde birim varsa, o birimin çalışanlarını yazdırıyorum
                    if (birimDizisi[i] != NULL) {
                        for (int j = 0; j < MAX_CALISAN; j++) {
                            // Eğer birimde çalışan varsa, çalışan bilgilerini yazdırıyorum
                            if (birimDizisi[i]->birimCalisanlar[j] != NULL) {
                                printCalisan(birimDizisi[i]->birimCalisanlar[j]);
                            }
                        }
                    }
                }
                break;
            }
            case 6: {
                
                // Maaş ortalamasını hesapla
                for (size_t i = 0; i < MAX_BIRIM; i++) {
                    // Eğer birim dizisinde birim varsa, maaş ortalamasını hesaplıyorum
                    if (birimDizisi[i] != NULL) {
                        float ortalama = maasOrtalamasiHesapla(birimDizisi[i]);
                        // Hesaplanan maaş ortalamasını yazdırıyorum
                        printf("''BIRIM '%s' ICIN MAAS ORTALAMASI: %.2f''\n", birimDizisi[i]->birimAdi, ortalama);
                    }
                }
                break;
            }
            case 7: {
                  // Ortalama üstü maaş alan çalışanları listeleme
                for (size_t i = 0; i < MAX_BIRIM; i++) {
                    // Eğer birim dizisinde birim varsa, o birimdeki ortalama üstü maaş alan çalışanları listeliyorum
                    if (birimDizisi[i] != NULL) {
                        ortalamaUstundekiCalisanlariListele(birimDizisi[i]);
                    }
                }
                break;
            }
               
            case 8: {
                 // En yüksek maaşlı çalışanı yazdırma
                for (size_t i = 0; i < MAX_BIRIM; i++) {
                    // Eğer birim dizisinde birim varsa, en yüksek maaşlı çalışanı yazdırıyorum
                    if (birimDizisi[i] != NULL) {
                        enYuksekMaasliCalisaniYazdir(birimDizisi[i]);
                    }
                }
                break;
            }

            case 9: {
                //Maaş güncelle 
            unsigned short int birimKodu; 
            float yeniMaas;

            // Kullanıcıdan birim kodu ve yeni maaş bilgilerini alıyorum
            printf("BIRIM KODU: ");
            scanf("%hu", &birimKodu);  
            printf("YENI MAAS: ");
            scanf("%f", &yeniMaas);

            // Birim dizisinde birim koduna göre birim arıyorum ve maaşı güncelliyorum
            for (size_t i = 0; i < MAX_BIRIM; i++) {
                if (birimDizisi[i] != NULL && birimDizisi[i]->birimKodu == birimKodu) {  
                maasGuncelle(birimDizisi[i], yeniMaas);
                break;
                        }
                    }
                break;
            }
            case 10: {
                // Birim ve çalışanları dosyaya yazdırma
                tumBirimVeCalisanBilgileriniYazdir(birimlerDosyaAdi, calisanlarDosyaAdi, birimDizisi);
                break;
            }
            case 11: {
                // Birim ve çalışanları dosyadan okuma
                tumBirimVeCalisanBilgileriniOku(birimlerDosyaAdi, calisanlarDosyaAdi, birimDizisi);
                break;
            }
            case 12: {
                // Çıkış
                printf("CIKIS YAPILIYOR...\n");
                return 0;
            }
      default:
          // Geçersiz seçim durumu
                printf("GECERSIZ SECIM. LUTFEN 1-11 ARASI BIR SECIM YAPIN.\n");
                break;
        }
    
    }

    // Bellek temizliği
    for (int i = 0; i < MAX_BIRIM; i++) {
        if (birimDizisi[i] != NULL) {
            for (int j = 0; j < MAX_CALISAN; j++) {
                if (birimDizisi[i]->birimCalisanlar[j] != NULL) {
                    free(birimDizisi[i]->birimCalisanlar[j]->calisanAdi);
                    free(birimDizisi[i]->birimCalisanlar[j]->calisanSoyadi);
                    free(birimDizisi[i]->birimCalisanlar[j]);
                }
            }
            free(birimDizisi[i]->birimAdi);
            free(birimDizisi[i]->birimCalisanlar);
            free(birimDizisi[i]);
        }
    }
    free(birimDizisi);
    return 0;
}