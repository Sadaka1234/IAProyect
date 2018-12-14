#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <iterator>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;

// forward checking conflict-directed backjumping

//Struct para mostrar datos
struct datos{
  float score;
  set<int> nodos;
};


//Clase Nodos--------------------------------------------
class Nodo
  {
    int id, s; //posición x, posición y, puntaje s
		float x, y;
  public:
    Nodo (int, float, float, int);
    float get_x();
    float get_y();
    int get_s();
    int get_id();
  };
Nodo::Nodo(int idd,float a, float b, int c)
  {
  id = idd;
  x = a;
	y = b;
	s = c;
  };
float Nodo::get_x()
  {
  return x;
  };
float Nodo::get_y()
  {
  return y;
  };
int Nodo::get_s()
  {
  return s;
  };
int Nodo::get_id()
  {
  return id;
  };


//Distancia entre Nodos--------------------------------------------
float distancia(Nodo i, Nodo j)
  {
  return sqrt(pow(i.get_x()-j.get_x(), 2) + pow(i.get_y()-j.get_y(), 2));
  }

//Tiempo entre Nodos--------------------------------------------
float tiempo(Nodo i, Nodo j, int velocidad)
  {
  //velocidad = distancia/tiempo => tiempo = distancia/velocidad
  return distancia(i, j)/velocidad;
  }


//Clase rutas--------------------------------------------
class Ruta
  {
   std::vector<int> rutaInts;
   std::vector<Nodo> ruta;
   public:
     Ruta ();
     void addNodo(Nodo nodo);
     void delNodo();
     Nodo seeNodo();
     datos score(set<int> usados, int nu_nodos);
     float tiempoRuta(int velocidad);
     float tiempoRutaExtra(Nodo nodo, int velocidad);
     void rutaPrint();
     vector<int> rutaEnteros();
  };
Ruta::Ruta()
  {
  };

//Retorna Puntaje Ruta y la ruta en si con los nodos "usados"--------------------------------------------
datos Ruta::score(set<int> usados, int nu_nodos)
  {
  datos returning;
  std::vector<int> usadosPrima;
  float score = 0;
  //cout << "Cantidad de nodos de ruta: "<< ruta.size() << endl;
  for(std::vector<Nodo>::size_type i = 0; i != ruta.size(); i++)
    {
    if (std::find(usados.begin(), usados.end(), ruta[i].get_id())==usados.end())
      {
      score += ruta[i].get_s();
      usadosPrima.push_back(ruta[i].get_id());
      };
    };
  returning.score = score;
  usados.insert(usadosPrima.begin(), usadosPrima.end());
  returning.nodos.insert(usados.begin(), usados.end());
  return returning;
  };

//Tiempo total de ruta--------------------------------------------
float Ruta::tiempoRuta(int velocidad)
  {
  float time = 0;
  size_t Size0 = 0;
  size_t Size1 = 1;
  size_t Size = ruta.size();
  if ( Size == Size0 || Size == Size1)
    {
    return 0;
    }
  else
    {
    for(std::vector<Nodo>::size_type i = 0; i != (Size-1); i++)
      {
      time += tiempo(ruta[i], ruta[i+1], velocidad);
      };
    return time;
    }
  };

  //Tiempo total ruta mas tiempo de nodo ingresado--------------------------------------------
  float Ruta::tiempoRutaExtra(Nodo nodo, int velocidad)
  {
  float time = 0;
  size_t Size0 = 0;
  size_t Size1 = 1;
  size_t Size = ruta.size();
  if ( Size == Size0)
    {
    return 0;
    }
  else if (Size == Size1)
    {
    return tiempo(this->seeNodo(), nodo, velocidad);
    }
  else
    {
    for(std::vector<Nodo>::size_type i = 0; i != (Size-1); i++)
      {
      time += tiempo(ruta[i], ruta[i+1], velocidad);
      }
    time += tiempo(nodo, ruta.back(), velocidad);
    return time;
    }
  };

//Agrega nodo al final
void Ruta::addNodo(Nodo nodo)
  {
  ruta.push_back(nodo);
  rutaInts.push_back(nodo.get_id());
  }
//Borra nodo al final
void Ruta::delNodo()
  {
  ruta.pop_back();
  rutaInts.pop_back();
  }
//Muestra ultimo nodo
Nodo Ruta::seeNodo()
  {
  return ruta.back();
  }
//Printea la ruta
void Ruta::rutaPrint()
  {
    if (ruta.empty())
      {
      cout << "Empty";
      }
    else
    {
    for(std::vector<int>::size_type i = 0; i != ruta.size(); i++)
      {
      cout << rutaInts[i] << " ";
      };
    };
  cout << endl;
  };

  vector<int> Ruta::rutaEnteros()
    {
    return rutaInts;
    };

  // Best Global---------------------------------------------------------
  std::vector<Ruta> Route_Sbest;
  float Value_Sbest = 0;
  std::vector<Nodo> Grafo;
  int cont = 0;
  int contBest = 0;


// Funcion split para el input--------------------------------------------

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

//Aqui ocurre la magia--------------------------------------------
void FC(vector<Ruta> Rutas, int velocidad, int nu_nodos, int nu_rutas, float tiempo_max, set<int> Nodos, int iter)
  {
  //Condicion de termino de rutas
  if (iter > nu_rutas)
    {
    set<int> usados;
    float score = 0;
    datos dato;
    for(std::vector<Nodo>::size_type ruta = 0; ruta != (Rutas.size()-1); ruta++)
      {
      dato = Rutas[ruta].score(usados, nu_nodos);
      score += dato.score;
      };
    cont += 1;
    //Actualiza mejor valor
    if ( Value_Sbest <= score )
      {
      if (Value_Sbest == score )
        {
        contBest += 1;
        }
      else if (Value_Sbest < score)
        {
        contBest = 1;
        }
      Value_Sbest = score;
      Route_Sbest.clear();
      for(std::vector<Nodo>::size_type ruta = 0; ruta != (Rutas.size()-1); ruta++)
        {
        Route_Sbest.push_back(Rutas[ruta]);
        };
      }
    }

    //Si el ultimo nodo en una ruta es el nodo final, genera ruta nueva
    else if (Rutas.back().seeNodo().get_id() == (nu_nodos-1))
      {
      Nodos.clear();
      Ruta ruta = Ruta();
      ruta.addNodo(Grafo[0]);
      vector<int> usades;
      for (size_t i=0; i< Rutas.size(); i++)
        {
        vector<int> minirutita = Rutas[i].rutaEnteros();
        for (size_t j=0; j< minirutita.size(); j++)
          {
          usades.push_back(minirutita[j]);
          }
        }
      Rutas.push_back(ruta);
      for (int i=1; i<nu_nodos; i++)
          {
          Nodos.insert(i);
          };
      for (std::vector<int>::size_type i = 0; i < usades.size(); i++)
        {
        if (usades[i]!= 0 && usades[i] != (nu_nodos-1))
            {
            Nodos.erase(Nodos.find(usades[i]));
            }
      };
      FC(Rutas, velocidad, nu_nodos, nu_rutas, tiempo_max, Nodos, iter+1);
      }
    //Cualquier otro caso
    else
      {
        //Se filtra el dominio (Permite eliminar los conflictos futuros. Los pasados ya fueron filtrados en el paso 0)
        set<int> nodostemp;
        for (set<int>::iterator it = Nodos.begin(); it != Nodos.end(); ++it)
          {
          if (Rutas.back().tiempoRutaExtra(Grafo[*it], velocidad) <= tiempo_max)
            {
            nodostemp.insert(*it);
            }
          }
          Nodos.clear();
          Nodos.insert(nodostemp.begin(), nodostemp.end());

          const bool is_in = Nodos.find(nu_nodos-1) != Nodos.end();
          while(!Nodos.empty() && is_in)
            {
            Rutas.back().addNodo(Grafo[*Nodos.begin()]);
            Nodos.erase(*Nodos.begin());
            FC(Rutas, velocidad, nu_nodos, nu_rutas, tiempo_max, Nodos, iter);
            Rutas.back().delNodo();
            };
          };
        };



//Main
int main(){
	std::ios::sync_with_stdio(false);
  //Declaración de variables
	string input, n, m, t;			//String iterador, num_nodos, num_rutas, tiempo_máximo
  std::set<int> Nodos; //Cola con ID's de nodos por revisar (parte con todos)
  std::vector<Ruta> Rutas; // Vector con rutas
  auto start = std::chrono::system_clock::now( );

  //velocidad
  //srand(time(NULL));
  //rand()%30+1;
  float velocidad = 1;

  //Proximas 9 lineas solo para recibir los primeros 3 datos54rf
  std::getline(std::cin, n);
	std::getline(std::cin, m);
	std::getline(std::cin, t);
	int nu_nodos = std::stoi (n.substr(2));
	int nu_rutas = std::stoi(m.substr(2));
	float tiempo_max = std::stof(t.substr(5));







  //Vector con Nodos
  vector<string> temp_array;
  // Iterador para recibir los nodos

	for (int i = 0; i<nu_nodos; i += 1)
			{
			std::getline(std::cin, input);
      temp_array = split(input , '	');
      Grafo.push_back( Nodo(i, std::stof(temp_array[0]) , std::stof(temp_array[1]) , std::stoi(temp_array[2])) );
			};
  Ruta rutita = Ruta();
  int posible = 0;
  //CAso en que no sea posible llegar desde el nodo 0 al nodo n-1 (imposible)
  if (tiempo(Grafo[0], Grafo[nu_nodos-1], velocidad) > tiempo_max)
    {
    cout << "-------------- No existe solución alguna ------------------------------------------------------------------------" << endl;
    posible = 1;
    Value_Sbest = 0;
    Ruta ruta = Ruta();
    Route_Sbest.push_back( ruta );
    Route_Sbest.back().addNodo(Grafo[0]);
    }
  else
    {
    //Primer caso
    Ruta ruta = Ruta();
    ruta.addNodo(Grafo[0]);
    Rutas.push_back(ruta);
    //Cola con elementos
    for (int i=1; i<nu_nodos; i++)
        {
        Nodos.insert(i);
        };
    FC(Rutas, velocidad, nu_nodos, nu_rutas, tiempo_max, Nodos, 1);
    };
  //De aqui en adelante son solo prints
  cout << endl;
  cout << "Número Nodos: " << nu_nodos << endl; //Numero nodos
	cout << "Número Rutas: " << nu_rutas << endl;  //Numero rutas
	cout << "Tiempo Máximo: " << tiempo_max << endl;  //Tiempo maximo ruta
  cout << "Velocidad: "<< velocidad << endl; //velocidad
  if (posible == 1)
    {
    cout << "Imposible obtener solución" << endl;
    cout << "IMPORTANTE: Tiempo de nodo inicial a final mayor al tiempo máximo: " << tiempo(Grafo[0], Grafo[nu_nodos-1], velocidad) << endl;
    }
  else
    {
    cout << "Cantidad de soluciones posibles: " << cont << endl;
    cout << "Cantidad de soluciones optimas: " << contBest << endl;
    cout << "Mejor solución encontrada: " << endl;
    cout << "Score total ruta: " << Value_Sbest << endl;
    set<int> usados;
    for (int i = 0; i < nu_rutas; i++){
      datos datito = Route_Sbest[i].score(usados,nu_nodos);
      cout << "Ruta " << i << ":::  ";
      cout << "Score : " << datito.score << " | ";
      cout << "Tiempo : "<< Route_Sbest[i].tiempoRuta(velocidad) << " | ";
      usados.insert(datito.nodos.begin(), datito.nodos.end());
      Route_Sbest[i].rutaPrint();

      };
    }

   std::chrono::duration<float> elapsed = std::chrono::system_clock::now() - start;

  cout << "Tiempo de ejecución: " << elapsed.count( )<< " [segundos]" << endl;

  return 0;
};
