#include "Graphmtx.h"
#include <fstream>
#include <ctime>

int main()
{
	time_t program_start = clock();
	haiwei_v1::Graphmtx G(600);
	std::fstream data("graph_data.csv", std::ios::in);
	if (!data) { std::cerr << "File could not be opened"; 	system("pause"); exit(1); }
	char buffer[20] = "\n";
	int index, begin, end, weight;
	time_t data_read_start = clock();
	while (!data.eof()) {
		data.getline(buffer, 20);
		sscanf(buffer, "%d,%d,%d,%d", &index, &begin, &end, &weight);
		G.insertEdge(index, begin, end, weight);
	}
	data.close();
	time_t data_read_end = clock();
	G.print();
	time_t program_end = clock();
	std::cout << "data_read : " << double(data_read_end - data_read_start) / CLOCKS_PER_SEC << std::endl;
	std::cout << "program_total_time : " << double(program_end - program_start) / CLOCKS_PER_SEC << std::endl;

	std::ofstream result;
	result.open("result.csv");
	G.printFile(result);
	result << "data_read : " << double(data_read_end - data_read_start) / CLOCKS_PER_SEC << std::endl;
	result << "program_total_time : " << double(program_end - program_start) / CLOCKS_PER_SEC << std::endl;
	result.close();
	system("pause");
	return 0;
}