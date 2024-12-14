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
void enqueue(queue* q, barang* item, int jumlah);
transaksi* dequeue(queue* q);
void initqueue(queue** q);
void tambahTransaksi(queue* q, barang* head);
void tampilkanAntrean(queue* q);
void tampilkanAntreanPertama(queue* q);
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
    barang* boxList = NULL;
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
            printf("1. pindah box ke gudang\n");
            printf("2. Tampil data box di gudang \n");
            printf("3. Kembali ke Menu Utama\n");
            printf("Pilih menu (1-3): ");
            scanf("%d", &pilihpindahbarang);
            getchar();

            if (pilihpindahbarang == 1)
                if (head != NULL) {
                    push(&gudang, head); // Memindahkan barang ke gudang
                    head = head->next;   // Menghapus barang dari daftar utama
                } else {
                    printf("Tidak ada barang untuk dipindahkan ke gudang.\n");
                }
                else if (pilihpindahbarang == 2)
                    tampilkanGudang(gudang);                        
            } while (pilihpindahbarang != 3);
        }
        
        else if (pilih == 3)
        {
            int pilihantransaksi;
            do
            {
            printf("1. Tambah Transaksi\n");
            printf("2. Tampilkan box data antrean \n");
            printf("3. Menampilkan antrian pertama\n");
            printf("4. Menampilkan antrian terakhir\n");
            printf("5. Menampilkan jumlah antrian\n");
            printf("6. Kirim box dalam antrian\n");
            printf("7. Kembali ke menu utama\n");
            printf("8. Tampilkan jumlah transaksi\n");
            printf("Pilih menu (1-8): ");
            scanf("%d", &pilihantransaksi);
            getchar();
            switch (pilihantransaksi){
                case 1: 
                    tambahTransaksi(antrean, head);
                    break;
                case 2:
                    tampilkanAntrean(antrean);
                    break;
                case 3:
                    tampilkanAntreanPertama(antrean);
                    break;
                case 4:
                    tampilkanAntreanTerakhir(antrean);
                    break;
                case 5:
                    tampilkanJumlahAntrean(antrean);
                    break;
                case 6: 
                    kirimBoxDalamAntrian(antrean);
                    break;
                case 7:
                    printf("Kembali ke menu utama.\n");
                    break;
                case 8:
                    tampilkanJumlahTransaksi(antrean);
                    break;
                default:
                    printf("Pilihan tidak valid.\n");
                }
            }while (pilihantransaksi != 7);
            return 0;
        }
    } while (pilih != 0);

    return 0;

    if (pilihantransaksi < 1 || pilihantransaksi > 8){
        printf("pilihan tidak valid. Silahkan pilih kembali.\n");
        continue;
    }
    if (pilih == 0){
        printf("Apakah anda yakin ingin keluar? (y/n): ");
        char confirm;
        scanf("%c", &confirm);
        if (confirm == 'y' || confirm == 'Y'){
            break;
        }
    }
    
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
// fungsi tampilkan data 

void tampilData (barang **head){
    if (*head == NULL)
    {
        printf("tidak ada data barang yang tersedia.\n");
        getchar();
        return;
    }

    barang  *pCur = *head;
    printf("daftar barang:\n");

    while (pCur = pCur->next);
    {
        printf("Nama Barang : %s\n", pCur->namabarang);
        printf("Kategori : %s\n", pCur->kategori);
        printf("Harga Barang : %f\n", pCur->harga);
        printf("Stok Barang : %d\n", pCur->stock);
    }
    
getchar();

    
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
void initqueue(queue** q){
    *q = (queue*)malloc(sizeof(queue));
    (*q)->front = NULL;
    (*q)->rear = NULL;
}

void enqueue(queue* q, barang* item, int jumlah){
    transaksi* t = (transaksi*) malloc(sizeof(transaksi));
    t->item = item;
    t->jumlah = jumlah;
    t->totalprice = item->harga *jumlah;
    t->antrean = (q->rear == NULL) ? 1 : (q->rear->antrean+1);
    t->next = NULL;

    if(q->rear == NULL){
        q->front = t;
        q->rear = t;
    }else{
        q->rear->next = t;
        q->rear = t;
    }
    printf("Transaksi berhasil ditambahkan! anda berada di antrean ke-%d. \n", t->antrean);
}

transaksi* dequeue(queue* q) {
    if(q->front == NULL) {
        printf("Antrian Kosong!\n");
        return 0;
    }

    transaksi* temp = q->front;
    q->front = q->front->next;
    if(q->front == NULL){
        q->rear = NULL;
    }
    return temp;
}

//==================================================================================================
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

// Fungsi untuk menampilkan antrean
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


//Fungsi untuk menampilkan antrean pertama
void tampilkanAntreanPertama(queue* q) {
    system("cls");
    if (q->front != NULL){
        printf("Antrean Pertama : Barang; %s, Jumlah: %d, Total: %.2f\n",
                q->front->item->namabarang, q->front->jumlah, q->front->totalprice);
    } else {
        printf("Antrian kosong.\n");
    }
}

//Fungsi untuk menampilkan jumlah antrean
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

//Fungsi untuk mengirim box dalam antrian
void kirimBoxDalamAntrian(queue* q) {
    system("cls");
    transaksi* t = dequeue(q);
    if (t != NULL){
        printf("Transaksi ke-%d dengan barang %s (jumlah: %d, total: %.2f) telah diproses.\n",
                t->antrean, t->item->namabarang, t->jumlah, t->totalprice);
        free(t);
    }
}

//Fungsi untuk menampilkan antrean terakhir
void tampilkanAntreanTerakhir(queue* q) {
    system("cls");
    if (q->rear != NULL) {
        printf("Antrean Terakhir: Barang: %s, Jumlah: %d, Total: %.2f\n",
               q->rear->item->namabarang, q->rear->jumlah, q->rear->totalprice);
    } else {
        printf("Antrian kosong.\n");
    }
}

//Fungsi untuk menampilkan jumlah transaksi
void tampilkanJumlahTransaksi(queue* q) {
    system("cls");
    if (q->front == NULL){
        printf("Tidak ada transaksi yang terjadi.\n")
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