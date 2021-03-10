#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum CULORI {
	ROZ,
	ALB = 10,
	VERDE,
	MARO,
	ALBASTRU,
	ROSU = 20,
	GALBEN,
	PORTOCALIU
};

const char* transformaEnumInSirDeCaractere(CULORI culoare) {
	switch (culoare)
	{
	case ROZ:
		return "roz";
	case ALB:
		return "alb";
	case VERDE:
		return "verde";
	case MARO:
		return "maro";
	case ALBASTRU:
		return "albastru";
	case ROSU:
		return "rosu";
	case GALBEN:
		return "galben";
	case PORTOCALIU:
		return "partocaliu";
	}
}

CULORI transformaSirDeCaractereInEnum(char* culoareCaSirDeCaractere) {
	if (strcmp(culoareCaSirDeCaractere, "roz") == 0) {
		return CULORI::ROZ;
	}
	else if (strcmp(culoareCaSirDeCaractere, "alb") == 0) {
		return CULORI::ALB;
	}
	else if (strcmp(culoareCaSirDeCaractere, "verde") == 0) {
		return CULORI::VERDE;
	}
	else if (strcmp(culoareCaSirDeCaractere, "maro") == 0) {
		return CULORI::MARO;
	}
	else if (strcmp(culoareCaSirDeCaractere, "albastru") == 0) {
		return CULORI::ALBASTRU;
	}
	else if (strcmp(culoareCaSirDeCaractere, "rosu") == 0) {
		return CULORI::ROSU;
	}
	else if (strcmp(culoareCaSirDeCaractere, "galben") == 0) {
		return CULORI::GALBEN;
	}
	else if (strcmp(culoareCaSirDeCaractere, "partocaliu") == 0) {
		return CULORI::PORTOCALIU;
	}
}

union user
{
	int varsta; //4bytes
	char nume[40]; //40byte
	char gen;//M sau F - 1byte
};

struct client {
	char nume[50]; //50bytes
	int varsta; //4bytes
};

struct telefon
{
	CULORI culoareTelefon;
	char* marca;
	double pret;
	int anFabricatie;
	char marime;
	bool android;
	client proprietarTelefon;
};

void afisareClient(client c) {
	printf("nume = %s\n", c.nume);
	printf("varsta = %d\n", c.varsta);
}

void afisareClientInFisier(FILE* fisier, client c) {
	fprintf(fisier, "%s\n", c.nume);
	fprintf(fisier, "%d\n", c.varsta);
}

void afisareTelefon(telefon t)
{
	printf("marca = %s\n", t.marca);
	printf("culoare = %s\n", transformaEnumInSirDeCaractere(t.culoareTelefon));
	printf("pret = %.2lf\n", t.pret);
	printf("an fabricatie = %d\n", t.anFabricatie);
	printf("marime = %c\n", t.marime);

	printf("android = %s\n", t.android == true ? "true" : "false");

	afisareClient(t.proprietarTelefon);
}

void afisareTelefonInFisier(FILE* fisier, telefon t)
{
	fprintf(fisier, "%s\n", t.marca);
	fprintf(fisier, "%s\n", transformaEnumInSirDeCaractere(t.culoareTelefon));
	fprintf(fisier, "%.2lf\n", t.pret);
	fprintf(fisier, "%d\n", t.anFabricatie);
	fprintf(fisier, "%c\n", t.marime);

	fprintf(fisier, "%s\n", t.android == true ? "true" : "false");

	afisareClientInFisier(fisier, t.proprietarTelefon);
}

void citireClientDinFisier(FILE* fisier, client& c) {
	fgetc(fisier);
	fgets(c.nume, 100, fisier);
	c.nume[strcspn(c.nume, "\n")] = 0;//pentru a scapa de \n cand citesti cu fgets

	fscanf(fisier, "%d", &c.varsta);
}

void citireTelefonDinFisier(FILE* fisier, telefon& t) {
	char aux[100];
	fscanf(fisier, "%s", &aux);
	t.marca = (char*)malloc((strlen(aux) + 1) * sizeof(char));//+1 reprezinta '\0' -> sf de sir caractere
	strcpy(t.marca, aux);

	fscanf(fisier, "%s", &aux);
	t.culoareTelefon = transformaSirDeCaractereInEnum(aux);

	fscanf(fisier, "%lf", &t.pret);
	fscanf(fisier, "%d", &t.anFabricatie);
	fscanf(fisier, " %c", &t.marime); //la %c cand se citeste din fisier se citeste linie noua in loc de marime...si trb sa pui spatiu in fata ca sa evita asta

	fscanf(fisier, "%s", &aux);
	if (strcmp(aux, "true") == 0) {
		t.android = true;
	}
	else {
		t.android = false;
	}

	citireClientDinFisier(fisier, t.proprietarTelefon);
}


void scriereTelefonInFisierBinar(FILE* fisier, telefon t) {
	//functia fwrite - primeste ca input===> fwrite(addressData, sizeData, numbersData, pointerToFile);
	//addressData - adresa variabilei scrise (cu "&" in fata)
	//sizeData - dimensiunea variabilei salvate (sizeof)
	//numbersData - numarul de variabile salvate
				//int arr[3] = {101, 203, 303};
				// 
				//fwrite(arr, sizeof(int), 2, fp); //va scrie primele 2 elemente din vector
	//pointerToFile - fisierul unde se salveaza variabila, adica:  fisierBinarOut

	//DACA scrierea are erori atunci fwrite va retuna un numar mai mic decat variabila numbersData;

	//fwrite(&l, sizeof(l), 1, fisier);//scriam asa daca nu aveam char*
		
	char aux[100];
	strcpy(aux, t.marca);
	fwrite(&aux, sizeof(aux), 1, fisier);

	strcpy(aux, transformaEnumInSirDeCaractere(t.culoareTelefon));
	fwrite(&aux, sizeof(aux), 1, fisier);

	fwrite(&t.pret, sizeof(t.pret), 1, fisier);
	fwrite(&t.anFabricatie, sizeof(t.anFabricatie), 1, fisier);
	fwrite(&t.marime, sizeof(t.marime), 1, fisier);

	if (t.android == true) {
		strcpy(aux, "true");
	}
	else {
		strcpy(aux, "false");
	}
	fwrite(&aux, sizeof(aux), 1, fisier);

	fwrite(&t.proprietarTelefon, sizeof(t.proprietarTelefon), 1, fisier);
}

void citireTelefonDinFisierBinar(FILE* fisier, telefon& t) {
	//citire din fisier binar
	//functia fread - primeste ca input===> fread(addressData, sizeData, numbersData, pointerToFile);
	//descrierea parametrilor este la fel ca la fwrite

	//fread(&l, sizeof(l), 1, fisier); //scriam asa daca nu aveam char*

	char aux[100];
	fread(&aux, sizeof(aux), 1, fisier);
	t.marca = (char*)malloc((strlen(aux) + 1) * sizeof(char));
	strcpy(t.marca, aux);

	fread(&aux, sizeof(aux), 1, fisier);
	t.culoareTelefon = transformaSirDeCaractereInEnum(aux);

	fread(&t.pret, sizeof(t.pret), 1, fisier);
	fread(&t.anFabricatie, sizeof(t.anFabricatie), 1, fisier);
	fread(&t.marime, sizeof(t.marime), 1, fisier);

	fread(&aux, sizeof(aux), 1, fisier);
	if (strcmp(aux, "true") == 0) {
		t.android = 1;
	}
	else {
		t.android = 0;
	}

	fread(&t.proprietarTelefon, sizeof(t.proprietarTelefon), 1, fisier);
}

void main() {
	int X = 10;
	CULORI culori = CULORI::MARO;
	printf("%d\n", culori);

	user u;
	u.varsta = 20;
	printf("%d\n", u.varsta);

	u.gen = 'M';
	printf("%c\n", u.gen);

	strcpy(u.nume, "Gigel");
	printf("%s\n", u.nume);


	telefon t;

	strcpy(t.proprietarTelefon.nume, "Popescu Ion");
	t.proprietarTelefon.varsta = 20;

	t.marca = (char*)malloc((strlen("Huawei") + 1) * sizeof(char));//+1 reprezinta '\0' -> sf de sir caractere
	strcpy(t.marca, "Huawei");

	t.culoareTelefon = CULORI::PORTOCALIU;
	t.anFabricatie = 2020;
	t.pret = 3999.99;
	t.android = true;
	t.marime = 'M';

	printf("\n\n");
	afisareTelefon(t);

	//scriere in fisier

	//w-creare fisier si scriere in el, daca exista fisierul exista se sterg toate informatiile din el
	//wb-este "w" in mod binar

	//r-citire din fisier, daca fisierul nu exista se intoarce NULL la fopen()
	//rb-este "r" in mod binar, daca fisierul nu exista se intoarce NULL la fopen()

	//a-adaugare informatii la sf fisierului, daca NU exista fisierul se face unul nou
	//ab- este "a" in mod binar

	//r+ sau rb+ - fisier deschis pentru citire si scriere/ citire si scriere in mod binar, daca fisierul nu exista se intoarce NULL la fopen()

	//w+ sau wb+ - fisier deschis pentru citire si scriere in mod binar. 

	//a+ si ab+ - fisier deschis pentru citire si adaugare la final

	FILE* fisier = fopen("telefoane.txt", "w");
	if (fisier == NULL) {
		printf("ERROR: telefoane.txt nu a fost deschis pentru scriere\n");
		exit(1);
	}
	printf("\n\nS-a scris ceva in fisierul text\n\n");

	afisareTelefonInFisier(fisier, t);

	fclose(fisier);

	free(t.marca);

	FILE* fisier2 = fopen("telefoane.txt", "r");
	if (fisier2 == NULL) {
		printf("ERROR: telefoane.txt nu a putut fi deschis pentru citire\n");
		exit(1);
	}

	telefon t2;
	citireTelefonDinFisier(fisier2, t2);

	afisareTelefon(t2);

	fclose(fisier2);


	// scriere si citire din fisier binar

	FILE* fisierBinar = fopen("telefoaneBinar.bin", "wb");
	if (fisierBinar == NULL) {
		printf("ERROR: telefoaneBinar.bin nu a fost deschis pentru scriere\n");
		exit(1);
	}
	printf("\n\nS-a scris ceva in fisierul binar\n\n");

	scriereTelefonInFisierBinar(fisierBinar, t2);
	fclose(fisierBinar);


	FILE* fisierBinar2 = fopen("telefoaneBinar.bin", "rb");
	if (fisierBinar2 == NULL) {
		printf("ERROR: telefoaneBinar.bin nu a putut fi deschis pentru citire\n");
		exit(1);
	}

	telefon t4;
	citireTelefonDinFisierBinar(fisierBinar2, t4);

	afisareTelefon(t4);

	fclose(fisierBinar2);

	free(t2.marca);
	free(t4.marca);
	

	printf("\n\n==========feof=======\n\n");

	FILE* fisierTxt = fopen("telefoane.txt", "r");
	if (fisierTxt == NULL) {
		printf("ERROR: telefoane.txt nu a fost deschis pentru scriere\n");
		exit(1);
	}

	char aux[100];
	fscanf(fisierTxt, "%s", &aux);
	while (!feof(fisierTxt)) {
		printf("%s\n", aux);

		fscanf(fisierTxt, "%s", &aux);
	}

	rewind(fisierTxt);
	printf("\n\n");

	fscanf(fisierTxt, "%s", &aux);
	while (!feof(fisierTxt)) {
		printf("%s\n", aux);

		fscanf(fisierTxt, "%s", &aux);
	}

	fclose(fisierTxt);
}