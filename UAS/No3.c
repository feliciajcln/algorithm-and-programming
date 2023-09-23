#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;

struct diary{
	char date[25];
	char log[300];
};

struct diary harian[100], temp;
int jml = 0, i, j;

int main (){
start :
	printf("Silahkan pilih salah satu menu di bawah ini\n");
	printf("1. Menulis log harian\n");
	printf("2. Membaca semua log harian\n");
	printf("3. Mencari log harian tertentu berdasarkan tanggal\n");
	printf("4. Keluar dari program\n");
	
	int angka;
	scanf("%d", &angka); getchar();
	
	switch (angka){
		case 1 :
			write();
			system("pause");
			goto start;
		case 2 :
			read();
			system("pause");
			goto start;
		case 3 :
			search();
			system("pause");
			goto start;
		case 4 :
			system("pause");
			goto exit;	
	}
exit :
	return(0);
}

void write (){
	fp = fopen("log_harian.txt", "a");
	
	printf("Tanggal : ");
	scanf("%[^\n]", harian[jml].date); getchar();
	fprintf(fp, "%s\n", harian[jml].date);
	
	printf("Record : ");
	scanf("%[^#]", harian[jml].log); getchar();
	fprintf(fp, "%s", harian[jml].log);
	fprintf(fp, "#\n");
	
	jml++;
	
	fclose(fp);
}

void read (){
	fp = fopen("log_harian.txt", "r");
	
	while (!feof(fp)){
		fscanf(fp, "%[^\n]\n", harian[jml].date);
		fscanf(fp, "%[^#]#", harian[jml].log);
		printf("Tanggal : %s\n", harian[i].date);
		printf("Record :\n%s", harian[i].log);
		printf("\n");
	}
	fclose(fp);
}

void binary (char str[], int min, int max, char find[]){
	int mid = (min + max) / 2;
	if (strcmp(str[mid], find) > 0){
		max = mid - 1;
	}
	else if (strcmp(str[mid], find) < 0){
		min = mid + 1;
	}
	else{
		return mid;
	}
	return -1;
}

void search (){
	fp = fopen("log_harian.txt", "r");
	
	for (i=0; !feof(fp); i++){
		fscanf(fp, "%[^\n]\n", harian[i].date);
		fscanf(fp, "%[^#]#", harian[i].log);
		jml++;
	}
	for (i=0; i<jml-1; i++){
		for (j=0; j<jml-i-1; j++){
			if (strcmp(harian[j].date, harian[j+1].date) > 0){
				char temp1[25];
				strcpy(temp1, harian[j].date);
				strcpy(harian[j].date, harian[j+1].date);
				strcpy(harian[j+1].date, temp1);
				char temp2[300];
				strcpy(temp2, harian[j].log);
				strcpy(harian[j].log, harian[j+1].log);
				strcpy(harian[j+1].log, temp2);
			}
		}
	}
	char search[25];
	printf("Tanggal yang ingin dicari : ");
	scanf("%[^\n]", search); getchar();
	
	int min = 0, max = jml, index = -1;
	int mid = (min + max) / 2;
	while (min <= max){
		if (strcmp(harian[mid].date, search) > 0){
			max = mid - 1;
			continue;
		}
		else if (strcmp(harian[mid].date, search) < 0){
			min = mid + 1;
			continue;
		}
		else{
			index = mid;
			break;
		}
		index = -1;
	}
	if (index != -1){
		printf("Tanggal : %s", harian[index].date);
		printf("Record :\n%s\n", harian[index].log);
	}
	else{
		printf("Log harian tidak ditemukan\n");
	}
	
	for (i=0; i<jml; i++){
		printf("%s\n%s", harian[i].date, harian[i].log);
	}
/*	char search[25];
	printf("Tanggal yang ingin dicari : ");
	scanf("%[^\n]", search); getchar();
	int index = -1;
	index = binary(harian, 0, jml, search);
	if (index != -1){
		printf("Tanggal : %s", harian[index].date);
		printf("Record :\n%s\n", harian[index].log);
	}
	else{
		printf("Log harian tidak ditemukan\n");
	}*/
	fclose(fp);
}
