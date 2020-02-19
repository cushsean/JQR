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

#include "encode.h"

typedef struct cereal{
	char		ch;
	int16_t		s_16;
	uint16_t	u_16;
	int32_t		s_32;
	uint32_t	u_32;
	int64_t		s_64;
	uint64_t	u_64;
	float		fl;
	double		db;
	char		str[128];
}cereal_t;

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
	//const char* msg = argv[3];

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

	printf("\nclient: connecting to %s\n", ipstr);
	
	/*int bytes_sent = send(sock_mine, msg, sizeof(msg), 0);
	if(bytes_sent == -1)
		perror("auth");
	else
		printf("Authentication sent\n");
	*/
	char buf[1024];
	int buf_len = sizeof(buf);
	memset(buf, '\0', buf_len);
	/*
	*	NOTE:
	*	Instead of above, could also set the byte after the 
	*	received message to '\0'. This byte would be:
	*	buf[bytes_recv]
	*/
	int bytes_recv = recv(sock_mine, buf, buf_len-1, 0);
	if(bytes_recv == -1)
		perror("recv");
	else{
		printf("client: %d bytes recv\n", bytes_recv);
	}
	//char* err_msg = "INVALID ENTRY";
	//printf("%s\n%s\n%ld\n", buf, err_msg, strlen(err_msg));
	//if(strncmp(buf, err_msg, 13)){
		cereal_t packet;
		
		unpack(buf, "chHlLqQ16s",
				&packet.ch,
				&packet.s_16,
				&packet.u_16,
				&packet.s_32,
				&packet.u_32,
				&packet.s_64,
				&packet.u_64,
				//&packet.fl,
				//&packet.db,
				packet.str
			);
		
		printf("Received:\n\n");
		printf("ch=%c\n", packet.ch);
		printf("s_16=%d\n", packet.s_16);
		printf("u_16=%d\n", packet.u_16);
		printf("s_32=%d\n", packet.s_32);
		printf("u_32=%d\n", packet.u_32);
		printf("s_64=%ld\n", packet.s_64);
		printf("u_64=%ld\n", packet.u_64);
		//printf("fl=%.7f\n", packet.fl);
		//printf("db=%.20lf\n", packet.db);
		printf("str=%s\n", packet.str);
	//}
	close(sock_mine);

	return EXIT_SUCCESS;
} 