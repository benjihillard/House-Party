#include <stdio.h>
#include <string.h>
#include "rooms.h"
#include "items.h"
#include "adventure.h"

char subject[100]; // global system input string

void go(char string[10],avatar* ptr)
{
  if (strcmp(string,"north")==0) {     //move north
    if(ptr->location->north != NULL){
      ptr->location = ptr->location->north;
    }
  }
  if (strcmp(string,"south")==0) {     //move south
    if(ptr->location->south != NULL){
      ptr->location = ptr->location->south;
    }
  }
  if (strcmp(string,"east")==0) {     //move east
    if(ptr->location->east != NULL){
      ptr->location = ptr->location->east;
    }
  }
  if (strcmp(string,"west")==0) {     //move west
    if(ptr->location->west != NULL){
      ptr->location = ptr->location->west;
    }
  }
  if (strcmp(string,"up")==0) {     //move up
    if(ptr->location->up != NULL){
      ptr->location = ptr->location->up;
    }
  }
  if (strcmp(string,"down")==0) {     //move down
    if(ptr->location->down != NULL){
      ptr->location = ptr->location->down;
    }
  }
}

char* get_subject()
{
  int x=0;
  char temp;
  subject[0] = '\0';          //zero out string just incase
  for(;;){
    temp = getchar();         //grabs char from system input
    if(temp == '\n'){break;}  //breaks if thats the end on the command (ie enter has been pressed)
    if(temp != ' '){          //ignores spaces
      subject[x] = temp;      // add to export string
      x++;
    }
  }
  subject[x] = '\0';         // mark end of string
  char* rtn = subject;
  return rtn;
}

void item_swap(char* name,item* from,item* to)
{
  item *temp = NULL;
  temp = (item *)malloc(sizeof(item*));
  temp = item_remove(name,from);         // remove from desired list
  if(strcmp(name,temp->name)==0){        // check if its the right thing (ie item named error with fail)
    items_add(temp,to);                  //add to new desired list
  }else{
    printf("sorry i dont think thats a thing.\n");  //error
  }
}

void main()
{
  //loading items
  item* mud_room_items = create_item(    "head","",create_item("puke",         puke,NULL));
  item* living_room_items = create_item( "head","",create_item("ipod",         ipod,create_item("beer",             beer,NULL)));
  item* dinning_room_items = create_item("head","",create_item("cards",        cards,create_item("wine",wine,NULL)));
  item* kitchen_items = create_item(     "head","",create_item("jungle-juice", jungle_juice,create_item("lighter",  lighter,create_item("dust-pan",dust_pan,NULL))));
  item* garage_items = create_item(      "head","",create_item("roach",        roach,NULL));
  item* bathroom_items = create_item(    "head","",create_item("drugs",        drugs,create_item("deoderant",       deoderant,create_item("sink-water",sink_water,create_item("eye-drops",eye_drops,NULL)))));
  item* bedroom_items = create_item(     "head","",create_item("clothes",      clothes,create_item("Juul",          juul,NULL)));
  item* bedroom2_items = create_item(    "head","",NULL);
  item* hallway_items = create_item(     "head","",create_item("blueprint",    blueprint,create_item("gum",         gum,NULL)));
  item* backpack = create_item("          head","",create_item("cellphone",    cellphone, create_item("lint",       lint,create_item("cigs",cigs,create_item("bottle-caps",bottle_caps,NULL)))));

  //building map                       for look           for altered state     descr of entering     items in room
  room* mud_room = create_room(      mudroom_descr,      mudroom_descr_alt,     mudroom_enter,      mud_room_items);
  room* dinning_room = create_room(  dinning_room_descr, dinning_room_descr_alt,dinning_room_enter, dinning_room_items);
  room* kitchen = create_room(       kitchen_descr,      kitchen_descr_alt ,    kitchen_enter,      kitchen_items);
  room* garage = create_room(        garage_descr,       garage_descr_alt,      garage_enter,       garage_items);
  room* living_room = create_room(   living_room_descr,  living_room_descr_alt, living_room_enter,  living_room_items);
  room* hallway = create_room(       hallway_descr,      hallway_descr_alt,     hallway_enter,      hallway_items);
  room* bathroom = create_room(      bathroom_descr,     bathroom_descr_alt,    bathroom_enter,     bathroom_items);
  room* bedroom = create_room(       bedroom_desrc,      bedroom_desrc_alt,     bedroom_enter,      bedroom_items);
  room* bedroom2 = create_room(      bedroom2_descr,     bedroom2_descr_alt,    bedroom2_enter,     bedroom2_items);
  //linking mudroom exits
  room_exit_north(mud_room,living_room);
  room_exit_east(mud_room,dinning_room);
  room_exit_up(mud_room,hallway);
  // linking dinning room exits
  room_exit_north(dinning_room,kitchen);
  room_exit_west(dinning_room,mud_room);
  // linking kitchen exits
  room_exit_south(kitchen,dinning_room);
  room_exit_east(kitchen,garage);
  room_exit_west(kitchen,living_room);
  // linking garage exits
  room_exit_west(garage,kitchen);
  // linking living room exits
  room_exit_south(living_room,mud_room);
  room_exit_east(living_room,kitchen);
  //linking hallway exits
  room_exit_south(hallway,bedroom2);
  room_exit_east(hallway,bedroom);
  room_exit_west(hallway,bathroom);
  room_exit_down(hallway,mud_room);
  //bathroom exits
  room_exit_east(bathroom,hallway);
  // bedroom exit
  room_exit_west(bedroom,hallway);
  // bedroom2 exit
  room_exit_north(bedroom2,hallway);

  item_cause_on(living_room_items->next->next); //setting cause of beer
  item_cause_on(dinning_room_items->next->next);//setting cause of wine
  item_cause_on(kitchen_items->next);           //setting cause of jungle juice

  // list of non reusable items
  item_reusable_off(kitchen_items->next);           // jungle juice
  item_reusable_off(living_room_items->next->next); //beer
  item_reusable_off(dinning_room_items->next->next); //wine
  item_reusable_off(bathroom_items->next); //drugs
  item_reusable_off(bathroom_items->next->next->next); //sinkwater
  item_reusable_off(hallway_items->next->next); //gum





  char string[10];
  avatar *player = NULL;
  player = (avatar *)malloc(sizeof(room*)); //create avatar pointer
  //if (player == NULL){return NULL;}
  player->backpack = (item *)malloc(sizeof(item*));
  player->backpack = backpack;                       //set items of backpack
  player->location =(room *)malloc(sizeof(room*));
  player->location = bedroom2;                       //set location
  player->state = 0;
  printf("\033[H\033[J");                           //clear screen
  printf("%s\n", welcome_message);
  for (; ;) {                       //game loop
    printf("\n\n\n > ");
    scanf( "%s" , string );  // ask for user input
    printf("\033[H\033[J");
    printf("\033[H\033[J");
    printf("\033[H\033[J");
    printf("\033[H\033[J");


    if (strcmp(string,"quit")==0) {  //quit/exit
      break;




    } else if (strcmp(string,"help")==0) {  //print help options
      while ((getchar()) != '\n');
      printf("%s\n", helptext);




    } else if (strcmp(string,"go")==0) {  // move rooms
      go(get_subject(),player);  //change rooms
      if(player->state == 0){    //determines state of room
        printf("%s\n",player->location->description_enter); //normal state description
      }else{
        printf("%s\n",player->location->description_alt); //altered state descriptions
      }
      if(player->location == garage && player->state == 1){ // condition to end game
        printf("\033[H\033[J");
        printf("\033[H\033[J");
        printf("\033[H\033[J");
        printf("\033[H\033[J");
        printf("CONGRADS YOU MADE IT OUT");
      }



    } else if (strcmp(string,"take")==0) {  //take item
      char *temp  = get_subject();  // find what to take
      item_swap(temp,player->location->items, player->backpack); //swap from room to bag
      printf("you grabed the %s.\n",temp );



    } else if (strcmp(string,"drop")==0) {
      char *temp  = get_subject(); // find what to drop
      item_swap(temp,player->backpack,player->location->items); //swap it back to room list
      printf("you droped the %s.\n",temp);




    } else if (strcmp(string,"use")==0) { // use items
      item *temp = NULL;
      temp = (item *)malloc(sizeof(item*));
      temp = item_remove(get_subject(),player->backpack);
      printf("%s\n",temp->description);
      if(temp->reusable == 1){         //if reusable put back after use
        items_add(temp,player->backpack);
      }
      if(temp->cause==1){   // if item has a cause change state
        player->state = 1;
      }




    } else if (strcmp(string,"check")==0) { // check bag or room for items
      char* sub = get_subject();
      if (strcmp(sub,"room")==0) {
        printf("You look around the room you see:\n");
        items_print(player->location->items);
      }
      if (strcmp(sub,"bag")==0) {
        printf("You look in your bag the contents are:\n");
        items_print(player->backpack);
      }



    } else if (strcmp(string,"look")==0) {  // look see where you are
      printf("%s\n", player->location->description);
      while ((getchar()) != '\n');


    }else{
      printf("Thats not a thing you know how to do and now you have make a fool of yourself.\n");
      while ((getchar()) != '\n');
    }
  }
}
