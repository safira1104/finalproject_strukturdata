#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// - mengisi box yang kosong
// - atribut tambah, ubah, hapus
// - barang :  nama, kategori, harga/box, jumlah stock (per kardus dibatasi 20/25)

#define MAX_STOCK_PER_BOX 25

//struktur untuk barang 
struct barang{
    char namabarang[100];
    char kategori[50];
    float harga;
    int stock;
    struct barang *next; 
};
typedef struct barang barang;

void tambahData(barang **head);
void ubahData(barang **head);
void hapusData(barang **head);
void jumlahData(barang **head);
void cariData(barang **head);
void tampilData(barang **head);

// Fungsi untuk menghapus spasi di awal dan akhir string
void trim(char *str) {
    char *end;
    // Hapus spasi di awal
    while (isspace((unsigned char)*str)) str++;
    // Hapus spasi di akhir
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}


int main(){

    barang *head = NULL;
    int pilih;
    do
    {
        system("cls");
        printf("masukkan pilihan\n");
        printf("1. tambah data barang\n");
        printf("2. ubah data barang\n");
        printf("3. hapus data barang\n");
        printf("4. jumlah data barang\n");
        printf("5. cari data barang\n");
        printf("6. tampil data barang\n");

         printf("MASUKKAN PILIHAN (tekan 0 untuk keluar) : ");
         fflush(stdin);
         scanf("%d", &pilih);
         if (pilih == 1)
            tambahData(&head);
         else if (pilih == 2)
            ubahData(&head);
         else if (pilih == 3)
            hapusData(&head); 
         else if (pilih == 4)
            jumlahData(&head);      
         else if (pilih == 5)
            hapusAwal(&head); 
         else if (pilih == 6)
            tampilData(&head);   
    } while (pilih != 0);

    return 0;
    
}

//========================================================
// fungsi tambah data
void tambahData(barang **head){
    barang *baru = (barang *)malloc(sizeof(barang));

    system("cls");
    printf("Masukkan nama barang: ");
    fflush(stdin);
    gets(baru->kategori);
    trim(baru->kategori);
    for (int i = 0; baru->namabarang[i]; i++)
    {
        baru->namabarang[i] = tolower(baru->namabarang[i]);
    }

    printf("Masukkan kategori barang: ");
    fflush(stdin);
    gets(baru->kategori);
    trim(baru->kategori);
    for (int i = 0; baru->kategori; i++)
    {
        baru->kategori[i] = tolower(baru->kategori[i]);
    }
    
    printf("Masukkan harga barang: ");
    scanf("%f", &baru->harga);
    printf("Masukkan jumlah stok barang (maksimum %d); ", MAX_STOCK_PER_BOX);
    scanf("%d", &baru->stock);
    if (baru->stock > MAX_STOCK_PER_BOX)
    {
        printf("stok melebihi batas maksimum! batas maksimum stok %d.\n", MAX_STOCK_PER_BOX);
        baru->stock = MAX_STOCK_PER_BOX;
    }
    baru->next = *head;
    *head = baru;
    printf("Data berhasil ditambahkan!\n");
    getch();
        
}

//========================================================
// fungsi ubah data
void ubahData(barang **head){
    char nama[100];
    printf("masukkan nama barang yang akan diubah: ");
    fflush(stdin);
    gets(nama);
    trim(nama);
    for (int i = 0; nama[i]; i++)
    {
        nama[i] = tolower(nama[i]);
    }

    barang *PCur = *head;
    while (PCur != NULL){
        if (strcmp(PCur->namabarang, nama) == 0)
        {
            printf("Masukkan nama barang baru: ");
            fflush(stdin);
            gets(PCur->namabarang);
            trim(PCur->namabarang);
            for (int i = 0; PCur->namabarang[i]; i++)
            {
                PCur->namabarang[i] = tolower(PCur->namabarang[i]);
            }
            
            printf("Masukkan kategori barang baru: ");
            fflush(stdin);
            gets(PCur->kategori);
            trim(PCur->kategori);
            for (int i = 0; PCur->kategori[i]; i++)
            {
                PCur->kategori[i] = tolower(PCur->kategori[i]);
            }

            printf("Masukkan harga barang baru: ");
            scanf("%f", &PCur->harga);
            printf("Masukkan jumlah stok barang baru (maksimum %d): ", MAX_STOCK_PER_BOX);
            scanf("%d", &PCur->stock);
            if (PCur->stock > MAX_STOCK_PER_BOX) {
                printf("Stok melebihi maksimum!\n", MAX_STOCK_PER_BOX);
                PCur->stock = MAX_STOCK_PER_BOX;
            }
            printf("Data berhasil diubah!\n");
            getch();
            return;
        }
        printf("Data tidak ditemukan!\n");
        getch();
        
    }  
}

//========================================================
// fungsi hapus data