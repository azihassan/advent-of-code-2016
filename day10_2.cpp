#include <iostream>
#include <vector>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <map>
#include <list>

struct Bot
{
	int low;
	int high;

	Bot()
	{
		low = 0;
		high = 0;
	}

	void take(int value)
	{
		if(low == 0)
		{
			low = value;
			return;
		}
		if(value < low)
		{
			high = low;
			low = value;
		}
		else
		{
			high = value;
		}
	}

	friend std::ostream& operator<< (std::ostream& out, const Bot& bot);
};

std::ostream& operator<< (std::ostream& out, const Bot& bot)
{
	out << "Bot has a low value of " << bot.low << " and a high value of " << bot.high;
	return out;
}

int main(int argc, char *argv[])
{
	std::map<int, Bot> bots;
	std::ifstream fh("input10");
	std::string line;
	std::list<std::string> instructions;
	while(getline(fh, line))
	{
		if(line.find("value ") == 0)
		{
			int value;
			int bot;
			sscanf(line.c_str(), "value %d goes to bot %d", &value, &bot);
			bots[bot].take(value);
		}
		else
		{
			instructions.push_back(line);
		}
	}

	std::map<int, int> outputs;
	while(!instructions.empty())
	{
		std::vector<std::list<std::string>::iterator> to_remove;
		for(auto instruction = instructions.begin(); instruction != instructions.end(); instruction++)
		{
			int giver, low, high;
			char dest_1_str[100], dest_2_str[100];
			sscanf(instruction->c_str(), "bot %d gives low to %s %d and high to %s %d", &giver, dest_1_str, &low, dest_2_str, &high);
			if(bots[giver].low == 0 || bots[giver].high == 0)
				continue;
			std::string dest_1(dest_1_str);
			std::string dest_2(dest_2_str);
			if(dest_1 == "bot")
				bots[low].take(bots[giver].low);
			else
				outputs[low] += bots[giver].low;
			if(dest_2 == "bot")
				bots[high].take(bots[giver].high);
			else
				outputs[high] += bots[giver].high;
			bots[giver].low = 0;
			bots[giver].high = 0;
			to_remove.push_back(instruction);
		}
		for(auto& r: to_remove)
			instructions.erase(r);
	}
	std::cout << outputs[0] * outputs[1] * outputs[2] << std::endl;
	std::cout << "Done" << std::endl;
	return 0;
}
