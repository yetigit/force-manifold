cmake_minimum_required(VERSION 3.2)
project(force_manifold)

find_package(OpenVDB REQUIRED)

file(GLOB SRC src/*.h src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC 3rd/glm)

target_link_libraries(${PROJECT_NAME} OpenVDB::openvdb)

if (MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE /openmp)
endif()