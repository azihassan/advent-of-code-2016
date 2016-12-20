#include <stdio.h>
#include <stdlib.h>

struct Elf
{
	int presents;
	int number;
	struct Elf *next;
};

struct Elf * new_elf(int number);
void print_elves(struct Elf *elf);

int main(void)
{
	size_t input = 3017957;
	struct Elf *head = new_elf(0);
	struct Elf *current = head;
	size_t length = input;
	for(size_t i = 1; i < input; i++)
	{
		struct Elf *elf = new_elf(i);
		current->next = elf;
		current = elf;
	}
	current->next = head; //circular

	struct Elf *it = head;
	while(1)
	{
		if(it == it->next)
			break;
		struct Elf *next = it->next;
		it->presents += next->presents;
		it->next = next->next;
		free(next);
		it = it->next;
	}

	//print_elves(it);
	printf("Elf #%d has %d present(s)\n", it->number + 1, it->presents);
	free(it);
	return 0;
}

struct Elf * new_elf(int number)
{
	struct Elf *elf = malloc(sizeof(struct Elf));
	elf->presents = 1;
	elf->number = number;
	elf->next = NULL;
	return elf;
}

void print_elves(struct Elf *elf)
{
	struct Elf *it = elf;
	while(1)
	{
		printf("Elf #%d has %d presents\n", it->number, it->presents);
		it = it->next;
		if(it == elf)
			break;
	}
}
