CXX = g++
CXXFLAGS = -I src/utils -I src/geometry -I libs/raylib/src
LDFLAGS = -L libs/raylib/src -lraylib
ifeq ($(OS),Windows_NT)
	LDFLAGS += -lgdi32 -lwinmm
endif
BUILD_DIR = build

.PHONY: all clean

all: $(BUILD_DIR)/main $(BUILD_DIR)/test

$(BUILD_DIR)/Matrix.o: src/utils/Matrix.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c src/utils/Matrix.cpp -o $(BUILD_DIR)/Matrix.o

$(BUILD_DIR)/Vector.o: src/utils/Vector.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c src/utils/Vector.cpp -o $(BUILD_DIR)/Vector.o

$(BUILD_DIR)/Mesh.o: src/geometry/Mesh.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c src/geometry/Mesh.cpp -o $(BUILD_DIR)/Mesh.o

$(BUILD_DIR)/main: src/main.cpp $(BUILD_DIR)/Matrix.o $(BUILD_DIR)/Vector.o $(BUILD_DIR)/Mesh.o
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/main src/main.cpp $(BUILD_DIR)/Matrix.o $(BUILD_DIR)/Vector.o $(BUILD_DIR)/Mesh.o $(LDFLAGS)

$(BUILD_DIR)/test: src/test.cpp $(BUILD_DIR)/Matrix.o $(BUILD_DIR)/Vector.o $(BUILD_DIR)/Mesh.o
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/test src/test.cpp $(BUILD_DIR)/Matrix.o $(BUILD_DIR)/Vector.o $(BUILD_DIR)/Mesh.o $(LDFLAGS)


clean:
	rm -rf $(BUILD_DIR)
