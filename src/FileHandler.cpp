#include "header.h"
#include "FileHandler.h"

std::vector<char*> FileReader::fileReader(char* path)
{
	char output[100];
	char output2[100];
	int x;


	std::ifstream file(path);
	file.getline(output,100);
	//file >> output;
	//file >> output2;
	file >> x;
	file.close();
	printf("--- %s , %s , %d\n", output, output2, x);

	return std::vector<char*>();
}
