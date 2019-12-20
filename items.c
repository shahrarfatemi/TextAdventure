#include "items.h"
#include <string.h>

int get_item(Item items[],char * str,int n){
    for(int i = 0 ; i < n ; i++){
        if(strcmp(str,items[i].name) == 0){
            return i;
        }
    }
    return -1;
}

int use_item(Room * room,Item items[],char * item_name,int n){
    int index = get_item(items,item_name,n);
    if(index > -1){
        if(strcmp(item_name,"match") == 0){
            if(room->state == STATE_DARK){
                items[index].state = STATE_USED;
                return items[index].point-10;
            }
            else{
                items[index].state = STATE_USED;
                return items[index].point;
            }
        }
        else if(strcmp(item_name,"candle") == 0){
            if(items[index].state != STATE_USED){
                items[index].state += 1;
            }
            if(room->state == STATE_DARK){                
                if(items[index].state == STATE_USED){
                    return items[index].point-10;
                }
                else{
                    return items[index].point;
                }
            }
            else{
                return items[index].point;
            }
        }
        else if(strcmp(item_name,"keyring") == 0){
            if(strcmp(room->name,"Cell Room") == 0 && cell_unlocked == 0){
                items[index].state = STATE_USED;
                cell_unlocked = 1;
                return items[index].point-100;
            }
            else{
                items[index].state = STATE_USED;
                return items[index].point+10;
            }
        }
        else if(strcmp(item_name,"knife") == 0){
            if(strcmp(room->name,"Cell Room") == 0 && cell_unlocked != 0){
                return WIN;
            }
            else{
                return 30;
            }
        }
        else if(strcmp(item_name,"ball") == 0){
            if(strcmp(room->name,"Dressing Room") == 0 && dog_avoided == 0){
                items[index].state = STATE_USED;
                dog_avoided = 1;
                return items[index].point-20;
            }
            else{
                items[index].state = STATE_USED;
                return items[index].point;
            }
        }
        else if(strcmp(item_name,"spellcard") == 0){
            if(strcmp(room->name,"Library Room") == 0 && sculp_avoided == 0){
                items[index].state = STATE_USED;
                sculp_avoided = 1;
                return items[index].point-20;
            }
            else{
                items[index].state = STATE_USED;
                return items[index].point;
            }
        }
        else if(strcmp(item_name,"fireflies") == 0){
            if(items[index].state != STATE_USED){
                items[index].state += 1;
            }
            if(room->state == STATE_DARK){                
                if(items[index].state == STATE_USED){
                    return items[index].point-10;
                }
                else{
                    return items[index].point;
                }
            }
            else{
                return items[index].point;
            }
        }
        else if(strcmp(item_name,"locket") == 0){    
            items[index].state = STATE_USED;
            return items[index].point+10;
        }
        else if(strcmp(item_name,"invisible-cloak") == 0){
            if(strcmp(room->name,"Dressing Room") == 0 && dog_avoided == 0){
                items[index].state = STATE_USED;
                dog_avoided = 1;
                return items[index].point-20;
            }
            else{
                items[index].state = STATE_USED;
                return items[index].point;
            }
        }
        else if(strcmp(item_name,"diamond") == 0){
            if(strcmp(room->name,"Dressing Room") == 0 && room->state == STATE_INVISIBLE){
                items[index].state = STATE_USED;
                room->state = STATE_OK;
                return items[index].point-80;
            }
            else{
                items[index].state = STATE_USED;
                return items[index].point;
            }
        }
        else if(strcmp(item_name,"grandchild") == 0){
            if(strcmp(room->name,"Cell Room") == 0 && cell_unlocked == 0){
                items[index].state = STATE_USED;
                cell_unlocked = 1;
                return items[index].point-100;
            }
            else{
                items[index].state = STATE_USED;
                return items[index].point+10;
            }
        }
    }
    return 0;
}