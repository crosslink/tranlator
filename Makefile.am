AM_CPPFLAGS = -std=c++0x  -pedantic -I $(srcdir)/include
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
	$(SOURCE_DIR)/google_translator.cpp \
	$(SOURCE_DIR)/webpage_retriever.cpp \
	$(SOURCE_DIR)/corpus_translator.cpp
corpus_translator_LDADD = -lpthread -lcurl 

google_translate_SOURCES = $(TEST_DIR)/google_translate.cpp
google_translate_LDADD = -lpthread -lcurl 