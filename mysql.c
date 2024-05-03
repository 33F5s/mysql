#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "mysql.h"

int main(void){
    //初始化
    MYSQL *db;
    db = mysql_init(NULL);
    if(db==NULL){
        perror("fail to init");
        return -1;
    }

    //连接至数据库
    db = mysql_real_connect(db,host,user,password,dbsensor,port,NULL,0);
    if(db==NULL){
        perror("fail to connect");
        return -1;
    }

    //打开传感器设备文件
    int dht11fd = open(dht11Dir,O_RDONLY);
    int ap3216cfd = open(ap3216cDir,O_RDONLY);
    
    char sql_qry[100];                       //sql指令
    char data8[5];                           //传感器数据读取暂存 8位
    short data16[6];                         //传感器数据读取暂存 16位

    time_t now;
    struct tm *t;
    char mytime[30];
    while (1)
    {
        //获取当前时间
        time(&now);
        t = localtime(&now);                
        sprintf(mytime,"%d-%d-%d %d:%d:%d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);

        //dht11数据上传
        read(dht11fd,data8,5);
        sprintf(sql_qry,"insert into dht11(date,tempture,humidity) values ('%s','%d.%d','%d.%d')",mytime,data8[2],data8[3],data8[0],data8[1]);
        int ret = mysql_query(db,sql_qry);
        if(ret!=0){
            perror("fail to query");
            return -1;
        }

        //ap3216c数据就上传
        read(ap3216cfd,data16,6);
        sprintf(sql_qry,"insert into ap3216c(date,als,ir) values ('%s','%d','%d')",mytime,data16[0],data16[1]);
        ret = mysql_query(db,sql_qry);
        if(ret!=0){
            perror("fail to query");
            return -1;
        }

        sleep(10);
    }


    return 0;
}