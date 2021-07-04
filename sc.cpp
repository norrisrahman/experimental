#include <iostream>
#include <array>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

struct Record {
	string tanggal;
	string ID;
    int jumlahTelur;
    int harga;
};

int dataSize(fstream &Database);
void addData(Record ternak);
void inputData();
void readData();
void printData();
void sortData(int x);
void saveDB(struct Record sortRecord[], int size);
void searchData();
void Search();
void updateData();
void deleteData();

int main() {
    string x;

    cout << "===================================================" << endl;
    cout << "    Program Record Data Peternakan Ayam Petelur" << endl;
    cout << "===================================================" << endl;

    menu:
    // system("cls");
    cout << "Pilih Jenis Operasi :" << endl;
    cout << "1. Tambah Data" << endl;
    cout << "2. Tampilkan Seluruh Data" << endl;
    cout << "3. Urutkan Data dari Data Terbaru" << endl;
    cout << "4. Urutkan Data Berdasarkan Jumlah Telur" << endl;
    cout << "5. Mencari Data" << endl;
    cout << "6. Update Data" << endl;
    cout << "7. Hapus Data" << endl;
    cout << "8. Exit" << endl;
    cout << endl;

    cout << "Pilih Menu [1-4]: ";
    cin >> x;

    if (x == "1"){
        inputData();
        goto menu;
    }
    else if ( x=="2"){
        readData();
        goto menu;
    }
    else if (x =="3" ) {
        sortData(1);
        goto menu;
    }
    else if (x == "4"){
        sortData(2);
        goto menu;
    }
    else if (x =="5") {
        searchData();
        goto menu;
    }
    else if (x == "6"){
        updateData();
        goto menu;
    }
    else if (x== "7") {
        deleteData();
        system("cls");
        cout << "Penghapusan Data Sukses" << endl;
        goto menu;
    }
    else if (x == "8") {
        system("cls");
        atexit;
    }
    else {
        system ("cls");
        cout << "\nInput Tidak Valid !!! \n" << endl;
        goto menu;
    }
	return 0;
}

void inputData() {
    string tanggal,bulan,tahun, tgl;

    Record ternak;

    system("cls");
    cout << "\nInput Record Harian" << endl;
    cout << "===================================\n"  << endl;
    cout << "Masukkan Tanggal (dd)\t\t: ";
    cin >> tanggal;
    cout << "Masukkan Bulan (mm)\t\t: ";
    cin >> bulan;
    cout << "Masukkan Tahun (yyyy)\t\t: ";
    cin >> tahun;

    ternak.tanggal = tanggal + "/" + bulan + "/" + tahun;

    ternak.ID = tahun + bulan + tanggal;

    cout << "Masukkan Jumlah Telur \t\t: ";
    cin >> ternak.jumlahTelur;
    cout << "Masukkan Harga Telur/Kg \t: ";
    cin >> ternak.harga; 

    addData(ternak);

    cout << endl;
}

void addData( Record ternak) {
    fstream data;
    data.open("data2.txt", ios::app);

    data << ternak.tanggal << "    "<< ternak.ID << "   " << ternak.jumlahTelur << "    " << ternak.harga << endl;

    data.close();
}

int dataSize(fstream &Database) {
    Record dataSize;
    int size;


    Database.open("data2.txt");
    while (getline(Database, dataSize.tanggal))
        size++;

    Database.close();

    return size ;
}

void readData() {
    fstream Database;
    int size;

    size = dataSize(Database);

    Database.open("data2.txt");

    Record* sortRecord = new Record[size];

    for(int i = 0; i<size; i++){

        Database >> sortRecord[i].tanggal;
        Database >> sortRecord[i].ID;
        Database >> sortRecord[i].jumlahTelur;
        Database >> sortRecord[i].harga;
    }

    Database.close();
    
    system("cls");
    cout << "Menampi;kan Semua Data :\n" << endl;
    cout << "Tanggal\t\t\t" << "ID Record\t" << "Jumlah Telur" << "\t" << "Harga /Kg" << endl;
    cout << "======================================================================" << endl;
    for ( int i=0; i<size; i++) {
        cout << sortRecord[i].tanggal << "\t\t" << sortRecord[i].ID << "\t" << sortRecord[i].jumlahTelur << "\t\t"<< "Rp " << sortRecord[i].harga << endl; 
    }

    cout << endl;
}

void sortDesc(struct Record arr[], int n){
    int i, j;
    struct Record key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;        
        while (j >= 0 && arr[j].ID < key.ID) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
            arr[j + 1] = key;
    }
}

void sortQty(struct Record arr[], int n) {
    int i, j;
    struct Record key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;        
        while (j >= 0 && arr[j].jumlahTelur < key.jumlahTelur) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
            arr[j + 1] = key;
    }
}

void sortData(int x) {
    fstream Database;
    int size;

    size = dataSize(Database);

    Database.open("data2.txt");

    Record* sortRecord = new Record[size];

    for(int i = 0; i<size; i++){

        Database >> sortRecord[i].tanggal;
        Database >> sortRecord[i].ID;
        Database >> sortRecord[i].jumlahTelur;
        Database >> sortRecord[i].harga;
    }

    Database.close();

    if (x == 1) {
        sortDesc(sortRecord, size);
        saveDB(sortRecord, size);
    }
    else if ( x== 2) {
        sortQty(sortRecord, size);
        saveDB(sortRecord, size);
    }
    
    system("cls");
    cout << "Hasil Pengurutan Data :\n" << endl;
    cout << "Tanggal\t\t\t" << "ID Record\t" << "Jumlah Telur" << "\t" << "Harga /Kg" << endl;
    cout << "======================================================================" << endl;
    for ( int i=0; i<size; i++) {
        cout << sortRecord[i].tanggal << "\t\t" << sortRecord[i].ID << "\t" << sortRecord[i].jumlahTelur << "\t\t"<< "Rp " << sortRecord[i].harga << endl; 
    }

    cout << endl;
    
}

void saveDB(struct Record sortRecord[], int size) {

    fstream Database;
    Database.open("data2.txt", ios::trunc | ios::out);

    for (int i=0; i < size; i++){

        Database << sortRecord[i].tanggal << "    " << sortRecord[i].ID << "   " << sortRecord[i].jumlahTelur << "      " << sortRecord[i].harga << endl;
    }

    Database.close();
}

void printErr () {
    system ("cls");
    cout << "\n\nKeyword Invalid / Data Tidak Ada\n\n"<< endl;
}

void printSearch (Record array) {
    system ("cls");
    cout << "\nHasil Pencarian Data :\n" << endl;
    cout << "Tanggal\t\t\t" << "ID Record\t" << "Jumlah Telur" << "\t" << "Harga /Kg" << endl;
    cout << "======================================================================" << endl;
    cout << array.tanggal << "\t\t" << array.ID << "\t" << array.jumlahTelur << "\t\t"<< "Rp " << array.harga << endl;
    cout << endl; 
}

void searchData () {
    string keyword;
    int size;

    fstream Database;

    size = dataSize(Database);

    Database.open("data2.txt");

    Record* array = new Record[size];

    for(int i = 0; i<size; i++){

        Database >> array[i].tanggal;
        Database >> array[i].ID;
        Database >> array[i].jumlahTelur;
        Database >> array[i].harga;
    }

    Database.close();

    cout<<"Masukkan Tanggal Record (dd/mm/yyyy) : ";
    cin >> keyword;

    for(int i=0;i<size;i++) {
        if(array[i].tanggal==keyword) {
            cout << "test" << endl;
            printSearch(array[i]);
            return;
        }
    }
    printErr();
}

void updateData() {
    string keyword, tanggal,bulan,tahun, tgl;
    int size;

    fstream Database;

    size = dataSize(Database);

    Database.open("data2.txt");

    Record* array = new Record[size];

    for(int i = 0; i<size; i++){

        Database >> array[i].tanggal;
        Database >> array[i].ID;
        Database >> array[i].jumlahTelur;
        Database >> array[i].harga;
    }

    Database.close();

    readData();

    cout<<"Masukkan Tanggal Record Untuk Update Data (dd/mm/yyyy) : ";
    cin >> keyword;

    for(int i=0;i<size;i++) {
        if(array[i].tanggal==keyword) {
            cout << "\nTanggal\t\t\t" << "ID Record\t" << "Jumlah Telur" << "\t" << "Harga /Kg" << endl;
            cout << "======================================================================" << endl;
            cout << array[i].tanggal << "\t\t" << array[i].ID << "\t" << array[i].jumlahTelur << "\t\t"<< "Rp " << array[i].harga << endl;

            cout << "\nMasukkan Data Baru : " << endl;
                cout << "Masukkan Tanggal \t: ";
                cin >> tanggal;
                cout << "Masukkan Bulan \t\t: ";
                cin >> bulan;
                cout << "Masukkan Tahun \t\t: ";
                cin >> tahun;

                array[i].tanggal = tanggal + "/" + bulan + "/" + tahun;
                array[i].ID = tahun + bulan + tanggal;

                cout << "Masukkan Jumlah Telur \t: ";
                cin >> array[i].jumlahTelur;
                cout << "Masukkan Harga Telur/Kg \t: ";
                cin >> array[i].harga;

                saveDB(array, size);

                cout << endl;
            return;
        }
    }
    printErr();
}

void deleteData () {
    string keyword, tanggal,bulan,tahun, tgl;
    int size;

    fstream Database;

    size = dataSize(Database);

    Database.open("data2.txt");

    Record* array = new Record[size];

    for(int i = 0; i<size; i++){

        Database >> array[i].tanggal;
        Database >> array[i].ID;
        Database >> array[i].jumlahTelur;
        Database >> array[i].harga;
    }

    Database.close();

    readData();

    cout<<"Masukkan tanggal record yang ingin dihapus (dd/mm/yyyy) : ";
    cin >> keyword;

    for(int i=0;i<size;i++) {
        if(array[i].tanggal==keyword) {
            for(int j=i; j<size -1; j++) {
                array[j].tanggal = array[j+1].tanggal;
                array[j].ID = array[j+1].ID;
                array[j].jumlahTelur = array[j+1].jumlahTelur;
                array[j].harga = array[j+1].harga;
            }
            size--;

            saveDB(array, size);
            return;
        }
    }
    printErr(); 
}