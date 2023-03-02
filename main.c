#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "outeffects.h"

#define MAX_STRING_SIZE 1024

typedef struct {
  int id;
  char name[MAX_STRING_SIZE];
  char tags[MAX_STRING_SIZE];
  char location[MAX_STRING_SIZE];
} Prefix;
int PrefixesCount = 0;

enum FileActions { READ, WRITEONCE, REWRITE};
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

Prefix *file_operations(enum FileActions action, Prefix *prefix) {
  switch (action) {
    case READ: {
      Prefix *prefix = NULL;
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

      json_object_put(root);
      return prefix;
      break;
    }
    case WRITEONCE: {
      struct json_object *new_entry = json_object_new_object();

      json_object_object_add(new_entry, "name", json_object_new_string(prefix[PrefixesCount].name));
      json_object_object_add(new_entry, "tags", json_object_new_string(prefix[PrefixesCount].tags));
      json_object_object_add(new_entry, "location", json_object_new_string(prefix[PrefixesCount].location));

      json_object *root = json_object_from_file("data.json");
      if (!json_object_is_type(root, json_type_array)) {
        root = json_object_new_array();
      }
      
      json_object_array_add(root, new_entry);

      FILE *data = fopen("data.json", "w");
      fputs(json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY), data);

      json_object_put(root);
      break;
    }
    case REWRITE: {
      json_object *root = json_object_new_array();

      for (int i = 0; i < PrefixesCount; i++) {
        json_object *entry = json_object_new_object();

        json_object_object_add(entry, "name", json_object_new_string(prefix[i].name));
        json_object_object_add(entry, "tags", json_object_new_string(prefix[i].tags));
        json_object_object_add(entry, "location", json_object_new_string(prefix[i].location));

        json_object_array_add(root, entry);
      }

      FILE *data = fopen("data.json", "w");
      fputs(json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY), data);

      fclose(data);
      json_object_put(root);
      break;
    }
  }

  return 0;
}

void prefix_operations(enum PrefixActions action, Prefix *prefix, char *id) {
  switch (action) {
    case CREATE: {
      PrefixesCount++;
      prefix = realloc(prefix, (PrefixesCount + 1) * sizeof(Prefix));
      
      print_mode(PREFIX_CREATE);

      printf("(1/3) │ Name: ");
      strncpy(prefix[PrefixesCount].name, get_input(), MAX_STRING_SIZE);

      printf("(2/3) │ Tags: ");
      strncpy(prefix[PrefixesCount].tags, get_input(), MAX_STRING_SIZE);

      printf("(3/3) │ Location: ");
      strncpy(prefix[PrefixesCount].location, get_input(), MAX_STRING_SIZE);

      prefix[PrefixesCount].id = PrefixesCount;

      file_operations(WRITEONCE, prefix);
      print_color(GREEN);
      printf("\n>> Prefix Created\n");
      print_color(DEFAULT);

      break;
    }
    case EDIT: {
      printf("EDIT");
      break;
    }
    case DELETE: {
      char *endptr;
      long itd = strtol(id, &endptr, 10); // Convert argument string to int to get clear id

      char *rpn = prefix[itd].name; // Get the name of the prefix to be deleted
      char *rpt = prefix[itd].tags; // Get the name of the prefix to be deleted
      char *rpl = prefix[itd].location; // Get the name of the prefix to be deleted

      print_mode(PREFIX_DELETE);

      printf("Selected Prefix:\n\n");

      printf("│ Name: %s\n", rpn);
      printf("│ Tags: %s\n", rpt);
      printf("│ Location: %s\n\n", rpl);

      printf(":: Are you sure you want to remove this prefix? [y/N]: ");

      if (strcmp(get_input(), "y") == 0) {
        
        if (itd >= PrefixesCount) {
          printf("[E] Prefix ID out of range\n");
          break;
        }

        for (int i = itd; i < PrefixesCount; i++) {
          prefix[i] = prefix[i + 1];
        }

        PrefixesCount--;

        if (PrefixesCount > 0) {
          prefix = realloc(prefix, PrefixesCount * sizeof(Prefix));
        } else {
          prefix = realloc(prefix, sizeof(Prefix));
        }

        file_operations(REWRITE, prefix);
        print_color(RED);
        printf(">> Prefix Deleted\n");
        print_color(DEFAULT);

        break;
      } else {
        print_color(YELLOW);
        printf("[!] Operation Cancelled\n");
        print_color(DEFAULT);

        break;
      }
    } 
  }
}

int main(int argc, char **argv) {

  if (argc >= 1) {
    Prefix *prefix = file_operations(READ, NULL);
    if (!prefix) {
      printf("[E] The pointer to the structure has not been passed");
      return 1;
    }

    if (strcmp(argv[1], "create") == 0) {
      prefix_operations(CREATE, prefix, NULL);

    } else if (strcmp(argv[1], "list") == 0) {
      printf("╭─ data.json\n");
      printf("╰─ Saved Prefixes\n\n");

      if (PrefixesCount == 0) {
        print_mode(PREFIX_NOTFOUND);
      } else {
        for (int i = 0; i < PrefixesCount; i++) {
          printf(" │ ID: %d\n", prefix[i].id);
          printf(" │ Name: %s\n", prefix[i].name);
          printf(" │ Tags: %s\n", prefix[i].tags);
          printf(" │ Location: %s\n\n", prefix[i].location);
        }
      }

    } else if (strcmp(argv[1], "delete") == 0) {
      if (argv[2]) {
        prefix_operations(DELETE, prefix, argv[2]);
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
