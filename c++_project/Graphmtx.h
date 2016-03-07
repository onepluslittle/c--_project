// file : Graphmtx.h
// description : graph as adjacency matrix and Dijkstra
// 2016.3.7 

#ifndef HUAWEI_GRAPHMTX_H_VERSION1
#define HUAWEI_GRAPHMTX_H_VERSION1

//#include <cassert>
#include <iostream>
#include <vector>
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
	//void print(void);
	std::ostream& print(std::ostream& out);
	void Dijkstra(int begin, std::ostream& out);

private:
	int m_maxOfVertices;
	int m_numOfVertices;
	int m_numOfEdges;
	int* m_VerticesList;
	int* m_EdgesList;
	int** m_Edge;
}; // class Graphmtx

Graphmtx::Graphmtx(int maxOfVertices)
	:m_numOfVertices(0), m_numOfEdges(0) {
	this->m_maxOfVertices = (0 < maxOfVertices && maxOfVertices <= 600) ? DefaultMaxVertices : maxOfVertices;
	this->m_numOfVertices = this->m_maxOfVertices;
	m_VerticesList = new int[m_maxOfVertices];
	m_Edge = (int**) new int*[m_maxOfVertices];
	for (int i = 0; i < m_maxOfVertices; ++i) {
		m_Edge[i] = new int[m_maxOfVertices];
		//initialize the matrix = 0 or maxWeight
		for (int j = 0; j < m_maxOfVertices; ++j)
			m_Edge[i][j] = (i == j)? 0 : maxWeight;
	}
}

Graphmtx::~Graphmtx() {
	delete [] m_VerticesList;
	for (int i = 0; i < m_maxOfVertices; ++i)
		delete [] m_Edge[i];
}

bool Graphmtx::insertEdge(int indexOfEdge, int begin, int end, int weight){
	//only record the min Weight among the parallel Edge
	if (-1 < begin && begin < m_maxOfVertices && -1 < end && end < m_maxOfVertices
		&& 1 <= weight && weight <= 20 && weight < m_Edge[begin][end]) {
		m_Edge[begin][end] = weight;
		++m_numOfEdges;
		return true;
	}
	else return false;
}

std::ostream& Graphmtx::print(std::ostream& out) {
	out << "vertices : " << m_numOfVertices << ", edges : " << m_numOfEdges << std::endl;
	for (int i = 0; i < m_maxOfVertices; ++i)
		for (int j = 0; j < m_maxOfVertices; ++j) {
			int weight = m_Edge[i][j];
			if (0 < weight && weight < maxWeight)
				out << '(' << i << ',' << j << ',' << weight << ")\n";
		}
	return out;
}


// Dijkstra algorithm
// parameters : 
//     begin   : the start vertice
//     dist[j] : the shortest path length for begin to j, 0 <= j < n
//     path[j] : store the shortest path length, 0 <= j < n
//void ShortestsPath(Graphmtx& G, int begin, int* dist, int* path) {
//	const int n = G.m_numOfVertices;
//	bool* S = new bool[n];//the set of vertices in the shortest path
//	int i, j, k;
//	int weight, minWeight;
//	for (i = 0; i < n; ++i) {
//		dist[i] = G.m_Edge[begin][i]; // initialize  the dist[]
//		S[i] = false;
//		*(path+i) = (i != begin && dist[i] < maxWeight) ? begin : -1;
//	} // end for
//	S[begin] = true; dist[begin] = 0;
//	for (i = 0; i < n - 1; ++i) {
//		minWeight = maxWeight; int u = begin;
//		for (j = 0; j < n; ++j)
//			if (S[j] == false && *(dist+j) < minWeight) {u = j; minWeight = *(dist+j);}
//		S[u] = true;
//		for (k = 0; k < n; ++k) {
//			weight = G.m_Edge[u][k];
//			if (S[k] == false && weight < maxWeight && dist[u] + weight < dist[k]) {
//				*(dist+k) = *(dist+u) + weight;
//				*(path+k) = u;
//			}
//		}// end inner for 
//	}// end outer for
//	delete []S;
//}

//void printShortestPath(std::ostream& out, Graphmtx& G, int begin, int* dist, int* path) {
//	out << "从起点" << begin << "到其他各顶点的最短路径为：" << std::endl;
//	int i, j, k, n = G.m_numOfVertices;
//	int* d = new int[n];
//	for (i = 0; i < n; ++i) {
//		if (i != begin) {
//			j = i; k = 0;
//			while (j != begin) { d[k++] = j; j = *(path+j); }
//			out << "the shortest path of vertice " << i << "is " << begin;
//			while (k > 0) { out << d[--k] << " "; }
//			out << "the shortest path length is " << dist[i] << std::endl;
//		}
//	} // end for
//	delete []d;
//}

void Graphmtx::Dijkstra(int begin, std::ostream& out) {
	const int n = this->m_numOfVertices;
	int* dist = new int[n];
	int* path = new int[n];
	//std::vector<int> path(n);
	bool* S = new bool[n];//the set of vertices in the shortest path
	int i, j, k;
	int weight, minWeight;
	for (i = 0; i < n; ++i) {
		dist[i] = this->m_Edge[begin][i]; // initialize  the dist[]
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
			weight = this->m_Edge[u][k];
			if (S[k] == false && weight < maxWeight && dist[u] + weight < dist[k]) {
				*(dist + k) = *(dist + u) + weight;
				path[k] = u;
			}
		}// end inner for 
	}// end outer for
	delete[]S;

	out << "从起点" << begin << "到其他各顶点的最短路径为：" << std::endl;
	int* d = new int[n];
	for (i = 0; i < n; ++i) {
		if (i != begin) {
			j = i; k = 0;
			while (j != begin && j != -1) { d[k++] = j; j = path[j]; }
			out << "the shortest path of vertice " << i << " is " << begin;
			//output the path
			while (k > 0) { out << "|" << d[--k] ; }
			out << ".The shortest path length is " << dist[i] << std::endl;
		}
	} // end for
	delete[]d;
	//delete[]path;
	delete[]dist;
}

} // namespace haiwei_v1

#endif // !HUAWEI_GRAPHMTX_H_VERSION1

