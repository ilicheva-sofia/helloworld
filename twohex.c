#include<stdio.h>

int main(){
    int start_val, end_val;
    scanf("%x %x" , &start_val, &end_val);
    if (start_val < 32){ start_val = 32;} //до этого идут непечатные символы
    for (int  i=start_val;  i <=end_val;  i++) {  
        printf("| %0x | %c | \n",  i,  i );
        
    }
 
}