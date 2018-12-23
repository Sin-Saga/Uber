#include<iostream>
#include<iomanip>
#include<fstream>
#include<queue>
#include<string>
#include"Slist.h"
#include"graph.h"
using namespace std;
class city                               //City Class
{
public:
	city()
	{
		vertex1 = "NULL";
		vertex2 = "NULL";
		weight = 0;
		price_per_passenger = 00;
	}
	string  getvertex1()
	{
		return vertex1;
	}
	string  getvertex2()
	{
		return vertex2;
	}
	int getweight()
	{
		return weight;
	}
	double getprice()
	{
		return price_per_passenger;
	}
	friend ostream& operator<<(ostream &off, city c);
	friend ifstream& operator>> (ifstream &iff, city &c);
private:
	string vertex1, vertex2;
	int weight;
	double price_per_passenger;
};
ostream& operator<<(ostream & out, city c)
{
	out << c.vertex1 << setw(20) << c.vertex2 << setw(10) << c.weight << setw(20) << c.price_per_passenger;
	return out;
}
ifstream& operator >> (ifstream &in, city & c)
{
	in >> c.vertex1 >> c.vertex2 >> c.weight >> c.price_per_passenger;
	return in;
}

class passenger                                        //Passenger Class
{
public:
	passenger()
	{
		ID = 0;
		source = "NULL";
		destination = "NULL"; 
		passenger_type1 = "NULL";
		passenger_type2 = "NULL";
	}
	string getpassenger_type1()
	{
		return passenger_type1;
	}
	string getpassenger_type2()
	{
		return passenger_type2;
	}
	string  getsource()
	{
		return source;
	}
	string  getdestination()
	{
		return destination;
	}
	int gettotal_passengers()
	{
		return total_passengers;
	}
	int getID()
	{
		return ID;
	}
	friend ostream& operator<<(ostream &out, passenger c);
	friend ifstream& operator>> (ifstream &in, passenger &c);
private:
	int ID, total_passengers;
	string source , destination , passenger_type1 , passenger_type2;
};
ostream& operator<<(ostream & out, passenger p)
{
	out << p.ID << setw(20) << p.source << setw(20) << p.destination << setw(20) << p.passenger_type1 << "  " << p.passenger_type2;
	return out;
}
ifstream& operator >> (ifstream &in, passenger & p)
{
	in >> p.ID >> p.source >> p.destination >> p.passenger_type1 >>p.passenger_type2;
	return in;
}

int main()                                                //Main
{
	int count1 = 0, count2 = 0, Total_cities = 0, start = 0, index = 0;
	ifstream in("city.txt");
	cout << endl << endl;
	cout << "---------------------------------------------------- Welcome to Uber Transport service---------------------------------------------------" << endl << endl;
	if (in.fail())                                              //checking file exist or not
	{
		cout << "File does not exist" << endl;
	}
	else if(in.is_open())
	{
		queue<city>* q = new queue<city>();
		List<string>*list = new List<string>();
		city C1;
		in >> Total_cities;
		while (!in.eof())                                  //Taking Input of Cities
		{
			in >> C1;
			q->push(C1);
			count2++;
		}
		city * C = new city[count2];
		for (int i = 0; i < count2; i++)
		{
			C[i] = q->front();
			q->pop();
		}
		while (count1 < count2)                            //Making Nodes of Cities
		{
			Node<string> * pnode = new Node<string>(C[count1].getvertex1());
			if (!list->search(C[count1].getvertex1()))
			{
				list->Insert(pnode);
			}
			Node<string> * pnode2 = new Node<string>(C[count1].getvertex2());
			if (!list->search(C[count1].getvertex2()))
			{
				list->Insert(pnode2);
			}
			count1++;
		}
		cout << endl << endl;
		Graph<int> * G = new Graph<int>(Total_cities);
		Node<string>*temp = list->getfirst();
		int x = 0;
		while (temp != NULL)                                 //Making both Graphs ([1] with respect to Distance, [2] with Respect to Price)
		{
			for (int i = 0; i < count2; i++)
			{
				if (temp->getData() == C[i].getvertex1())
				{
					int y = 0;
					Node<string> * temp2 = list->getfirst();
					while (temp2->getData() != C[i].getvertex2())
					{
						y++;
						temp2 = temp2->GetNext();
					}
					G->insertEdge(x, y, C[i].getweight(), C[i].getprice());				
				}
			}
			temp = temp->GetNext();
			x++;
		}
		cout << endl;
		cout << "----------------------------------------Welcome to Uber Car service----------------------------------------" << endl << endl;
		cout << "-----------------------------------------Cities Schedule-----------------------------------------" << endl << endl;
		cout << "starting" << setw(20) << "Destination" << setw(12) << "Distance" << setw(25) << "Price Per Passenger" << endl << endl;
		count1 = 0;
		while (count1 < count2)                               //Displaying Cities Data (starting, Destination, Distance, Price Per Passenger)
		{
			cout << C[count1];
			cout << endl;
			count1++;
		}
		cout << "-------------------------------------------Total Cities-------------------------------------------" << endl << endl;
		cout << Total_cities << endl << endl;                 // Total Number of cities
		cout << "-------------------------------------------cities names-------------------------------------------" << endl << endl;
		cout << setw(70) << "Our Uber Ride is only Accessable for these Cities" << endl << endl;
		list->print();                                        //Printing Nodes
		cout << endl << endl;
		cout << "-----------------------------Distance from One City to another City--------------------------------" << endl << endl;
		Node<string> * temp3 = list->getfirst();
		cout << setw(12);
		for (int i = 0; i < Total_cities; i++)                //Displaying y-axis co-ordinates with numbering
		{
			cout << "(" << i << ")" << setw(10);
		}
		cout << endl;
		cout << setw(15);
		for (int i = 0; i < Total_cities; i++)
		{
			cout << temp3->getData() << "    ";
			temp3 = temp3->GetNext();
		}
		cout << endl << endl;
		G->getgraph_distance(list->getfirst());                //Displaying Graph with respect to Distances
		cout << endl << endl << endl;
		cout << "-------------------------------Shortest paths from a City to every City------------------------------" << endl << endl << endl;
		Node<string>* temp4 = list->getfirst();
		Node<string>* temp5 = list->getfirst();
		cout << "Source->Destination" << setw(20) << "Distance" << endl;
		cout << endl;
		for (int i = 0; i < Total_cities; i++)                  //Applying Dijkstra_algo with Respect to Distance
		{
			for (int j = 0; j < Total_cities; j++)
			{
				G->Dijkstra_algo_distance(temp4->getData(), temp5->getData(), list->getfirst(), Total_cities, index);
				temp5 = temp5->GetNext();
				index = index + 1;
			}
			temp4 = temp4->GetNext();
			temp5 = list->getfirst();
			cout << endl;
		}
		cout << endl << endl;
		cout << "****************************************Minimum spanning Tree***************************************" << endl << endl;
		G->prim(Total_cities, list->getfirst());
		cout << endl << endl;
		cout << "----------------------------------------Minimum Number of Hops----------------------------------------" << endl << endl << endl;
		cout << setw(66) << "By considering Adjacency Matrix" << endl << endl << endl;
		cout << "Source->Destination" << setw(20) << "Distance" << endl << endl << endl;
		Node<string> * temp6 =  list->getfirst();
		for (int j = 0; j < Total_cities; j++)
		{
			G->minimum_hops(temp6->getData(), list->getfirst(), Total_cities);             //Getting Path by considering Minimum Number of Hops
			temp6 = temp6->GetNext();
			cout << endl;
		}
		cout << endl << endl;
		int total_passenger = 0, count3 = 0, count4 = 0;
		ifstream inn("passenger.txt");
		if (inn.fail())                                                       //checking passenger file exist or not
		{
			cout << "File does not exist" << endl;
		}
		else if(inn.is_open())
		{
			queue<passenger> * q1 = new queue<passenger>();
			queue<passenger> * q2 = new queue<passenger>();
			inn >> total_passenger;
			passenger p1;
			cout << "-----------------------------------------Passengers Schedule----------------------------------------" << endl << endl;
			cout << "ID" << setw(20) << "starting" << setw(20) << "Destination" << setw(25) << "Passenger Type" << endl << endl;
			while (!inn.eof())                             //Taking input
			{
				inn >> p1;
				cout << p1;
				if (p1.getpassenger_type1() == "premium" || p1.getpassenger_type1() == "Premium")
				{
					q1->push(p1);
				}
				else
				{
					q2->push(p1);
					count4++;
				}
				cout << endl;
			}
			cout << endl << endl;
			while (count3 < count4)
			{
				p1 = q2->front();
				q2->pop();
				q1->push(p1);
				count3++;
			}
			cout << "------------------------------------------Total Passengers------------------------------------------" << endl << endl;
			cout << total_passenger << endl << endl;
			cout << "-----------------------------------Allocating Ride to Our Passengers--------------------------------" << endl << endl;
			int * car_count = new int[Total_cities];                    //Declaring Array to take count of cities
			for (int i = 0; i < Total_cities; i++)
			{
				car_count[i] = 0;                                       //Setting All Index Value equal to Zero
			}
			int variable = 0;
			cout << "---------------------------------Allocating Ride to Premium Passengers------------------------------" << endl << endl;
			for (int i = 0; i < total_passenger; i++)
			{
				cout << endl;
				Node<string>* temp9 = list->getfirst();
				int source_coordinate = 0, Destination_coordinate = 0;
				p1 = q1->front();
				q1->pop();
				if ((p1.getpassenger_type1() == "Normal" || p1.getpassenger_type1() == "normal" ) && variable == 0)              //For Giving a double Space Difference Between (Premium And Normal) users
				{
					cout << "------------------------------Allocating Ride to Normal Passengers---------------------------" << endl << endl;
					variable = 1;
				}
				cout << "User ID" << setw(15) << "Source" << setw(20) << "Destination" << setw(20) << "User type" << endl;
				cout << endl;
				cout << p1 << "        " << endl << endl;                              //Displaying Passengers data including (User ID, Source, destination, User Type)
				while (temp9->getData() != p1.getsource())                             //Taking x-axis co-ordinate or Index
				{
					temp9 = temp9->GetNext();
					source_coordinate++;
				}
				temp9 = list->getfirst();
				while (temp9->getData() != p1.getdestination())                        //Taking y-axis co-ordinate or Index
				{
					temp9 = temp9->GetNext();
					Destination_coordinate++;
				}
				car_count[source_coordinate] = car_count[source_coordinate] + 1;       //Increasing Car_Count Index by 1
				if (car_count[source_coordinate] > 5)                                  //Checking Car_Count index value must not be greater then 5
				{
					cout << "Sorry Sir! Car is not available at this moment Please Try Later" << endl << endl << endl;               //Giving warning That No car is Available
				}
				else
				{
					cout << "Your Shortest Path is" << "  ==>            ";
					if (p1.getpassenger_type1() == "premium" || p1.getpassenger_type1() == "Premium")
					{
						int Index = 0;
						Index = (source_coordinate*Total_cities) + Destination_coordinate;                     //Getting Index Value
						Node<string>* temp10 = G->getpathorder_1(Index);                                       //Getting Shortest Path By Order 1 for Premium User
						Node<string>* value=list->getfirst();
						while (temp10 !=NULL)
						{
							cout << temp10->getData();
							value = temp10;
							temp10 = temp10->GetNext();
							if (temp10 != NULL)
							{
								cout << "-->";
							}
						}
						cout << endl;
						cout << "Distance= " << value->getdistance() << endl;
						cout<<"Price= Rs " << value->getdistance() * 15 << endl;                                    //Premium User cherged 15 rupees Per Km
					}
					else
					{
						int Index = 0;
						Index = (source_coordinate * Total_cities) + Destination_coordinate;       //Getting Index Value
						Node<string>* temp11 = G->getpathorder_1(Index);                           //Getting Shortest Path By Order 1 for Normal User
						Node<string>* value2 = list->getfirst();
						while (temp11 != NULL)
						{
							cout << temp11->getData();
							value2 = temp11;
							temp11 = temp11->GetNext();
							if (temp11 != NULL)
							{
								cout << "-->";
							}
						}
						cout << endl;						
						cout << "Distance= " << value2->getdistance() << endl;
						cout << "Price= Rs " << value2->getdistance() * 10 << endl;                                    //Normal User cherged 10 rupees Per Km
					}
					cout << endl << endl;
				}
			}
		}
		cout << "----------------------------------------Welcome to Uber Bus service----------------------------------------" << endl << endl;
		cout << setw(90) << "Our Price Per Passenger from One city to every city is given below" << endl << endl << endl;
		Node<string> * temp12 = list->getfirst();
		cout << setw(12);
		for (int i = 0; i < Total_cities; i++)                    //Displaying y-axis co-ordinates with numbering
		{
			cout << "(" << i << ")" << setw(10);
		}
		cout << endl;
		cout << setw(15);
		for (int i = 0; i < Total_cities; i++)
		{
			cout << temp12->getData() << "    ";
			temp12 = temp12->GetNext();
		}
		cout << endl << endl;
		G->getgraph_Price(list->getfirst());                      //Displaying Graph with respect to Price
		cout << endl << endl;
		cout << "------------------------Shortest paths from a city to every city with respect to price-----------------------" << endl << endl << endl;
		Node<string>* temp13 = list->getfirst();
		Node<string>* temp14 = list->getfirst();
		cout << "Source->Destination" << setw(20) << "Distance" << endl << endl;
		index = 0;
		for (int i = 0; i < Total_cities; i++)                    //Applying Dijkstra_algo with respect to Price
		{
			for (int j = 0; j < Total_cities; j++)
			{
				G->Dijkstra_algo_Price(temp13->getData(), temp14->getData(), list->getfirst(), Total_cities, index);
				temp14 = temp14->GetNext();
				index = index + 1;
			}
			temp13 = temp13->GetNext();
			temp14 = list->getfirst();
			cout << endl;
		}
		cout << endl << endl;
	}
	system("pause");
	return 0;
}