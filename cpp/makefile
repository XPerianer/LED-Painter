RGB_INCDIR= ../matrix_library/include
RGB_LIBDIR= ../matrix_library/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

CXX := g++
CXXFLAGS := -Wall -O3 -g -std=c++0x
OBJECTS := painter.o
BINARIES := painter_bin

painter.app : $(OBJECTS) $(RGB_LIBRARY)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

readRGBFile.app :  readRGBFile.o $(RGB_LIBRARY)
	$(CXX) readRGBFile.o -o $@ $(LDFLAGS)


# (FYI: Make sure, there is a TAB-character in front of the $(MAKE))
$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR)

painter.o : painter.cpp painter.h
	$(CXX) $(CXXFLAGS) -I$(RGB_INCDIR)  painter.cpp -c -o  $@

readRGBFile.o : readRGBFile.cpp readRGBFile.h
		$(CXX) $(CXXFLAGS) -I$(RGB_INCDIR)  readRGBFile.cpp -c -o  $@
