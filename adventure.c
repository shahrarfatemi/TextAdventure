#include "rooms.h"
#include "items.h"
#include <stdio.h>
#include <string.h>

#define true 1
#define false 0
#define sack_capacity 4

static char input[50] = "";
int total_score;
int number_of_items;
Room current_room;

#define entry_room rooms[0]
#define store_room rooms[1]
#define hall_room rooms[2]
#define dark_room rooms[3]
#define library_room rooms[4]
#define dressing_room rooms[5]
#define dim_room rooms[6]
#define cell_room rooms[7]
//Room rooms[MAX_ROOM];
const char str1[] = "It has got 2 doors.\nnorth) Hall Room,\nwest) Store Room\n";

const char str2[] = "This room is very filthy.It has got 2 doors.\neast) Entry Room,\nnorth) Dressing Room\n";

const char str3[] = "It has got 3 doors.\nup) Library Room,\nsouth) Entry Room,\neast) Dim Room\nEvery time one leaves this room,some points are duducted\n";

const char str4[] = "It has got 1 door.\nsouth) Dressing Room\n";

const char str5[] = "Can you cast a spell? Because there is a sculpture of a previous captive in this room.\nThe room has got 1 door.\ndown) Hall Room\n";

const char str6[] = "There is a mad dog in this room.Can you somehow avoid it?\nThe room has got 3 doors.\nnorth) Dark Room,\nsouth) Store Room,\nup) Cell Room\n";

const char str7[] = "It has got 1 door.\nwest) Hall Room\n";

const char str8[] = "Rohan is captured here in a locked cell.His hands and feet are tied with ropes.The room has got 1 door.\ndown) Dressing Room\n";

Room entry_adj_rooms[3];
Room store_adj_rooms[2];
Room hall_adj_rooms[3];
Room dark_adj_rooms[1];
Room lib_adj_rooms[1];
Room dressing_adj_rooms[3];
Room dim_adj_rooms[2];
Room cell_adj_rooms[1];
Room rooms[MAX_ROOM];

Item items[MAX_ITEM];
Item my_items[sack_capacity];
int current_room_index;

int get_input()
{
    printf("--> ");
    return fgets(input, sizeof(input), stdin) != NULL; 
}

int drop_item_from_my_bag(char * name){
    int found = -1;
    for(int i = 0 ; i < number_of_items ; i++){
        if(strcmp(my_items[i].name,name) == 0){
            found = i;
            break;
        }
    }
    if(found != -1){
        while(found + 1 < number_of_items ){
            my_items[found] = my_items[found+1];
            found++;
        }
        number_of_items--;
        return found;
    }
    return found;
}

int parse_and_exec( char * cmd)
{
    char * verb = strtok(cmd, " \n");
    char * noun = strtok(NULL, " \n");
    if(total_score > 300){
        (rooms[7].state == STATE_DARK)?(rooms[7].state = STATE_DARK):(rooms[7].state = STATE_OK);
    }
    else{
        rooms[7].state = STATE_UNAVAILABLE;
    }
    if(verb != NULL)
    {
        if(strcmp(verb, "quit") == 0)
        {
            return false;
        }
        else if(strcmp(verb, "look") == 0)
        {
            printf("I'm %s-ing \n", verb);
            describe_current_room(current_room);
            if(current_room.state == STATE_DARK || current_room.state == STATE_INVISIBLE){
                //printf("The contents of the room are hidden\n");
            }
            else{
                look(items,current_room,MAX_ITEM);
            }
        }
        else if(strcmp(verb, "go") == 0)
        {
            printf("Let's %s to %s\n", verb, noun);
            int index = get_next_room(rooms,current_room,noun);
            if(index == -2){
                printf("This room is unavailable.Collect more points to unlock it.\n");
            }
            else if(index == -1){
                printf("invalid command\n");
            }
            else{
                if(strcmp(current_room.name,"Hall Room")==0){
                    total_score -= 10;
                }
                current_room = rooms[index];
                current_room_index = index;
                //printf("state : %d\n",current_room.state);
                describe_current_room(current_room);
            }
        }
        else if(strcmp(verb, "take") == 0)
        {
            int index = get_item(items,noun,MAX_ITEM);
            int taken = -1;
            for(int i = 0 ; i < number_of_items ; i++){
                if(strcmp(my_items[i].name,noun) == 0){
                    taken = 1;
                }
            }
            if(taken == -1){
                if(index < 0){
                    printf("invalid name of item\n");    
                }
                else{
                    if(number_of_items < sack_capacity && items[index].state != STATE_USED){
                        my_items[number_of_items++] = items[index];
                        printf("Let's %s the %s\n", verb, noun);
                        total_score += items[index].point;
                        items[index].state = STATE_UNUSED;
                    }
                    else{
                        printf("Your bag is full,you have to drop something at first\n");
                    }
                }
            }
            else{
                printf("You already have this\n");
            }
            
        }
        else if(strcmp(verb, "use") == 0)
        {
            int found = -1;
            for(int i = 0 ; i < number_of_items ; i++){
                if(strcmp(my_items[i].name,noun) == 0){
                    found = i;
                    break;
                }
            }
            if(found != -1){
                int result = use_item(rooms,items,noun,MAX_ITEM,current_room_index);
                int index = get_item(items,noun,MAX_ITEM);
                if(items[index].state == STATE_USED){
                    drop_item_from_my_bag(noun);
                }
                total_score -= result;
                printf("Let's %s the %s\n", verb, noun);
                if(result == WIN){
                    printf("You won!!\n");
                    return false;
                }
                else if(result == LOSE){
                    printf("You lost!!\n");
                    return false;
                }
            }
            else{
                printf("You don't have the %s\n", noun);
            }
        }
        else if(strcmp(verb, "drop") == 0)
        {
            int result = drop_item_from_my_bag(noun);
            if(result == -1){
                printf("invalid name of item\n");
            }
            else{
                int index = get_item(items,noun,MAX_ITEM);
                if(index < 0){
                    printf("invalid name of item\n");
                }
                else{
                    items[index].location = &rooms[current_room_index];
                    printf("Let's %s the %s\n", verb, noun);
                    total_score -= items[index].point;
                    items[index].state = STATE_NOT_TAKEN;
                }
            }
        }
        else if(strcmp(verb, "inventory") == 0)
        {
            if(number_of_items == 0){
                printf("My sack is empty!!\n");
            }
            else{    
                printf("Items I have now:\n");
                for(int i = 0 ; i < number_of_items ; i++){
                    printf("%d) %s  =>  %s\n",i+1,my_items[i].name,my_items[i].description);
                }
            }
        }
        else 
        {
            printf("I don't know how to %s\n", verb);
        }

    }

    return true;
}

void init(){
    rooms[0] = (Room){"Entry Room",str1,3,entry_adj_rooms,STATE_OK};
    rooms[1] = (Room){"Store Room",str2,1,store_adj_rooms,STATE_OK};
    rooms[2] = (Room){"Hall Room",str3,3,hall_adj_rooms,STATE_OK};
    rooms[3] = (Room){"Dark Room",str4,3,dark_adj_rooms,STATE_DARK};
    rooms[4] = (Room){"Library Room",str5,3,lib_adj_rooms,STATE_DARK};
    rooms[5] = (Room){"Dressing Room",str6,3,dressing_adj_rooms,STATE_INVISIBLE};
    rooms[6] = (Room){"Dim Room",str7,3,dim_adj_rooms,STATE_OK};
    rooms[7] = (Room){"Cell Room",str8,3,cell_adj_rooms,STATE_UNAVAILABLE};

    entry_adj_rooms[0] = store_room;
    entry_adj_rooms[1] = hall_room;
    entry_adj_rooms[2] = dim_room;

    store_adj_rooms[0] = entry_room;
    store_adj_rooms[1] = dressing_room;

    hall_adj_rooms[0] = entry_room;
    hall_adj_rooms[1] = library_room;
    hall_adj_rooms[2] = dim_room;

    dark_adj_rooms[0] = dressing_room;

    lib_adj_rooms[0] = hall_room;

    dressing_adj_rooms[0] = store_room;
    dressing_adj_rooms[1] = dark_room;
    dressing_adj_rooms[2] = cell_room;

    dim_adj_rooms[0] = hall_room;
    dim_adj_rooms[1] = entry_room;

    cell_adj_rooms[0] = dressing_room;

    items[0] = (Item){"match","It can be used to make fire or light",&entry_room,NULL,50,STATE_NOT_TAKEN};
    items[1] = (Item){"candle","It can be use to lighten a space.It can be used a maximum of 3 times.",&entry_room,NULL,80,STATE_NOT_TAKEN};
    items[2] = (Item){"keyring","A set of keys.",&hall_room,NULL,100,STATE_NOT_TAKEN};
    items[3] = (Item){"knife","This knife is a really sharp one",&store_room,NULL,100,STATE_NOT_TAKEN};
    items[4] = (Item){"ball","This is a nice blue ball",&dim_room,NULL,100,STATE_NOT_TAKEN};
    items[5] = (Item){"spellcard","A spell is imprinted on it.",&hall_room,NULL,200,STATE_NOT_TAKEN};
    items[6] = (Item){"fireflies","A box of fire flies.",&hall_room,NULL,100,STATE_NOT_TAKEN};
    items[7] = (Item){"locket","An expensive locket",&dim_room,NULL,50,STATE_NOT_TAKEN};
    items[8] = (Item){"invisible-cloak","Wearing it can make you invisible",&store_room,NULL,100,STATE_NOT_TAKEN};
    items[9] = (Item){"diamond","A pearl",&store_room,NULL,-50,STATE_NOT_TAKEN};
    items[10] = (Item){"grandchild","She is the grandchild of the witch that captured Rohan",&dark_room,NULL,100,STATE_NOT_TAKEN};
    //items[11] = (Item){"sculpture","The sculpture of a previous captive",&library_room,//NULL,300,STATE_UNUSED};

}

int main()
{
    init();
    printf("Dhrubo and Rohan are two friends.One day while Rohan was absent from the game in the evening,Dhrubo went to Rohan's house for bringing him.\n");
    printf("Dhrubo met Rohan's parents and got to know that the witch residing at the peak of a nearby hill took Rohan to get him married to her grandchild.\n");
    printf("Dhrubo instantly went towards the hill to rescue his friend.At the top of the hill,he found a big two-storey house\n");
    printf("Welcome to Dhrubo's rescue mission!\n\n");
    current_room = rooms[0];
    current_room_index = 0;
    number_of_items = 0;
    total_score = 50;
    describe_current_room(rooms[0]);

    while(parse_and_exec(input) && get_input())
    {
        // main loop
    }

    printf("Bye! \n");
    
    return 0;
}