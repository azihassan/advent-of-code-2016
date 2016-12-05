<?php
$input = $argc > 1 ? $argv[1] : 'uqwqemis';
$j = 0;
for($i = 0; ; $i++)
{
	$hash = md5($input . $i);
	if(strpos($hash, '00000') === 0)
	{
		echo $hash[5];
		if(++$j === 8)
			break;
	}
}
echo PHP_EOL;
