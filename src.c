#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



/*=======SECURITY_FUNCT=======*/
int guvenli_int_al(const char *mesaj, int *out)
{
    char buf[64], *end;
    printf("%s", mesaj);

    if (!fgets(buf, sizeof(buf), stdin)) return 0;

    *out = (int)strtol(buf, &end, 10);
    if (end == buf) return 0;

    while (*end == ' ' || *end == '\n') end++;
    return *end == '\0';
}

int guvenli_double_al(const char *mesaj, double *out)
{
    char buf[64], *end;
    printf("%s", mesaj);

    if (!fgets(buf, sizeof(buf), stdin)) return 0;

    *out = strtod(buf, &end);
    if (end == buf) return 0;

    while (*end == ' ' || *end == '\n') end++;
    return *end == '\0';
}

#define PI 3.141592
/*==EXPERIMENT_CHOİCE_FUNCT==*/
void deney_secim(void);

/*==NORMAL_FUNCT==*/
void Serbest_Dusme(double *result);
void Yukari_Atis(double *result);
void Agirlik(double *result);
void Kutlecekimsel_Potansiyel_Enerji(double *result);
void Hidrostatik_Basinc(double *result);
void Arsimet_Kaldirma_Kuvveti(double *result);
void Sabit_ip_Gerilmesi(double *result);

/*==SPECIAL_FUNCT==*/
void Basit_Sarkac_Periyodu(const char** isimler,const float* gezegen_g);
void Asansor(const char** isimler,const float* gezegen_g);

/*==NORMAL_FUNCT_RESULT_FUNC==*/
void Gezegen_islem(int a,const char **isimler,const int gezegen_sayisi,const float *gezegen_g,
                   double result,const char **birimler);

/*============MAIN_FUNCT============*/
int main(void)
{
    /*==========IMPORTANT_ARRAYS_AND_VARIABLES==========*/
    const char* deney_birim[]={"m","m","N","j","N/m^2","m^3","N"};
    const char* gezegen_isim[]={"merkur","venus","dunya","mars","jupiter","saturn","uranus","neptun"};
    const float gezegen_ivme[8]={3.70,8.87,9.81,3.71,24.79,10.44,8.69,11.15};
    char isim[52];
    int  choice;
    /*=========NAME_INPUT=========*/
    while (1) {
        printf("isminizi girin (maksimum 50 karakter): ");
        if (!fgets(isim, sizeof(isim), stdin)) continue;

        if (!strchr(isim, '\n')) {
            printf("Karakter siniri asildi!\n");
            while (getchar() != '\n');
            continue;
        }

        isim[strcspn(isim, "\n")] = '\0';
        if (isim[0] == '\0') {printf("isim bos olamaz!\n");continue;}
        break;
    }
            printf("\nHosgeldin %s!\n",isim);

            /*==SHOW_EXPERIMENT==*/
            deney_secim();

            /*===MAIN_LOOP===*/
            while(1){
                double result = 0.0;
                if (!guvenli_int_al("\nBir deney seciniz: ", &choice)){
                    printf("Gecersiz secim!\n");
                    continue;
                }
                switch (choice) {
                    case -1:printf("cikis yapiliyor...");break;
                    case 1: Serbest_Dusme(&result); break;
                    case 2: Yukari_Atis(&result); break;
                    case 3: Agirlik(&result); break;
                    case 4: Kutlecekimsel_Potansiyel_Enerji(&result); break;
                    case 5: Hidrostatik_Basinc(&result); break;
                    case 6: Arsimet_Kaldirma_Kuvveti(&result); break;
                    case 7: Sabit_ip_Gerilmesi(&result); break;
                    //ozel durumlular
                    case 8:Basit_Sarkac_Periyodu(gezegen_isim,gezegen_ivme);break;
                    case 9: Asansor(gezegen_isim,gezegen_ivme);break;
                    default: printf("Gecerli araligin disinda bir deger girdiniz!\n");continue;
                    }
                if(choice==-1) break;
                if(choice<8)    Gezegen_islem(choice,gezegen_isim,8,gezegen_ivme,result,deney_birim);
        }
    return 0;
}

/*==========ALL_FUNCTS==========*/

void deney_secim(void){
    printf("\n1- Serbest Dusme\n");
    printf("2- Yukari Atis\n");
    printf("3- Agirlik\n");
    printf("4- Potansiyel Enerji\n");
    printf("5- Hidrostatik Basinc\n");
    printf("6- Arsimet Kuvveti\n");
    printf("7- ip Gerilmesi\n");
    printf("8- Basit Sarkac\n");
    printf("9- Asansor\n");
}

void Serbest_Dusme(double *ptr1){
    /*     h = g*t*t/2    */

    printf("Serbest dusme deneyi secildi\n");
    double t;
    while (!guvenli_double_al("Cismin havada kalma suresi(s): ", &t))
        printf("Gecersiz sayi!\n");
    (t<0) ? t*=-1 : (void)0;

    *ptr1 += t*t/2;

}

void Yukari_Atis(double *ptr1){
    /*     h = v*v/2g    */

    printf("Yukari atis deneyi secildi\n");
    double v_ilk;
    while (!guvenli_double_al("Ilk hiz(m/s): ", &v_ilk))
        printf("Gecersiz sayi!\n");
    (v_ilk<0) ? v_ilk*=-1 : (void)0;

    *ptr1 += v_ilk*v_ilk/2;
}

void Agirlik(double *ptr1){
    /*     G = m*g     */

    printf("Agirlik deneyi secildi\n");
    double m;
    while (!guvenli_double_al("Kutle(kg): ", &m))
        printf("Gecersiz sayi!\n");
    (m<0) ? m*=-1 : (void)0;

    *ptr1 += m;
}
void Kutlecekimsel_Potansiyel_Enerji(double *ptr1){
    /*      E = m*g*h    */


    printf("Kutlecekimsel potansiyel enerji deneyi secildi\n");
    double m,h;
    while (!guvenli_double_al("Kutle(kg): ", &m)) printf("Gecersiz!\n");
    (m<0) ? m*=-1 : (void)0;
    while (!guvenli_double_al("Yukseklik(m): ", &h)) printf("Gecersiz!\n");
    (h<0) ? h*=-1 : (void)0;

    *ptr1 += m*h;
}

void Hidrostatik_Basinc(double *ptr1){
    /*    P = p*g*h   */


    printf("Hidrostatik basinc deneyi secildi\n");
    double p,h;
    while (!guvenli_double_al("Yogunluk(kg/m^3): ", &p)) printf("Gecersiz!\n");
    (p<0) ? p*=-1 : (void)0;
    while (!guvenli_double_al("Derinlik(m): ", &h)) printf("Gecersiz!\n");
    (h<0) ? h*=-1 : (void)0;

    *ptr1 += p*h;
}

void Arsimet_Kaldirma_Kuvveti(double *ptr1){
    /*     F = p*g*V     */

    printf("Arsimet kaldirma kuvveti deneyi secildi\n");
    double p,V;
    while (!guvenli_double_al("Yogunluk(kg/m^3): ", &p)) printf("Gecersiz!\n");
    (p<0) ? p*=-1 : (void)0;
    while (!guvenli_double_al("Hacim(m^3): ", &V)) printf("Gecersiz!\n");
    (V<0) ? V*=-1 : (void)0;

    *ptr1 += p*V;
}

void Sabit_ip_Gerilmesi(double *ptr1){
    /*   T = m.g  */

    printf("Sabit ip gerilmesi deneyi secildi\n");
    double m;
    while (!guvenli_double_al("Kutle(kg): ", &m)) printf("Gecersiz!\n");
    (m<0) ? m*=-1 : (void)0;

    *ptr1 += m;
}

void Basit_Sarkac_Periyodu(const char **isimler,const float *gezegen_g){
    /*      T = 2*pi*(L/g)^0.5    */

    printf("Basit sarkac periyodu deneyi secildi\n");
    double L;
    while (!guvenli_double_al("Ip uzunlugu(m): ", &L)) printf("Gecersiz!\n");
    (L<0) ? L*=-1 : (void)0;

    for(int i=0;i<8;i++){
        printf("[%7s] = %8.2lf s\n",*(isimler+i),2*PI*sqrt(L)/ sqrt(*(gezegen_g+i)));
    }
}

void Asansor(const char** isimler,const float* gezegen_g){
    /*  N = m * (g+a)  */

    printf("Asansor deneyi secildi\n");
    double m,a;
    while (!guvenli_double_al("Kutle(kg): ", &m)) printf("Gecersiz!\n");
    (m<0) ? m*=-1 : (void)0;
    printf("Not:\n");
    printf("## Asansor yukari yonde ivmelenerek hizlaniyor yada asagi yonde ivmelenerek yavasliyorsa a pozitif gir ##\n");
    printf("## Asansor yukari yonde ivmelenerek yavasliyor yada asagi yonde ivmelenerek hizlaniyorsa a negatif gir ##\n\n");
    while (!guvenli_double_al("Ivmelenme(m/s^2): ", &a)) printf("Gecersiz!\n");

    for(int i=0;i<8;i++){
        if (*(gezegen_g+i) + a <= 0){printf("[%7s] = temas yok\n",*(isimler+i));continue;};
        printf("[%7s] = %8.2lf N\n",*(isimler+i),m * (*(gezegen_g+i)+a));

    }
}

void Gezegen_islem(int a,const char **isimler,const int gezegen_sayisi,const float *gezegen_g,
                   double result,const char **birimler){

    for(int i=0;i<gezegen_sayisi;i++){
        double g = *(gezegen_g+i);
        if(a==2) g = 1.0/g;

        printf("[%7s] = %8.2lf %s\n",*(isimler+i),result * g,*(birimler+ a-1));
    }
}





















