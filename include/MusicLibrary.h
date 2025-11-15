#pragma once
#include "./Song.h"
#include <vector>
#include <map>
#include <unordered_map>

class MusicLibrary
{
private:
  std::vector<Song> m_songs;
  std::unordered_map<int, Song *> m_songIndexByID;
  std::map<std::string, Song *> m_songIndexByTitle;
  std::unordered_map<std::string, std::vector<Song *>> m_artistIndex;
  std::unordered_map<std::string, std::vector<Song *>> m_albumIndex;

public:
  MusicLibrary(/* args */);
  ~MusicLibrary();

  void loadLibrary(const std::vector<Song> &songs);
  const std::vector<Song> &getAllSongs() const;
  Song *findSongByID(int id) const;
  Song *findSongByTitle(const std::string &title) const;
  std::vector<Song *> findSongsByArtist(const std::string &artist) const;
  std::vector<Song *> findSongsByAlbum(const std::string &album) const;
};
