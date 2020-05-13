#include <stdio.h>
#include <stdlib.h>

struct Room {
  char* description;
  char* description_alt;
  char* description_enter;
  struct Item* items;
  struct Room* north;
  struct Room* south;
  struct Room* east;
  struct Room* west;
  struct Room* up;
  struct Room* down;
};
typedef struct Room room;

room* create_room(char* description, char* description_alt,char* description_enter, struct Item* items);
void room_exit_north(room* current, room* other);
void room_exit_south(room* current, room* other);
void room_exit_east(room* current, room* other);
void room_exit_west(room* current, room* other);
void room_exit_up(room* current, room* other);
void room_exit_down(room* current, room* other);
