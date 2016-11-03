#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

//Prototipos de función
void llena_vectores(void);
void llena_tabla(void);

//Variables globales
std::string item;
int peso, valor;
int n = 23; //cantidad de artículos
int w = 0; //capacidad de la mochila
int aux = 0;
vector<int> valores;
vector<int> pesos;
vector<string> items;
vector<string> items_seleccionados;

int main()
{
  llena_vectores();
  llena_tabla();
  return 0;
}

//Busca el archivo mochila.txt, lee los datos y los guarda en sus respectivos vectores
void llena_vectores()
{
  ifstream lector ("mochila.txt");

  if (lector)
  {
    lector>>w;
    for (int i = 0; i < 23; ++i)
    {
      lector>>peso>>valor>>item;
      
      valores.push_back (valor);
      pesos.push_back (peso);
      items.push_back (item);
    }
  }
  else
  {
    cout<<"No se pudo abrir el archivo"<<endl;
  }
}

void llena_tabla()
{
  ofstream escritor ("resultado.txt");
  int m[n][w];

  for (int i = 0; i <= w; ++i)
  {
    m[0][i] = 0;
  }
  items_seleccionados.push_back("Nada");
  for (int i = 1; i < n; ++i)
  {
    for (int j = 0; j <= w; ++j)
    {
      if (pesos[i] > j)
      {
        m[i][j] = m[i-1][j];
      }
      else
      {
        aux = fmax(m[i-1][j],m[i-1][j-pesos[i]]+valores[i]);

        if (aux == m[i-1][j-pesos[i]]+valores[i] && aux != m[i-1][j])
        {
          items_seleccionados.push_back(items[i]);
        }

        m[i][j] = aux;

      } 
    }
  }

  if (escritor)
  {
    for (int j = 0; j < w; ++j)
    {
      for (int i = 0; i < n; ++i)
      {
        escritor << "\t"<<m[i][j];
      }
      escritor << std::endl;
    }
    /*for (int i = 0; i < items_seleccionados.size(); ++i)
    {
      escritor <<items_seleccionados[i]<< std::endl;
    }*/
  }

}