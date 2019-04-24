<?php

include 'db_config.php';

// inspired by https://www.dyclassroom.com/chartjs/chartjs-how-to-draw-bar-graph-using-data-from-mysql-table-and-php
// put data into db

$json = $_POST["data"];
//$json='{"time":"1531759100", "sensor":[{"sensor_type":"1","value":"20.5"},{"sensor_type":"2","value":"20.5"}]}';
$json_obj = json_decode($json);

//get connection
$mysqli = new mysqli(DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME);

if(!$mysqli)
    die("Connection failed: " . $mysqli->error);

$query = "INSERT INTO `report`(`report_time_local`) VALUES (FROM_UNIXTIME(".$mysqli->escape_string($json_obj->time)."))";
$mysqli->query($query);

foreach($json_obj->sensor as $measurement)
{
	$query = "INSERT INTO `measurement`(`report_id`, `sensor_type_id`, `measurement_value`) ".
	          "SELECT  MAX(report_id),".$mysqli->escape_string($measurement->sensor_type).",".$mysqli->escape_string($measurement->value)." FROM report";
    $mysqli->query($query);
}

//close connection
$mysqli->close();

$record = mktime().";".$json_obj->time;
foreach($json_obj->sensor as $measurement)
{
	$record = $record.";".$measurement->sensor_type.";".$measurement->value;
}
file_put_contents(date('Y-m-d').".log", $record."\r\n", FILE_APPEND);
?>