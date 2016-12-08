#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#define WIDTH 50
#define HEIGHT 6

class Screen
{
private:
	std::vector<std::string> screen;
	int width;
	int height;
	std::string screen_column(size_t col);
	std::string shift_right(const std::string& row, int amount, size_t max) const;
public:
	Screen(size_t width, size_t height);
	void draw_screen() const;
	void draw_rect(size_t width, size_t height);
	void shift_right(size_t row, int amount);
	void shift_down(size_t col, int amount);
	int lit() const;
};

int main(int argc, char *argv[])
{
	Screen screen(50, 6);

	std::ifstream fh("input8");
	std::string instruction;
	while(getline(fh, instruction))
	{
		if(instruction[1] == 'e') //r[e]ct
		{
			int width = std::stoi(instruction.substr(instruction.find(" ") + 1, instruction.find("x")));
			int height = std::stoi(instruction.substr(instruction.find("x") + 1));
			screen.draw_rect(width, height);
		}
		else if(instruction[7] == 'r') //rotate [r]ow 
		{
			int row = std::stoi(instruction.substr(instruction.find("=") + 1, instruction.find(" by")));
			int amount = std::stoi(instruction.substr(instruction.rfind(" ") + 1));
			screen.shift_right(row, amount);
		}
		else
		{
			int col = std::stoi(instruction.substr(instruction.find("=") + 1, instruction.find(" by")));
			int amount = std::stoi(instruction.substr(instruction.rfind(" ") + 1));
			screen.shift_down(col, amount);
		}
	}
	screen.draw_screen();
	std::cout << screen.lit() << std::endl;

	return 0;
}

std::string Screen::shift_right(const std::string& row, int amount, size_t max) const
{
	std::string result = row;
	for(int i = 0; i <= amount; i++)
		result = "." + result;
	if(result.length() >= max)
		result.replace(0, result.length() - max, result.substr(max + 1));
	return result.substr(0, max);
}

void Screen::shift_right(size_t row, int amount)
{
	screen[row] = shift_right(screen[row], amount, width);
}

void Screen::shift_down(size_t col, int amount)
{
	std::string column = screen_column(col);
	column = shift_right(column, amount, height);
	for(size_t row = 0; row < column.length(); row++)
		screen[row][col] = column[row];
}

std::string Screen::screen_column(size_t col)
{
	std::string column;
	column.reserve(height);
	for(const auto& row: screen)
		column.push_back(row[col]);
	return column;
}

void Screen::draw_rect(size_t width, size_t height)
{
	for(size_t r = 0; r < height; r++)
	{
		for(size_t c = 0; c < width; c++)
		{
			screen[r][c] = '#';
		}
	}
}

void Screen::draw_screen() const
{
	for(const auto& row: screen)
		std::cout << row << std::endl;
	std::cout << std::endl;
}

Screen::Screen(size_t width, size_t height)
{
	this->width = width;
	this->height = height;
	screen.reserve(height);
	while(height--)
	{
		std::string row(width, '.');
		screen.push_back(row);
	}
}

int Screen::lit() const
{
	int count = 0;
	for(const auto& row: screen)
		for(char cell: row)
			count += cell == '#';
	return count;
}
