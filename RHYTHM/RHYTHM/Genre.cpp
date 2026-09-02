#include "Genre.h"
#include <fstream>
#include <sstream>
#include <iostream>

Genre::Genre(const std::string& genreName) : name(genreName) {}

bool Genre::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open " << filename << "\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Format: "Artist - Title - Year"
        size_t firstDash = line.find(" - ");
        size_t secondDash = line.find(" - ", firstDash + 3);

        if (firstDash == std::string::npos || secondDash == std::string::npos) {
            // If we don't find the expected two " - " delimiters, skip the line
            continue;
        }

        std::string artist = line.substr(0, firstDash);
        std::string title = line.substr(firstDash + 3, secondDash - (firstDash + 3));
        std::string yearStr = line.substr(secondDash + 3);

        // Convert yearStr to int
        int year = 0;
        try {
            year = std::stoi(yearStr);
        }
        catch (...) {
            // If conversion fails, skip this line
            continue;
        }

        Song s;
        s.artist = artist;
        s.title = title;
        s.year = year;
        songs.push_back(s);
    }
    return true;
}

std::vector<Song> Genre::searchByDecade(int decade) const {
    std::vector<Song> result;
    int start = decade;
    int end = decade + 9;
    for (const auto& s : songs) {
        if (s.year >= start && s.year <= end) {
            result.push_back(s);
        }
    }
    return result;
}

std::vector<Song> Genre::searchByArtist(const std::string& artistName) const {
    std::vector<Song> result;
    // For case-insensitive matching
    std::string lowerArtistName = artistName;
    for (auto& c : lowerArtistName) c = tolower((unsigned char)c);

    for (const auto& s : songs) {
        std::string a = s.artist;
        for (auto& c : a) c = tolower((unsigned char)c);

        if (a.find(lowerArtistName) != std::string::npos) {
            result.push_back(s);
        }
    }
    return result;
}
