CXX ?= g++
CXXFLAGS ?= -std=c++11 -Ofast -march=native -mtune=native -fno-exceptions -funsafe-loop-optimizations -fomit-frame-pointer -DFARMHASH_NO_CXX_STRING -DFARMHASH_LITTLE_ENDIAN -flto
INPUTS := farmhash.o fasttextinputreader.cc

all: fasttextinputreader

farmhash.o: farmhash.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

fasttextinputreader: $(INPUTS)
	$(CXX) $(CXXFLAGS) -fprofile-use -o $@ $(INPUTS)
	strip -s $@

profile: $(INPUTS)
	$(CXX) $(CXXFLAGS) -fprofile-generate -o fasttextinputreader-profile $(INPUTS)

noprofile: $(INPUTS)
	$(CXX) $(CXXFLAGS) -o fasttextinputreader $(INPUTS)

clean:
	rm fasttextinputreader fasttextinputreader-profile farmhash.o || true
