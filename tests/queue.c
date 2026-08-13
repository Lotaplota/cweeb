#include <stdio.h>
#include <stdlib.h>
#include "../functions.h"

int main(void)
{
    printf("hello!\n");
    Queue * q = CreateQueue(3);
    AddLink(q, CreateLink("https://google.com/"));
    AddLink(q, CreateLink("https://reddit.com/"));
    AddLink(q, CreateLink("https://linuxmint.com/"));
    AddLink(q, CreateLink("https://can'tgo!.com/"));
}