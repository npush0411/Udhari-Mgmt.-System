#include <stdio.h>
#include "front.h"
#include <stdlib.h>

int main() 
{

    printf("\n-- Welcome to Udhari Management system ! --\n");

    printf("Developers -\n");
    printf("| Pushkar Nashikkar (22410074) |\n");
    printf("| Suprit Bashetti (22410073)    |\n");
    printf("| Atharva Pandey (22410069)     |\n");
    printf("| Viraj Gotmare (22410068)      |\n");

    initDB();

    loge();

    fclose(fu);
    fclose(frec);
    return 0;
}
