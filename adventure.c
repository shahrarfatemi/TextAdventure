#include <stdio.h>
#include <string.h>
#include "rooms.h"

#define true 1
#define false 0

static char input[50] = "look around";

int get_input()
{
    printf("--> ");
    return fgets(input, sizeof(input), stdin) != NULL; 
}

int parse_and_exec(const char * cmd)
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
            printf("I'm %s-ing %s\n", verb, noun);
        }
        else if(strcmp(verb, "go") == 0)
        {
            printf("Let's %s to %s\n", verb, noun);
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

int main()
{
    printf("Welcome to Dhrubo's rescue mission!\n\n");

    while(parse_and_exec(input) && get_input())
    {
        // main loop
    }

    printf("Bye! \n");
    
    return 0;
}
