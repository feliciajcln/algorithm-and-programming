#include <stdio.h> // header file untuk standart input output
#include <stdlib.h> // header file untuk exit status (error handling)
#include <string.h> // header file untuk fungsi pengelolahan string

FILE *fp; // buffer pointer file untuk membuka data transaksi

/*data type struct dengan alias catatan berisi tanggal, jenis, ket, dan nominal*/
typedef struct data{
	char tanggal[25];
	char jenis[10];
	char ket[1000];
	long int nominal;
} catatan;

catatan transaksi[100];
int jml = 0, i, j;

/*prototipe fungsi*/
void input (); 
void swap (catatan *a, catatan *b);
void show ();
void search ();

/*main program*/
int main (){
	
start :
	printf("Silahkan pilih salah satu menu di bawah ini\n");
	printf("1. Input transaksi\n");
	printf("2. Menampilkan semua data transaksi\n");
	printf("3. Mencari transaksi tertentu berdasarkan tanggal\n");
	printf("4. Keluar dari program\n");
	
	int angka;
	scanf("%d", &angka); getchar();
	
	switch (angka){
		case 1 :
			input();
			printf("Data transaksi telah berhasil tersimpan!\n");
			system("pause");
			goto start;
		case 2 :
			show();
			system("pause");
			goto start;
		case 3 :
			search();
			system("pause");
			goto start;
		case 4 :
			system("pause");
			goto exit;
		default :
			printf("Masukan angka 1/2/3/4");
			goto start;
	}

exit :
	return(0);
}

/*fungsi untuk memasukan data transaksi*/
void input(){
	fp = fopen("data_transaksi.txt", "a"); // membuka file data_transaksi.txt dengan mode append untuk menambahkan data
	
	if (fp == NULL){				 //error handling kondisi jika file tidak ditemukan
		printf("File not found\n");
		exit(1);					 //error handling berupa exit status
	}
	printf("Tanggal transaksi : ");
	scanf("%[^\n]", transaksi[jml].tanggal); getchar(); // scan tulisan yang diinput oleh user
	fprintf(fp, "%s\n", transaksi[jml].tanggal); // memasukan tulisan ke dalam file
	
	printf("Jenis transaksinya (Debit/Kredit) : ");
	scanf("%[^\n]", transaksi[jml].jenis); getchar(); // scan tulisan yang diinput oleh user
	fprintf(fp, "%s\n", transaksi[jml].jenis); // memasukan tulisan ke dalam file
	
	printf("Nama transaksi (keterangan) : ");
	scanf("%[^\n]", transaksi[jml].ket); getchar(); // scan tulisan yang diinput oleh user
	fprintf(fp, "%s\n", transaksi[jml].ket); // memasukan tulisan ke dalam file
	
	printf("Nilai transaksi: ");
	scanf("%ld", &transaksi[jml].nominal); getchar(); // scan tulisan yang diinput oleh user
	fprintf(fp, "%d\n", transaksi[jml].nominal); // memasukan tulisan ke dalam file
		
	fclose(fp); // menutup buffer pointer file
}

/*fungsi untuk menukar dua data*/
void swap (catatan *a, catatan *b){
	catatan temp = *a;
	*a = *b;
	*b = temp;
}

/*fungsi untuk menampilkan semua data transaksi*/
void show (){
	fp = fopen("data_transaksi.txt", "r"); // membuka file data_transaksi.txt dengan mode read untuk membaca isi file
	
	if (fp == NULL){				 //error handling kondisi jika file tidak ditemukan
		printf("File not found\n");
		exit(1);					 //error handling berupa exit status
	}
	
	for (i=0; !feof(fp); i++){
		fscanf(fp, "%[^\n]\n", transaksi[i].tanggal); // scan tanggal transaksi
		fscanf(fp, "%[^\n]\n", transaksi[i].jenis); // scan jenis transaksi
		fscanf(fp, "%[^\n]\n", transaksi[i].ket); // scan nama transaksi (keterangan)
		fscanf(fp, "%ld\n", &transaksi[i].nominal); // scan nilai transaksi (nominal)
		jml++;
	}
	
	/* sorting data*/
	for (i=0; i<jml-1; i++){
		for (j=0; j<jml-i-1; j++){
			if (strcmp(transaksi[j].tanggal, transaksi[j+1].tanggal) > 0){
				swap(&transaksi[j], &transaksi[j+1]); // menukar dua data menggunakan fungsi swap
			}
		}
	}
	
	/*menghitung selisih total transaksi*/
	long int total_kredit = 0, total_debit = 0;
	for (i=0; i<jml; i++){
		if (strcmp(transaksi[i].jenis, "Kredit") == 0){
			total_kredit += transaksi[i].nominal;
		}
		else if (strcmp(transaksi[i].jenis, "Debit") == 0){
			total_debit += transaksi[i].nominal;
		}
	}
	
	/*menampilkan semua data transaksi*/
	printf("No.	Tanggal Transaksi	Jenis Transaksi			Nama Transaksi			Nilai Transaksi\n");
	for (i=0; i<jml; i++){
		printf("%d\t%s\t%s\t\t\t\t%s\t\t\t%ld\t\n", i+1, transaksi[i].tanggal, transaksi[i].jenis, transaksi[i].ket, transaksi[i].nominal);
	}
	printf("Selisih total transaksi : %ld\n", total_debit - total_kredit);
	
	fclose(fp); // menutup buffer pointer file
}

/*fungsi untuk mencari data transaksi tertentu berdasarkan tanggal*/
void search (){
	fp = fopen("data_transaksi.txt", "r"); // membuka file data_transaksi.txt dengan mode read untuk membaca isi file
	
	if (fp == NULL){				 //error handling kondisi jika file tidak ditemukan
		printf("File not found\n");
		exit(1);					 //error handling berupa exit status
	}

	for (i=0; !feof(fp); i++){
		fscanf(fp, "%[^\n]\n", transaksi[i].tanggal); // scan tanggal transaksi
		fscanf(fp, "%[^\n]\n", transaksi[i].jenis); // scan jenis transaksi
		fscanf(fp, "%[^\n]\n", transaksi[i].ket); // scan nama transaksi (keterangan)
		fscanf(fp, "%ld\n", &transaksi[i].nominal); // scan nilai transaksi (nominal)
		jml++;
	}
	
	char search[25];
	printf("Masukan tanggal yang ingin dicari : ");
	scanf("%[^\n]", search); getchar();
	
	/*proses searching*/
	int index = 0, total = 0;
	for (i=0; i<jml; i++){
		if (strcmp(transaksi[i].tanggal, search) == 0){
			total++;
		}
		else{
			index++;
		}
	}
	
	/*proses menampilkan data*/
	if (index == jml){
		printf("Data transaksi tidak ditemukan\n");
	}
	else if (total > 0){
		printf("No.	Tanggal Transaksi	Jenis Transaksi			Nama Transaksi			Nilai Transaksi	\n");
		if (total > 1){
			for (i=0; i<total; i++){
				printf("%d\t%s\t%s\t\t\t\t%s\t\t\t%ld\t\n", i+1, transaksi[i].tanggal, transaksi[i].jenis, transaksi[i].ket, transaksi[i].nominal);
			}	
		}
		else{
			printf("%d\t%s\t%s\t\t\t\t%s\t\t\t%ld\t\n", 1, transaksi[total].tanggal, transaksi[total].jenis, transaksi[total].ket, transaksi[total].nominal);
		}
	}
	
	fclose(fp); // menutup buffer pointer file
}
