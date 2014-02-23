#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <pthread.h>

char *HOST = "127.0.0.1";
char PORT[100];
char *CONFIG="httpd.conf";
char WWWROOT[100];

struct request {
    int sock;
    char buff[100];
    char http[100];
    char url[100];
    char method[100];
    char cookie[100];
    char filename[100];
    char mime[100];
    char path[100];
};

void read_input(int argc, char *argv[]){
    int i;
    for(i=1;i<argc;i++){
        if(strcmp(argv[i++], "-p")==0){
            strcpy(PORT, argv[i]);
        }
    }
}

void read_file(){
    FILE *fp = fopen(CONFIG, "r");
    char line[100], key[100], value[100];

    while(fgets(line, 100, fp)!=NULL){
        sscanf(line, "%[^ ] %s", key, value);
        if(strcmp(key, "PORT")==0){
            strcpy(PORT, value);
        }
        else if(strcmp(key, "WWWROOT")==0){
            strcpy(WWWROOT, value);
        }
    }

}

int get_status_line(char *buff, char *http, char *method, char *url){
    char *token;
    char  *temp = strdup(buff);

    while((token=strsep(&temp, "\n"))!=NULL){
        sscanf(token, "%[^ ] %[^ ] %s", method, url, http);
        return;
    }
    return 0;
}

int get_header(struct request *r, char *buff){
    char *token;
    char key[100], value[100];
    char  *temp = strdup(buff);

    while((token=strsep(&temp, "\n"))!=NULL){
        sscanf(token, "%[^ ] %s", key, value);
        if(strcmp(key, "Cookie:")==0){
            strcpy(r->cookie, value);
        }
    }
    return 0;
}

int get_mime(char *ext, char *mime){
  
    FILE *fp = fopen("mime.types", "r");
    char line[100], key[100], value[100];

    while(fgets(line, 100, fp)!=NULL){
        if(line[0] == '#') continue;
        sscanf(line, "%[^ ] %s", key, value);
        if(strcmp(value, ext)==0){
            strcpy(mime, key);
            return 0;
        }
     
    }
    return 1; 
}

int get_filesize(FILE *fp){
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    rewind(fp);
    return size;
}

int sendHeader(char *buff, int size, char *mime){
    

}

void *run(void *attr){
    char buff[1000];
    struct request *r = (struct request*)attr;
    printf("Recieved: %s\n", r->buff);

    while(1){
    recv(r->sock, buff, 1000, 0);
    printf("after select %s\n", buff);
    sleep(10);
    }


  

    /*

    //Get status line data
    get_status_line(r->buff, r->http, r->method, r->url);
    
    get_header(r, r->buff);
    strcpy(r->filename, strrchr(r->url, '/')+1);
    
    char ext[100];
    strcpy(ext, strrchr(r->filename, '.')+1);
    printf("%s\n",r->filename);

    get_mime(ext, r->mime);
    printf("%s\n",r->mime);

    //Make path
    strcat(r->path, WWWROOT);
    strcat(r->path, r->filename);
    printf("%s\n", r->path);

    FILE *fp = fopen(r->path, "r");
    int size = get_filesize(fp);
    printf("Size: %d\n", size);
    

    //Send Header
    sendHeader("\r\nHTTP/1.1 200 OK", size, mime);
    */
}

void start(){
    struct addrinfo hints, *res;

    memset(&hints, 0, 1000);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(HOST, PORT, &hints, &res);

    int sock = socket(res->ai_family, res->ai_socktype, 0);

    bind(sock, res->ai_addr, res->ai_addrlen);

    listen(sock, 10);

    char buff[100];
    while(1){
        printf("WAITING\n");
        int nsock = accept(sock, res->ai_addr, &(res->ai_addrlen));
        printf("ACCEPTED\n");

        recv(nsock, buff, 100, 0);

        struct request *r = (struct request *)malloc(sizeof(*r));      
        strcpy(r->buff, buff);
        r->sock = nsock;

        pthread_t th;
        pthread_create(&th, NULL, run, (void*)r);

    }

}

int main(int argc, char *argv[]){

    read_file();
    read_input(argc, argv);


    start();

}
