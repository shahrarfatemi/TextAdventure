#include "items.h"
#include "rooms.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int dog_avoided = 0;
int sculp_avoided = 0;
int cell_unlocked = 0;


int get_next_room(Room rooms[],Room current_room,char* dir){
    if(strcmp(current_room.name,"Entry Room") == 0){
        if(strcmp(dir,"north") == 0){
            return 2;
        }
        else if(strcmp(dir,"west") == 0){
            return 1;
        }
    }
    else if(strcmp(current_room.name,"Store Room") == 0){
        if(strcmp(dir,"north") == 0){
            return 5;
        }
        else if(strcmp(dir,"east") == 0){
            return 0;
        }
    }
    else if(strcmp(current_room.name,"Hall Room") == 0){
        if(strcmp(dir,"up") == 0){
            return 4;
        }
        else if(strcmp(dir,"south") == 0){
            return 0;
        }
        else if(strcmp(dir,"east") == 0){
            return 6;
        }
    }
    else if(strcmp(current_room.name,"Dark Room") == 0){
        if(strcmp(dir,"south") == 0){
            return 5;
        }
        else if(strcmp(dir,"west") == 0){
            return 1;
        }
    }
    else if(strcmp(current_room.name,"Library Room") == 0){
        if(strcmp(dir,"down") == 0){
            return 2;
        }
    }
    else if(strcmp(current_room.name,"Dressing Room") == 0){
        if(strcmp(dir,"north") == 0){
            return 3;
        }
        else if(strcmp(dir,"south") == 0){
            return 1;
        }
        else if(strcmp(dir,"up") == 0){
            if(rooms[7].state == STATE_UNAVAILABLE){
                return -2;//means unavailable
            }
            else{
                return 7;
            }
        }
    }
    else if(strcmp(current_room.name,"Dim Room") == 0){
        if(strcmp(dir,"west") == 0){
            return 2;
        }
    }
    else if(strcmp(current_room.name,"Cell Room") == 0){
        if(strcmp(dir,"down") == 0){
            return 5;
        }
    }
    return -1;
}

void describe_current_room(Room room){
    printf("Now in %s\n",room.name);
    if(room.state == STATE_OK || room.state == STATE_VISIBLE){
        if(strcmp(room.name,"Dressing Room") == 0 && dog_avoided != 0){
            printf("The room has got 3 doors.\nnorth) Dark Room,\nsouth) Store Room,\nup) Cell Room\n");
        }
        else if(strcmp(room.name,"Library Room") == 0 && sculp_avoided != 0){
            printf("The room has got 1 door.\ndown) Hall Room\n");
        }
        else if(strcmp(room.name,"Cell Room") == 0 && sculp_avoided != 0){
            printf("Rohan's'cell is unlocked now.His hands and feet are tied with ropes.The room has got 1 door.\ndown) Dressing Room\n");
        }
        else{
            printf("%s",room.description);
        }
    }
    else if(room.state == STATE_DARK){
        printf("This room is dark\n");
    }
    else if(room.state == STATE_INVISIBLE){
        printf("The contents of this room is invisible\n");
    }
    else if(room.state == STATE_UNAVAILABLE){
        printf("you don't have enough points to enter the room\n");
    }
}

void look(Item items[],Room room,int n){
    int i,size = 0;
    Item * itms = (Item*)malloc(sizeof(Item)*n);
    for(int i = 0 ; i < n ; i++){
        if(items[i].state == STATE_NOT_TAKEN){
            if(strcmp((items[i].location)->name,room.name) == 0){
                itms[size++] = items[i];
            }
        }
    }
    if(size!=0){
        printf("The room has :\n");
        for(i = 0 ; i < size ; i++){
            printf("%s => %s\n",itms[i].name,itms[i].description);
        }
    }
    else{
        printf("The room is empty\n");
    }
}



