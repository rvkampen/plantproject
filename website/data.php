<?php
// inspired by https://www.dyclassroom.com/chartjs/chartjs-how-to-draw-bar-graph-using-data-from-mysql-table-and-php
// retrieve data from db to be displayed

//setting header to json
header('Content-Type: application/json');

include 'db_config.php';

//query to get data from the table
$query = "SELECT * FROM `measurements` WHERE `measurement_type`=1";

//get connection
$mysqli = new mysqli(DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME);

if(!$mysqli)
    die("Connection failed: " . $mysqli->error);

//execute query
$result = $mysqli->query($query);

//loop through the returned data
$data = array();
foreach ($result as $row) {
	$data[] = $row;
}

//free memory associated with result
$result->close();

//close connection
$mysqli->close();

//now print the data
print json_encode($data);

?>