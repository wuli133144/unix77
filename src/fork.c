
#include"../inc/common.h"


#include<unistd.h>
#include<sys/types.h>
#include <sys/wait.h>
#include<errno.h>
#include<signal.h>

#define   TEST(msg)  printf(msg)

#define BUFSIZ       1024


/*@Fork start@*/
int Fork(){
    int fd;
    if((fd=fork())<0){
        err_exit("fork failed");
    }
    return fd;
}
/*@Fork end@*/


/*@vfork start @*/
int Vfork(){
      int fd;
    if((fd=vfork())<0){
        err_exit("vfork failed");
    }
    return fd;
}
/*@vfork end@*/

/*@close() start@*/
int Close(int fd){
    int cl;
    if((cl=close(fd))<0){
        err_exit("close error");
    }
    return cl;
}
/*@close end@*/


/*@waitpid() start@*/
int Wait(int *status){
     int s;
     if((s=waitpid(-1,status,0))==-1){
        err_exit("wait error!");
     }
     return s;
}  
/*@waitpid end@*/


/*@waitpid start@*/
 int Waitpid(int pid,int *status,int flag){
      int ret;
      if((ret=waitpid(pid,status,flag))==-1){
          err_exit("waitpid error!");
      }
      return ret;
 }
/*@waitpid end@*/


/*@waitpid plus@*/
void waitplus(){
    int childid;
    while((childid=Wait(NULL))!=-1){
        continue;
    }
    if(errno!=ECHILD){
        err_exit("wait error!");
    }
    return ;
}
/*#waitpid plus end#*/

/*@s_wait start@*/
int S_wait(int *status){
     int ret;
     while((ret=wait(NULL))==-1&&errno==EINTR){//handle eintr
         continue;
     }
     return ret;
}
/*@s_wait end@*/

/*@waitnointr_s start@*/
void Waitnointr_s(void){
    int childid;
     while((childid=Wait(NULL))!=-1){//handle errno intr
         continue;
     }
     if(errno!=ECHILD){
         err_exit("wait error!");
     } 

}

/*@waitnotr_s end@*/

/*@waitnointr start@*/
 void Waitnointr(){
     int childid;
     while((childid=Wait(NULL))!=-1&&EINTR==errno){//handle errno intr
         continue;
     }
     if(errno!=ECHILD){
         err_exit("wait error!");
     }
 }
/*@waitnointr end@*/



/*@getpgrp start@*/

pid_t Getpgrp(){
     pid_t pid;
      if((pid=getpgrp()<0)){
         err_exit("getpgrp failed");
      }
      return pid;
}
/*@getpgrp end@*/



/*@setpgid set proc group@*/
int Setpgid(pid_t pid,pid_t pgid){
     int ret;
     if((ret=setpgid(pid,pgid))==-1){
         err_exit("setpgid error!");
     }
     return ret;
}
/*@setpgid end@*/

int main(int argc ,char **argv){

       int fd;
       int status;
       fd=Fork();
       if(fd==0){
                Setpgid(getpid(),getppid());
                printf("%d\n",Getpgrp());
                printf("%d\n",Getpgrp());
                exit(0);
       }
       else {
                 Setpgid(getpid(),getpid());//create master of group
                 printf("%d\n",Getpgrp());
                 printf("%d\n",Getpgrp());
                 Wait(&status);
                 return 0;
       }      



    // TEST();
        
    //     int fd;
    //     int fd_fork;
    //     int status;

    //     char buf[BUFSIZ];
    //     bzero(buf,sizeof(buf));
    //    // setbuf(stdout,buf);
    //     fd=open("s_info",O_RDONLY);
    //     close(fd);
    //     close(fd);
    //     close(fd);
    //     fd_fork=Fork();
      #if 0
        if(fd_fork>0){
           TEST("parent msg\n");    
           wait(&status);
           exit(0);
           //_exit(0);
           // return 0; 
        }else if(fd_fork==0){
           TEST("child msg\n");    
           exit(0);
           //_exit(0);
        }
    #endif


  #if 0//test fork
   
   if(fd_fork==0){
       printf("child pid:%d",getpid());
       printf("child_parent pid:%d",getppid());
       printf("user id:%d",getuid());
       printf("user e id:%d",geteuid());
       
    
       return 0;
   }else{
        printf("parent pid:%d",getpid());
        printf("user parent id:%d",getuid());
        printf("user parent e id:%d",geteuid());
        wait(&status);
        return 0;
   }

  #endif

  #if 0
    char buffer[]="hello xrs!\n";
     
     //setbuf(stdout,buffer);
      setvbuf(stdout,buffer,_IONBF,sizeof(buffer));
      printf(buffer);
    if(fd_fork==0){
           printf("child!");
           exit(0);
    }else{
           printf("parent!");   
           return 0;              
    } 

  #endif 


  #if 1
        //  if(fd_fork==0){
        //      read(fd,buf,sizeof(buf));
        //      TEST(buf);
        //      //close(fd);
        //      //close(fd);
        //      exit(0);
        //  }else{
        //      sleep(1);
            
        //       close(fd);//close fd count--
        //       close(fd);
        //       close(fd);
        //       close(fd);
        //       //FILE 
        //      TEST("parent proc");
        //       wait(&status);
        //      return 0;

        //  }
  #endif


}