/*
 * article_reader.cpp
 *
 *  Created on: Apr 24, 2012
 *      Author: monfee
 */

#include "article_reader.h"
//#include "ant_link_parts.h"

#include <time.h>
#include <stdio.h>
#include <string.h>

#include <string>
#include <iostream>
#include <exception>
#include <algorithm>

using namespace std;

/*
 *
 *
 */
char *article_reader::string_clean(token_string& token, long lower_case_only)
{
char *ch, *from, *to;

/*
	remove XML tags and remove all non-alnum (but keep case)
*/
ch = token.start;
while (/**ch != '\0' && */(ch - token.start) < token.length)
	{
	if (*ch == '<')			// then remove the XML tags
		{
		while (*ch != '>')
			*ch++ = ' ';
		*ch++ = ' ';
		}
	else if (!isalnum(*ch))	// then remove it
		*ch++ = ' ';
	else
		{
		if (lower_case_only)
			{
			*ch = (char)tolower(*ch);
			ch++;
			}
		else
			ch++;
		}
	}

return token.start;
}



article_reader::article_reader(const char *file) {
	first_para = NULL;
	first_section = NULL;
	next_section = NULL;
	sec_start = NULL;
}

article_reader::~article_reader() {

}

/*
 * process xml file by each element
 */

token_string *article_reader::get_next_token() {
	process();
	return &current_token;
}

void article_reader::copy_to_next_token(article_writer& writer) {
//	content.a
}

token_string * article_reader::get_next_token(article_writer& the_writer) {
	writer = &the_writer;

	progress = TITLE;
	process();
	return &current_token;
}

void article_reader::process() {
	init_token();

	if (current != previous) {
		copy_to_current(previous, current);
		previous = current;
	}

	while (progress <= EXTERNAL_LINKS && current_token.length == 0) {
		switch (progress) {
		case TITLE:
			this->read_title();
			++progress;
			break;
		case CATEGORIES:
			this->read_categories();
	//		++progress;
			break;
		case ABSTRACT:
			this->read_abstract();
	//		++progress;
			break;
		case MAIN_TEXT:
			this->read_main_text();
	//		++progress;
			break;
		case NOTES:
			this->skip_notes();
//			this->read_notes();
			read_section();
	//		++progress;
			break;
		case REFERENCES:
			this->skip_references();
			read_section();
//			++progress;
			break;
		case EXTERNAL_LINKS:
			this->skip_external_links();
			read_section();
//			++progress;
			break;
		}
	}

	if (progress > EXTERNAL_LINKS) {
		wrap_up_to_end();
	}
}

void article_reader::read() {
	article::read();
	current = content;
	previous = current;

	first_para = strstr(current, "<p>");
	first_section = strstr(current, "<sec>");
}

void article_reader::read_title() {
	static const char *TITLE_TAG_START = "<title>";
	static const char *TITLE_TAG_END = "</title>";

	start = strstr(current, TITLE_TAG_START);
	if (start != NULL) {
		start += strlen(TITLE_TAG_START);
		current_token.start = start;
		copy_to_current(current, start);

		end = strstr(start, TITLE_TAG_END);
		if (end != NULL) {
			previous = current;
			current = end += strlen(TITLE_TAG_END);
			current_token.length = end - start;


//			start = strchr(start, '"');
//			++start;
//			end =  strchr(start, '"');
		}
	}

	if (start == NULL || end == NULL) {
		string msg = string("The article is not well-formed in the article title: ") + file_path;
		throw msg.c_str();
	}
}

void article_reader::read_categories() {
	static const char *CATEGORY_TAG = "category";
//	static const char *CATEGORY_TAG_START = "<category>";
//	static const char *CATEGORY_TAG_END = "</category>";

	read_element_text(CATEGORY_TAG);

	if (start == NULL) {
		++progress;
		wrap_up_to_body();
	}
	else
		if (end == NULL) {
			string msg = string("The article is not well-formed in the article title: ") + file_path;
			throw msg.c_str();
		}

}

void article_reader::read_abstract() {
	while (current < first_section) {

	}
}

void article_reader::read_main_text() {
	read_section();
//	while (next_section != NULL)
//		read_section();
}

void article_reader::skip_notes() {
	copy_to_section_end();
}

void article_reader::skip_references() {
	copy_to_section_end();
}


void article_reader::skip_external_links() {
	copy_to_section_end();
}

void article_reader::read_notes() {

}

void article_reader::reconstruct_comment() {
	static const char *COMMENT_TAG_START = "<!--";
	static const char *COMMENT_TAG_END = "-->";


//	time_t t = time(0);
//	tm* lt = localtime(t);
//	char date[11];
//	sprintf(date, "%02d/%02d/%04d", lt->tm_mday, lt->tm_mon + 1, lt->year +
//	1900);


	start = strstr(current, COMMENT_TAG_START);
	if (start != NULL) {
//		start += strlen(COMMENT_TAG_START);
		end = strstr(start, COMMENT_TAG_END);
		if (end != NULL) {
			end += strlen(COMMENT_TAG_END);

//			start = strchr(start, '"');
//			++start;
//			end =  strchr(start, '"');
		}
	}

	if (start != NULL) {
		copy_to_current(current, start);
		create_comment();
		current = start;

		if (end != NULL) {
			current = end;
		}
		else {
			string msg = string("The article is not well-formed in the comment: ") + file_path;
			throw msg.c_str();
		}
	}
	else {
		create_comment();
	}
}

void article_reader::create_comment() {
	static const char *COMMENT_TEMPLATE = "<!-- generated by CROSSLINK/Translator with Google Translate, [EECS, SEF@QUT] on %s -->\n";
	const int MAXLEN = 80;
	char s[MAXLEN];
	time_t t = time(0);
	strftime(s, MAXLEN, "%d/%m/%Y %H:%M:%S", localtime(&t));
	string datetime(s);
	sprintf(s, COMMENT_TEMPLATE, datetime.c_str());
	writer->fill(s);
}

void article_reader::init_token() {
	current_token.start = NULL;
	current_token.length = 0;

	start = NULL;
	end = NULL;
}

void article_reader::read_section() {
	static const char *SECTION_TAG_START = "<sec>";
	static const char *NOTES_TEXT = "Notes";
	static const char *REFERENCES_TEXT = "References";
	static const char *EXTERNAL_LINKS_TEXT = "Externallinks";

//	const char *sec_start;
	if (sec_start == NULL || (next_section != NULL && current > next_section)) {
		if (next_section != NULL) {
			sec_start = next_section;
		}
		else {
			sec_start = strstr(current, SECTION_TAG_START);
		}

		copy_to_current(current, sec_start);
		current = sec_start;

		if (sec_start != NULL) {
			next_section = strstr(sec_start + strlen(SECTION_TAG_START), SECTION_TAG_START);
			// the first st is the section title of current section
			read_element_text("st");
			current_tag.erase(remove_if(current_tag.begin(), current_tag.end(), (int(*)(int))isspace), current_tag.end());
			if (strncasecmp(current_tag.c_str(), NOTES_TEXT, strlen(NOTES_TEXT)) == 0)
				progress = NOTES; //skip_notes();
			else if ((strncasecmp(current_tag.c_str(), REFERENCES_TEXT, strlen(REFERENCES_TEXT)) == 0))
				progress = REFERENCES; //skip_references();
			else if (strncasecmp(current_tag.c_str(), EXTERNAL_LINKS_TEXT, strlen(EXTERNAL_LINKS_TEXT)) == 0)
				progress = EXTERNAL_LINKS; //skip_external_links();
			else {
				if (current_token.length != 0)
					break;

			}
		}
	}
	else {
		read_para();
	}
}


/*
 * current version skip the table
 * const char *p_start, const char *p_end
 */
void article_reader::read_para() {
	read_element_text("p");
	if (current_token.length > 0)
		string_clean(current_token);
}

void article_reader::read_element_text(const char* tag_name) {
	string tag_start;
	string tag_end;

	current_tag = tag_name;

	if (tag_name != NULL) {
		tag_start = string("<") + tag_name + string(">");
		tag_end = string("</") + tag_name + string(">");;
	}
	else {
		tag_start = string("<");
		tag_end = string("<");
	}

	start = strstr(current, tag_start.c_str());
	if (start != NULL) {
		start += strlen(tag_start.c_str());

		if (start == "<") {
			start = strchr(++start, '>');
			if (start != NULL) {
				++start;
				while (isspace(*start))
					++start;
			}
			else {
				string msg = string("The article is not well-formed, missing < or >: ") + file_path;
				throw msg.c_str();
			}
		}

		current_token.start = start;
		copy_to_current(current, start);
		previous = current = start;

		end = strstr(start, tag_end.c_str());
		if (end != NULL) {
			previous = current;
			current = end += strlen(tag_end.c_str());
			current_token.length = end - start;
		}
	}

	while (current_token.length > 0 && isspace(current_token.start[current_token.length -1]))
		current_token.length--;
}

void article_reader::wrap_up_to_body() {
	static const char *BODY_TAG_START = "<bdy>";

	start = strstr(current, BODY_TAG_START);
	if (start != NULL) {
//		start += strlen(BODY_TAG_START);
//		while (isspace(*start))
//			++start;

		current = start;
		copy_to_current(previous, current);
		previous = current;
	}
	else {
		string msg = string("The article is not well-formed in the <bdy>: ") + file_path;
		throw msg.c_str();
	}
}

void article_reader::wrap_up_to_end() {
	writer->fill(current);
}

void article_reader::copy_to_current(const char *start, const char *end) {
	writer->fill(start, end - start);
}

void article_reader::copy_to_section_end() {

	static const char *SECTION_TAG_END = "</sec>";
	const char *section_end = NULL;
	if (start != NULL) {
		section_end = strstr(start, SECTION_TAG_END);
		if (section_end != NULL) {
			section_end += strlen(SECTION_TAG_END);
			copy_to_current(start, section_end);
			current = section_end;
		}
	}
}









