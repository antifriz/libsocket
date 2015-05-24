LIB_NAME = InetWrappersCxx
INC_FOLDER = ../include
LIB_A_FOLDER = ../lib

LIBRARY = $(LIB_A_FOLDER)/lib$(LIB_NAME).a

MYSTL_INC_FOLDER= ../../mystl/include
SOURCE!= ls */*.cc

#INTERNAL_HEADERS!= ls */*.h
EXTERNAL_HEADERS!= ls $(INC_FOLDER)/*/*/*.h
#EXTERNAL_HEADERS = $(EXTERNAL_HEADERS_REL:%=$(INC_FOLDER)/%)
HEADERS = $(INTERNAL_HEADERS) $(EXTERNAL_HEADERS) 

CXX = g++
CXXFLAGS = -Wall -g  -I$(INC_FOLDER) -I$(MYSTL_INC_FOLDER)
ARFLAGS = cr

OBJECTS = ${SOURCE:.cc=.o}

$(LIBRARY): $(OBJECTS)
	$(MAKE) -C ../../mystl/src
	$(AR) $(ARFLAGS) $(LIBRARY) $(OBJECTS)

.cc.o: $(HEADERS)
	$(CXX) $(CXXFLAGS) $< -c -o $@

clean:
	$(MAKE) -C ../../mystl/src clean
	-rm -f $(LIBRARY) $(OBJECTS) *.core

