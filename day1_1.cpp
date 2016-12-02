#include <iostream>
#include <cmath>
#include <fstream>

enum Direction {UP, DOWN, LEFT, RIGHT};
struct Position
{
	int x;
	int y;
};

int main(int argc, char *argv[])
{
	Position position = {0, 0};
	Direction direction;
	std::ifstream fh(argv[1]);
	std::string turn;
	while(fh >> turn)
	{
		switch(direction)
		{
			case UP:	direction = turn[0] == 'R' ? RIGHT : LEFT; break;
			case DOWN:	direction = turn[0] == 'R' ? LEFT : RIGHT; break;
			case LEFT:	direction = turn[0] == 'R' ? UP : DOWN; break;
			case RIGHT:	direction = turn[0] == 'R' ? DOWN : UP; break;
		}
		int offset = std::stoi(turn.substr(1));
		if(direction == LEFT)
			position.x -= offset;
		else if(direction == RIGHT)
			position.x += offset;
		if(direction == UP)
			position.y -= offset;
		else if(direction == DOWN)
			position.y += offset;
	}
	std::cout << "New position : {" << position.x << ',' << position.y << '}' << std::endl;
	std::cout << "Distance : " << (std::abs(position.x) + std::abs(position.y)) << std::endl;
	return 0;
}
