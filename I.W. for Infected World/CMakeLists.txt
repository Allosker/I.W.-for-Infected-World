cmake_minimum_required(VERSION 3.28)
project(IW_for_Infected_World LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SourceFiles "code_files/*.cpp")
add_executable(main ${SourceFiles} "code_files/Utilities/visual_effects/LifeBar.h"   "code_files/entities/collectibles/Collectible.cpp" "code_files/entities/collectibles/Collectible.h")
target_include_directories(main PUBLIC "code_files")
target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)
target_compile_definitions(main PRIVATE ASSETS_DIR="${PROJECT_SOURCE_DIR}/assets")


# target_compile_definitions(main PRIVATE ASSETS_DIR="./assets") <- replace line 20 with this if you want to share it to friends or other people
# target_compile_definitions(main PRIVATE ASSETS_DIR"${PROJECT_SOURCE_DIR}/assets") <- this if you only want your PC to be able to find the specified files