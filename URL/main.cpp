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
unsigned long max_liczba_iteracji = 0; // Maksymalna iloœæ iteracji
double epsilon = 0; // Dok³adnoœæ 'epsilon'

double normy[3];

void a()
{
	ifstream plikWejœciowy;
	string liczba;
	cout << "podaj rzad rownania" << endl;
	cin >> n;
	cout << "podaj max ilosc iteracji" << endl;
	cin >> max_liczba_iteracji;
	cout << "podaj epsilon" << endl;
	cin >> epsilon;
	plikWejœciowy.open("Plik wejsciowy.txt");
	A = new double*[n];			//two¿ymy miejsce na macierz A
	for (int i = 0; i < n; i++)
	{
		A[i] = new double[n];
	}
	B = new double[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			plikWejœciowy >> liczba;
			A[i][j] = stod(liczba);			//pobieranie macierzy A z pliku
		}
	}
	for (int i = 0; i < n; i++)
	{
		plikWejœciowy >> liczba;	//pobieranie macierzy B z pliku
		B[i] = stod(liczba);
	}
	plikWejœciowy.close();
}

int b()
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
			if (i == j)
			{
				alfa[i][j] = 0;
			}
			else if (A[i][i] != 0)
			{
				alfa[i][j] = -(A[i][j] / A[i][i]);
			}
			else
			{
				return 1;
			}
			//alfa[i][j] = (double)(i == j ? 0 : (-(A[i][j] / A[i][i])));
		}
		beta[i] = (double)(B[i] / A[i][i]);
	}
	return 0;
}

void c()
{
	//double norma[3];	//normy maja byc liczone z alfy
	unsigned long it = 0;
	double suma = 0;
	oX = new double[n];	//poprzednia iteracja
	X = new double[n];
	for (int i = 0; i < n; i++)
	{
		X[i] = beta[i];
	}
	//memcpy(X, beta, (sizeof(double)*n));
	//X = new double[n];
	
	do {
		//memcpy(oX, X, (sizeof(double)*n));	//kopiuje aktualny wektor
		for (int i = 0; i < n; i++)
		{
			oX[i] = X[i];
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (j != i)
				{
					suma =+ alfa[i][j] * oX[j] + beta[i];	//obliczanie nowego X
				}
			}
			X[i] = suma;		//zapisuje sume do aktualnego wektora
			suma = 0;
		}

		it++;

		normy[0] = abs(X[n-1]);		//norma 1
		suma = 0;
		for (int i = 0; i < n; i++)
		{
			suma += abs(X[i]);
		}
		normy[1] = suma;		//norma 2
		suma = 0;
		for (int i = 0; i < n; i++)
		{
			suma += pow(X[i], 2);	
		}
		normy[2] = sqrt(suma);		//norma 3
	} while ((normy[0] <= epsilon) || (normy[1] <= epsilon) || (normy[2] <= epsilon) || (it >= max_liczba_iteracji));
	cout << "iteracja "<<it << endl;
	for (int i = 0; i < n; i++)
	{
		cout<<X[i]<<endl;
	}
}

void d()
{

}

int main()
{
	a();
	if (b() != 1)
	{
		c();
	}
	else
	{
		cout << "dzielenie przez 0";
	}
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