#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <locale.h>

#define kucuk(sayi1,sayi2) sayi1<sayi2 ? sayi1 : sayi2
#define buyuk(sayi1,sayi2) sayi1>sayi2 ? sayi1 : sayi2
//Kucuk ve buyuk sayiyi dondurmek için makro kullandık

enum gun{Pazartesi=1,Sali,Carsamba,Persembe,Cuma,Cumartesi,Pazar};
static int gunBilgisi=1;
static int yil=2021;
static int ay=1;
static int gunSayisi=1;
static int saat = 9;
static int dakika = 30;
//Takvim kullanmak için bir enum yanında da bir kaç değişken olurşturduk

typedef struct hastaDurum{
    char durum;
}durum;
typedef struct hastaKayit{
    char ad[30];
    char soyad[30];
    char cinsiyet;
    float boy;
    float kilo;
    int yas;
    int no;
    durum hastanindurumu;
}hastalar;
// Konsolda gecici tutulan bilgiler

typedef struct FhastaDurum{
    char durum;
}Fdurum;
typedef struct fhastaKayit{
    char ad[30];
    char soyad[30];
    char cinsiyet;
    float boy;
    float kilo;
    int yas;
    int no;
    Fdurum hastanindurumu;
}Fhastalar;
// Dosyadan alinan karsilastirma icin kullanilan bilgiler

char menu(){
    char kontrol;
     printf("Lutfen istediginiz islemi tuslayiniz\n");
     printf("0. Hasta Kaydetme\n1. Hasta Kontrol\n2. Hasta Durumu\n3. Hasta Numarasi aratma\n4. Hasta Sayisi alma\n5. Yas odakli aratma\n6. Cinsiyet odakli aratma\n7. Durum sayisi aratma\n8. Bilgilerini bildiginiz hastanin hasta no'sunu ogrenme\n9. Risk durumlarina gore hasta sayisi\n");
     printf("\n");
     printf("Seciminiz: ");
     scanf(" %c",&kontrol);
     printf("\n");
     return kontrol;
}
//Menü ekranı çıktısı için

int evetHayir(){
        char sec;
        printf("\n");
        printf("Devam etmek istiyor musunuz ? [E/H]\n");
        scanf(" %c", &sec);
        printf("\n");
        if(sec == 'E' || sec == 'e'){
            return 0;
        }
        return 1;
}
//Kullanıcıdan devam mı değil mi cevabını almak için

int hastaNoBul(Fhastalar *Fhasta,char arama1[2][30],float arama2[2],int arama3,char arama4[2],int a){
    int sayac = 0;
    for(int i=0; i<a; i++){
        sayac = 0;
        sayac += strcmp(Fhasta[i].ad,arama1[0]);
        sayac += strcmp(Fhasta[i].soyad,arama1[1]);
        //Üstteki iki satırda string.h kütüphanesinden gelen strcmp fonsiyonu ile.
        //İki stringi karşılaştırdık ve eğer stringler eşitse 0 değerini veren fonksiyon.
        //Değer doğru çıktığında bizim sayacımızı değiştirmedi.

        if(sayac == 0 && Fhasta[i].cinsiyet == arama4[0] && Fhasta[i].boy == arama2[0] && Fhasta[i].kilo == arama2[1] && Fhasta[i].yas == arama3 && Fhasta[i].hastanindurumu.durum == arama4[1]){
            return Fhasta[i].no;
        }
    }

    printf("\nAradiginiz hasta bulunamadi");

    return 0;
}
//Hastaların bilgilerine göre hasta numarası alma.

void hastaTablosu(Fhastalar *Fhasta,int kSayi){
        for(int i=0; i<kSayi; i++){
            printf("----------------------------------------------\n");
            printf("| %s | %s | %c | %.1f | %.1f | %d | %d | %c |\n",Fhasta[i].ad,Fhasta[i].soyad,Fhasta[i].cinsiyet,Fhasta[i].boy,Fhasta[i].kilo,Fhasta[i].yas,Fhasta[i].no,Fhasta[i].hastanindurumu.durum);
        }
        printf("----------------------------------------------\n");
}
//Hastalarımızı bastırmak için

void durumaGoreHastaTablosu(Fhastalar *Fhasta,int kSayi,char hdurum){
        for(int i=0; i<kSayi; i++){
           if(hdurum == Fhasta[i].hastanindurumu.durum){
                printf("----------------------------------------------\n");
                printf("| %s | %s | %c | %.1f | %.1f | %d | %d | %c |\n",Fhasta[i].ad,Fhasta[i].soyad,Fhasta[i].cinsiyet,Fhasta[i].boy,Fhasta[i].kilo,Fhasta[i].yas,Fhasta[i].no,Fhasta[i].hastanindurumu.durum);
           }
        }
        printf("----------------------------------------------\n");
}
//Belirli durumdaki hastalarımızı bastırmak için

void binarySearch(int hno,Fhastalar *Fhasta,int a){
        int taban=0;
        int tavan= a-1;
        while(taban<=tavan){
            int orta=(tavan+taban)/2;
            if(Fhasta[orta].no == hno){
                printf("----------------------------------------------\n");
                printf("| %s | %s | %c | %.1f | %.1f | %d | %d | %c |\n",Fhasta[orta].ad,Fhasta[orta].soyad,Fhasta[orta].cinsiyet,Fhasta[orta].boy,Fhasta[orta].kilo,Fhasta[orta].yas,Fhasta[orta].no,Fhasta[orta].hastanindurumu.durum);
                break;
            }
            else if(Fhasta[orta].no > hno){
                tavan = orta-1;
            }
            else{
                 taban = orta+1;
            }
        }
        printf("----------------------------------------------\n");
}
//Hastanedeki hasta sayıları büyük sayılar olduğu için binary search kullanmamız bizim için daha hızlı bir yöntem

void karsilastir(int kSayi,hastalar *hasta, Fhastalar *Fhasta){
    for(int i=0; i<kSayi; i++){
            int sayac = 0,karsilastirAd = 0,karsilastirSoyad = 0,j = 0;

                while((hasta[i].ad[j] != NULL) && (Fhasta[i].ad[j] != NULL))
                    if(hasta[i].ad[j] != Fhasta[i].ad[j]){
                        karsilastirAd++;
                        j++;
                    }
                    else{
                        j++;
                        continue;
                    }
                //Bunun yerine strcmp hazır fonksiyonunu da kullanabilirdik fakat algoritmayı daha iyi anlamak için kendimiz yazmayı tercih ettik
                j=0;

                while((hasta[i].ad[j] != NULL) && (Fhasta[i].ad[j] != NULL))
                    if(hasta[i].ad[j] != Fhasta[i].ad[j]){
                        karsilastirSoyad++;
                        j++;
                    }
                    else{
                        j++;
                        continue;
                    }
                //Bunun yerine strcmp hazır fonksiyonunu da kullanabilirdik fakat algoritmayı daha iyi anlamak için kendimiz yazmayı tercih ettik

            if(karsilastirAd != 0){
                printf("%d. hastanin adlari birbiriyle uyusmamaktadir ! \a \n",i+1);
                printf("Hastanin konsoldaki adi %s Dosyadaki adi %s'dir\n",hasta[i].ad,Fhasta[i].ad);
                sayac++;
            }
            if(karsilastirSoyad != 0){
                printf("%d. hastanin soyadlari birbiriyle uyusmamaktadir ! \a \n",i+1);
                printf("Hastanin konsoldaki soyadi %s Dosyadaki soyadi %s'dir\n",hasta[i].soyad,Fhasta[i].soyad);
                sayac++;
            }
            if(hasta[i].cinsiyet != Fhasta[i].cinsiyet){
                printf("%d. hastanin cinsiyetleri birbiriyle uyusmamaktadir ! \a \n",i+1);
                printf("Hastanin konsoldaki boyu %c Dosyadaki boyu %c'dir\n",hasta[i].cinsiyet,Fhasta[i].cinsiyet);
                sayac++;
            }
            if(hasta[i].boy != Fhasta[i].boy){
                printf("%d. hastanin boylari birbiriyle uyusmamaktadir ! \a \n",i+1);
                printf("Hastanin konsoldaki boyu %.1f Dosyadaki boyu %.1f'dir\n",hasta[i].boy,Fhasta[i].boy);
                sayac++;
            }
            if(hasta[i].kilo != Fhasta[i].kilo){
                printf("%d. hastanin kilolari birbiriyle uyusmamaktadir ! \a \n",i+1);
                printf("Hastanin konsoldaki kilosu %.1f Dosyadaki kilosu %.1f'dir\n",hasta[i].kilo,Fhasta[i].kilo);
                sayac++;
            }
            if(hasta[i].yas != Fhasta[i].yas){
                printf("%d. hastanin yaslari birbiriyle uyusmamaktadir ! \a \n",i+1);
                printf("Hastanin konsoldaki yasi %d Dosyadaki yasi %d'dir\n",hasta[i].yas,Fhasta[i].yas);
                sayac++;
            }
            if(hasta[i].no != Fhasta[i].no){
                printf("%d. hastanin numaralari birbiriyle uyusmamaktadir ! \a \n",i+1);
                printf("Hastanin konsoldaki hasta numarasi %d Dosyadaki hasta numarasi %d'dir\n",hasta[i].no,Fhasta[i].no);
                sayac++;
            }
            if(hasta[i].hastanindurumu.durum != Fhasta[i].hastanindurumu.durum){
                printf("%d. hastanin durumlari birbiriyle uyusmamaktadir ! \a \n",i+1);
                printf("Hastanin konsoldaki durumu %c Dosyadaki durumu %c'dir\n",hasta[i].hastanindurumu.durum,Fhasta[i].hastanindurumu.durum);
                sayac++;
            }
            if(sayac == 0){
                printf("%d. hastanin bilgileri tamamen uyusmaktadir\n",i+1);
            }
        }
}
//Dosyadaki bilgileri konsoldaki bilgilerle karşılaştırarak bilgi yazımında hata olup olmadığına bakar

void yasaGoreArama(int yas1,int yas2,Fhastalar *Fhasta,int a){
    int kucuk,buyuk;

    if(yas1>=yas2){
        buyuk = yas1;
        kucuk = yas2;
    }
    else{
        buyuk = yas2;
        kucuk = yas1;
    }
    //Yukarıdaki iki karşılaştırmayı yazdığımız makrolar ile de yapabilirdik fakat mantığını anlamak amacıyla ikisini de kullannmayı tercih ettik


    printf("Ust sinir: %d\nAlt sinir: %d\n",buyuk(yas1,yas2),kucuk(yas1,yas2));
    //Makrolarımızı kullanarak sınır bilgilerini bastırdık

    for(int i=0; i<a; i++){
        if((Fhasta[i].yas >= kucuk )&&(Fhasta[i].yas <= buyuk)){
             printf("----------------------------------------------\n");
             printf("| %s | %s | %c | %.1f | %.1f | %d | %d | %c |\n",Fhasta[i].ad,Fhasta[i].soyad,Fhasta[i].cinsiyet,Fhasta[i].boy,Fhasta[i].kilo,Fhasta[i].yas,Fhasta[i].no,Fhasta[i].hastanindurumu.durum);
        }
    }
    printf("----------------------------------------------\n");
}
//Belli iki yas arasindaki kisileri bastirma. Risk grupları vb.

void cinsiyetSorgu(char cinsiyet,Fhastalar *Fhasta,int a){
    for(int i=0; i<a;i++){
        if(Fhasta[i].cinsiyet == cinsiyet){
            printf("----------------------------------------------\n");
            printf("| %s | %s | %c | %.1f | %.1f | %d | %d | %c |\n",Fhasta[i].ad,Fhasta[i].soyad,Fhasta[i].cinsiyet,Fhasta[i].boy,Fhasta[i].kilo,Fhasta[i].yas,Fhasta[i].no,Fhasta[i].hastanindurumu.durum);
        }
    }
    printf("----------------------------------------------\n");
}
//Belli cinsiyetleri bastırma.

void durumSayisiSoyle(Fhastalar *Fhasta,int a){
    int i=0,k=0,agir=0;
    for(int j=0; j<a; j++){
        if(Fhasta[j].hastanindurumu.durum == 'i'){
            i++;
        }
        else if(Fhasta[j].hastanindurumu.durum == 'k'){
            k++;
        }
        else if(Fhasta[j].hastanindurumu.durum == 'a'){
            agir++;
        }
    }
    printf("Durumu:\nIyi hastalar: %d\nKaybedilen hastalar: %d\nDurumu agir hastalar: %d\n",i,k,agir);
}
//Hasta durum sayilarini bastiran

void yasAraligiAl(Fhastalar *Fhasta,int a){

    int cocuk=0,ergenlik=0,yetiskin=0,yasli=0;
    int risk;

    while(1){
    printf("Lutfen hangi risk durumu olduğunu seeçiniz\n");
    printf("1. Covid19\n2. Obezite\n");
    scanf("%d",&risk);

    if(risk == 2){
    for(int i=0; i<a; i++){
        if((Fhasta[i].kilo/pow(Fhasta[i].boy,2))>29.9){
            if(Fhasta[i].yas <= 13){
                cocuk++;
            }
            else if(Fhasta[i].yas <=24){
                ergenlik++;
            }
            else if(Fhasta[i].yas <=40){
                yetiskin++;
            }
            else{
                yasli++;
            }
            printf("----------------------------------------------\n");
            printf("| %s | %s | %c | %.1f | %.1f | %d | %d | %c |\n",Fhasta[i].ad,Fhasta[i].soyad,Fhasta[i].cinsiyet,Fhasta[i].boy,Fhasta[i].kilo,Fhasta[i].yas,Fhasta[i].no,Fhasta[i].hastanindurumu.durum);
        }
    }
    printf("----------------------------------------------\n");
    printf("Risk altindakiler:\nErgenlik Cagindakilerin sayisi: %d\nYetiskin sayisi: %d",ergenlik,yetiskin);
    printf("\nCocuk sayisi: %d\nYasli sayisi: %d\n",cocuk,yasli);
    break;
    }

    if(risk == 1){
        for(int i=0; i<a; i++){
            if(Fhasta[i].yas <= 13){
                cocuk++;
                printf("----------------------------------------------\n");
                printf("| %s | %s | %c | %.1f | %.1f | %d | %d | %c |\n",Fhasta[i].ad,Fhasta[i].soyad,Fhasta[i].cinsiyet,Fhasta[i].boy,Fhasta[i].kilo,Fhasta[i].yas,Fhasta[i].no,Fhasta[i].hastanindurumu.durum);
            }
            else{
                yasli++;
                printf("----------------------------------------------\n");
                printf("| %s | %s | %c | %.1f | %.1f | %d | %d | %c |\n",Fhasta[i].ad,Fhasta[i].soyad,Fhasta[i].cinsiyet,Fhasta[i].boy,Fhasta[i].kilo,Fhasta[i].yas,Fhasta[i].no,Fhasta[i].hastanindurumu.durum);
            }
        }
    printf("----------------------------------------------\n");
    printf("Risk altindakiler:\nCocuk sayisi: %d\nYasli sayisi: %d\n",cocuk,yasli);
    break;
    }

    else{
        printf("Lutfen gecerli bir rakam giriniz\n");
    }

    }
}
//Covid ve obezite risk değerine sahip kişileri bastırmak için

void tarih(enum gun bugun){

    if(bugun == Pazartesi){
        printf("\n%d %d %d Pazartesi ",gunSayisi,ay,yil);
    }
    else if(bugun == Sali){
        printf("\n%d %d %d Sali ",gunSayisi,ay,yil);
    }
    else if(bugun == Carsamba){
        printf("\n%d %d %d Carsamba ",gunSayisi,ay,yil);
    }
    else if(bugun == Persembe){
        printf("\n%d %d %d Persembe ",gunSayisi,ay,yil);
    }
    else if(bugun == Cuma){
        printf("\n%d %d %d Cuma ",gunSayisi,ay,yil);
    }
    else if(bugun == Cumartesi){
        printf("\n%d %d %d Cumartesi ",gunSayisi,ay,yil);
    }
    else if(bugun == Pazar){
        printf("\n%d %d %d Pazar ",gunSayisi,ay,yil);
    }

    if(saat >= 10){
        printf("%d:",saat);
    }
    else{
        printf("0%d:",saat);
    }
    if(dakika >= 10){
        printf("%d",dakika);
    }
    else{
        printf("0%d",dakika);
    }

    saat += rand()%12+1;
    dakika = rand()%59+1;
    if(saat >=24){
        saat = 0;
        gunSayisi++;
    }
    if(gunSayisi == 31){
        ay++;
        gunSayisi = 1;
    }
    if(ay == 13){
        yil++;
        ay=1;
    }
}
//Her ay 30 gün olarak alınmıştır tarih ve saat bastırır.

int main()
{
    FILE *dosya,*dosya2;

    setlocale(LC_ALL,"Turkish");
    //Türkçe karakterler kullanmayı tercih etmesek de arada alışkanlıktan Türkçe karakterlerle kelime yazılırsa bastırmak için.

    dosya = fopen("Hasta Kayit.txt","w");
    //.c dosyasinin oldugu yere bir Hasta Kayit.txt açtik

    int a=0;

    srand(time(NULL));

    printf("Lutfen islem yapilmasini istediginiz hasta sayisini giriniz\n");
    scanf("%d",&a);
    printf("\n");

    hastalar *hasta;
    hasta = calloc(a,sizeof(*hasta));
    //sizeof kullanmak yerine 78 yazabilirdik çünkü yapının boyutunu kendimiz hesaplayabiliyoruz.
    Fhastalar *Fhasta;
    Fhasta = calloc(a,sizeof(*Fhasta));
    //sizeof kullanmak yerine 78 yazabilirdik çünkü yapının boyutunu kendimiz hesaplayabiliyoruz.
    //Structlar oluşturuldu

    char kontrol;

    do{

    kontrol = menu();

    if(kontrol == '0'){

        for(int i=0; i<a; i++){
            while(1){
                printf("Lutfen sirasiyla %d. hastanin:\n1-Adini \n2-Soyadini \n3-Cinsiyetini [e,k] \n4-Boyunu \n5-Kilosunu \n6-Yasini \n7-Hasta Numarasini \n8-Hasta Durumunu [i,k,a] giriniz\n",i+1);
                printf("Lutfen boy ve kilo girerken virgulden sonra sadece 1 basamak giriniz !\a\n");
                scanf("%s %s %c %f %f %d %d %c",hasta[i].ad,hasta[i].soyad,&hasta[i].cinsiyet,&hasta[i].boy,&hasta[i].kilo,&hasta[i].yas,&hasta[i].no,&hasta[i].hastanindurumu.durum);
                printf("\n");

                if((hasta[i].hastanindurumu.durum == 'i' || hasta[i].hastanindurumu.durum == 'k' || hasta[i].hastanindurumu.durum == 'a')&& !(hasta[i].no <1 || hasta[i].boy <0 || hasta[i].kilo <0 || hasta[i].yas <=0) && ((hasta[i].cinsiyet == 'k') || (hasta[i].cinsiyet == 'K') || (hasta[i].cinsiyet == 'E') || (hasta[i].cinsiyet == 'e'))){
                }
                else{
                    printf("\nHasta bilgileri gecersiz\n");
                    printf("\n");
                    continue;
                }
                break;
            }
        }

        hastaTablosu(hasta,a);

        if((dosya = fopen("Hasta Kayit.txt","w")) == NULL){
            printf("Dosya basariyla acilamadi\a\n");
            return 0;
        }

        for(int i=0; i<a; i++){
            fprintf(dosya, "%s %s %c %.1f %.1f %d %d %c\n", hasta[i].ad,hasta[i].soyad,hasta[i].cinsiyet,hasta[i].boy,hasta[i].kilo,hasta[i].yas,hasta[i].no,hasta[i].hastanindurumu.durum);
        }

        fclose(dosya);
    }

    else if(kontrol == '1'){

        int kSayi;
        while(1){
            printf("Kontrol etmek istediginiz hasta sayisini giriniz\n");
            scanf("%d", &kSayi);
            printf("\n");

            if(kSayi > a){
                printf("Etkilesime gecebileceginiz maksimum sayi %d'dir\n",a);
                printf("\n");
                continue;
            }
            break;
        }

        if((dosya = fopen("Hasta Kayit.txt","r") == NULL)){
            printf("Dosya basariyla acilamadi\a\n");
            return 0;
        }

        dosya = fopen("Hasta Kayit.txt","r");

        for(int i=0; i<kSayi; i++){
            fscanf(dosya,"%s %s %c %f %f %d %d %c",Fhasta[i].ad,Fhasta[i].soyad,&Fhasta[i].cinsiyet,&Fhasta[i].boy,&Fhasta[i].kilo,&Fhasta[i].yas,&Fhasta[i].no,&Fhasta[i].hastanindurumu.durum);
        }

        hastaTablosu(Fhasta,kSayi);

        printf("\n");

        karsilastir(kSayi,hasta,Fhasta);

        fclose(dosya);

    }

    else if(kontrol == '2'){

        if((dosya = fopen("Hasta Kayit.txt","r") == NULL)){
            printf("Dosya basariyla acilamadi\a\n");
            return 0;
        }

        printf("Durumu iyi hastalari listelemek icin i, agir olanlari listelemek icin a, kaybedilenleri olanlari listelemek icin k giriniz\n");
        char hdurum;
        scanf(" %c",&hdurum);

        dosya = fopen("Hasta Kayit.txt","r");
        for(int i=0; i<a; i++){
            fscanf(dosya,"%s %s %c %f %f %d %d %c",Fhasta[i].ad,Fhasta[i].soyad,&Fhasta[i].cinsiyet,&Fhasta[i].boy,&Fhasta[i].kilo,&Fhasta[i].yas,&Fhasta[i].no,&Fhasta[i].hastanindurumu.durum);
        }

        durumaGoreHastaTablosu(Fhasta,a,hdurum);

        fclose(dosya);

    }

    else if(kontrol == '3'){

        if((dosya = fopen("Hasta Kayit.txt","r") == NULL)){
            printf("Dosya basariyla acilamadi\a\n");
            return 0;
        }

        printf("Aramak istediginiz hasta numarasini giriniz\n");
        int hno;
        scanf("%d",&hno);

        dosya = fopen("Hasta Kayit.txt","r");
        for(int i=0; i<a; i++){
            fscanf(dosya,"%s %s %c %f %f %d %d %c",Fhasta[i].ad,Fhasta[i].soyad,&Fhasta[i].cinsiyet,&Fhasta[i].boy,&Fhasta[i].kilo,&Fhasta[i].yas,&Fhasta[i].no,&Fhasta[i].hastanindurumu.durum);
        }

        binarySearch(hno,Fhasta,a);
        //Binary Search kullandık çünkü hastanelerdeki hasta sayıları genelde büyük sayılardır.

        fclose(dosya);

    }

    else if(kontrol == '4'){

        if((dosya = fopen("Hasta Kayit.txt","r") == NULL)){
            printf("Dosya basariyla acilamadi\a\n");
            return 0;
        }
        dosya = fopen("Hasta Kayit.txt","r");

        int hastaSayisi=-1;
        char gecici[8][30];

        if(feof(dosya)){
            hastaSayisi=0;
        }

        while(!(feof(dosya))){
            fscanf(dosya,"%s %s %s %s %s %s %s %s",&gecici[0],&gecici[1],&gecici[2],&gecici[3],&gecici[4],&gecici[5],&gecici[6],gecici[7]);
            hastaSayisi++;
        }

        fclose(dosya);

        printf("Kayitli hasta sayisi = %d\n",hastaSayisi);
        printf("\n");
    }

    else if(kontrol == '5'){

        if((dosya = fopen("Hasta Kayit.txt","r") == NULL)){
            printf("Dosya basariyla acilamadi\a\n");
            return 0;
        }

        int yas1, yas2;
        printf("Lutfen arama yapmak istediginiz iki yas araligi giriniz\nEger tek bir yas ariyorsaniz ikisini ayni giriniz !\n");
        scanf("%d %d",&yas1,&yas2);
        dosya = fopen("Hasta Kayit.txt","r");

        for(int i=0; i<a; i++){
            fscanf(dosya,"%s %s %c %f %f %d %d %c",Fhasta[i].ad,Fhasta[i].soyad,&Fhasta[i].cinsiyet,&Fhasta[i].boy,&Fhasta[i].kilo,&Fhasta[i].yas,&Fhasta[i].no,&Fhasta[i].hastanindurumu.durum);
        }

        yasaGoreArama(yas1,yas2,Fhasta,a);
        fclose(dosya);

    }

    else if(kontrol == '6'){

        if((dosya = fopen("Hasta Kayit.txt","r") == NULL)){
            printf("Dosya basariyla acilamadi\a\n");
            return 0;
        }

        char cinsiyet;
        printf("Lutfen aramak istediginiz cinsiyeti giriniz\n");
        scanf(" %c",&cinsiyet);

        dosya = fopen("Hasta Kayit.txt","r");

        for(int i=0; i<a; i++){
            fscanf(dosya,"%s %s %c %f %f %d %d %c",Fhasta[i].ad,Fhasta[i].soyad,&Fhasta[i].cinsiyet,&Fhasta[i].boy,&Fhasta[i].kilo,&Fhasta[i].yas,&Fhasta[i].no,&Fhasta[i].hastanindurumu.durum);
        }

        cinsiyetSorgu(cinsiyet,Fhasta,a);

        fclose(dosya);

    }

    else if(kontrol == '7'){

    if((dosya = fopen("Hasta Kayit.txt","r") == NULL)){
        printf("Dosya basariyla acilamadi\a\n");
        return 0;
    }

    dosya = fopen("Hasta Kayit.txt","r");

    for(int i=0; i<a; i++){
        fscanf(dosya,"%s %s %c %f %f %d %d %c",Fhasta[i].ad,Fhasta[i].soyad,&Fhasta[i].cinsiyet,&Fhasta[i].boy,&Fhasta[i].kilo,&Fhasta[i].yas,&Fhasta[i].no,&Fhasta[i].hastanindurumu.durum);
    }

    durumSayisiSoyle(Fhasta,a);

    fclose(dosya);

    }

    else if(kontrol == '8'){

    if((dosya = fopen("Hasta Kayit.txt","r") == NULL)){
        printf("Dosya basariyla acilamadi\a\n");
        return 0;
    }

    printf("Lutfen hasta no'sunu ogrenmek istediginiz hastanın bilgilerini giriniz\n");
    printf("1-Adini \n2-Soyadini \n3-Cinsiyetini [e,k] \n4-Boyunu \n5-Kilosunu \n6-Yasini \n7-Hasta Durumunu [i,k,a] giriniz\n");
    char arama1[2][30];
    float arama2[2];
    int arama3;
    char arama4[2];
    scanf("%s %s %c %f %f %d %c",arama1[0],arama1[1],&arama4[0],&arama2[0],&arama2[1],&arama3,&arama4[1]);

    dosya = fopen("Hasta Kayit.txt","r");

    for(int i=0; i<a; i++){
        fscanf(dosya,"%s %s %c %f %f %d %d %c",Fhasta[i].ad,Fhasta[i].soyad,&Fhasta[i].cinsiyet,&Fhasta[i].boy,&Fhasta[i].kilo,&Fhasta[i].yas,&Fhasta[i].no,&Fhasta[i].hastanindurumu.durum);
    }

    int arananNo;
    arananNo = hastaNoBul(Fhasta,arama1,arama2,arama3,arama4,a);
    printf("\nAradiginiz hastanin hasta numarasi : %d\n",arananNo);

    fclose(dosya);

    }

    else if(kontrol == '9'){

        if((dosya = fopen("Hasta Kayit.txt","r") == NULL)){
        printf("Dosya basariyla acilamadi\a\n");
        return 0;
        }

        dosya = fopen("Hasta Kayit.txt","r");

        for(int i=0; i<a; i++){
            fscanf(dosya,"%s %s %c %f %f %d %d %c",Fhasta[i].ad,Fhasta[i].soyad,&Fhasta[i].cinsiyet,&Fhasta[i].boy,&Fhasta[i].kilo,&Fhasta[i].yas,&Fhasta[i].no,&Fhasta[i].hastanindurumu.durum);
        }

        yasAraligiAl(Fhasta,a);

        fclose(dosya);
    }

    else{
        printf("Lutfen gecerli bir rakam tuslayiniz \n");
    }

    enum gun static bugun = 1;
    tarih(bugun);
    if(bugun == 7){
        bugun = 1;
    }
    bugun++;
    //Her islem süresince 1 gün geçmiş gibi düşünüyoruz.

    if(evetHayir()!= 0){
        break;
    }

    dosya = fopen("Hasta Kayit.txt","r");
    fflush(dosya);
    fclose(dosya);

    }while(1);
    //Sonsuz işlem döngüsü kullanıcıdan hayır mesajı alana kadar devam eder

    dosya2 = fopen("Hasta Kayit Final.txt","w");
    //.c dosyasinin oldugu yere bir Hasta Kayit Final.txt açtik

    for(int i=0; i<a; i++){
        if(Fhasta[i].hastanindurumu.durum == 'k'){
            continue;
        }
        else{
            fprintf(dosya2,"%s %s %c %.1f %.1f %d %d %c\n",Fhasta[i].ad,Fhasta[i].soyad,Fhasta[i].cinsiyet,Fhasta[i].boy,Fhasta[i].kilo,Fhasta[i].yas,Fhasta[i].no,Fhasta[i].hastanindurumu.durum);
        }
    }
    //Dosyadan kaybedilen hastaları kaldırır

    for(int i=0; i<a; i++){
        if(Fhasta[i].hastanindurumu.durum == 'k'){
            strcpy(Fhasta[i].ad," ");
            // Yapı stringlerine direkt atama yapamadığımız için
            strcpy(Fhasta[i].soyad," ");
            // Yapı stringlerine direkt atama yapamadığımız için
            Fhasta[i].cinsiyet = ' ';
            Fhasta[i].boy = 0;
            Fhasta[i].kilo = 0;
            Fhasta[i].yas = 0;
            Fhasta[i].no = 0;
            Fhasta[i].hastanindurumu.durum = ' ';
        }
    }
    // Sistemden kaybedilen hastaları kaldırır

    hastaTablosu(Fhasta,a);

    fclose(dosya2);

    char secim1;
    printf("\nHasta gecmisini silmek ister misiniz [E\\H]\n");
    scanf(" %c",&secim1);

    if(secim1 == 'E' || secim1 == 'e'){
        if(remove("Hasta Kayit.txt") == 0){
            printf("Gecmis basari ile silindi\n");
        }
        else{
            printf("Gecmis silinemedi\n");
        }
    }

    printf("\nSistemden basariyla cikis yapilmistir...\n");

    return 0;
}
