#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 1024

typedef struct {
  int id;
  char name[MAX_STRING_SIZE];
  char tags[MAX_STRING_SIZE];
  char location[MAX_STRING_SIZE];
} Prefix;
int PrefixesCount = 0;

enum FileActions { READ, WRITE };
enum PrefixActions { CREATE, EDIT, DELETE };

char *get_input(void) {
  static char input_buf[MAX_STRING_SIZE];
  fgets(input_buf, MAX_STRING_SIZE, stdin);

  size_t input_len = strlen(input_buf);
  if (input_len > 0 && input_buf[input_len - 1] == '\n') {
    input_buf[input_len - 1] = '\0';
  }

  return input_buf;
}

Prefix *file_operations(enum FileActions action) {
  Prefix *prefix = NULL;
  switch (action) {
    case READ: {
      struct json_object *parsed_json;

      struct json_object *name;
      struct json_object *tags;
      struct json_object *location;

      json_object *root = json_object_from_file("data.json");
      if (json_object_is_type(root, json_type_array)) {
        int arrayLen = json_object_array_length(root);
        prefix = (Prefix *)malloc(sizeof(Prefix));

        for (int i = 0; i < arrayLen; i++) {
          parsed_json = json_object_array_get_idx(root, i);

          json_object_object_get_ex(parsed_json, "name", &name);
          json_object_object_get_ex(parsed_json, "tags", &tags);
          json_object_object_get_ex(parsed_json, "location", &location);

          prefix[PrefixesCount].id = PrefixesCount;
          strncpy(prefix[PrefixesCount].name, json_object_get_string(name),
                  MAX_STRING_SIZE);
          strncpy(prefix[PrefixesCount].tags, json_object_get_string(tags),
                  MAX_STRING_SIZE);
          strncpy(prefix[PrefixesCount].location,
                  json_object_get_string(location), MAX_STRING_SIZE);

          PrefixesCount++;


          prefix = realloc(prefix, (PrefixesCount + 1) * sizeof(Prefix));
        }
      }

      return prefix;
      break;
    }
    case WRITE: {
        printf("WRITE");
        break;
    }
  }

  return 0;
}

void prefix_operations(enum PrefixActions action, Prefix *prefix) {
  switch (action) {
    case CREATE: {
      PrefixesCount++;
      prefix = realloc(prefix, (PrefixesCount + 1) * sizeof(Prefix));
      
      printf("╭─────────────────╮\n");
      printf("│ Prefix Creation │\n");
      printf("╰─────────────────╯\n\n");

      printf("(1/3) │ Name: ");
      strncpy(prefix[PrefixesCount].name, get_input(), MAX_STRING_SIZE);

      printf("(2/3) │ Tags: ");
      strncpy(prefix[PrefixesCount].tags, get_input(), MAX_STRING_SIZE);

      printf("(3/3) │ Location: ");
      strncpy(prefix[PrefixesCount].location, get_input(), MAX_STRING_SIZE);

      prefix[PrefixesCount].id = PrefixesCount;

      printf("\nPrefix %s Created", prefix[PrefixesCount].name);
    }
    case EDIT: {
      
    }
    case DELETE: {
      
    }
  }
}

int main(int argc, char **argv) {

  if (argc >= 1) {
    Prefix *prefix = file_operations(READ);
    if (!prefix) {
      printf("[E] The pointer to the structure has not been passed");
      return 1;
    }

    if (strcmp(argv[1], "create") == 0) {
      prefix_operations(CREATE, prefix);

    } else if (strcmp(argv[1], "list") == 0) {
      printf("╭─ data.json\n");
      printf("╰─ Saved Prefixes\n\n");

      for (int i = 0; i < PrefixesCount; i++) {
        printf(" │ ID: %d\n", prefix[i].id);
        printf(" │ Name: %s\n", prefix[i].name);
        printf(" │ Tags: %s\n", prefix[i].tags);
        printf(" │ Location: %s\n\n", prefix[i].location);
      }
    } else {
      printf(
          "Unrecongised option: %s\nUse wineman --help for more information\n",
          argv[1]);
    }
    free(prefix);
  }

  return 0;
}
