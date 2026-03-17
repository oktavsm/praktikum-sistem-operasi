#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Inisialisasi mutex dan variabel global
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

// Fungsi untuk menambah nilai counter
void *increase() {
    pthread_mutex_lock(&mutex1);
    int i;
    for (i = 0; i < 99999; i++) {
        counter++;
        printf("Counter value: %d\n", counter);
    }
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

// Fungsi untuk mengurangi nilai counter
void *decrease() {
    pthread_mutex_lock(&mutex1);
    int i;
    for (i = 0; i < 99999; i++) {
        counter--;
        printf("Counter value: %d\n", counter);
    }
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

int main() {
    int rc1, rc2;
    pthread_t thread1, thread2;

    // Membuat thread pertama untuk mengeksekusi fungsi increase
    if ((rc1 = pthread_create(&thread1, NULL, &increase, NULL))) {
        printf("Thread creation failed: %d\n", rc1);
    }

    // Membuat thread kedua untuk mengeksekusi fungsi decrease
    if ((rc2 = pthread_create(&thread2, NULL, &decrease, NULL))) {
        printf("Thread creation failed: %d\n", rc2);
    }

    /* Menunggu hingga thread selesai sebelum main berlanjut.
       Tanpa ini, program utama bisa keluar dan menghentikan semua thread
       sebelum mereka menyelesaikan tugasnya.
    */
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    exit(EXIT_SUCCESS);
}