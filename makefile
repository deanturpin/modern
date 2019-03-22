objects = $(patsubst %.cpp, tmp/%.o, $(wildcard *.cpp))

all: tmp
	$(MAKE) -j $(shell nproc) $(objects)
	echo 'This is generated from [main.cpp](the source) when it compiles successfully.' > readme.md
	echo '```c++' >> readme.md
	cat main.cpp >> readme.md
	echo '```' >> readme.md

CXX = g++-8

FLAGS = --std=c++2a --all-warnings --extra-warnings -Wno-address \
	-Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor

tmp/%.o: %.cpp
	$(CXX) $(FLAGS) -o $@ $< -lstdc++fs -lpthread
	./$@

tmp:
	mkdir $@

clean:
	rm -rf tmp
