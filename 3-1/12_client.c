/*******************************************\
|	Modified Beej's code to fit my needs.	|
\*******************************************/

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

int main(int argc, char* argv[]){

	struct addrinfo hints;
	struct addrinfo *servinfo;
	struct addrinfo *res;
	int status;
	char ipstr[INET_ADDRSTRLEN];
	int sock_mine;

	if(argc != 3){
		fprintf(stderr, "SYNOPSIS: client ip port\n");
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
			perror("client: socket");
			continue;
		}
		
		if(connect(sock_mine, servinfo->ai_addr, servinfo->ai_addrlen) == -1){
			perror("client: connect");
			continue;
		}
		
		break;
	}
	
	freeaddrinfo(res);
	
	if(servinfo == NULL){
		fprintf(stderr, "client: failed to connect\n");
		return EXIT_FAILURE;
	}
	
	inet_ntop(
		servinfo->ai_family,
		(struct sockaddr*)servinfo->ai_addr,
		ipstr,
		sizeof ipstr
	);
	freeaddrinfo(servinfo);
	
	socklen_t i;
	int type;
	
	if(getsockopt(sock_mine, SOL_SOCKET, SO_TYPE, &type, &i) == -1)
		perror("getsockopt");
	printf("client: the sock is of type %s\n", 
		type ? "DATAGRAM" : "STREAM");
	printf("client: connecting to %s\n", ipstr);
	
	//char buf[128];
	//int buf_len = sizeof(buf);
	//memset(buf, '\0', buf_len);
	/*
	*	NOTE:
	*	Instead of above, could also set the byte after the 
	*	received message to '\0'. This byte would be:
	*	buf[bytes_recv]
	*/
	int buf;
	int buf_len = sizeof(int);
	int bytes_recv = recv(sock_mine, &buf, buf_len, 0);
	if(bytes_recv == -1)
		perror("recv");
	else{
		printf("client: %d bytes recv\n", bytes_recv);
		printf("be_buf: %d\n", buf);
		buf = be32toh(buf);
		printf("h_buf: %d\n", buf);
	}

	close(sock_mine);

	return EXIT_SUCCESS;
} 