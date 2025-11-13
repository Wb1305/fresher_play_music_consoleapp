#pragma once
#include <string>
#include <iostream>

struct Song
{
  std::string m_title;
  std::string m_artist;
  std::string m_album;
  int m_id;
  int m_duration;

  // constructor song
  Song(int id = 0, std::string title = "Unknown", std::string artist = "Unknown", std::string album = "Unknown", int duration = 0) : m_id(id), m_title(title), m_artist(artist), m_album(album), m_duration(duration) {}
};
