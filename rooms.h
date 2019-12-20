#ifndef ROOMS_H
#define ROOMS_H

#define MAX_ROOM 8

#define STATE_INVISIBLE -9999
#define STATE_UNAVAILABLE   -1
#define STATE_VISIBLE   0
#define STATE_DARK  -1000
#define STATE_OK 0

typedef struct Room
{
    const char * name;
    const char * description;
    int n_doors;
    //struct Room * adj_rooms;
    struct Room *adj_rooms;
    int state;
} Room;

extern Room rooms[];

#define entry_room rooms[0]
#define store_room rooms[1]
#define hall_room rooms[2]
#define dark_room rooms[3]
#define library_room rooms[4]
#define dressing_room rooms[5]
#define dim_room rooms[6]
#define cell_room rooms[7]

struct Item;


extern int dog_avoided;
extern int sculp_avoided;
extern int cell_unlocked;

int before_(Room room);
int after_(Room room);
int get_next_room(Room rooms[],Room current_room,char* dir);
void describe_current_room(Room room);
void look(struct Item *items,Room room,int n);

#endif
