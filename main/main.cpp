// #include "../test/ConsoleApplication.h"
#include "../view/ConsoleView.h"
#include "../controller/MusicController.h"
#include "../include/MusicPlayer.h"
#include "../include/PlaybackQueue.h"
#include "../view/ConsoleView.h"

#include <iostream>

int main()
{
  MusicPlayer model;
  ConsoleView view;
  MusicController controller(model, view);
  controller.run();

  // PlaybackQueue playBack;
  // std::vector<Song> listSongs = {
  //     {101, "Song A", "Artist 1", "Album X", 180},
  //     {102, "Song B", "Artist 1", "Album X", 200},
  //     {103, "Song C", "Artist 2", "Album Y", 220},
  //     {104, "Song D", "Artist 2", "Album X", 180},
  //     {105, "Song E", "Artist 1", "Album X", 200},
  //     {106, "Song F", "Artist 4", "Album Y", 220},
  // };

  // for (const auto &song : listSongs)
  // {
  //   playBack.addSong(song);
  // };

  // std::cout << "Current Song: " << playBack.getCurrentSong().m_title << std::endl;

  // view.displayQueue(playBack);

  return 0;
}