#include <iostream>
#include <string>
#include <fstream>

using namespace std;

double **A; // Macierz A
double *B; // Wektor B
double *X; // Wektor X
double *oX; // Wektor X poprzedniej iteracji

double **alfa; // Macierz alfa
double *beta; // Wektor beta

unsigned long n = 0; // Rozmiar macierzy A i wektor�w B i X
unsigned long max_liczba_iteracji = 0; // Maksymalna ilo�� iteracji
double epsilon = 0; // Dok�adno�� 'epsilon'

double *normy[3];

void a()
{
	ifstream plikWej�ciowy;
	string liczba;
	cout << "podaj rzad rownania" << endl;
	cin >> n;
	cout << "podaj max ilosc iteracji" << endl;
	cin >> max_liczba_iteracji;
	cout << "podaj epsilon" << endl;
	cin >> epsilon;
	plikWej�ciowy.open("Plik wejsciowy.txt");
	A = new double*[n];			//two�ymy miejsce na macierz A
	for (int i = 0; i < n; i++)
	{
		A[i] = new double[n];
	}
	B = new double[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			plikWej�ciowy >> liczba;
			A[i][j] = stod(liczba);			//pobieranie macierzy A z pliku
		}
	}
	for (int i = 0; i < n; i++)
	{
		plikWej�ciowy >> liczba;	//pobieranie macierzy B z pliku
		B[i] = stod(liczba);
	}
	plikWej�ciowy.close();
}

void b()
{
	// Przekszta�canie A i B
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{

		}
	}

	// Wyznaczanie alfy i bety
	alfa = new double*[n];
	for( int i = 0; i < n; i++ )
		alfa[i] = new double[n];

	beta = new double[n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			alfa[i][j] = (double)(i == j ? 0 : (-(A[i][j] / A[i][i])));
		}
		beta[i] = (double)(B[i] / A[i][i]);
	}
}

void c()
{
	double norma[3];
	unsigned long it = 0;
	double suma = 0;
	memcpy(X, beta, (sizeof(double)*n));
	for (int j = 0; j < n; j++)
	{
		norma[0] += abs(A[n - 1][j]);	//norma 1
		norma[1] += abs(A[j][n - 1]);	//norma 2
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			norma[2] += pow(A[i][j], 2);
		}
	}
	norma[2] = sqrt(norma[2]);		//norma 3
	do {
		memcpy(oX, X, (sizeof(double)*n));
		it++;
		X = NULL;

		norma[0] = 0;
		norma[1] = 0;
		norma[2] = 0;
	} while ((norma[0] <= epsilon) || (norma[1] <= epsilon) || (norma[2] <= epsilon) || (it >= max_liczba_iteracji));
}

void d()
{

}

int main()
{
	a();
	for (int i = 0; i < n; i++)	//zwolnienie pamieci
	{
		delete[] A[i];
	}
	delete[] A;
	delete[] B;
	cin.ignore();
	getchar();
	return 0;
}