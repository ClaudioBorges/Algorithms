// Union-find algorithm using union by rank and path compression.

class Edge {
public:
    // Edges in a graph connecting two vertices pointed by src and dst.
    int src;
    int dst;
};

class Graph {
public:
    int V; // Number of vertices.
    int E; // Number of edges.

    // Represent the graph as an array of edges.
    Edge * edge;

    Graph( int _V, int _E ) : V( _V ),
                              E( _E ),
                              edge( new Edge[ _E ] ) {}

    ~Graph() {
        delete edge;
        edge = nullptr;
    }
};

struct Subset {
    int parent;
    int rank;
};

int find( :w

int main() {
    int V = 3, E = 5;
    Graph * graph = new Graph( V, E );


    delete graph;
    graph = nullptr;

    return 0;
}
