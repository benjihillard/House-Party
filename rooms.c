#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rooms.h"
#include "items.h"

room* create_room(char* description, char* description_alt,char* description_enter, struct Item* items)
{
  room *ptr = NULL;
  ptr = (room *)malloc(sizeof(room*));
  if (ptr == NULL){return NULL;}
  ptr->description = description;
  ptr->description_alt = description_alt;
  ptr->description_enter = description_enter;
  ptr->items = (struct Item *)malloc(sizeof(struct Item*));
  ptr->items = items;
  ptr->north = (room *)malloc(sizeof(room*));
  ptr->north = NULL;
  ptr->south = (room *)malloc(sizeof(room*));
  ptr->south = NULL;
  ptr->east = (room *)malloc(sizeof(room*));
  ptr->east = NULL;
  ptr->west = (room *)malloc(sizeof(room*));
  ptr->west = NULL;
  ptr->up = (room *)malloc(sizeof(room*));
  ptr->up = NULL;
  ptr->down = (room *)malloc(sizeof(room*));
  ptr->down = NULL;
  return ptr;
}

void room_exit_north(room* current, room* other)
{
  current->north = other;
}

void room_exit_south(room* current, room* other)
{
  current->south = other;
}

void room_exit_east(room* current, room* other)
{
  current->east = other;
}

void room_exit_west(room* current, room* other)
{
  current->west = other;
}

void room_exit_up(room* current, room* other)
{
  current->up = other;
}

void room_exit_down(room* current, room* other)
{
  current->down = other;
}
