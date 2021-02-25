#include<stdio.h> //librarie folosita pentru citire si scriere
#include<stdlib.h> //librarie folosita pentru alocarea/dezalocarea pointerilor
#include<math.h> //libarrie a folosi diverse functii matematice

void test1(int& x) {
	x++;
}

//metoda bisectiei
//Sa se rezolve ecuatiile 1,2,3 prin metoda bisectiei

double ecuatie1(double x) {
	return 3 * pow(x, 3) - 2 * pow(x, 2) + 10 * x + 30;
}

double ecuatie2(double x) {
	return 3 * x - 9;
}

double ecuatie3(double x) {
	return 3 * pow(x, 2) - 3 * x - 1;
}

void metodaBisectiei(double A, double B, int N,
	double(*ptr_ecuatie)(double), double epsilon,
	double& solutie, int& cod) {//se pune "&" pentru ca variabilele cod si solutie se modifica in acest bloc si vrem sa primim valorile modificate si in main()

	//A,B - capetele intervalului in care se cauta radacina unica

	//N-numarul maxim de pasi de cautare(daca nu gasesti radicina in 1000 pasi te opresti...nu cauti la nesfarsit)

	//double(*ptr_ecuatie)(double) - pointer la functie -> folosita pentru a transmite mai departe ecuatiile de mai sus 1,2,3
	//daca va uitati atent pointerul la functie are acelasi format ca antetul functiilor de mai sus.

	//epsilon - eroarea acceptata - o variabila cat mai mica : 0.00001 

	//solutie - se va salva in variabila solutie valoarea radacinei
	//cod - poate fi 0 sau 1 ...-> 1 daca s-a gasit radacina, 0 altfel.

	solutie = cod = 0;

	if (ptr_ecuatie(A) == 0) { solutie = A; cod = 1; return; } //aici se verifica daca partea inferioara a intervalului este radacina ecuatiei
	if (ptr_ecuatie(B) == 0) { solutie = B; cod = 1; return; } //aici se verifica daca partea superioara a intervalului este radacina ecuatiei
	if (ptr_ecuatie(A) * ptr_ecuatie(B) > 0) {
		printf("Nu s-a gasit nicio radacina sau s-au gasit prea multe\n"); //aici e clar ce se intampla sper...
		cod = 0; return;
	}
	while (N > 0 && cod == 0) {///se itereaza in maxim N pasi sau pana cand se gaseste radacina
		solutie = (A + B) / 2; //ne pozitionam la mijlocul intervalului [A,B]

		if (ptr_ecuatie(solutie) == 0) { //daca valoarea de la mijlocul intervalului [A,B] este radacina atunci am gasit solutia.
			cod = 1; continue;
		}

		if (ptr_ecuatie(A) * ptr_ecuatie(solutie) < 0) {//daca nu s a gasit radacina mai sus atunci trebuie sa cautam alt interval
			B = solutie;//in cazul asta noul interval de cautare va fi [A,solutie] - (unde solutie era (A+B)/2)
		}
		else {
			A = solutie;//in cazul asta noul interval de cautare va fi [solutie, B] - (unde solutie era (A+B)/2)
		}

		if (B - A <= epsilon) {//se accepta o radacina x in care f(x) sa tinda catre 0......
			cod = 1;
		}

		N--;//se trece la urmatorul pas. daca nu se gaseste solutia in N pasi atunci codul ramane 0;
	}


}

void main() {
	//bit 0-1
	//1 byte este format din biti
	int x = 10;//var. intreaga - ocupa 4 bytes 
	float y = 12.3;//var. reala - ocupa 4 bytes
	double z = 1888.22;//var.reala - ocupa 8 bytes
	char w = 'c';//var. caracter - ocupa 1 byte


	//%d = format de afisare pentru int
	//%lf = format de afisare pentru double
	//%f = format de afisare pentru flot
	//%c = format de afisare pentru chat
	//%p = format de afisare pentru pointer/adrese
	printf("Acesta este un mesaj.\n");
	printf("x=%d  y=%.2f z=%.2lf  w=%c\n\n", x, y, z, w);
	printf("adresa lui x = %p\n", &x);


	int hh1 = 200;
	test1(hh1);
	printf("hh1=%d\n", hh1);

	int* pointerX = &hh1;
	(*pointerX)++;
	printf("hh1=%d\n", hh1);


	printf("valoarea variabilei pointerulX este: %p\n", pointerX);
	printf("adresa lui hh1 este: %p\n", &hh1);
	printf("valoarea de la adresa stocata in variabila pointerulX este: %d\n", *pointerX);

	int a;
	double b;

	//printf("a=");
	//scanf_s("%d", &a);
	//printf("a=%d\n", a);

	//printf("b=");
	//scanf_s("%lf", &b);
	//printf("b=%.2lf\n", b);

	//int N;
	//printf("N="); scanf_s("%d", &N);
	
	//int* vector = (int*)malloc(N * sizeof(int)); // aloca pe heap memorie pentru N elemente de tip int
	//int* vector = (int*)calloc(N, sizeof(int)); //aloca pe heap memorie pentru N elemente de tip int si in plus toate elementele sunt initializate cu 0.
	//int* vector = (int*)realloc(vector, 100 * sizeof(int)); //realoca memorie pentru un vector existent(adica scazi/cresti nr de elemente din vector).
	/*for (int i = 0; i < N; i++) {
		printf("vector[%d]=", i);
		scanf_s("%d", &vector[i]);
	}

	for (int i = 0; i < N; i++) {
		printf("vector[%d]=%d ", i, vector[i]);
	}*/

	//free(vector);


	//pointer la functie
	double (*ptrLaFunctie)(double);
	
	ptrLaFunctie = ecuatie1;
	printf("Dupa apelare de ecuatie1(2) se afiseaza: %.2lf\n", ptrLaFunctie(2));

	ptrLaFunctie = ecuatie2;
	printf("Dupa apelare de ecuatie2(2) se afiseaza: %.2lf\n", ptrLaFunctie(2));

	ptrLaFunctie = ecuatie3;
	printf("Dupa apelare de ecuatie3(2) se afiseaza: %.2lf\n", ptrLaFunctie(2));


	//metoda bisectiei
	double solutie = 0;
	int cod = 0;
	metodaBisectiei(-2, 12, 1000, ecuatie1, 0.0001, solutie, cod);
	printf("ecuatie 1: cod=%d, solutie=%.2lf\n", cod, solutie);

	metodaBisectiei(-2, 12, 1000, ecuatie2, 0.0001, solutie, cod);
	printf("ecuatie 2: cod=%d, solutie=%.2lf\n", cod, solutie);

	metodaBisectiei(-2, 12, 1000, ecuatie3, 0.0001, solutie, cod);
	printf("ecuatie 3: cod=%d, solutie=%.2lf\n", cod, solutie);
}

