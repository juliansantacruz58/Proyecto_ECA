/* Universidad Autónoma de Aguascalientes
   Centro de Ciencias Básicas
   Ciencias de la Computación
   Ing. en Computación Inteligente
   Semestre: III
   Materia: Estructuras Computacionales Avanzadas.
   Docente: Miguel Ángel Meza de Luna
   Alumno: José Julián Badajoz Santacruz.
   Algoritmo 1: Kosaraju. */
   
#include <iostream>
#include <locale.h>
#include <fstream>

using namespace std;

//Definición de tamaños globales.
#define MAXN 100
#define MAXE 500

//Estructuras de lista de adyacencia.
//head es el primer borde del nodo,
//next es el que sigue,
//to dice hacia quién va la arista.
int head[MAXN], to[MAXE], nextEdge[MAXE], edgeCount= 0;

//Grafo transpuesto.
int headT[MAXN], toT[MAXE], nextEdgeT[MAXE], edgeCountT= 0;

//Visitados para los DFS.
bool visitado[MAXN];

//Pila.
int pila[MAXN];
int top= -1;

//Prototipo de funciones:
void agregarArista(int u, int v);
void agregarAristaTranspuesta(int u, int v);
void dfs_orden(int nodo);
void dfs_componente(int nodo);
void kosaraju(int n);

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	
    int n, m;

    cout << "-------- KOSARAJU --------" << endl;
    cout << "\n¿Cuántos nodos tiene el grafo?" << endl;
    cin >> n;

    cout << "\n¿Cuántas aristas dirigidas tiene? " << endl;
    cin >> m;

    //Inicialización de listas con -1.
    for(int i=0; i<n; i++)
	{
		head[i]= -1;
	}
	 
    for(int i=0; i<n; i++)
	{
		headT[i]= -1;
	} 

    cout << "\nIntroduce las aristas en formato: u v" << endl;
    cout << "(Recuerda: esto significa una flecha de u -> v)" << endl << endl;

    for(int i=0; i<m; i++) 
	{
        int u, v;
        cout << "\nArista " << i+1 << ": ";
        cin >> u >> v;

        agregarArista(u, v);
        agregarAristaTranspuesta(v, u); 
    }

    kosaraju(n);

    return 0;
};

//Adición de aristas.
void agregarArista(int u, int v) 
{
	//La arista se dirigie hacia v.
    to[edgeCount]= v;   
    //El siguiente de la arista, era el que estaba primero.
    nextEdge[edgeCount]= head[u];  
    //Ahora es la primer arista del nodo u.
    head[u]= edgeCount;  
    edgeCount++;
};

//Adición de arista transpuesta.
void agregarAristaTranspuesta(int u, int v) 
{
    toT[edgeCountT]= v;
    nextEdgeT[edgeCountT]= headT[u];
    headT[u]= edgeCountT;
    edgeCountT++;
};

//Primer DFS para el ordenamiento.
void dfs_orden(int nodo) 
{
    visitado[nodo]= true;

    //Recorrrido de todas las aristas fuera del nodo actual.
	for(int e= head[nodo]; e!= -1; e= nextEdge[e]) 
	{
        int vecino= to[e];
        
		if(!visitado[vecino]) 
		{
            dfs_orden(vecino);
        }
    }

    //Ahora se almacena en la pila.
    pila[++top]= nodo;
};

//DFS sobre grafo transpuesto para hallar componentes fuertementa conexas.
void dfs_componente(int nodo) 
{
    visitado[nodo]= true;
    
    //Se muestra que el nodo si pertenezca a esos componentes.
    cout << nodo << " ";  

    for(int e= headT[nodo]; e!= -1; e= nextEdgeT[e]) 
	{
        int vecino= toT[e];
        
		if(!visitado[vecino]) 
		{
            dfs_componente(vecino);
        }
    }
};

//Algoritmo Korasaju.
void kosaraju(int n) 
{
    //DFS normal para obtener el orden.
    for(int i=0; i<n; i++) 
	{
        if(!visitado[i]) 
		{
            dfs_orden(i);
        }
    }

    //Limpiar los nodos visitados para el inicio del segundo recorrido.
    for(int i= 0; i<n; i++)
    {
    	visitado[i] = false;
	}

    cout << "\n----- Componentes Fuertemente Conexas (SCC) -----" << endl;

    //Obtener nodos de la pila y realizar DFS en el transpuesto.
    while(top>=0) 
	{
        int nodo= pila[top--];

        if(!visitado[nodo]) 
		{
            dfs_componente(nodo);
            cout << endl;
        }
    }
};
