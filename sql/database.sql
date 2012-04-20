create database google_translate_info;


CREATE TABLE IF NOT EXISTS `connection_log` (
  `id` int(11) NOT NULL,
  `connection_date` date NOT NULL,
  `times` int(11) NOT NULL,
  KEY `id` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

CREATE USER 'gt'@'localhost' IDENTIFIED BY '***';

GRANT USAGE ON * . * TO 'gt'@'localhost' IDENTIFIED BY '***' WITH MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0 ;

