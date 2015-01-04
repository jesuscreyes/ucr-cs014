using namespace std;

class Node;
class Edge;


class Edge{
    
    public:
        Node* start;
        Node* end;
        int weight;
        
        Edge(){
            start = NULL;
            end = NULL;
            weight = -1;
        }
        
};

class Node{
    
    public:
        string name;
        int cost;
        list<Edge> edges;
        
        Node(){
            name = "";
            cost = -1;
        }
};
