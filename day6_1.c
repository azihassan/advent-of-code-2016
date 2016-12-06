#include <stdio.h>
#include <stdbool.h>
#include <string.h>

size_t max_idx(const int *array, size_t size);
bool strip(char *str, size_t length);

int main(int argc, char *argv[])
{
	FILE *fh = fopen("input6", "r");
	char msg[1024];
	
	fgets(msg, 1024, fh);
	size_t msg_length = strlen(msg);
	if(strip(msg, msg_length))
		msg_length--;

	int character_count[msg_length][26];
	for(size_t x = 0; x < msg_length; x++)
		for(size_t y = 0; y < 26; y++)
			character_count[x][y] = 0;

	for(size_t i = 0; i < msg_length; i++)
		character_count[i][msg[i] - 'a']++;

	while(fgets(msg, 1024, fh))
	{
		strip(msg, msg_length);
		for(size_t i = 0; i < msg_length; i++)
			character_count[i][msg[i] - 'a']++;
	}
	fclose(fh);

	for(size_t i = 0; i < msg_length; i++)
		printf("%c", 'a' + max_idx(character_count[i], 26));
	return 0;
}

size_t max_idx(const int *array, size_t size)
{
	int max = 0;
	for(size_t i = 0; i < size; i++)
		if(array[i] > array[max])
			max = i;
	return max;
}

bool strip(char *str, size_t length)
{
	if(str[length - 1] == '\n')
	{
		str[length - 1] = '\0';
		return true;
	}
	return false;
}
