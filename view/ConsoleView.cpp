#include "ConsoleView.h"
#include <limits>

void ConsoleView::displayMenu() const
{
  std::cout << "\n===================== MUSIC PLAYER =====================" << std::endl;
  std::cout << " 1. Hien thi toan bo thu vien" << std::endl;
  std::cout << " 2. Tim bai hat theo ID" << std::endl;
  std::cout << " 3. Tim bai hat theo tieu de" << std::endl;
  std::cout << " 4. Tim bai hat theo nghe si" << std::endl;
  std::cout << " 5. Chon va phat mot bai hat (theo ID)" << std::endl;
  std::cout << " 6. Phat bai hat tiep theo (playNext)" << std::endl;
  std::cout << " 7. Phat bai hat truoc do (playBack)" << std::endl;
  std::cout << " 8. Them mot Album vao hang doi" << std::endl;
  std::cout << " 9. Tao mot Smart Playlist (theo Artist)" << std::endl;
  std::cout << "10. Hien thi hang doi hien tai" << std::endl;
  std::cout << "11. Them bai hat vao hang doi(them theo ten)" << std::endl;
  std::cout << "12. Xoa bai hat khoi hang doi(xoa theo ID)" << std::endl;
  std::cout << "13. ON/OFF phat tron bai" << std::endl;
  std::cout << " 0. Thoat" << std::endl;
  std::cout << "==========================================================" << std::endl;
  std::cout << "Vui long nhap lua chon: ";
}

void ConsoleView::displayAllSongs(const std::vector<Song> &songs) const
{
  std::cout << " > Hien thi toan bo bai hat:\n";
  for (const auto &song : songs)
  {
    displaySong(song);
  }
}

void ConsoleView::displayQueue(PlaybackQueue &queue) const
{
  std::cout << " > Danh sach hang doi:\n";
  if (queue.isEmpty())
  {
    std::cout << " => Hang doi dang rong\n";
    return;
  }
  try
  {
    Song currSong = queue.getCurrentSong();
    std::cout << " [Dang Phat] ";
    displaySong(currSong);
    std::list<Song> listQueue = queue.getPlaybackList();
    for (const auto &song : listQueue)
    {
      if (song.m_id != currSong.m_id)
      {
        std::cout << " [Tiep theo] ";
        displaySong(song);
      }
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "LOI: Khong in hang doi" << e.what() << '\n';
  }
}

void ConsoleView::displayShuffleSong(ShuffleManager &shuffle) const
{
  std::vector<Song> shuffleSong = shuffle.getShuffledList();
  for (const Song &s : shuffleSong)
  {
    displaySong(s);
  }
}

void ConsoleView::displaySong(const Song &song) const
{
  std::cout << " [-] [" << song.m_id << "] " << song.m_title << " - " << song.m_artist << " - " << song.m_album << " - " << song.m_duration << std::endl;
}

void ConsoleView::displaySmartList(PlaybackQueue &smartList) const
{
  std::cout << " === Smart List ===\n";
  for (const Song &s : smartList)
  {
    displaySong(s);
  }
}

// helper function:
int ConsoleView::getUserChoice()
{
  int choice = -1;
  while (true)
  {
    std::cin >> choice;
    if (std::cin.fail())
    {
      std::cout << "Loi: Vui long chi nhap so, Hay nhap lai: \n";
      std::cin.clear();
      clearCin();
      continue;
    }
    clearCin();
    return choice;
  };
}

std::string ConsoleView::getUserInput()
{
  std::string input;
  std::getline(std::cin, input);
  return input;
}

void ConsoleView::clearCin() const
{
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}