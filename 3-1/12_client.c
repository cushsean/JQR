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
	struct addrinfo *res_tmp;
	struct addrinfo *res;
	int status;
	char ipstr[INET_ADDRSTRLEN];
	int sock_mine;

	if(argc != 3){
		fprintf(stderr, "usage: showip hostname\n");
		return 1;
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if((status = getaddrinfo(argv[1], argv[2], &hints, &res_tmp)) != 0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
	}

	printf("IP address for %s:\n\n", argv[1]);

	for(res = res_tmp; res != NULL; res = res->ai_next){
		void* addr;
		char* ipversion;

		struct sockaddr_in *ipv4 = (struct sockaddr_in*)res->ai_addr;
		addr = &(ipv4->sin_addr);
		ipversion = "IPv4";

		inet_ntop(res->ai_family, addr, ipstr, sizeof(ipstr));
		printf("\t%s: %s\n\n", ipversion, ipstr);

		sock_mine = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		connect(sock_mine, res->ai_addr, res->ai_addrlen);
		
		char buf[128];
		int buf_len = sizeof(buf);
		memset(buf, '\0', buf_len);
		int bytes_recv = recv(sock_mine, buf, buf_len, 0);
		printf("SERVER: %d bytes recv\n", bytes_recv);
		printf("%.*s\n", bytes_recv, buf);
		
		//sleep(2);
		
		char* msg =
			"I have a UDP joke,\n\
you might get it and you might not,\n\
I don't really care.";
		int msg_len = strlen(msg);
		int bytes_sent = sendto(
							sock_mine, 
							buf, 
							buf_len, 
							0, 
							res->ai_addr, 
							res->ai_addrlen
						);
		if(bytes_sent < msg_len)
			printf("NOTE: Only %d bytes of %d were sent.", bytes_sent, msg_len);
		
		close(sock_mine);
	}

	freeaddrinfo(res_tmp);


	return EXIT_SUCCESS;
} 