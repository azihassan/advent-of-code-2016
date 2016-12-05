<?php
$input = $argc > 1 ? $argv[1] : 'uqwqemis';
$j = 0;
$decrypted = '________';
for($i = 0; ; $i++)
{
	$hash = md5($input . $i);
	if(strpos($hash, '00000') === 0 && '0' <= $hash[5] && $hash[5] <= '7' && $decrypted[$hash[5]] === '_')
	{
		$decrypted[$hash[5]] = $hash[6];
		echo $decrypted, PHP_EOL;
		if(++$j === 8)
			break;
	}
}
