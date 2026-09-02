#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include "Listener.h"
#include "Genre.h"
#include "Playlist.h"

int main() {
    // Login process
    Listener listener;
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;
    bool loggedIn = false;
    while (attempts < MAX_ATTEMPTS && !loggedIn) {
        std::string username, password;
        std::cout << "=== Welcome to RYHTHM ===\n";
        std::cout << "Please login.\nUsername: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password; // (for a real system, you'd mask input)

        if (listener.login(username, password)) {
            loggedIn = true;
            std::cout << "Login successful!\n";
        }
        else {
            std::cout << "Invalid credentials.\n";
            attempts++;
        }
    }

    if (!loggedIn) {
        std::cout << "Too many failed attempts. Exiting...\n";
        return 0;
    }

    // Load genres
    std::vector<Genre> genres;
    // Assuming all .dat files in the "genres" folder are valid genre files:
    for (const auto& entry : std::filesystem::directory_iterator("genres")) {
        if (entry.is_regular_file()) {
            // Extract genre name from filename (e.g., rock.dat -> rock)
            std::string path = entry.path().string();
            std::string filename = entry.path().filename().string();
            // Remove extension
            size_t dotPos = filename.find('.');
            std::string genreName = (dotPos == std::string::npos) ? filename : filename.substr(0, dotPos);

            Genre g(genreName);
            if (g.loadFromFile(path)) {
                genres.push_back(g);
            }
        }
    }

    // Create a playlist
    Playlist playlist;

    // Main Menu
    bool done = false;
    while (!done) {
        std::cout << "\n=== RYHTHM MENU ===\n";
        std::cout << "1. Search for song by decade\n";
        std::cout << "2. Search for song by artist\n";
        std::cout << "3. Search for song by genre\n";
        std::cout << "4. Display current playlist\n";
        std::cout << "5. Shuffle playlist\n";
        std::cout << "6. Add a new feature (Add a song by title)\n";
        std::cout << "7. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int decade;
            std::cout << "Enter decade (e.g. 1980): ";
            std::cin >> decade;
            // Search all genres for songs from that decade
            {
                std::vector<Song> results;
                for (auto& g : genres) {
                    auto v = g.searchByDecade(decade);
                    results.insert(results.end(), v.begin(), v.end());
                }

                if (results.empty()) {
                    std::cout << "No songs found from " << decade << "s.\n";
                }
                else {
                    std::cout << "Found these songs:\n";
                    for (size_t i = 0; i < results.size(); i++) {
                        std::cout << i + 1 << ". " << results[i].artist << " - "
                            << results[i].title << " (" << results[i].year << ")\n";
                    }
                    std::cout << "Add any to playlist? Enter number or 0 to skip: ";
                    int sel;
                    std::cin >> sel;
                    if (sel > 0 && sel <= (int)results.size()) {
                        playlist.addSong(results[sel - 1]);
                        std::cout << "Song added to playlist.\n";
                    }
                }
            }
            break;
        }
        case 2: {
            std::string artist;
            std::cout << "Enter artist name: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, artist);

            std::vector<Song> results;
            for (auto& g : genres) {
                auto v = g.searchByArtist(artist);
                results.insert(results.end(), v.begin(), v.end());
            }

            if (results.empty()) {
                std::cout << "No songs found by " << artist << ".\n";
            }
            else {
                std::cout << "Found these songs:\n";
                for (size_t i = 0; i < results.size(); i++) {
                    std::cout << i + 1 << ". " << results[i].artist << " - "
                        << results[i].title << " (" << results[i].year << ")\n";
                }
                std::cout << "Add any to playlist? Enter number or 0 to skip: ";
                int sel;
                std::cin >> sel;
                if (sel > 0 && sel <= (int)results.size()) {
                    playlist.addSong(results[sel - 1]);
                    std::cout << "Song added to playlist.\n";
                }
            }
            break;
        }
        case 3: {
            std::cout << "Available genres:\n";
            for (size_t i = 0; i < genres.size(); i++) {
                std::cout << i + 1 << ". " << genres[i].getName() << "\n";
            }
            std::cout << "Select a genre: ";
            int gsel;
            std::cin >> gsel;
            if (gsel > 0 && gsel <= (int)genres.size()) {
                const auto& songs = genres[gsel - 1].getSongs();
                if (songs.empty()) {
                    std::cout << "No songs found in this genre.\n";
                }
                else {
                    std::cout << "Songs in " << genres[gsel - 1].getName() << ":\n";
                    for (size_t i = 0; i < songs.size(); i++) {
                        std::cout << i + 1 << ". " << songs[i].artist << " - "
                            << songs[i].title << " (" << songs[i].year << ")\n";
                    }
                    std::cout << "Add any to playlist? Enter number or 0 to skip: ";
                    int sel;
                    std::cin >> sel;
                    if (sel > 0 && sel <= (int)songs.size()) {
                        playlist.addSong(songs[sel - 1]);
                        std::cout << "Song added to playlist.\n";
                    }
                }
            }
            break;
        }
        case 4: {
            playlist.display();
            break;
        }
        case 5: {
            playlist.shuffle();
            std::cout << "Playlist shuffled.\n";
            break;
        }
        case 6: {
            // Another feature: Add a song by directly entering details:
            std::string artist, title;
            int year;
            std::cout << "Enter artist: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, artist);
            std::cout << "Enter title: ";
            std::getline(std::cin, title);
            std::cout << "Enter year: ";
            std::cin >> year;

            Song s{ artist, title, year };
            playlist.addSong(s);
            std::cout << "Song added.\n";
            break;
        }
        case 7: {
            std::cout << "Exiting RYHTHM. Goodbye!\n";
            done = true;
            break;
        }
        default:
            std::cout << "Invalid selection, try again.\n";
        }
    }

    return 0;
}
