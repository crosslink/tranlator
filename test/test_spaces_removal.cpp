#include "../src/string_utils.h"

#include <string>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	const char *TEST_STRING = "afdsakwwe esa8dfwe    aefw were vsfg wer wedfsdff  "
			"fwererw '8@E asjiefw    hsfs         4月25日       ——"
"月食       。"
              ""
""
 ""
"8月20日       ——"
"英格兰       和"
"苏格兰       签定和约。"
                      ""
""
 ""
"11月3日       ——"
"日食       。   ;"
""
"";
	std::string result;
	remove_redundant_spaces(TEST_STRING, result);
	cout << result;
	return 0;
}
