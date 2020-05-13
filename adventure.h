#include <stdio.h>
#include <stdlib.h>

// hold info about the player
struct Avatar{
  item* backpack; //players inventory
  room* location; // points to current room of player
  int state;
};
typedef struct Avatar avatar;
// takes direction of 10 or less char and redirects the Avatars location to the loction on the map in that direction
void go(char string[10],avatar* ptr);
// grabs the second command from player input
// example take BLANK function returns BLANK
char* get_subject();
// swaps items from one list to another like room to backpack
void item_swap(char* name,item* from,item* to);

//game descriptions
char* welcome_message = "          Welcome to Awkward House Party!\nYou have just wokken up, your head is pounding. where\nare you? who's bedroom is this? how did you get here?\nwhere are your friend? is that a tattoo?  why does it\nsay 'help' on your arm? so many questions. you should\ngo home. but wait you didnt drive here. shit who did.\n";
char* helptext = "Welcome to Awkward House Party \nhere are the commands \n\n-go DIRECTION- to change rooms \n\nDIRECTIONS include \n-north \n-south \n-east \n-west \n-up \n-down \n\n-look -to see whats happening in a room \n\n-take ITEM- to grab an ITEM you see \n\n-drop ITEM- to drop an ITEM you have \n\n-use ITEM- to use an ITEM you see or halve \n\n -check the 'room' or your 'bag' for a list of items \n\n-quit- to leave the game \n";

//item descriptions
char* blueprint = "-------------------DOWNSTAIRS-----------------------------\n_______________________________________\n|              |                       |_______________\n|              |                       |               |\n|              D        kitchen        |               |\n|              |                       D               |\n|   living     |                       |    garage     |\n|           ___|      _________DD______|               |\n|          |-s-|     |                 |               |\n|          |-t-|     |                 |_______________|\n|          |-a-|     |                 |\n|          |-i-|     |     dinning     |\n|          |-r-|_____|                 |\n|___ D_____|         |                 |\n|              mud   D                 |\n|____________________|_________________|\n\n--------------------UPSTAIRS-----------------------------\n_______________________________________\n|                        |             |\n|                        |             |\n|___     hallway         D   bedroom   |\n|   |                    |             |\n|   D                    |             |\n|   |______     ____ DD__|_____________|\n|          |-s-|                       |\n|          |-t-|                       |\n|   bath   |-a-|                       |\n|          |-i-|       bedroom 2       |\n|          |-r-|                       |\n|__________|___|_______________________|";
char* puke = "GROSS!! did you really just pick up puke.\nyou know have puke all over your stuff\nyou smell terrible\n";
char* ipod = "You press a button, the music stops\nyou can here people from the living room\nfreakking out, you may have started a riot.\n";
char* spitter = "oh your thought that was beer but it was\n accually someones spitter, you are now throwing\nup. it taste like winter green\n";
char* cards = "you just picked up a pile of card and through\nthem every where. now you just look like a dick.\n";
char* wine = "wow this is good some, must have stolen this\n from their parents. you feel a buzz coming on.\n";
char* jungle_juice = "wow this is delicious. what do you mean it \ncontains grain alco--\n\n     *you are now black out*\n";
char* lighter = "you just caught something on fire\nquickly stomp it out\nor leave the room\n";
char* dust_pan = "this has literraly no use.\n\n";
char* clothes = "you stole someones clothes, your out of\ncontrol. better hope you dont runn into them\n";
char* juul = "yummmmm cotton candy nicotine\n";
char* gum = "your breath has score has increased by 12%\n";
char* cellphone = "sorry you dont have service here.\n";
char* lint = "you are so poor.\n";
char* cigs = "puff PUFF\ncough cough\n'yeah i love these things'\n";
char* bottle_caps = "woah thats alot of bottle caps!\nhow much did you drink?\nyou should see a doctor.\n";
char* drugs = "you stole those guys drugs.\nwell quick take them before you\nget caught with them. your heart is racing\n";
char* deoderant = "your hygine score has increased by 3%.\n";
char* sink_water = "your are now hydrated. good for you\n";
char* eye_drops = "you know look like you have been crying.\n";
char* beer = "you drink the beer\n";
char* roach = "  ";
//room descriptions

char * mudroom_descr         = "This is the mudroom of the house. \nits sandwiched between the dinning room(west)\nand the living room around the corner(north)\nthere are some shoes I'd suggest not touching\nand some puke I'd suggest even less\n";
char * mudroom_descr_alt     = "           *squish*\n*steps in puke without relizing it*\n*looks around for a second* \n*confused  as to why your here*";
char * mudroom_enter         = "Gross it smells bad in here, you've walked\ninto a room littered in shoes. looks like\nsome on puked in the corner over there.\nyou can here the the muffled sounds of a\nparty on either side of you.\n";
char * living_room_descr     = "this is the living room. the mudroom is to the south\nthe kitchen is to the west.\n";
char * living_room_descr_alt = "Oh THIS IS MY JAMMMMMMMMMM!!!!!\n*awkward dancing beggins*\n*people beggin to stare*\n*awkward dancing intensifies*\n";
char * living_room_enter     = "you enter a dark room packed with people.\nmusic playing so loud its breaking the speaks\nits hard to move around and everyone you bump\ninto is sweaty. you work your way throught the\ncrowd hopefully you run into someone you know\n";
char * kitchen_descr         = "This is the kitchen. the dinning room is to\nthe south, living room to the east and access\nto the garage is to the west\n";
char * kitchen_descr_alt     = "WHATS UP HOMIES!!! *daps up people you dont know* \n have you seen my friend? he looks like...\n *continues to describe what could litteraly be anyone*";
char * kitchen_enter         = "you walk in to a kitchen. there are people\nin indiviual conversations. some sitting on\nthe counter, some leaning against appliances\nthere is a large container of mystery liquid\nsitting on a table, with a laddle\n ";
char * dinning_room_descr    = "this is the dinning room the kitchen is to the north\n     and the mudroom is to the east\n";
char * dinning_room_descr_alt= "DAMN THEIR HOT *you say REALLY loudly to your self*\n anyone wanna play? *there is no response*\n";
char * dinning_room_enter    = "There are some scatted playing cards on the table\n acouple half finished drinks lying around\n a couple of girs are taking selfies behind an ironic poster in the corner\n";
char * garage_descr          = "Its a garage Just like any other\n";
char * garage_descr_alt      = "oh look its jim you found him\n";
char * garage_enter          = "smells like cigarettes and weed in here.\n there is a thin cloud of smoke covering the room\n acouple people are leaning on somes car\n ";
char * hallway_descr         = "This is the Hallway. It connects two bedrooms\none bedroom to the(west) and one to the (south)\nalso a bathroom(east) there are blue print \npainting on the wall and a step stair case(down)\nwithout a  railling";
char * hallway_descr_alt     = "       *freaking out*\n*back against the wall, scared to move*\ndont fall, dont fall, dont fall\n";
char * hallway_enter         = "You walk into an upstairs hallway. with\na stair case heading down stairs. the \nstaircase has no railing. the paintings\non the wall are weird looking blueprints.\n ";
char * bathroom_descr        = "This is the bathroom. is got everything you\nexspect from a bathroom, except a this one\nhas some possible drug users in it. ";
char * bathroom_descr_alt    = "        *walks in like you own the place*    Whats Up Homies mind if, i get in on that\n*they look upset* ... *your not reading their signals*\n      you sould probabaly leave";
char * bathroom_enter        = "*knock Knock* *Knock Knock*\nno answer you walkin to a baathroom with\nthree people in it hundle around a sink\nthey look confused, like your the wierd one\nfor not holding up in the bathroom\n";
char * bedroom_desrc         = "this is the bedroom, I think there is a couple\nhooking up in there. you should probably avoid\nthis room to not look like a creep\n";
char * bedroom_desrc_alt     = "              * you walk in *\n           *flick the light on*\n*you are immeadiatly chased by a shirt less man*\n";
char * bedroom_enter         = "     * lights are off *it sounds like a couple is in here\nthere is are some clothes on the floor\nyou here a 'DO YOU MIND' from the darkness\n";
char * bedroom2_descr        = "\n\n          just a bedroom nothing to see here\n\n\n";
char * bedroom2_enter        = "\n\n          oh this is where you started\n\n\n";
char * bedroom2_descr_alt    = "Oh I remember now jim brought me up here\nbecause I was to drunk\n";
