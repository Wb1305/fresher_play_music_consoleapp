#include "MusicController.h"
#include "../include/Algorithms.h"

MusicController::MusicController(MusicPlayer &model, ConsoleView &view) : m_player(model), m_view(view)
{
  loadMockData();
}

void MusicController::run()
{
  int choice = -1;
  while (choice != 0)
  {
    m_view.displayMenu();
    choice = m_view.getUserChoice();
    switch (choice)
    {
    case 1:
      handleDisplayLibrary();
      break;
    case 2:
      handleFindByID();
      break;
    case 3:
      handleFindByTitle();
      break;
    case 4:
      handleFindByArtist();
      break;
    case 5:
      handleSelectAndPlay();
      break;
    case 6:
      handlePlayNext();
      break;
    case 7:
      handlePlayPrevious();
      break;
    case 8:
      handleAddAlbum();
      break;
    case 9:
      handleCreateSmartPlaylist();
      break;
    case 10:
      handleDisplayQueue();
      break;
    case 11:
      handleAddSongInPlayback();
      break;
    case 12:
      handleRemoveSongOutPlayback();
      break;
    case 13:
      handleShufflePlaylist();
      break;
    case 0:
      std::cout << " > Tam biet!" << std::endl;
      break;
    default:
      std::cout << "\n*** LOI: Lua chon khong hop le. Vui long chon tu 0-13. ***" << std::endl;
      break;
    }
  }
}

void MusicController::loadMockData()
{
  std::cout << "Load mock data\n";
  std::vector<Song> mockSongs = {
      {101, "Song A", "Artist 1", "Album X", 180},
      {102, "Song B", "Artist 1", "Album X", 200},
      {103, "Song C", "Artist 2", "Album Y", 220},
      {104, "Song D", "Artist 2", "Album X", 180},
      {105, "Song E", "Artist 1", "Album X", 200},
      {106, "Song F", "Artist 4", "Album Y", 220},
      {107, "Song G", "Artist 5", "Album Y", 220},
      {108, "Song H", "Artist 6", "Album Z", 180},
      {109, "Song K", "Artist 5", "Album Y", 200},
      {110, "Song J", "Artist 3", "Album Y", 220},
  };
  m_player.load(mockSongs);
}

void MusicController::handleDisplayLibrary()
{
  const std::vector<Song> &songs = m_player.getLibraryObject().getAllSongs();
  m_view.displayAllSongs(songs);
}

void MusicController::handleFindByID()
{
  std::cout << " > Nhap ID bai hat can tim: \n";
  int id = m_view.getUserChoice();
  Song *song = m_player.getLibraryObject().findSongByID(id);
  if (song)
  {
    std::cout << " => Tim thay: [" << song->m_id << "] " << song->m_title << " - " << song->m_artist << std::endl;
  }
  else
  {
    std::cout << " => Khong tim thay bai hat co ID: " << id << std::endl;
  }
}

void MusicController::handleFindByTitle()
{
  std::cout << " > Nhap ten bai hat: \n";
  std::string title = m_view.getUserInput();
  Song *song = m_player.getLibraryObject().findSongByTitle(title);
  if (song)
  {
    std::cout << " => Tim thay: [" << song->m_id << "] " << song->m_title << " - " << song->m_artist << std::endl;
  }
  else
  {
    std::cout << " => Khong tim thay bai hat " << title << std::endl;
  }
}

void MusicController::handleFindByArtist()
{
  std::cout << " > Nhap ten artist: \n";
  std::string artist = m_view.getUserInput();
  const std::vector<Song *> songs = m_player.getLibraryObject().findSongsByArtist(artist);
  if (!songs.empty())
  {
    std::cout << "=> Danh bai hat cua artist: \n";
    // m_view.displayAllSongs(songs);
    for (const auto &song : songs)
    {
      std::cout << "[" << song->m_id << "] " << song->m_title << " - " << song->m_artist << " trong " << song->m_album << ", duration: " << song->m_duration << std::endl;
    }
  }
  else
  {
    std::cout << " => Khong tim thay bai hat nao cua artist " << artist << std::endl;
  }
}

void MusicController::handleSelectAndPlay()
{
  std::cout << " > Nhap ID bai hat can phat: \n";
  size_t songID;
  songID = m_view.getUserChoice();
  m_player.selectAndPlaySong(songID);
}

void MusicController::handlePlayNext()
{
  std::cout << "=> Bai hat tiep theo: \n";
  m_player.playNext();
  handleDisplayQueue();
}

void MusicController::handlePlayPrevious()
{
  Song preSong = m_player.getPlaybackHistory().playPreviousSong();
  std::cout << "=> Bai hat truoc do: \n"
            << preSong.m_title << std::endl;
}

void MusicController::handleAddAlbum()
{
  std::cout << " > Nhap ten album: ";
  std::string album = m_view.getUserInput();
  addAlbumToQueue(album, m_player.getLibraryObject(), m_player.getPlaybackObject());
  std::cout << "Add album " << album << " vao hang doi thanh cong\n";
  handleDisplayQueue();
}

void MusicController::handleCreateSmartPlaylist()
{
  std::cout << "Handle\n";
}

void MusicController::handleDisplayQueue()
{
  m_view.displayQueue(m_player.getPlaybackObject());
}

void MusicController::handleAddSongInPlayback()
{
  std::cout << " > Nhap ten bai hat can them: ";
  std::string title = m_view.getUserInput();
  Song *song = m_player.getLibraryObject().findSongByTitle(title);
  if (song != nullptr)
  {
    m_player.getPlaybackObject().addSong(*song);
    std::cout << " => Da them bai hat " << title << " vao hang doi\n";
  }
  else
  {
    std::cout << " => Bai hat khong ton tai\n";
  }
  handleDisplayQueue();
}

void MusicController::handleRemoveSongOutPlayback()
{
  std::cout << " > Nhap ID bai hat can xoa: ";
  int id = m_view.getUserChoice();
  m_player.getPlaybackObject().removeSong(id);
  handleDisplayQueue();
}

void MusicController::handleShufflePlaylist()
{
  bool isEnable = m_player.toggleShuffle();
  handleDisplayQueue();
}
