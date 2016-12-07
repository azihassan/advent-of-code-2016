import std.stdio;
import std.array : array;
import std.functional : pipe;
import std.algorithm : filter, map, sum, any, canFind;
import std.string;

int main(string[] args)
{
	auto fh = File("input7");
	int count;
	foreach(line; fh.byLine.map!(pipe!(idup, strip)))
	{
		if(line.strip.supports_ssl)
			count++;
	}
	count.writeln;
	return 0;
}

auto outside_brackets(string input)
{
	struct OutsideBrackets
	{
		private
		{
			string input;
			int open_idx;
			int close_idx;
			bool last_handled;
			bool first_handled;
		}

		this(string input)
		{
			this.input = input;
			first_handled = false;
			last_handled = false;
		}

		void popFront()
		{
			if(!first_handled)
			{
				open_idx = input.indexOf('[');
				return;
			}
			close_idx = input.indexOf(']', open_idx);
			open_idx = input.indexOf('[', close_idx);
		}

		string front()
		{
			if(!first_handled)
			{
				first_handled = true;
				return input[0 .. open_idx];
			}
			if(!last_handled && open_idx == -1)
			{
				last_handled = true;
				return input[close_idx + 1 .. $];
			}
			return input[close_idx + 1 .. open_idx];
		}

		bool empty()
		{
			return open_idx == -1 && last_handled;
		}
	}
	auto brackets = OutsideBrackets(input);
	brackets.popFront;
	return brackets;
}

unittest
{
	import std.array : array;
	string input = "gdlrknrmexvaypu[crqappbbcaplkkzb]vhvkjyadjsryysvj[nbvypeadikilcwg]jwxlimrgakadpxu[dgoanojvdvwfabtt]yqsalmulblolkgsheo[foobar]qlkjpogilskj[]qlks";
	auto brackets = input.outside_brackets.array;
	assert(brackets[0] == "gdlrknrmexvaypu");
	assert(brackets[1] == "vhvkjyadjsryysvj");
	assert(brackets[2] == "jwxlimrgakadpxu");
	assert(brackets[3] == "yqsalmulblolkgsheo");
	assert(brackets[4] == "qlkjpogilskj");
	assert(brackets[5] == "qlks");

	input = "[first]qsdjlqskjdlkqsdj[second]qlsjdjqsh[last]";
	brackets = input.outside_brackets.array.filter!(a => a.length > 1).array;
	//assert(brackets[0] == "");
	assert(brackets[0] == "qsdjlqskjdlkqsdj");
	assert(brackets[1] == "qlsjdjqsh");
	//assert(brackets[3] == "");
}

auto inside_brackets(string input)
{
	struct InsideBrackets
	{
		private
		{
			string input;
			int open_idx;
			int close_idx;
		}

		this(string input)
		{
			this.input = input;
		}

		void popFront()
		{
			open_idx = input.indexOf('[', close_idx);
			close_idx = input.indexOf(']', open_idx);
		}

		string front()
		{
			return input[open_idx + 1 .. close_idx];
		}

		bool empty()
		{
			return open_idx == -1;
		}
	}
	auto brackets = InsideBrackets(input);
	brackets.popFront;
	return brackets;
}

unittest
{
	import std.array : array;
	string input = "gdlrknrmexvaypu[crqappbbcaplkkzb]vhvkjyadjsryysvj[nbvypeadikilcwg]jwxlimrgakadpxu[dgoanojvdvwfabtt]yqsalmulblolkgsheo[foobar]qlkjpogilskj[]qlks";
	auto brackets = input.inside_brackets.array;
	assert(brackets[0] == "crqappbbcaplkkzb");
	assert(brackets[1] == "nbvypeadikilcwg");
	assert(brackets[2] == "dgoanojvdvwfabtt");
	assert(brackets[3] == "foobar");
	assert(brackets[4] == "");

	input = "[first]qsdjlqskjdlkqsdj[second]qlsjdjqsh[last]";
	brackets = input.inside_brackets.array;
	assert(brackets[0] == "first");
	assert(brackets[1] == "second");
	assert(brackets[2] == "last");
}

bool supports_ssl(string input)
{
	string[] inside = input.inside_brackets.array;
	foreach(seq; input.outside_brackets.array.filter!(a => a.length > 1))
	{
		foreach(i; 0 .. seq.length - 2)
			if(seq[i] != seq[i + 1] && seq[i] == seq[i + 2])
				if(inside.any!(part => part.canFind(format("%c%c%c", seq[i + 1], seq[i + 2], seq[i + 1]))))
					return true;
	}
	return false;
}

unittest
{
	assert("aba[bab]xyz".supports_ssl == true);
	assert("xyx[xyx]xyx".supports_ssl == false);
	assert("aaa[kek]eke".supports_ssl == true);
	assert("zazbz[bzb]cdb".supports_ssl == true);
}

bool has_aba(string sequence)
{
	foreach(i; 0 .. sequence.length - 2)
		if(sequence[i] != sequence[i + 1] && sequence[i] == sequence[i + 2])
			return true;
	return false;
}

unittest
{
	assert("abaxyz".has_aba == true);
	assert("xyxxyx".has_aba == true);
	assert("aaaeke".has_aba == true);
	assert("qsdhjkqshd".has_aba == false);
	assert("zazbzcdb".has_aba == true);
}
