#include "Graphmtx.h"
#include <fstream>
#include <ctime>

int main()
{
	//data_read_part***********************
	time_t program_start = clock();
	haiwei_v1::Graphmtx G(600);
	std::fstream graph_data("graph_data.csv", std::ios::in);
	if (!graph_data) { std::cerr << "graph_data file could not be opened"; 	system("pause"); exit(1); }
	char buffer[20] = "\n";
	int index, begin, end, weight;
	time_t data_read_start = clock();
	while (!graph_data.eof()) {
		graph_data.getline(buffer, 20);
		sscanf(buffer, "%d,%d,%d,%d", &index, &begin, &end, &weight);
		G.insertEdge(index, begin, end, weight);
	}
	graph_data.close();

	std::fstream path_data("path_data.csv", std::ios::in);
	if (!path_data) { std::cerr << "path_data file could not be opened"; system("pause"); exit(1); }
	std::string  verticesDemand;
	path_data.getline(buffer, 20);
	sscanf(buffer, "%d,%d,%s", &begin, &end, verticesDemand.c_str());
	path_data.close();
	time_t data_read_end = clock();
	//*************************************

	//G.print(std::cout);

	//shortest_path_part ******************	
	time_t path_find_start = clock();
	//int* dist = new int[G.GetVertices()];
	//int* path = new int[G.GetVertices()];
	//haiwei_v1::ShortestsPath(G, begin, dist, path);
	//haiwei_v1::printShortestPath(std::cout, G, begin, dist, path);
	std::ofstream result;
	result.open("result.csv");
	G.Dijkstra(begin, result);
	time_t path_find_end = clock();
	//haiwei_v1::printShortestPath(result, G, begin, dist, path);
	result << "data_read : " << double(data_read_end - data_read_start) / CLOCKS_PER_SEC << std::endl;
	result << "path_find_total_time : " << double(path_find_end - path_find_start) / CLOCKS_PER_SEC << std::endl;
	result.close();
	//**************************************

	//delete []dist;
	//delete []path;

	time_t program_end = clock();

	//show_cost_time_part
	//std::cout << "data_read : " << double(data_read_end - data_read_start) / CLOCKS_PER_SEC << std::endl;
	//result << "path_find_total_time : " << double(path_find_end - path_find_start) / CLOCKS_PER_SEC << std::endl;
	//std::cout << "program_total_time : " << double(program_end - program_start) / CLOCKS_PER_SEC << std::endl;
	//**************************************

	system("pause");
	return 0;
}