// graph.cpp 
// functions for mlgc
// by frg
#include <iostream>
#include <string>
#include <vector>
#include <deque>
using namespace std;;
//#include <fstream> //pour lire les fichiers

class Node{
    public: 
        Node(string alabel = ""){label = alabel;visited = false;} 
        ~Node(){}
        void setLabel(string alabel) { this->label= alabel; } 
        string getLabel() const { return label; }           // note: const after function declaration allows makes the output a const object
        void setVisit(bool whateva) {this->visited= whateva;}
        bool isVisited() {return this->visited;}
        vector<Node*> getNeighs() const {return theNeighs;}
        void add2Neighs(Node* aNode);
        void add2Neighs(vector<Node*> & someNeighs);

    private: 
        string label;
        bool visited;
        double weight;
        vector<Node*> theNeighs;
};

class Graph{
    public:
        Graph(string gname = ""){this->graphName = gname;};
        ~Graph();
        void setName(string someName){this->graphName = someName;}
        string getName() const {return this->graphName;}

        void addNode(Node* aNode);
        void setAllVisit(bool visit);
        bool isNodeInGraph(Node *aNode);
        vector<Node*> getAllNodes(){return allNodes;}
        vector<Node*> BFS();
    private:
        int nEdges;
        int nNodes;
        string graphName;
        Node* Node0;
        vector<Node*> allNodes;
};

void Node::add2Neighs(vector<Node*> &someNeighs)
{
    for (int i=0;i<someNeighs.size();i++)
        this->add2Neighs(someNeighs[i] );
}

void Node::add2Neighs(Node* aNode)
{
    bool add = true;
    for (int i=0;i<this->theNeighs.size();i++)
    {
        if (aNode->label == this->theNeighs[i]->label)
            add = false;
    }
    if (add) {
        this->theNeighs.push_back(aNode);
        cout << "add2Neighs,smt"<<endl;}
    else
        cout<<" neighbour '"<< aNode->getLabel()<<"' already inserted"<< endl;
}

bool Graph::isNodeInGraph(Node* aNode){
    bool exists = false;
    for (int i=0;i<this->allNodes.size();i++)
    {
        if (aNode->getLabel() == allNodes[i]->getLabel())
            exists = true;
    }
        return exists;
}

void Graph::addNode(Node* aNode){
    bool exists = isNodeInGraph(aNode);
    // add Node
    if (!exists)
    {
        if (this->allNodes.size() == 0)
            Node0 = aNode;
        this->allNodes.push_back(aNode);  
        this->nNodes +=1;
    }
    // add all Neighbours 
    for (int i=0;i<aNode->getNeighs().size();i++)
    {
        exists = false;
        exists = (this->isNodeInGraph(aNode->getNeighs()[i]));
        if (!exists)
            this->allNodes.push_back(aNode->getNeighs()[i]);  
            this->nNodes +=1;
            this->nEdges +=1;
    }
}

void Graph::setAllVisit(bool visit){
    for (int i=0;i<this->allNodes.size();i++)
    {
        (this->allNodes[i])->setVisit(visit);
    }
}

vector<Node*> Graph::BFS(){
    Node* currentN = NULL;
    Node* aNode = NULL; 
    deque<Node*> Queue;
    vector<Node*> allBFSorted;
    // initialize
    this->setAllVisit(false);
    Queue.push_back(this->Node0);
    while (!Queue.empty())// && (current != NULL))?
    {
        currentN = Queue.front();
        allBFSorted.push_back(currentN);
        Queue.pop_front();
        for (int i=0;i<currentN->getNeighs().size();i++)
        {
            if ( !( currentN->getNeighs()[i]->isVisited() ) )
            {
                Queue.push_back(currentN->getNeighs()[i]); 
                currentN->getNeighs()[i]->setVisit(true);
            }             
        }   
    }
    return allBFSorted;
}

//////////////////////////////////////////////////
// external fns
//////////////////////////////////////////////////
ostream& operator << (std::ostream & out, const Node& aNode){
    int m = aNode.getNeighs().size();
    out<< "node '"<< aNode.getLabel()<<"'; ";
    out<< m<<" neighs: ";
    for (int i=0;i<m;i++)
    {
        out<<"'"<<aNode.getNeighs()[i]->getLabel()<<"'";
        if (i<m-1) 
            out<<",";
    }
    out<<".";
    return out;
}

ostream& operator << (std::ostream & out,Graph & aGraph){
    int n= aGraph.getAllNodes().size();
    out << " Graph: ";
    out << " Nodes = "<<n<<endl;
    for (int i=0;i<n;i++)
    {
        out << (*aGraph.getAllNodes()[i]);
        if (i<n-1) 
            out<<"|";
    }
    out<<endl;
    return out;
}




