#include "../include/MusicLibrary.h"

MusicLibrary::MusicLibrary() {
};

MusicLibrary::~MusicLibrary() {};

void MusicLibrary::loadLibrary(const std::vector<Song> &songs)
{
  m_songs = songs;
  // clear bộ nhớ
  m_songIndexByID.clear();
  m_songIndexByTitle.clear();
  m_artistIndex.clear();

  // gan lai danh sach
  for (size_t i = 0; i < m_songs.size(); ++i)
  {
    Song *songPtr = &m_songs[i];
    m_songIndexByID[songPtr->m_id] = songPtr;
    m_songIndexByTitle[songPtr->m_title] = songPtr;
    m_artistIndex[songPtr->m_artist].push_back(songPtr);
  }
};

const std::vector<Song> &MusicLibrary::getAllSongs() const
{
  return m_songs;
}

Song *MusicLibrary::findSongByID(int id) const
{
  auto it = m_songIndexByID.find(id);
  if (it == m_songIndexByID.end())
  {
    return nullptr;
  }
  return it->second;
};

Song *MusicLibrary::findSongByTitle(const std::string &title) const
{
  auto it = m_songIndexByTitle.find(title);
  if (it == m_songIndexByTitle.end())
  {
    return nullptr;
  }
  return it->second;
};

std::vector<Song *> MusicLibrary::findSongsByArtist(const std::string &artist) const
{
  auto it = m_artistIndex.find(artist);
  if (it != m_artistIndex.end())
  {
    return it->second;
  }
  return {};
}