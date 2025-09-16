#include <stdio.h>
#include <stdbool.h>

int main(){
    int akhlaq,honesty,zakat,social,conflict;
    bool prayer=false;
    int fasting;
    int fastingScore[]={0,1,2};
    float CI;
    printf("Enter akhlaq:\n");
    scanf("%i", &akhlaq);

    printf("Enter honesty:\n");
    scanf("%i", &honesty);

    printf("Enter zakat:\n");
    scanf("%i", &zakat);

    printf("Enter social:\n");
    scanf("%i", &social);

    printf("Enter conflict:\n");
    scanf("%i", &conflict);

    printf("Enter prayer (1 for regular, 0 for irregular):\n");
    scanf("%i", &prayer);

    printf("Enter fasting (0 for never, 1 for sometimes, 2 for always):\n");
    scanf("%i", &fasting);
    if (fastingScore[fasting]){
        if (akhlaq>=0 && akhlaq<=10 && honesty>=0 && honesty<=10 && zakat>=0 && zakat<=10 && social>=0 && social<=10 && conflict>=0 && conflict<=10){
            CI=(akhlaq*2.5)+(honesty*2.0)+(prayer*15)+(fasting*5.0)+(zakat*1.0)+(social*1.0)-(conflict*1.0);
            if (CI<100 && CI>0)
            {
                if (CI>84){
                    printf("Classification :Excellent Muslim Character\n Remarks:Role model for society");
                }else if(CI>69){
                    printf("Classification :Good Muslim Character 🙂\n Remarks:Practicing believer");
                }else if(CI>49){
                    printf("Classification :Average Character ⚠️\n Remarks:Needs minor improvements");
                }else if(CI>29){
                    printf("Classification :Needs Improvement ❗\n Remarks:Work on Akhlaq & Ibadah");
                }else{
                    printf("Classification :Weak Character ❌\n Remarks:Requires serious guidance");
                }
                return 0;
            }else{
                printf("invalid CI");
                return 0;
            }

        }else{
            printf("invalid input");
            return 0;
        }


    }else{
        printf("invalid fasting input");
        return 0;
    }
}
