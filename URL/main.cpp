#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

double **A; // Macierz A
double *B; // Wektor B
double *X; // Wektor X
double *oX; // Wektor X poprzedniej iteracji

double **alfa; // Macierz alfa
double *beta; // Wektor beta

unsigned long n = 0; // Rozmiar macierzy A i wektorów B i X
unsigned long max_liczba_iteracji = 0; // Maksymalna ilość iteracji
double epsilon = 0; // Dokładność 'epsilon'
int iteracja;
double normy[3];

void a()
{
	ifstream plikWejściowy;
	string liczba;
	cout << "podaj rzad rownania" << endl;
	cin >> n;
	cout << "podaj max ilosc iteracji" << endl;
	cin >> max_liczba_iteracji;
	cout << "podaj epsilon" << endl;
	cin >> epsilon;
	plikWejściowy.open("Plik wejsciowy.txt");
	A = new double*[n];			//twożymy miejsce na macierz A
	for (int i = 0; i < n; i++)
	{
		A[i] = new double[n];
	}
	B = new double[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			plikWejściowy >> liczba;
			A[i][j] = stod(liczba);			//pobieranie macierzy A z pliku
		}
	}
	for (int i = 0; i < n; i++)
	{
		plikWejściowy >> liczba;	//pobieranie macierzy B z pliku
		B[i] = stod(liczba);
	}
	plikWejściowy.close();
}

int b()
{
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
			else if (A[i][i] != 0)		//sprawdzanie dzielenia przez 0
			{
				alfa[i][j] = -(A[i][j] / A[i][i]);		//obliczanie alfy
			}
			else
			{
				return 1;
			}
		}
		if (A[i][i] != 0)		//sprawdzanie dzielenia przez 0
		{
			beta[i] = (double)(B[i] / A[i][i]);		//obliczanie bety
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

void c()
{
	unsigned long it = 0;
	double suma = 0;
	double stopObliczen = 0;
	double warunkiZbieznosci[3];
	oX = new double[n];	//poprzednia iteracja
	X = new double[n];
	for (int i = 0; i < n; i++)
	{
		X[i] = beta[i];
	}
	
	do {

		for (int i = 0; i < n; i++)
		{
			oX[i] = X[i];		//kopiowanie poprzedniego wektora
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (j != i)
				{
					suma =+ alfa[i][j] * oX[j] ;	//obliczanie nowego X
				}
			}
			X[i] = suma + beta[i];		//zapisuje sume do aktualnego wektora
			suma = 0;
		}

		it++;
		stopObliczen = 0;
		for (int i = 0; i < n; i++)	//stop pobliczen iteracyjnych sposobem 2
		{
			stopObliczen += abs(X[i] - oX[i]);
		}
		stopObliczen = stopObliczen / n;
		stopObliczen = sqrt(stopObliczen);
	} while ((stopObliczen>=epsilon) && (it <= max_liczba_iteracji));
	iteracja = it;
	suma = 0;
	//obliczanie warunkow zbieznosci
	for (int i = 0; i < n; i++)
	{
		suma += abs(alfa[n - 1][i]);		//1 warunek zbieznosci
	}
	warunkiZbieznosci[0] = suma;
	suma = 0;
	for (int i = 0; i < n; i++)
	{
		suma += abs(alfa[i][n-1]);		//2 warunek zbieznosci
	}
	warunkiZbieznosci[1] = suma;
	suma = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			suma += pow(alfa[i][j],2);		//3 warunek zbieznosci
		}
	}
	warunkiZbieznosci[2] = sqrt(suma);
	cout << warunkiZbieznosci[0] << " " << warunkiZbieznosci[1] << " " << warunkiZbieznosci[2] << endl;
	if ((warunkiZbieznosci[0] < 1) && (warunkiZbieznosci[1] < 1) && (warunkiZbieznosci[2] < 1))
	{
		cout << "proces zbiezny";
	}
	else
	{
		cout << "proces nie zbiezny";
	}
}

void d()
{
	ofstream plik;
	
	double *bladBezwzgledny;
	double rozwiazanieDokladne[] = { 1, 1, 0, -1, - 1 };
	plik.open("raport.txt");
	plik << "Macierz A" <<endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			plik << setw(8) << A[i][j] << " ";
		}
		plik << endl;
	}
	plik << "Wektor B" << endl;
	for (int i = 0; i < n; i++)
	{
		plik << setw(8) << B[i] << " ";
	}
	plik << endl;
	plik << "Epsilon: " << epsilon << " maxymalna ilosc iteracji " << max_liczba_iteracji << endl;
	plik << "Alfa" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			plik << setw(8) << alfa[i][j] << " ";
		}
		plik << endl;
	}
	plik << endl;
	plik << "Beta" << endl;
	for (int i = 0; i < n; i++)
	{
		plik << setw(8) << beta[i] << " ";
	}
	plik << endl;
	plik << "Przedostatnia iteracja" << endl;
	for (int i = 0; i < n; i++)
	{
		plik << setw(8) << oX[i] << " ";
	}
	plik << endl;
	plik << "Ostatnia iteracja" << endl;
	for (int i = 0; i < n; i++)
	{
		plik << setw(8) << X[i] << " ";
	}
	plik << endl;
	plik << "ilosc iteracji " << iteracja << endl;
	bladBezwzgledny = new double[n];
	for (int i = 0; i < n;i++)
	{
		bladBezwzgledny[i] = abs(rozwiazanieDokladne[i] - X[i]);
	}
	plik << "blad bezwzgledny ";		//obliczenie bledu bezwzglednego
	for (int i = 0; i < n; i++)
	{
		plik << bladBezwzgledny[i]<<" ";
	}
	delete[] bladBezwzgledny;
}

int main()
{
	ofstream plik;
	a();
	if (b() == 0)		//jeśli nie będzie dzielenia przez zero
	{
		c();
		d();
	}
	else
	{
		cout << "dzielenie przez 0";
		plik.open("raport.txt");
		plik << "blad" << endl<<"dzielenie przez 0";

	}
	for (int i = 0; i < n; i++)	//zwolnienie pamieci
	{
		delete[] A[i];
		delete[] alfa[i];
	}
	delete[] X;
	delete[] oX;
	delete[] beta;
	delete[] alfa;
	delete[] A;
	delete[] B;
	cin.ignore();
	getchar();
	return 0;
}