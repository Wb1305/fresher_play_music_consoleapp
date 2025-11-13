cmake_minimum_required(VERSION 3.10)
project(MusicPlayer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(
  MusicPlayer
  main/main.cpp

  source/MusicLibrary.cpp
  source/MusicPlayer.cpp
  source/PlaybackQueue.cpp
  source/Algorithms.cpp
  source/PlaybackHistory.cpp
  # source/ShuffleManager.cpp
  
  view/ConsoleView.cpp

  controller/MusicController.cpp
)


