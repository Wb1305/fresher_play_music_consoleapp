#pragma once
#include <set>
#include <vector>
#include "Song.h"
#include <random> //dung cho std::shuffle
#include <list>
#include <algorithm>

class ShuffleManager
{
private:
  std::set<int> m_playedSongs;      // chua id cua tat ca bai hat
  std::vector<Song> m_shuffleSongs; // ds songs bị xáo trộn
  size_t m_currentIndex;
  std::mt19937 m_randomGenerator;

  void shuffleSongs();

public:
  ShuffleManager();
  void startShuffle(const std::list<Song> &originalSongs);
  // void playShuffledList();
  Song getNextSong();
  const std::vector<Song> &getShuffledList() const;
  bool isEnableShuffle() const;
};