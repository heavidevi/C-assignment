#include <stdio.h>
int main(){
   int c1, c2, c3, c4, c5;
   int count1 = 1, count2 = 1, count3 = 1, count4 = 1, count5 = 1;
   printf("Enter 5 numbers (Your hand): ");
   scanf("%d %d %d %d %d", &c1, &c2, &c3, &c4, &c5);
   printf("%d %d %d %d %d\n", c1, c2, c3, c4, c5);

  
   if (c2 == c1) count1++;
   if (c3 == c1) count1++;
   if (c4 == c1) count1++;
   if (c5 == c1) count1++;
   
   if (c1==c2) count2++;
   
   if (c3==c2) count2++;
   if (c4==c2) count2++;
   if (c5==c2) count2++;

   if (c1==c3) count3++;
    if (c2==c3) count3++;
    if (c4==c3) count3++;
    if (c5==c3) count3++;

    
    if (c1==c4) count4++;
    if (c2==c4) count4++;
    if (c3==c4) count4++;
    if (c5==c4) count4++;

   
    if (c1==c5) count5++;
    if (c2==c5) count5++;
    if (c3==c5) count5++;
    if (c4==c5) count5++;
   
   if ((count1==3 && (count2==2 || count3==2 || count4==2 || count5==2)) ||
        (count2==3 && (count1==2 || count3==2 || count4==2 || count5==2)) ||
        (count3==3 && (count1==2 || count2==2 || count4==2 || count5==2)) ||
        (count4==3 && (count1==2 || count2==2 || count3==2 || count5==2)) ||
        (count5==3 && (count1==2 || count2==2 || count3==2 || count4==2))) {
        printf("Full House\n");
    } else {
        printf("Not a Full House\n");
    }
   

   return 0;
}