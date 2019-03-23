objects = $(patsubst %.cpp, tmp/%.o, $(wildcard *.cpp))

all: tmp
	$(MAKE) -j $(shell nproc) $(objects)
	clang-format -i main.cpp
	cat _readme.md > readme.md
	echo '```c++' >> readme.md
	cat main.cpp >> readme.md
	echo '```' >> readme.md

CXX = g++-8

FLAGS = --std=c++2a --all-warnings --extra-warnings -Wno-address \
	-Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor \
	-Wno-unused-variable

tmp/%.o: %.cpp
	$(CXX) $(FLAGS) -o $@ $< -lstdc++fs -lpthread
	./$@

tmp:
	mkdir $@

clean:
	rm -rf tmp
