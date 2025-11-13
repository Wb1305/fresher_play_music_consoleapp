#pragma once
#include <stack>
#include "Song.h"

class PlaybackHistory
{
private:
  std::stack<Song> m_playbackHistory;

public:
  PlaybackHistory() = default;
  ~PlaybackHistory() {};

  Song playPreviousSong();
  void addSong(const Song &song);
  bool isEmpty() const;
};