#include <stdio.h>
int main(){
    int num; 
    scanf("%d",&num); //reading an int from user and and storing it in num
    for(int i=1; //initialising i as 1, 1 is factor of all numbers
        i<=num; //iterating a loop from i(=1) to number
        ++i){  
        if (num%i==0){ //checks if i is a divisor of number
            printf("%d",i); 

           if (i!=num){ //printing space as long as i is not the number itself
                printf(" ");
            }
        }
    }
    printf("\n"); //moving it to the new line as given in sample executable
}