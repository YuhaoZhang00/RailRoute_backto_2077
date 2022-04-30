#pragma once
#include "header.h"
#include <vector>
#include <fstream>

class FileReader
{
private:
	std::ifstream o_file;

public:
	FileReader(char* path)
		: o_file(path)
	{}

	~FileReader()
	{
		o_file.close();
	}

	std::vector<std::string> readWholeFile() {
		std::vector<std::string> output;
		while (o_file) {
			std::string outputStr;
			readLine(outputStr);
			output.emplace_back(outputStr);
		}
		output.pop_back();
		return output;
	}

	void readLine(std::string& output) {
		std::getline(o_file, output);
	}

	int readNumber() {
		std::string temp;
		std::getline(o_file, temp);
		//printf("%s - ", temp.c_str());
		int output = stoi(temp);
		//printf("%d\n", output);
		return output;
	}
};

class FileWriter
{
private:
	std::ofstream o_file;

public:
	FileWriter(char* path)
		: o_file(path)
	{}

	~FileWriter()
	{
		o_file.close();
	}

	template <typename T>
	void write(T content) {
		o_file << content << std::endl;
	}
};
