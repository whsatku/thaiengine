CXX ?= g++
CXXFLAGS ?= -std=c++11 -Ofast -march=native -mtune=native -fno-exceptions -funsafe-loop-optimizations -fomit-frame-pointer -DFARMHASH_NO_CXX_STRING -DFARMHASH_LITTLE_ENDIAN
INPUTS := farmhash.o fasttextinputreader.cc

all: fasttextinputreader

farmhash.o: farmhash.cc
	$(CXX) $(CXXFLAGS) -c -flto -o $@ $<

fasttextinputreader: $(INPUTS)
	$(CXX) $(CXXFLAGS) -fprofile-use -fwhole-program -o $@ $(INPUTS)

profile: $(INPUTS)
	$(CXX) $(CXXFLAGS) -fprofile-generate -fwhole-program -o fasttextinputreader-profile $(INPUTS)

noprofile: $(INPUTS)
	$(CXX) $(CXXFLAGS) -fwhole-program -o fasttextinputreader $(INPUTS)

clean:
	rm fasttextinputreader fasttextinputreader-profile farmhash.o || true