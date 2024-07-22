#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <conio.h>


void extractUserName(char userData[], char userId[])
{  
    int i = 0;
    int j=0;
    int count=0;
    while (userData[i] != '\0')
    {
        if(userData[i]==','){
            count++;
        }
        if(count==2){
            i++;
            while(userData[i]!=','){
                userId[j++]=userData[i++];
            }
            userId[j]='\0';
            break;
        }
        i++;
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
void extractUserEmail(char *userData,char *userEmail){
int i=0;
int j=0;
int count=0;
while(userData[i]!='\0'){
    if(userData[i]==','){
        count++;
    }
    if(count==4){
        i++;
        while(userData[i]!=','){
            userEmail[j++]=userData[i++];
        }
        userEmail[j]='\0';
        break;
    }
    i++;
}
}
void extractUserPhoneNum(char *userData,char *userPhoneNum){
int i=0;
int j=0;
int count=0;
while(userData[i]!='\0'){
    if(userData[i]==','){
        count++;
    }
    if(count==5){
        i++;
        while(userData[i]!=','){
            userPhoneNum[j++]=userData[i++];
        }
        userPhoneNum[j]='\0';
        break;
    }
    i++;
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
    printf("\n");
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
        printf("-----Please give us an input without space and only using alphabet and numbers with max length of 30\n");
        fgets(temp, 100, stdin);
        temp[strlen(temp) - 1] = '\0';
    }
}
void validUserInput(char temp[])
{
    while (strlen(temp) > 30 ||strstr(temp," ")!=0||strstr(temp,","))
    {
        printf("-----Please give us an input without space and \",\" with max length of 30\n");
        fgets(temp, 100, stdin);
        temp[strlen(temp) - 1] = '\0';
    }
}
void validUserInputCommentEdition(char temp[])
{
    while (strlen(temp) > 480 ||strstr(temp,","))
    {
        printf("-----Please give us an input without space and \",\" with max length of 500\n");
        fgets(temp, 500, stdin);
        temp[strlen(temp) - 1] = '\0';
    }
}
void validUserInputProductEdition(char temp[])
{
    while (strlen(temp) > 190||strstr(temp,","))
    {
        printf("-----Please give us an input without \",\" with max length of 200\n");
        fgets(temp, 200, stdin);
        temp[strlen(temp) - 1] = '\0';
    }
}
void validUserInputPassEdition(char temp[])
{
    while (strlen(temp) > 30 || strstr(temp, " ") != 0||strstr(temp,","))
    {
        printf("-----Please give us an input without space and \",\" with max length of 30\n");
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
        printf("-----Invalid input please select again \n");
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
void writeNewUserData(char userName[],char password[],char email[],char phoneNum[],int userRole){
    createDir(userName);
    char filePath[50];
    createUserDataPath(userName,filePath);
    createFile(filePath);
      FILE *fptr = fopen(filePath, "a");
   if(userRole==1){ //1 for sellers
    // for seller we have status,id,pass,email,phonenumber,wallet,score,nscore and another txt for their products
    fprintf(fptr, "%s,%d,%s,%s,%s,%s,%d,%d,%d,","active",userRole, userName, password, email,phoneNum,0,0,0);
   }
   else if(userRole==2){
    // for buyer we have status,username,pass,email,phonenumber,wallet and another file for their purchased products
    fprintf(fptr, "%s,%d,%s,%s,%s,%s,%d,","active",userRole, userName, password, email,phoneNum,0);
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
        printf("-----Invalid input please select again(1 or 2)\n");
        fgets(path, 50, stdin);
        pathI= atoi(path);
    }
    return pathI;
}
int extractUserRole(char UserData[]){
int role;
int i=0;
while(UserData[i]!='\0'){
    if(UserData[i]==','){
        i++;
        role=UserData[i]-'0';
        return role;
    }
    i++;
}
return 0;
}
int checkPass(char realPass[],char inputPass[]){
       if(strcmp(realPass,inputPass)==0){ // succesffully login
        printf("-----login succeed\n");
        return 1;
       }
       else{
          printf("-----password incorrect!\nDo you want to try again another password(select 1)or return to menu(select 2)\n");
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
int checkEmailandPhone(char userData[]){
char userEmail[50];
char userPhoneNum[50];
char userInputEmail[200];
char userInputPhoneNum[200];
extractUserEmail(userData,userEmail);
extractUserPhoneNum(userData,userPhoneNum);
printf("-----Please give us your email:\n");
fgets(userInputEmail,100,stdin);
userInputEmail[strlen(userInputEmail)-1]='\0';
validUserInput(userInputEmail);
printf("-----Please give us your Phone Numebr:\n");
fgets(userInputPhoneNum,100,stdin);
userInputPhoneNum[strlen(userInputPhoneNum)-1]='\0';
validUserInput(userInputPhoneNum);

int flag=-1;
if(strcmp(userEmail,userInputEmail)==0&&strcmp(userPhoneNum,userInputPhoneNum)==0){
    flag=1;
}
if(flag==-1){
    printf("-----InCorrect! Do you want to try another email and phonenumber(select 1) or return to menu(select 2)?\n");
    int path=getPath();
    if(path==1){
        flag=checkEmailandPhone(userData);
    }
    else if(path==2){
        return -1;
    }
}
return flag;
}
void writeEditedUserData(char userData[],char userName[]){
    char filePath[100];
    createUserDataPath(userName,filePath);
    FILE *fptr=fopen(filePath,"w");
    fprintf(fptr,"%s",userData);
    fclose(fptr);
    printf("-----Password successfully changed\n");
}

void ChangePassword(char userData[]){
char prev[100];
int prevCounter=0;
char next[100];
int nextConter=0;
char newpass[100];
printf("-----Please give us your new password :\n");
getPass(newpass);
validUserInputPassEdition(newpass);
int i=0;
int count=0;
while(userData[i]!='\0'){
    if(userData[i]==','){
        count++;
    }
    if(count<3){
     prev[prevCounter]=userData[i];
     prevCounter++;
    }
    prev[prevCounter]='\0';
    if(count>=4){
        next[nextConter]=userData[i];
        nextConter++;
    }
    next[nextConter]='\0';
    i++;
}
char newUserData[200]={'\0'}; 
strcat(newUserData,prev);
strcat(newUserData,",");
strcat(newUserData,newpass);
strcat(newUserData,next);
char userName[50];
extractUserName(newUserData,userName);
writeEditedUserData(newUserData,userName);
}

void signup()
{
    char userName[100];
    char password[100];
    char email[100];
    char phoneNum[100];
    printf("-----Please enter your username (max length : 30)\n");
    fgets(userName, 100, stdin);
    userName[strlen(userName) - 1] = '\0';
    validUserName(userName);
    while (checkDuplicateUserName(userName) == 1) // 1 is for when the account is already existed
    {
        printf("-----this UserName is already taken, please give us another userName\n");
        fgets(userName, 100, stdin);
        userName[strlen(userName) - 1] = '\0';
        validUserName(userName);
    }
    printf("-----Please enter your password(we recommend that it is better to use at least 8 charecter)(max length : 30)\n");
    getPass(password);
    validUserInputPassEdition(password);

    printf("-----Please enter your email:\n");
    fgets(email, 100, stdin);
    email[strlen(email) - 1] = '\0';
    validUserInput(email);
    printf("-----Please enter your phone number :\n");
    fgets(phoneNum, 100, stdin);
    phoneNum[strlen(phoneNum) - 1] = '\0';
    validUserInput(phoneNum);
    printf("-----Are you a seller(select 1) or a customer (select 2)\n");
    int userRole = accountRole(userRole);
    /// now lets print all the data on file
    writeNewUserData(userName,password,email,phoneNum,userRole);
        if(userRole==3){
            admin();
        }
        else if(userRole==1){
            seller(userName);
        }
        else if(userRole==2){
            buyer(userName);
        }
}


void forgetPassword(){
    char useridInput[50];
    printf("-----Please give us your userName:(max length 30)\n");
    fgets(useridInput,50,stdin);
    useridInput[strlen(useridInput)-1]='\0';
    validUserName(useridInput);
    char userData[200];
    checkid(useridInput,userData);
    if(strcmp(userData,"failed")==0){ // we dont have  the id 
        printf("-----We don't have such a UserName\nDo you want to try again another ID(select 1) and or return to menu (select 2)\n");
        int pathI=getPath();
    if(pathI==1){
      forgetPassword();
    }
    else if (pathI==2){
        menu();
        return ;
    }
}
  int result=checkEmailandPhone(userData);
  if (result==-1){
     menu();
     return ;
  }
  else{
  ChangePassword(userData);
  }
}

void login(int code){
    char useridInput[50];
    printf("-----Please give us your userName:(max length 30)\n");
    fgets(useridInput,50,stdin);
    useridInput[strlen(useridInput)-1]='\0';
    validUserName(useridInput);
    char userData[200];
    checkid(useridInput,userData);
    if(strcmp(userData,"failed")==0){ // we dont have  the id 
        printf("-----We don't have such a UserName\nDo you want to try again another ID(select 1) and or return to menu (select 2)\n");
        int pathI=getPath();
    if(pathI==1){
      login(code);
    }
    else if (pathI==2){
        menu();
    }
    } // end if UserId
    else{ // now we have the id and we need to check the pass
       char passUser[50];
       char passInput[50];
       extractUserPassword(userData,passUser);
       printf("-----Please enter your password\n");
       getPass(passInput);
       validUserInputPassEdition(passInput);
       int result=checkPass(passUser,passInput);
       if(result==1){ // code 1 for normal login and 2 for change password
        if(code==2){
          ChangePassword(userData);
        }
        int role=extractUserRole(userData);
        if(role==3){
            admin();
        }
        else if(role==1){
            seller(useridInput);
        }
        else if(role==2){
            buyer(useridInput);
        }
       }
       else if(result==-1){   //return to menu 
        menu();
       }
    }
}
/*
int main()
{
      //signup();
    //login();
    //writeNewUserData("mewmew","idk","pedaret@iahsc","0921867351",2);
    
    return 0;
}
*/