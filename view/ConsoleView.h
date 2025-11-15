#pragma once
#include <string>
#include "../include/PlaybackQueue.h"
#include "../include/ShuffleManager.h"
#include <vector>

class ConsoleView
{
public:
  ConsoleView() = default;
  void displayMenu() const;
  void displayAllSongs(const std::vector<Song> &songs) const;
  void displayQueue(PlaybackQueue &queue) const;
  void displayShuffleSong(ShuffleManager &shuffle) const;
  void displaySong(const Song &song) const;
  void displaySmartList(PlaybackQueue &smartList) const;
  void displayOptionWithSong() const;
  int getUserChoice();
  std::string getUserInput();
  void clearCin() const;
};
