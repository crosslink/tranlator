/*
 * input_manager.h
 *
 *  Created on: Apr 23, 2012
 *      Author: monfee
 */

#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

class input_manager {
private:
	std::string input;

public:
	input_manager();
	virtual ~input_manager();

	void load(const char *file);

	std::string next_text();
	std::string next_file();
};

#endif /* INPUT_MANAGER_H_ */
