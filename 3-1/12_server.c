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
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	int status;
	char ipstr[INET_ADDRSTRLEN];
	int sock_mine;
	int sock_curr;
	int yes = 1;
	
	if(argc != 3){
		fprintf(stderr, "SYNOPSIS: server ip port\n");
		return EXIT_FAILURE;
	}
	
	const char* ip_dest = argv[1];
	const char* port_dest = argv[2];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if((status = getaddrinfo(ip_dest, port_dest, &hints, &res)) != 0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return EXIT_FAILURE;
	}

	printf("IP address for %s:\n\n", ip_dest);

	for(servinfo = res; servinfo != NULL; servinfo = servinfo->ai_next){
		void* addr;
		char* ipversion;

		struct sockaddr_in *ipv4 = (struct sockaddr_in*)servinfo->ai_addr;
		addr = &(ipv4->sin_addr);
		ipversion = "IPv4";

		inet_ntop(servinfo->ai_family, addr, ipstr, sizeof(ipstr));
		printf("\t%s: %s\n\n", ipversion, ipstr);

		if((sock_mine = socket(
							servinfo->ai_family, 
							servinfo->ai_socktype, 
							servinfo->ai_protocol
						)) == -1){
			perror("server: socket");
			continue;
		}
		
		if(setsockopt(sock_mine, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1){
			perror("setsockopt");
			exit(EXIT_FAILURE);
		}
		
		if(bind(sock_mine, servinfo->ai_addr, servinfo->ai_addrlen) == -1){
			close(sock_mine);
			perror("server: bind");
			continue;
		}
				
		char hostname[128];
		gethostname(hostname, sizeof(hostname));
		printf("Server's Hostname is: %s\n", hostname);
		
		break;
	}
	
	freeaddrinfo(res);
	
	if (servinfo == NULL){
		fprintf(stderr, "server: failed to bind\n");
		exit(EXIT_FAILURE);
	}
	
	if(listen(sock_mine, BACKLOG) == -1){
		perror("server: listen");
		exit(EXIT_FAILURE);
	}
	
	printf("server: waiting for connections...\n");
	
	while(TRUE){
		addr_size = sizeof their_addr;
		if((sock_curr = accept(
							sock_mine, 
							(struct sockaddr*)&their_addr, 
							&addr_size
						)) == -1){
			perror("server: accept");
			continue;
		}
		
		//getpeername(sock_mine, (struct sockaddr*)&their_addr, &addr_size);
		inet_ntop(
			their_addr.ss_family,
			&their_addr, 
			ipstr, 
			sizeof(ipstr)
		);
		printf("server: connection from %s\n", ipstr);
		
		if(!fork()){
			//Children only zone
			close(sock_mine);
			char* msg = "This is a test.\nThis is only a test.";
			int msg_len = strlen(msg);
			//int msg = 1;
			//printf("host: %x\n", msg);
			//printf("htole32: %d\n", htole32(msg));
			//printf("htobe32: %d\n", htobe32(msg));
			//printf("h_msg: %d\n", msg);
			//msg = htobe32((uint32_t)msg);
			//printf("be_msg: %d\n", msg);
			int bytes_sent = send(sock_curr, msg, msg_len, 0);
			if(bytes_sent == -1)
				perror("send");
			else
				printf("%d bytes of %d were sent.", bytes_sent, msg_len);
			
			exit(EXIT_SUCCESS); //Return to your parents
		}
		close(sock_curr);
	}	

	close(sock_mine);

	freeaddrinfo(res);


	return EXIT_SUCCESS;
} 