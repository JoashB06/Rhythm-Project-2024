#include "Playlist.h"
#include <algorithm>
#include <iostream>
#include <random>

void Playlist::addSong(const Song& s) {
    playlistSongs.push_back(s);
}

void Playlist::display() const {
    if (playlistSongs.empty()) {
        std::cout << "Playlist is empty.\n";
        return;
    }
    for (size_t i = 0; i < playlistSongs.size(); i++) {
        std::cout << i + 1 << ". " << playlistSongs[i].artist << " - "
            << playlistSongs[i].title << " (" << playlistSongs[i].year << ")\n";
    }
}

void Playlist::shuffle() {
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(playlistSongs.begin(), playlistSongs.end(), g);
}
