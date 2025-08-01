CXX = g++
CXXFLAGS = -I src/utils -I src/geometry -I libs/raylib/src
LDFLAGS = -L libs/raylib/src -lraylib
ifeq ($(OS),Windows_NT)
	LDFLAGS += -lgdi32 -lwinmm
endif
BUILD_DIR = build
MAIN_BUILD = build/main
ifeq ($(OS),Windows_NT)
	MAIN_BUILD = build/main.exe
endif
TEST_BUILD = build/test
ifeq ($(OS),Windows_NT)
	TEST_BUILD = build/test.exe
endif
RAYLIB_DIR = libs/raylib/src
LIBRAYLIB = $(RAYLIB_DIR)/libraylib.a

.PHONY: all clean

all: $(LIBRAYLIB) $(MAIN_BUILD) $(TEST_BUILD)

$(LIBRAYLIB):
	@echo "Building Raylib static library..."
	$(MAKE) -C $(RAYLIB_DIR)

$(BUILD_DIR)/Matrix.o: src/utils/Matrix.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c src/utils/Matrix.cpp -o $(BUILD_DIR)/Matrix.o

$(BUILD_DIR)/Vector.o: src/utils/Vector.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c src/utils/Vector.cpp -o $(BUILD_DIR)/Vector.o

$(BUILD_DIR)/Mesh.o: src/geometry/Mesh.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c src/geometry/Mesh.cpp -o $(BUILD_DIR)/Mesh.o

$(MAIN_BUILD): src/main.cpp $(BUILD_DIR)/Matrix.o $(BUILD_DIR)/Vector.o $(BUILD_DIR)/Mesh.o
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/main src/main.cpp $(BUILD_DIR)/Matrix.o $(BUILD_DIR)/Vector.o $(BUILD_DIR)/Mesh.o $(LDFLAGS)

$(TEST_BUILD): src/test.cpp $(BUILD_DIR)/Matrix.o $(BUILD_DIR)/Vector.o $(BUILD_DIR)/Mesh.o
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/test src/test.cpp $(BUILD_DIR)/Matrix.o $(BUILD_DIR)/Vector.o $(BUILD_DIR)/Mesh.o $(LDFLAGS)


clean:
	rm -rf $(BUILD_DIR)
