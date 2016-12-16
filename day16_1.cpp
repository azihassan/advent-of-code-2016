#include <iostream>
#include <algorithm>

const int disk_size = 272;

std::string generate_data(const std::string& input);
std::string generate_checksum(std::string input);
int main(void)
{
	std::string input = "11110010111001001";
	std::cout << input << std::endl;
	if(input.length() < disk_size)
		input = generate_data(input);
	std::cout << generate_checksum(input) << std::endl;
	return 0;
}

std::string generate_data(const std::string& input)
{
	std::string result = input;
	while(result.length() < disk_size)
	{
		std::string a = result;
		std::string b = result;
		std::reverse(b.begin(), b.end());
		std::transform(b.begin(), b.end(), b.begin(), [](char c) {return c == '1' ? '0' : '1';});
		result = a + "0" + b;
	}
	return result.substr(0, disk_size + 1);
}

std::string generate_checksum(std::string input)
{
	std::string result;
	while(true)
	{
		for(size_t i = 0; i < input.length() - 1; i += 2)
		{
			result += input[i] == input[i + 1] ? "1" : "0";
		}
		if(result.length() % 2 != 0)
			break;
		input = result;
		result = "";
	}
	return result;
}
