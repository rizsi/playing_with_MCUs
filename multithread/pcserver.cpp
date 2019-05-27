#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h> /* Added for the nonblocking socket */
#include <errno.h> /* Added for the nonblocking socket */
#include <string.h>
#include "../../sha1/sha1.h"
#include "base64.h"

#define BUFFER_SIZE 1024
#define on_error(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); exit(1); }

#define LINE_MAX 128

typedef struct {
	pthread_t t;
	int client_fd;
	char line[LINE_MAX];
	char calculatedKey[30]; // Includes \n !
	uint8_t linePtr;
} CLIENT;

int16_t readChar(CLIENT * c)
{
	char ret;
	int read = recv(c->client_fd, &ret, 1, 0);
	if (read < 0)
	{
		if(errno!=EAGAIN&&errno!=EWOULDBLOCK)
		{
			on_error("Client read failed\n");
			return -2;
		}
		return -1;
	}else if(read==0)
	{
		return -1;
	}else
	{
//		printf("%c", ret); 
		return (uint8_t)ret;
	}
}
int16_t readFullChar(CLIENT * c)
{
	int16_t v=readChar(c);
	while(v<0)
	{
		if(v<-1)
		{
			return v;
		}
		usleep(10000);
		v=readChar(c);
	}
	return v;
}
uint8_t writeChar(CLIENT * c, uint8_t ch)
{
	char ret;
	while(1)
	{
		int read = send(c->client_fd, &ch, 1, 0);
		if (read < 0)
		{
			if(errno!=EAGAIN&&errno!=EWOULDBLOCK)
			{
				on_error("Client read failed\n");
				return 1;
			}
			// Wait little and try again
		}else if(read==0)
		{
			// Wait little and try again
		}else
		{
			return 0;
		}
		usleep(10000);
	}
}
uint8_t readLine(CLIENT * c)
{
	c->linePtr=0;
	int16_t ch;
	while(1)
	{
		ch=readChar(c);
		if(ch>=0)
		{
			if(ch=='\r')
			{
				// ignore
			}else if(ch=='\n')
			{
				// line ended
				c->line[c->linePtr]=0;
				return 0;
			}
			else
			{
				c->line[c->linePtr]=(char)ch;
				c->linePtr++;
				if(c->linePtr>=LINE_MAX-2)
				{
					// Crop the end of line to not overflow
					c->linePtr=LINE_MAX-2;
				}
			}
		}else if(ch==-1)
		{
			usleep(10000);
		}else
		{
			// error
			return 1;
		}
	}
}
uint8_t sendAll(CLIENT * c, const char * data, int n)
{
	for(int i=0;i<n;++i)
	{
		if(writeChar(c, data[i]))
		{
			return 1;
		}
	}
	return 0;
}
void writeString(CLIENT * c, const char * str)
{
	sendAll(c, str, strlen(str));
//	usleep(5000000);
}
void protoAssert(CLIENT * c, uint8_t v)
{
	if(!v)
	{
		printf("PROTOCOL ERROR\n");
		fflush(stdout);
	}
}
void serveWS(CLIENT * c)
{
/*
 	while (1) {
		readLine(c);
		printf("WS line: %s\n",c->line);
		if(c->linePtr==0)
		{
			break;
		}
	}
*/
	printf("All lines received!\n");
//	usleep(5000000);
//	printf("Send line 1 node\n");
//	fflush(stdout);
//	usleep(5000000);
	printf("Send reply!\n");
	writeString(c, "HTTP/1.1 101 WebSocket Protocol Handshake\nUpgrade: websocket\nConnection: Upgrade\nSec-WebSocket-Accept: ");
	writeString(c, c->calculatedKey);
	writeString(c, "\n");
	writeChar(c, 0b10000001);
	writeChar(c, 0b00000001);
	writeChar(c, 'A');
	writeChar(c, 0b10000001);
	writeChar(c, 0b00000001);
	writeChar(c, 'B');
	printf("Payload value:\n");
	fflush(stdout);
 	uint8_t c0=readFullChar(c);
	protoAssert(c, c0 & 0b10000000); // Must be finish frame: each message is single frame
	protoAssert(c, c0 & 0b01110000 == 0); // These bits must be 0
	uint8_t opcode=c0 & 0b00001111;
	protoAssert(c, opcode==1); // Must be a text message
 	uint8_t c1=readFullChar(c);
	protoAssert(c, c1 & 0b10000000); // Must be masked because this is a client message
	uint8_t size0=c1 & 0b01111111;
	protoAssert(c, size0!=126); // Extended size is not handled yet by this server
	protoAssert(c, size0!=127); // Extended size is not handled yet by this server
	printf("Size: %d\n",size0);
	uint8_t mask[4];
	for(int i=0;i<4;++i)
	{
		mask[i]=readFullChar(c);
	}
	for(int i=0;i<size0;++i)
	{
		uint8_t c0=readFullChar(c);
		uint8_t c1=c0^mask[i%4];
		printf(" %c %x", c1,(int)c1);
	}
}
void serveHtml(CLIENT * c)
{
	writeString(c, "HTTP/1.1 200 OK\n\n<!DOCTYPE html>\n<html>\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n<link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n<script>\nwindow.addEventListener(\"load\", function(){\n\tconsole.info(\"Loaded!\");\n\tvar ws = new WebSocket(\"ws://localhost:8888/echo\");\n\t         ws.onopen = function() {\n                  \n                  // Web Socket is connected, send data using send()\n                  ws.send(\"ALMA\");\n                  console.info(\"Message is sent...\");\n               };\n\t\t\t\t\n               ws.onmessage = function (evt) { \n                  var received_msg = evt.data;\n                  console.info(\"Message is received...\"+received_msg+\"REALLY\");\n               };\n\t\t\t\t\n               ws.onclose = function() { \n                  \n                  // websocket is closed.\n                  console.info(\"Connection is closed...\"); \n               };\n}, false);\n\n</script>\n</head>\n<body>tartalom\n</body></html>\n\n");

}
char mark[]="258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
void * serve_client(void * p)
{
	CLIENT * c=(CLIENT *)p;
	char newline[]="\n";
	printf("new thread\n");
	fcntl(c->client_fd, F_SETFL, O_NONBLOCK);
	uint8_t isWS=0;
 	while (1) {
		if(readLine(c))
		{
			break;
		}
		printf("Queries: %s\n", c->line);
		if(!strncmp(c->line, "Sec-WebSocket-Key: ", 19))
		{
			printf("WebSocket: %s\n", c->line+19);
			unsigned char hash_out[21];
//			SHA1(aa, c->line+19, 24);
//			printf("sha1ed: %s\n", "");
			SHA1_CTX ctx;
			unsigned int ii;
			SHA1Init(&ctx);
			for (ii=0; ii<24; ii+=1)
			{
				SHA1Update(&ctx, (const unsigned char*)c->line+19 + ii, 1);
			}
			for (ii=0; ii<strlen(mark); ii+=1)
			{
				SHA1Update(&ctx, (const unsigned char*)mark+ ii, 1);
			}
			SHA1Final((unsigned char *)hash_out, &ctx);
			size_t out_len;
			unsigned char * based=base64_encode(hash_out, 20, &out_len);
			strcpy(c->calculatedKey, (char *)based);
			printf("%s linePtr: %d\n", based, c->linePtr);
			free(based);
			isWS=1;
		}
		if(c->linePtr==0)
		{
			if(isWS)
			{
				serveWS(c);
			}
			else
			{
				serveHtml(c);
			}
			break;
		}
    }
	close(c->client_fd);
	printf("Thread exit\n");
    free(p);
    return NULL;
}
int main (int argc, char *argv[]) {
  if (argc < 2) on_error("Usage: %s [port]\n", argv[0]);

  int port = atoi(argv[1]);

  int server_fd, client_fd, err;
  struct sockaddr_in server, client;

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) on_error("Could not create socket\n");

  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  int opt_val = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val);

  err = bind(server_fd, (struct sockaddr *) &server, sizeof(server));
  if (err < 0) on_error("Could not bind socket\n");

  err = listen(server_fd, 128);
  if (err < 0) on_error("Could not listen on socket\n");

  printf("Server is listening on %d\n", port);

  while (1) {
    socklen_t client_len = sizeof(client);
    client_fd = accept(server_fd, (struct sockaddr *) &client, &client_len);
    if (client_fd < 0) on_error("Could not establish new connection\n");
	CLIENT * c=(CLIENT *)malloc(sizeof(CLIENT));
	c->client_fd=client_fd;
	pthread_create(&(c->t), NULL, serve_client, c);
  }

  return 0;
}

