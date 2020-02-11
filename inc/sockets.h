#ifndef SOCKETS_H_CUSHMAN
#define SOCKETS_H_CUSHMAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <endian.h>
#include <netdb.h>

struct addrinfo{
	int 			ai_flags;		//AI_PASSIVE, AI_CONONNAME, etc.
	int 			ai_family;		//AF_INET, AF_INET6, AF_UNSPEC
	int 			ai_socktype;	//SOCK_STREAM, SOCK_DGRAM
	int 			ai_protocol;	//use 0 for "any"
	size_t 			ai_addrlen;		//size of ai_addr in bytes
	struct sockaddr *ai_adder;		//struct sockadder_in or _in6
	char 			*ai_cononname;	//full cononical hostname

	struct addrinfo *ai_next;		//linked list, next node
};

struct sockaddr{
	unsigned short 	sa_family;		//address family, AF_xxx
	char 			sa_data[14];	//14 bytes of protocol address
};

struct sockaddr_in{
	short int 			sin_family; 	//Address family, AF_INET
	unsigned short int 	sin_port;		//Por number
	struct in_addr 		sin_addr;		//Internet address
	unsigned char 		sin_zero[8];	//Same size as struct sockaddr
};

struct in_addr{
	uint32_t s_addr; //A 32-bit int (4 bytes)
};

struct sockaddr_in6{
	u_int16_t		sin6_family;	//address family, AF_INET6
	u_int16_t		sin6_port;		//port number, Network Byte Order
	u_int32_t		sin6_flowinfo;	//IPv6 flow information
	struct in6_addr	sin6_addr;		//IPv6 address
	u_int32_t		sin6_scope_id;	//Scope ID
};

struct in6_addr{
	unsinged char	s6_addr[16];	//IPv6 address
};

struct sockaddr_storage{
	sa_family_t	ss_family;	//address family

	//padding
	char		__ss_pad1[_ss_PAD1SIZE];
	int64_t		__ss_align;
	char		__ss_pad2[_ss_PAD2SIZE];
};

#endif /* SOCKETS_H_CUSHMAN */