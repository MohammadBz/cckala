#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <conio.h>
#include "loginSignup.c"
#include "DirAndFile.c"
#include "accountsFunctions.c"

void asciiArt(){
     printf("\x1b[32m");
 FILE *fptr=fopen("asciiArt.txt","r");
 while(!feof(fptr)){
    char temp[100];
    fgets(temp,100,fptr);
    printf("%s",temp);
 }
}
int getPathMenu(){
        char path[50];
        fgets(path,50,stdin);
        int pathI=atoi(path);
    
     while (strlen(path) > 2 || ( pathI!= 1 && pathI != 2&&pathI!=3&&pathI!=4&&pathI!=5))
    {
        printf("-----Invalid input please select again(1 or 2 or 3 or 4 or 5)\n");
        fgets(path, 50, stdin);
        pathI= atoi(path);
    }
    return pathI;
}
void menuText(){
    printf("\n**************************************\n");
   printf("----Welcome!-----\n");
   printf("-----1-Sign up-----\n");
   printf("-----2-Login-----\n");
   printf("-----3-Change password-----\n");
   printf("-----4-forget password-----\n");
   printf("-----5-Exit-----\n");
    printf("**************************************\n");
}
void menu(){
   menuText();
   int path=getPathMenu();
   while(path!=5){
   switch(path){
    case 1:
    signup();
    break;
    case 2:
    login(1);
    break;
    case 3 :
    printf("-----You have to login first :\n");
    login(2);
    break;
    case 4:
    forgetPassword();
    break;
    case 5:
    break;
   }
   menuText();
   path=getPathMenu();
   }
   exit(0);
}

int main() {
   
   asciiArt();
    menu();  
    return 0;
}
