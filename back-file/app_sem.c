#include "app_sem.h" 


int sem_id;
int set_semvalue(){
    sem_u sem_union;
    sem_union.val = 1;
    if(semctl(sem_id,0,SETVAL,sem_union) == -1)
        return 0;
    return 1;
}

int semaphore_p(){
    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = -1;
    sem_buf.sem_flg = SEM_UNDO;
    if(semop(sem_id,&sem_buf,1) == -1){
        fprintf(stderr,"semaphore_p failed!\n");
        return 0;
    }
    return 1;
}


int semaphore_v(){
    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = 1;
    sem_buf.sem_flg = SEM_UNDO;
    if(semop(sem_id,&sem_buf,1) == -1){
        fprintf(stderr,"semaphore_v failed!\n");
        return 0;
    }
    return 1;
}


void del_semvalue(){
    sem_u sem_union;
    if(semctl(sem_id,0,IPC_RMID,sem_union) == -1){
        fprintf(stderr,"Delete Failed!\n");
    }
}


void init_semvalue(){
    sem_u sem_union[4];
    if(-1 == (sem_id = semget(KEY,4,IPC_CREAT|660))){
        printf("ERROR!");
    }
    for(int i = 0; i < 4;i++){
        sem_union[i].val = 1;
        semctl(sem_id,i,SETVAL,sem_union[i]);
    }

    for(int i = 0; i < 4; i++){
        printf("The semval(%d) = %d \n",i,semctl(sem_id,i,GETVAL,NULL));
    }
}
