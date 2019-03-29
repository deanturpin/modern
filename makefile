all: tmp tmp/main.o
	clang-format -i main.cpp
	echo '```c++' > readme.md
	cat main.cpp >> readme.md
	echo '```' >> readme.md
	tmp/main.o

CXX = g++-8

CXXFLAGS = --std=c++2a --all-warnings --extra-warnings --pedantic \
	-Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor

tmp/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< -lpthread

tmp:
	mkdir $@

clean:
	rm -rf tmp
