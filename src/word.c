#include "include/ni-gen.h"

const char *words_history[] = {
    "allies", "axis", "ottoman", "colony", "empire",
    "ancient", "siege", "war", "attack", "prussia",
    "napoleon", "anatolia", "soldier", "military", "comrade",
    "conquer", "occupy", "bound", "border", "flag",
    "country", "gun", "battle", "treaty", "revolution",
    "dynasty", "kingdom", "republic", "monarchy", "invasion",
    "defense", "fortress", "general", "army", "navy",
    "cavalry", "infantry", "ceasefire", "alliance", "rebellion",
    "sovereign", "capital", "civil", "province", "imperial",
    "territory", "anthem", "march"
};

const char *words_mathematics[] = {
    "variable", "function", "factor", "sum", "prime",
    "angle", "term", "product", "area", "integral",
    "calculus", "algebra", "matrix", "vector", "derivative",
    "limit", "equation", "theorem", "proof", "ratio",
    "fraction", "decimal", "geometry", "trigonometry", "statistics",
    "probability", "logarithm", "integer", "constant"
};

const char *words_computers[] = {
    "bitwise", "logic", "algorithm", "hex", "binary",
    "boolean", "callback", "digit", "float", "input",
    "output", "ai", "web", "internet", "command",
    "operator", "bitmask", "memory", "process", "function",
    "null", "pointer", "address", "error", "syntax",
    "data", "buffer", "compiler", "interpreter", "variable",
    "array", "structure", "thread", "kernel", "driver",
    "firmware", "stack", "queue", "heap", "object",
    "class", "method", "interface", "library", "framework",
    "debug", "exception", "instance", "linux", "unix",
    "macintosh", "root", "container", "database", "query",
    "shell", "windows", "terminal", "app", "bug",
    "iphone", "android", "program", "boot", "bitmap"
};

const char *words_random[] = {
    "yellow", "cat", "sky", "night", "apple",
    "blue", "plane", "dog", "bright", "cube",
    "red", "white", "green", "dark", "colour",
    "truck", "bus", "plank", "coffee", "circle",
    "glass", "boat", "manul", "krill", "fish",
    "tree", "mountain", "river", "stone", "paper",
    "chair", "table", "window", "mirror", "shadow",
    "rain", "snow", "cloud", "storm", "wind",
    "bread", "cheese", "music", "clock", "road",
    "lake", "ink", "candle", "ocean", "sand",
    "grass", "dust", "letter", "desert", "wave",
    "book", "fire", "island", "rust", "flower",
    "tea", "world", "bee", "fox", "bird"
};

const size_t words_history_length = sizeof(words_history) / sizeof(words_history[0]);
const size_t words_mathematics_length = sizeof(words_mathematics) / sizeof(words_mathematics[0]);
const size_t words_computers_length = sizeof(words_computers) / sizeof(words_computers[0]);
const size_t words_random_length = sizeof(words_random) / sizeof(words_random[0]);

// This order should not be changed. Always keep the enumeration order.
const char **word_address_list[] = {
    words_history,
    words_mathematics,
    words_computers,
    words_random
};

const size_t word_length_list[] = {
    words_history_length,
    words_mathematics_length,
    words_computers_length,
    words_random_length
};

bool char_is_hard(char c) {
    c = tolower(c);

    if(isalpha(c) != 0) {
        if(c == 'g' || c == 'j' || c == 'q' ||
            c == 't' || c == 'w' || c == 'x' ||
            c == 'z') {
            return true;
        } else {
            return false;
        }
    }

    return false;
}

void set_name_softness(const NameData name_data, char *complete_word) {
    size_t word_length = strlen(complete_word);
	char new_word[word_length];
	size_t new_word_index = 0;

    if(name_data.softness == SOFT) {
		for(size_t i = 0; i < word_length; i++) {
			if(char_is_hard(complete_word[i])) {
				continue;
			}

			new_word[new_word_index] = complete_word[i];
			new_word_index++;
		}

		// Set the new complete_word.
		memcpy(complete_word, new_word, word_length);
    }
}

void put_name_digits(char *name) {
	int n = rand() % (999 - 0 + 1) + 0;
	char str_n[100];

	sprintf(str_n, "%d", n);
	strcat(name, str_n);
}

char *generate_name(const NameData name_data) {
    // Total word count to collect.
    size_t word_count = 0;

    switch(name_data.length) {
        case SHORT:
            word_count = 3;

            break;
        case LONG:
            word_count = 5;
    }

    // Words of selected category.
    const char **words = word_address_list[name_data.category - 1];
    // These indexes will be used to pick random words from selected category.
    int word_indexes[word_count];

    // Generate random and unique indexes.
    for(size_t i = 0; i < word_count; i++) {
        word_indexes[i] = rand() % (word_length_list[name_data.category] + 0);

        for(size_t j = 0; j < word_count; j++) {
            for(size_t k = j + 1; k < word_count; k++) {
                if(word_indexes[j] == word_indexes[k]) {
                    word_indexes[j] = rand() % (word_length_list[name_data.category] + 0);
                    j--;
                    continue;
                }
            }
        }
    }

    const char *collection[word_count];
    char *complete_word = arena_alloc(&arena, sizeof(char *) * 100);

    // Split and merge collected words.
    for(size_t i = 0; i < word_count; i++) {
        collection[i] = words[word_indexes[i]];
        collection[i] = collection[i] - (strlen(collection[i]) / 2);

        strcat(complete_word, collection[i]);
    }

    set_name_softness(name_data, complete_word);

	if(name_data.digits == YES) {
		put_name_digits(complete_word);
	}

    return complete_word;
}

int validate_selections(const NameData name_data) {
    int return_value = EXIT_SUCCESS;

    if(name_data.category != HISTORY && name_data.category != COMPUTERS && name_data.category != MATHEMATICS && name_data.category != RANDOM) {
        return_value = EXIT_FAILURE;
    } else if(name_data.digits != YES && name_data.digits != NO) {
        return_value = EXIT_FAILURE;
    } else if(name_data.softness != SOFT && name_data.softness != HARD) {
        return_value = EXIT_FAILURE;
    } else if(name_data.length != SHORT && name_data.length != LONG) {
        return_value = EXIT_FAILURE;
    }

    return return_value;
}
