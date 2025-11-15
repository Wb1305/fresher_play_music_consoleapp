#pragma once
#include "PlaybackQueue.h"
#include "PlaybackHistory.h"
#include "MusicLibrary.h"
#include "ShuffleManager.h"

class MusicPlayer
{
public:
  MusicPlayer();
  ~MusicPlayer() {};

  void load(const std::vector<Song> &songs);
  void selectAndPlaySong(int songID);
  void playNext(); // phat bai tiep theo trong hang doi
  bool toggleShuffle();
  bool statusShuffleEnable();

  const MusicLibrary &getLibraryObject() const;
  PlaybackQueue &getPlaybackObject();
  PlaybackHistory &getPlaybackHistory();
  const ShuffleManager &getShuffle() const;

private:
  void playNextWithNormal();
  void playNextWithShuffle();

private:
  MusicLibrary m_library;
  PlaybackQueue m_queue;
  PlaybackHistory m_history;
  ShuffleManager m_shuffle;
  bool m_isShuffleEnable;
};