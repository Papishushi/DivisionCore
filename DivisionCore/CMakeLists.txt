cmake_minimum_required(VERSION 3.20)
project(DivisionCore)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DivisionCore
        main.cpp
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
        Scene.cpp
        Scene.h
        MessageArgs.cpp
        MessageArgs.h
        PrimitiveType.cpp
        PrimitiveType.h
        HideFlags.cpp
        HideFlags.h
        GameController.cpp
        GameController.h
        EventHandler.cpp
        EventHandler.h
        EventObserver.cpp
        EventObserver.h
        EventEmitter.cpp
        EventEmitter.h
        Dictionary.cpp
        Dictionary.h
        Vector.cpp
        Vector.h
        Random.cpp
        Random.h
        Tile.cpp
        Tile.h Tilemap.cpp Tilemap.h)
