#include <pthread.h>
#include <stdio.h>

int counter = 0;

void *increment(void *arg){
    for (int i = 0; i < 100000; i++){
        counter++;
    }
    return NULL;
}

int main(){
    pthread_t t1, t2, t3, t4;

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);
    pthread_create(&t3, NULL, increment, NULL);
    pthread_create(&t4, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("counter = %d\n", counter);
    return 0;
}
