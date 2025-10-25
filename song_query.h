#ifndef SONG_QUERY_H
#define SONG_QUERY_H
#include "song_database.h"

void displaySongsByArtist(const SongDatabase *db);
void displaySongsByAlbum(const SongDatabase *db);
void displaySongsByYear(const SongDatabase *db);
void displaySongsByGenre(const SongDatabase *db);

#endif // SONG_QUERY_H
