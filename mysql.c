#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <string.h>

#include "mysql.h"

int main(void){

    MYSQL *test;
    test = mysql_init(NULL);
    if(test==NULL){
        perror("fail to init");
        return -1;
    }

    test = mysql_real_connect(test,host,user,password,dbname,port,NULL,0);
    if(test==NULL){
        perror("fail to connect");
        return -1;
    }

    char *sql="delete from testTable";
    int ret = mysql_query(test,sql);
    if(ret!=0){
        perror("fail to query");
        return -1;
    }


    return 0;
}