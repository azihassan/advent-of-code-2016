<?php
$input = trim(file_get_contents('input9'));
echo strlen($input), PHP_EOL;
echo unzipped_length($input);
exit;

var_dump(unzipped_length('ADVENT') == 6);
var_dump(unzipped_length('A(1x5)BC') == 7);
var_dump(unzipped_length('(3x3)XYZ') == 9);
var_dump(unzipped_length('A(2x2)BCD(2x2)EFG') == 11);
var_dump(unzipped_length('(6x1)(1x3)A') == 6);
var_dump(unzipped_length('X(8x2)(3x3)ABCY') == 18);
var_dump(unzipped_length('(4x14)JVWV') == 56);

function unzipped_length($input)
{
	$length = 0;
	while(true)
	{
		$open = strpos($input, '(');
		if($open === false)
		{
			$length += strlen($input);
			break;
		}
		$length += $open;
		$close = strpos($input, ')');
		$format = substr($input, $open + 1, $close - $open - 1);
		sscanf($format, "%dx%d", $count, $repetition);
		$input = substr($input, $close + 1);
		$length += $count * $repetition;
		$input = substr($input, $count);
	}

	return $length;
}
