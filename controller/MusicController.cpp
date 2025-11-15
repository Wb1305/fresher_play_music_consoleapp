#include "MusicController.h"
#include "../include/Algorithms.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>

std::string trim(const std::string &str)
{
  size_t first = str.find_first_not_of(" \t\n\r");
  if (std::string::npos == first)
  {
    return str;
  }
  size_t last = str.find_last_not_of(" \t\n\r");
  return str.substr(first, (last - first + 1));
}

MusicController::MusicController(MusicPlayer &model, ConsoleView &view) : m_player(model), m_view(view)
{
  // loadMockData();
  const std::string filepath = "../media/SongList/list_song.txt";
  loadDataFromFile(filepath);
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
      if (m_player.getPlaybackObject().isEmpty() && m_player.getPlaybackHistory().isEmpty())
      {
        std::cout << " [=] Vui long chon bai hat de phat truoc (5), Xin vui long chon lai...\n";
      }
      else
      {
        handlePlayNext();
      }
      break;
    case 7:
      if (m_player.getPlaybackObject().isEmpty() && m_player.getPlaybackHistory().isEmpty())
      {
        std::cout << " [=] Vui long chon bai hat de phat truoc (5), Xin vui long chon lai...\n";
      }
      else
      {
        handlePlayPrevious();
      }
      break;
    case 8:
      if (m_player.getPlaybackObject().isEmpty() && m_player.getPlaybackHistory().isEmpty())
      {
        std::cout << " [=] Vui long chon bai hat de phat truoc (5), Xin vui long chon lai...\n";
      }
      else
      {
        handleAddAlbum();
      }
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
  std::cout << " ... Load mock data\n";
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

void MusicController::loadDataFromFile(const std::string &filePath)
{
  std::vector<Song> loadedSongs;
  std::ifstream file(filePath);
  if (!file.is_open())
  {
    throw std::runtime_error(" [LOI] Khong mo file thanh cong");
  }
  std::string line;
  int lineCount = 1;
  while (std::getline(file, line))
  {
    // lineCount++;
    if (line.empty())
    {
      continue;
    }
    // if (line.find_first_not_of(" \t\n\r") == std::string::npos)
    // {
    //   continue;
    // }
    // if (lineCount == 1 && line.rfind("\xEF\xBB\xBF", 0) == 0)
    // {
    //   line = line.substr(3);
    // }

    std::stringstream strStream(line);
    std::string str_id, title, artist, album, str_duration;

    std::getline(strStream, str_id, ',');
    std::getline(strStream, title, ',');
    std::getline(strStream, artist, ',');
    std::getline(strStream, album, ',');
    std::getline(strStream, str_duration);

    try
    {
      int id = std::stoi(trim(str_id));
      int duration = std::stoi(trim(str_duration));

      loadedSongs.emplace_back(id, trim(title), trim(artist), trim(album), duration);
    }
    catch (const std::exception &e)
    {
      std::cerr << " [LOI] Khi load file data - ";
      std::cerr << e.what() << '\n';
    }
  }
  file.close();
  m_player.load(loadedSongs);
  std::cout << " [=] Load data songs thanh cong\n";
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
  try
  {
    songID = m_view.getUserChoice();
  }
  catch (const std::exception &e)
  {
    std::cout << "[LOI] Vui long nhap ID\n";
    std::cerr << e.what() << '\n';
  }
  m_player.selectAndPlaySong(songID);
}

void MusicController::handlePlayNext()
{
  std::cout << "=> Phat bai hat tiep theo\n";
  m_player.playNext();
  if (m_player.statusShuffleEnable())
  {
    handleDisplayShufflelist();
    return;
  }
  handleDisplayQueue();
}

void MusicController::handlePlayPrevious()
{
  Song preSong = m_player.getPlaybackHistory().playPreviousSong();
  std::cout << "=> Bai hat truoc do: "
            << preSong.m_title << std::endl;
  m_player.getPlaybackObject().playSong(preSong);
}

void MusicController::handleAddAlbum()
{
  std::cout << " > Nhap ten album: ";
  std::string album = m_view.getUserInput();
  addAlbumToQueue(album, m_player.getLibraryObject(), m_player.getPlaybackObject());
  std::cout << "Add album " << album << " vao hang doi thanh cong\n";
  // handleDisplayQueue();
}

void MusicController::handleCreateSmartPlaylist()
{
  // std::cout << "handleCreateSmartPlaylist\n";
  std::cout << " > Chon mot bai hat de phat, nhap ten bai hat: ";
  std::string title = m_view.getUserInput();
  Song *startSong = m_player.getLibraryObject().findSongByTitle(title);
  if (startSong == nullptr)
  {
    std::cout << " [LOI] Khong tim thay bai hat";
    return;
  }
  PlaybackQueue smartListQueue = generateSmartPlaylist(*startSong, m_player.getLibraryObject(), 5);
  std::cout << " => Tao SmartList thanh cong\n";
  m_view.displaySmartList(smartListQueue);
}

void MusicController::handleDisplayQueue()
{
  m_view.displayQueue(m_player.getPlaybackObject());
}

void MusicController::handleAddSongInPlayback()
{
  if (m_player.getPlaybackObject().isEmpty())
  {
    std::cout << " => Vui long chon mot bai hat de phat truoc\n";
    return;
  }

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
    return;
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
  std::cout << " > Danh sach da duoc xao tron: \n";
  bool isEnable = m_player.toggleShuffle();
  if (isEnable)
  {
    std::cout << " => Bat phat tron bai\n";
  }
  else
  {
    std::cout << " => Tat phat trong bai\n";
  }
  handleDisplayShufflelist();
}

void MusicController::handleDisplayShufflelist()
{
  ShuffleManager shuffle = m_player.getShuffle();
  m_view.displayShuffleSong(shuffle);
}