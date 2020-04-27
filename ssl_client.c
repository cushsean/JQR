#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define SIZEOF_BUF (1024)

int openConnection(const char *host, int port){
	int sd;
	struct sockaddr_in addr;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&addr, 0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_aton(host, &addr.sin_addr);

	if( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 ){
		close(sd);
		perror("client: connect");
		abort();
	}

	return sd;
}

SSL_CTX* initCTX(void){
	SSL_METHOD *method;
	SSL_CTX *ctx;

	OpenSSL_add_all_algorithms();		// Load cryptos
	SSL_load_error_strings();			// Get error messages
	method = TLSv1_2_client_method();	// Create new client method instance
	ctx = SSL_CTX_new(method);			// Create new context
	if(ctx == NULL){
		ERR_print_errors_fp(stderr);
		abort();
	}
	return ctx;
}

void showCerts(SSL *ssl){
	X509 *cert;
	char *line;

	cert = SSL_get_peer_certificate(ssl);
	if(cert != NULL){
		printf("Server certs:\n");
		line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
		printf("Subject: %s\n", line);
		free(line);
		line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
		printf("Issure: %s\n", line);
		free(line);
		X509_free(cert);
	}
	else{
		fprintf(stderr, "No cert configured.\n");
	}

	return;
}

int main(int argc, char* argv[]){

	SSL_CTX *ctx;
	int server;
	SSL *ssl;
	char buf[SIZEOF_BUF];
	char acClientRequest[1024] = {0};
	int bytes;
	char *host;
	char *port;

	if(argc != 3){
		fprintf(stderr, "SYNOPSIS: <hostname> <port number>\n\n");
		return EXIT_FAILURE;
	}
	
	SSL_library_init();

	host = argv[1];
	port = argv[2];

	ctx = initCTX();

	server = openConnection(host, atoi(port));
	ssl = SSL_new(ctx);	// create new SSL connection
	SSL_set_fd(ssl, server);	// Attach the socket descriptor
	if(SSL_connect(ssl) == -1)
		ERR_print_errors_fp(stderr);
	else{

		printf("client: connecting...\n");

		char UN[16] = {0};
		char PW[16] = {0};

		const char *cpRequestMessage = 
			"%s:%s";

		printf("Enter the User Name : ");
		scanf("%s", UN);
		printf("Enter the Password : ");
		scanf("%s", PW);

		sprintf(acClientRequest , cpRequestMessage, UN, PW);

		printf("\n\nConnected with %s encryption\n\n", SSL_get_cipher(ssl));
		
		showCerts(ssl);
		
		// Send encryped message
		SSL_write(ssl, acClientRequest, strlen(acClientRequest));

		// Recv encrypted message
		memset(buf, 0, SIZEOF_BUF);
		bytes = SSL_read(ssl, buf, sizeof(buf));
		buf[bytes] = 0; // Set null-terminator

		// Print out the message
		printf("Received: %d bytes\n", bytes);
		printf("\"%s\"", buf);
		SSL_free(ssl);
		
		// bytes = recv(server, &buf, SIZEOF_BUF, 0);
		// if(bytes == -1)
		// 	perror("client: recv");
		// else{
		// 	printf("client: %d bytes recv\n", bytes);
		// 	printf("%s\n", buf);
		// }

	}
	close(server);
	SSL_CTX_free(ctx);

	return 0;
}