#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 
1. menu data barang supermarket
- tambah barang 
- ubah
- hapus 
2. menu pemindahan barang
- pindah box ke gudang(bisa milih box yang mana)(push)
- tampil data digudang (display stack)
3. menu transaksi
- tambah transaksi
- barang apa 
- total harga berapa  (transaksi berhasil pop stack)
- masuk dalam antrian ke berapa (menampilkan informasi dia antrean ke berapa) 

- menampilkan data antrian
- menampilkan antrian pertama 
- menampilkan antrian terakhir
- ada berapa atrian 
- kirim (hapus data queue)

*/


//struktur untuk barang 
struct barang{
    char namabarang[100];
    char kategori[50];
    float harga;
    int stock;
    struct barang *next; 
};
typedef struct barang barang;

typedef struct Stack {
    barang* box;             // Box yang disimpan di gudang
    struct Stack* next;   // Pointer untuk stack
} Stack;

void tambahData(barang **head);
void ubahData(barang **head);
void hapusData(barang **head);
void tampilData(barang **head);
void push(Stack** stack, barang* box);
barang* pop(Stack** stack);
void tampilkanGudang(Stack* stack);

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
    barang* boxList = NULL;
    Stack* gudang = NULL;
    int pilih;
    do
    {
        system("cls");
        printf("masukkan pilihan\n");
        printf("1. Tambah data barang\n");
        printf("2. Pindah box ke gudang\n");
        printf("3. Transaksi\n");

         printf("MASUKKAN PILIHAN (tekan 0 untuk keluar) : ");
         fflush(stdin);
         scanf("%d", &pilih);

        if (pilih == 1)
        {
            int pilihdatabarang;
            do
            {
            printf("1. tambah Data Barang\n");
            printf("2. Ubah Data Barang\n");
            printf("3. Hapus Data Barang\n");
            printf("4. Tampil Data Barang\n");
            printf("5. Kembali ke Menu Utama\n");
            printf("Pilih menu (1-5): ");
            scanf("%d", &pilihdatabarang);
            getchar();

                if (pilih == 1)
                    tambahData(&head);
                else if (pilih == 2)
                    ubahData(&head);
                else if (pilih == 3)
                    hapusData(&head);    
                else if (pilih == 4)
                    tampilData(&head);                     
            } while (pilihdatabarang != 5);
        }

        else if (pilih == 2)
        {
            int pilihpindahbarang;
            do
            {
            printf("1. pindah box ke gudang\n");
            printf("2. Tampil data box di gudang \n");
            printf("3. Kembali ke Menu Utama\n");
            printf("Pilih menu (1-3): ");
            scanf("%d", &pilihpindahbarang);
            getchar();

                if (pilih == 1)
                    if (head != NULL) {
                        push(&gudang, head); // Memindahkan barang ke gudang
                        head = head->next;   // Menghapus barang dari daftar utama
                    } else {
                        printf("Tidak ada barang untuk dipindahkan ke gudang.\n");
                    }
                else if (pilih == 2)
                    tampilkanGudang(&head);                        
            } while (pilihpindahbarang != 3);
        }
         
        else if (pilih == 3)
        {
            int pilihtransaksi;
            do
            {
            printf("1. Tambah Transaksi\n");
            printf("2. Tampilkan box data antrean \n");
            printf("3. Menampilkan antrian pertama\n");
            printf("4. Menampilkan antrian terakhir\n");
            printf("5. Menampilkan jumlah antrian\n");
            printf("6. Kirim box dalam antrian\n");
            printf("7. Kembali ke menu utama\n");
            printf("Pilih menu (1-7): ");
            scanf("%d", &pilihtransaksi);
            getchar();
                       
            } while (pilihtransaksi != 7);
        }


    } while (pilih != 0);

    return 0;
    
}

//========================================================
// fungsi tambah data
void tambahData(barang **head){
    barang *pNew = (barang *)malloc(sizeof(barang));
    system("cls");

    printf("Masukkan nama barang: ");
    fflush(stdin);
    gets(pNew->namabarang);
    trim(pNew->namabarang);
    for (int i = 0; pNew->namabarang[i]; i++)
    {
        pNew->namabarang[i] = tolower(pNew->namabarang[i]);
    }

    printf("Masukkan kategori barang: ");
    fflush(stdin);
    gets(pNew->kategori);
    trim(pNew->kategori);
    for (int i = 0; pNew->kategori; i++)
    {
        pNew->kategori[i] = tolower(pNew->kategori[i]);
    }
    
    printf("Masukkan harga barang: ");
    scanf("%f", &pNew->harga);
    printf("Masukkan jumlah stok barang:  ");
    scanf("%d", &pNew->stock);


    pNew->next = *head;
    *head = pNew;
    printf("Data berhasil ditambahkan!\n");
    getch();
        
}

//========================================================
// fungsi ubah data
void ubahData(barang **head){
    char nama[100];

    system("cls");
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

            printf("Masukkan jumlah stok barang baru : ");
            scanf("%d", &PCur->stock);

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

void hapusData(barang **head){
    char nama[100];
    system("cls");

    printf("Masukkan nama barang akan dihapus: ");
    fflush(stdin);
    gets(nama);
    trim(nama);

    barang *pCur = *head;
    barang *ppre = NULL;

    while (pCur != NULL)
    {
        if (strcmp(pCur->namabarang, nama) == 0)
        {
            if (ppre == NULL)
            {
                *head = pCur->next;
            }else{
                ppre->next = pCur->next;
            }

            free(pCur);
            printf("barang berhasil dihapus!\n");
            getch();
            return;  
        }

        ppre = pCur;
        pCur = pCur->next;
    }

    printf("barang tidak ditemukan!\n");
    getch();
    
}
//========================================================
//FUNGSI STACK 
void push(Stack** stack, barang* box) {
    Stack* baru = (Stack*)malloc(sizeof(Stack));
    baru->box = box;
    baru->next = *stack;
    *stack = baru;
}

// Fungsi untuk mengambil barang dari gudang (stack)
barang* pop(Stack** stack) {
    if (*stack == NULL) {
        printf("Gudang kosong!\n");
        return NULL;
    }
    Stack* temp = *stack;
    barang* box = temp->box;
    *stack = (*stack)->next;
    free(temp);
    return box;
}
void tampilkanGudang(Stack* stack) {
    if (stack == NULL) {
        printf("Gudang kosong.\n");
        return;
    }
    Stack* temp = stack;
    while (temp != NULL) {
        int totalBarang = 0;
        // for (int i = 0; i < temp->box->jumlahBarang; i++) {
        //     totalBarang += temp->box->barang[i].jumlah;  // Menghitung jumlah barang
        // }
        printf("Box: %s, Jumlah Barang: %d\n", temp->box->namabarang, totalBarang);
        temp = temp->next;
    }
}

//========================================================
//FUNGSI QUEUE  