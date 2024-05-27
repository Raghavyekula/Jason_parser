#include <stdio.h>
#include <stdlib.h>
#include"parser.h"

int i=0;
int main()
{
    char *json="{\"command\":\"set_temp\", \"value\":\"24\"}";

    JSONContext ctx;
    JSONPair pair[50];
     json_parse_init(&ctx,json);
    if((json_parse_next(&ctx,pair))==1)
    {
        int j=0;
        while(j<=i)
        {
        printf("%s %s\n", pair[j].key, pair[j].value);
        j++;
        }
    } else
    {
        printf("Failed to parse JSON.\n");
    }

    return 0;
}
