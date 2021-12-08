#include <stdio.h>
#include <math.h>

void decimal_to_binary_print(int num, int *ruler){
  //num=100               //100   100   36    4     4     4       0       0
  int res=0;              //0     0     1     11    110   1100    11001   110010
  for(int i=0;i<8;i++){
    res=res*10;           //0     0     10    110   1100  11000   110010  1100100
    if(i!=7){
      if(num>=ruler[i]){  //128   64    32    16    8     4       2       *
        res+=1;           //X     1     11    X     X     1       X
        num=num-ruler[i]; //X     36    4     X     X     0       X       *
      }
    }
    else{
      if(num==1)          //                                    1
        res+=1;           //                                    X
    }
  }
  if(res<10000000){       //YES
    int copy=res;
    do{
      printf("0");        //0         <P1>
      copy=copy*10;       //11001000  <- Copy
    }while(copy<10000000);//NO        
  }
  printf("%d",res);       //1100100   <P2>

  //Final print: <P1> + <P2> -> 01100100
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
  //converts each character to integer until it finds the octet end (dot)
  while(hold[counter]!='.'){
    *ip1=*ip1*10;
    *ip1+=hold[counter]-48;
    printf("\n[%d]",*ip1);
    counter++;
  }
  printf("\n");
  counter++;

  while(hold[counter]!='.'){
    *ip2=*ip2*10;
    *ip2+=hold[counter]-48;
    printf("\n[%d]",*ip2);
    counter++;
  }
  printf("\n");
  counter++;

  while(hold[counter]!='.'){
    *ip3=*ip3*10;
    *ip3+=hold[counter]-48;
    printf("\n[%d]",*ip3);
    counter++;
  }
  printf("\n");
  counter++;
  //converts each character to integer until it finds the octet end. Since it's the 4rd octet, it no longer ends with a dot, but with the mask slash
  while(hold[counter]!='/'){
    *ip4=*ip4*10;
    *ip4+=hold[counter]-48;
    printf("\n[%d]",*ip4);
    counter++;
  }
  printf("\n\n/");
  counter++;
  //converts subnet mask portion of IP to integer until it finds the string end
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

//Read IP/Mask

  int ip1, ip2, ip3, ip4, subnet_size, check;
  
  do{
    ip1=0, ip2=0, ip3=0, ip4=0, subnet_size=0, check=0; //resets variables to ensure integrity every loop
    printf("\nWrite an IP and mask number in the format 0.0.0.0/0: \n\n>>> ");

    char hold[100];
    fgets(hold, 100, stdin); //fgets doesn't freeze when incomplete after a '.'

  //verify IP format: if we have 3 '.' and 1 '/' in that order
    int counter1=0, counter=0;
    for(int i=0;hold[i]!='\n';i++){
      if(hold[i]=='.')
        counter++;
      else if(counter==3 && hold[i]=='/')
        counter1++;
    }

  //if IP has the correct format, converts string to integers
    if(counter==3 && counter1==1){

      separate_IP_octets_plus_mask(hold, &ip1, &ip2, &ip3, &ip4, &subnet_size);

    //verifies if octets are NOT between 0->255 and mask is NOT between 1->30. If true, loop around    
      if(ip1<0 || ip2<0 || ip3<0 || ip4<0 || subnet_size<=0 || ip1>255 || ip2>255 || ip3>255 || ip4>255 || subnet_size>30){ 
        printf("\n----- Invalid! -----\n");
        check=1;
      }
    }

  //incorrect format, loops around
    else{
      printf("\n----- Invalid! -----\n");
      check=1;
    }
  }while(check==1); //check var used as boolean to loop around

  printf("\n\n<< Binary >>\n-------- IP: ");

//convert integers to binary and print -> ip1.ip2.ip3.ip4 \n mask1.mask2.mask3.mask4

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