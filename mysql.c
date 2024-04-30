#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <string.h>

int main(void){

    MYSQL *test;
    test = mysql_init(NULL);
    if(test==NULL){
        perror("fail to init");
        return -1;
    }

    test = mysql_real_connect(test,"47.109.197.224","root","123456","test",3306,NULL,0);
    if(test==NULL){
        perror("fail to connect");
        return -1;
    }

    char *sql="insert into testTable values (1,'33f')";
    int ret = mysql_query(test,sql);
    if(ret!=0){
        perror("fail to query");
        return -1;
    }


    return 0;
}