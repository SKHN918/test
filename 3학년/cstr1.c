#include <stdio.h>
/*피보나치 수열*/
int fivo(int i){
    if (i==0) return 0;
    if (i==1) return 1;
    return fivo(i-1) + fivo(i-2);
}

int main(){
    printf("%d", fivo(6));
}



