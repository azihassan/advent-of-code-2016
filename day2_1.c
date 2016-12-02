//http://adventofcode.com/2016/day/2
#include <stdio.h>
#define KBD_LENGTH 3

const char keyboard[KBD_LENGTH][KBD_LENGTH] = {
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'}
};

struct Position
{
	int x;
	int y;
};

int main(int argc, char *argv[])
{
	FILE *fh = fopen(argv[1], "r");
	struct Position pos = {.x = 1, .y = 1};
	//for(int i = 0; i < 4; i++)
	char sequence[1024];
	while(fgets(sequence, 1024, fh))
	{
		for(size_t j = 0; sequence[j]; j++)
		{
			switch(sequence[j])
			{
				case 'U': pos.y = pos.y - 1 < 0 ? pos.y : pos.y - 1; break;
				case 'D': pos.y = pos.y + 1 > KBD_LENGTH - 1 ? pos.y : pos.y + 1; break;
				case 'L': pos.x = pos.x - 1 < 0 ? pos.x : pos.x - 1; break;
				case 'R': pos.x = pos.x + 1 > KBD_LENGTH - 1 ? pos.x : pos.x + 1; break;
			}
		}
		printf("%c", keyboard[pos.y][pos.x]);
	}
	printf("\n");
	fclose(fh);
	return 0;
}
