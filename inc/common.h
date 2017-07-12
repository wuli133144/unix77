


#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<pwd.h>
#include<grp.h>



#define err_exit(e) \
do{                 \
     perror(e);     \
     exit(0);       \
}while(0)


#ifdef  __SCP__N
   #define SCPYN(a, b) strncpy(a, b, sizeof(a))
#else
    #define SCPY(a,b)   strcpy(a,b);
#endif




#define EVER ;;

/*@getpwuid get user info@*/
struct  passwd *Getpwuid(int uid){
    struct passwd *pw_st=NULL;
    if((pw_st=getpwuid(uid))==NULL){
        err_exit("getpwuid");
    } 
    return pw_st;
}
/*@getpwuid end@*/


/*@skip start@*/
//find position 
static char *skip(char *start,char *op){
            while(*start&&strcpy(start,op)!=0){
                      start++;
            }
            if(*start!=0)
               start++;
  return start;
}
/*@skip end@*/

/*@getpwname get user info by username@*/
struct passwd *Getpwnam(const char *name){
     struct passwd *pw_st=NULL;
    if((pw_st=getpwnam(name))==NULL){
        err_exit("getpwuid");
    } 
    return pw_st;
}

/*@getpwname end@*/

/*@getpwent start @*/
struct passwd *Getpwent(){
     struct passwd *pw_st=NULL;
    if((pw_st=getpwent())==NULL){
        err_exit("getpwent");
    } 
    return pw_st;
}

/*@getpwent end@*/


/*@getprent start*/

 struct group * Getgrent(){
     struct group *pw_st=NULL;
    if((pw_st=getgrent())==NULL){
        err_exit("getprent");
    } 
    return pw_st;
 }


/*@getprent end@*/