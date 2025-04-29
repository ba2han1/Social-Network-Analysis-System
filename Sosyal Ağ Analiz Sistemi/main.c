#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KULLANICI 100

typedef enum { KIRMIZI, SIYAH } Renk;

typedef struct Kullanici {
    int id;
    struct Kullanici* arkadaslar[MAX_KULLANICI];
    int arkadas_sayisi;

    struct Kullanici* sol;
    struct Kullanici* sag;
    struct Kullanici* ebeveyn;
    Renk renk;
} Kullanici;

Kullanici* kullanicilar[MAX_KULLANICI];
int kullanici_sayisi = 0;
Kullanici* rbt_kok = NULL;

// --------------------- Red-Black Tree -----------------------

void sola_dondur(Kullanici** kok, Kullanici* x) {
    Kullanici* y = x->sag;
    x->sag = y->sol;
    if (y->sol) y->sol->ebeveyn = x;
    y->ebeveyn = x->ebeveyn;
    if (!x->ebeveyn)
        *kok = y;
    else if (x == x->ebeveyn->sol)
        x->ebeveyn->sol = y;
    else
        x->ebeveyn->sag = y;
    y->sol = x;
    x->ebeveyn = y;
}

void saga_dondur(Kullanici** kok, Kullanici* y) {
    Kullanici* x = y->sol;
    y->sol = x->sag;
    if (x->sag) x->sag->ebeveyn = y;
    x->ebeveyn = y->ebeveyn;
    if (!y->ebeveyn)
        *kok = x;
    else if (y == y->ebeveyn->sag)
        y->ebeveyn->sag = x;
    else
        y->ebeveyn->sol = x;
    x->sag = y;
    y->ebeveyn = x;
}

void ekleme_duzelt(Kullanici** kok, Kullanici* z) {
    while (z->ebeveyn && z->ebeveyn->renk == KIRMIZI) {
        if (z->ebeveyn == z->ebeveyn->ebeveyn->sol) {
            Kullanici* y = z->ebeveyn->ebeveyn->sag;
            if (y && y->renk == KIRMIZI) {
                z->ebeveyn->renk = SIYAH;
                y->renk = SIYAH;
                z->ebeveyn->ebeveyn->renk = KIRMIZI;
                z = z->ebeveyn->ebeveyn;
            } else {
                if (z == z->ebeveyn->sag) {
                    z = z->ebeveyn;
                    sola_dondur(kok, z);
                }
                z->ebeveyn->renk = SIYAH;
                z->ebeveyn->ebeveyn->renk = KIRMIZI;
                saga_dondur(kok, z->ebeveyn->ebeveyn);
            }
        } else {
            Kullanici* y = z->ebeveyn->ebeveyn->sol;
            if (y && y->renk == KIRMIZI) {
                z->ebeveyn->renk = SIYAH;
                y->renk = SIYAH;
                z->ebeveyn->ebeveyn->renk = KIRMIZI;
                z = z->ebeveyn->ebeveyn;
            } else {
                if (z == z->ebeveyn->sol) {
                    z = z->ebeveyn;
                    saga_dondur(kok, z);
                }
                z->ebeveyn->renk = SIYAH;
                z->ebeveyn->ebeveyn->renk = KIRMIZI;
                sola_dondur(kok, z->ebeveyn->ebeveyn);
            }
        }
    }
    (*kok)->renk = SIYAH;
}

void agaca_ekle(Kullanici* z) {
    Kullanici* y = NULL;
    Kullanici* x = rbt_kok;

    while (x) {
        y = x;
        if (z->id < x->id)
            x = x->sol;
        else
            x = x->sag;
    }

    z->ebeveyn = y;
    if (!y)
        rbt_kok = z;
    else if (z->id < y->id)
        y->sol = z;
    else
        y->sag = z;

    z->sol = z->sag = NULL;
    z->renk = KIRMIZI;

    ekleme_duzelt(&rbt_kok, z);
}

Kullanici* agacta_ara(Kullanici* kok, int id) {
    if (!kok || kok->id == id) return kok;
    if (id < kok->id) return agacta_ara(kok->sol, id);
    return agacta_ara(kok->sag, id);
}

// ---------------- Graph ----------------------

Kullanici* kullanici_olustur(int id) {
    Kullanici* kullanici = (Kullanici*)malloc(sizeof(Kullanici));
    kullanici->id = id;
    kullanici->arkadas_sayisi = 0;
    kullanici->sol = kullanici->sag = kullanici->ebeveyn = NULL;
    kullanici->renk = KIRMIZI;
    return kullanici;
}

void kullanici_ekle(int id) {
    Kullanici* kullanici = kullanici_olustur(id);
    kullanicilar[kullanici_sayisi++] = kullanici;
    agaca_ekle(kullanici);
}

Kullanici* kullanici_bul(int id) {
    return agacta_ara(rbt_kok, id);
}

void arkadaslik_ekle(int id1, int id2) {
    Kullanici* k1 = kullanici_bul(id1);
    Kullanici* k2 = kullanici_bul(id2);
    if (k1 && k2) {
        k1->arkadaslar[k1->arkadas_sayisi++] = k2;
        k2->arkadaslar[k2->arkadas_sayisi++] = k1;
    }
}

// DFS
void dfs(Kullanici* kullanici, int derinlik, int ziyaret_edilen[], int mevcut) {
    if (!kullanici || mevcut > derinlik || ziyaret_edilen[kullanici->id]) return;
    ziyaret_edilen[kullanici->id] = 1;
    printf("Kullanici %d derinlik %d\n", kullanici->id, mevcut);
    int i;
    for (i = 0; i < kullanici->arkadas_sayisi; i++) {
        dfs(kullanici->arkadaslar[i], derinlik, ziyaret_edilen, mevcut + 1);
    }
}

// ---------------- Ortak Arkadaş Analizi ----------------

void ortak_arkadas(Kullanici* k1, Kullanici* k2) {
    printf("\nOrtak Arkadaslar: ");
    int bulundu = 0;
    int i, j;
    for (i = 0; i < k1->arkadas_sayisi; i++) {
        for (j = 0; j < k2->arkadas_sayisi; j++) {
            if (k1->arkadaslar[i]->id == k2->arkadaslar[j]->id) {
                printf("%d ", k1->arkadaslar[i]->id);
                bulundu = 1;
            }
        }
    }
    if (!bulundu) printf("Yok");
    printf("\n");
}

// ---------------- Etki Alanı Hesaplama ----------------

void etki_alani(Kullanici* kullanici) {
    int ziyaret_edilen[MAX_KULLANICI] = {0};
    int etki_sayisi = 0;
    printf("\nEtki Alani (Kullanici %d): ", kullanici->id);

    dfs(kullanici, 10, ziyaret_edilen, 0);

    int i;
    for (i = 0; i < MAX_KULLANICI; i++) {
        if (ziyaret_edilen[i]) etki_sayisi++;
    }

    printf("Toplam Etki Alani: %d kullanici\n", etki_sayisi);
}

// ---------------- Topluluk Tespiti ----------------

void topluluk_tespiti(Kullanici* kullanici, int ziyaret_edilen[]) {
    printf("\nTopluluk: ");
    int i;
    ziyaret_edilen[kullanici->id] = 1;
    printf("%d ", kullanici->id);

    for (i = 0; i < kullanici->arkadas_sayisi; i++) {
        if (!ziyaret_edilen[kullanici->arkadaslar[i]->id]) {
            topluluk_tespiti(kullanici->arkadaslar[i], ziyaret_edilen);
        }
    }
}

// ---------------- Dosya Yazımı ----------------

void dosyaya_yaz() {
    FILE* fp = fopen("veriseti.txt", "w");
    if (!fp) {
        printf("Dosya yazilamadi!\n");
        return;
    }

    fprintf(fp, "# Kullanicilar\n");
    int i;
    for (i = 0; i < kullanici_sayisi; i++) {
        fprintf(fp, "KULLANICI %d\n", kullanicilar[i]->id);
    }

    fprintf(fp, "\n# Arkadaslik Iliskileri\n");
    for (i = 0; i < kullanici_sayisi; i++) {
        int j;
        for (j = 0; j < kullanicilar[i]->arkadas_sayisi; j++) {
            if (kullanicilar[i]->id < kullanicilar[i]->arkadaslar[j]->id) {
                fprintf(fp, "ARKADAS %d %d\n", kullanicilar[i]->id, kullanicilar[i]->arkadaslar[j]->id);
            }
        }
    }

    fclose(fp);
    printf("veriseti.txt basariyla kaydedildi.\n");
}

// ---------------- Main ------------------------

int main() {
    int n_kullanicilar, n_arkadasliklar;
    int ziyaret_edilen[MAX_KULLANICI] = {0};

    printf("Kac kullanici eklemek istersiniz? ");
    scanf("%d", &n_kullanicilar);

    int i, j;
    for (i = 0; i < n_kullanicilar; i++) {
        int id;
        printf("Kullanici ID girin: ");
        scanf("%d", &id);
        kullanici_ekle(id);
    }

    printf("Kac arkadaslik iliskisi tanimlanacak? ");
    scanf("%d", &n_arkadasliklar);

    for (j = 0; j < n_arkadasliklar; j++) {
        int id1, id2;
        printf("Arkadaslik (id1 id2): ");
        scanf("%d %d", &id1, &id2);
        arkadaslik_ekle(id1, id2);
    }

    dosyaya_yaz();

    printf("\nDFS ile 2 derinliğe kadar arkadasları listele:\n");
    int baslangic_id;
    printf("Baslangic kullanici ID: ");
    scanf("%d", &baslangic_id);

    Kullanici* baslangic = kullanici_bul(baslangic_id);
    if (baslangic) {
        dfs(baslangic, 2, ziyaret_edilen, 0);
    }

    // Ortak arkadaş analizi
    int kullanici1, kullanici2;
    printf("\nOrtak arkadas analizi icin iki kullanici ID girin (ID1 ID2): ");
    scanf("%d %d", &kullanici1, &kullanici2);
    Kullanici* k1 = kullanici_bul(kullanici1);
    Kullanici* k2 = kullanici_bul(kullanici2);
    if (k1 && k2) ortak_arkadas(k1, k2);

    // Etki alanı hesaplama
    printf("\nEtki alani hesaplamak icin bir kullanici ID girin: ");
    scanf("%d", &kullanici1);
    Kullanici* k3 = kullanici_bul(kullanici1);
    if (k3) etki_alani(k3);

    // Topluluk tespiti
    printf("\nTopluluk tespiti icin tum kullanicilar uzerinde analiz yapiliyor...\n");
    for (i = 0; i < kullanici_sayisi; i++) {
        if (!ziyaret_edilen[kullanicilar[i]->id]) {
            topluluk_tespiti(kullanicilar[i], ziyaret_edilen);
        }
    }

    // --- veriseti.txt dosyasını aç ve içeriğini göster ---
    printf("\n\n Olusturulan veriseti.txt dosyasinin icerigi:\n\n");

    FILE* fp = fopen("veriseti.txt", "r");
    if (!fp) {
        printf("veriseti.txt dosyasi acilamadi!\n");
        return 1;
    }

    char satir[256];
    while (fgets(satir, sizeof(satir), fp)) {
        printf("%s", satir);
    }

    fclose(fp);

    return 0;
}

