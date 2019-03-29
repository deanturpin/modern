objects = $(patsubst %.cpp, tmp/%.o, $(wildcard *.cpp))

all: tmp tmp/main.o
	clang-format -i main.cpp
	$(MAKE) -j $(shell nproc) $(objects)
	echo '```c++' > readme.md
	cat main.cpp >> readme.md
	echo '```' >> readme.md
	tmp/main.o

CXX = g++-8

FLAGS = --std=c++2a --all-warnings --extra-warnings --pedantic \
	-Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor

tmp/%.o: %.cpp
	$(CXX) $(FLAGS) -o $@ $< -lstdc++fs -lpthread

tmp:
	mkdir $@

clean:
	rm -rf tmp
