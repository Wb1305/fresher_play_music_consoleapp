#pragma once

#include "../include/MusicPlayer.h"
#include "../view/ConsoleView.h"

class MusicController
{
public:
  MusicController(MusicPlayer &model, ConsoleView &view);
  void run();
  ~MusicController() {};

private:
  MusicPlayer m_player;
  ConsoleView m_view;
  // --- Hàm Setup ---
  void loadMockData();
  void loadDataFromFile(const std::string &filePath);
  // --- Hàm xử lý cho từng lựa chọn menu ---
  void handleDisplayLibrary();
  void handleFindByID();
  void handleFindByTitle();
  void handleFindByArtist();
  void handleSelectAndPlay();
  void handlePlayNext();
  void handlePlayPrevious();
  void handleAddAlbum();
  void handleCreateSmartPlaylist();
  void handleDisplayQueue();
  void handleAddSongInPlayback();
  void handleRemoveSongOutPlayback();
  void handleShufflePlaylist();
  void handleDisplayShufflelist();
};