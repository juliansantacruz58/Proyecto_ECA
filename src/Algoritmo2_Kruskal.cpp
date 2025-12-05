/* Universidad Autónoma de Aguascalientes
   Centro de Ciencias Básicas
   Ciencias de la Computación
   Ing. en Computación Inteligente
   Semestre: III
   Materia: Estructuras Computacionales Avanzadas.
   Docente: Miguel Ángel Meza de Luna
   Alumno: José Julián Badajoz Santacruz.
   Algoritmo 2: Krusjal. */

#include <iostream>
#include <locale.h>

using namespace std;

//Definición de tamaños globales.
#define MAXN 100
#define MAXE 500   

//Aristas guardadas: u, v y peso.
int edges[MAXE][3];
int edgeCount= 0;

//UNION-FIND para evitar ciclos.
int padre[MAXN];
int rangoUF[MAXN];

//Prototipo de funciones:
void makeSet(int n);
int findUF(int x);
bool unionUF(int x, int y);
void ordenarAristas();
void kruskal(int n);

int main() 
{
	setlocale(LC_ALL, "");
	
    int n, m;

    cout << "----- KRUSKAL -----" << endl;

    cout << "¿Cuántos nodos tiene el grafo? " << endl;
    cin >> n;

    cout << "¿Cuántas aristas tiene? " << endl;
    cin >> m;

    cout << "\nIntroduce las aristas en formato: u v peso" << endl;
    cout << "(Esto significa una arista no dirigida entre u y v)" << endl;

    for(int i=0; i<m; i++) 
	{
        cout << "\nArista " << i+1 << ": ";
        cin >> edges[edgeCount][0] >> edges[edgeCount][1] >> edges[edgeCount][2];
        edgeCount++;
    }

    kruskal(n);

    return 0;
};

//Creación de conjuntos de nodos.
void makeSet(int n) 
{
    for(int i=0; i<n; i++) 
	{
        padre[i]= i;
        rangoUF[i]= 0;
    }
};

//Hallazgo del elemento principal del conjunto.
int findUF(int x) 
{
    if(padre[x]!= x) 
	{
		//Comprensión del camino.
        padre[x]= findUF(padre[x]); 
	}
    return padre[x];
};

//Unión de nodos.
bool unionUF(int x, int y) 
{
    int rx= findUF(x);
    int ry= findUF(y);

    if(rx==ry)
	{
		return false;
	} 

    if(rangoUF[rx]<rangoUF[ry]) 
	{
        padre[rx]= ry;
    }
    else if(rangoUF[rx]>rangoUF[ry]) 
	{
        padre[ry]= rx;
    }
    else 
	{
        padre[ry]= rx;
        rangoUF[rx]++;
    }

    return true;
};

//Ordenamiento por método de la búrbuja (Burble Sort).
void ordenarAristas() 
{
    for(int i=0; i<edgeCount-1; i++) 
	{
        for(int j=0; j<edgeCount-i-1; j++) 
		{
            if(edges[j][2]>edges[j+1][2]) 
			{
			    //Intercambio simple.
                int u= edges[j][0];
                int v= edges[j][1];
                int w= edges[j][2];

                edges[j][0]= edges[j+1][0];
                edges[j][1]= edges[j+1][1];
                edges[j][2]= edges[j+1][2];

                edges[j+1][0]= u;
                edges[j+1][1]= v;
                edges[j+1][2]= w;
            }
        }
    }
};

//Algoritmo Kruskal.
void kruskal(int n) 
{
    makeSet(n);
    ordenarAristas();

    int costoTotal= 0;

    cout << "\n----- MST (Arbol de Expansion Minima) -----" << endl;

    for(int i=0; i<edgeCount; i++) 
	{
        int u= edges[i][0];
        int v= edges[i][1];
        int w= edges[i][2];

        //Si unirlos no causa ciclo, pertenece al MST.
        if(unionUF(u, v)) 
		{
            cout << u << " - " << v << " (peso = " << w << ")" << endl;
            costoTotal+= w;
        }
    }

    cout << "\nCosto total del MST: " << costoTotal << endl;
};

