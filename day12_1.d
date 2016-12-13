import std.stdio;
import std.conv : to;
import std.string;

int main(string[] args)
{
	auto cpu = Cpu("input12");
	cpu.program.writeln;
	while(cpu.next_instruction)
	{
		;
	}
	writeln(cpu.registers["a"]);
	return 0;
}

struct Cpu
{
	string[] program;
	int pc;
	int[string] registers;
	void delegate()[string] callbacks;

	this(string file)
	{
		auto fh = File(file);
		foreach(line; fh.byLine)
			program ~= line.idup.strip;
		callbacks["jnz"] = &jnz;
		callbacks["inc"] = &inc;
		callbacks["dec"] = &dec;
		callbacks["cpy"] = &cpy;
		registers["a"] = 0;
		registers["b"] = 0;
		registers["c"] = 0;
		registers["d"] = 0;
	}


	bool next_instruction()
	{
		//registers.writeln;
		//program[pc].writeln;
		auto cb = callbacks.get(program[pc][0 .. 3], &generic);
		cb();
		return pc < program.length;
	}

	void generic()
	{
		writeln("Unknown instruction : ", program[pc]);
		pc++;
	}

	void jnz()
	{
		auto parts = program[pc].split(" ");
		if(parts[1].isNumeric && parts[1].to!int != 0)
		{
			pc += parts[2].to!int;
			return;
		}
		//program[pc].writeln;
		if(!parts[1].isNumeric && registers[parts[1]] != 0)
		{
			pc += parts[2].to!int;
			return;
		}
		pc++;
	}

	void cpy()
	{
		auto parts = program[pc].split(" ");
		registers[parts[2]] = parts[1].isNumeric ? parts[1].to!int : registers[parts[1]].to!int;
		pc++;
	}

	void inc()
	{
		auto parts = program[pc].split(" ");
		registers[parts[1]]++;
		pc++;
	}

	void dec()
	{
		auto parts = program[pc].split(" ");
		registers[parts[1]]--;
		pc++;
	}
}
