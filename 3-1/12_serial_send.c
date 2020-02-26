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
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "encode.h"

#define BACKLOG (20)
#define FALSE (0)
#define TRUE (!FALSE)

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
	char		bin[128];
}cereal_t;

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
	srand(time(NULL));
	
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
		printf("\nserver: connection from %s\n", ipstr);
		
		unsigned char buf[BUF_SIZE];
		//buf = malloc(128);
		//buf = realloc(buf, 1028);
				
		//Initialize struct and assign values
		cereal_t packet;
		packet.ch = 'a';
		packet.s_16 = rand()%65535-32767;
		packet.u_16 = rand()%65535;
		packet.s_32 = rand()%4294967295-2147483647;
		packet.u_32 = rand()%4294967295;
		packet.s_64 = rand()-9223372036854775807;
		packet.u_64 = rand();
		packet.fl = M_PI;
		packet.db = M_PI;
		strncpy(packet.str, "This is a test.\nThis is only a test.\0", 37);
		uint32_t bin_len = 45;
		memcpy(packet.bin, "\0This is binary data.\0 With a Null Terminator.", bin_len);
		//Serialize
		
		uint32_t packetsize = pack(buf, "chHlLqQfdsb",
				(int8_t)packet.ch,
				packet.s_16,
				packet.u_16,
				packet.s_32,
				packet.u_32,
				packet.s_64,
				packet.u_64,
				packet.fl,
				packet.db,
				packet.str,
				packet.bin,
				bin_len
			);
		if(packetsize == -1){
			perror("pack");
			exit(EXIT_FAILURE);
		}
		printf("packet is %u bytes\n", packetsize);
		buf[packetsize++] = '\0';
		
		//Send it
		int bytes = 0;
		
		//preamble
		char preamble[17];	//preamble 6 BELLs, uint32 packetsize, 6 BELLs, NULL Terminator
		memset(preamble, '\a', 16); //loads preamble with the BELL
		preamble[16] = '\0'; //Adds null at the end
		char msg_len[4];
		packi32(msg_len, packetsize-1); //package packetsize into msg_len
		//packi32 not required if endianess is handeled otherwise
		memcpy(preamble+6, msg_len, 4); //insert packetsize
		if((bytes = send(sock_curr, preamble, 16, 0)) == -1)
			perror("preamble");
		bytes = 0;	//reset bytes
		
		//recv ACK;
		char ack[6];
		if((bytes = recv(sock_curr, ack, 6, 0)) == -1)
			perror("ACK");
		bytes = 0;	//reset bytes
		if(strncmp(ack, "ACK", 3)){
			fprintf(stderr, "ACK not received. Terminating transmission.\n");
			exit(1);
		}
		
		//main packet
		packetsize /= 2; 			//testing partial r/w
		while(bytes < packetsize){
			bytes += send(sock_curr, buf+bytes, packetsize-bytes, 0);
			if(bytes == -1){
				perror("send");
				break;
			}
			fprintf(stderr, "NOTE: %d total bytes were sent out of %d.\n", bytes, packetsize);
			if(bytes == 65) 		//testing partial r/w
				packetsize *= 2;	//testing partial r/w
		}
		bytes = 0;	//reset bytes
		printf("Sent:\n\n");
		printf("ch=%c\n", packet.ch);
		printf("s_16=%d\n", packet.s_16);
		printf("u_16=%d\n", packet.u_16);
		printf("s_32=%d\n", packet.s_32);
		printf("u_32=%d\n", packet.u_32);
		printf("s_64=%ld\n", packet.s_64);
		printf("u_64=%ld\n", packet.u_64);
		printf("fl=%.7f\n", packet.fl);
		printf("db=%.20lf\n", packet.db);
		printf("str=%s\n", packet.str);
		printf("bin=");
		print_bin(packet.bin, 40);
		
		
		close(sock_curr);
	}	

	close(sock_mine);

	freeaddrinfo(res);


	return EXIT_SUCCESS;
} 