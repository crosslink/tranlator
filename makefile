
SOURCE_DIR=src

TARGET = translator

CPPFLAGS = -I/home/monfee/workspace/stpl -std=c++0x

DEBUGMODE = 1

SOURCES = \
	$(SOURCE_DIR)/google_translator.cpp \
	$(SOURCE_DIR)/webpage_retriever.cpp \
	$(SOURCE_DIR)/translator.cpp

LIBRARIES = curl

include ~/src/edam.mk
