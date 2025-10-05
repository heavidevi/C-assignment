#include <stdio.h>
#include <stdlib.h>



int main(){
    int x,y;
    printf("Enter two integers: ");
    scanf("%d %d",&x,&y);
    
    if (x>0 && y>0){
        printf("The point(%i,%i) lies on quadrant I\n", x, y);
    }else if (x<0 && y>0){
        printf("The point(%i,%i) lies on quadrant II\n", x, y);
    }else if (x<0 && y<0){
        printf("The point(%i,%i) lies on quadrant III\n", x, y);
    }else if (x>0 && y<0){
        printf("The point(%i,%i) lies on quadrant IV\n", x, y);
    }else{
        printf("The point(%i,%i) lies on the origin\n", x, y);
    }
    
}



