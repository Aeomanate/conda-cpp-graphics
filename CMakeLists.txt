cmake_minimum_required(VERSION 3.15)
project(cpp-graphics)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED)
find_package(SFML REQUIRED)
find_package(GTest REQUIRED)
find_package(RapidJSON REQUIRED)

include_directories(
	${Boost_INCLUDE_DIRS} 
	${SFML_INCLUDE_DIRS}
       	${GTest_INCLUDE_DIRS} 
	${RapidJSON_INCLUDE_DIRS})

add_executable(cpp-graphics main.cpp)

target_link_libraries(
	cpp-graphics 
	${Boost_LIBRARIES} 
	sfml-graphics sfml-window sfml-system 
	GTest::GTest GTest::Main)

enable_testing()
add_test(NAME cpp-graphics-test COMMAND cpp-graphics)

