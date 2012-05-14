/*
 * translation_write_exception.h
 *
 *  Created on: May 14, 2012
 *      Author: monfee
 */

#ifndef TRANSLATION_WRITE_EXCEPTION_H_
#define TRANSLATION_WRITE_EXCEPTION_H_

//#define NOTHROW throw ()

#include <exception>
#include <string>

class translation_write_exception: public std::exception {
public:
	enum {NO_ERROR = 0, WRITE_FILE_ERROR = 1, WRITE_DATABASE_ERROR = 2};

private:
	int type;
	std::string error_message;

public:
	translation_write_exception(int type);
	virtual ~translation_write_exception() throw() {}

	int get_type() const;
	void set_type(int type);

//	const char* what() const throw();
	const char* what() const throw() { return error_message.c_str(); }
};

#endif /* TRANSLATION_WRITE_EXCEPTION_H_ */
