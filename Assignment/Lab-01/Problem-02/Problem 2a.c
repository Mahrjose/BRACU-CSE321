
#include <stdio.h>

int main(){

  int num1 = 0;
  printf("Enter the first Number: ");
  scanf("%d", &num1);

  int num2 = 0;
  printf("Enter the second Number: ");
  scanf("%d", &num2);

  if (num1 > num2){
    printf("%d\n", num1 - num2);
  }
  else if (num1 < num2){
    printf("%d\n", num1 + num2);
  }
  else{
    printf("%d\n", num1 * num2);
  }

  return 0;
}