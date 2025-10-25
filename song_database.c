#include "song_database.h"
#include <string.h>

void initDatabase(SongDatabase *db) {
    db->size = 0; //amount of songs rn
    db->capacity = 100; //how much we allocate for songs for now
    db->songs = malloc(db->capacity * sizeof(Song)); //dynamically allocates memory for the array of sonds for now
    if (db->songs == NULL) { // checks if mallocation went wrong
        printf("Memory allocation failed\n");
        exit(1); //terminates the program due to an error
    }
}

void loadDatabase(SongDatabase *db, const char *filename) {
    strncpy(db->filename, filename, sizeof(db->filename) - 1); //store the filename
    db->filename[sizeof(db->filename) - 1] = '\0'; //add null terminator
    FILE *file = fopen(filename, "r"); //creates a file
    if (!file) {
        printf("File \"%s\" does not exist. The database is empty.\n", filename);
        return; // Leave the database as initialized (empty by "initDatabase")
    }

    char buffer[100]; //temporary thing to read thru database
    while (fgets(buffer, sizeof(buffer), file)) { //fgets reads file line by line and stores it into buffer until eof, \n or 100 chars are read
        buffer[strcspn(buffer, "\n")] = '\0'; //removes \n (strcspn checks the length of buffer before newline occurs)
        if (strlen(buffer) == 0) {
            continue; //skip blank datas
        }
        //make sure theres enough space
        if (db->size == db->capacity) {
            db->capacity *= 2; //doubles the space when the amt of songs reaches the limit
            db->songs = realloc(db->songs, db->capacity * sizeof(Song)); //realllocates memory accordingly
            if (!db->songs) { //handle errors
                printf("Memory reallocation failed\n");
                exit(1);
            }
        }

        Song new_song; //creating a new song to be read from db

        //store title
        strncpy(new_song.title, buffer, sizeof(new_song.title) - 1); //copies up to 49 characters from the buffer into the title
        new_song.title[sizeof(new_song.title) - 1] = '\0'; //puts the zero terminator at the end if amt of chars in buffer
                                                           //overflows the allocated size for title

        //read artist
        if (!fgets(buffer, sizeof(buffer), file)) break; //checks the eof or error again
        buffer[strcspn(buffer, "\n")] = '\0'; //removes newline again as before
        if (strlen(buffer) == 0) continue; //skips blanks
        strncpy(new_song.artist, buffer, sizeof(new_song.artist) - 1); //copies bufer contents into the artist
        new_song.artist[sizeof(new_song.artist) - 1] = '\0'; //adds zero terminator

        //the rest of data element readings use the exact same principle

        //read album
        if (!fgets(buffer, sizeof(buffer), file)) break;
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) == 0) continue;
        strncpy(new_song.album, buffer, sizeof(new_song.album) - 1);
        new_song.album[sizeof(new_song.album) - 1] = '\0';

        //read release year
        if (!fgets(buffer, sizeof(buffer), file)) break;
        if (strlen(buffer) == 0) continue;
        new_song.release_year = atoi(buffer); //converts the read string into an integer for further operations

        //read genre
        if (!fgets(buffer, sizeof(buffer), file)) break;
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) == 0) continue;
        strncpy(new_song.genre, buffer, sizeof(new_song.genre) - 1);
        new_song.genre[sizeof(new_song.genre) - 1] = '\0';

        //read length
        if (!fgets(buffer, sizeof(buffer), file)) break;
        if (sscanf(buffer, "%d %d", &new_song.length_minutes, &new_song.length_seconds) != 2) { //assigns min and sec
                                                                                                //checks if it returns 2 successful integers for min and sec
            continue; //skip invalid lines
        }
        //add the new song to the database
        db->songs[db->size++] = new_song; //also increments the size upon adding a song
    }

    fclose(file); //close file when we re done
    printf("Database loaded successfully. %d songs loaded.\n", db->size);
}

void addSong(SongDatabase *db) {
    if (db->size == db->capacity) { //size will be changing so we handle the memory reallocation
        db->capacity *= 2;
        db->songs = realloc(db->songs, db->capacity * sizeof(Song));
        if (!db->songs) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(1);
        }
    }

    Song new_song;
    printf("Enter song title: ");
    scanf(" %49[^\n]", new_song.title);

    printf("Enter the artist: ");
    scanf(" %49[^\n]", new_song.artist);

    printf("Enter album: ");
    scanf(" %49[^\n]", new_song.album);

    printf("Enter release year: ");
    scanf("%d", &new_song.release_year);
    getchar();

    printf("Enter genre: ");
    scanf(" %19[^\n]", new_song.genre);

    printf("Enter length (minutes seconds): ");
    scanf("%d %d", &new_song.length_minutes, &new_song.length_seconds);
    getchar();

    db->songs[db->size++] = new_song; //increments the size upon adding a song
    printf("Song added successfully.\n");
}

void deleteSong(SongDatabase *db) {
    char title[50];
    printf("Enter the title of the song to delete: ");
    scanf(" %49[^\n]", title);

    int found = 0; //song was found
    for (int i = 0; i < db->size; i++) {
        if (strcmp(db->songs[i].title, title) == 0) { //compares the title in database to the input title
            found = 1;

            for (int j = i; j < db->size - 1; j++) {
                db->songs[j] = db->songs[j + 1];
            } //shift array

            db->size--; //decrease the size of the database
            printf("Song %s has been removed from the database.\n", title);
            break;
        }
    }

    if (!found) {
        printf("Song %s not found in the database.\n", title);
    }
}

void printSongInfo(const Song *song) {
    printf("\nTitle: %s\n", song->title);
    printf("Artist: %s\n", song->artist);
    printf("Album: %s\n", song->album);
    printf("Release Year: %d\n", song->release_year);
    printf("Genre: %s\n", song->genre);
    printf("Length: %d:%02d\n", song->length_minutes, song->length_seconds);
}

void editSong(SongDatabase *db){
    char title[50];
    printf("Enter the title of the song you want to edit: ");
    scanf(" %49[^\n]", title);
    getchar();

    int found = 0; //indicator of whether the song was found or not
    for (int i = 0; i < db->size; i++) {
        if (strcmp(db->songs[i].title, title) == 0) {
            found = 1;

            //display the current song details
            printf("\nEditing song: %s\n", db->songs[i].title);
            printf("Current data of the song:\n");
            printSongInfo(&db->songs[i]);

            //request new details
            printf("\nEnter new details (leave blank to keep current value):\n");

            //edit artist
            char artist[50];
            printf("New artist: ");
            fgets(artist, sizeof(artist), stdin);
            artist[strcspn(artist, "\n")] = '\0';
            if (strlen(artist) > 0) { //updates only if users input is not empty
                strncpy(db->songs[i].artist, artist, sizeof(db->songs[i].artist));
            }

            //edit album
            char album[50];
            printf("New album: ");
            fgets(album, sizeof(album), stdin);
            album[strcspn(album, "\n")] = '\0';
            if (strlen(album) > 0) {
                strncpy(db->songs[i].album, album, sizeof(db->songs[i].album));
            }

            //edit release year
            char release_year[10]; //year as a string to consider empty input valid
            printf("New release year: ");
            fgets(release_year, sizeof(release_year), stdin);
            release_year[strcspn(release_year, "\n")] = '\0';
            if (strlen(release_year) > 0) {
                db->songs[i].release_year = atoi(release_year); //stores it as integer
            }

            //edit genre
            char genre[20];
            printf("New genre: ");
            fgets(genre, sizeof(genre), stdin);
            genre[strcspn(genre, "\n")] = '\0';
            if (strlen(genre) > 0) {
                strncpy(db->songs[i].genre, genre, sizeof(db->songs[i].genre));
            }

            //edit length
            char length[10];
            printf("New length (minutes seconds): ");
            fgets(length, sizeof(length), stdin);
            length[strcspn(length, "\n")] = '\0';
            if (strlen(length) > 0) {
                sscanf(length, "%d %d", &db->songs[i].length_minutes, &db->songs[i].length_seconds);
            }

            printf("Song updated successfully\n");
            return;
        }
    }

    if (!found) {
        printf("Song \"%s\" not found in the database.\n", title);
    }
}

void saveDatabase(SongDatabase *db, const char *filename){
    if (strlen(db->filename) == 0) {
        printf("Error: No associated filename for the database. Please specify a file name when saving.\n");
        return;
    }
    FILE *file = fopen(db->filename, "w"); //open the specified file for writing
    if (!file) {
        printf("Error: Could not open file %s for writing.\n", db->filename);
        return; //exit if the file couldn't be opened
    }

    //write each song into the file
    for (int i = 0; i < db->size; i++) {
        fprintf(file, "%s\n", db->songs[i].title);
        fprintf(file, "%s\n", db->songs[i].artist);
        fprintf(file, "%s\n", db->songs[i].album);
        fprintf(file, "%d\n", db->songs[i].release_year);
        fprintf(file, "%s\n", db->songs[i].genre);
        fprintf(file, "%d %d\n", db->songs[i].length_minutes, db->songs[i].length_seconds);
    }

    fclose(file);
    printf("Database saved successfully to %s.\n", db->filename);
}


void freeDatabase(SongDatabase *db) {
    free(db->songs); //frees the allocated memory for songs array
}
