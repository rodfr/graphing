// main.cpp
// by frg
#include "graph.cpp"

//////////////////////////////////////////////////
// launch main prog
//////////////////////////////////////////////////

//int main(int argc, char* argv[])
int main()
{
  cout<< "debut main"<<endl;

  Graph* myGraph = new Graph();

  Node a;
  cout <<a<< endl;
  a.setLabel("a");
  Node b("b");
  Node c("c");
  Node d("d");
  Node e("e");

  vector<Node*> someVector;

  someVector.push_back(&b);
  someVector.push_back(&c);
  someVector.push_back(&d);

  a.add2Neighs(someVector );
  c.add2Neighs(&d);
  
  cout<< a <<endl;
  cout<< b <<endl;

  myGraph->addNode(&a); 
  myGraph->addNode(&b); 
  myGraph->addNode(&c); 
  myGraph->addNode(&d); 
  myGraph->addNode(&e);

  cout<<"\n this is the new graph: "<< (*myGraph)<<endl;

  vector<Node*> sortedNodes = myGraph->BFS();

  for (vector<Node*>::iterator it =sortedNodes.begin();it!=sortedNodes.end();it++)
  {
    cout<< (*it)->getLabel()<<" | ";
  } 

  myGraph->genDotFile();

  cout<< "outtahere"<<endl;
}
