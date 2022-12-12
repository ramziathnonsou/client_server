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
#include <string.h>


int start();

int main(int argc, char *argv[]){

   int ret, size_inbytes = 0, sd, csd;
   fd_set readset, writeset;
   const char* filename = argv[1];
   struct sockaddr client_addr;
   int clen;
   sd = start();
   //int client = 1;
   while (1){
	if((csd = accept(sd, &client_addr, &clen)) < 0){
		fprintf(stderr, "erreur %d\n", errno);
		return -1;
	}
	pid_t pid = fork();
	if(pid < 0) {
		fprintf(stderr, "erreur: %d\n", errno);
		return -1;
	}
	if(pid == 0) {
		fprintf(stdout, "\nConnexionréussie\n");
		int fichier = open(filename, O_RDONLY);
		write(csd, filename, strlen(filename));
		char chaine[6291456];
		int lu = 6291456;
		while(lu > 0) {
			lu = read(fichier, chaine, 6291456);
			write(csd, chaine, lu);
		}
		close(fichier);
		for(;;){}
	}
	//client++;
    }
    fprintf(stderr , "buffer du clavier %d", size_inbytes);
}

int start(){
   int sd, ret;
   struct sockaddr_in serv_addr;
   sd = socket(AF_INET, SOCK_STREAM, 0);
   if(sd<0){
      printf("Error in socket creation\n");
      return sd;
   }
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   serv_addr.sin_port = htons(5555);

   ret=bind(sd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
   if(ret<0){
      printf("Error dans le bind\n");
      close(sd);
      return ret;
    }

    if(listen(sd, 10) == -1)
    {
        printf("erreur de lecture\n");
        return -1;
    }
    
    return sd;

}