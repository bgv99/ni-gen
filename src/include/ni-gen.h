#ifndef NI_GEN_H
#define NI_GEN_H

#ifdef _WIN32
#define CMD_CLEAR "cls"
#else
#define CMD_CLEAR "clear"
#endif

// 100,000,000 bytes.
#define ARENA_SIZE 100000000

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum {
    SHORT = 1,
    LONG = 2
} NameLength;

typedef enum {
    SOFT = 1,
    HARD = 2
} NameSoftness;

typedef enum {
    HISTORY = 1,
    MATHEMATICS = 2,
    COMPUTERS = 3,
    RANDOM = 4
} NameCategory;

typedef enum {
    YES = 1,
    NO = 2
} NameDigits;

typedef struct {
    NameLength length;
    NameSoftness softness;
    NameCategory category;
    NameDigits digits;
} NameData;

typedef struct {
    void *ptr;
    size_t offset;
    size_t length;
    size_t capacity;
    bool failed;
} Arena;

Arena arena_init(size_t arena_size);
void arena_destroy(Arena arena);
void *arena_alloc(Arena *arena, size_t alloc_size);

int validate_selections(const NameData name_data);
char *generate_name(const NameData name_data);
void set_name_softness(const NameData name_data, char *complete_name);
bool char_is_hard(char c);
void put_name_digits(char *name);

extern const char *words_history[];
extern const char *words_computers[];
extern const char *words_mathematics[];
extern const char *words_random[];
extern const char **word_address_list[];
extern const size_t words_history_length;
extern const size_t words_mathematics_length;
extern const size_t words_computers_length;
extern const size_t words_random_length;
extern const size_t word_length_list[];
extern Arena arena;

#endif
