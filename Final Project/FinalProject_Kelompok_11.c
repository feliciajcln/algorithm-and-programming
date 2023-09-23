#include <stdio.h> // header file untuk standart input output
#include <stdlib.h> // header file untuk fungsi memory allocation dan exit status (error handling)
#include <string.h> // header file untuk fungsi pengolahan string


FILE *fp1; // buffer pointer file khusus untuk membuka database password
FILE *fp2; // buffer pointer file khusus untuk membuka file save diary
FILE *fp3; // buffer pointer file khusus untuk memindahkan isi diary

/* Data type struct dengan alias struktur berisi date (string) dan word (string) */
typedef struct diary{
	char date[21];
	char word[1001];
} struktur;

/* Prototipe fungsi */
int check_pass(char *pass);
void write_diary();
void read_all();
void swap(struktur *a, struktur *b);
int partisi(struktur str[], int low, int high);
void quickSort(struktur str[], int low, int high);
int strbinSearch(struktur str[], int n, char x[]);
void read_search();
void delete_all();
void delete_one();
void change_pass();

/* MAIN PROGRAM */
int main(){
	
start : // label untuk bagian awal program
	printf("+ login\n");
	printf("- exit\n");
	
	char click;
	fflush(stdin);
	scanf("%c", &click); // scan input user berupa '+' untuk login, '-' untuk exit
	
	/* Kondisi berdasarkan input */
	switch(click){
		case 43 : // option '+'
			goto retry; // menuju label retry
		
		case 45 : // option '-'
			goto close; // menuju label close
			
		default : // jika input bukan '+' atau '-'
			printf("Input '+' or '-' only!\n");
			goto start; // kembali ke label start
	}
	
retry : // label untuk menjalankan perulangan apabila password yang diinput salah
	printf("Input your password\n");
	printf("(Default password is \"mydiary123\")\n");
	
	char password[15];
	scanf("%s", password); //scan input password user
	
	/* Variabel untuk patokan password benar atau salah */
	int hasil = 0;
	hasil = check_pass(password);
	
	/* Persyaratan password berdasarkan fungsi yang dipanggil */
	if (hasil != 0){
		printf("PASSWORD INCORRECT!\n");
		goto retry; // kembali ke label retry karena kesalahan input password (input kembali)
	} 
	else{ // persyaratan jika password benar
		goto menu; // masuk ke label menu (pusat program untuk memilih aktivitas)
	}
	
menu : // label untuk mengakses menu pada aplikasi
	printf("Welcome, user! XD\n");
	printf("1. Write Diary\n");
	printf("2. Read Diary\n");
	printf("3. Delete History\n");
	printf("4. Change Password\n");
	printf("5. Log out\n");
	printf("0. Guide\n");
	
	int option;
	scanf("%d", &option); // memilih menu
	
	/* Kondisi pemilihan menu */
	switch (option){
		case 0 : // label untuk membuka menu guide
			printf("1. Choose what you want to do in menu.\n");
			printf("2. To write, go to Write Diary menu then input your writing.\n   Press enter to go to new line.\n");
			printf("3. To save your writing, input \"#\" in the end of your message.\n");
			printf("4. You can read your records in Read Diary menu.\n");
			printf("5. You can delete your history in Delete History menu.\n");
			printf("6. To change password, go to change password menu then input your new password.\n");
			system("pause");
			goto menu; // kembali ke label menu
		
		case 1 : // label untuk membuka menu write diary
			write_diary();	// pemanggilan fungsi untuk menulis diary
			printf("Save success!\n");
			printf("\"Today will be past, and tommorow will be a new start.\"\n");
			system("pause");
			goto menu; // kembali ke label menu
			
		case 2 : // label untuk membuka menu read diary
			fflush(stdin);
			
			char choose;
			printf("a. Read all history\n");
			printf("b. Read choosen history\n");

			printf("Your choice: ");
			scanf("%c", &choose); fflush(stdin); // scan pilihan user (a atau b)
			
			if (choose == 97 || choose == 65){ // jika pilihan user a / A
				read_all(); // pemanggilan fungsi untuk membaca semua history
				system("pause");
			}
			else if (choose == 98 || choose == 66){ // jika pilihan user b / B
				read_search(); // pemanggilan fungsi untuk membaca history yang dipilih
				printf("\n");
				system("pause");
			}
			else{ // jika input buka a / b
				printf("input only a or b!\n");
			}
			goto menu; // kembali ke label menu
			
		case 3 : // label untuk membuka menu delete history
			fflush(stdin);
			char chose;
			printf("a. Delete all history\n");
			printf("b. Delete choosen history\n");

			printf("Your choice: ");
			scanf("%c", &choose); fflush(stdin); // scan pilihan user (a atau b)
			
			if (chose == 97 || chose == 65){ // jika pilihan user a / A
				delete_all(); // pemanggilan fungsi untuk menghapus semua history
				printf("Delete success.\n");
				system("pause");
			}
			else if (chose == 98 || chose == 66){ // jika pilihan user b / B
				delete_one(); // pemanggilan fungsi untuk menghapus history yang dipilih
				printf("Delete success.\n");
				system("pause");
			}
			else{ // jika input buka a / b
				printf("input only a or b!\n");
			}
			goto menu; // kembali ke label menu
			
		case 4 : // label untuk membuka menu change password
			change_pass(); // pemanggilan fungsi untuk mengganti password
			printf("You have changed your password\n");
			system("pause");
			goto menu; // kembali ke label menu
			
		case 5 : // label untuk memuka menu log out
			printf("You have logged out!\n");
			system("pause");
			goto start; // kembali ke label start (awal program)
			
		default : // label bila input tidak sesuai
			printf("Input number only in the menu!\n");
			goto menu; // kembali ke label menu
	}
	
close : // label untuk menutup program
	printf("Thank You! Come back anytime XD\n");
	
	return 0;
}

/* Fungsi untuk mengecek password */
int check_pass(char *pass){
	fp1 = fopen("password_base.txt", "r"); // membuat file diary_history.txt dengan mode read untuk membaca password
	
	if (fp1 == NULL){				//error handling kondisi jika file tidak ditemukan
		printf("file not found\n");
		exit(1);					//error handling berupa exit status
	}
	
	char base_pass[15];
	fscanf(fp1, "%s", base_pass); // membaca string yaitu password dalam file
	
	/* Persyaratan jika password salah (menggunakan strcmp untuk membandingkan password, return '0' jika sama, dan return '1' jika tidak sama */
	if (strcmp(pass, base_pass) != 0){
		fclose(fp1); // menutup buffer pointer file
		return 1; // return nilai 1 jika password salah
	}
	else{
		fclose(fp1); // menutup buffer pointer file
		return 0; // return nilai 0 jika password benar
	}
}
/* Fungsi untuk menulis diary */
void write_diary(void){
	struktur record; // variabel bertipe data struktur 
	
	//membuka file diary_history.txt dengan mode append untuk menambahkan tulisan
	fp2 = fopen("diary_history.txt", "a"); 
	
	if (fp2 == NULL){				//error handling kondisi jika file tidak ditemukan
		printf("file not found\n");
		exit(1);					//error handling berupa exit status
	}	
	fflush(stdin);
	printf("Date: ");
	scanf("%^[\n]", &record.date); fflush(stdin); // scan tulisan yang diinput user
	fprintf(fp2, "%s", record.date); // menuliskan tanggal ke dalam file
	fprintf(fp2, "\n"); // print enter di dalam file supaya input berikutnya di baris baru
	
	printf("Record:\n");
	scanf("%[^#]", &record.word); fflush(stdin); // scan tulisan yang diinput user
	fprintf(fp2, "%s", record.word); // menuliskan catatan user ke dalam file
	fprintf(fp2, "#"); // print "#" di ujung catatan sebagai penanda agar dapat dibaca di menu read
	fprintf(fp2, "\n"); // print enter di dalam file supaya input berikutnya di baris baru
	
	fclose(fp2); //menutup buffer pointer file	
}

/* Fungsi untuk membaca keseluruhan isi file */
void read_all(void){
	struktur *buff; // buffer pointer sebagai tempat menampung string dari file. Array bersifat dinamis
	long numbytes; // variabel untuk menyimpan jumlah alokasi memori yang diperlukan
	
	// membuka file diary_history.txt dengan mode read untuk membaca
	fp2 = fopen("diary_history.txt", "r");
	
	if (fp2 == NULL){				// error handling kondisi jika file tidak ditemukan
		printf("file not found\n");
		exit(1);					// error handling berupa exit status
	}
	
	// mendapatkan jumlah memori yang harus dialokasikan
	fseek(fp2, 0L, SEEK_END); 
	numbytes = ftell(fp2);
	
	fseek(fp2, 0L, SEEK_SET); // mereset indikator posisi pointer ke awal file
	
	// mengalokasikan memori untuk buffer pointer menyimpang string
	buff = (struktur*)calloc(numbytes, sizeof(struktur)); // ti
	
	if (buff == NULL){				// error handling kondisi jika file tidak ditemukan
		printf("file not found\n");
		exit(1);					// error handling berupa exit status
	}
	
	int i = 0; // variabel indeks awal array dinamis
	/* Melakukan scan tiap komponen dalam file dengan loop */
	while (!feof(fp2)){
		fscanf(fp2, "%[^\n]\n", &buff[i].date); fflush(stdin); // scan pada tanggal
		fscanf(fp2, "%[^#]#", &buff[i].word); fflush(stdin); // scan pada tulisan
		fscanf(fp2, "\n"); // scan pada enter
		i++; // increment indeks
	}
	
	int j; // variabel indeks sebagai patokan array untuk di output
	/* Print setiap komponen yang sudah discan dan disimpan dalam array dinamis */
	for (j = 0; j < i; j++){
		printf("%S\n%s\n\n", buff[j].date, buff[j].word); // format output pada console
	}
	
	fclose(fp2); // menutup buffer pointer file
	free(buff); // melepaskan memori yang dialokasikan untuk buffer pointer
}

/* Fungsi untuk melakukan swap antara dua data */
void swap(struktur *a, struktur *b){ // menggunakan void pointer karena tipe datanya struktur
	// menyimpan data ke variabel temporary sebagai bantuan
	struktur tmp = *a;
	*a = *b;
	*b = tmp;
}

/* Fungsi partisi untuk mencari indeks titik geser */
int partisi(struktur str[], int lowm int high){
	int i = (low - 1); // inisialisasi titik geser berada di -1 (indeks awal 0 dikurang 1)
	
	int j;
	/* Loop untuk mencari indeks titik geser (i) */
	for (j = low; j <= high - 1; j++){
		if (strcmp(str[j].date, str[high].date) < 0){ // membandingkan string berdasarkan tanggal
			// str[high].date adalah pivot (pembanding), menggunakan data di indeks terakhir
			// prinsipnya adalah menempatkan data yang lebih kecil dari pivot ke bawah (anggap kiri)
			// sedangkan sisanya ke atas (anggap kanan)
			// jika string dengan indeks saat iterasi lebih kecil dari indeks pivot
			i++; // indeks titik geser akan bertambah 1
			swap(&str[i], &str[j]); // menukar data di indeks geser dengan data di indeks iterasi				
		}
	}
	swap(&str[i + 1], &str[high]); // menukar data pivot dengan data di indeks titik geser +1
	return (i + 1); // mengembalikan nilai berupa indeks titik gesernya
}

/* Fungsi untuk mengeksekusi pengurutan data berdasarkan */
void quickSort(struktur str[], int low, int high){
	if (low < high){ // fungsi akan rekursif selama indeks terkecil tidak sama dengan indeks terbesar
		int point = partisi(str, low, high); // mengambil nilai yang dikembalikan fungsi partisi
		
		quickSort(str, low, point - 1); // rekursif sort dengan indeks terbesarnya adalah partisi - 1
		quickSort(str, point + 1, high); // rekursif sort dengan indeks terkecilnya adalah partisi + 1
	}
}

/* Fungsi Binary Search untuk melakukan pencarian pada record diary yang tersimpan */
int strbinSearch(struktur str[], int n, char x[]){
	int min = 0; // indeks awal pencarian mulai dari 0
	int max = n - 1; // indeks akhir pencarian berada di n (berdasarkan indeks) dikurangi 1 karena mulai dari 0
	
	while (min <= max){
		int mid = (min + max) / 2; // titik tengah pencarian
		int res = -1000; // sebagai antisipasi error
		
		/* Kondisi jika hasil pencarian belum ditemukan (data berada di bawah) */
		if (strcmp(x, str[mid].date) == 0){
			return mid; // return titik tengah
		}
		
		/* Kondisi jika hasil pencarian belum ditemukan (data berada di atas) */
		if (strcmp(x, str[mid].date) > 0){
			min = mid - 1; // titik awal berpindah ke titik tengah + 1
		}
		
		/* Kondisi jika hasil pencarian belum ditemukan (data berada di bawah) */
		if (strcmp(x, str[mid].date) < 0){
			max = mid - 1; // titik akhir berpindah ke titik tengah - 1
		}
	}
	return -1; // return 1 jika tidak ditemukan
}

/* Fungsi untuk membaca history berdasarkan tanggal yang diinput user */
void read_search(void){
	struktur *saved; // buffer pointer sebagai tempat menampung string dari file. Array bersifat dinamis
	long size; // variabel untuk menyimpan jumlah alokasi memori yang diperlukan
	
	// membuka file diary_history.txt dengan mode read
	fp2 = fopen("diary_history.txt", "r");
	
	if (fp2 == NULL){				// error handling kondisi jika file tidak ditemukan
		printf("file not found\n");
		exit(1);					// error handling berupa exit status
	}
	
	// mendapatkan jumlah memori yang harus dialokasikan
	fseek(fp2, 0L, SEEK_END); 
	numbytes = ftell(fp2);
	
	fseek(fp2, 0L, SEEK_SET); // mereset indikator posisi pointer ke awal file
	
	// mengalokasikan memori untuk buffer pointer menyimpang string
	saved = (struktur*)calloc(size, sizeof(struktur)); // tipe datanya adalah struktur (akumulasi ukuran dari
	
	if (saved == NULL){				// error handling kondisi jika file tidak ditemukan
		printf("file not found\n");
		exit(1);					// error handling berupa exit status
	}
	
	int idx = 0; // variabel indeks awal array dinamis
	/* Melakukan scan tiap komponen dalam file dengan loop */
	while (!feof(fp2)){
		fscanf(fp2, "%[^\n]\n", &saved[i].date); fflush(stdin); // scan pada tanggal
		fscanf(fp2, "%[^#]#", &saved[i].word); fflush(stdin); // scan pada tulisan
		fscanf(fp2, "\n"); // scan pada enter
		idx++; // increment indeks
	}
	quickSort(saved, 0, idx - 1);
	char find[21];
	printf("Input date: ");
	scanf("%[^\n]", &find); getchar(); // scan tanggal yang diinput user untuk dicari
	
	/* Variabel untuk patokan pencarian apakah ketemu atau tidak */
	int hasil = -1;
	hasil = strbinSearch(saved, idx, find);
	
	if (hasil == -1){ // kondisi jika pencarian tidak ditemukan
		printf("record not found\n");
	}
	else{ // kondisi jika pencarian ditemukan
		printf("%s\n%s\n", saved[hasil].date, saved[hasil].word); // print hasil pencarian ke console
	}
	
	fclose(fp2); // menutup buffer pointer file
	free(saved); // melepaskan memori yang dialokasikan untuk buffer pointer
}

/* Function untuk menghapus history diary secara total */
void delete_all(void){
	// membuka file diary_history.txt dengan mode write untuk menimpa tulisan 
	fp3 = fopen("diary_history.txt", "w");
	
	if (fp3 == NULL){				// error handling kondisi jika file tidak ditemukan
		printf("file not found\n");
		exit(1);					// error handling berupa exit status
	}
	fprintf(fp3, ""); // printf kosong untuk menghapus total
	fclose(fp3); // menutup buffer pointer file
}

/* Function untuk menghapus history diary yang dipilih user */
void delete_one(void){
	char filename[21] = "diary_history.txt";
	
	// membuka file diary_history.txt dengan mode read untuk membaca isi file
	fp2 = fopen(filename, "r");
	
	if (fp2 == NULL){				// error handling kondisi jika file tidak ditemukan
		printf("file not found\n");
		exit(1);					// error handling berupa exit status
	}
	
	char tempfile[21] = "temp.txt";
	fp3 = fopen(tempfile, "w"); // membuat file temp.txt untuk menyimpan isi file sementara
	
	if (fp3 == NULL){				// error handling kondisi jika file tidak ditemukan
		printf("file not found\n");
		exit(1);					// error handling berupa exit status
	}
	
	char del[21];
	printf("Input date: ");
	scanf("%[^\n]", del); getchar(); // scan tanggal yang diinput user untuk dicari
	
	struktur save;
	/* Melakukan scan tiap komponen dalam file dengan loop */
	while (!feof(fp2)){
		fscanf(fp2, "%[^\n]\n", &save.date); fflush(stdin); 
		fscanf(fp2, "%[^#]#", &save.word); fflush(stdin); 
		fscanf(fp2, "\n"); 
		
		if (strcmp(del, save.date) == 0){
			continue;
		}
		
		/* Memindahkan isi file ke file temporary kecuali tanggal yang diinput user */
		fprintf(fp3, "%s\n", save.date);
		fprintf(fp3, "%s", save.word);
		fprintf(fp3, "#");
		fprintf(fp3, "\n");
	}
	
	fclose(fp2); // menutup buffer pointer file	
	fclose(fp3); // menutup buffer pointer file

	remove(filename); // menghapus file awal
	rename(tempfile, filename); // merubah nama file temporary menjadi nama file awal
}

/* Function untuk mengganti password */
void change_pass(void){
	// membuka file diary_history.txt dengan mode write untuk menimpa tulisan
	fp1 = fopen("password_base.txt", "w"); 
	
	if (fp1 == NULL){				// error handling kondisi jika file tidak ditemukan
		printf("file not found\n");
		exit(1);					// error handling berupa exit status
	}
	printf("Input new password\n");
	
	char new_pass[15];
	scanf("%s", new_pass);			// input password baru
	fprintf(fp1, "%s", new_pass);	// save password baru ke dalam file
	
	fclose(fp1); // menutup buffer pointer file
}
