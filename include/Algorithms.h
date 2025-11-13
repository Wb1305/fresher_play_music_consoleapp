#pragma once
#include <string>
#include "MusicLibrary.h"
#include "PlaybackQueue.h"
#include <queue>

void addAlbumToQueue(const std::string &albumName, const MusicLibrary &library, PlaybackQueue &queue);

PlaybackQueue generateSmartPlaylist(const Song &startSong, const MusicLibrary &library, int maxSize);