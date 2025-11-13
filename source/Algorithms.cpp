
#include "../include/Algorithms.h"
#include <iostream>

void addAlbumToQueue(const std::string &albumName, const MusicLibrary &library, PlaybackQueue &queue)
{
  const std::vector<Song> &songs = library.getAllSongs();
  for (const Song &song : songs)
  {
    if (song.m_album == albumName)
    {
      queue.addSong(song);
    }
  }
}

PlaybackQueue generateSmartPlaylist(const Song &startSong, const MusicLibrary &library, int maxSize)
{
  return {};
}