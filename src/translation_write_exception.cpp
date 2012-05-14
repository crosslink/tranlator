/*
 * translation_write_exception.cpp
 *
 *  Created on: May 14, 2012
 *      Author: monfee
 */

#include "translation_write_exception.h"

translation_write_exception::translation_write_exception(int type) {
	if (type == WRITE_FILE_ERROR) {
		error_message = "Error: can't write to disk";
	}
	else if (type == WRITE_FILE_ERROR) {
		error_message = "Error: can't write to database";
	}
}

int translation_write_exception::get_type() const {
	return type;
}

void translation_write_exception::set_type(int type) {
	this->type = type;
}

//translation_write_exception::~translation_write_exception() {
//}
//
//const char* translation_write_exception::what() const {
//	return error_message.c_str();
//}


