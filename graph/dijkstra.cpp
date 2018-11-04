#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <functional>
#include <limits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

class Edge {
    public:
        int dstId;
        int weigth;

        Edge( int _dstId, int _weigth ) : weigth( _weigth ), dstId( _dstId ) {}

        bool operator==( const Edge & obj ) const {
            if( obj.dstId == this->dstId ) {
                return true;
            }
            return false;
        }
};

namespace std {
    template<>
    struct hash< Edge > {
        size_t
        operator()( const Edge & obj ) const {
            return std::hash<int>()( obj.dstId );
        }
    };
}

class Vertex {
    public:
        int id;
        std::unordered_set< Edge > edges;

        Vertex() {}
        Vertex( int _id ) : id( _id )  {}

        void addDirectedEdge( Edge && edge ) {
            edges.insert( edge );
        }

        void printVertex() const {
            std::cout << "Adjacency list of vertex id(" << id << "): head ";
            for( auto & edge : edges ) {
                std::cout << "-> " << "[id(" << edge.dstId << "), w("
                          << edge.weigth << ")] ";
            }
            std::cout << std::endl;
        }
};

class Graph {
    public:
        std::unordered_map< int, Vertex > graph;

        Graph() {}
        void addUndirectedEdge( int id1, int id2, int weigth ) {
            assert( id1 != id2 );

            Vertex & v1 = graph[ id1 ];
            Vertex & v2 = graph[ id2 ];

            // Populate the ids in case it's just been created.
            v1.id = id1;
            v2.id = id2;

            v1.addDirectedEdge( Edge( id2, weigth ) );
            v2.addDirectedEdge( Edge( id1, weigth ) );
        }

        std::pair< std::vector< int >, std::vector< int > >
        shortestPath( int fromId, int toId ) const {
            if( graph.find( fromId ) == graph.end() ||
                graph.find( toId ) == graph.end() ) {
                return std::make_pair( std::vector< int >(),
                                       std::vector< int >() );
            }

            // Creates the distance and path maps.
            std::unordered_map< int, int > distanceMap;
            std::unordered_map< int, int > pathMap;

            // Initialize the distance and path map.
            for( const auto & it : graph ) {
                int id = it.second.id;
                distanceMap[ id ] = std::numeric_limits<int>::max();
                pathMap[ id ] = id;
            }

            // Create the priority queue and initialize it.
            typedef std::pair<int, int> pi;
            std::priority_queue< pi,
                                 std::vector< pi >,
                                 std::greater< pi > > pq;
            // Set the fromId to distance equal 0.
            pq.push( std::make_pair( 0, fromId ) );
            distanceMap[ fromId ] = 0;
            pathMap[ fromId ] = fromId;

            // Stop when every single vertex has been processed.
            // [TODO] Stop when we have found the shortest path from A to B.
            while( !pq.empty() ) {
                int currentId = pq.top().second;
                pq.pop();
                int currentDistance = distanceMap[ currentId ];

                // Compute the distance for each vertex.
                Vertex v = graph.at( currentId );
                for( const auto & edge : v.edges ) {
                    int adjId = edge.dstId;
                    int adjWeigth = edge.weigth;
                    int adjDistance = distanceMap[ adjId ];

                    int adjProposedDistance = currentDistance + adjWeigth;

                    // If there's a shortest path to adjId through u.
                    if( adjProposedDistance < adjDistance ) {
                        // Update the adj distance and path maps,  and add the new
                        // distance to the priority queue.
                        distanceMap[ adjId ] = adjProposedDistance;
                        pathMap[ adjId ] = currentId;
                        pq.push( std::make_pair( adjProposedDistance, adjId ) );
                    }
                }
            }

            std::vector< int > path;
            std::vector< int > dist;
            int currentId = toId;
            int originId = toId;
            do {
                currentId = originId;
                path.push_back( currentId );
                dist.push_back( distanceMap[ currentId ] );

                originId = pathMap[ currentId ];
            } while( originId != currentId );

            return std::make_pair( path, dist );
        }

        void printPath( const std::pair< std::vector< int >,
                                         std::vector< int > > & pathPair ) const {
            const std::vector< int > & path = pathPair.first;
            const std::vector< int > & dist = pathPair.second;

            assert( path.size() == dist.size() );
            int size = path.size();

            std::cout << "Shortest path: head";
            for( int i = size - 1; i >= 0; --i ) {
                 std::cout << " -> " << "[id("<< path[ i ] << "), dist("
                           << dist[ i ] << ")]";
            }
            std::cout << std::endl;
        }

        void printGraph() const {
            std::cout << "Graph:" << std::endl;
            for( auto && it : graph ) {
                it.second.printVertex();
            }
        }
};

int main() {
    // Set a predefined seed, so we can predict what happens.
    std::srand( std::time( nullptr ) );
    const int maxWeigth = 50;

    Graph graph;
    graph.addUndirectedEdge( 0, 2, std::rand() % maxWeigth );
    graph.addUndirectedEdge( 1, 3, std::rand() % maxWeigth );
    graph.addUndirectedEdge( 2, 4, std::rand() % maxWeigth );
    graph.addUndirectedEdge( 3, 4, std::rand() % maxWeigth );
    graph.addUndirectedEdge( 3, 5, std::rand() % maxWeigth );
    graph.addUndirectedEdge( 4, 5, std::rand() % maxWeigth );
    graph.printGraph();
    graph.printPath( graph.shortestPath( 0, 5 ) );
    graph.printPath( graph.shortestPath( 1, 5 ) );
    graph.printPath( graph.shortestPath( 3, 5 ) );
    graph.printPath( graph.shortestPath( 5, 2 ) );

    std::cout << std::endl << std::endl;

    // Random graph =)
    int maxVertexes = 15;
    int minVertexes = 5;
    int numVertexes = ( std::rand() % ( maxVertexes - minVertexes ) ) + minVertexes;
    int maxEdgesPerVertex = numVertexes / 3;
    for( int i = 0; i < numVertexes; ++i ) {
        int v1 = i;
        int v2 = v1;
        while ( v1 == v2 ) {
            v2 = std::rand() % numVertexes;
        }
        graph.addUndirectedEdge( v1, v2, std::rand() % maxWeigth );
    }
    graph.printGraph();
    for( int i = 0; i < numVertexes; ++i ) {
        graph.printPath( graph.shortestPath( i, std::rand() % numVertexes ) );
    }
}
