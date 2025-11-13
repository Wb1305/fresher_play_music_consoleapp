#include "ConsoleView.h"
#include <limits>

void ConsoleView::displayMenu() const
{
  std::cout << "\n=========== MUSIC PLAYER ============" << std::endl;
  std::cout << " 1. Hien thi toan bo thu vien" << std::endl;
  std::cout << " 2. Tim bai hat theo ID" << std::endl;
  std::cout << " 3. Tim bai hat theo tieu de" << std::endl;
  std::cout << " 4. Tim bai hat theo nghe si" << std::endl;
  std::cout << " 5. Chon va phat mot bai hat (theo ID)" << std::endl;
  std::cout << " 6. Phat bai hat tiep theo (Next)" << std::endl;
  std::cout << " 7. Phat bai hat truoc do (Back/History)" << std::endl;
  std::cout << " 8. Them mot Album vao hang doi" << std::endl;
  std::cout << " 9. Tao mot Smart Playlist (theo Artist)" << std::endl;
  std::cout << "10. Hien thi hang doi hien tai" << std::endl;
  std::cout << "11. Them bai hat vao hang doi(them theo ten)" << std::endl;
  std::cout << "12. Xoa bai hat khoi hang doi(xoa theo ID)" << std::endl;
  std::cout << "13. Phat tron bai trong playlist" << std::endl;
  std::cout << " 0. Thoat" << std::endl;
  std::cout << "==========================================================" << std::endl;
  std::cout << "Vui long nhap lua chon: ";
}

void ConsoleView::displayAllSongs(const std::vector<Song> &songs) const
{
  std::cout << " > Hien thi toan bo bai hat:\n";
  for (const auto &song : songs)
  {
    std::cout << "[" << song.m_id << "] " << song.m_title << " - " << song.m_artist << " trong " << song.m_album << ", duration: " << song.m_duration << std::endl;
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

  const std::list<Song> listPlayback = queue.getPlaybackList();

  for (const auto &song : listPlayback)
  {
    std::cout << " [Tiep theo] " << "[" << song.m_id << "] " << song.m_title << " - " << song.m_artist << " - " << song.m_album << std::endl;
  }

  // try
  // {
  //   Song currSong = queue.getCurrentSong();
  //   std::cout << " [Dang phat] " << currSong.m_title << " - " << currSong.m_artist << std::endl;

  //   for (const auto &song : queue)
  //   {
  //     if (song.m_id != currSong.m_id)
  //     {
  //       std::cout << " [Tiep theo] " << song.m_title << " - " << song.m_artist << std::endl;
  //     }
  //   }
  // }
  // catch (const std::exception &e)
  // {
  //   std::cerr << "LOI: Khong in hang doi" << e.what() << '\n';
  // }
}

int ConsoleView::getUserChoice()
{
  int choice = -1;
  std::cin >> choice;
  if (std::cin.fail())
  {
    std::cout << "Loi: Vui long nhap 1 so\n";
    std::cin.clear();
    clearCin();
    return -1;
  }
  clearCin();
  return choice;
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