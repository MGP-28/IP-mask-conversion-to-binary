#include <stdio.h>
#include <math.h>

void decimal_to_binary_print(int num, int *ruler){
  int res=0;
  for(int i=0;i<8;i++){
    res=res*10;
    if(i!=7){
      if(num>=ruler[i]){
        res+=1;
        num=num-ruler[i];
      }
    }
    else{
      if(num==1)
        res+=1;
    }
  }
  if(res<10000000){
    int copy=res;
    do{
      printf("0");
      copy=copy*10;
    }while(copy<10000000);
  }
  printf("%d",res);
}

void subnet_size_to_binary_print(int subnet_size, int *ruler){
  int cont=0;
    while(subnet_size-8>0){
      subnet_size=subnet_size-8;
      cont++;
    }
    printf("Subnet mask: ");
    for(int i=0; i<cont; i++){
      printf("11111111.");
    }
  //calculate subnet number where network ends and host IPs begin
      int sum=0, power=7;
      for(int i=0; i<subnet_size; i++){
        sum+=pow(2,power);
        power--;
      }
      decimal_to_binary_print(sum, ruler);
    //fills the zeros after, if needed, to complete a 4 number IP
      for(int i=cont; i<3; i++){
        printf(".00000000");
      }
}

void build_ruler(int *ruler){
  int exp=0;
  for(int i=7;i>=0;i--){ //128-64-32-16-8-4-2-1
    ruler[i]=pow(2,exp);
    exp++;
  }
}

void separate_IP_octets_plus_mask(char *hold, int *ip1, int *ip2, int *ip3, int *ip4, int *subnet_size){

  int counter=0;

  while(hold[counter]!='.' && hold[counter]!=-1){
    *ip1=*ip1*10;
    *ip1+=hold[counter]-48;
    printf("\n[%d]",*ip1);
    counter++;
  }
  printf("\n");
  counter++;

  while(hold[counter]!='.' && hold[counter]!=-1){
    *ip2=*ip2*10;
    *ip2+=hold[counter]-48;
    printf("\n[%d]",*ip2);
    counter++;
  }
  printf("\n");
  counter++;

  while(hold[counter]!='.' && hold[counter]!=-1){
    *ip3=*ip3*10;
    *ip3+=hold[counter]-48;
    printf("\n[%d]",*ip3);
    counter++;
  }
  printf("\n");
  counter++;

  while(hold[counter]!='/' && hold[counter]!=-1){
    *ip4=*ip4*10;
    *ip4+=hold[counter]-48;
    printf("\n[%d]",*ip4);
    counter++;
  }
  printf("\n\n/");
  counter++;

  while(hold[counter]!='\n'){
    *subnet_size=*subnet_size*10;
    *subnet_size+=hold[counter]-48;
    printf("\n[%d]",*subnet_size);
    counter++;
  }
}

int main(void) {
  //Create ruler for powers of 2 up until 255
  int ruler[8];
  build_ruler(ruler);

  //Read number
  int ip1, ip2, ip3, ip4, subnet_size, check;
  
  do{
    ip1=0, ip2=0, ip3=0, ip4=0, subnet_size=0, check=0;
    printf("\nWrite an IP and mask number in the format 0.0.0.0/0: \n\n>>> ");

    char hold[100];
    fgets(hold, 100, stdin);

    int counter1=0, counter=0;

    for(int i=0;hold[i]!='\n';i++){
      if(hold[i]=='.')
        counter++;
      else if(hold[i]=='/')
        counter1++;
    }

    if(counter==3 && counter1==1){

    separate_IP_octets_plus_mask(hold, &ip1, &ip2, &ip3, &ip4, &subnet_size);

      if(ip1<0 || ip2<0 || ip3<0 || ip4<0 || subnet_size<=0 || ip1>255 || ip2>255 || ip3>255 || ip4>255 || subnet_size>30){
        printf("\n----- Invalid! -----\n");
        check=1;
      }
    }
    else{
      printf("\n----- Invalid! -----\n");
      check=1;
    }
  }while(check==1);

  printf("\n\n<< Binary >>\n-------- IP: ");

  decimal_to_binary_print(ip1, ruler);
  printf(".");
  decimal_to_binary_print(ip2, ruler);
  printf(".");
  decimal_to_binary_print(ip3, ruler);
  printf(".");
  decimal_to_binary_print(ip4, ruler);
  printf("\n");
  subnet_size_to_binary_print(subnet_size, ruler);

  return 0;
}