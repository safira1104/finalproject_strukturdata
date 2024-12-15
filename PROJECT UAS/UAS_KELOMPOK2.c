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
- barang apa (buat supaya barangnya bisa lebih dari 1)
- total harga berapa  (transaksi berhasil pop stack)
- masuk dalam antrian ke berapa (menampilkan informasi dia antrean ke berapa) 

- menampilkan data antrian
- menampilkan antrian pertama 
- menampilkan antrian terakhir
- ada berapa atrian 
- kirim (hapus data queue)

*/


//struktur untuk barang 
typedef struct barang{
    char namabarang[100];
    char kategori[50];
    float harga;
    int stock;
    struct barang *next; 
} barang;

typedef struct Stack {
    barang* box;             // Box yang disimpan di gudang
    struct Stack* next;   // Pointer untuk stack
} Stack;

typedef struct transaksi{
    barang* item;
    int jumlah;
    float totalprice;
    int antrean;
    struct transaksi* next;
}transaksi;

typedef struct queue{
    transaksi* front;
    transaksi* rear;
}queue;



void tambahData(barang **head);
void ubahData(barang **head);
void hapusData(barang **head);
void tampilData(barang **head);

void push(Stack** stack, barang* box);
void pindahKeGudang(barang **head, Stack** gudang);
void tampilkanGudang(Stack* stack);


barang* pop(Stack** stack);


void initqueue(queue** q);
void enqueue(queue* q, barang* item, int jumlah);
transaksi* dequeue(queue* q);


void tambahTransaksi(queue* q, Stack** gudang);
void tampilJumlahTransaksi(queue* q);


void tampilkanAntrean(queue* q);
void tampilkanAntreanPertama(queue* q);
void tampilkanAntreanTerakhir(queue* q);
void tampilkanJumlahAntrean(queue* q);
void kirimBoxDalamAntrian(queue* q);



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
    Stack* gudang = NULL;
    queue* antrean = NULL;
    initqueue(&antrean);


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

        if (pilih == 1){

            int pilihdatabarang;
            do
            {
            
            system("cls");
            printf("1. tambah Data Barang\n");
            printf("2. Ubah Data Barang\n");
            printf("3. Hapus Data Barang\n");
            printf("4. Tampil Data Barang\n");
            printf("5. Kembali ke Menu Utama\n");
            printf("Pilih menu (1-5): ");
            scanf("%d", &pilihdatabarang);
            getchar();

        if (pilihdatabarang == 1)
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
            
            system("cls");
            printf("1. pindah box ke gudang\n");
            printf("2. Tampil data box di gudang \n");
            printf("3. Kembali ke Menu Utama\n");
            printf("Pilih menu (1-3): ");
            scanf("%d", &pilihpindahbarang);
            getchar();

            if (pilihpindahbarang == 1)
                pindahKeGudang(&head, &gudang);
            else if (pilihpindahbarang == 2)
                tampilkanGudang(gudang);                        
            } while (pilihpindahbarang != 3);
        }
        
        else if (pilih == 3)
        {
            int pilihantransaksi;
            do
            {
            system("cls");
            printf("1. Tambah Transaksi\n");
            printf("2. Tampilkan jumlah transaksi \n");
            printf("3. Tampilkan data antrean\n");
            printf("4. Tampilkan antrean pertama\n");
            printf("5. Tampilkan antrean terakhir\n");
            printf("6. Tampilkan jumlah antrean\n");
            printf("7. Kirim box dalam antrean\n");
            printf("8. Kembali ke menu utama\n");
            printf("Pilih menu (1-8): ");
            scanf("%d", &pilihantransaksi);
            getchar();
                if (pilihantransaksi == 1){
                    tambahTransaksi(antrean, &gudang);
                } else if (pilihantransaksi == 2){
                    tampilJumlahTransaksi(antrean);
                } else if (pilihantransaksi == 3){
                    tampilkanAntrean(antrean);
                } else if (pilihantransaksi == 4){
                    tampilkanAntreanPertama(antrean);
                } else if (pilihantransaksi == 5){
                    tampilkanAntreanTerakhir(antrean);
                } else if (pilihantransaksi == 6){
                    tampilkanJumlahAntrean(antrean);
                } else if (pilihantransaksi == 7){
                    kirimBoxDalamAntrian(antrean);
                } else {
                    printf("Pilihan tidak valid.\n");
                }
            
            } while (pilihantransaksi != 8);
        }
    } while (pilih != 0);    
}

//========================================================
// fungsi tambah data (safira)
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
    
    printf("Masukkan harga barang (per box): ");
    scanf("%f", &pNew->harga);
    printf("Masukkan jumlah stok barang (per box):  ");
    scanf("%d", &pNew->stock);


    pNew->next = *head;
    *head = pNew;
    printf("Data berhasil ditambahkan!\n");
    getchar();
        
}

//========================================================
// fungsi ubah data (safira)
void ubahData(barang **head){
    char nama[100];
    barang *PCur = *head;

    system("cls");
    printf("masukkan nama barang yang akan diubah: ");
    fflush(stdin);
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = '\0';
    trim(nama);

    for (int i = 0; nama[i]; i++)
    {
        nama[i] = tolower(nama[i]);
    }

    barang PCur = PCur->next;
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

            printf("Masukkan harga barang (per box) baru: ");
            scanf("%f", &PCur->harga);

            printf("Masukkan jumlah stok barang (per box)baru : ");
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
// fungsi hapus data //safira

void hapusData(barang **head){
    char nama[100];
    system("cls");

    printf("Masukkan nama barang akan dihapus: ");
    fflush(stdin);
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = '\0';
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
            getchar();
            return;  
        }

        ppre = pCur;
        pCur = pCur->next;
    }

    printf("barang tidak ditemukan!\n");
    getchar();
    
}

//========================================================
// fungsi tampilkan data (lucky)

void tampilData (barang **head){
    if (*head == NULL)
    {
        printf("tidak ada data barang yang tersedia.\n");
        getchar();
        return;
    }

    barang  *pCur = *head;
    printf("daftar barang:\n");

    while (pCur != NULL){
        printf("Nama Barang : %s\n", pCur->namabarang);
        printf("Kategori : %s\n", pCur->kategori);
        printf("Harga Barang : %.2f\n", pCur->harga);
        printf("Stok Barang : %d\n", pCur->stock);
        printf("--------------------------\n");
        pCur = pCur->next;
    }
    
getchar();

    
}

//========================================================
//FUNGSI STACK (noval)
//memasukkan barang yang telah diinput kegudang dengan push 

void push(Stack** stack, barang* box) {
    Stack* baru = (Stack*)malloc(sizeof(Stack));
    baru->box = box;
    baru->next = *stack;
    *stack = baru;
}


//========================================================
//pindah box ke gudang (noval)

void pindahKeGudang(barang **head, Stack** gudang);
//ISI DISINI

//========================================================
//menampilkan barang yang sudah dipindah ke gudang (noval)
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
// Fungsi untuk mengambil barang dari gudang (stack) (noval)

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

//========================================================
//FUNGSI QUEUE  //lucky

void initqueue(queue** q){
    *q = (queue*)malloc(sizeof(queue));
    (*q)->front = NULL;
    (*q)->rear = NULL;
}

//==================================================================================================
//berlian

void enqueue(queue* q, barang* item, int jumlah){
    transaksi* t = (transaksi*) malloc(sizeof(transaksi));
    t->item = item;
    t->jumlah = jumlah;
    t->totalprice = item->harga *jumlah;
    t->antrean = (q->rear == NULL) ? 1 : (q->rear->antrean+1);
    t->next = NULL;

    if(q->rear == NULL){
        q->front = t;
    } else {
        q->rear->next = t;
    }
    q->rear = t;
    printf("Transaksi berhasil ditambahkan! anda berada di antrean ke-%d. \n", t->antrean);
}

//==================================================================================================
// berlian
//Fungsi untuk menambah Transaksi
void tambahTransaksi(queue* q, barang* head){
    system("cls");
    if (head != NULL){
        int jumlah;
        printf("Masukkan Jumlah Barang yang Dibeli: ");
        scanf("%d", &jumlah);
        enqueue(q, head, jumlah);
    } else {
        printf("Tidak ada barang untuk ditransaksikan.\n");
    }
}


//==================================================================================================
// Fungsi untuk menampilkan jumlah transaksi //berlian

void tampilJumlahTransaksi(queue* q){
    system("cls");
    if (q->front == NULL){
        printf("Tidak ada transaksi yang terjadi.\n");
        return;
    }
    int count = 0; //Untuk menghitung jumlah total transaksi
    transaksi* temp = q->front;

    //Iterasi semua transaksi dalam antrean
    while (temp != NULL){
        count++;
        temp = temp->next;
    }
    
    printf("Jumlah transaksi yang terjadi: %d\n", count);
}


//==================================================================================================
// Fungsi untuk menampilkan antrean //lucky

void tampilkanAntrean(queue* q) {
    system("cls");
    if (q->front == NULL){
        printf("Antrian Kosong.\n");
        return;
    }

    transaksi* temp = q->front;
    printf("Daftar Antrean;\n");
    while (temp != NULL){
        printf("Antrean ke-%d: Barang: %s, Jumlah: %d, Total: %.2f\n",
                temp->antrean, temp->item->namabarang, temp->jumlah, temp->totalprice);
        temp = temp->next;
    }
}


//==================================================================================================
//Fungsi untuk menampilkan antrean pertama //lucky

void tampilkanAntreanPertama(queue* q) {
    system("cls");
    if (q->front != NULL){
        printf("Antrean Pertama : Barang; %s, Jumlah: %d, Total: %.2f\n",
                q->front->item->namabarang, q->front->jumlah, q->front->totalprice);
    } else {
        printf("Antrian kosong.\n");
    }
}

//==================================================================================================
//Fungsi untuk menampilkan antrean terakhir //steven

void tampilkanAntreanTerakhir(queue* q) {
    system("cls");
    if (q->rear = NULL) {
        printf("tidak ada antrean saat ini. \n");
        return;
}

    printf("antrean terakhir:\n");
    printf("barang: %s\n", q->rear->item->namabarang);
    printf("jumlah: %d\n, q->rear->jumlah");
    printf("total harga: %.2f\n", q->rear->totalprice);
    printf("nomor antrean: %d\n, q->rear->antrean");

}


//==================================================================================================
//Fungsi untuk menampilkan jumlah antrean //steven
void tampilkanJumlahAntrean(queue* q) {
    system("cls");
    if (q->front == NULL){
        printf("Antrian kosong.\n");
        return;
    }
    int count = 0;
    transaksi* temp = q->front;
    while (temp != NULL){
        count++;
        temp = temp->next;
    }
    printf("Jumlah antrian: %d\n", count);
}


//==================================================================================================
//steven
transaksi* dequeue(queue* q) {
    if (q->front == NULL) {
        printf("Antrian Kosong!\n");
        return NULL;
    }

    transaksi* temp = q->front;
    q->front = q->front->next;

    if(q->front == NULL) {
        q->rear = NULL;
    }

    return temp;
}

//==================================================================================================
// Fungsi untuk mengirim box dalam antrian
//steven
void kirimBoxDalamAntrian(queue* q) {
    system("cls");
    transaksi* t = dequeue(q);
    if (t != NULL){
        printf("Transaksi ke-%d dengan barang %s (jumlah: %d, total: %.2f) telah diproses.\n",
                t->antrean, t->item->namabarang, t->jumlah, t->totalprice);
        free(t);
    }
}