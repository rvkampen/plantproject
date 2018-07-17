<?php

include 'db_config.php';

// inspired by https://www.dyclassroom.com/chartjs/chartjs-how-to-draw-bar-graph-using-data-from-mysql-table-and-php
// put data into db

$json = $_POST["data"];
//$json='{"time":"1531759100", "sensor":[{"id":"1","type":"1","value":"20.5"},{"id":"2","type":"1","value":"20.5"}]}';
$arr = json_decode($json);

//get connection
$mysqli = new mysqli(DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME);

if(!$mysqli)
    die("Connection failed: " . $mysqli->error);

foreach($arr->sensor as $row)
{
    // query to insert the data
    $query = "INSERT INTO `measurements` (`sensor_id`, `measurement_type`, `measurement_time_local`, `measurement_value`)".
    "VALUES (".$mysqli->escape_string($row->id).",".$mysqli->escape_string($row->type).",FROM_UNIXTIME(".$mysqli->escape_string($arr->time)."), ".$mysqli->escape_string($row->value).");";
    
    //execute query
    $mysqli->query($query);
}

//close connection
$mysqli->close();

?>