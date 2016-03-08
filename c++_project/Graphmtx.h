// file : Graphmtx.h
// description : graph as adjacency matrix and Dijkstra
//               read path_data to m_demandVertice[]
// version : 0.3
// 2016.3.8 22:22

#ifndef HUAWEI_GRAPHMTX_H_VERSION1
#define HUAWEI_GRAPHMTX_H_VERSION1
#include <iostream>
namespace haiwei_v1 {
const int DefaultMaxVertices = 30;
const int maxWeight = 100;
class Graphmtx
{
	//friend void ShortestsPath(Graphmtx& G, int begin, int dist[], int path[]);
	//friend void printShortestPath(std::ostream& out, Graphmtx& G, int begin, int dist[], int path[]);

public:
	Graphmtx(int maxOfVertices = DefaultMaxVertices);
	~Graphmtx(void);
	int GetVertices(void) { return this->m_numOfVertices; }
	bool insertEdge(int indexOfEdge, int begin, int end, int Weight);
	bool insertDemandVertices(int index);
	//void print(void);
	std::ostream& print(std::ostream& out);
	//void Dijkstra(int begin, std::ostream& out);
	void DijkstraPath(int begin, int end, std::ostream& out);
	void DijkstraPath_minHeap(int begin, int end, std::ostream& out);

private:
	int m_maxOfVertices;
	int m_numOfVertices;
	int m_numOfEdges;
	int* m_VerticesList;
	int* m_EdgesList;
	struct  Edge {
		int index;
		int weight;
		Edge(int i, int w): index(i), weight(w) {}
		Edge() : index(-1), weight(0) {}
	}; // Edge
	Edge** m_Edge;
	int* m_demandVertice;
	int m_numOfDemandVertice;
}; // class Graphmtx

Graphmtx::Graphmtx(int maxOfVertices)
	:m_numOfVertices(0), m_numOfEdges(0) {
	this->m_maxOfVertices = (0 < maxOfVertices && maxOfVertices <= 600) ? DefaultMaxVertices : maxOfVertices;
	this->m_numOfVertices = this->m_maxOfVertices;
	m_VerticesList = new int[m_maxOfVertices];
	m_Edge = (Edge**) new Edge*[m_maxOfVertices];
	for (int i = 0; i < m_maxOfVertices; ++i) {
		m_Edge[i] = new Edge[m_maxOfVertices];
		//initialize the matrix = 0 or maxWeight
		for (int j = 0; j < m_maxOfVertices; ++j)
			m_Edge[i][j].weight = (i == j)? 0 : maxWeight;
	}
	m_demandVertice = new int[m_maxOfVertices];
	this->m_numOfDemandVertice = 0;
}

Graphmtx::~Graphmtx() {
	delete [] m_VerticesList;
	delete [] m_demandVertice;
	for (int i = 0; i < m_maxOfVertices; ++i)
		delete [] m_Edge[i];
}

bool Graphmtx::insertEdge(int indexOfEdge, int begin, int end, int weight){
	//only record the min Weight among the parallel Edge
	if (-1 < begin && begin < m_maxOfVertices && -1 < end && end < m_maxOfVertices
		&& 1 <= weight && weight <= 20 && weight < m_Edge[begin][end].weight) {
		m_Edge[begin][end].index = indexOfEdge;
		m_Edge[begin][end].weight = weight;
		++m_numOfEdges;
		return true;
	}
	else return false;
}

bool Graphmtx::insertDemandVertices(int index) {
	if (0 <= index && index < this->m_maxOfVertices) {
		this->m_demandVertice[++m_numOfDemandVertice] = index;
		return true;
	}
	return false;
}
std::ostream& Graphmtx::print(std::ostream& out) {
	out << "vertices : " << m_numOfVertices << ", edges : " << m_numOfEdges << std::endl;
	for (int i = 0; i < m_maxOfVertices; ++i)
		for (int j = 0; j < m_maxOfVertices; ++j) {
			int weight = m_Edge[i][j].weight;
			if (0 < weight && weight < maxWeight)
				out << '(' << i << ',' << j << ',' << weight << ")\n";
		}
	return out;
}

//void Graphmtx::Dijkstra(int begin, std::ostream& out) {
//	const int n = this->m_numOfVertices;
//	int* dist = new int[n];
//	int* path = new int[n];
//	//std::vector<int> path(n);
//	bool* S = new bool[n];//the set of vertices in the shortest path
//	int i, j, k;
//	int weight, minWeight;
//	for (i = 0; i < n; ++i) {
//		dist[i] = this->m_Edge[begin][i].weight; // initialize  the dist[]
//		S[i] = false;
//		path[i] = (i != begin && dist[i] < maxWeight) ? begin : -1;
//	} // end for
//	S[begin] = true; dist[begin] = 0;
//	for (i = 0; i < n - 1; ++i) {
//		minWeight = maxWeight; int u = begin;
//		for (j = 0; j < n; ++j)
//			if (i != j && S[j] == false && *(dist + j) < minWeight) { u = j; minWeight = *(dist + j); }
//		S[u] = true;
//		for (k = 0; k < n; ++k) {
//			weight = this->m_Edge[u][k].weight;
//			if (S[k] == false && weight < maxWeight && dist[u] + weight < dist[k]) {
//				*(dist + k) = *(dist + u) + weight;
//				path[k] = u;
//			}
//		}// end inner for 
//	}// end outer for
//	delete[]S;
//
//	out << "从起点" << begin << "到其他各顶点的最短路径为：" << std::endl;
//	int* d = new int[n];
//	for (i = 0; i < n; ++i) {
//		if (i != begin) {
//			j = i; k = 0;
//			while (j != begin && j != -1) { d[k++] = j; j = path[j]; }
//			out << "the shortest path of vertice " << i << " is " << begin;
//			//output the path
//			while (k > 0) { out << "|" << d[--k] ; }
//			out << ".The shortest path length is " << dist[i] << std::endl;
//		}
//	} // end for
//	delete[]d;
//	//delete[]path;
//	delete[]dist;
//}

void Graphmtx::DijkstraPath(int begin, int end, std::ostream& out) {
	const int n = this->m_numOfVertices;
	int* dist = new int[n];
	int* path = new int[n];
	bool* S = new bool[n];//the set of vertices in the shortest path
	int i, j, k;
	int weight, minWeight;
	for (i = 0; i < n; ++i) {
		dist[i] = this->m_Edge[begin][i].weight; // initialize  the dist[]
		S[i] = false;
		path[i] = (i != begin && dist[i] < maxWeight) ? begin : -1;
	} // end for
	S[begin] = true; dist[begin] = 0;
	for (i = 0; i < n - 1; ++i) {
		minWeight = maxWeight; int u = begin;
		for (j = 0; j < n; ++j)
			if (i != j && S[j] == false && *(dist + j) < minWeight) { u = j; minWeight = *(dist + j); }
		S[u] = true;
		for (k = 0; k < n; ++k) {
			weight = this->m_Edge[u][k].weight;
			if (S[k] == false && weight < maxWeight && dist[u] + weight < dist[k]) {
				*(dist + k) = *(dist + u) + weight;
				path[k] = u;
				//if (k == end) break;
			}
		}// end inner for 
		//if (k == end) break;
	}// end outer for
	delete[]S;
	delete[]dist;

	// use stack to store the path from end->begin, reverse to output
	int* stack = new int[n];
	i = end; k = 0;
	while (i != begin) {
		stack[++k] = i;
		i = path[i];
	}
	stack[++k] = begin;
	while (k > 1) { out << (this->m_Edge[stack[k]][stack[k-1]]).index; --k;  if (k > 2) out << '|'; }
	out << '\n';

	delete[]stack;
	delete[]path;
}

void Graphmtx::DijkstraPath_minHeap(int begin, int end, std::ostream& out) {

}

} // namespace haiwei_v1

#endif // !HUAWEI_GRAPHMTX_H_VERSION1

