#include "../include/PlaybackHistory.h"
#include "../include/Song.h"

Song PlaybackHistory::playPreviousSong()
{
  if (isEmpty())
  {
    throw std::runtime_error("Lich su dang rong");
  }
  Song song = m_playbackHistory.top();
  m_playbackHistory.pop();
  return song;
};

void PlaybackHistory::addSong(const Song &song)
{
  // add song
  m_playbackHistory.push(song);
};

bool PlaybackHistory::isEmpty() const
{
  return m_playbackHistory.empty();
};