import std.stdio;
import std.string : strip;
import std.format : formattedRead;

int main(string[] args)
{
	auto fh = File(args[1]);
	int possible;
	string line;
	while((line = fh.readln.strip) !is null)
	{
		int a, b, c;
		line.formattedRead("%d %d %d", &a, &b, &c);
		if(a + b > c && b + c > a && c + a > b)
			possible++;
	}
	possible.writeln;
	return 0;
}
