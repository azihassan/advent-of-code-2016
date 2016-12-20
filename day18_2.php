<?php
$parent = boolify(trim(file_get_contents('input18'))); //trap = true, safe = false
$width = sizeof($parent);
$safe = 0;
for($i = 0; $i < 399999; $i++)
{
	$safe += ($width - sizeof(array_filter($parent)));
	$row = [];
	for($j = 0; $j < $width; $j++)
	{
		$left = $j - 1 >= 0 ? $parent[$j - 1] : false;
		$right = $j + 1 < $width ? $parent[$j + 1] : false;

		$row[] = $left ^ $right;
	}
	$parent = $row;
}
$safe += ($width - sizeof(array_filter($parent)));
echo $safe;

function boolify($string)
{
	return array_map(function($e) {
		return $e == '^';
	}, str_split($string));
}
