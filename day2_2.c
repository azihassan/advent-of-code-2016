//http://adventofcode.com/2016/day/2
#include <stdio.h>
#define KBD_LENGTH 5

const char keyboard[KBD_LENGTH][KBD_LENGTH] = {
	{'_', '_', '1', '_', '_'},
	{'_', '2', '3', '4', '_'},
	{'5', '6', '7', '8', '9'},
	{'_', 'A', 'B', 'C', '_'},
	{'_', '_', 'D', '_', '_'},
};

struct Position
{
	int x;
	int y;
};

int main(int argc, char *argv[])
{
	FILE *fh = fopen(argv[1], "r");
	struct Position pos = {.x = 0, .y = 2};
	char sequence[1024];
	while(fgets(sequence, 1024, fh))
	{
		for(size_t j = 0; sequence[j]; j++)
		{
			switch(sequence[j])
			{
				case 'U': pos.y = pos.y - 1 < 0 || keyboard[pos.y - 1][pos.x] == '_' ? pos.y : pos.y - 1; break;
				case 'D': pos.y = pos.y + 1 > KBD_LENGTH - 1 || keyboard[pos.y + 1][pos.x] == '_' ? pos.y : pos.y + 1; break;
				case 'L': pos.x = pos.x - 1 < 0 || keyboard[pos.y][pos.x - 1] == '_' ? pos.x : pos.x - 1; break;
				case 'R': pos.x = pos.x + 1 > KBD_LENGTH - 1 || keyboard[pos.y][pos.x + 1] == '_' ? pos.x : pos.x + 1; break;
			}
		}
		printf("%c", keyboard[pos.y][pos.x]);
	}
	printf("\n");
	fclose(fh);
	return 0;
}
