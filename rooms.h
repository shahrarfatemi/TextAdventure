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

#endif
