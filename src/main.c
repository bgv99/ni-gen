#include "include/ni-gen.h"

Arena arena;

int main() {
    arena = arena_init(ARENA_SIZE);

    srand(time(NULL));

    NameData name_data;

    system(CMD_CLEAR);

    printf("1] Minimal\n");
    printf("2] Long\n");

    scanf("%d", (int *) &name_data.length);

    system(CMD_CLEAR);

    printf("1] Soft\n");
    printf("2] Hard\n");

    scanf("%d", (int *) &name_data.softness);

    system(CMD_CLEAR);

    printf("1] History\n");
    printf("2] Mathematics\n");
    printf("3] Computers\n");
    printf("4] Random\n");

    scanf("%d", (int *) &name_data.category);

    system(CMD_CLEAR);

    printf("1] Add digits\n");
    printf("2] Don't add digits\n");

    scanf("%d", (int *) &name_data.digits);

    system(CMD_CLEAR);

    if(validate_selections(name_data) == EXIT_FAILURE) {
        printf("Choose a valid option!\n");

        return EXIT_FAILURE;
    }

    printf("Name: %s\n", generate_name(name_data));

    arena_destroy(arena);

    return EXIT_SUCCESS;
}
