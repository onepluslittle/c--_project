//#pragma once
#ifndef HUAWEI_GRAPHMTX_H_VERSION1
#define HUAWEI_GRAPHMTX_H_VERSION1

//#include <cassert>
#include <iostream>
namespace haiwei_v1 {

const int DefaultMaxVertices = 600;
const int maxWeight = 100;
class Graphmtx
{
public:
	Graphmtx(int maxOfVertices = DefaultMaxVertices);
	~Graphmtx(void);
	bool insertEdge(int indexOfEdge, int begin, int end, int Weight);
	void print(void);
	std::ostream& printFile(std::ostream& out);

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

void Graphmtx::print() {
	std::cout << "vertices : " << m_numOfVertices << ", edges : " << m_numOfEdges << std::endl;
	for (int i = 0; i < m_maxOfVertices; ++i)
		for (int j = 0; j < m_maxOfVertices; ++j){
			int weight = m_Edge[i][j];
			if (0 < weight && weight < maxWeight)
				std::cout << '(' << i << ',' << j << ','<< weight << ")\n";
		}
}

std::ostream& Graphmtx::printFile(std::ostream& out) {
	out << "vertices : " << m_numOfVertices << ", edges : " << m_numOfEdges << std::endl;
	for (int i = 0; i < m_maxOfVertices; ++i)
		for (int j = 0; j < m_maxOfVertices; ++j) {
			int weight = m_Edge[i][j];
			if (0 < weight && weight < maxWeight)
				out << '(' << i << ',' << j << ',' << weight << ")\n";
		}
	return out;
}


} // namespace haiwei_v1

#endif // !HUAWEI_GRAPHMTX_H_VERSION1

