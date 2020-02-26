/********************************************
*	Modified Beej's code to fit my needs.	*
*********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <endian.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>

#define BACKLOG (20)
#define FALSE (0)
#define TRUE (!FALSE)

int main(int argc, char* argv[]){
	
	struct addrinfo hints;
	struct addrinfo *servinfo;
	struct addrinfo *res;
	int status;
	char ipstr[INET_ADDRSTRLEN];
	int sock_mine;
	int bytes_sent;
	
	if(argc != 3){
		fprintf(stderr, "SYNOPSIS: talker ip port\n");
		return EXIT_FAILURE;
	}
	
	char* ip_dest = argv[1];
	char* port_dest = argv[2];
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	if((status = getaddrinfo(ip_dest, port_dest, &hints, &res)) != 0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return EXIT_FAILURE;
	}
	
	for(servinfo = res; servinfo != NULL; servinfo = servinfo->ai_next){
		
		if((sock_mine = socket(servinfo->ai_family, servinfo->ai_socktype,
			servinfo->ai_protocol)) == -1){
			close(sock_mine);
			perror("talker: socket");
			continue;
		}
		
		break;
	}
	
	freeaddrinfo(res);
	
	if(servinfo == NULL){
		fprintf(stderr, "talker: failed to create socket\n");
		return EXIT_FAILURE;
	}
	
	char* msg = "I want to tell you a joke. I don't care if you get it \
though and I don't really care.";
	
	//int msg_len = sizeof(msg);
	
	if((bytes_sent = sendto(sock_mine, msg, strlen(msg), 0,
		servinfo->ai_addr, servinfo->ai_addrlen)) == -1){
		perror("talker: sendto");
		return EXIT_FAILURE;
	}
	
	printf("talker: sent %d bytes to %s\n", bytes_sent, ip_dest);
	
	return EXIT_SUCCESS;
}