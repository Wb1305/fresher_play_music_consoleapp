#include "../include/PlaybackQueue.h"

PlaybackQueue::PlaybackQueue()
{
  // trỏ tới sau phần tử cuối cùng
  m_current_song = m_playback_queue.end();
};

bool PlaybackQueue::isEmpty() const
{
  return m_playback_queue.empty();
}

int PlaybackQueue::size()
{
  return m_playback_queue.size();
}

void PlaybackQueue::addSong(const Song &song)
{
  m_playback_queue.push_back(song);
  // kiem tra queue rong
  if (m_current_song == m_playback_queue.end())
  {
    m_current_song = m_playback_queue.begin(); // trỏ đến phần tử đầU tiên
  }
};

void PlaybackQueue::removeSong(int songID)
{
  if (isEmpty())
  {
    std::cout << "Hang doi rong, khong the remove\n";
    return;
  }

  for (auto it = m_playback_queue.begin(); it != m_playback_queue.end();)
  {
    if (it->m_id == songID)
    {
      if (it == m_current_song)
      {
        it = m_playback_queue.erase(it);
        m_current_song = it;
      }
      else
      {
        it = m_playback_queue.erase(it);
      }
    }
    else
    {
      ++it;
    }
  }
  // truong hop m_current_song tro toi end()
  if (!isEmpty() && m_current_song == m_playback_queue.end())
  {
    m_current_song = m_playback_queue.begin();
  }
};

Song PlaybackQueue::getCurrentSong()
{
  if (isEmpty())
  {
    // throw std::runtime_error("Hang doi rong");
    std::cout << "Khong co bai nao trong hang doi\n";
  }
  if (m_current_song == m_playback_queue.end())
  {
    return *m_playback_queue.begin();
  }
  return *m_current_song;
};

void PlaybackQueue::playNext()
{
  if (isEmpty())
  {
    // throw std::runtime_error("Hang doi rong");
    std::cout << "Hang doi dang trong, khong the chuyen bai\n";
  }
  ++m_current_song;
  if (m_current_song == m_playback_queue.end())
  {
    m_current_song = m_playback_queue.begin();
  }
};

void PlaybackQueue::playSong(const Song &song)
{
  std::cout << "[Dang phat] " << song.m_title << std::endl;
  m_playback_queue.push_back(song);
  m_current_song = --(m_playback_queue.end());
};

const std::list<Song> &PlaybackQueue::getPlaybackList() const
{
  return m_playback_queue;
}

PlaybackQueue::~PlaybackQueue() {}