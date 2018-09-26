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
SELECT sensor_type.sensor_type_id, sensor.sensor_id, sensor.sensor_name, measurementtype.measurementtype_name FROM sensor_type
INNER JOIN measurementtype ON sensor_type.measurementtype_id = measurementtype.measurementtype_id 
INNER JOIN sensor ON sensor_type.sensor_id = sensor.sensor_id
ORDER BY measurementtype.measurementtype_id, sensor.sensor_id
SQL;

$stmt_sensors = $mysqli->prepare($query_sensors);
$stmt_sensors->execute();
$stmt_sensors->bind_result($sensor_type_id, $sensor_id, $sensor_name, $measurementtype_name);
while ($stmt_sensors->fetch()) 
{
	$data["order".$sensor_type_id] = array("name"=>$sensor_name, "sensor_id"=>$sensor_id, "type"=>$measurementtype_name, "data"=>array());
}
$stmt_sensors->close();

$query_data = <<<SQL2
SELECT `sensor_type_id`
     , DATE_FORMAT(report.report_time_server, '%Y-%m-%dT%TZ') 
     , measurement_value 
FROM report
INNER JOIN measurement ON report.report_id = measurement.report_id
WHERE report.report_time_server > DATE_SUB(NOW(),INTERVAL ? HOUR)
ORDER BY report.report_time_server
SQL2;

if($timespan > 50)
{
	$query_data = <<<SQL2
	SELECT `sensor_type_id`
		 , DATE_FORMAT(MIN(report.report_time_server), '%Y-%m-%dT%TZ') 
		 , AVG(measurement_value)
	FROM report
	INNER JOIN measurement ON report.report_id = measurement.report_id
	WHERE report.report_time_server > DATE_SUB(NOW(),INTERVAL ? HOUR)
	GROUP BY sensor_type_id, UNIX_TIMESTAMP(report.report_time_server) DIV 300
	ORDER BY MIN(report.report_time_server)
SQL2;
}

$stmt_data = $mysqli->prepare($query_data);
$stmt_data->bind_param("d", $timespan);
$stmt_data->execute();
$stmt_data->bind_result($sensor_type_id, $time, $value);
while ($stmt_data->fetch()) 
{
	$data["order".$sensor_type_id]["data"][]= array("time" => $time, "value" => $value);
}
$stmt_data->close();

$mysqli->close();

print json_encode($data);
?>