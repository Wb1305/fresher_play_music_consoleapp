
#include "../include/MusicPlayer.h"

MusicPlayer::MusicPlayer() : m_isShuffleEnable(false) {}

void MusicPlayer::load(const std::vector<Song> &songs)
{
  m_library.loadLibrary(songs);
}

const MusicLibrary &MusicPlayer::getLibraryObject() const
{
  return m_library;
}

PlaybackQueue &MusicPlayer::getPlaybackObject()
{
  return m_queue;
};

PlaybackHistory &MusicPlayer::getPlaybackHistory()
{
  return m_history;
};

void MusicPlayer::selectAndPlaySong(int songID)
{
  Song *songToPlay = m_library.findSongByID(songID);
  if (songToPlay == nullptr)
  {
    // throw std::runtime_error("songToPlay la nullptr");
    std::cout << " => Bai hat khong hop le";
  }
  if (!m_queue.isEmpty())
  {
    m_history.addSong(m_queue.getCurrentSong());
  }
  m_queue.playSong(*songToPlay);
}

void MusicPlayer::playNext()
{
  if (m_queue.isEmpty())
  {
    // throw std::runtime_error("=> Hang doi dang trong, khong the phat bai hat tiep theo");
    std::cout << "=> Hang doi dang trong, khong the phat bai hat tiep theo\n";
  }
  if (m_isShuffleEnable)
  {
    playNextWithShuffle();
    return;
  }
  playNextWithNormal();
}

void MusicPlayer::playNextWithNormal()
{
  // lấy bài hiện tại, push vao history
  try
  {
    Song currSong = m_queue.getCurrentSong();
    m_history.addSong(currSong);
    m_queue.removeSong(currSong.m_id);
    std::cout << "=> Da day " << currSong.m_title << " vao History\n";
  }
  catch (const std::exception &e)
  {
    std::cerr << "LOI: Khi day them bai hat hien tai vao history " << e.what() << '\n';
  }
  // play
  try
  {
    // m_queue.playNext();
    if (!m_queue.isEmpty())
    {
      std::cout << " [Dang phat] [" << m_queue.getCurrentSong().m_id << "] " << m_queue.getCurrentSong().m_title << " - " << m_queue.getCurrentSong().m_artist << " - " << m_queue.getCurrentSong().m_album << std::endl;
    }
    else
    {
      std::cout << " => Da phat het bai hat trong hang doi\n";
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "LOI: Khi chon va phat bai hat " << e.what() << '\n';
  }
}

void MusicPlayer::playNextWithShuffle()
{
  try
  {
    Song nextSong = m_shuffle.getNextSong();
    m_queue.playSong(nextSong);
  }
  catch (const std::exception &e)
  {
    std::cerr << " [LOI] Phat bai hat khi Shuffle\n";
    std::cerr << e.what() << '\n';
  }
}

bool MusicPlayer::toggleShuffle()
{
  m_isShuffleEnable = !m_isShuffleEnable;

  if (m_isShuffleEnable)
  {
    std::list<Song> tempList;
    if (!m_queue.isEmpty())
    {
      for (const Song &s : m_queue)
      {
        tempList.push_back(s);
      }
    }
    else
    {
      // std::cout << "=> Da tat Shuffle\n";
    }
    m_shuffle.startShuffle(tempList);
  }
  return m_isShuffleEnable;
}

const ShuffleManager &MusicPlayer::getShuffle() const
{
  return m_shuffle;
}

bool MusicPlayer::statusShuffleEnable()
{
  return m_isShuffleEnable;
}