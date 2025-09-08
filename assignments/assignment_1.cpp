#include <iostream>
#include <string>

class MyList {
   private:
    std::string* playlist;
    int size;
    int max;

   public:
    MyList(int m) : playlist{nullptr}, size{0}, max{m = 10} {
        // my compiler complains about the implicit conversion without
        // static_cast
        playlist = new std::string[static_cast<unsigned>(max)];
    };

    ~MyList() {
        // free all allocated memory
        delete[] playlist;
    };

    bool isFull() { return max == size; }

    bool isEmpty() { return size == 0; }

    int getSize() { return size; }

    int add(std::string song) {
        if (size < max) {
            playlist[size] = song;
            size++;
            return 0;
        }
        // if size >= max, return error code
        return -1;
    }

    std::string get(int songNumber) {
        // check for valid index
        if (songNumber >= 0 && songNumber < size) {
            return playlist[songNumber];
        }
        // for all invalid indices, return empty string
        return "";
    }

    int remove(std::string song) {
        // the index the song was found at
        int foundIdx{-1};
        for (int i{0}; i < size; i++) {
            if (playlist[i] == song) {
                // record index at which the song was found
                foundIdx = i;
                // break from loop once song is found and removed
                break;
            }
        }
        // if the song was found, then remove it from the playlist and shift
        // elements to the left for all elements greater than i
        if (foundIdx != -1) {
            // not the most efficient implementation, but this maintains the
            // order of the list.
            // if the last element of the list was removed, we don't need to
            // do anything besides change the size of the playlist.
            for (int i = foundIdx; i < size - 1; i++) {
                playlist[i] = playlist[i + 1];
            }

            size = size - 1;
            return 0;
        }
        // if the song was not found, return error code
        return -1;
    }
};

int main() {
    int SIZE = 5;
    MyList SongList{SIZE};

    std::cout << "Enter the names of five songs to add to the playlist"
              << std::endl;
    for (int i{0}; i < SIZE; i++) {
        std::string songName;
        std::cout << "Enter song #" << i + 1 << ": ";
        std::cin >> songName;
        SongList.add(songName);
    }
    std::cout << std::endl << std::endl;

    std::cout << "PLAYLIST:" << std::endl << std::endl;

    // loop through playlist and print song names
    for (int i{0}; i < SIZE; i++) {
        std::cout << SongList.get(i) << std::endl;
    }

    std::cout << "\nEnter the name of a song to remove: ";
    std::string removeName;
    std::cin >> removeName;

    int remove = SongList.remove(removeName);

    // if the song is not found, show the user an error message and request a
    // new song to remove. repeat until remove is successful
    while (remove == -1) {
        std::cout << "Song could not be found." << std::endl;
        std::cout << "Enter the name of a song to remove: ";
        std::cin >> removeName;
        remove = SongList.remove(removeName);
    }

    std::cout << std::endl << std::endl;

    std::cout << "UPDATED PLAYLIST:" << std::endl << std::endl;

    // loop through the updated playlist and print song names
    for (int i{0}; i < SIZE; i++) {
        std::cout << SongList.get(i) << std::endl;
    }
}
