#include<string>
#include<iostream>
#include<string>
#include"Slist.h"
using namespace std;
#ifndef GRAPH_H
#define GRAPH_H

template<class T>
class Edge
{
public:
	double distance, price;

private:

};
 
template<class T>
class Graph
{
public:

	Graph(int numVertex)                                    //Constructor Of Graph Class
	{            
		numVertices = numVertex;                            //setting Number of vertices

		adj_matrix = new Edge<double> *[numVertex];
		for (int i = 0;i < numVertex;i++)                   //Declaring 2D-Array of Adjacency Matrix
		{
			adj_matrix[i] = new Edge<double>[numVertex];
		}
		for (int i = 0;i < numVertex;i++)
		{
			for (int j = 0;j < numVertex;j++)
			{
				adj_matrix[i][j].distance = 0;                       //Setting All Paths equal to zero ( means no path Exist )
				adj_matrix[i][j].price = 0;                          //Setting All Price equal to zero ( means no path Exist )
			}
		}
		L = new List<string> * [numVertex*numVertex];      //Declaring Array of Singly Linked List to store Shortest Path After finding By Dijkstra Algorithm ( Later use for finding Shortest Path and Distance in Order 1 )
	    for (int i = 0; i < numVertex*numVertex; i++)
		{
			L[i] = new List<string> ();
		}
	}
	template <class T>
	void Dijkstra_algo_distance(string source, string destination, Node<T> * temp, int size, int index)
	{
		int x = 0, y = 0;
		Node<string> * temp2 = temp;
		Node<string> * temp3 = new Node<string>(source);
		Node<string> * temp9 = temp3;
		while (temp2->getData() != source)                 //Finding Source Co-ordinate/Vertex Number 
		{
			temp2 = temp2->GetNext();
			x++;
		}
		temp2 = temp;
		while (temp2->getData() != destination)            //Finding Destination Co-ordinate/Vertex Number 
		{
			temp2 = temp2->GetNext();
			y++;
		}
		double *distance = new double[size];               //Declaring Array to Store Distance from Source to Every Vertex
		bool *visited = new bool[size];                    //Declaring Array to Check that a Vertex is visited or not
		for (int i = 0; i < size; i++)
		{
			visited[i] = false;                            //Setting All Vertex Non-visited
			distance[i] = 200000000;                       //Setting All Nodes at infinity
		}
		cout << source << "->";                            
		distance[x] = 0;                                   //Set source Index value of distance storing Array equal to Zero(Because distance from a source to itself is Zero)
		for (int i = 0; i < size - 1; i++)
		{
			int min = -1;
			for (int i = 0; i < size; i++)                 //Finding min Vertex in Distance storing array
			{
				if (!visited[i] && (min == -1 || distance[i] < distance[min]))    //Checking That Vertex is visited or not
				{
					min = i;
				}
			}
			visited[min] = true;                           //Mark Min Vertex visited
			for (int j = 0; j < size; j++)
			{
				if (adj_matrix[min][j].distance != 0 && !visited[j])             //Checking Path In Adjacency Matrix (with Respect to Distance) Exist or not and Vertex Must not be Visited
				{
					double a = distance[min] + adj_matrix[min][j].distance;      // Distance from Source + Weight of New edge
					if (a < distance[j])
					{
						if (j == y)                         
						{
							Node<T> * temp5 =  temp;
							int xyz = 0;
							while (xyz != min)                      
							{
								temp5 = temp5->GetNext();
								xyz++;
							}
							if (xyz != x)
							{
								Node<T> * temp6 = new Node<T>(temp5->getData());  //Making Node of New city where we go Next
								temp3->SetNext(temp6);                            //Storing name of City where we go Next
								temp3 = temp3->GetNext();                         //Storing Path for Later use
								cout << temp5->getData() << "->";                 //Getting name of City where we go Next
							}
						}
						distance[j] = a;
					}
				}
			}
		}
		Node<T> * temp8 = new Node<T>(destination);
		temp3->SetNext(temp8);
		temp3 = temp3->GetNext();
		temp3->Setdistance(distance[y]);                //Here we Set Our Total Distance From source to Destination At Node For Later Use(For Order 1 we got Distance from Here)
		L[index]->Insert(temp9);                        //Here we insert Our Total Path From source to Destination In Singly Linked List At Specific Index For Later Use(For Order 1 we got Path from Here)
		cout << destination;
		cout << setw(20) << distance[y] << "    ";
		cout << endl;
	}

	template <class T>
	void Dijkstra_algo_Price(string source, string destination, Node<T> * temp, int size, int index)
	{
		int x = 0, y = 0;
		Node<string> * temp2 = temp;
		while (temp2->getData() != source)                 //Finding Source Co-ordinate/Vertex Number 
		{
			temp2 = temp2->GetNext();
			x++;
		}
		temp2 = temp;
		while (temp2->getData() != destination)            //Finding destination Co-ordinate/Vertex Number 
		{
			temp2 = temp2->GetNext();
			y++;
		}
		double *distance = new double[size];               //Declaring Array to Store Distance from Source to Every Vertex
		bool *visited = new bool[size];                    //Declaring Array to Check that a Vertex is visited or not
		for (int i = 0; i < size; i++)
		{
			visited[i] = false;                            //Setting All Vertex Non-visited
			distance[i] = 200000000;                       //Setting All Nodes at infinity
		}
		cout << source << "->";
		distance[x] = 0;                                   //Set source Index value of distance storing Array equal to Zero(Because distance from a source to itself is Zero)
		for (int i = 0; i < size - 1; i++)
		{
			int min = -1;
			for (int i = 0; i < size; i++)                 //Finding min vertex in Distance storing array
			{
				if (!visited[i] && (min == -1 || distance[i] < distance[min]))    //Checking That Vertex is visited or not
				{
					min = i;
				}
			}
			visited[min] = true;                            //Mark Min Vertex visited
			for (int j = 0; j < size; j++)
			{
				if (adj_matrix[min][j].price != 0 && !visited[j])             //checking Path In Adjacency Matrix(with Respect ot price) Exist or not and Vertex Must not be Visited
				{
					double a = distance[min] + adj_matrix[min][j].price;      // Distance from Source + Weight of New edge
					if (a < distance[j])
					{
						if (j == y)
						{
							Node<T> * temp3 = temp;
							int xyz = 0;
							while (xyz != min)
							{
								temp3 = temp3->GetNext();
								xyz++;
							}
							if (xyz != x)
							{
								cout << temp3->getData() << "->";             //Getting name of City where we go Next
							}
						}
						distance[j] = a;
					}
				}
			}
		}
		cout << destination;                            //Displaying Destination
        cout << setw(20) << distance[y] << "    ";           //Displaying distance
		cout << endl;
	}

	Node<string>* getpathorder_1(int index)                  //Getting Path From Singly Linked List at Specific Index in Order 1
	{
		return L[index]->getfirst();
	}

	template<class T>
	void minimum_hops(string source, Node<T> * temp, int size)
	{
		int n = 0, u = 0, m = 0, v = 0;
		Node<T> * temp2 = temp;
		while (temp2->getData() != source)                //Finding Source Co-ordinate/Vertex Number  
		{
			temp2 = temp2->GetNext();
			n++;
		}
		bool * visited = new bool[size];                  //Declaring An Array to Check that Vertex is visited or not
		for (int i = 0; i < size; i++)
		{
			visited[i] = false;                           //Setting all Vertex Not-visited
		}
		visited[n] = true;                                //Marking Source is Visited
		for (int i = 0; i < size; i++)
		{
			double dist = 0;
			u = i; 
			if (!visited[i] && adj_matrix[n][i].distance != 0)              //If Direct Path Is Available Then
			{
				dist = 0;
				visited[i] = true;                         //if Direct Path Exist Then Mark It visited
				int x = 0;
				cout << temp2->getData() << "->";
				Node<T> * temp3 = temp;
				while (x != i)
				{
					temp3 = temp3->GetNext();
					x++;
				}
				dist = dist + adj_matrix[n][x].distance;                    //Weight of that edge or Distance between these cities
				cout << temp3->getData() << setw(10) << dist << endl;
			}
			else                      //If Direct Path Is Not Available Then
			{
				dist = 0;
                for (int j = 0; j < size; j++)
				{
					m = n + j;               //Going to next City 
					if (!visited[u] && m < size && adj_matrix[n + j][u].distance != 0 && adj_matrix[n][m].distance != 0)      //Check that Vertex is visited or not and Next City must not be out of Range of total Cities
					{
						visited[u] = true;                                         //If we got path then Mark that vertex is visited
						int x = 0;
						cout << temp2->getData() << "->";
						dist = dist + adj_matrix[n][m].distance;                   //Weight of that edge or Distance between these cities
						Node<T> * temp3 = temp;
						while (x != m)
						{
							temp3 = temp3->GetNext();                              //Getting name of City where we go Next
							x++;
						}
						cout << temp3->getData() << "->";
						temp3 = temp;
						x = 0;
						while (x != u)
						{
							temp3 = temp3->GetNext();                              //Getting name of Destination 
							x++;
						}
						dist = dist + adj_matrix[m][u].distance;                   // Distance from source + Weight of that edge or Distance between these cities
						cout << temp3->getData() << setw(10) << dist << endl;
					}
					else if (m >= size && adj_matrix[n][m - size].distance != 0)       //If Next City Count Exceed Total Cities and Path Exist
					{
						if (!visited[u] && adj_matrix[m - size][u].distance != 0 && adj_matrix[n][m - size].distance != 0)     //if Vertex is not visited and we got path
						{
							dist = 0;
							visited[u] = true;                            //Mark Vertex visited
							int x = 0;
							cout << temp2->getData() << "->";
							Node<T> * temp3 = temp;
							while (x != m - size)
							{
								temp3 = temp3->GetNext();
								x++;
							}
							dist = dist + adj_matrix[n][m-size].distance;          //Weight of that edge or Distance between these cities
							cout << temp3->getData() << "->";
							temp3 = temp;
							x = 0;
							while (x != u)
							{
								temp3 = temp3->GetNext();
								x++;
							}
							dist = dist + adj_matrix[m-size][u].distance;          // Distance from source + Weight of that edge or Distance between these cities
							cout << temp3->getData() << setw(10) << dist << endl;
						}

					}
				}
			}
		}

	}

	template<class T>
	void prim(int size, Node<T> * temp)
	{

		string * arr = new string[size];
		Node<T> * temp2 = new Node<T>();
		temp2 = temp;
		for (int i = 0; i < size; i++)
		{
			arr[i] = temp2->getData();
			temp2 = temp2->GetNext();
		}
		bool * visited = new bool[size];
		for (int i = 0; i < size; i++)
		{
			visited[i] = false;
		}
		int i = 0, j = 0, k = 0, l = 0, m = 0;
		double min = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (m == 1 && adj_matrix[i][j].distance < min && adj_matrix[i][j].distance != 0)
				{
					k = i;
					l = j;
					min = adj_matrix[i][j].distance;
				}
				else if (m == 0 && adj_matrix[i][j].distance != 0)
				{
					m = 1;
					k = i;
					l = j;
					min = adj_matrix[i][j].distance;
				}
			}
		}
		visited[k] = true;
		visited[l] = true;
		int m1 = 0, a = 0, b = 0, k1 = 0;
		double min1 = 0;
		cout << "Edges Include in minimum spanning tree" << endl;
		cout << endl;
		cout << arr[k] << "<--->" << adj_matrix[k][l].distance << "<--->" << arr[l] << endl;
		while (k1 < size - 2)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (visited[i] && !visited[j] && adj_matrix[i][j].distance != 0)
					{
						if (m1 == 0)
						{
							a = i;
							b = j;
							m1 = 1;
							min1 = adj_matrix[i][j].distance;
						}
						else if (m1 == 1 && adj_matrix[i][j].distance < min1)
						{
							a = i;
							b = j;
							min1 = adj_matrix[i][j].distance;
						}
					}
				}
			}
			visited[b] = true;
			k1++;
			m1 = 0;
			cout << arr[a] << "<--->" << adj_matrix[a][b].distance << "<--->" << arr[b] << endl;
		}
	}
	template<class T>
	void getgraph_distance(Node<T>* temp)                                           //Displaying x-axis Co-ordinated (cities) with Numbering
	{
		Node<T>* temp2 = temp;
		for (int i = 0;i < numVertices;i++)
		{
			cout << temp2->getData() << endl;
			cout << "(" << i << ")" << setw(10);
			for (int j = 0;j < numVertices;j++)
			{
				cout << adj_matrix[i][j].distance << "           ";             //Displaying Adjacency Matrix with respect to Distance
			}
			cout << endl;
			temp2 = temp2->GetNext();
		}
	} 
	template<class T>
	void getgraph_Price(Node<T>* temp)                                          //Displaying x-axis Co-ordinated (cities) with Numbering
	{
		Node<T>* temp2 = temp;
		for (int i = 0;i < numVertices;i++)
		{
			cout << temp2->getData() << endl;
			cout << "(" << i << ")" << setw(10);
			for (int j = 0;j < numVertices;j++)
			{
				cout << adj_matrix[i][j].price << "           ";                 //Displaying Adjacency Matrix with respect to Price
			}
			cout << endl;
			temp2 = temp2->GetNext();
		}
	}
	void insertEdge(int frmVertex, int toVertex, double weight ,double Price)    //Inserting Weight and Price at appropriate Place
	{
		adj_matrix[frmVertex][toVertex].distance = weight;
		adj_matrix[toVertex][frmVertex].distance = weight;
		adj_matrix[frmVertex][toVertex].price = Price;
		adj_matrix[toVertex][frmVertex].price = Price;
	}
private:
	List<string> ** L;
	Edge<double> **adj_matrix;
	int numVertices;
};

#endif