#ifndef SONG_DATABASE_H
#define SONG_DATABASE_H //prevents
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { //typedef will make the code less wordy by creating a name for a datatype like struct in this case
    char title[50]; //all the names for data are self explanatory
    char artist[50];
    char album[50];
    int release_year;
    char genre[20];
    int length_minutes;
    int length_seconds;
} Song; //creates a struct for a song which will contain all its info

typedef struct {
    Song *songs;        //Pointer to the dynamic array of songs
    int size;           //Number of songs currently in the array
    int capacity;       //Tracks the maximum number of songs the database can hold without resizing (less usage of realloc)
    char filename[100]; //Stores the name of the file for the database
} SongDatabase;

void initDatabase(SongDatabase *db);
void loadDatabase(SongDatabase *db, const char *filename);
void addSong(SongDatabase *db);
void deleteSong(SongDatabase *db);
void editSong(SongDatabase *db);
void saveDatabase(SongDatabase *db, const char *filename);
void freeDatabase(SongDatabase *db);
void printSongInfo(const Song *song);

#endif
