#include "../include/ShuffleManager.h"

ShuffleManager::ShuffleManager() : m_currentIndex(0), m_randomGenerator(std::random_device{}()) {}

void ShuffleManager::shuffleSongs()
{
  if (!m_shuffleSongs.empty())
  {
    std::shuffle(m_shuffleSongs.begin(), m_shuffleSongs.end(), m_randomGenerator);
  }
  else
  {
    // throw std::runtime_error("Danh sach shuffle rong");
    std::cout << "Danh sach shuffle rong\n";
  }
}

void ShuffleManager::startShuffle(const std::list<Song> &originalSong)
{
  // m_shuffleSongs.assign(originalSong.begin(), originalSong.end());
  m_playedSongs.clear();
  m_currentIndex = 0;
  checkDuplicate(originalSong);
  shuffleSongs();
}

Song ShuffleManager::getNextSong()
{
  if (m_shuffleSongs.empty())
  {
    // throw std::runtime_error("Danh sach shuffle rong");
    std::cout << "Danh sach shuffle rong\n";
  }
  if (m_currentIndex >= m_shuffleSongs.size())
  {
    m_playedSongs.clear();
    m_currentIndex = 0;
    shuffleSongs();
  }
  Song nextSong = m_shuffleSongs[m_currentIndex];
  m_playedSongs.insert(nextSong.m_id);
  m_currentIndex++;
  return nextSong;
}

// void ShuffleManager::playShuffledList()
// {
// }

const std::vector<Song> &ShuffleManager::getShuffledList() const
{
  return m_shuffleSongs;
}

// bool ShuffleManager::isEnableShuffle() const
// {
//   if (m_shuffleSongs.empty())
//   {
//     return false;
//   }
//   return true;
// }

void ShuffleManager::checkDuplicate(const std::list<Song> &originalSong)
{
  std::set<int> playedTracker;
  for (const Song &s : originalSong)
  {
    bool isAdded = playedTracker.insert(s.m_id).second;
    if (isAdded)
    {
      m_shuffleSongs.push_back(s);
    }
  }
}