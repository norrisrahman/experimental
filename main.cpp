#include <iostream>
#include <string>
#include <array>
#include <fstream>

using namespace std;

struct Penumpang{
	string tanggal;
	string identitas;
	string nama;
	string jenis_kelamin;
	string maskapai;
	string tujuan_keberangkatan;
		
};


void tulisData() {
	fstream myFile;
	string tanggal, bulan, tahun, tgl;

	Penumpang pesawat;

	system("cls");
	cout << "\nMasukkan tanggal keberangkatan" << endl;
	cout << "===================================\n" << endl;
	cout << "Masukkan Tanggal \t\t: ";
	cin >> tanggal;
	cout << "Masukkan Bulan \t\t\t: ";
	cin >> bulan;
	cout << "Masukkan Tahun \t\t\t: ";
	cin >> tahun;

	pesawat.tanggal = tanggal + "/" + bulan + "/" + tahun;

	pesawat.identitas = tahun + bulan + tanggal;

	cout << "Masukkan jenis kelamin \t\t: ";
	cin >> pesawat.jenis_kelamin;
	cout << "Masukka nama maskapai\t: ";
	cin >> pesawat.maskapai;
	cout << "Masukkan Tujuan Keberangkatan: ";
	cin >> pesawat.tujuan_keberangkatan;
	cout << "Masukkan nama penumpang: ";
	cin >> pesawat.nama;
	
	myFile.open("data.txt", ios::app);

	myFile << pesawat.tanggal << endl;
	myFile << pesawat.identitas << endl;
	myFile << pesawat.jenis_kelamin << endl;
	myFile << pesawat.maskapai << endl;
	myFile << pesawat.tujuan_keberangkatan << endl;
	myFile << pesawat.nama << endl << endl;

	myFile.close();
}

int hitungData() {
	fstream myFile;
	int ukuran = 0;

	Penumpang pesawat;

	myFile.open("data.txt");

	myFile >> pesawat.tanggal;
		myFile >> pesawat.identitas;
		myFile >> pesawat.jenis_kelamin;
		myFile >> pesawat.maskapai;
		myFile >> pesawat.tujuan_keberangkatan;
		myFile >> pesawat.nama;
	while (!myFile.eof()) {
		ukuran++;
		myFile >> pesawat.tanggal;
		myFile >> pesawat.identitas;
		myFile >> pesawat.jenis_kelamin;
		myFile >> pesawat.maskapai;
		myFile >> pesawat.tujuan_keberangkatan;
		myFile >> pesawat.nama;
	}

	myFile.close();

	return ukuran;

}

void bacaData () {
    fstream myFile;
    int size = hitungData();

    Penumpang*  pesawat = new Penumpang[size];

    myFile.open("data.txt");

    for (int i=0; i < size; i++) {
        myFile >> pesawat[i].tanggal;
		myFile >> pesawat[i].identitas;
		myFile >> pesawat[i].jenis_kelamin;
		myFile >> pesawat[i].maskapai;
		myFile >> pesawat[i].tujuan_keberangkatan;
		myFile >> pesawat[i].nama;
    }
    
    myFile.close();

    for (int i=0; i < size; i++) {
        cout << pesawat[i].tanggal << "\t\t" << pesawat[i].identitas << "\t\t" << pesawat[i].jenis_kelamin << "\t\t" << pesawat[i].maskapai << "\t\t" << pesawat[i].tujuan_keberangkatan << "\t\t" << pesawat[i].nama << "\t\t" << endl;
    }
}

void simpanData (struct Penumpang pesawat[], int size) {

    fstream myFile;
    myFile.open("data.txt", ios::trunc | ios::out);

    for (int i=0; i < size; i++){

        myFile << pesawat[i].tanggal << endl;
        myFile << pesawat[i].identitas << endl;
        myFile << pesawat[i].jenis_kelamin << endl;
        myFile << pesawat[i].maskapai << endl;
        myFile << pesawat[i].tujuan_keberangkatan << endl;
        myFile << pesawat[i].nama << endl << endl;
    }
    myFile.close();
}

void urutData() {
    fstream myFile;
    int i, j;
    int size = hitungData();

    Penumpang* pesawat = new Penumpang[size];

    myFile.open("data.txt");

    for(int i = 0; i<size; i++){
        myFile >> pesawat[i].tanggal;
		myFile >> pesawat[i].identitas;
		myFile >> pesawat[i].jenis_kelamin;
		myFile >> pesawat[i].maskapai;
		myFile >> pesawat[i].tujuan_keberangkatan;
		myFile >> pesawat[i].nama;
    }

    myFile.close();

    struct Penumpang key;
    for (i = 1; i < size; i++) {
        key = pesawat[i];
        j = i - 1;        
        while (j >= 0 && pesawat[j].identitas < key.identitas) {
            pesawat[j + 1] = pesawat[j];
            j = j - 1;
        }
            pesawat[j + 1] = key;
    }

    simpanData(pesawat, size);

    
    system("cls");
	cout << "Menampilkan Seluruh data" << endl;
	cout << "Tanggal \t\t" << "Jenis Kelamin\t\t" << "Maskapai\t\t" << "Tujuan\t\t\t" << "Nama" << endl;
	cout << "==============================================================================================" << endl;
	for (int i = 0; i < size; i++) {
		cout << pesawat[i].tanggal
			<< "\t\t" << pesawat[i].jenis_kelamin
			<< "\t\t\t" << pesawat[i].maskapai
			<< "\t\t\t" << pesawat[i].tujuan_keberangkatan
			<< "\t\t\t" << pesawat[i].nama << endl;
	}

	cout << endl;

    cout << endl;
}

void cariData () {
    fstream myFile;
    string kataKunci;
    int size = hitungData();

    Penumpang* pesawat = new Penumpang[size];

    myFile.open("data.txt");

    for(int i = 0; i<size; i++){
        myFile >> pesawat[i].tanggal;
		myFile >> pesawat[i].identitas;
		myFile >> pesawat[i].jenis_kelamin;
		myFile >> pesawat[i].maskapai;
		myFile >> pesawat[i].tujuan_keberangkatan;
		myFile >> pesawat[i].nama;
    }

    myFile.close();

    cout<<"Nama Penumpang : ";
    cin >> kataKunci;

    cout << "Menampilkan Hasil Pencarian : " << endl;
	cout << "Tanggal \t\t" << "Jenis Kelamin\t\t" << "Maskapai\t\t" << "Tujuan\t\t\t" << "Nama" << endl;
	cout << "==============================================================================================" << endl;
    for(int i=0;i<size;i++) {
        if(pesawat[i].nama==kataKunci) {
            cout << pesawat[i].tanggal
			<< "\t\t" << pesawat[i].jenis_kelamin
			<< "\t\t\t" << pesawat[i].maskapai
			<< "\t\t\t" << pesawat[i].tujuan_keberangkatan
			<< "\t\t\t" << pesawat[i].nama << endl;
            return;
        }
    }
    system ("cls");
    cout << "\n\nPencarian Tidak Ditemukan\n\n"<< endl;
}

void pesanError() {
    system ("cls");
    cout << "\n\nPencarian Tidak Ditemukan\n\n"<< endl;
}

void updateData() {
    string tanggal,bulan,tahun, tgl;
    fstream myFile;
    string kataKunci;
    int size = hitungData();

    Penumpang* pesawat = new Penumpang[size];

    myFile.open("data.txt");

    for(int i = 0; i<size; i++){
        myFile >> pesawat[i].tanggal;
		myFile >> pesawat[i].identitas;
		myFile >> pesawat[i].jenis_kelamin;
		myFile >> pesawat[i].maskapai;
		myFile >> pesawat[i].tujuan_keberangkatan;
		myFile >> pesawat[i].nama;
    }

    myFile.close();

    cout<<"Nama Penumpang : ";
    cin >> kataKunci;

    system ("cls");

    for(int i=0;i<size;i++) {
        if(pesawat[i].nama==kataKunci) {
            cout << "Menampilkan Data Yang Ingin Di Update" << endl;
	        cout << "Tanggal \t\t" << "Jenis Kelamin\t\t" << "Maskapai\t\t" << "Tujuan\t\t\t" << "Nama" << endl;
	        cout << "==============================================================================================" << endl;
            cout << pesawat[i].tanggal
                    << "\t\t" << pesawat[i].jenis_kelamin
                    << "\t\t\t" << pesawat[i].maskapai
                    << "\t\t\t" << pesawat[i].tujuan_keberangkatan
                    << "\t\t\t" << pesawat[i].nama << endl;

            cout << "\nMasukkan tanggal keberangkatan" << endl;
            cout << "===================================\n" << endl;
            cout << "Masukkan Tanggal \t\t: ";
            cin >> tanggal;
            cout << "Masukkan Bulan \t\t\t: ";
            cin >> bulan;
            cout << "Masukkan Tahun \t\t\t: ";
            cin >> tahun;

            pesawat[i].tanggal = tanggal + "/" + bulan + "/" + tahun;

            pesawat[i].identitas = tahun + bulan + tanggal;

            cout << "Masukkan jenis kelamin \t\t: ";
            cin >> pesawat[i].jenis_kelamin;
            cout << "Masukka nama maskapai\t: ";
            cin >> pesawat[i].maskapai;
            cout << "Masukkan Tujuan Keberangkatan: ";
            cin >> pesawat[i].tujuan_keberangkatan;
            cout << "Masukkan nama penumpang: ";
            cin >> pesawat[i].nama;

            simpanData(pesawat, size);

            cout << endl;
            return;
        }
    }
    pesanError();
}

void hapusData () {
    fstream myFile;
    string kataKunci;
    int size = hitungData();

    Penumpang* pesawat = new Penumpang[size];

    myFile.open("data.txt");

    for(int i = 0; i<size; i++){
        myFile >> pesawat[i].tanggal;
		myFile >> pesawat[i].identitas;
		myFile >> pesawat[i].jenis_kelamin;
		myFile >> pesawat[i].maskapai;
		myFile >> pesawat[i].tujuan_keberangkatan;
		myFile >> pesawat[i].nama;
    }

    myFile.close();

    cout<<"Nama Penumpang : ";
    cin >> kataKunci;

    for(int i=0;i<size;i++) {
        if(pesawat[i].nama==kataKunci) {
            for(int j=i; j<size -1; j++) {
                pesawat[j].nama = pesawat[j+1].tanggal;
                pesawat[j].identitas = pesawat[j+1].identitas;
                pesawat[j].jenis_kelamin = pesawat[j+1].jenis_kelamin;
                pesawat[j].maskapai = pesawat[j+1].maskapai;
                pesawat[j].tujuan_keberangkatan = pesawat[j+1].tujuan_keberangkatan;
                pesawat[j].nama = pesawat[j+1].nama;
                
            }
            size--;

            simpanData(pesawat, size);
            return;
        }
    }
    pesanError(); 
}

int main() {
	int pilihan;


	cout << "\n============================================" << endl;
	cout << "===DATABASE PENUMPANG PESAWAT SELAMA PANDEMI===" << endl;
	cout << "==============================================" << endl << endl;

	pilihan :
	cout << "1. Menambah data penumpang" << endl;
	cout << "2. Tampilkan data penumpang" << endl;
	cout << "3. Mengurutkan data penumpang" << endl;
	cout << "4. Mencari data penumpang" << endl;
	cout << "5. Update data penumpang" << endl;
	cout << "6. Hapus data penumpang" << endl;
	cout << "7. Program selesai" << endl;

	cout << "Masukkan pilihan menu : ";
	cin >> pilihan;

	switch (pilihan)
	{
	case 1 :
		tulisData();
		goto pilihan;
		break;
	case 2:
		bacaData();
		goto pilihan;
		break;
    case 3:
		urutData();
		goto pilihan;
		break;
    case 4:
		cariData();
		goto pilihan;
		break;
    case 5:
		updateData();
		goto pilihan;
		break;
    case 6:
		hapusData();
		goto pilihan;
		break;
	default:
		break;
	}
}