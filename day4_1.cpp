#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>

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
			if(output.length() >= 5)
				break;
		}

		std::string checksum = line.substr(line.find("[") + 1, 5);
		if(checksum == output.substr(0, 5))
			sectors += std::stoi(line.substr(last_dash + 1, 3));
	}
	std::cout << sectors << std::endl;

	return 0;
}
