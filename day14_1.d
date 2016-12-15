import std.stdio;
import std.range;
import std.algorithm;
import std.conv : to;
import std.digest.md;

immutable salt = "jlmsuwbz";
int main(string[] args)
{
	int nth = 0;
	for(uint i = 0; ; i++)
	{
		string input = salt ~ i.to!string;
		string hash = input.md5Of.toHexString;
		char repeated = hash.repeated_characters(3);
		if(repeated != '-')
		{
			for(uint j = 1; j < 1000; j++)
			{
				string new_hash = md5Of(salt ~ to!string(i + j)).toHexString;
				char new_repeated = new_hash.repeated_characters(5);
				if(new_repeated == repeated)
				{
					nth++;
					writeln("Index #", i, " gave the key #", nth);
					if(nth == 64)
						return 0;
					break;
				}
			}
		}
	}
	return 0;
}

char repeated_characters(const ref string input, int amount, char sentinel = '-')
{
	foreach(i; 0 .. input.length - amount + 1)
	{
		//string chunk = input[i .. i + amount];
		auto chunk = input[i .. $].take(amount);
		if(chunk.equal(input[i].repeat.take(amount)))
			return input[i];
		/*bool ok = true;
		foreach(j; 0 .. amount)
		{
			if(input[i] != input[j])
			{
				ok = false;
				break;
			}
		}
		if(ok)
			return input[i];*/
	}
	return sentinel;
}

unittest
{
	string input = "abc18".md5Of.toHexString;
	input.repeated_characters(3).writeln;
	assert(input.repeated_characters(3) == '8');

	input = "abc39".md5Of.toHexString;
	input.repeated_characters(3).writeln;
	assert(input.repeated_characters(3) == 'E');

	input = "abc92".md5Of.toHexString;
	assert(input.repeated_characters(3) == '9');

	input = "abc200".md5Of.toHexString;
	assert(input.repeated_characters(5) == '9');

	input = "abcdef";
	assert(input.repeated_characters(5) == '-');

	input = "abcdefff";
	assert(input.repeated_characters(3) == 'f');

	input = "lsqkjdlkqsj";
	assert(input.repeated_characters(5, '?') == '?');
}
