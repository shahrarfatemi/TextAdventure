//#include "items.h"
#include <string.h>

int get_item(Item items[],char * str,int n){
    for(int i = 0 ; i < n ; i++){
        if(strcmp(str,items[i].name) == 0){
            return i;
        }
    }
    return -1;
}