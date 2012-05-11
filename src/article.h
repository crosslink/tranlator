/*
 * article.h
 *
 *  Created on: Apr 24, 2012
 *      Author: monfee
 */

#ifndef ARTICLE_H_
#define ARTICLE_H_

#include <string>

class article {
public:
	enum {WRITE_TO_DATABASE = 1, WRITE_TO_DISK = 2};

    /*, WRITE_TO_DISK_AND_DATABASE = 3*/
protected:
    std::string file_path;
    std::string name;
    std::string ext;
    char* content;
    long doc_id;

    std::string source_lang;
    std::string target_lang;

public:
    article();
    article(const char* file);
    virtual ~article();
    virtual void read();
    virtual void write();
    virtual void write(int write_type);
    virtual void write(const char* content);
    virtual void write(const char* content, const char* path, int write_type);
    static std::string id2dir(unsigned long  id);
    static int file2id(const char* file);
    std::string file2name(const char* file);

    std::string get_source_lang() const;
    void set_source_lang(std::string source_lang);
    std::string get_target_lang() const;
    void set_target_lang(std::string target_lang);

    long get_doc_id();
    void set_doc_id(long  id);

};

#endif /* ARTICLE_H_ */
