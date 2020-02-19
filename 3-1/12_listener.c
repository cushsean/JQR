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

#define FALSE (0)
#define TRUE (!FALSE)

int main(int argc, char* argv[]){
	
	struct addrinfo hints;
	struct addrinfo *servinfo;
	struct addrinfo *res;
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	int status;
	char ipstr[INET_ADDRSTRLEN];
	int sock_mine;
	int sock_curr;
	int bytes_recv;
	char buf[128];
	
	if(argc != 3){
		fprintf(stderr, "SYNOPSIS: listener ip port\n");
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
			perror("listener: socket");
			continue;
		}
		
		if(bind(sock_mine, servinfo->ai_addr, servinfo->ai_addrlen) == -1){
			close(sock_mine);
			perror("listener: bind");
			continue;
		}
		
		break;
	}
	
	freeaddrinfo(res);
	
	if(servinfo == NULL){
		fprintf(stderr, "listener: failed to bind");
		return EXIT_FAILURE;
	}
	
	printf("listener: waiting to recvfrom...\n");
	
	addr_size = sizeof their_addr;
	if((bytes_recv = recvfrom(sock_mine, buf, sizeof(buf)-1, 0,
		(struct sockaddr*)&their_addr, &addr_size)) == -1){
		perror("listener: recvfrom");
		return EXIT_FAILURE;
	}
	
	printf("listener: got packet from %s\n",
		inet_ntop(their_addr.ss_family, &their_addr, ipstr, sizeof(ipstr)));
	printf("listener: packet is %d bytes lone\n", bytes_recv);
	buf[bytes_recv] = '\0';
	printf("listener: packet contains \"%s\"\n", buf);
	
	close(sock_mine);
	
	return EXIT_SUCCESS;
}