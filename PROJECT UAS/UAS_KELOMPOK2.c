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
    barang* box;             
   struct Stack* next;   
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

void push(Stack** gudang, barang* box);
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
    
    while (isspace((unsigned char)*str)) str++;
    
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
            printf("1. Tambah Data Barang\n");
            printf("2. Ubah Data Barang\n");
            printf("3. Hapus Data Barang\n");
            printf("4. Tampil Data Barang\n");
            printf("5. Kembali ke Menu Utama\n");
            printf("Pilih menu (1-5): ");
            scanf("%d", &pilihdatabarang);
            getchar();

            if (pilihdatabarang == 1)
                tambahData(&head);
            else if (pilihdatabarang == 2)
                ubahData(&head);
            else if (pilihdatabarang == 3)
                hapusData(&head);
            else if (pilihdatabarang == 4)
                tampilData(&head);
            } while (pilihdatabarang != 5);
        }

        else if (pilih == 2)
        {
            int pilihpindahbarang;
            do
            {
            
            system("cls");
            printf("1. Pindah box ke gudang\n");
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
// fungsi tambah data 
void tambahData(barang **head){
    barang *pNew = (barang *)malloc(sizeof(barang));
    system("cls");

    printf("Masukkan nama barang: ");
    fflush(stdin);
    fgets(pNew->namabarang, sizeof(pNew->namabarang), stdin);
    trim(pNew->namabarang);
    if (strlen(pNew->namabarang) == 0) {
        printf("Nama barang tidak boleh kosong!\n");
        free(pNew);
        return;
    }
    for (int i = 0; pNew->namabarang[i] != '\0'; i++){
        pNew->namabarang[i] = tolower(pNew->namabarang[i]);
    }

    printf("Masukkan kategori barang: ");
    fflush(stdin);
    fgets(pNew->kategori, sizeof(pNew->kategori), stdin);
    trim(pNew->kategori);
    if (strlen(pNew->kategori) == 0) {
        printf("Kategori tidak boleh kosong!\n");
        free(pNew);
        return;
    }
    for (int i = 0; pNew->kategori[i] != '\0'; i++) {
        pNew->kategori[i] = tolower(pNew->kategori[i]);
    }
    
    printf("Masukkan harga barang (per box): ");
    if (scanf("%f", &pNew->harga) != 1) {
        printf("Input harga tidak valid\n");
        free(pNew);
        return;
    }
    
    printf("Masukkan jumlah stok barang (per box):  ");
    if (scanf("%d", &pNew->stock) != 1) {
        printf("Input stok tidak valid\n");
        free(pNew);
        return;
    }
    

    pNew->next = *head;
    *head = pNew;

    printf("Data berhasil ditambahkan!\n");
    getchar();
        
}

//========================================================
// fungsi ubah data 
void ubahData(barang **head){
    char nama[100];
    barang *PCur = *head;

    system("cls");

    printf("Daftar nama barang yang tersedia:\n");
    while (PCur != NULL) {
        printf("- %s\n", PCur->namabarang);
        PCur = PCur->next;
    }
    printf("--------------------------\n");
    
    printf("masukkan nama barang yang akan diubah: ");
    fflush(stdin);
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = '\0';
    trim(nama);

    for (int i = 0; nama[i]; i++) {
        nama[i] = tolower(nama[i]);
    }

    PCur = *head;
    while (PCur != NULL){
        if (strcmp(PCur->namabarang, nama) == 0) {
            printf("Barang ditemukan: %s\n", PCur->namabarang);

            char input[100];
            printf("Masukkan nama barang baru (kosongkan untuk tetap menggunakan nama '%s'): ", PCur->namabarang);
            fflush(stdin);
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';
            trim(input);

            if (strlen(input) > 0) {
                strcpy(PCur->namabarang, input);
                for (int i = 0; PCur->namabarang[i]; i++) {
                    PCur->namabarang[i] = tolower(PCur->namabarang[i]);
                }
            }
            
            printf("Masukkan kategori barang baru (kosongkan untuk tetap menggunakan kategori '%s'): ", PCur->kategori);
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';
            trim(input);

            if (strlen(input) > 0) {
                strcpy(PCur->kategori, input);
                for (int i = 0; PCur->kategori[i]; i++) {
                    PCur->kategori[i] = tolower(PCur->kategori[i]);
                }
            }

            printf("Masukkan harga barang baru (kosongkan untuk tetap menggunakan kategori %.2f): ", PCur->harga);
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';

            if (strlen(input) > 0) {
                PCur->harga = atof(input);
            }
            

            printf("Masukkan jumlah stok barang  (kosongkan untuk tetap menggunakan kategori %d): ", PCur->stock);
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';

            if (strlen(input) > 0) {
                PCur->harga = atoi(input);
            }

            printf("Data berhasil diubah!\n");
            getch();
            return;
        }

        PCur = PCur->next;
    }  

    printf("Data tidak ditemukan!\n");
    getch();
}

//========================================================
// fungsi hapus data 

void hapusData(barang **head){
    char nama[100];
    barang *pCur = *head;

    system("cls");

    printf("Masukkan nama barang yang tersedia:\n");
    while (pCur != NULL) {
        printf("- %s\n", pCur->namabarang);
        pCur = pCur->next;
    }
    printf("--------------------------\n");


    printf("Masukkan nama barang yang akan dihapus: ");
    fflush(stdin);
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = '\0';
    trim(nama);

    pCur = *head;
    barang *ppre = NULL;

    while (pCur != NULL)
    {
        if (strcmp(pCur->namabarang, nama) == 0) {
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

void tampilData (barang **head) {

    system("cls");
    if (*head == NULL) {
        printf("Tidak ada data barang yang tersedia.\n");
        getchar(); 
        return;
    }

    printf("Daftar nama barang yang tersedia:\n");
    barang *pCur = *head;
    while (pCur != NULL) {
        printf("- %s\n", pCur->namabarang);
        pCur = pCur->next;
    }
    printf("--------------------------\n");

    char namaBarang[50];
    printf("Masukkan nama barang yang ingin ditampilkan: ");
    fflush(stdin);
    fgets(namaBarang, sizeof(namaBarang), stdin);
    trim(namaBarang);

    for (int i = 0; namaBarang[i] != '\0'; i++) {
        namaBarang[i] = tolower(namaBarang[i]);
    }

    pCur = *head;
    int ditemukan = 0;

    while (pCur != NULL) {
        if (strcmp(pCur->namabarang, namaBarang) == 0) { 
            printf("Barang ditemukan:\n");
            printf("Nama Barang     : %s\n", pCur->namabarang);
            printf("Kategori        : %s\n", pCur->kategori);
            printf("Harga Barang    : %.2f\n", pCur->harga);
            printf("Stock Barang    : %d\n", pCur->stock);
            printf("----------------------------\n");
            ditemukan = 1;
            break;
        }
        pCur = pCur->next;
    }

    if (!ditemukan) {
        printf("Barang dengan nama '%s' tidak ditemukan.\n", namaBarang);
    }

    getchar(); 
}

//========================================================
//memasukkan barang yang telah diinput kegudang dengan push 

void push(Stack** gudang, barang* box) {
    Stack* newNode = (Stack*)malloc(sizeof(Stack));
    if (newNode == NULL) {
        printf("Alokasi Memori Gagal!!\n");
        return;
    }
    newNode->box = (barang*)malloc(sizeof(barang));
    if (newNode->box == NULL) {
        printf("Alokasi Memori Untuk Box Gagal!!\n");
        free(newNode);
        return;
    }

    strcpy(newNode->box->namabarang, box->namabarang);
    strcpy(newNode->box->kategori, box->kategori);
    newNode->box->harga = box->harga;
    newNode->box->stock = box->stock;

    newNode->next = *gudang;
    *gudang = newNode;
    
}


//========================================================
//pindah box ke gudang 

void pindahKeGudang(barang **head, Stack** gudang) {
    system("cls");
    if(*head != NULL) {
        printf("Daftar Barang Yang Tersedia: \n");

        printf("Daftar nama barang yang tersedia: \n");
        barang *pCur = *head; 
        while (pCur != NULL) {
            printf("- %s\n", pCur->namabarang);
            pCur = pCur->next;
        }
        printf("--------------------------\n");

        char nama[100];
        printf("Masukkan nama barang yang akan dipindahkan ke gudang: ");
        fflush(stdin);
        fgets(nama, sizeof(nama), stdin);
        nama[strcspn(nama, "\n")] = '\0';

        pCur = *head;
        barang* prev = NULL;

        while (pCur != NULL) {
            if (strcmp(pCur->namabarang, nama) == 0) {
                
                push(gudang, pCur);

                if (prev == NULL) {
                    *head = pCur->next;
                }else {
                    prev->next = pCur->next;
                }
                free(pCur);
                printf("Yess! Barang berhasil dipindahkan ke gudang.\n");
                getchar();
                return;
            }
            prev = pCur;
            pCur = pCur->next;
        }
        printf("Barang dengan nama '%s' tidak ditemukan!\n", nama);
        getchar();
    } else {
        printf("Tidak ada barang untuk dipindahkan ke gudang.\n");
        getchar();
    }
}


//========================================================
//menampilkan barang yang sudah dipindah ke gudang 
void tampilkanGudang(Stack* stack) {
    system("cls");

    if (stack == NULL) {
        printf("Gudang kosong.\n");
        printf("Tekan Enter untuk kembali ke menu...");
        getchar();
        return;
    }

    Stack* temp = stack;
    printf("Barang di gudang: \n");
    while (temp != NULL) {
        
        printf("=======================\n");
        printf("Nama Barang : %s\n", temp->box->namabarang);
        printf("Kategori    : %s\n", temp->box->kategori);
        printf("Harga       : %.2f\n", temp->box->harga);
        printf("Jumlah Stok : %d\n", temp->box->stock);
        printf("----------------------\n");
        
        temp = temp->next;
    }
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}

//========================================================
// Fungsi untuk mengambil barang dari gudang (stack) 

barang* pop(Stack** stack) {
    if (*stack == NULL) {
        printf("Gudang kosong!!\n");
        return NULL;
    }
    Stack* temp = *stack;
    barang* box = temp->box;
    *stack = (*stack)->next;
    free(temp);
    return box;
}

//========================================================
//FUNGSI QUEUE  

void initqueue(queue** q) {
    *q = (queue*)malloc(sizeof(queue));
    if (*q == NULL) {
        printf("Gagal mengalokasikan memori untuk antrean.\n");
        exit(1); 
    }
    (*q)->front = NULL;
    (*q)->rear = NULL;
}

//==================================================================================================

void enqueue(queue* q, barang* item, int jumlah) {
    transaksi* t = (transaksi*) malloc(sizeof(transaksi));
    t->item = item;
    t->jumlah = jumlah;
    t->totalprice = item->harga *jumlah;
    t->antrean = (q->rear == NULL) ? 1 : (q->rear->antrean+1);
    t->next = NULL;

    if(q->rear == NULL) {
        q->front = t;
    } else {
        q->rear->next = t;
    }
    q->rear = t;
    printf("Transaksi berhasil ditambahkan! anda berada di antrean ke-%d. \n", t->antrean);
}

//==================================================================================================
//Fungsi untuk menambah Transaksi
void tambahTransaksi(queue* q, Stack** gudang){
    system("cls");
    if (*gudang == NULL) {
        printf("Gudang kosong. Tidak dapat memproses transaksi. \n");
        getchar();
        return;
    }

    int jumlahBarangDipilih = 0;
    float totalHarga = 0.0;
    barang* barangDipilih[100]; 
    int jumlah[100];

    printf("Daftar Barang Tersedia di Gudang:\n");
    Stack* gudangTemp = *gudang;
    int index = 0;
    while (gudangTemp != NULL){
        printf("%d. Nama Barang : %s\n", index + 1, gudangTemp->box->namabarang);
        printf("    Kategori    : %s\n", gudangTemp->box->kategori);
        printf("    Harga       : %.2f\n", gudangTemp->box->harga);
        printf("    Jumlah Stock: %d\n", gudangTemp->box->stock);
        printf("-----------------------------\n");
        gudangTemp = gudangTemp->next;
        index++;
    }

    if (index == 0 ) {
        printf("Tidak ada barang yang dapat dipilih.\n");
        return;
    }

    printf("Masukkan jumlah barang yang ingin dibeli: ");
    scanf("%d", &jumlahBarangDipilih);
    getchar(); 

    for (int i = 0; i < jumlahBarangDipilih; i++) {
        char namaBarang[100];
        int barangTersedia = 0;

        while (1) {
            printf("masukkan nama barang ke-%d: ", i + 1);
            fgets(namaBarang, sizeof(namaBarang), stdin);
            namaBarang[strcspn(namaBarang, "\n")] = 0;

            gudangTemp = *gudang;
            while (gudangTemp != NULL){
                if (strcmp(gudangTemp->box->namabarang, namaBarang) == 0) {
                    barangTersedia = 1;
                    break;
                }
                gudangTemp = gudangTemp->next;
            }

            if (!barangTersedia) {
                printf("Barang tidak tersedia, coba lagi.\n");
            } else {
                break;
            }
        }

        barangDipilih[i] = gudangTemp->box;
        jumlah[i] = 1; 
        totalHarga += gudangTemp->box->harga;

        Stack* prev =  NULL;
        gudangTemp = *gudang;
        while (gudangTemp != NULL){
            if (strcmp(gudangTemp->box->namabarang, namaBarang) == 0) {
                break;
            }
            prev = gudangTemp;
            gudangTemp = gudangTemp->next;
        }

        if (prev != NULL) {
            prev->next = gudangTemp->next;
        } else {
            *gudang = gudangTemp->next;
        }
        free(gudangTemp);
    }

    transaksi* newTransaksi = (transaksi*)malloc(sizeof(transaksi));
    newTransaksi->item = (barang*)malloc(sizeof(barang) * jumlahBarangDipilih); 
    for (int i = 0; i < jumlahBarangDipilih; i++){
        newTransaksi->item[i] = *barangDipilih[i];
    }

    if (jumlahBarangDipilih == 0) {
        printf("Tidak ada barang yang dipilih. Transaksi batal.\n");
        free(newTransaksi->item);
        free(newTransaksi);
        return;
    }

    newTransaksi->jumlah = jumlahBarangDipilih;
    newTransaksi->totalprice = totalHarga;
    newTransaksi->next = NULL;

    int posisiAntrean = 1;
    if (q->rear != NULL) {
        posisiAntrean = q->rear->antrean + 1; 
    }
    newTransaksi->antrean = posisiAntrean; 

    if (q->rear == NULL) {
        q->front = newTransaksi;
    } else {
        q->rear->next = newTransaksi;
    }
    q->rear = newTransaksi;

    printf("\nTransaksi berhasil!\n");
    printf("Total harga: %.2f\n", totalHarga);
    printf("Transaksi telah dimasukkan ke dalam antrean pada posisi ke-%d.\n", posisiAntrean);
    printf("Tekan Enter untuk kembali ke menu...");
    getchar(); 
}


//==================================================================================================
// Fungsi untuk menampilkan jumlah transaksi 

void tampilJumlahTransaksi(queue* q){
    system("cls");
    if (q->front == NULL) {
        printf("Tidak ada transaksi yang terjadi.\n");
        printf("Tekan Enter untuk kembali ke menu..");
        getchar(); 
        return;
    }
    int count = 0; 
    transaksi* temp = q->front;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    
    printf("Jumlah transaksi yang terjadi: %d\n", count);
    printf("Tekan Enter untuk kembali ke menu...");
    getchar(); 
}


//==================================================================================================
// Fungsi untuk menampilkan antrean 

void tampilkanAntrean(queue* q) {
    system("cls");
    if (q->front == NULL){
        printf("Antrian Kosong.\n");
        getch();
    }

    transaksi* temp = q->front;
    printf("Daftar Antrean:\n");
    printf("================================\n");
    while (temp != NULL){
        printf("Antrean ke-%d\n", temp->antrean);

        if (temp->item != NULL){
            printf("  Barang  :\n");
            for (int i = 0; i < temp->jumlah; i++){ 
                if (temp->item[i].namabarang != NULL) {
                    printf("    - %s\n", temp->item[i].namabarang);
                } else {
                    printf("    - Nama barang tidak valid\n");
                }
            }
            printf("    Jumlah  : %d\n", temp->jumlah);
            printf("    Total   : %.2f\n", temp->totalprice);
        } else {
            printf("    Data barang tidak valid.\n");
        }
        printf("---------------------------------\n");

        temp = temp->next;
    }
    printf("================================\n");
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}


//==================================================================================================
//Fungsi untuk menampilkan antrean pertama 

void tampilkanAntreanPertama(queue* q) {
    system("cls");
    if (q->front != NULL) {
        printf("Antrean Pertama:\n");
        printf("=======================================\n");

        if (q->front->item != NULL) {
            printf("  Barang  :\n");
            for (int i = 0; i < q->front->jumlah; i++) {
                if (q->front->item[i].namabarang != NULL) {
                    printf("    - %s\n", q->front->item[i].namabarang); 
                } else {
                    printf("    - Nama barang tidak valid\n");
                }
            }
            printf("    Jumlah  : %d\n", q->front->jumlah);
            printf("    Total   : %.2f\n", q->front->totalprice);
        } else {
            printf("    Data barang tidak valid.\n");
        }
        printf("=================================\n");
    } else {
        printf("Antrian kosong.\n");
    }

    printf("Tekan Enter untuk kembali ke menu...");
    getchar();
}

//==================================================================================================
//Fungsi untuk menampilkan antrean terakhir

void tampilkanAntreanTerakhir(queue* q) {
    system("cls");

    if (q->rear == NULL) {
        printf("Tidak ada antrean saat ini.\n");
        getchar(); 
        return; 
    }

    if (q->rear->item != NULL) {
        printf("Antrean terakhir:\n");
        printf("Barang      : %s\n", q->rear->item->namabarang);
        printf("Jumlah      : %d\n", q->rear->jumlah);
        printf("Total Harga : %.2f\n", q->rear->totalprice);
        printf("Nomor Antrean : %d\n", q->rear->antrean);
    } else {
        printf("Data transaksi terakhir tidak valid.\n");
    }

    printf("Tekan Enter untuk kembali ke menu...");
    getchar(); 
}


//==================================================================================================
//Fungsi untuk menampilkan jumlah antrean

void tampilkanJumlahAntrean(queue* q) {
    system("cls");
    if (q->front == NULL) {
        printf("Antrian kosong.\n");
        getchar();  
        return;
    }
    
    int count = 0;
    transaksi* temp = q->front;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    printf("Jumlah antrian: %d\n", count);
    printf("Tekan Enter untuk kembali ke menu...");
    getchar();  
}


//==================================================================================================

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
void kirimBoxDalamAntrian(queue* q) {
    system("cls");

    transaksi* t = dequeue(q);
    if (t != NULL) {
        printf("Transaksi ke-%d dengan barang %s (jumlah: %d, total: %.2f) telah diproses.\n",
                t->antrean, t->item->namabarang, t->jumlah, t->totalprice);

        
        free(t);  
    } else {
        printf("Tidak ada transaksi dalam antrean.\n");
    }

    printf("Tekan Enter untuk kembali ke menu...");
    getchar(); 
}