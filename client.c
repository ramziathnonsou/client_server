#include <sys/select.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>    
#include <sys/stat.h>  
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>


int init(char* name);

int main(int argc, char *argv[]){

   int ret, size_inbytes = 0, sd;
   fd_set readset, writeset;
   char* filename = argv[1];
   sd = init(filename);
   close(sd);
   return 0;
}

int init(char* name){
   struct sockaddr_in serv_adresse;
   int sd;
   if((sd = socket(AF_INET, SOCK_STREAM, 0))< 0){
        printf("\n Erreur  de socket \n");
        return sd;
   }

   serv_adresse.sin_family = AF_INET;
   serv_adresse.sin_port = htons(5555);
   serv_adresse.sin_addr.s_addr = inet_addr("127.0.0.1");

    
   if(connect(sd, (struct sockaddr *)&serv_adresse, sizeof(serv_adresse))<0){
        printf("\n Error: Connect Failed (%d) \n", errno);
        return -1;
   }
   int fchier = open(name, O_CREAT | O_WRONLY, 0644);
   
   int lu= 6291456;
   while(lu > 0) {
	char buffer[6291456];
	lu = read(sd, buffer, 6291456);
	write(fchier, buffer, lu);
   }
   close(fchier);
   //for(;;){}
   printf("end %d\n", sd);
   return sd;
}
