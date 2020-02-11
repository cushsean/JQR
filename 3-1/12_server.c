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

int main(int argc, char* argv[]){

	struct addrinfo hints;
	struct addrinfo *res_tmp;
	struct addrinfo *res;
	struct sockaddr_storage their_addr;
	struct sockaddr_storage another_addr;
	socklen_t addr_size;
	int status;
	char ipstr[INET_ADDRSTRLEN];
	int sock_mine;
	int sock_curr;

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
		bind(sock_mine, res->ai_addr, res->ai_addrlen);
		listen(sock_mine, BACKLOG);
		addr_size = sizeof their_addr;
		sock_curr = accept(sock_mine, (struct sockaddr*)&their_addr, &addr_size);
		
		char* msg = "This is a test.\nThis is only a test.";
		int msg_len = strlen(msg);
		int bytes_sent = send(sock_curr, msg, msg_len, 0);
		if(bytes_sent < msg_len)
			printf("NOTE: Only %d bytes of %d were sent.", bytes_sent, msg_len);
		getpeername(sock_mine, (struct sockaddr*)&their_addr, &addr_size);
		inet_ntop(res->ai_family, &their_addr, ipstr, sizeof(ipstr));
		printf("Client's Hostname is: %s\n", ipstr);
		
		char hostname[128];
		gethostname(hostname, sizeof(hostname));
		printf("Server's Hostname is: %s\n", hostname);
		
		printf("Prep Datagram\n");
		sleep(2);
		char buf[256];
		int buf_len = sizeof(buf);
		memset(buf, '\0', buf_len);
		addr_size = sizeof another_addr;
		int bytes_recv = recvfrom(
						sock_mine, 
						buf, 
						buf_len-1, 
						0, 
						(struct sockaddr*)&another_addr, 
						&addr_size
					);
		printf("CLIENT: %d bytes recv\n", bytes_recv);
		printf("%.*s\n", bytes_recv, buf);
		
		close(sock_mine);
	}

	freeaddrinfo(res_tmp);


	return EXIT_SUCCESS;
} 