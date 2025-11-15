
#include "../include/Algorithms.h"
#include <iostream>
#include <set>

void addAlbumToQueue(const std::string &albumName, const MusicLibrary &library, PlaybackQueue &queue)
{
  const std::vector<Song *> songs = library.findSongsByAlbum(albumName);
  for (const Song *s : songs)
  {
    queue.addSong(*s);
  }

  // const std::vector<Song> &songs = library.getAllSongs();
  // for (const Song &song : songs)
  // {
  //   if (song.m_album == albumName)
  //   {
  //     queue.addSong(song);
  //   }
  // }
}

PlaybackQueue generateSmartPlaylist(const Song &startSong, const MusicLibrary &library, int maxSize)
{
  PlaybackQueue smartPlaylist;
  if (maxSize <= 0)
  {
    return smartPlaylist;
  }
  std::queue<Song> exploreQueue;
  std::set<int> visitedSong;

  smartPlaylist.addSong(startSong);
  exploreQueue.push(startSong);
  visitedSong.insert(startSong.m_id);

  while (!exploreQueue.empty() && smartPlaylist.size() < maxSize)
  {
    Song currSong = exploreQueue.front();
    exploreQueue.pop();

    std::vector<Song *> artists = library.findSongsByArtist(currSong.m_artist);

    for (Song *artist : artists)
    {
      if (smartPlaylist.size() >= maxSize)
        break;
      if (visitedSong.find(artist->m_id) == visitedSong.end())
      {
        visitedSong.insert(artist->m_id);
        exploreQueue.push(*artist);
        smartPlaylist.addSong(*artist);
      }
    }

    if (smartPlaylist.size() >= maxSize)
      break;

    // const std::vector<Song> &allSongs = library.getAllSongs();
    std::vector<Song *> album = library.findSongsByAlbum(currSong.m_album);
    for (const Song *s : album)
    {
      if (smartPlaylist.size() >= maxSize)
        break;
      if (visitedSong.find(s->m_id) == visitedSong.end())
      {
        visitedSong.insert(s->m_id);
        exploreQueue.push(*s);
        smartPlaylist.addSong(*s);
      }
    }
  }
  return smartPlaylist;
}