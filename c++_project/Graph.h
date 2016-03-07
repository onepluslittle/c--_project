//#pragma once
#ifndef HUAWEI_GRAPH_H_VERSION1
#define HUAWEI_GRAPH_H_VERSION1

namespace haiwei_v1 {

class  Graph
{
public:
	Graph(int numOfVertices);
	virtual ~ Graph() = 0;
	bool GraphEmpty(void) const {
		return m_numOfEdges == 0;
	}
	/*bool GraphFull(void) const {
		return numEdges == maxVertices * (maxVertices-1);
	}*/
private:
	int m_numOfEdges;
	int numVertices;
	int maxVertices;
};

}// namespace haiwei_v1

#endif // !HUAWEI_GRAPH_H_VERSION1

