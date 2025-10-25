#include <stdio.h>
#include "song_database.h"
#include "song_query.h"

int main() {
    SongDatabase db; // new database
    initDatabase(&db); // initializes the new database
    int choice; //variable for user to select options
    char filename[100]; //name of the file to be worked with

    do {
        printf("\nMain Menu:\n");
        printf("1. Load Database\n");
        printf("2. Add New Song\n");
        printf("3. Delete Song\n");
        printf("4. Edit Song\n");
        printf("5. Save Database\n");
        printf("6. Display Songs by Artist\n");
        printf("7. Display Songs by Album\n");
        printf("8. List Songs by Year\n");
        printf("9. List Songs by Genre\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); //gets rid of newline

        switch (choice) {
            case 1:
                printf("Enter filename to load: ");
                scanf(" %99[^\n]", filename);
                getchar();
                loadDatabase(&db, filename);
                break;
            case 2:
                addSong(&db);
                break;
            case 3:
                printf("Delete Song\n");
                deleteSong(&db);
                break;
            case 4:
                printf("Edit Song\n");
                editSong(&db);
                break;
            case 5:
                printf("Enter name of file to save: ");
                scanf(" %99[^\n]", filename);
                getchar();
                saveDatabase(&db, filename);
                break;
            case 6:
                printf("Display Songs by Artist\n");
                displaySongsByArtist(&db);
                break;
            case 7:
                printf("Display Songs by Album\n");
                displaySongsByAlbum(&db);
                break;
            case 8:
                printf("Display Songs by Year\n");
                displaySongsByYear(&db);
                break;
            case 9:
                printf("Display Songs by Genre\n");
                displaySongsByGenre(&db);
                break;
            case 10:
                printf("Exiting program...\n");
                break;
            default: //when no case matches the input
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 10); //executes the program until user selects to exit it

    freeDatabase(&db); //frees the allocated memory
    return 0;
}

