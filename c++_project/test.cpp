#include "Graphmtx.h"
#include <fstream>
#include <ctime>
//#include <stdlib.h>

int main()
{
	//data_read_part***********************
	time_t program_start = clock();
	haiwei_v1::Graphmtx G(600);
	std::fstream graph_data("graph_data.csv", std::ios::in);
	if (!graph_data) { std::cerr << "graph_data file could not be opened"; 	system("pause"); exit(1); }
	const int buf_length = 20;
	char buffer[buf_length] = "\n";
	int index, begin, end, weight;
	time_t data_read_start = clock();
	while (!graph_data.eof()) {
		graph_data.getline(buffer, buf_length);
		sscanf(buffer, "%d,%d,%d,%d", &index, &begin, &end, &weight);
		G.insertEdge(index, begin, end, weight);
	}
	graph_data.close();

	std::fstream path_data("path_data.csv", std::ios::in);
	if (!path_data) { std::cerr << "path_data file could not be opened"; system("pause"); exit(1); }
	//std::string  verticesDemand;
	char buffer2[100] = "\n";
	path_data.getline(buffer2, sizeof(buffer2));
	sscanf(buffer2, "%d,%d,%s", &begin, &end, buffer2);
	char* token;
	for (token = strtok(buffer2, "|"); NULL != token; token = strtok(NULL, "|")) {
		int index = atoi(token);
		G.insertDemandVertices(index);
	}

	path_data.close();
	time_t data_read_end = clock();
	//*************************************

	//G.print(std::cout);

	//shortest_path_part ******************	
	time_t path_find_start = clock();
	std::ofstream result;
	result.open("result.csv");
	G.DijkstraPath(begin, end, result);
	G.DijkstraPath(begin, end, std::cout);
	time_t path_find_end = clock();
	//haiwei_v1::printShortestPath(result, G, begin, dist, path);
	result << "data_read : " << double(data_read_end - data_read_start) / CLOCKS_PER_SEC << std::endl;
	result << "path_find_total_time : " << double(path_find_end - path_find_start) / CLOCKS_PER_SEC << std::endl;
	result.close();
	//**************************************

	time_t program_end = clock();
	//**************************************
	std::cout << "done\n";
	system("pause");
	return 0;
}