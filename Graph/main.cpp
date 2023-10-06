

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

//************************** Node *************************

class Node{
public:
    int data;
    Node* next;

    Node(int value, Node* pNext){ //constructor
        data = value;
        next = pNext;
    }
};


//************************** Graph ****************************
class Graph {
	public:
		//add the node with neighborId as the neighbor of nodeId
		void addNeighbor(int nodeId, int neighborId);

		//reads the edge list from file and creates the adjacency list data structure
		void loadGraph(string edgeListFileName);

		//writes the adjacency list into the file
		void dumpGraph(string adjListFileName);

		//Prints number of nodes, number of edges, and maximum degree on terminal
		void printGraphInfo();

		//returns the number of neighbor (degree) of a node
		int getNumNeighbors(int nodeId);
        //get the size of array

		//returns the number of nodes in the graph
		int getNumVertices();

	private:
		vector<Node*> vertices;

};

void Graph::loadGraph(string edgeListFileName) {
    ifstream edgeFile;
    edgeFile.open(edgeListFileName);
    assert(edgeFile.fail() == false);

    int vertex;
    int neighbor;

    while(!edgeFile.eof()){
        edgeFile >> vertex;
        edgeFile >> neighbor;

        if (vertex >= neighbor){ //checking if vertex is bigger than neighbor and vertices
            while(vertex >= vertices.size()){
                vertices.push_back(NULL);
            }
        }
        else{
            while(neighbor >= vertices.size()){
                vertices.push_back(NULL);
            }
        }

        if (vertices.at(vertex) == NULL){
            vertices.at(vertex) = new Node(neighbor, NULL);
        }
        else{
            addNeighbor(vertex, neighbor);
        }


        if (vertices.at(neighbor) == NULL){
            vertices.at(neighbor) = new Node(vertex, NULL);
        }

        else{
            addNeighbor(neighbor, vertex);
        }

    }

    edgeFile.close();

}

void Graph::addNeighbor(int nodeId, int neighborId){
    Node* neighborNode = new Node (neighborId, NULL);
    Node* pHead = vertices.at(nodeId); //assigning pHead to the head of the main Node

    if (pHead->data == neighborId){ //in case there is only one node
        return;
    }
    if (pHead->data > neighborId){
        neighborNode->next = pHead;
        vertices.at(nodeId) = neighborNode;
    }

    else {
        while (pHead != NULL) {
            if (pHead->data == neighborId){ //checking if it's in the middle of the list == do nothing
                return;
            }
            if (pHead->next == NULL){
                pHead->next = neighborNode; //adding to the back of the list
            }
            else if(pHead->data < neighborId && pHead->next->data > neighborId){ //inserting somewhere in the middle of the list
                neighborNode->next = pHead->next;
                pHead->next = neighborNode;
            }

            pHead = pHead->next;
        }




        //if neighbor is in the linked list, just return
        //else, create a new node and add to the end of the linked list

    }
}

void Graph::dumpGraph(string adjListFileName){
    ofstream myOutStream;
    myOutStream.open(adjListFileName);
    assert(myOutStream.fail() == false);

    //myOutStream << "Hello world!" << endl ;

    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices.at(i) != NULL) {
            myOutStream << i << ":";
            Node *pHead = vertices.at(i);
            while (pHead != NULL) {
                myOutStream << " " << pHead->data ;
                pHead = pHead->next;
            }
            myOutStream << endl;
        }
    }

    myOutStream.close();

}

void Graph::printGraphInfo(){
    cout << "Number of nodes: " << getNumVertices() << endl;
    int degrees = 0;
    int numEdges = 0;

    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices.at(i) != NULL) {
            int edgesCounter = getNumNeighbors(i);
            numEdges += edgesCounter;
            if (edgesCounter > degrees){
                degrees = edgesCounter;
            }
        }
    }
    cout << "Number of edges: " << numEdges/2 << endl;
    cout << "Maximum degree: " << degrees << endl;
}

int Graph::getNumNeighbors(int nodeId){
    Node* pHead = vertices.at(nodeId);
    int counter = 0;
    while(pHead != NULL){
        counter++;
        pHead = pHead->next;
    }

    return counter;
}

int Graph::getNumVertices(){

    int counter = 0;
    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices.at(i) != NULL){
            counter++;
        }
    }
    return counter;

}

void run(string edgeListFileName, string adjListFileName) {
    Graph* graph = new Graph;
    graph->loadGraph(edgeListFileName);
    graph->printGraphInfo();
    graph->dumpGraph(adjListFileName);


}

//*****************************************************************************


int main() {
	//Change the filenames according to your local path.
    string edgeListFileName("toy.txt");
    string adjListFileName("toy2.txt");
	run(edgeListFileName, adjListFileName);
    return 0;
}
