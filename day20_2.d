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
	ulong highest = 0;
	foreach(line; fh.byLine)
	{
		ulong[] range = line.strip.split("-").to!(ulong[]);
		if(range[1] > highest)
			highest = range[1];
		ranges ~= range;
	}
	ulong smallest = 0;
	bool done;
	int count;
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
		{
			smallest++;
			if(smallest == HIGH)
				break;
			count++;
		}
		if(smallest > highest)
			break;
	}
	writeln(count + (HIGH - highest));
}
