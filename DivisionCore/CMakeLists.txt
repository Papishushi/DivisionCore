cmake_minimum_required(VERSION 3.20)
project(DivisionCore)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DivisionCore
        Behaviour.h
        Component.cpp
        Component.h
        Entity.h
        GameObject.cpp
        GameObject.h
        Object.h
        RunningBehaviour.h
        Transform.h
        Vector2.h
        Vector3Euler.h
        Scene.h Behaviour.cpp Entity.cpp Object.cpp RunningBehaviour.cpp Scene.cpp Transform.cpp Vector2.cpp Vector3Euler.cpp)
