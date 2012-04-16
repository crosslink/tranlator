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
		
noinst_PROGRAMS = corpus_translator google_translate 

corpus_translator_SOURCES = \
	$(SOURCE_DIR)/sys_file.cpp \
	$(SOURCE_DIR)/sys_files.cpp \
	$(SOURCE_DIR)/google_translator.cpp \
	$(SOURCE_DIR)/webpage_retriever.cpp \
	$(SOURCE_DIR)/corpus_translator.cpp
	
corpus_translator_LDADD = -lpthread -lcurl 
corpus_translator_CFLAGS = $(AM_CFLAGS) $(AM_CXXFLAGS) 

google_translate_SOURCES = \
	$(SOURCE_DIR)/sys_file.cpp \
	$(SOURCE_DIR)/google_translator.cpp \
	$(SOURCE_DIR)/webpage_retriever.cpp \
	$(TEST_DIR)/google_translate.cpp
						
google_translate_LDADD = -lpthread -lcurl 
google_translate_CFLAGS = $(AM_CFLAGS) $(AM_CXXFLAGS)