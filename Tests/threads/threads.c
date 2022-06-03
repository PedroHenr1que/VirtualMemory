#include <stdio.h>
#include <pthread.h>
void *test(void *args);
int main () {

        pthread_t threads[5];

        for (int i = 0; i < 5; i++) {
                int num = i;
                pthread_create(&threads[i], NULL, test, (void *)(size_t)num);
        }

        for (int i = 0; i < 5; i++) {
                int returnedValue;
                pthread_join(threads[i], (void *) &returnedValue);
                
                printf("%d\n",returnedValue);
                
        }
        
        
        return 0;
}

void *test(void *args) {

        int num = (int)(size_t)args;
        num = num * 10;
        return (void *)(size_t)num;
}