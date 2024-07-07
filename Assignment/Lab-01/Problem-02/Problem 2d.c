#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void emailChecker(char email[]) {

    bool isDomainStr = false;
    const char oldDomain[10] = "kaaj.com";
    const char newDomain[10] = "sheba.xyz";
    char domainStr[10] = "";

    int size = strlen(email);
    for(int i = 0; i < size; i++) {

        if(isDomainStr){
            if(email[i] == '\n') { //reached at the end
                break; 
            }

            strncat(domainStr, &email[i], 1);
        }
        else if(email[i] == '@'){
            isDomainStr = true;
            continue;
        }
    }

    if(strcmp(oldDomain, domainStr) == 0){
        printf("Email address is outdated\n");
    }
    else if(strcmp(newDomain, domainStr) == 0){
        printf("Email address is okay\n");
    } else {
        printf("Invalid Email address\n");
    }
}

int main(){

    char email[25];
    printf("Please Enter Email: ");
    // scanf("%24s", email);
    fgets(email, sizeof(email), stdin);

    emailChecker(email);
    return 0;
}