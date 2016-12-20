import std.stdio;
import std.algorithm;
import std.functional;
import std.string;
import std.conv;

void main()
{
	ulong HIGH = 4294967295;
	auto fh = File("input20");
	ulong[][] ranges;
	foreach(line; fh.byLine)
	{
		ulong[] range = line.strip.split("-").to!(ulong[]);
		ranges ~= range;
	}
	ulong smallest = 0;
	bool done;
	while(true)
	{
		done = true;
		foreach(range; ranges)
		{
			if(range[0] <= smallest && smallest <= range[1])
			{
				smallest = range[1] + 1;
				done = false;
			}
		}
		if(done)
			break;
	}
	smallest.writeln;
}
