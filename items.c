#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rooms.h"
#include "items.h"



item *create_item(char* name, char* description, item *next)
{
  item *ptr = NULL;
  ptr = (item *)malloc(sizeof(item*));
  if (ptr == NULL){return NULL;}
  ptr->name = name;
  ptr->description  = description;
  ptr->next = (item *)malloc(sizeof(item*));
  ptr->next = next;
  ptr->reusable = 1;
  ptr->cause = 0;
  ptr->effect = "this item has no effect";
  return ptr;
}

void item_reusable_off(item* ptr){
  ptr->reusable = 0;
}

void item_cause_on(item* ptr){
  ptr->cause = 1;
}

void items_print(item* ptr)
{
  while (ptr->next != NULL) {
    printf("%s\n",ptr->next->name);
    ptr = ptr->next;
  }
}

void items_add(item* add, item* list)
{
  add->next = NULL;
  while (list->next != NULL) {
    list = list->next;
  }
  list->next = add;
}

item *item_remove(char* name, item* ptr)
{
  item *rtn = NULL;
  rtn = (item *)malloc(sizeof(item*));
  if (rtn == NULL){return NULL;}
  while (ptr->next != NULL) {
      if(strcmp(ptr->next->name,name)==0){
        rtn = ptr->next;
        if(rtn->next == NULL){
          ptr->next = NULL;
          return rtn;
        }
        ptr->next = rtn->next;
        rtn->next = NULL;
        return rtn;
      }
      ptr = ptr->next;
    }
    rtn->name = "error";
    rtn->description = "you grab for it but its not there, I think \nthat item was a figment of your imagination";
    return rtn;
}
