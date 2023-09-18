cmake_minimum_required(VERSION 3.22)
project(ex4_noam_susman)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex4_noam_susman
        Activation.cpp
        Activation.h
        Dense.cpp
        Dense.h
        main.cpp
        Matrix.cpp
        Matrix.h
        MlpNetwork.cpp
        MlpNetwork.h)

add_executable(ex4_tests
        Activation.cpp
        Activation.h
        Dense.cpp
        Dense.h
        matrix_tests.cpp
        Matrix.cpp
        Matrix.h
        MlpNetwork.cpp
        MlpNetwork.h)

add_executable(ex4_presub
        Activation.cpp
        Activation.h
        Dense.cpp
        Dense.h
        presubmit.cpp
        Matrix.cpp
        Matrix.h
        MlpNetwork.cpp
        MlpNetwork.h)

add_executable(ex4_tests_oryan
        ex4_test/ex4_tests/ex4_tests/main.cpp
        ex4_test/ex4_tests/ex4_tests/oh_tests_exceptions.cpp
        ex4_test/ex4_tests/ex4_tests/api/Matrix.cpp
        ex4_test/ex4_tests/ex4_tests/api/Dense.cpp
        ex4_test/ex4_tests/ex4_tests/api/MlpNetwork.cpp
        ex4_test/ex4_tests/ex4_tests/api/Activation.cpp)

add_executable(play play.cpp)
