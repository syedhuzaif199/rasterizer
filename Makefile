CXX = g++
CXXFLAGS = -I src/utils -I src/geometry -I libs/raylib/src
LDFLAGS = -L libs/raylib/src -lraylib 
SRC = src/main.cpp src/utils/Vector.cpp src/utils/Matrix.cpp src/geometry/Mesh.cpp
TESTSRC = src/test.cpp src/utils/Vector.cpp src/utils/Matrix.cpp src/geometry/Mesh.cpp
BUILD_DIR = build

all: main test


main: $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/main $(SRC) $(LDFLAGS)

test: $(TESTSRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/test $(TESTSRC) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)
