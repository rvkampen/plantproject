CREATE TABLE `sensors` (
  `sensor_id` int(11) NOT NULL AUTO_INCREMENT,
  `sensor_name` varchar(255) NOT NULL,
  PRIMARY KEY (`sensor_id`)
)ENGINE=InnoDB;

CREATE TABLE `measurementtype` (
  `measurementtype_id` int(11) NOT NULL AUTO_INCREMENT,
  `measurementtype_name` varchar(255) NOT NULL,
  PRIMARY KEY (`measurementtype_id`)
)ENGINE=InnoDB;

CREATE TABLE `measurements` (
  `sensor_id` int(11) NOT NULL,
  `measurement_id` int(11) NOT NULL AUTO_INCREMENT,
  `measurement_type` int(11) NOT NULL,
  `measurement_time_server` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `measurement_time_local` DATETIME NOT NULL,
  `measurement_value` double NOT NULL,
  CONSTRAINT pk_measurement  PRIMARY KEY (`measurement_id`,`sensor_id`,`measurement_type`),
  CONSTRAINT fk_measurement_sensor FOREIGN KEY (sensor_id) REFERENCES sensors(sensor_id),
  CONSTRAINT fk_measurement_type FOREIGN KEY (measurement_type) REFERENCES measurementtype(measurementtype_id)
)ENGINE=InnoDB;

INSERT INTO `sensors` (`sensor_id`, `sensor_name`) VALUES ('1', 'Black box 1');
INSERT INTO `sensors` (`sensor_id`, `sensor_name`) VALUES ('2', 'Black box 2');

INSERT INTO `measurementtype` (`measurementtype_id`, `measurementtype_name`) VALUES ('1', 'Temperature');
INSERT INTO `measurementtype` (`measurementtype_id`, `measurementtype_name`) VALUES ('2', 'Humidity');
INSERT INTO `measurementtype` (`measurementtype_id`, `measurementtype_name`) VALUES ('3', 'Pressure');

INSERT INTO `measurements` (`sensor_id`, `measurement_type`, `measurement_time_local`, `measurement_value`) VALUES (1,1,FROM_UNIXTIME(1531759100), 20.3);
INSERT INTO `measurements` (`sensor_id`, `measurement_type`, `measurement_time_local`, `measurement_value`) VALUES (2,1,FROM_UNIXTIME(1531759100), 20.3), (2,2,FROM_UNIXTIME(1531759100), 50.1);