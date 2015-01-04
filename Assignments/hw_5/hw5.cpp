#include <iostream>
#include <list>
#include <fstream>
#include <math.h>
#include <queue>
#include "other.h"

using namespace std;

double infin = pow(2,61) - 1;

class Graph{
        
    public:
        list<Node*> nodes;
        Graph(const string &listFile);
};

Graph::Graph(const string &listFile){
    //String variable to be used to push dictionary words onto queue
    string line;
    ifstream myfile (listFile.c_str());
    if(myfile.is_open()){
        while(getline(myfile,line)){
            //Declare new edge
            //Set the start node, end node, and weight of edge accordingly
            string startName;
            startName.append(line,0,1);
            //cout << startName << endl;
            string endName;
            endName.append(line,5,1);
            //cout << endName << endl;
            string w;
            w.append(line,9,2);
            int currWeight = atoi(w.c_str());
            //cout << "Weight: " << currWeight << endl;
            //Up to this point, name of start node, end node, edge, and
            //value for weight is acquired
            ////
            //Check if Nodes in graph's list of nodes have the name of the
            //nodes that are given
            //Declare nodes and then declare edges that attach nodes
            Node* startNode = new Node();
            Node* endNode = new Node();
            if(nodes.empty()){
                //List of nodes for graph is empty
                //cout << "Line 44" << endl;
                startNode->name = startName;
                nodes.push_back(startNode);
                endNode->name = endName;
                nodes.push_back(endNode);
            }
            else{
                //List of nodes for graph is NOT empty
                //cout << "Line 54" << endl;
                //Iterate through list and see if the names of the nodes in
                //list match the strings acquired from input
                bool startExist = false;
                bool endExist = false;
                for(list<Node*>::iterator iterator = nodes.begin(), end = nodes.end(); iterator != end; ++iterator){
                    Node* tempNode = *iterator;
                    if(tempNode->name == startName){
                        //Start node is already in graph
                        startExist = true;
                        startNode = tempNode;
                    }
                    else if(tempNode->name == endName){
                        //End node is already in graph
                        endExist = true;
                        endNode = tempNode;
                    }
                }
                if(!startExist){
                    //Start node is not in graph
                    //creating new node and inserting into graph
                    startNode->name = startName;
                    nodes.push_back(startNode);
                }
                if(!endExist){
                    //End node is not in graph
                    //Creating new node and inserting it into graph
                    endNode->name = endName;
                    nodes.push_back(endNode);
                }
            }
            //cout << "Size of nodes: " << nodes.size() << endl;
            //cout << "StartNode: " << startNode->name << endl;
            //cout << "EndNode: " << endNode->name << endl;
            //Have created nodes up to this point.
            //Now I need to create the edges, and push them on the start nodes
            //list of edges
            Edge *newEdge = new Edge();
            newEdge->start = startNode;
            newEdge->end = endNode;
            newEdge->weight = currWeight;
            //cout << "New edges start node is: " << newEdge->start->name << endl;
            //cout << "New edges end node is: " << newEdge->end->name << endl;
            //cout << "New edges weight is: " << newEdge->weight << endl;
            //cout << "Node " << startNode->name << " pushing this back" << endl << endl;
            startNode->edges.push_back(*newEdge);
        }
        myfile.close();
    }
}

void dijkstras(Graph g, string s){
    //cout << endl << "DIJKSTRAS" << endl << endl;
    //Must get Node who's name matches string s
    Node* startNode = new Node();
    for(list<Node*>::iterator iterator = g.nodes.begin(), end = g.nodes.end(); iterator != end; ++iterator){
        Node* tempNode = *iterator;
        if(tempNode->name == s){
            //Start node is already in graph
            startNode = tempNode;
        }
    }
    if(startNode->name == ""){
        //Start node not found in graph
        cerr << "Error: Start node not in graph" << endl;
        return;
    }
    else{
        //Start node is found in graph.
        //Commence dijkstras algorithm
        //This sequence sets the costs of each Node to infinity or 0 accordingly
        for(list<Node*>::iterator iterator = g.nodes.begin(), end = g.nodes.end(); iterator != end; ++iterator){
            Node* tempNode = *iterator;
            if(tempNode != startNode){
                //Set cost of all nodes that aren't start node to INFINITY
                tempNode->cost = INFINITY;
                //INFINITY = 2147483647
                //cout << "Setting " << tempNode->name << "'s cost to infinity" << endl;
            }
            else{
                tempNode->cost = 0;
                //cout << "Setting " << tempNode->name << "'a cost to 0" << endl;
            }
        }
        list<Node*> Q;

//ALGORITHM FOR SORTING List!!!!!

        //Going to try popping off graph's node list in order
        while(!g.nodes.empty()){
            //while graph's node list is not empty
            Node* smallestCostNode = new Node();
            Node* tempNode = new Node();
            smallestCostNode->cost = INFINITY;
            for(list<Node*>::iterator iterator = g.nodes.begin(), end = g.nodes.end(); iterator != end; ++iterator){
                tempNode = *iterator;
                if(smallestCostNode->cost >= tempNode->cost){
                    smallestCostNode = tempNode;
                }
            }
            //cout << "Current smallestCostNode: " << smallestCostNode->name << endl;
            Q.push_back(smallestCostNode);
            g.nodes.remove(smallestCostNode);
            //cout << "Print Queue" << endl;
            //while(!Q.empty()){
                //cout << Q.top()->name << endl;
                //Q.pop();
            //}
        }
        //cout << "G.nodes.size(): " << g.nodes.size() << endl << endl;
        list<Node*> final;
        while(!Q.empty()){
            Node* current = Q.front();
            final.push_back(Q.front());
            //cout << "Current Node: " << current->name << endl;
            //cout << "Q's size: " << Q.size() << endl;
            Q.pop_front();
            //cout << "Q's size: " << Q.size() << endl;
            //cout << current->name << "'s size of edge list: " << current->edges.size() << endl;
            for(list<Edge>::iterator iterator = current->edges.begin(), end = current->edges.end(); iterator != end; ++iterator){
                Edge tempEdge = *iterator;
                bool containsEnd = false;
                list<Node*> tempQ = Q;
                //THIS SHOULD NOT BE BASED ON Q
                //IT SHOULD BE THE LIST OF EDGES FOR CURRENT NODEs
                while(!tempQ.empty()){
                    //cout << endl << "tempQ.top()->name: " << tempQ.front()->name << endl;
                    //cout << "tempEdge.start->name: " << tempEdge.start->name << endl;
                    //cout << "tempEdge.end->name: " << tempEdge.end->name << endl;
                    if(tempQ.front()->name == tempEdge.end->name){
                        //cout << "tempEdge.start->name: " << tempEdge.start->name << endl;
                        //cout << "tempEdge.end->name: " << tempEdge.end->name << endl;

                        containsEnd = true;
                        tempQ.pop_front();
                    }
                    else{
                        tempQ.pop_front();
                    }
                }
                //cout << "current Edge's start node: " << tempEdge.start->name << endl;
                //cout << "current Edge's end node: " << tempEdge.end->name << endl;
                if(tempEdge.start == current && containsEnd){
                    //cout << "Current edge's start node is same as current Node" << endl;
                    //cout << "And queue contains current edge's end node" << endl;
                    //cout << "Current cost: " << current->cost << endl;
                    //cout << "Current edge's weight: " << tempEdge.weight << endl;
                    int newCost = current->cost + tempEdge.weight;
                    if(newCost < tempEdge.end->cost){
                        tempEdge.end->cost = newCost;
                        //cout << tempEdge.end->name << "'s new cost is: " << newCost << endl;
                        //cout << "Q's size: " << Q.size() << endl << endl;
                    }
                }
            }
            //Finished going through edges
            //At this point, need to update list of unvisisted nodes
            list<Node*> tempQ = Q;
            while(!Q.empty()){
                Q.pop_front();
            }
            //cout << "Q size: " << Q.size() << endl;
            //cout << "tempQ size: " << tempQ.size() << endl;
            while(!tempQ.empty()){
                Node* tempNode = new Node();
                Node* smallestCostNode = *tempQ.begin();
                for(list<Node*>::iterator iterator = tempQ.begin(), end = tempQ.end(); iterator != end; ++iterator){
                    tempNode = *iterator;
                    //cout << tempNode->name << endl;
                    //cout << tempNode->cost << endl;
                    if(smallestCostNode->cost >= tempNode->cost){
                        smallestCostNode = tempNode;
                    }
                }
                //cout << endl << "smallestCostNode: " << smallestCostNode->name << endl;
                Q.push_back(smallestCostNode);
                tempQ.remove(smallestCostNode);
            }
        }
        //Now need to short final list by name
        //cout << "SORTING FINAL" << endl;
        //cout << "Front of final: " << final.front()->name << endl;
        list<Node*> sortedFinal;
        while(!final.empty()){
            Node* tempNode = new Node();
            Node* smallestLetterNode = *final.begin();
            for(list<Node*>::iterator iterator = final.begin(), end = final.end(); iterator != end; ++iterator){
                tempNode = *iterator;
                //cout << tempNode->name << endl;
                //cout << tempNode->cost << endl;
                if(smallestLetterNode->name >= tempNode->name){
                    smallestLetterNode = tempNode;
                }
            }
            //cout << endl << "smallestLetterNode: " << smallestLetterNode->name << endl;
            sortedFinal.push_back(smallestLetterNode);
            final.remove(smallestLetterNode);
        }
        string startNodeName = startNode->name;
        cout << endl;
        while(!sortedFinal.empty()){
            if(startNodeName != sortedFinal.front()->name){
                cout << startNodeName << " -> " << sortedFinal.front()->name << " = ";
                cout << sortedFinal.front()->cost << endl;
            }
            sortedFinal.pop_front();
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]){
    
    if(argc != 3){
        cout << "Error: Incorrect number of arguments" << endl;
        return 0;
    }
    
    Graph g (argv[1]);
    string startNodeName = argv[2];
    
    dijkstras(g, startNodeName);
    
    return 0;
}
