<?php
header('Content-Type: application/json');

include 'db_config.php';

$mysqli = new mysqli(DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME);
if (mysqli_connect_errno())
{
    printf("Connect failed: %s\n", mysqli_connect_error());
    exit();
}

$timespan  = $_GET["timespan"];
if(!$timespan)
	$timespan = 48;

$data = array();

$query_sensors = <<<SQL
SELECT sensors.sensor_id,sensors.sensor_name, measurementtype.measurementtype_id,measurementtype.measurementtype_name, count(*) as count FROM measurements
INNER JOIN measurementtype ON measurements.measurement_type = measurementtype.measurementtype_id 
INNER JOIN sensors ON measurements.sensor_id = sensors.sensor_id
WHERE measurement_time_server > DATE_SUB(NOW(),INTERVAL ? HOUR) AND measurements.measurement_value > 1
GROUP By measurementtype.measurementtype_id, sensors.sensor_id
SQL;

$stmt_sensors = $mysqli->prepare($query_sensors);
$stmt_sensors->bind_param("d", $timespan);
$stmt_sensors->execute();
$stmt_sensors->bind_result($sensor_id, $sensor_name, $measurement_type, $measurement_name, $count);
while ($stmt_sensors->fetch()) 
{
	$data[$sensor_id."_".$measurement_type] = array("name"=>$sensor_name, "sensor_id"=>$sensor_id, "type"=>$measurement_name, "count"=>$count, "data"=>array());
}
$stmt_sensors->close();

$query_data = <<<SQL2
SELECT sensor_id
     , measurement_type
     , DATE_FORMAT(measurement_time_server, '%Y-%m-%dT%TZ') as time
     , measurement_value as value
FROM `measurements`
WHERE measurement_time_server > DATE_SUB(NOW(),INTERVAL ? HOUR) AND measurements.measurement_value > 1
SQL2;

if($timespan > 50)
{
	$query_data = <<<SQL2
	SELECT sensor_id
		 , measurement_type
		 , DATE_FORMAT(MIN(measurement_time_server), '%Y-%m-%dT%TZ') as time
		 , ROUND(AVG(measurement_value),2) as value
	FROM `measurements`
	WHERE measurement_time_server > DATE_SUB(NOW(),INTERVAL ? HOUR) AND measurements.measurement_value > 1
	GROUP BY sensor_id, measurement_type, UNIX_TIMESTAMP(measurement_time_server) DIV 300
SQL2;
}

$stmt_data = $mysqli->prepare($query_data);
$stmt_data->bind_param("d", $timespan);
$stmt_data->execute();
$stmt_data->bind_result($sensor_id, $measurement_type, $time, $value);
while ($stmt_data->fetch()) 
{
	$data[$sensor_id."_".$measurement_type]["data"][]= array("time" => $time, "value" => $value);
}
$stmt_data->close();

$mysqli->close();

print json_encode($data);
?>