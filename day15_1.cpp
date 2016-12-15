#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>

struct Disc
{
	int current;
	int positions;
	friend std::ostream& operator<<(std::ostream& out, const Disc& disc);
	bool slot()
	{
		return current == 0;
	}

	Disc& operator++(int wat)
	{
		if(++current == positions)
			current = 0;
		return *this;
	}
};
bool canFall(std::vector<Disc> discs);
void rotate(std::vector<Disc>& discs);

std::ostream& operator<<(std::ostream& out, const Disc& disc)
{
	out << '[' << disc.current << '/' << disc.positions << ']';
	return out;
}

int main(int argc, char *argv[])
{
	std::ifstream fh("input15");
	std::string line;
	std::vector<Disc> discs;
	while(getline(fh, line))
	{
		Disc disc = {0, 0};
		int ignore;
		sscanf(line.c_str(), "Disc #%d has %d positions; at time=0, it is at position %d.", &ignore, &disc.positions, &disc.current);
		discs.push_back(disc);
	}

	int time = 0;
	while(true)
	{
		if(canFall(discs))
		{
			std::cout << "Ball falls through all discs at time " << time << std::endl;
			break;
		}
		rotate(discs);
		time++;
	}
	return 0;
}

void rotate(std::vector<Disc>& discs)
{
	for(auto& disc: discs)
		disc++;
}

bool canFall(std::vector<Disc> discs)
{
	size_t ball_position = 0;
	while(ball_position < discs.size())
	{
		rotate(discs);
		if(!discs[ball_position].slot())
			return false;
		ball_position++;
	}
	return true;
}
