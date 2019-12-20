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

int use_item(Room rooms[],Item items[],char * item_name,int n,int in){
    int index = get_item(items,item_name,n);
    if(index > -1){
        if(strcmp(item_name,"match") == 0){
            if(rooms[in].state == STATE_DARK){
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
            if(rooms[in].state == STATE_DARK){                
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
            if(strcmp(rooms[in].name,"Cell Room") == 0 && cell_unlocked == 0){
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
            if(strcmp(rooms[in].name,"Cell Room") == 0 && cell_unlocked != 0){
                return WIN;
            }
            else{
                return 30;
            }
        }
        else if(strcmp(item_name,"ball") == 0){
            if(strcmp(rooms[in].name,"Dressing Room") == 0 && dog_avoided == 0){
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
            if(strcmp(rooms[in].name,"Library Room") == 0 && sculp_avoided == 0){
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
            if(rooms[in].state == STATE_DARK){                
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
            if(strcmp(rooms[in].name,"Dressing Room") == 0 && dog_avoided == 0){
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
            if(strcmp(rooms[in].name,"Dressing Room") == 0 && rooms[in].state == STATE_INVISIBLE){
                items[index].state = STATE_USED;
                rooms[in].state = STATE_OK;
                return items[index].point-80;
            }
            else{
                items[index].state = STATE_USED;
                return items[index].point;
            }
        }
        else if(strcmp(item_name,"grandchild") == 0){
            if(strcmp(rooms[in].name,"Cell Room") == 0 && cell_unlocked == 0){
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