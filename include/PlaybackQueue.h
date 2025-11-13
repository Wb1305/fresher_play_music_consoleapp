#pragma once
#include "Song.h"
#include <list>
#include <stdexcept>
// #include <iostream>

class PlaybackQueue
{
private:
  std::list<Song> m_playback_queue;
  std::list<Song>::iterator m_current_song;

public:
  PlaybackQueue();
  bool isEmpty() const;
  int size();
  void addSong(const Song &song);
  void removeSong(int songID);
  Song getCurrentSong();
  void playNext();
  void playSong(const Song &song);
  const std::list<Song> &getPlaybackList() const;

  using const_iterator = std::list<Song>::const_iterator;
  const_iterator begin() const
  {
    return m_playback_queue.begin();
  }
  const_iterator end() const
  {
    return m_playback_queue.end();
  }

  ~PlaybackQueue();
};