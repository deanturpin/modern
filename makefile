objects = $(patsubst %.cpp, tmp/%.o, $(wildcard *.cpp))

all: tmp
	$(MAKE) -j $(shell nproc) $(objects)
	clang-format -i main.cpp
	echo '```c++' > readme.md
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
