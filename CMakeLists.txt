cmake_minimum_required(VERSION 3.27)
project(LOP_VND)

set(CMAKE_CXX_STANDARD 23)

add_executable(LOP_VND src/main.cpp
        src/skeleton/instance/instance.cpp
        src/algorithms/initialisation/random_permutation.cpp
        src/algorithms/initialisation/cw_heuristic.cpp
        src/algorithms/operations/exchange.cpp
        src/algorithms/operations/insert.cpp
        src/algorithms/operations/transpose.cpp
        src/algorithms/pivots/best_improvement.cpp
        src/algorithms/pivots/first_improvement.cpp
        src/skeleton/config/configuration.cpp
        src/algorithms/solution/solution.cpp
        src/algorithmType/iterative/iterative.cpp
        src/skeleton/utilities/utilities.cpp
        src/algorithmType/vnd/vnd.cpp
        src/skeleton/output/output.cpp
        mourir.cpp
)
