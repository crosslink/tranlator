AM_CPPFLAGS = -std=c++0x  -pedantic -I $(srcdir)/include -I/home/monfee/workspace/stpl
AM_LDFLAGS = @LIBS@ -L/usr/lib64/mysql @MYSQL_LIBS@
#LIB_UNISEG = @LIB_UNISEG@

SOURCE_DIR = src
TEST_DIR = test
UTILS_DIR = utils
SQL_DIR = sql

noinst_HEADERS = 
	
includes= 
		
inst_PROGRAMS = 
instdir = /usr/bin

libgoogle_translate_headers = \
	$(SOURCE_DIR)/translation_write_exception.h \
	$(SOURCE_DIR)/urlcode.h \
	$(SOURCE_DIR)/ant_link_parts.h \
	$(SOURCE_DIR)/string_utils.h \
	$(SOURCE_DIR)/pattern_singleton.h \
	$(SOURCE_DIR)/article.h \
	$(SOURCE_DIR)/article_reader.h \
	$(SOURCE_DIR)/article_writer.h \
	$(SOURCE_DIR)/language.h \
	$(SOURCE_DIR)/corpus.h \
	$(SOURCE_DIR)/input_manager.h \
	$(SOURCE_DIR)/database_mysql.h \
	$(SOURCE_DIR)/sys_file.h \
	$(SOURCE_DIR)/sys_files.h \
	$(SOURCE_DIR)/google_translator.h \
	$(SOURCE_DIR)/google_research_translator.h \
	$(SOURCE_DIR)/webpage_retriever.h
	
libgoogle_translate_sources = \
	$(SOURCE_DIR)/translation_write_exception.cpp \
	$(SOURCE_DIR)/urlcode.cpp \
	$(SOURCE_DIR)/article.cpp \
	$(SOURCE_DIR)/article_reader.cpp \
	$(SOURCE_DIR)/article_writer.cpp \
	$(SOURCE_DIR)/language.cpp \
	$(SOURCE_DIR)/corpus.cpp \
	$(SOURCE_DIR)/input_manager.cpp \
	$(SOURCE_DIR)/database_mysql.cpp \
	$(SOURCE_DIR)/sys_file.cpp \
	$(SOURCE_DIR)/sys_files.cpp \
	$(SOURCE_DIR)/google_translator.cpp \
	$(SOURCE_DIR)/google_research_translator.cpp \
	$(SOURCE_DIR)/webpage_retriever.cpp

lib_LTLIBRARIES = libgoogle_translate.la

libgoogle_translate_ladir = /usr/include
libgoogle_translate_la_SOURCES = $(libgoogle_translate_sources)
libgoogle_translate_la_HEADERS = $(libgoogle_translate_headers)
libgoogle_translate_la_LIBADD = -lpthread -lcurl 
libgoogle_translate_la_LIBFLAGS = 
		
test_PROGRAMES = test_parse_translation	test_database test_spaces_removal
		
noinst_PROGRAMS = corpus_translator google_translate reset_article $(test_PROGRAMES)

corpus_translator_SOURCES = \
	$(SOURCE_DIR)/corpus_translator.cpp
corpus_translator_LDADD = -lpthread -lcurl -lgoogle_translate
corpus_translator_DEPENDENCIES = libgoogle_translate.la
corpus_translator_LDFLAGS = -static

google_translate_SOURCES = $(TEST_DIR)/google_translate.cpp
google_translate_LDADD = -lpthread -lcurl -lgoogle_translate
google_translate_DEPENDENCIES = libgoogle_translate.la
google_translate_LDFLAGS = -static

google_translate_SOURCES = $(TEST_DIR)/google_translate.cpp
google_translate_LDADD = -lpthread -lcurl -lgoogle_translate
google_translate_DEPENDENCIES = libgoogle_translate.la
google_translate_LDFLAGS = -static

test_parse_translation_SOURCES = $(TEST_DIR)/test_parse_translation.cpp
test_parse_translation_LDADD = -lgoogle_translate
test_parse_translation_DEPENDENCIES = libgoogle_translate.la
test_parse_translation_LDFLAGS = -static

test_database_SOURCES = $(TEST_DIR)/test_database.cpp
test_database_LDADD = -lgoogle_translate
test_database_DEPENDENCIES = libgoogle_translate.la
test_database_LDFLAGS = -static

test_spaces_removal_SOURCES = $(TEST_DIR)/test_spaces_removal.cpp

HEADER_FILES = $(SOURCE_DIR)/*.h
SQL_FILES = $(SQL_DIR)/*.sql

EXTRA_DIST = \
	makefile \
	files/test.xml \
	files/google_translate_research_api_example_result.xml \
	sql/database.sql \
	sql/others.sql \
	test_key.sh \
	update_key.sh
