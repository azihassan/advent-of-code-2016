#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

const int INPUT = 1364;
struct Point
{
	int row;
	int col;
	bool wall;
	int distance;
	Point(int row, int col);
	Point operator+(const Point& p);
	bool operator==(const Point& p);
	friend std::ostream& operator<<(std::ostream& out, const Point& point);
};

int count_bits(int n);

int main(int argc, char *argv[])
{
	std::vector<Point> visited;
	std::queue<Point> points;
	Point start(1, 1);
	Point end(39, 31);
	points.push(start);

	const std::vector<Point> surrounding {
		Point(-1, 0),
		Point(+1, 0),
		Point(0, -1),
		Point(0, +1)
	};

	while(!points.empty())
	{
		auto top = points.front();
		points.pop();

		for(const auto& p: surrounding)
		{
			Point current = top + p;
			if(current.wall)
				continue;
			if(current.row < 0 || current.col < 0)
				continue;
			if(std::find(visited.begin(), visited.end(), current) != visited.end())
				continue;
			current.distance = top.distance + 1;
			if(current.distance > 50)
			{
				std::cout << visited.size() << std::endl;
				std::cout << "Done !" << std::endl;
				return 0;
			}
			points.push(current);
			visited.push_back(current);
		}
	}

	return 0;
}

int count_bits(int n)
{
	int count = 0;
	while(n)
	{
		count += n & 1;
		n >>= 1;
	}
	return count;
}

Point::Point(int row, int col)
{
	this->row = row;
	this->col = col;
	distance = 0;
	wall = count_bits(INPUT + col * col + 3 * col + 2 * col * row + row + row * row) % 2 != 0;
}

bool Point::operator==(const Point& p)
{
	return p.row == row && p.col == col;
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
	out << '[' << point.distance << "]{" << point.row << ':' << point.col << '}';
	return out;
}

Point Point::operator+(const Point& p)
{
	Point result(row + p.row, col + p.col);
	return result;
}
