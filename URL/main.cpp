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

unsigned long n = 0; // Rozmiar macierzy A i wektorów B i X
unsigned long max_it = 0; // Maksymalna iloœæ iteracji
double e = 0; // Dok³adnoœæ 'epsilon'

double *normy[3];

void a()
{

}

void b()
{
	// Przekszta³canie A i B
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

	memcpy(X, beta, (sizeof(double)*n));

	do {
		memcpy(oX, X, (sizeof(double)*n));
		it++;
		X = NULL;

		norma[0] = 0;
		norma[1] = 0;
		norma[2] = 0;
	} while ((norma[0] <= e) || (norma[1] <= e) || (norma[2] <= e) || (it >= max_it));
}

void d()
{

}

int main()
{
	return 0;
}