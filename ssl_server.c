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


int openListener(const char *host, int port){

	int sd;
	struct sockaddr_in addr;

	sd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0){
		perror("server: bind");
		abort();
	}

	if(listen(sd, 10) != 0){
		perror("server: listen");
		abort();
	}

	return sd;
}

SSL_CTX* initServerCTX(void){
	SSL_METHOD *method;
	SSL_CTX *ctx;

	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	method = TLSv1_2_server_method();
	ctx = SSL_CTX_new(method);
	if(ctx == NULL){
		ERR_print_errors_fp(stderr);
		abort();
	}
	
	return(ctx);
}

void loadCerts(SSL_CTX *ctx, char *certFile, char *keyFile){
	// Set local certs
	if(SSL_CTX_use_certificate_file(ctx, certFile, SSL_FILETYPE_PEM) <= 0){
		ERR_print_errors_fp(stderr);
		abort();
	}

	// Set private key
	if(SSL_CTX_use_PrivateKey_file(ctx, keyFile, SSL_FILETYPE_PEM) <= 0){
		ERR_print_errors_fp(stderr);
		abort();
	}

	// Verify private key
	if(!SSL_CTX_check_private_key(ctx)){
		fprintf(stderr, "Private key does not match public cert\n");
		abort();
	}
	
	return;
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

void servlet(SSL *ssl){
	char buf[SIZEOF_BUF] = {0};
	int sd;
	int bytes;

	const char *serverResponse = 
		"This is a TEST!!!!\n";

	const char *cpValidMessage = 
		"sean:Password";
	
	if(SSL_accept(ssl) == -1)
		ERR_print_errors_fp(stderr);
	else{
		showCerts(ssl);
		bytes = SSL_read(ssl, buf, SIZEOF_BUF);
		buf[bytes] = 0;

		printf("Client msg: \"%s\"\n", buf);
		
		if(bytes > 0){
			if(strcmp(cpValidMessage, buf) == 0)
				SSL_write(ssl, serverResponse, strlen(serverResponse));
			else
				SSL_write(ssl, "Invalid Message\n", strlen("Invalid Message"));
		}
		else
			ERR_print_errors_fp(stderr);
	}
	sd = SSL_get_fd(ssl);
	SSL_free(ssl);
	close(sd);
}

int main(int argc, char* argv[]){

	int server;
	char *host;
	char *port;
	SSL_CTX *ctx;

	if(argc != 3){
		fprintf(stderr, "SYNOPSIS: server ip port\n");
		return EXIT_FAILURE;
	}

	SSL_library_init();

	host = argv[1];
	port = argv[2];

	ctx = initServerCTX();
	loadCerts(ctx, "mycert.pem", "mycert.pem");

	server = openListener(host, atoi(port));

	while(1==1){
		int client;
		struct sockaddr_in addr;
		socklen_t len = sizeof(addr);
		SSL *ssl;

		if((client = accept(server, (struct sockaddr*)&addr, &len)) == -1){
			perror("server: accept");
			continue;
		}

		printf("Connection: %s:%d\n", inet_ntoa(addr.sin_addr), 
			ntohs(addr.sin_port));

		ssl = SSL_new(ctx);
		SSL_set_fd(ssl, client);
		servlet(ssl);

		// if(!fork()){
		// 	// Children Only Zone
		// 	close(server);
		// 	char *buf = "THIS IS A TEST.\n";
		// 	int buf_len = strlen(buf);
		// 	int bytes = send(client, buf, buf_len, 0);
		// 	if(bytes == -1)
		// 		perror("server: send");
		// 	else
		// 		printf("%d bytes of %d were sent.\n", bytes, buf_len);

		// 	exit(EXIT_SUCCESS); // Return to parent			
		// }
		 
		// close(client);
	}

	close(server);
	SSL_CTX_free(ctx);

	return 0;
}