
if(ESP_PLATFORM)
    idf_component_register( SRCS "main.cpp"
                            REQUIRES driver
                            INCLUDE_DIRS "." "include" $ENV{CADMIUM})
    idf_component_register( SRCS "deck_test.hpp"
                            REQUIRES driver
                            INCLUDE_DIRS "." "include" $ENV{CADMIUM})
    idf_component_register( SRCS "controller_lose_test.hpp"
                            REQUIRES driver
                            INCLUDE_DIRS "." "include" $ENV{CADMIUM})
    idf_component_register( SRCS "controller_win_test.hpp"
                            REQUIRES driver
                            INCLUDE_DIRS "." "include" $ENV{CADMIUM})
    idf_component_register( SRCS "controller_tie_test.hpp"
                            REQUIRES driver
                            INCLUDE_DIRS "." "include" $ENV{CADMIUM})

    target_compile_options(${COMPONENT_LIB} PUBLIC -std=gnu++2b)
    target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
    target_compile_options(${COMPONENT_LIB} PRIVATE "-frtti")
    target_compile_options(${COMPONENT_LIB} PRIVATE "-fexceptions")
    # target_compile_options(${COMPONENT_LIB} PRIVATE "-DNO_LOGGING")
    # target_compile_options(${COMPONENT_LIB} PRIVATE "-DNO_LOG_STATE")
    # target_compile_options(${COMPONENT_LIB} PRIVATE "-DDEBUG_DELAY")
else()

    # Regular CMake project setup for non-ESP32
    add_executable(${projectName} main.cpp)
    add_executable("deck_test" deck_main.cpp)
    add_executable("controller_lose_test" controller_lose_main.cpp)
    add_executable("controller_win_test" controller_win_main.cpp)
    add_executable("controller_tie_test" controller_tie_main.cpp)

    # Add required libraries and include directories
    target_include_directories(${projectName} PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories("deck_test" PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories("controller_lose_test" PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories("controller_win_test" PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories("controller_tie_test" PRIVATE "." "include" $ENV{CADMIUM})

    # Non-ESP32 specific compile options
    target_compile_options(${projectName} PUBLIC -std=gnu++2b)
    target_compile_options("deck_test" PUBLIC -std=gnu++2b)
    target_compile_options("controller_lose_test" PUBLIC -std=gnu++2b)
    target_compile_options("controller_win_test" PUBLIC -std=gnu++2b)
    target_compile_options("controller_tie_test" PUBLIC -std=gnu++2b)
endif()
