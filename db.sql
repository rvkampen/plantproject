CREATE TABLE `sensor` (
  `sensor_id` TINYINT NOT NULL AUTO_INCREMENT,
  `sensor_name` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`sensor_id`)
);

CREATE TABLE `measurementtype` (
  `measurementtype_id` TINYINT NOT NULL AUTO_INCREMENT,
  `measurementtype_name` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`measurementtype_id`)
);

CREATE TABLE `sensor_type` (
  `sensor_type_id` TINYINT NOT NULL AUTO_INCREMENT,
  `sensor_id` TINYINT NOT NULL,
  `measurementtype_id` TINYINT NOT NULL,
  CONSTRAINT pk_sensor_type  PRIMARY KEY (`sensor_type_id`),
  CONSTRAINT fk_sensor_type_sensor FOREIGN KEY (sensor_id) REFERENCES sensor(sensor_id),
  CONSTRAINT fk_sensor_type_type FOREIGN KEY (measurementtype_id) REFERENCES measurementtype(measurementtype_id)
);

CREATE TABLE `report` (
  `report_id` INT NOT NULL AUTO_INCREMENT,
  `report_time_server` TIMESTAMP,
  `report_time_local` TIMESTAMP,
  PRIMARY KEY (`report_id`)
);

CREATE TABLE `measurement` (
  `report_id` INT NOT NULL,
  `sensor_type_id` TINYINT NOT NULL,
  `measurement_value` FLOAT NOT NULL,
  CONSTRAINT pk_measurement  PRIMARY KEY (`report_id`,`sensor_type_id`),
  CONSTRAINT fk_measurement_sensor FOREIGN KEY (sensor_type_id) REFERENCES sensor_type(sensor_type_id),
  CONSTRAINT fk_measurement_report FOREIGN KEY (report_id) REFERENCES report(report_id)
);

INSERT INTO `sensor` (`sensor_id`, `sensor_name`) VALUES ('1', 'BlackBox');
INSERT INTO `sensor` (`sensor_id`, `sensor_name`) VALUES ('2', 'Clock');
INSERT INTO `sensor` (`sensor_id`, `sensor_name`) VALUES ('3', 'Baro');

INSERT INTO `measurementtype` (`measurementtype_id`, `measurementtype_name`) VALUES ('1', 'Temperature');
INSERT INTO `measurementtype` (`measurementtype_id`, `measurementtype_name`) VALUES ('2', 'Humidity');
INSERT INTO `measurementtype` (`measurementtype_id`, `measurementtype_name`) VALUES ('3', 'Pressure');

INSERT INTO `sensor_type` (`sensor_type_id`, `sensor_id`, `measurementtype_id`) VALUES ('1','1','1');
INSERT INTO `sensor_type` (`sensor_type_id`, `sensor_id`, `measurementtype_id`) VALUES ('2','1','2');
INSERT INTO `sensor_type` (`sensor_type_id`, `sensor_id`, `measurementtype_id`) VALUES ('3','2','1');
INSERT INTO `sensor_type` (`sensor_type_id`, `sensor_id`, `measurementtype_id`) VALUES ('4','3','1');
INSERT INTO `sensor_type` (`sensor_type_id`, `sensor_id`, `measurementtype_id`) VALUES ('5','3','3');

INSERT INTO `report`(`report_time_local`) VALUES (FROM_UNIXTIME(1531759100))

INSERT INTO `measurement`(`report_id`, `sensor_type_id`, `measurement_value`) SELECT  MAX(report_id), 1, 20.3 FROM report
INSERT INTO `measurement`(`report_id`, `sensor_type_id`, `measurement_value`) SELECT  MAX(report_id), 2, 43   FROM report
INSERT INTO `measurement`(`report_id`, `sensor_type_id`, `measurement_value`) SELECT  MAX(report_id), 3, 20.4 FROM report
INSERT INTO `measurement`(`report_id`, `sensor_type_id`, `measurement_value`) SELECT  MAX(report_id), 4, 21.3 FROM report
INSERT INTO `measurement`(`report_id`, `sensor_type_id`, `measurement_value`) SELECT  MAX(report_id), 5, 1008.6 FROM report
