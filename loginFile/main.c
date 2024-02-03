#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <dirent.h>
#include "DirAndFile.c"

void extractUserId(char temp[], char userId[])
{  
    int i = 0;
    int j = 3;
    while (temp[j] != ' ')
    {
        userId[i] = temp[j];
        i++;
        j++;
    }
}

void extractUserPassword(char *userData,char *passUser){
    int i=0;
    int j=0;
    int count=0;
    while(userData[j]!='\0'){
        if(userData[j]==','){
            count++;
        }
        if(count==3){
            j++;
            while(userData[j]!=','){
                passUser[i++]=userData[j++];
            }
            passUser[i]='\0';
            break; 
        }
        j++;
    }
    }

int checkRestricted(char userName[]){
int i=0;

int flagRestricted=1;
while(1){

 if(userName[i]=='\0'){
    break;
}
 else if(!( (userName[i]<='z'&&userName[i]>='a')||(userName[i]>='A'&&userName[i]<='Z')||(userName[i]>='0'&&userName[i]<='9') )){
flagRestricted=-1;
break;
}

i++;
}// end while 
return flagRestricted;
}
void getPass(char pass[])
{
    int i = 0;
    char temp;
    while (1)
    {
        temp = getch();
        if (temp == '\r')
        {
            pass[i] = '\0';
            break;
        }
        else
        {
            printf("*");
            pass[i] = temp;
            i++;
        }
    } // end while
}
int checkDuplicateUserName(char userName[])
{
    int result=isDirExist(userName); // 1 for true and -1 for false
    return result;
}
void validUserName(char temp[])
{
    while (strlen(temp) > 30 ||checkRestricted(temp)==-1)
    {
        printf("Please give us an input without space and only using alphabet and numbers with max length of 30\n");
        fgets(temp, 100, stdin);
        temp[strlen(temp) - 1] = '\0';
    }
}
void validUserInput(char temp[])
{
    while (strlen(temp) > 30 ||strstr(temp," ")!=0)
    {
        printf("Please give us an input without space with max length of 30\n");
        fgets(temp, 100, stdin);
        temp[strlen(temp) - 1] = '\0';
    }
}
void validUserInputPassEdition(char temp[])
{
    while (strlen(temp) > 30 || strstr(temp, " ") != 0)
    {
        printf("Please give us an input without space and with max length of 30\n");
        getPass(temp);
    }
}
int accountRole()
{
    char input[50];
    int role;
    fgets(input, 50, stdin);
    role = atoi(input);
    while (strlen(input) > 2 || ( role != 1 &&  role != 2))
    {
        printf("Invalid input please select again \n");
        fgets(input, 50, stdin);
        role = atoi(input);
    }
    return  role;
}

void createUserDataPath(char userName[],char filePath[]){
    strcpy(filePath,"UserDataBase\\");
    strcat(filePath,userName);
    strcat(filePath,"\\");
    strcat(filePath,"UserData.txt");
}
void createProductFile(char userName[]){
    char filePath[50];
    strcpy(filePath,"UserDataBase\\");
    strcat(filePath,userName);
    strcat(filePath,"\\");
    strcat(filePath,"products.txt");
    FILE *fptr=fopen(filePath,"w");
    fclose(fptr);
}
void writeUserData(char userName[],char password[],char email[],char phoneNum[],int userRole){
    createDir(userName);
    char filePath[50];
    createUserDataPath(userName,filePath);
    createFile(filePath);
      FILE *fptr = fopen(filePath, "a");
   if(userRole==1){ //1 for sellers
    // for seller we have status,id,pass,email,phonenumber,wallet,score,nscore and another txt for their products
    fprintf(fptr, "%s,%d,%s,%s,%s,%s,%d,%d,%d\n","active",userRole, userName, password, email,phoneNum,0,0,0);
   }
   else if(userRole==2){
    // for buyer we have status,username,pass,email,phonenumber,wallet and another file for their purchased products
    fprintf(fptr, "%s,%d,%s,%s,%s,%s,%d\n","active",userRole, userName, password, email,phoneNum,0);
   }
   fclose(fptr);
  createProductFile(userName);
}
void checkid(char inputUserName[],char userData[]){
    char filePath[50];
    int result=checkDuplicateUserName(inputUserName); // 1 for existed
    if(result==-1){
        strcpy(userData,"failed");
        return ;
    }
    else{
        createUserDataPath(inputUserName,filePath);
        readUserData(filePath,userData);
    }
  
}
int getPath(){
        char path[50];
        fgets(path,50,stdin);
        int pathI=atoi(path);
    
     while (strlen(path) > 2 || ( pathI!= 1 && pathI != 2))
    {
        printf("Invalid input please select again(1 or 2)\n");
        fgets(path, 50, stdin);
        pathI= atoi(path);
    }
    return pathI;
}
int checkPass(char realPass[],char inputPass[]){
       if(strcmp(realPass,inputPass)==0){ // succesffully login
        printf("login succesed\n");
        return 1;
       }
       else{
          printf("password incorrect!\nDo you want to try again another password(select 1)or return to menu(select 2)\n");
          int pathI=getPath();
          if(pathI==1){
            char inputPass[50];
            getPass(inputPass);
            validUserInputPassEdition(inputPass);
            int result=checkPass(realPass,inputPass);
            if(result==1){
                return 1;
            }
            else {
                return -1;
            }
          }
          else {
            return -1;
          }
       }
}

void signup()
{
    char userName[100];
    char password[100];
    char email[100];
    char phoneNum[100];
    printf("Please enter your username (max length : 30)\n");
    fgets(userName, 100, stdin);
    userName[strlen(userName) - 1] = '\0';
    validUserName(userName);
    while (checkDuplicateUserName(userName) == 1) // 1 is for when the account is already existed
    {
        printf("this UserName is already taken, please give us another userName\n");
        fgets(userName, 100, stdin);
        userName[strlen(userName) - 1] = '\0';
        validUserName(userName);
    }
    printf("Please enter your password(we recommend that it is better to use at least 8 charecter)(max length : 30)\n");
    getPass(password);
    validUserInputPassEdition(password);

    printf("Please enter your email:\n");
    fgets(email, 100, stdin);
    email[strlen(email) - 1] = '\0';
    validUserInput(email);
    printf("Please enter your phone number :\n");
    fgets(phoneNum, 100, stdin);
    phoneNum[strlen(phoneNum) - 1] = '\0';
    validUserInput(phoneNum);
    printf("Are you a seller(select 1) or a customer (select 2)\n");
    int userRole = accountRole(userRole);
    /// now lets print all the data on file
    writeUserData(userName,password,email,phoneNum,userRole);
}

void login(){
    char useridInput[50];
    printf("Please give us your userName:(max length 30)\n");
    fgets(useridInput,50,stdin);
    useridInput[strlen(useridInput)-1]='\0';
    validUserName(useridInput);
    char userData[200];
    checkid(useridInput,userData);
    if(strcmp(userData,"failed")==0){ // we dont have  the id 
        printf("We don't have such a UserName\nDo you want to try again another ID(select 1) and or return to menu (select 2)\n");
        int pathI=getPath();
    if(pathI==1){
        login();
    }
    else if (pathI==2){
        return ;
    }
    } // end if UserId
    else{ // now we have the id and we need to check the pass
       char passUser[50];
       char passInput[50];
       extractUserPassword(userData,passUser);
       printf("Please enter your password\n");
       getPass(passInput);
       validUserInputPassEdition(passInput);
       int result=checkPass(passUser,passInput);
       if(result==1){
        // do something with user data
       }
       else if(result==-1){   //return to menu 
        return ;
       }
    }
}

int main()
{
      signup();
    //login();
    //writeUserData("mewmew","idk","pedaret@iahsc","0921867351",2);
    
    return 0;
}
