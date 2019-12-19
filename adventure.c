#include "rooms.c"
#include "items.c"

#define true 1
#define false 0
#define sack_capacity 4

static char input[50] = "look around";
int total_score;
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
const char str1[] = "This is the entrance and the first room.It has got 2 doors.\nnorth) Hall Room,\nwest) Store Room\n";

const char str2[] = "This is the store room.It has got 2 doors.\neast) Entry Room,\nnorth) Dressing Room\n\n";

const char str3[] = "This is the hall room.It has got 3 doors.\nup) Library Room,\nsouth) Entry Room,\neast) Dim Room\n";

const char str4[] = "This is the dark room.It has got 1 door.\nsouth) Dressing Room\n";

const char str5[] = "This is the library room.It has got 1 door.\ndown) Hall Room\n";

const char str6[] = "This is the dressing room.It has got 3 doors.\nnorth) Dark Room,\nsouth) Store Room,\nup) Cell Room\n";

const char str7[] = "This is the dim room.It has got 1 doors.\nwest) Hall Room\n";

const char str8[] = "This is the cell.It has got 1 door.\ndown) Dressing Room\n";

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



int get_input()
{
    printf("--> ");
    return fgets(input, sizeof(input), stdin) != NULL; 
}

int parse_and_exec( char * cmd)
{
    char * verb = strtok(cmd, " \n");
    char * noun = strtok(NULL, " \n");

    if(verb != NULL)
    {
        if(strcmp(verb, "quit") == 0)
        {
            return false;
        }
        else if(strcmp(verb, "look") == 0)
        {
            printf("I'm %s-ing \n", verb);
            look(items,current_room,MAX_ITEM);
        }
        else if(strcmp(verb, "go") == 0)
        {
            printf("Let's %s to %s\n", verb, noun);
            Room temp = get_next_room(rooms,current_room,noun);
            if(strcmp(temp.name,"")==0){
                printf("invalid command\n");
            }
            else{
                current_room = temp;
                describe_current_room(current_room);
            }
        }
        else if(strcmp(verb, "take") == 0)
        {
            printf("Let's %s the %s\n", verb, noun);
        }
        else if(strcmp(verb, "use") == 0)
        {
            printf("Let's %s the %s\n", verb, noun);
        }
        else if(strcmp(verb, "drop") == 0)
        {
            printf("Let's %s the %s\n", verb, noun);
        }
        else 
        {
            printf("I don't know how to %s\n", verb);
        }

    }

    return true;
}

void before_entering(){
    before_(rooms[0]);
}

void after_entering(){
    printf("in after\n");
    after_(rooms[0]);
}

void init(){
    rooms[0] = (Room){"Entry Room",str1,3,entry_adj_rooms,STATE_OK};
    rooms[1] = (Room){"Store Room",str2,1,store_adj_rooms,STATE_OK};
    rooms[2] = (Room){"Hall Room",str3,3,hall_adj_rooms,STATE_OK};
    rooms[3] = (Room){"Dark Room",str4,3,dark_adj_rooms,STATE_OK};
    rooms[4] = (Room){"Library Room",str5,3,lib_adj_rooms,STATE_OK};
    rooms[5] = (Room){"Dressing Room",str6,3,dressing_adj_rooms,STATE_OK};
    rooms[6] = (Room){"Dim Room",str7,3,dim_adj_rooms,STATE_OK};
    rooms[7] = (Room){"Cell Room",str8,3,cell_adj_rooms,STATE_OK};

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

    items[0] = (Item){"Match","It can be used to make fire or light",&entry_room,NULL,50,STATE_UNUSED};
    items[1] = (Item){"Candle","It can be use to lighten a space.It can be used a maximum of 3 times.",&entry_room,NULL,100,STATE_UNUSED};
    items[2] = (Item){"Key-Ring","A set of seys.",&hall_room,NULL,200,STATE_UNUSED};
    items[3] = (Item){"Knife","This knife is a really sharp one",&store_room,NULL,200,STATE_UNUSED};
    items[4] = (Item){"Ball","This is a nice blue ball",&dim_room,NULL,150,STATE_UNUSED};
    items[5] = (Item){"Spell-Card","A spell is imprinted on it.",&hall_room,NULL,250,STATE_UNUSED};
    items[6] = (Item){"Fire-Fly Box","A box of fire flies.",&hall_room,NULL,300,STATE_UNUSED};
    items[7] = (Item){"Locket","An expensive locket",&dim_room,NULL,500,STATE_UNUSED};
    items[8] = (Item){"Invisible CLoak","Wearing it can make someone invisible",&store_room,NULL,300,STATE_UNUSED};
    items[9] = (Item){"Diamond","A pearl",&store_room,NULL,300,STATE_UNUSED};
    items[10] = (Item){"The GrandChild of the Witch","She is the grandchild of the witch that captured Rohan",&dark_room,NULL,500,STATE_UNUSED};

}

int main()
{
    init();
    nothing();
    printf("Welcome to Dhrubo's rescue mission!\n\n");
    current_room = rooms[0];
    total_score = 50;
    after_(rooms[0]);
    while(parse_and_exec(input) && get_input())
    {
        // main loop
        //before entering
        before_entering();

        //after entering
        after_entering();
    }

    printf("Bye! \n");
    
    return 0;
}