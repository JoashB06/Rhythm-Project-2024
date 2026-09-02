#pragma once
#include <string>
#include <vector>

struct Song {
    std::string artist;
    std::string title;
    int year;
};

class Genre {
public:
    Genre(const std::string& genreName);
    bool loadFromFile(const std::string& filename);
    const std::string& getName() const { return name; }
    const std::vector<Song>& getSongs() const { return songs; }
    // You can also implement search methods here:
    std::vector<Song> searchByDecade(int decade) const;
    std::vector<Song> searchByArtist(const std::string& artistName) const;

private:
    std::string name;
    std::vector<Song> songs;
};

