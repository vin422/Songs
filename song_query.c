#include "song_database.h"
#include "song_query.h"
#include <string.h>

void displaySongsByArtist(const SongDatabase *db) {
    char artist[50];
    printf("Enter the artist's name: ");
    scanf(" %49[^\n]", artist);

    int found = 0; //shows if any songs are found
    for (int i = 0; i < db->size; i++) {
        //compare the user input with the stored artist
        if (strcmp(db->songs[i].artist, artist) == 0) {
            found = 1;
            printSongInfo(&db->songs[i]);
        }
    }

    if (!found) {
        printf("No songs found for artist \"%s\".\n", artist);
    }
}

void displaySongsByAlbum(const SongDatabase *db){
    char album[50];
    printf("Enter the album's name: ");
    scanf(" %49[^\n]", album);

    int found = 0; //shows if any songs are found
    for (int i = 0; i < db->size; i++) {
        //compare the user input with the stored artist
        if (strcmp(db->songs[i].album, album) == 0) {
            found = 1;
            printSongInfo(&db->songs[i]);
        }
    }

    if (!found) {
        printf("No songs found for album \"%s\".\n", album);
    }
}

void displaySongsByYear(const SongDatabase *db){
    int year;
    printf("Enter the songs's release year: ");
    scanf("%d", &year);
    getchar();

    int found = 0; //shows if any songs are found
    for (int i = 0; i < db->size; i++) {
        //compare the user input with the stored artist
        if (db->songs[i].release_year == year) {
            found = 1;
            printSongInfo(&db->songs[i]); //print song info using the helper function
        }
    }

    if (!found) {
        printf("No songs found for a year %d", year);
    }
}

void displaySongsByGenre(const SongDatabase *db){
    char genre[20];
    printf("Enter the song's genre: ");
    scanf(" %19[^\n]", genre);

    int found = 0; //shows if any songs are found
    for (int i = 0; i < db->size; i++) {
        //compare the user input with the stored artist
        if (strcmp(db->songs[i].genre, genre) == 0) {
            found = 1;
            printSongInfo(&db->songs[i]);
        }
    }

    if (!found) {
        printf("No songs found for genre \"%s\".\n", genre);
    }
}
