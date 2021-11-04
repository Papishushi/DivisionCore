cmake_minimum_required(VERSION 3.20)
project(DivisionCore)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DivisionCore
        Behaviour.cpp
        Behaviour.h
        Component.cpp
        Component.h
        Entity.cpp
        Entity.h
        GameObject.cpp
        GameObject.h
        Object.cpp
        Object.h
        RunningBehaviour.cpp
        RunningBehaviour.h
        Transform.cpp
        Transform.h
        Vector2.h
        Vector3Euler.h
        Scene.cpp
        Scene.h
        MessageArgs.h
        PrimitiveType.h
        HideFlags.h
        GameController.h
        EventHandler.cpp
        EventHandler.h
        EventObserver.h
        EventEmitter.h
        Dictionary.h main.cpp)
