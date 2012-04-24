create database google_translate_info;

CREATE TABLE `google_translate_info`.`translations` (
`source` TEXT CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL ,
`translation` TEXT CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL ,
`source_lang` VARCHAR( 20 ) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL ,
`target_lang` VARCHAR( 20 ) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL
) ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS `connection_log` (
  `id` int(11) NOT NULL,
  `connection_date` date NOT NULL,
  `times` int(11) NOT NULL,
  KEY `id` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

CREATE USER 'gt'@'localhost' IDENTIFIED BY 'gtproject';

GRANT USAGE ON *.* TO 'gt'@'localhost' IDENTIFIED BY 'gtproject' WITH MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0 ;

