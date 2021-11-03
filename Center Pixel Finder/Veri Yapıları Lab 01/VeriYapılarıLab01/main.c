

//  152120181011 Serdar Demirtaþ
//  152120181033 Osman Çaðlar


#include<stdlib.h>
#include<stdio.h>

#define SIZE 100

int globalpixelarray[SIZE][SIZE] = { 0 };

int blobnumber = 0;
int numbersofpixels = 0;
int sumofrowvalues = 0;
int sumofcolumnvalues = 0;


// CPF (Center Pixel Finder) fonksiyonu
void CPF(int rowIndex, int columnIndex, int firstRowIndex, int firstColumnIndex,int rowNumberCPF,int colnumberCPF) {

	if (globalpixelarray[rowIndex][columnIndex] == 1) {
		globalpixelarray[rowIndex][columnIndex] = -1;

		if (rowIndex != 0) {
			CPF(rowIndex-1, columnIndex, firstRowIndex, firstColumnIndex, rowNumberCPF, colnumberCPF);
		}
		if (columnIndex + 1 != colnumberCPF) {
			 CPF(rowIndex, columnIndex + 1, firstRowIndex, firstColumnIndex, rowNumberCPF, colnumberCPF);
		}
		if (columnIndex != 0) {
			 CPF(rowIndex, columnIndex - 1, firstRowIndex, firstColumnIndex, rowNumberCPF, colnumberCPF);
		}
		if (rowIndex + 1 != rowNumberCPF) {
			 CPF(rowIndex + 1, columnIndex, firstRowIndex, firstColumnIndex, rowNumberCPF, colnumberCPF);
		}

	}

	if (rowIndex == firstRowIndex && columnIndex == firstColumnIndex) {
		for (int i = 0; i < rowNumberCPF; i++) {
			for (int j = 0; j < colnumberCPF; j++) {

				if (globalpixelarray[i][j] == -1) {
					numbersofpixels++;
					sumofcolumnvalues = sumofcolumnvalues + j;
					sumofrowvalues = sumofrowvalues + i;
				}


			}
		}

		for (int i = 0; i < rowNumberCPF; i++) {
			for (int j = 0; j < colnumberCPF; j++) {

				if (globalpixelarray[i][j] == -1) {
					globalpixelarray[i][j] = -2;
				}


			}
		}

	}

}


void main() {

	char fileName[50], tempChar;
	int i, j, pixelBoard[SIZE][SIZE], rowNumber=0, colNumber=0;
	FILE* file;

	printf("Enter the file name: ");
	gets_s(fileName, 50);
	printf("\n");

	if (fopen_s(&file, fileName, "r") != 0) {
		printf("\nERROR: The file was not found! \n");
		exit(1);
	}

	//Dosyadan okuma ve pixelboarda geçiþ
	while (!feof(file)) {
		fscanf_s(file, "%d", &rowNumber);
		fscanf_s(file, "%d", &colNumber);
		tempChar = fgetc(file);
		for (i = 0; i < rowNumber; i++) {
			for (j = 0; j < colNumber; j++) {

				tempChar = fgetc(file);

				if (tempChar == 'x')
					pixelBoard[i][j] = 1;
				else if (tempChar == ' ')
					pixelBoard[i][j] = 0;
			}
			if (j == colNumber)
				tempChar = fgetc(file);
		}
	}

	// pixelboard array'i globalpixelarray'e aktarma
	for (int k = 0; k < rowNumber; k++) {
		for (int l = 0; l < colNumber; l++) {
			globalpixelarray[k][l] = pixelBoard[k][l];
		}
	}


	// blobslarý ekrana yansýtma
	printf("   ");
	for (i = 0; i < colNumber; i++)
		printf("%d", i % 10);

	printf("\n");
	printf("  +");

	for (i = 0; i < colNumber; i++)
		printf("-");

	printf("+");
	printf("\n");


	for (i = 0; i < rowNumber; i++) {
		for (j = 0; j < colNumber; j++) {
			if (j == 0)
				printf(" %d|", i%10);

			if (pixelBoard[i][j] == 1)
				printf("x");
			else
				printf(" ");

			if (j == colNumber - 1)
				printf("|%d", i%10);

		}
		printf("\n");

	}


	printf("  +");

	for (i = 0; i < colNumber; i++)
		printf("-");
	printf("+");

	printf("\n   ");

	for (i = 0; i < colNumber; i++)
		printf("%d", i % 10);
	printf("\n\n\n");

	fclose(file);
	

	// CPF fonksiyonun çaðrýlmasý ve blobslarýn tespiti
	printf("-----VALUES----\n\n");

	for (int k = 0; k < rowNumber; k++) {
		for (int l = 0; l < colNumber; l++) {
			if (globalpixelarray[k][l] == 1) {
				CPF(k, l, k, l,rowNumber,colNumber);

				float Comrow = (float)sumofrowvalues / (float)numbersofpixels;
				float Comcolumn = (float)sumofcolumnvalues / (float)numbersofpixels;
				
				blobnumber++;

				printf("%d.Blob have %d pixels and CoM Row value is %.2f and Com Column value is %.2f\n\n",blobnumber,numbersofpixels,Comrow,Comcolumn);

				numbersofpixels = 0;
				sumofcolumnvalues = 0;
				sumofrowvalues = 0;


			}
		}
	}

	printf("\n");

	system("pause");
}