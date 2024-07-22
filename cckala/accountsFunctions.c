#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <conio.h>
#include <time.h>

struct buyer
{
    char status[10];
    char userName[50];
    char pass[50];
    char email[50];
    char phoneNum[50];
    float wallet;
};
struct seller
{
    char status[10];
    char userName[50];
    char pass[50];
    char email[50];
    char phoneNum[50];
    float wallet;
    int nscore;
    float score;
};
struct product
{
    char status[10];
    int category;
    char id[50];
    char productName[50];
    char content[200];
    int amount;
    float price;
};
struct productLineInfo
{
    char temp[200];
};
struct user
{
    char userName[200];
};
struct sellerP{
    char ID[50];
    int amount;
    float Price; 
    char Name[50];
};
void writeSellerEditedData(struct seller sellerTemp)
{
    char filePath[100] = {'\0'};
    createUserDataPath(sellerTemp.userName, filePath);
    FILE *fptr = fopen(filePath, "w");
    fprintf(fptr, "%s,%d,%s,%s,%s,%s,%f,%f,%d,", sellerTemp.status, 1, sellerTemp.userName, sellerTemp.pass, sellerTemp.email, sellerTemp.phoneNum, sellerTemp.wallet, sellerTemp.score, sellerTemp.nscore);
    fclose(fptr);
}
void writeBuyerEditedData(struct buyer buyerTemp)
{
    char filePath[100] = {'\0'};
    createUserDataPath(buyerTemp.userName, filePath);
    FILE *fptr = fopen(filePath, "w");
    fprintf(fptr, "%s,%d,%s,%s,%s,%s,%f,", buyerTemp.status, 2, buyerTemp.userName, buyerTemp.pass, buyerTemp.email, buyerTemp.phoneNum, buyerTemp.wallet);
    fclose(fptr);
}

int getRandNumber()
{
    srand(time(0));
    return rand();
}

int ReadFromDirectoryForUser(char *directoryPath, struct user *allUsers)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(directoryPath);
    int count = 0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            // printf("%s\n", dir->d_name);
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                strcpy(allUsers[count].userName, dir->d_name);
                count++;
            }
        }
        closedir(d);
    }
    return count;
}

int getPathAdminMenu()
{
    char path[50];
    fgets(path, 50, stdin);
    int pathI = atoi(path);

    while (strlen(path) > 2 || (pathI != 1 && pathI != 2 && pathI != 3 && pathI != 4 && pathI != 5 && pathI != 6 && pathI != 7 && pathI != 8))
    {
        printf("-----Invalid input please select again(1 or 2 or 3 or 4 or 5 or 6 or 7 or 8)\n");
        fgets(path, 50, stdin);
        pathI = atoi(path);
    }
    return pathI;
}
int getPathSellerMenu()
{
    char path[50];
    fgets(path, 50, stdin);
    int pathI = atoi(path);

    while (strlen(path) > 2 || (pathI != 1 && pathI != 2 && pathI != 3 && pathI != 4))
    {
        printf("-----Invalid input please select again(1 or 2 or 3 or 4)\n");
        fgets(path, 50, stdin);
        pathI = atoi(path);
    }
    return pathI;
}
int getPathBuyerMenu()
{
    char path[50];
    fgets(path, 50, stdin);
    int pathI = atoi(path);

    while (strlen(path) > 2 || (pathI != 1 && pathI != 2 && pathI != 3 && pathI != 4 && pathI != 5))
    {
        printf("-----Invalid input please select again(1 or 2 or 3 or 4 or 5)\n");
        fgets(path, 50, stdin);
        pathI = atoi(path);
    }
    return pathI;
}

void extractUserAnything(char *userData, char *userSpecifiedData, int limit)
{
    int i = 0;
    int j = 0;
    int count = 0;
    while (userData[i] != '\0')
    {
        if (userData[i] == ',')
        {
            count++;
        }
        if (count == limit)
        {
            if (count != 0 && userData[i] == ',')
            {
                i++;
            }
            while (userData[i] != ',' && userData[i] != '\0')
            {
                userSpecifiedData[j++] = userData[i++];
            }
            userSpecifiedData[j] = '\0';
            break;
        }
        i++;
    }
}

float extractUserWallet(char *userData, int limit)
{
    int i = 0;
    int j = 0;
    int count = 0;
    char userSpecifiedData[30] = {'\0'};
    while (userData[i] != '\0')
    {
        if (userData[i] == ',')
        {
            count++;
        }
        if (count == limit)
        {
            if (count != 0&& userData[i] == ',')
            {
                i++;
            }
            while (userData[i] != ','&& userData[i] != '\0')
            {
                userSpecifiedData[j++] = userData[i++];
            }
            userSpecifiedData[j] = '\0';
            break;
        }
        i++;
    }
    float result = atof(userSpecifiedData);
    return result;
}
int extractUserNScore(char *userData, int limit)
{
    int i = 0;
    int j = 0;
    int count = 0;
    char userSpecifiedData[30] = {'\0'};
    while (userData[i] != '\0')
    {
        if (userData[i] == ',')
        {
            count++;
        }
        if (count == limit)
        {
            if (count != 0&& userData[i] == ',')
            {
                i++;
            }
            while (userData[i] != ','&& userData[i] != '\0')
            {
                userSpecifiedData[j++] = userData[i++];
            }
            userSpecifiedData[j] = '\0';
            break;
        }
        i++;
    }
    int result = atoi(userSpecifiedData);
    return result;
}

void fillBuyerData(struct buyer *buyer, char userData[])
{
    extractUserAnything(userData, buyer->userName, 2);
    extractUserAnything(userData, buyer->pass, 3);
    extractUserAnything(userData, buyer->email, 4);
    extractUserAnything(userData, buyer->phoneNum, 5);
    extractUserAnything(userData, buyer->status, 0);
    buyer->wallet = extractUserWallet(userData, 6);
}
void fillProductData(struct product *newProduct, char productData[])
{
    // active,shotgun,1,4,it kills you with one bullet,
    extractUserAnything(productData, newProduct->status, 0);
    extractUserAnything(productData, newProduct->productName, 1);
    extractUserAnything(productData, newProduct->content, 4);
    newProduct->category = extractUserNScore(productData, 3);
}
void fillSellerData(struct seller *seller, char userData[])
{
    extractUserAnything(userData, seller->userName, 2);
    extractUserAnything(userData, seller->pass, 3);
    extractUserAnything(userData, seller->email, 4);  
    extractUserAnything(userData, seller->phoneNum, 5);
    extractUserAnything(userData, seller->status, 0);
    seller->wallet = extractUserWallet(userData, 6);
    
    seller->score = extractUserWallet(userData, 7);
    
    seller->nscore = extractUserNScore(userData, 8);
}

float fillProductPrice(struct product newProduct)
{
    char sellerPath[50];
    createProductSellerPath(newProduct.productName, sellerPath);
    FILE *fptr = fopen(sellerPath, "r");
    float price = 0;
    int nprice = 0;
    char temp[100];
    while (fgets(temp, 100, fptr) != NULL)
    {
        if (strlen(temp) > 5)
        {
            float TempNum = extractUserWallet(temp, 3);
            price += TempNum;
            nprice++;
        }
    }
    fclose(fptr);
    if (nprice == 0)
    {
        return 0;
    }
    float averagePrice = price / nprice;
    return averagePrice;
}
int fillProductAmount(struct product newProduct)
{
    char sellerPath[50];
    createProductSellerPath(newProduct.productName, sellerPath);
    FILE *fptr = fopen(sellerPath, "r");
    float amount = 0;
    char temp[100];
    while (fgets(temp, 100, fptr) != NULL)
    {
        if (strlen(temp) > 5)
        {
            int TempNum = extractUserNScore(temp, 2);
            amount += TempNum;
        }
    }
    fclose(fptr);
    if (amount == 0)
    {
        return 0;
    }
    return amount;
}

 int fillListOfSeller(struct sellerP sellerArr[],struct product newProduct){
       char sellerPath[50];
    createProductSellerPath(newProduct.productName, sellerPath);
     FILE *fptr = fopen(sellerPath, "r");
     int count=0;
      char temp[100];
    while (fgets(temp, 100, fptr) != NULL)
    {
        if (strlen(temp) > 5)
        {
            sellerArr[count].Price=extractUserWallet(temp,3);
             extractUserAnything(temp,sellerArr[count].ID,0);
             extractUserAnything(temp,sellerArr[count].Name,1);
            sellerArr[count].amount=extractUserNScore(temp,2);
            count++;
        }
    }
    
    fclose(fptr);
     return count;
 }

float fillProductScore(struct product newProduct)
{
    char commentPath[50];
    createProductCommentPath(newProduct.productName, commentPath);
    FILE *fptr = fopen(commentPath, "r");
    float Score = 0;
    int nscore = 0;
    char temp[100];
    while (fgets(temp, 100, fptr) != NULL)
    {
        if (strlen(temp) > 5)
        {
            float TempNum = extractUserWallet(temp,1);
            Score += TempNum;
            nscore++;
        }
    }
    fclose(fptr);
    if (nscore == 0)
    {
        return 0;
    }
    float averagePrice = Score / nscore;
    return averagePrice;
}

int extractAllUsersData(struct buyer buyerArr[], struct seller sellerArr[], int *buyerCount, int *sellerCount, struct user allUsersName[])
{
    int buyerCountTemp = 0;
    int sellerCountTemp = 0;
    int countAllUser = ReadFromDirectoryForUser("UserDataBase", allUsersName);
    for (int i = 0; i < countAllUser; i++)
    {
        char filePath[100] = {'\0'};
        char userData[200] = {'\0'};
        createUserDataPath(allUsersName[i].userName, filePath);
        readUserData(filePath, userData);
        int role = extractUserRole(userData);
        if (role == 1)
        { // seller
            fillSellerData(&sellerArr[sellerCountTemp], userData);
            sellerCountTemp++;
        }
        else if (role == 2)
        { // buyer
            fillBuyerData(&buyerArr[buyerCountTemp], userData);
            buyerCountTemp++;
        }
    }
    *buyerCount = buyerCountTemp;
    *sellerCount = sellerCountTemp;
    return countAllUser;
}
void viewAllSellers(struct seller sellerArr[], int sellerCount)
{
    printf("-----sellers are:\n");
    for (int i = 0; i < sellerCount; i++)
    {
        if (strcmp("inactive", sellerArr[i].status) != 0)
        {
            printf("-----UserName:%s-----Score:%f\n", sellerArr[i].userName, sellerArr[i].score);
        }
    }
}
void viewAllBuyers(struct buyer buyerArr[], int buyerCount)
{
    printf("-----buyers are:\n");
    for (int i = 0; i < buyerCount; i++)
    {
        if (strcmp("inactive", buyerArr[i].status) != 0)
        {
            printf("-----UserName:%s-----Email:%s\n", buyerArr[i].userName, buyerArr[i].email);
        }
    }
}
void viewSpecifiedUserInfo(struct user allUsersName[], int countAllUser)
{
    printf("Please enter the UserName:\n");
    char inputUserName[100];
    fgets(inputUserName, 100, stdin);
    inputUserName[strlen(inputUserName) - 1] = '\0';
    validUserName(inputUserName);
    int flag = -1;
    int i;
    for (i = 0; i < countAllUser; i++)
    {
        if (strcmp(inputUserName, allUsersName[i].userName) == 0)
        {
            flag = 0;
            break;
        }
    }
    if (flag == 0)
    {
        char filePath[100] = {'\0'};
        char userData[200] = {'\0'};
        createUserDataPath(allUsersName[i].userName, filePath);
        readUserData(filePath, userData);
        int role = extractUserRole(userData);
        if (role == 1)
        { // seller
            struct seller sellerTemp;
            fillSellerData(&sellerTemp, userData);
            printf("----status:%s--userName:%s--Password:%s--role:%s--email:%s--phoneNumber:%s--Wallet:%.3f--Score--%.2f-----\n\n", sellerTemp.status, sellerTemp.userName, sellerTemp.pass, "Seller", sellerTemp.email, sellerTemp.phoneNum, sellerTemp.wallet, sellerTemp.score);
            return;
        }
        else if (role == 2)
        { // buyer
            struct buyer buyerTemp;
            fillBuyerData(&buyerTemp, userData);
            printf("----status:%s--userName:%s--Password:%s--role:%s--email:%s--phoneNumber:%s--Wallet:%.3f-----\n\n", buyerTemp.status, buyerTemp.userName, buyerTemp.pass, "Buyer", buyerTemp.email, buyerTemp.phoneNum, buyerTemp.wallet);
            return;
        }
    }
    else if (flag == -1)
    {
        printf("----We dont have such a userName return to menu and try again\n");
    }
}
float changeWallet(float wallet)
{
    float changeValue = 0;
    printf("DO you want to increase(select 1) or decrease it (select 2)?\n");
    int path = getPath();
    if (path == 1)
    {
        printf("How Much Do you want to add?\n");
        scanf("%f", &changeValue);
        wallet += changeValue;
    }
    else if (path == 2)
    {
        printf("How Much Do you want to reduce?\n");
        scanf("%f", &changeValue);
        wallet -= changeValue;
    }
    return wallet;
}
void CheckWallet(struct user allUsersName[], int countAllUser)
{ // enter problem with scanf
    printf("Please enter the UserName:\n");
    char inputUserName[100];
    fgets(inputUserName, 100, stdin);
    inputUserName[strlen(inputUserName) - 1] = '\0';
    validUserName(inputUserName);
    int flag = -1;
    int i;
    for (i = 0; i < countAllUser; i++)
    {
        if (strcmp(inputUserName, allUsersName[i].userName) == 0)
        {
            flag = 0;
            break;
        }
    }
    if (flag == 0)
    {
        char filePath[100] = {'\0'};
        char userData[200] = {'\0'};
        createUserDataPath(allUsersName[i].userName, filePath);
        readUserData(filePath, userData);
        int role = extractUserRole(userData);
        if (role == 1)
        { // seller
            struct seller sellerTemp;
            fillSellerData(&sellerTemp, userData);
            printf("----userName:%s--Wallet:%.3f\n", sellerTemp.userName, sellerTemp.wallet);
            printf("Do you want to Change it?(select 1 for yes and 2 for no)\n");
            int path = getPath();
            if (path == 1)
            {
                sellerTemp.wallet = changeWallet(sellerTemp.wallet);
                writeSellerEditedData(sellerTemp);
                return;
            }
            else if (path == 2)
            {
                return;
            }
        }
        else if (role == 2)
        { // buyer
            struct buyer buyerTemp;
            fillBuyerData(&buyerTemp, userData);
            printf("----userName:%s--Wallet:%.3f\n", buyerTemp.userName, buyerTemp.wallet);
            printf("Do you want to Change it?(select 1 for yes and 2 for no)\n");
            int path = getPath();
            if (path == 1)
            {
                buyerTemp.wallet = changeWallet(buyerTemp.wallet);
                writeBuyerEditedData(buyerTemp);
                return;
            }
            else if (path == 2)
            {
                return;
            }
        }
    }
    else if (flag == -1)
    {
        printf("----We dont have such a userName return to menu and try again\n");
    }
}
void intToString(int num, char *str)
{
    sprintf(str, "%d", num);
}
void createIDForProduct(char id[], char ProductName[])
{
    id[0] = '\0';
    int randNum = getRandNumber() % 10000;
    char num[6];
    intToString(randNum, num);
    strcat(id, ProductName);
    strcat(id, "#");
    strcat(id, num);
}
void createProductDataPath(char ProductName[], char filePath[])
{
    strcpy(filePath, "ProductDataBase\\");
    strcat(filePath, ProductName);
    strcat(filePath, "\\");
    strcat(filePath, "ProductData.txt");
}
void createProductSellerPath(char ProductName[], char filePath[])
{
    strcpy(filePath, "ProductDataBase\\");
    strcat(filePath, ProductName);
    strcat(filePath, "\\");
    strcat(filePath, "seller.txt");
}
void createProductCommentPath(char ProductName[], char filePath[])
{
    strcpy(filePath, "ProductDataBase\\");
    strcat(filePath, ProductName);
    strcat(filePath, "\\");
    strcat(filePath, "comment.txt");
}
void createUserProductsPath(char userName[], char filePath[])
{
    strcpy(filePath, "UserDataBase\\");
    strcat(filePath, userName);
    strcat(filePath, "\\");
    strcat(filePath, "products.txt");
}
void writeNewSellerForProduct(char *userName, struct product newproduct, char *filepath)
{
    FILE *fptr = fopen(filepath, "a");
    // status,id,SellerName,amount,price
    fprintf(fptr, "%s,%s,%d,%f,\n", newproduct.id, userName, fillProductAmount(newproduct), newproduct.price);
    fclose(fptr);
}
void writeNewSellerForProductInUserDirectory(char *userName, struct product newproduct, char *filepath)
{
    FILE *fptr = fopen(filepath, "a");
    // status,id,SellerName,amount,price
    fprintf(fptr, "%s,%s,%d,%f,\n", newproduct.id, newproduct.productName, fillProductAmount(newproduct), newproduct.price);
    fclose(fptr);
}
int checkDuplicateProduct(char productName[])
{
    int result = isDirExistProductVersion(productName); // 1 for true and -1 for false
    return result;
}

void addSellerForProduct(char *userName, struct product newproduct)
{
    char filePath[50];
    createProductSellerPath(newproduct.productName, filePath);
    writeNewSellerForProduct(userName, newproduct, filePath);
}

void writeEditedProductData(struct product newProduct, char filePath[])
{
    FILE *fptr = fopen(filePath, "w");
    // status,name,amount,category,content,
    fprintf(fptr, "%s,%s,%d,%d,%s,", newProduct.status, newProduct.productName, fillProductAmount(newProduct), newProduct.category, newProduct.content);
    fclose(fptr);
}

createNewProductFiles(struct product newProduct)
{
    createDirProductEdition(newProduct.productName);
    char filePath1[50];
    createProductDataPath(newProduct.productName, filePath1);
    char filePath2[50];
    createProductSellerPath(newProduct.productName, filePath2);
    char filePath3[50];
    createProductCommentPath(newProduct.productName, filePath3);
    writeEditedProductData(newProduct, filePath1);
    FILE *fptr = fopen(filePath3, "w");
    fclose(fptr);
}
void addToUserSellerProducts(char *userName, struct product newProduct)
{
    char filePath[50];
    createUserProductsPath(userName, filePath);
    writeNewSellerForProductInUserDirectory(userName, newProduct, filePath);
}

void createProduct(char userName[])
{
    struct product newProduct;
    strcpy(newProduct.status, "active");
    printf("-----What is your product Name?\n");
    fgets(newProduct.productName, 100, stdin);
    newProduct.productName[strlen(newProduct.productName) - 1] = '\0';
    validUserName(newProduct.productName);
    int path = checkDuplicateProduct(newProduct.productName);
    createIDForProduct(newProduct.id, newProduct.productName);
    printf("-----How many of %s Do you provide?\n", newProduct.productName);
    char inputAmount[50];
    fgets(inputAmount, 50, stdin);
    inputAmount[strlen(inputAmount) - 1] = '\0';
    newProduct.amount = atoi(inputAmount);
    printf("-----How much is your price for every %s ?\n", newProduct.productName);
    char inputPrice[50];
    fgets(inputPrice, 50, stdin);
    inputPrice[strlen(inputPrice) - 1] = '\0';
    newProduct.price = atof(inputPrice);
    if (path == 1)
    { // already existed product
    }
    else
    { // new product
        printf("-----What is the category of your Product?\n-----1-Food\n-----2-Clothes\n-----3-cosmetic\n-----4-Digital Products\n");
        newProduct.category = getPathSellerMenu();
        printf("-----Describe the content of your Product\n");
        fgets(newProduct.content, 200, stdin);
        newProduct.content[strlen(newProduct.content) - 1] = '\0';
        validUserInputProductEdition(newProduct.content);
        createNewProductFiles(newProduct);
    }
    addSellerForProduct(userName, newProduct);
    addToUserSellerProducts(userName, newProduct);
}
int findProductNameByID(char inputID[], char filePath[], char productName[], struct productLineInfo userLineArr[])
{
    FILE *fptr = fopen(filePath, "r");
    int i = 0;
    while (!feof(fptr))
    {
        char temp[100] = {'\0'};
        char productID[50] = {'\0'};
        fgets(temp, 100, fptr);
        extractUserAnything(temp, productID, 0);
        if (strcmp(productID, inputID) == 0)
        {
            extractUserAnything(temp, productName, 1);
        }
        if (strlen(temp) > 5)
        {
            strcpy(userLineArr[i].temp, temp);
        }
        i++;
    }

    return i;
}
int removeProductByName(struct productLineInfo userLineArr[], int lines, char productID[], char filePath[])
{
    FILE *fptr = fopen(filePath, "w");
    int flag = 0;
    for (int i = 0; i < lines; i++)
    {
        char tempProductID[50] = {'\0'};
        extractUserAnything(userLineArr[i].temp, tempProductID, 0);
        if (strcmp(tempProductID, productID) != 0)
        {
            fprintf(fptr, "%s", userLineArr[i].temp);
        }
        else if (strcmp(tempProductID, productID) == 0)
        {
            flag = -1;
        }
    }
    return flag;
}

void RemoveProduct(char userName[])
{
    char filePathUser[50];
    struct productLineInfo userLineArr[50];
    struct productLineInfo ProductLineArr[50];
    char filePathProduct[50];
    char inputID[50];
    char productName[50];
    int userLine = -1;
    int productLine = -1;
    printf("-----Please give your product ID\n");
    fgets(inputID, 50, stdin);
    inputID[strlen(inputID) - 1] = '\0';
    validUserInput(inputID);
    createUserProductsPath(userName, filePathUser);
    int lines = findProductNameByID(inputID, filePathUser, productName, userLineArr);
    int flag = removeProductByName(userLineArr, lines, inputID, filePathUser);
    if (flag == 0)
    {
        printf("-----You dont have that Product\n");
        return;
    }
    createProductSellerPath(productName, filePathProduct);
    lines = findProductNameByID(inputID, filePathProduct, productName, ProductLineArr);
    removeProductByName(ProductLineArr, lines, inputID, filePathProduct);
    // createProductSellerPath()
}
void seeWalletSeller(char userName[])
{
    char UserDataPath[50];
    char userData[50];
    createUserDataPath(userName, UserDataPath);
    readUserData(UserDataPath, userData);
    struct seller sellerTemp;
    fillSellerData(&sellerTemp, userData);
    printf("----userName:%s--Wallet:%.3f\n", sellerTemp.userName, sellerTemp.wallet);
}
int extractAllProduct(struct product productArr[], struct user allproductsName[])
{

    int productsNum = ReadFromDirectoryForUser("ProductDataBase", allproductsName);
    for (int i = 0; i < productsNum; i++)
    {
        char proDataBasepath[50] = {'\0'};
        createProductDataPath(allproductsName[i].userName, proDataBasepath);
        char ProductData[100] = {'\0'};
        readProductData(proDataBasepath, ProductData);
        fillProductData(&productArr[i], ProductData);
    }
    return productsNum;
}
void viewTheListOfGoods(struct product productArr[], int productCount)
{
    printf("-----Here is the list of Products:\n");
    for (int i = 0; i < productCount; i++)
    {
        if (strcmp(productArr[i].status, "active") == 0)
        {
            printf("----ProductName:%s--average price:%.3f--amount:%d--score:%.3f\n", productArr[i].productName, fillProductPrice(productArr[i]), fillProductAmount(productArr[i]),fillProductScore(productArr[i])); ///// emtiaz ham baytad biad
        }
    }
}
void viewTheListOfGoodsSellerEdition(struct product productArr[], int productCount)
{
    printf("-----Here is the list of available Products:\n");
    for (int i = 0; i < productCount; i++)
    {
        if (strcmp(productArr[i].status, "active") == 0)
        {
            printf("----ProductName:%s--average price:%.3f--amount:%d--score:%.3f\n", productArr[i].productName, fillProductPrice(productArr[i]), fillProductAmount(productArr[i]),fillProductScore(productArr[i])); ///// emtiaz ham baytad biad
        }
    }
}

void RemoveProductAdminEdition(char userName[], char inputID[])
{
    char filePathUser[50];
    struct productLineInfo userLineArr[50];
    struct productLineInfo ProductLineArr[50];
    char filePathProduct[50];
    char productName[50];
    int userLine = -1;
    int productLine = -1;
    createUserProductsPath(userName, filePathUser);
    int lines = findProductNameByID(inputID, filePathUser, productName, userLineArr);

    createProductSellerPath(productName, filePathProduct);
    lines = findProductNameByID(inputID, filePathProduct, productName, ProductLineArr);
    removeProductByName(ProductLineArr, lines, inputID, filePathProduct);
    // createProductSellerPath()
}

void RemoveSeller(struct seller sellerArr[], int sellerCount)
{
    char sellerInput[50];
    printf("-----Please give us UserName\n");
    fgets(sellerInput, 100, stdin);
    sellerInput[strlen(sellerInput) - 1] = '\0';
    validUserName(sellerInput);
    int flag = 0;
    int i = 0;
    for (i = 0; i < sellerCount; i++)
    {
        if (strcmp(sellerInput, sellerArr[i].userName) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
    { // we have that account
        strcpy(sellerArr[i].status, "inactive");
        writeSellerEditedData(sellerArr[i]);
        char sellerProductsPath[50];
        createUserProductsPath(sellerArr[i].userName, sellerProductsPath);
        FILE *fptr = fopen(sellerProductsPath, "r");
        char temp[100] = {'\0'};
        while (fgets(temp, 100, fptr) != NULL)
        {
            printf("we ar ein while\n");
            char inputId[50];
            extractUserAnything(temp, inputId, 0);
            RemoveProductAdminEdition(sellerArr[i].userName, inputId);
        }
        fclose(fptr);
        fptr = fopen(sellerProductsPath, "w");
        fclose(fptr);
    }

    if (flag == 0)
    {
        printf("-----We dont have that UserName\n");
    }
}
void productSpecifications(struct product newProduct){
printf("-----These are the details of %s\n",newProduct.productName);
printf("-----Product Name:%s\n-----Average Price:%f\n-----amount:%d\n",newProduct.productName,fillProductPrice(newProduct),fillProductAmount(newProduct));
printf("-----Category:%d (1-Food-2-Clothes-3-cosmetic-4-Digital Products)\n",newProduct.category);
printf("-----Content:%s\n",newProduct.content);
}
void productSellersShow(struct product newProduct){
printf("-----These are the Sellers of %s:\n",newProduct.productName);
char sellerPath[50];
    createProductSellerPath(newProduct.productName, sellerPath);
    FILE *fptr = fopen(sellerPath, "r");
    char temp[100];
     while (fgets(temp, 100, fptr) != NULL)
    {
        char show[50];
        if (strlen(temp) > 5)
        {
         extractUserAnything(temp,show,1);
        printf("-----%s\n",show);
        }
    }
    fclose(fptr);
}
void addWalletToSeller(char userName[],float profit){

  char filePath[100] = {'\0'};
        char userData[200] = {'\0'};
        createUserDataPath(userName, filePath);
        readUserData(filePath, userData);
      
            struct seller sellerTemp;
            fillSellerData(&sellerTemp, userData);        
            float new=0.9*profit;
            sellerTemp.wallet+=new;
            writeSellerEditedData(sellerTemp);
}

void purchase(struct product newProduct,char userName[]){

        char filePath[100] = {'\0'};
        char userData[200] = {'\0'};
        createUserDataPath(userName, filePath);
        readUserData(filePath, userData);
         struct buyer buyerTemp;
         fillBuyerData(&buyerTemp, userData);
        printf("-----How many do you want?\n");
        char input[50];
        fgets(input,50,stdin);
        input[strlen(input)-1]='\0';
        int buyerAmount=atoi(input);  
        if(buyerAmount>fillProductAmount(newProduct)){
            printf("----Sorry We dont have that much of that product \n");
            return ;
        }

       struct sellerP listOfSellers[50];
       int sellersCount=fillListOfSeller(listOfSellers,newProduct);
       if(sellersCount==0){
        printf("-----there is no seller\n");
        return ;
       }
       else{
        printf("-----Choose the seller by their product Id\n");
        for(int i=0;i<sellersCount;i++){
            printf("-----%s--%f--%d\n",listOfSellers[i].ID,listOfSellers[i].Price,listOfSellers[i].amount);
        }
        char inputSeller[50];
        fgets(inputSeller,50,stdin);
        inputSeller[strlen(inputSeller)-1]='\0';
        validUserInput(inputSeller);
        int andis=-1;
             for(int i=0;i<sellersCount;i++){
            if(strcmp(inputSeller,listOfSellers[i].ID)==0){
                andis=i;
                break;
            }
        }
        if(andis==-1){
            printf("-----We dont have that Seller\n");
            return ;
        }
        if(listOfSellers[andis].amount<buyerAmount){
            printf("-----This seller dont have enough of that product\n");
            return ;
        }
        if(buyerTemp.wallet< (buyerAmount*listOfSellers[andis].Price)){
            printf("-----You dont have enough credit\n");
            return ;
        }
        /////////// final stage purchase
        float costedPrice=listOfSellers[andis].Price*buyerAmount;
        buyerTemp.wallet=buyerTemp.wallet-costedPrice;
        listOfSellers[andis].amount-=buyerAmount;

        writeBuyerEditedData(buyerTemp);
        char buyerProductsPath[50];
        createUserProductsPath(userName,buyerProductsPath);
        FILE *fptr=fopen(buyerProductsPath,"a");
        fprintf(fptr,"%s,%s,%d,%f,\n",listOfSellers[andis].ID,newProduct.productName,buyerAmount,listOfSellers[andis].Price);
        fclose(fptr);
        addWalletToSeller(listOfSellers[andis].Name,costedPrice);
        char ProductSellerPath[50];
        createProductSellerPath(newProduct.productName,ProductSellerPath);
        fptr=fopen(ProductSellerPath,"w");
        for(int i=0;i<sellersCount;i++){
            fprintf(fptr,"%s,%s,%d,%f\n",listOfSellers[i].ID,listOfSellers[i].Name,listOfSellers[i].amount,listOfSellers[i].Price);
        }
        fclose(fptr);
       }
}

void commitComment(struct product newProduct){
char text[500];
float Score;
printf("-----Give us your comment text\n");
fgets(text,500,stdin);
text[strlen(text)-1]='\0';
validUserInputCommentEdition(text);
printf("-----score the product in scale of 0 to 5\n");
char inputFloat[50];
fgets(inputFloat,50,stdin);
inputFloat[strlen(inputFloat)-1]='\0';
Score=atof(inputFloat);

char commentPath[50];
createProductCommentPath(newProduct.productName,commentPath);
FILE *fptr=fopen(commentPath,"a");
fprintf(fptr,"%s,%f,\n",text,Score);
fclose(fptr);

}
void commentProduct(struct product newProduct,char userName[]){
char productPath[50];
       int flag=-1;
       createUserProductsPath(userName,productPath);
       FILE *fptr=fopen(productPath,"r");
       char temp[100];
       while(fgets(temp,100,fptr)!=NULL){
        char productName[50];
        extractUserAnything(temp,productName,1);
        if(strcmp(productName,newProduct.productName)==0){
            flag=0;
        }
       }
       if(flag==-1){
        printf("-----first buy this product\n");
        return ;
       }
       else{
        commitComment(newProduct);
       }

}

void seeProductsByCategory(struct product productArr[],int productCount){
printf("-----In which category do you want to see the product?\n");
int path=getPathSellerMenu();
for(int i=0;i<productCount;i++){
    if(productArr[i].category==path){
        printf("----ProductName:%s--average price:%.3f--amount:%d--score:%.3f\n",productArr[i].productName,fillProductPrice(productArr[i]),fillProductAmount(productArr[i]),fillProductScore(productArr[i]));
    }
}

}

void productShowCase(struct product newProduct,char userName[]){
productShowCaseMenu(newProduct.productName);
int path=getPathBuyerMenu();
while(1){
    if(path==5){
        return;
    }
switch(path){
case 1:
productSpecifications(newProduct);
break;
case 2 :
productSellersShow(newProduct);
break;
case 3:
purchase(newProduct, userName);
break;
case 4:
commentProduct(newProduct,userName);
break;
}
productShowCaseMenu(newProduct.productName);
path=getPathBuyerMenu();
}

}
void buyerSeeAllProducts(struct product productArr[], int productCount,char userName[]){
viewTheListOfGoodsSellerEdition(productArr,productCount);
printf("-----Do you want to see any specific product?(yes select 1 no select 2)\n");
int path=getPath();
if(path==2){
    return;
}
else{ // path 1
    char userinputProduct[50];
    printf("-----Give us the productName:\n");
    fgets(userinputProduct,50,stdin);
    userinputProduct[strlen(userinputProduct)-1]='\0';
    validUserName(userinputProduct);
    int flag=-1;
    int i;
    for(i=0;i<productCount;i++){
   if(strcmp(userinputProduct,productArr[i].productName)==0){
    flag=1;
    break;
   }
    }
    if(flag==-1){
        printf("-----We dont have that userName\n");
        return ;
    }
    else{ // we have that accoutn
        productShowCase(productArr[i],userName);
        return;
    }
}

}
void searchProduct(struct product productArr[],int productCount,char userName[]){
char input[50];
printf("-----give us your userName for showing product specifications\n");
fgets(input,50,stdin);
input[strlen(input)-1]='\0';
validUserName(input);
int flag=-1;
int i;
for( i=0;i<productCount;i++){
    if(strcmp(productArr[i].productName,input)==0){
        flag=1;
        break;
    }
}

if(flag==-1){
    printf("-----We dont have that user name\n");
    return ;
}
else{
productShowCase(productArr[i],userName);
}
}

void seeWalletBuyer(char userName[]){
        char filePath[100] = {'\0'};
        char userData[200] = {'\0'};
        createUserDataPath(userName, filePath);
        readUserData(filePath, userData);
         struct buyer buyerTemp;
         fillBuyerData(&buyerTemp, userData);
         printf("-----You have %.3f credit in your account\n",buyerTemp.wallet);
         printf("-----Do you want to increase your wallet(select 1)or return to menu(select 2)\n");
         int path=getPath();
         if(path==2){
            return ;
         }
         else{
         printf("-----How Much Do you want to increase (max 1000)\n");
         char input[50];
         fgets(input,50,stdin);
         float increase=atof(input);
         while(increase>1000){
         printf("-----Out of range try again:\n");
         fgets(input,50,stdin);
         float increase=atof(input);
         }
         buyerTemp.wallet+=increase;
         writeBuyerEditedData(buyerTemp);
         }

}
void adminMenuText()
{
    printf("**************************************\n");
    printf("-----Welcome Admin-----\n");
    printf("-----1-View the list of goods-----\n");
    printf("-----2-View the list of sellers-----\n");
    printf("-----3-View the list of buyers-----\n");
    printf("-----4-View a user's information-----\n");
    printf("-----5-Remove sellers-----\n"); // product
    printf("-----6-Remove Product-----\n"); // product
    printf("-----7-check users wallet-----\n");
    printf("-----8-Return to menu-----\n");
    printf("**************************************\n");
}
void sellerMenuText(char userName[])
{
    printf("**************************************\n");
    printf("-----Welcome %s-----\n", userName);
    printf("-----1-Add Product-----\n");
    printf("-----2-Remove Product-----\n");
    printf("-----3-View Wallet-----\n");
    printf("-----4-Return to menu-----\n");
}
void buyerMenuText(char userName[])
{
    printf("**************************************\n");
    printf("-----Welcome %s-----\n", userName);
    printf("-----1-View the list of goods-----\n");
    printf("-----2-Display the list of products of a specific category-----\n");
    printf("-----3-View Wallet-----\n");
    printf("-----4-Product specifications-----\n");
    printf("-----5-return to Menu-----\n");
}
void productShowCaseMenu(char userName[]){
  printf("**************************************\n");
  printf("-----in the showcase of %s-----\n", userName);
  printf("-----1-Product Specifications\n");
   printf("-----2-Sellers of those goods-----\n");
    printf("-----3-Purchase of goods-----\n");
     printf("-----4-Commenting-----\n");
     printf("-----5-return-----\n");

}
void admin()
{
    struct user allproductsName[50];
    struct buyer buyerArr[100];
    struct seller sellerArr[100];
    struct product productArr[50];
    struct user allUsersName[100];
    int buyerCount = 0;
    int sellerCount = 0;
    int allUserCount = 0;
    int productCount = 0;
    productCount = extractAllProduct(productArr, allproductsName);
    allUserCount = extractAllUsersData(buyerArr, sellerArr, &buyerCount, &sellerCount, allUsersName);
    adminMenuText();
    int path = getPathAdminMenu();
    while (1)
    {
        if (path == 8)
        {
            menu();
            break;
        }
        switch (path)
        {
        case 1:
            viewTheListOfGoods(productArr, productCount);
            break;
        case 2:
            viewAllSellers(sellerArr, sellerCount);
            break;
        case 3:
            viewAllBuyers(buyerArr, buyerCount);
            break;
        case 4:
            viewSpecifiedUserInfo(allUsersName, allUserCount);
            break;
        case 5:
            RemoveSeller(sellerArr, sellerCount);
            break;
        case 6:

            break;
        case 7:
            CheckWallet(allUsersName, allUserCount);
            break;
        }
        adminMenuText();
        path = getPathAdminMenu();
    }
}

void seller(char userName[])
{

    struct product productArr[50];
    sellerMenuText(userName);
    int path = getPathSellerMenu();
    while (1)
    {
        if (path == 4)
        {
            menu();
            break;
        }
        switch (path)
        {
        case 1:
            createProduct(userName);
            break;
        case 2:
            RemoveProduct(userName);
            break;
        case 3:
            seeWalletSeller(userName);
            break;
        }
        sellerMenuText(userName);
        path = getPathSellerMenu();
    }
}



void buyer(char userName[])
{
    struct product productArr[50];
    struct user allproductsName[50];
    buyerMenuText(userName);
    int productCount = extractAllProduct(productArr, allproductsName);

    int path = getPathBuyerMenu();
    while (1)
    {
        if (path == 5)
        {
            menu();
            return;
        }
        switch (path)
        {
        case 1:
            buyerSeeAllProducts(productArr,productCount,userName);
            break;
        case 2:
            seeProductsByCategory(productArr,productCount);
            break;
        case 3:
           seeWalletBuyer(userName);
            break;
        case 4:
           searchProduct(productArr,productCount,userName);
            break;
        }
          buyerMenuText(userName);
          path = getPathBuyerMenu();
    }
}

/*
int main(){

    // admin();
    return 0;
}
*/