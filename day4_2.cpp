#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>

char rot(char c, int rotations);
void decrypt(const std::string& input, int sector);

int main(int argc, char *argv[])
{
	std::ifstream fh(argv[1]);
	std::string line;
	int sectors = 0;
	while(getline(fh, line))
	{
		size_t last_dash = line.rfind("-");
		if(last_dash == std::string::npos)
			continue;
		std::map<char, int> count;
		std::map<int, std::string> reversed;
		for(size_t i = 0; i < last_dash; i++)
			if(line[i] != '-')
				count[line[i]]++;
		for(const auto& kv : count)
			reversed[kv.second] += kv.first;
		
		std::string output;
		for(auto it = reversed.rbegin(); it != reversed.rend(); it++)
		{
			std::sort(it->second.begin(), it->second.end());
			output += it->second;
			if(output.length() > 5)
				break;
		}

		std::string checksum = line.substr(line.find("[") + 1, 5);
		if(checksum == output.substr(0, 5))
		{
			int sector = std::stoi(line.substr(last_dash + 1, 3));
			decrypt(line.substr(0, line.rfind("-")), sector);
		}
	}
	std::cout << sectors << std::endl;

	return 0;
}

void decrypt(const std::string& input, int sector)
{
	std::cout << '[' << sector << "] ";
	sector %= 26;
	for(char letter: input)
		std::cout << rot(letter, sector);
	std::cout << std::endl;
}

char rot(char c, int rotations)
{
	while(rotations--)
	{
		if('a' <= c && c <= 'z')
		{
			if(c + 1 > 'z')
				c = 'a';
			else
				c++;
		}
		else
		{
			c = ' ';
		}
	}
	return c;
}
