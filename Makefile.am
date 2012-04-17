AM_CPPFLAGS = -std=c++0x  -pedantic -I $(srcdir)/include -I/home/monfee/workspace/stpl
AM_LDFLAGS = @LIBS@
#LIB_UNISEG = @LIB_UNISEG@

SOURCE_DIR = src
TEST_DIR = test
UTILS_DIR = utils

noinst_HEADERS = 
	
includes= 
		
inst_PROGRAMS = 
instdir = /usr/bin

libgoogle_translate_sources = \
	$(SOURCE_DIR)/sys_file.cpp \
	$(SOURCE_DIR)/sys_files.cpp \
	$(SOURCE_DIR)/google_translator.cpp \
	$(SOURCE_DIR)/google_research_translator.cpp \
	$(SOURCE_DIR)/webpage_retriever.cpp

lib_LTLIBRARIES = libgoogle_translate.la

libgoogle_translate_la_SOURCES = $(libgoogle_translate_sources)
libgoogle_translate_la_LIBADD = -ldl -lpthread
libgoogle_translate_la_LIBFLAGS = 
		
test_PROGRAMES = test_parse_translation		
		
noinst_PROGRAMS = corpus_translator google_translate $(test_PROGRAMES)

corpus_translator_SOURCES = \
	$(libgoogle_translate_sources) \
	$(SOURCE_DIR)/corpus_translator.cpp
	
corpus_translator_LDADD = -lpthread -lcurl 
#corpus_translator_CFLAGS = $(AM_CFLAGS) $(AM_CXXFLAGS) 
corpus_translator_DEPENDENCIES = libgoogle_translate.la

google_translate_SOURCES = \
	$(libgoogle_translate_sources) \
	$(TEST_DIR)/google_translate.cpp
						
google_translate_LDADD = -lpthread -lcurl 
#google_translate_CFLAGS = $(AM_CFLAGS) $(AM_CXXFLAGS)
google_translate_DEPENDENCIES = libgoogle_translate.la

test_parse_translation_SOURCES = \
	$(libgoogle_translate_sources) \
	$(TEST_DIR)/test_parse_translation.cpp
						
test_parse_translation_LDADD = 
#test_parse_translation_CFLAGS = $(AM_CFLAGS) $(AM_CXXFLAGS)
test_parse_translation_DEPENDENCIES = libgoogle_translate.la

