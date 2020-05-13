#include <stdio.h>
#include <stdlib.h>

struct Item {
  char *name;
  char *description;
  struct Item *next;
  int reusable;
  int cause;
  char *effect;
};
typedef struct Item item;

item *create_item(char* name, char* description, item *next);
char *item_name(item *ptr);
char *item_description(item *ptr);
item *item_next(item *ptr);
void items_print(item* ptr);
void items_add(item* add, item* list);
item *item_remove(char* name, item* ptr);
void item_reusable_off(item* ptr);
void item_cause_on(item* ptr);
