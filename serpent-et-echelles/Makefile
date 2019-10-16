# Author : Drumurd
# Description : a very simple makefile for little projects in c++


CC := g++ # This is the main compiler
SRCDIR := src
INCDIR := include
BUILDDIR := obj
TARGET := bin/build
 
SRCEXT := cpp
INCEXT := hpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
INCLUDE := $(shell find $(INCDIR) -type f -name *.$(INCEXT))
CFLAGS := -g -Wall
LIB := -lsfml-graphics -lsfml-window -lsfml-system
INC := -I $(INCDIR)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(SRCDIR)/%.$(SRCEXT): $(INCDIR)/%.$(INCEXT)

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR)/ $(TARGET)

run: $(TARGET)
	@$(TARGET)

.PHONY: clean
