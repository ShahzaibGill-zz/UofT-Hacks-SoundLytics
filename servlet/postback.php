<?php
error_reporting(1);
/* SQL Configuration */
$dbhost = "localhost";
$dbuser = "justin_sound";
$dbpass = "soundlytics";
$dbname = "justin_soundlytics";
$link = mysql_connect($dbhost,$dbuser,$dbpass);
mysql_select_db($dbname, $link);


if($_GET) {
	$id = mysql_real_escape_string($_GET['id']);
	$sound = mysql_real_escape_string($_GET['sound']);
	$light = mysql_real_escape_string($_GET['light']);
	$temp = mysql_real_escape_string($_GET['temp']);
	mysql_query("INSERT INTO `entry` (`id`, `owner`, `date`, `sound`, `light`, `temp`) VALUES (NULL, '$id', NOW(), '$sound', '$light', '$temp');");
} else {
	exit();
}
?>