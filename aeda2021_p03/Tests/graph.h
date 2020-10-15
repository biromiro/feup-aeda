#include <iostream>
#include <vector>

using namespace std;

template <class N, class E> class Edge;

template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges;
    Node(N inf) {
        info = inf;
    }
};

template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }
};

template <class N, class E>
class Graph {
    vector< Node<N,E> *> nodes;
public:
    Graph();
    ~Graph();
    Graph & addNode(const N &inf);
    Graph & addEdge(const N &begin, const N &end, const E &val);
    Graph & removeEdge(const N &begin, const N &end);
    const E & edgeValue(const N &begin, const N &end);
    std::tuple<Node<N,E>*,Node<N,E>*> validEdgeConnection(const N &begin, const N &end);
    unsigned numEdges(void) const;
    unsigned numNodes(void) const;
    void print(std::ostream &os) const;
};


template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g);


// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }


// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    NodeDoesNotExist(N inf) {
        info = inf;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }

// exception EdgeAlreadyExists
template <class N>
class EdgeAlreadyExists
{
public:
    N destination, start;
    EdgeAlreadyExists(N begin, N dest) {
        destination = dest;
        start = begin;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeAlreadyExists<N> &edge)
{ out << "Edge already exists: " << edge.start << " , " << edge.destination; return out; }


// exception EdgeDoesNotExist
// exception EdgeAlreadyExists
template <class N>
class EdgeDoesNotExist
{
public:
    N destination, start;
    EdgeDoesNotExist(N begin, N dest) {
        destination = dest;
        start = begin;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeDoesNotExist<N> &edge)
{ out << "Edge does not exist: " << edge.start << " , " << edge.destination; return out; }


template <class N, class E>
Graph<N,E>::Graph() {
    std::vector<Node<N,E> *>() = nodes;
}

template <class N, class E>
Graph<N,E>::~Graph<N, E>() {
    std::vector<Node<N,E> *>().swap(nodes);
}

template <class N, class E>
unsigned Graph<N,E>::numNodes() const {
    return nodes.size();
}

template <class N, class E>
unsigned Graph<N,E>::numEdges() const {
    size_t numEdges = 0;
    for(const auto& elem: nodes){
        numEdges += elem->edges.size();
    }
    return numEdges;
}

template <class N, class E>
Graph<N,E>& Graph<N,E>::addNode(const N &inf) {
    for(const auto& elem: nodes){
        if(elem->info == inf)
            throw NodeAlreadyExists<N>(inf);
    }
    Node<N,E>* node = new Node<N,E>(inf);
    nodes.push_back(node);
    return (*this);
}
template <class N, class E>
std::tuple<Node<N,E>*,Node<N,E>*> Graph<N,E>::validEdgeConnection(const N &begin, const N &end) {
    bool beginFound = false, endFound = false;
    Node<N,E>* beginNode;
    Node<N,E>* endNode;
    for(const auto& elem: nodes){
        if(elem->info == begin) {
            beginFound = true;
            beginNode = elem;
        }
        if (elem->info == end) {
            endFound = true;
            endNode = elem;
        }
    }
    if(!beginFound){
        throw NodeDoesNotExist<N>(begin);
    }else if(!endFound){
        throw NodeDoesNotExist<N>(end);
    }

    return std::tuple<Node<N,E>*,Node<N,E>*>(beginNode,endNode);
}

template <class N, class E>
Graph<N,E>& Graph<N,E>::addEdge(const N &begin, const N &end, const E &val) {
    std::tuple<Node<N,E>*,Node<N,E>*> nodePointers = validEdgeConnection(begin,end);
    for (const auto &edge: std::get<0>(nodePointers)->edges) {
        if (edge.destination == std::get<1>(nodePointers)) {
            throw EdgeAlreadyExists<N>(begin, end);
        }
    }
    (std::get<0>(nodePointers)->edges).push_back(Edge<N,E>(std::get<1>(nodePointers),val));
    return (*this);
}

template <class N, class E>
const E &Graph<N,E>::edgeValue(const N &begin, const N &end) {
    std::tuple<Node<N,E>*,Node<N,E>*> nodePointers = validEdgeConnection(begin,end);
    for (const auto &edge: std::get<0>(nodePointers)->edges) {
        if (edge.destination == std::get<1>(nodePointers)) {
            return edge.value;
        }
    }
    throw EdgeDoesNotExist<N>(begin,end);
}

template<class N,class E>
Graph<N,E>& Graph<N,E>::removeEdge(const N &begin, const N &end) {
    std::tuple<Node<N,E>*,Node<N,E>*> nodePointers = validEdgeConnection(begin,end);
    for (auto it= std::get<0>(nodePointers)->edges.begin(); it <= std::get<0>(nodePointers)->edges.end(); it++) {
        if ((*it).destination == std::get<1>(nodePointers)) {
            (std::get<0>(nodePointers)->edges).erase(it);
            return (*this);
        }
    }
    throw EdgeDoesNotExist<N>(begin,end);
}

template <class N, class E>
void Graph<N,E>::print(std::ostream &os) const {
    for(const auto& elem: nodes){
        std::string transitions = "", transition = "";
        for (const auto& edge: elem->edges){
            transitions += ("[" + (edge.destination)->info + " " + to_string(edge.value) + "] ");
        }
        os << "( " << elem->info << transitions << ") ";
    }
}

template <class N, class E>
inline std::ostream& operator<<(std::ostream& os, const Graph<N,E>& graph){
    graph.print(os);
    return os;
}


