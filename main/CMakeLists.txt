
if(ESP_PLATFORM)
    idf_component_register( SRCS "main.cpp"
                            REQUIRES driver
                            INCLUDE_DIRS "." "include" $ENV{CADMIUM})
    idf_component_register( SRCS "TestCases/deck_test.cpp"
                            REQUIRES driver
                            INCLUDE_DIRS "." "include" $ENV{CADMIUM})
    idf_component_register( SRCS "TestCases/controller_lose_test.cpp"
                            REQUIRES driver
                            INCLUDE_DIRS "." "include" $ENV{CADMIUM})
    idf_component_register( SRCS "TestCases/controller_win_test.cpp"
                            REQUIRES driver
                            INCLUDE_DIRS "." "include" $ENV{CADMIUM})
    idf_component_register( SRCS "TestCases/controller_tie_test.cpp"
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
    add_executable("deck_test" TestCases/deck_main.cpp)
    add_executable("controller_lose_test" TestCases/controller_lose_main.cpp)
    add_executable("controller_win_test" TestCases/controller_win_main.cpp)
    add_executable("controller_tie_test" TestCases/controller_tie_main.cpp)
    add_executable("threshold_c_test" TestCases/threshold_c_test.cpp)
    add_executable("threshold_d_test" TestCases/threshold_d_test.cpp)
    add_executable("hand_cumulative" TestCases/hand_test_cumulative.cpp)
    add_executable("hand_illegal" TestCases/hand_test_illegal.cpp)

    # Add required libraries and include directories
    target_include_directories(${projectName} PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories("deck_test" PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories("controller_lose_test" PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories("controller_win_test" PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories("controller_tie_test" PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories("threshold_c_test" PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories("threshold_d_test" PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories("hand_cumulative" PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories("hand_illegal" PRIVATE "." "include" $ENV{CADMIUM})

    # Non-ESP32 specific compile options
    target_compile_options(${projectName} PUBLIC -std=gnu++2b)
    target_compile_options("deck_test" PUBLIC -std=gnu++2b)
    target_compile_options("controller_lose_test" PUBLIC -std=gnu++2b)
    target_compile_options("controller_win_test" PUBLIC -std=gnu++2b)
    target_compile_options("controller_tie_test" PUBLIC -std=gnu++2b)
    target_compile_options("threshold_c_test" PUBLIC -std=gnu++2b)
    target_compile_options("threshold_d_test" PUBLIC -std=gnu++2b)
    target_compile_options("hand_cumulative" PUBLIC -std=gnu++2b)
    target_compile_options("hand_illegal" PUBLIC -std=gnu++2b)
endif()
