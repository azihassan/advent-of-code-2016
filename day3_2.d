import std.stdio;
import std.range;
import std.functional : pipe;
import std.algorithm : map;
import std.conv : to;
import std.array : array;
import std.string : strip;

int main(string[] args)
{
	auto fh = File(args[1]);
	int possible;
	int[][] sides = fh.byLine.map!(pipe!(strip, split, to!(int[]))).array;
	foreach(triplet; sides.chunks(3))
	{
		foreach(triangle; triplet.transposed)
		{
			possible += is_possible(triangle.array);
		}
	}
	possible.writeln;
	return 0;
}

bool is_possible(int[] sides)
{
	return sides[0] + sides[1] > sides[2] && sides[1] + sides[2] > sides[0] && sides[2] + sides[0] > sides[1];
}
