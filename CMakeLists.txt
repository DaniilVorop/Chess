cmake_minimum_required(VERSION 3.26)
project(CourseWork)

set(CMAKE_CXX_STANDARD 17)
set(SFML_STATIC_LIBRARIES TRUE)

# определения операционной системы
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -mwindows")
    set(SFML_DIR "${CMAKE_CURRENT_BINARY_DIR}/SFML-2.6.0-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.0/lib/cmake/SFML")
else()
    # Для Linux
    set(SFML_DIR "${CMAKE_CURRENT_BINARY_DIR}/SFML-2.6.1-linux-gcc-64-bit/SFML-2.6.1/lib/cmake/SFML")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML 2.6 REQUIRED COMPONENTS graphics)

# Добавляем исполняемый файл

add_executable(PlayHostLinux
        Work/main.cpp
        Work/Board.cpp
        Work/Board.h
        Work/Figure.h
        Work/Coordinates.h
        Work/Pawn.h
        Work/Knight.cpp
        Work/Knight.h
        Work/Bishop.h
        Work/Rook.cpp
        Work/Rook.h
        Work/Queen.h
        Work/King.h
        Work/ImageBoard.h
        Work/Figure.cpp
        Work/Pawn.cpp
        Work/Bishop.cpp
        Work/Header.h
        Work/Queen.cpp
        Work/King.cpp
        Work/Game.cpp
        Work/Game.h
        Work/StockFish.cpp
        Work/StockFish.h
        Work/ImageMenu.h
        Work/Exceptions.h
        Work/MyDeque.h
        Work/Algorithms.h
        Work/Network.cpp
        Work/Network.h
)


add_executable(PlayClientLinux
        Work/main.cpp
        Work/Board.cpp
        Work/Board.h
        Work/Figure.h
        Work/Coordinates.h
        Work/Pawn.h
        Work/Knight.cpp
        Work/Knight.h
        Work/Bishop.h
        Work/Rook.cpp
        Work/Rook.h
        Work/Queen.h
        Work/King.h
        Work/ImageBoard.h
        Work/Figure.cpp
        Work/Pawn.cpp
        Work/Bishop.cpp
        Work/Header.h
        Work/Queen.cpp
        Work/King.cpp
        Work/Game.cpp
        Work/Game.h
        Work/StockFish.cpp
        Work/StockFish.h
        Work/ImageMenu.h
        Work/Exceptions.h
        Work/MyDeque.h
        Work/Algorithms.h
        Work/Network.cpp
        Work/Network.h
)

add_executable(PlayHostWindows
        Work/main.cpp
        Work/Board.cpp
        Work/Board.h
        Work/Figure.h
        Work/Coordinates.h
        Work/Pawn.h
        Work/Knight.cpp
        Work/Knight.h
        Work/Bishop.h
        Work/Rook.cpp
        Work/Rook.h
        Work/Queen.h
        Work/King.h
        Work/ImageBoard.h
        Work/Figure.cpp
        Work/Pawn.cpp
        Work/Bishop.cpp
        Work/Header.h
        Work/Queen.cpp
        Work/King.cpp
        Work/Game.cpp
        Work/Game.h
        Work/StockFish.cpp
        Work/StockFish.h
        Work/ImageMenu.h
        Work/Exceptions.h
        Work/MyDeque.h
        Work/Algorithms.h
        Work/Network.cpp
        Work/Network.h
)


add_executable(PlayClientWindows
        Work/main.cpp
        Work/Board.cpp
        Work/Board.h
        Work/Figure.h
        Work/Coordinates.h
        Work/Pawn.h
        Work/Knight.cpp
        Work/Knight.h
        Work/Bishop.h
        Work/Rook.cpp
        Work/Rook.h
        Work/Queen.h
        Work/King.h
        Work/ImageBoard.h
        Work/Figure.cpp
        Work/Pawn.cpp
        Work/Bishop.cpp
        Work/Header.h
        Work/Queen.cpp
        Work/King.cpp
        Work/Game.cpp
        Work/Game.h
        Work/StockFish.cpp
        Work/StockFish.h
        Work/ImageMenu.h
        Work/Exceptions.h
        Work/MyDeque.h
        Work/Algorithms.h
        Work/Network.cpp
        Work/Network.h
)


# Линкуем SFML к нашему исполняемому файлу
target_link_libraries(PlayClientLinux
        sfml-graphics)


target_link_libraries(PlayHostLinux
        sfml-graphics
)
target_link_libraries(PlayClientWindows
        ws2_32
        sfml-graphics)


target_link_libraries(PlayHostWindows
        ws2_32
        sfml-graphics
)
#target_link_libraries(Work sfml-graphics sfml-network sfml-audio sfml-window sfml-system)



#cmake_minimum_required(VERSION 3.26)
#project(CourseWork)
#
#set(CMAKE_CXX_STANDARD 17)
#
##set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
#set(SFML_STATIC_LIBRARIES TRUE)
#
#set(SFML_DIR "${CMAKE_CURRENT_BINARY_DIR}/SFML-2.6.1-linux-gcc-64-bit/SFML-2.6.1/lib/cmake/SFML")
#
#
#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
#
#find_package(SFML 2.6.0 REQUIRED COMPONENTS graphics)
#
#add_executable(PlayHost
#        Work/main.cpp
#        Work/Board.cpp
#        Work/Board.h
#        Work/Figure.h
#        Work/Coordinates.h
#        Work/Pawn.h
#        Work/Knight.cpp
#        Work/Knight.h
#        Work/Bishop.h
#        Work/Rook.cpp
#        Work/Rook.h
#        Work/Queen.h
#        Work/King.h
#        Work/ImageBoard.h
#        Work/Figure.cpp
#        Work/Pawn.cpp
#        Work/Bishop.cpp
#        Work/Header.h
#        Work/Queen.cpp
#        Work/King.cpp
#        Work/Game.cpp
#        Work/Game.h
#        Work/StockFish.cpp
#        Work/StockFish.h
#        Work/ImageMenu.h
#        Work/Exceptions.h
#        Work/MyDeque.h
#        Work/Algorithms.h
#        Work/Network.cpp
#        Work/Network.h
#)
#
#
#add_executable(PlayClient
#        Work/main.cpp
#        Work/Board.cpp
#        Work/Board.h
#        Work/Figure.h
#        Work/Coordinates.h
#        Work/Pawn.h
#        Work/Knight.cpp
#        Work/Knight.h
#        Work/Bishop.h
#        Work/Rook.cpp
#        Work/Rook.h
#        Work/Queen.h
#        Work/King.h
#        Work/ImageBoard.h
#        Work/Figure.cpp
#        Work/Pawn.cpp
#        Work/Bishop.cpp
#        Work/Header.h
#        Work/Queen.cpp
#        Work/King.cpp
#        Work/Game.cpp
#        Work/Game.h
#        Work/StockFish.cpp
#        Work/StockFish.h
#        Work/ImageMenu.h
#        Work/Exceptions.h
#        Work/MyDeque.h
#        Work/Algorithms.h
#        Work/Network.cpp
#        Work/Network.h
#)
#
#target_link_libraries(PlayClient
#        sfml-graphics)
#
#
#target_link_libraries(PlayHost
#        sfml-graphics
#)
##target_link_libraries(PlayHost sfml-audio-d sfml-network-d sfml-graphics-d sfml-window-d sfml-system-d)
#
#
#
##target_link_libraries(OpenGL -lglew32 -lopengl32 -lfreeglut -lglfw3 -lgdi32)
#
