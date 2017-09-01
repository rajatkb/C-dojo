#include <stdio.h>

int range(long long int l , long long int u , long long int increment=1) {
    static long long int i; 
    static int state = 0;
    switch (state) {
        case 0: /* start of function */
        for (i = l; i < u; i+=increment) {
           state=1; /* so we will come back to "case 1" */
            return i;

            case 1:; /* resume control straight after the return */
        }
    }
    state= 0;
    return 0;
}

int main()
{
	long long int i;

    for(;i=range(1,7274);)
    {
        printf("%d\n" , i);
    }
}
