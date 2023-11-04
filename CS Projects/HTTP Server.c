#define  _POSIX_C_SOURCE 200809L
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/select.h>
#include<assert.h>

#include<sys/socket.h>
#include<arpa/inet.h>

#define exit(N) {fflush(stdout); fflush(stderr); _exit(N); }
static void handle_client(int connfd);


static int get_port(void)
{
    int fd = open("port.txt", O_RDONLY);
    if (fd < 0) {
        perror("Could not open port.txt");
        exit(1);
    }

    char buffer[32];
    int r = read(fd, buffer, sizeof(buffer));
    if (r < 0) {
        perror("Could not read port.txt");
        exit(1);
    }

    return atoi(buffer);
}

int main(int argc, char** argv)
{
    int port = get_port();

    printf("Using port %d\n", port);
    printf("PID: %d\n", getpid());

    // Make server available on port

    // create socket
    int listenfd = socket (AF_INET, SOCK_STREAM, 0);

    // bind socket to socket address
    static struct sockaddr_in server ;
    server . sin_family = AF_INET ;
    server . sin_port = htons (port);
    inet_pton ( AF_INET , " 127.0.0.1 ", &( server . sin_addr ));

    // Bind
    int optval = 1;
    setsockopt ( listenfd , SOL_SOCKET , SO_REUSEADDR , & optval , sizeof ( optval ));
    bind ( listenfd , ( struct sockaddr *)& server , sizeof ( server ));

    // set socket to be listening
    listen (listenfd, 100);



    // Process client requests
    // implement the accept loop we discussed in class calling handle_client
    struct sockaddr_in client;
    socklen_t csize = sizeof(client);
    while (1) {
        int connfd = accept ( listenfd , ( struct sockaddr *)& client , & csize );
        handle_client ( connfd );
        close ( connfd );
    }
    close(listenfd);
    return 0;
}


static char request[2048];
static char response[2048];

static char* message = "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n%s";
//erorr messages
static char* fileNotFound = "HTTP/1.1 404 Not Found\r\n\r\n";
static char* badRequest = "HTTP/1.1 400 Bad Request\r\n\r\n";
//for milestone4
int length = 7;
//data for milestone8
int requestNum = -1, headerBytes = 0, bodyBytes = 0, errors = 0, errorBytes = 0;

static void handle_client (int connfd) {
    // receive the clients request and store it in char request[]
    static char savedMessage[2048] = "<empty>";
    ssize_t amt = recv(connfd , request , 2048, 0);
    request[amt] = '\0';
    char copyRequest[2048];
    strcpy(copyRequest,request);
    char* method = strtok(request, " ");
    char* url = strtok(NULL, " ");
    char* startOfHeader = strtok(NULL, "\r\n");

    

    if (url != NULL && method != NULL) {
        if (strcmp(method,"GET") == 0 && strcmp(url,"/ping") == 0) {
            //handle GET /ping here
            //test 2
            char* content = "pong";
            snprintf(response, 1024, message, 4, "");
            headerBytes += strlen(response);
            bodyBytes += strlen(content);
            snprintf(response, 1024, message, 4, content);
            send(connfd, response,strlen(response), 0);


        } else if (strcmp(method,"GET") == 0 && strcmp(url,"/echo") == 0) {
            //handle GET /echo here
            //test 3
            char* token = strtok(NULL, "\r\n");
            char* tokenList[40];
            
            int count = 1;
            int headerLength = 0;

            //takes first header otherwise theres no headers
            if (token != NULL) {
                tokenList[0] = token;
                headerLength = headerLength + strlen(token);
            } else {
                count = 0;
            }

            //loops through all headers
            while (token != NULL && headerLength < 1004) {
                token = strtok(NULL, "\r\n");
                if (token != NULL) {
                    tokenList[count] = token;
                    headerLength = headerLength + strlen(token) + strlen("\r\n");
                    count++;
                }
            }

            //creates a character array to store the headers initializes it to a null char at 0th index
            char headers[2048];
            headers[0] = '\0';

            //adds the \r\n to all necessary parts of the character array: headers
            for (int i = 0; i < count; i++) {
                strcat(headers, tokenList[i]);
                if (i < count -1) {
                    strcat(headers, "\r\n");
                }
            }

            //forces length to be 1004 as its max
            if (headerLength > 1004) {
                headerLength = 1004;
            }

            //places a null in the last accepted character so strcpy stops at the 1004th character
            char newHeaders[1005];
            headers[1004] = '\0';
            strcpy(newHeaders, headers);
            
            

            snprintf(response, 2048, message, headerLength, "");
            headerBytes += strlen(response);
            bodyBytes += strlen(newHeaders);
            snprintf(response, 2048, message, headerLength, newHeaders);
            printf("\n\n\nresponse: %s\n\n\n", response);

            //ensures the entire message is sent
            int bytesToSend = strlen(response);
            int bytesSent = send(connfd, response, strlen(response), 0);
            while (bytesSent < bytesToSend) {
                bytesSent += send(connfd, response, strlen(response), 0);
            }

        } else if (strcmp(method,"GET") == 0 && strcmp(url,"/read") == 0) {
            //handle GET /read here
            //test 4

            snprintf(response, 2048, message, length, "");
            headerBytes += strlen(response);
            bodyBytes += strlen(savedMessage);
            snprintf(response, 2048, message, length, savedMessage);
            int bytesToSend = strlen(response);
            
            int bytesSent = send(connfd, response, strlen(response), 0);

            while (bytesSent < bytesToSend) {
                bytesSent += send(connfd, response, strlen(response), 0);
            }

        } else if (strcmp(method,"POST") == 0 && strcmp(url,"/write") == 0) {
            //handle POST /write here
            //test 4
            
            char* lineStart = request;
            const char* target = "Content-Length: ";
            printf("request: <%s>\n\n\n\n", copyRequest);
            lineStart = strstr(copyRequest, target);
            if (lineStart != NULL) {
                length = atoi(lineStart + strlen(target));
                if (length > 1024) {
                    length = 1024;
                }

                // Move to the content after the double carriage return
                lineStart = strstr(lineStart, "\r\n\r\n");
                if (lineStart != NULL) {
                    lineStart += 4;
                }
            }
            if (lineStart[strlen(lineStart) - 1] == '\n') {
                lineStart[strlen(lineStart) - 1] = '\0';
            }

            int bodyLength = strlen(lineStart);
            printf("line length: <%d>\n\n\n", bodyLength);
            printf("line: \n%s\n\n\n", lineStart);

            char newBody[1024];
            strncpy(newBody,lineStart,1024);

            
            snprintf(savedMessage, 1025, "%s", lineStart);
            snprintf(response, 2048, message, length, "");
            headerBytes += strlen(response);
            bodyBytes += strlen(savedMessage);
            snprintf(response, 2048, message, length, savedMessage);
            printf("reponse:\n%s\n\n\n", response);
            int bytesToSend = strlen(response);
            
            int bytesSent = send(connfd, response, strlen(response), 0);

            while (bytesSent < bytesToSend) {
                bytesSent += send(connfd, response, strlen(response), 0);
            }
            

        } else if (strcmp(method,"GET") == 0 && strcmp(url,"/stats") == 0) {

            char* statsMessage = "Requests: %d\nHeader bytes: %d\nBody bytes: %d\nErrors: %d\nError bytes: %d";
            char stats[1024];
            snprintf(stats,1024,statsMessage,requestNum, headerBytes, bodyBytes, errors, errorBytes);
            bodyBytes += strlen(stats);
            int statLength = strlen(stats);
            snprintf(response, 2048, message, statLength, "");
            headerBytes += strlen(response);
            snprintf(response, 2048, message, statLength, stats);
            send(connfd, response, strlen(response), 0);

            
            
        } else if (strcmp(method, "GET") == 0) {
            //handle GET (filename here)
            //test 5

            //open file stored in url
            url[strlen(url)] = '\0';
            char* newUrl = (char*)malloc((strlen(url) + 2));
            newUrl[0] = '.';
            strcpy(newUrl + 1, url);
            int fd  = open(newUrl, O_RDONLY,0);
            // if (access(newUrl, F_OK) == 0) {
            //     printf("File is accessible file name: <%s>\n", newUrl);
            // }

            //file doesn't exist
            if (fd < 0) {
                //printf("file does not exist: <%s>\n", newUrl);
                // for (int i = 0; i <= (int)strlen(newUrl); i++) {
                //     printf("Char %d: %c\n", i, newUrl[i]);
                // }
                send(connfd, fileNotFound, strlen(fileNotFound), 0);
                
                errors++;
                errorBytes += strlen(fileNotFound);
                return;
            }
            free(newUrl);
            //finds file size using fstat
            struct stat buf;
            fstat(fd, &buf);
            int size = buf.st_size;

            snprintf(response, 1024, message, size,"");
            
            headerBytes += send(connfd, response, strlen(response), 0);

            char fileBuffer[1024];
            ssize_t bytesRead = 0;
            while ((bytesRead = read(fd, fileBuffer, 1023)) > 0) {
                bodyBytes += send(connfd, fileBuffer, bytesRead, 0);
            }
            close(fd);
            

        } else {
            //handle bad requests here
            send(connfd, badRequest, strlen(badRequest), 0);
            errorBytes += strlen(badRequest);

            errors++;
            requestNum--;
            
        }
    }
    requestNum++;
}