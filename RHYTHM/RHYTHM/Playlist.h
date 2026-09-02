#pragma once
#include <vector>
#include <string>
#include "Genre.h"  // For Song struct

class Playlist {
public:
    void addSong(const Song& s);
    void display() const;
    void shuffle();
    // Maybe remove a song, etc.

private:
    std::vector<Song> playlistSongs;
};

