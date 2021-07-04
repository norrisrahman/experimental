#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

struct Sayur {
	int pk;
	string sayur;
	string harga;
	string stok;
};

int getOption(){
	int input;
	system("clear");
	cout << "\nPEDAGANG SAYUR, PASAR KRIAN" << endl;
	cout << "\nPilihan untuk Daftar Harga Sayur" << endl;
	cout << "1. Entry Daftar Harga Sayur" << endl;
	cout << "2. Hapus Data Harga Sayur" << endl;
	cout << "3. Tambah Daftar Harga Sayur" << endl;
	cout << "4. Edit Daftar Harga Sayur" << endl;
	cout << "5. Urutkan Daftar Harga Sayur" << endl;
	cout << "6. Mencari Data Harga Sayur" << endl;
	cout << "7. Menampilkan Daftar Harga Sayur yang Ada" << endl;
	cout << "8. Menampilkan Kesalahan Proses" << endl;
	cout << "9. Simpan Daftar Harga Sayur dalam File secara Permanen" << endl;
	cout << "=============================" << endl;
	cout << "pilih [1-9]? : ";
	cin >> input;
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	return input;
}

void checkDatabase(fstream &data){
	data.open("data.bin", ios::out | ios::in | ios::binary);

	// check file ada atau tidak
	if (data.is_open()){
		cout << "Daftar Harga Sayur Tersedia" << endl;
	} else {
		cout << "Daftar Harga Sayur Tidak Tersedia, Silahkan Buat Daftar Baru" << endl;
		data.close();
		data.open("data.bin", ios::trunc | ios::out | ios::in | ios::binary);
	}
}

void writeData(fstream &data, int posisi, Sayur &inputSayur){
	data.seekp((posisi - 1)*sizeof(Sayur), ios::beg);
	data.write(reinterpret_cast<char*>(&inputSayur),sizeof(Sayur));
}

int getDataSize(fstream &data){
	int start, end;
	data.seekg(0,ios::beg);
	start = data.tellg();
	data.seekg(0,ios::end);
	end = data.tellg();
	return (end-start)/sizeof(Sayur);
}

Sayur readSayur(fstream &data, int posisi){
	Sayur readSayur;
	data.seekg((posisi - 1)*sizeof(Sayur),ios::beg);
	data.read(reinterpret_cast<char*>(&readSayur),sizeof(Sayur));
	return readSayur;
}

void tambahDaftarSayur(fstream &data){ //FUNGSI UNTUK ENTRY DATA

	Sayur inputSayur, lastSayur;

	int size = getDataSize(data);

	cout << "Ukuran data : " << size << endl;

	if(size == 0){
		inputSayur.pk = 1;
	} else {
		lastSayur = readSayur(data,size);
		cout << "pk = " << lastSayur.pk << endl;
		inputSayur.pk = lastSayur.pk + 1;
	}

	cout << "Nama Sayur: ";
	getline(cin, inputSayur.sayur);
	cout << "Harga Sayur (per 100g): ";
	getline(cin, inputSayur.harga);
	cout << "Stok Sayur yang tersedia/gram: ";
	getline(cin, inputSayur.stok);

	writeData(data,size+1,inputSayur);
}

void displayDaftarSayur(fstream &data){ //FUNGSI UNTUK MENAMPILKAN DATA YANG SEDANG DIPROSES
	int size = getDataSize(data);
	Sayur showSayur;
	cout << "no.\tpk.\tSayur.\tHarga (per 100g).\tStok/gram." << endl;
	for(int a = 1; a <= size; a++){
		showSayur = readSayur(data,a);
		cout << a << "\t";
		cout << showSayur.pk << "\t";
		cout << showSayur.sayur << "\t";
		cout << showSayur.harga << "\t";
		cout << showSayur.stok << endl;
	}
}

void editDaftarSayur(fstream &data){ //FUNGSI UNTUK EDIT DATA
	int nomor;
	Sayur updateSayur;
	cout << "Nomor yang dipilih: ";
	cin >> nomor;
	cin.ignore(numeric_limits<streamsize>::max(),'\n');

	updateSayur = readSayur(data,nomor);

	cout << "\n\nData yang dipilih: " << endl;
	cout << "Nama Sayur : " << updateSayur.sayur << endl;
	cout << "Harga Sayur (per 100g): " << updateSayur.harga << endl;
	cout << "Stok Sayur yang tersedia/gram: " << updateSayur.stok << endl;

	cout << "\nSilahkan diubah daftar harga sayur: "<< endl;
	cout << "Nama Sayur : ";
	getline(cin,updateSayur.sayur );
	cout << "Harga Sayur (per 100g):";
	getline(cin,updateSayur.harga);
	cout << "Stok Sayur yang tersedia/gram: ";
	getline(cin,updateSayur.stok);

	writeData(data,nomor,updateSayur);
}

void hapusDaftarSayur(fstream &data){ //FUNGSI UNTUK HAPUS DATA
	int nomor,size,offset;
	Sayur blankSayur, tempSayur;
	fstream dataSementara;

	size = getDataSize(data);
	cout << "Nomor yang akan dihapus: ";
	cin >> nomor;

	writeData(data,nomor,blankSayur);
	dataSementara.open("temp.dat", ios::trunc|ios::out|ios::in|ios::binary);

	offset = 0;

	for (int a=1 ; a <=size ; a++){
		tempSayur = readSayur(data,a);

		if (!tempSayur.sayur.empty()){
			writeData(dataSementara,a - offset,tempSayur);
		} else {
			offset++;
			cout << "Daftar Harga Sayur Terhapus" << endl;
		}
	}

	size = getDataSize(dataSementara);
	data.close();
	data.open("data.bin",ios::trunc|ios::out|ios::binary);
	data.close();
	data.open("data.bin",ios::out|ios::in|ios::binary);

	for(int a = 1; a <= size; a++){
		tempSayur = readSayur(dataSementara,a);
		writeData(data,a,tempSayur);
	}
}

// void sortHARGA(int harga [], int x){ //Mengurutkan data
//     int urutt;

//     cout << endl;
//     cout << "Urutkan harga secara descending: " << endl;
//     cout << "1. Terbesar ke terkecil" << endl;
//     cout << "2. Terkecil ke terbesar" << endl;
//     cout << "Pilih: " << endl; cin >> urutt;

//     if(urutt==1){
//         int temp, a;
//         for(int a = 0; a < x-1; a++){
//             for (int b = a+1; b < x; b++){
//                 if (harga[a] < harga [b]){
//                     temp = harga[a];
//                     harga[a] = harga [b];
//                     harga[b] = temp;
//                     }}
//     }
//     cout << sortHarga[a].harga <<endl;

//     }else if (urutt==2){
//         int temp, a;
//         for (int a = 0; a < x-1; a++){
//             for (int b = a+1; b < x; b++){
//                 if (harga[a] > harga [b]){
//                     temp = harga[a];
//                     harga[a] = harga [b];
//                     harga[b] = temp;
//                     }}
//                     }
//     cout << sortHarga[a].harga << endl;
//     } else {
//         cout << "Tidak bisa mengurutkan data, harap ketik 1 atau 2" <<endl;
//     }
// }




int main(){

    fstream data;
    checkDatabase(data);

    int pilihan = getOption();
    char is_continue;

    enum option{ENTRY = 1, HAPUS, TAMBAH, EDIT, URUT,CARI, PROSES, SALAH, TXT, SELESAI};
    while(pilihan != SELESAI){
        switch(pilihan){
            case ENTRY:
                cout << "Entry data baru untuk harga sayur" << endl;
                tambahDaftarSayur(data);
                break;
            case HAPUS:
                cout << "Hapus data harga sayur" << endl;
                displayDaftarSayur(data);
                hapusDaftarSayur(data);
                displayDaftarSayur(data);
                break;
            case TAMBAH:
                cout << "Tambah data harga sayur" << endl;
                tambahDaftarSayur(data);
                break;
            case EDIT:
                cout << "Edit daftar harga sayur" << endl;
                displayDaftarSayur(data);
                editDaftarSayur(data);
                displayDaftarSayur(data);
                break;
            case URUT:
                cout << "Urutkan data harga sayur" << endl;
                // sortHARGA();
                break;
            case CARI:
                cout << "Cari data harga sayur" << endl;
                break;
            case PROSES:
                cout << "Tampilkan harga sayur yang sedang diproses" << endl;
                displayDaftarSayur(data);
                break;
            case SALAH:
                cout << "Tampilkan kesalahan proses" << endl;
                break;
            case TXT:
                cout << "Menyimpan data menjadi file txt" << endl;
                break;
            default:
                cout << "Pilihan tidak ditemukan" << endl;
                break;
        }
		label_continue:
        cout << "Lanjutkan? If yes type y, if no type n: ";
        cin >> is_continue;
        if((is_continue == 'y') | (is_continue == 'Y')){
            pilihan = getOption();
        }else if ((is_continue == 'n') | (is_continue == 'N')){
            break;
        }else {
            goto label_continue;
            }
		}


	cout << "Selesai dan Terima Kasih" << endl;

	cin.get();
	return 0;
}


