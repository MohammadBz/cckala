
int isDirExist(char userName[]){
    char directoryPath[50];
    strcpy(directoryPath,"UserDataBase\\");
    strcat(directoryPath,userName);
    DIR *d;
    int result=1;
    d = opendir(directoryPath);
    if(!d){
        closedir(d);
        result =-1;
        return result;
    }
    closedir(d);
    return result;
}

int createDir(char userName[]){
    char path[50];
    strcpy(path,"UserDataBase\\");
    strcat(path,userName);
    int result = mkdir(path);
    return result;
}

void readUserData(char *filePath,char *userData){
FILE *fptr=fopen(filePath,"r");
fgets(userData,200,fptr);
fclose(fptr);
}

void createFile(char filePath[]){
    FILE *fptr=fopen(filePath,"w");
    fclose(fptr);
}
