#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void play_ignition();
void play_engine(int speed);
void play_crash();

int main()
{
    int running = 1;

    play_ignition();

    while (running)
    {

    int speed = rand()%100;

    play_engine(speed);

    char choice=getchar();
    if(choice == 'c' || choice =='C')
    {
        play_crash();
        running=0;
    }
    }
    printf("Game Over!\n");
    return 0;
}
void play_ignition()
{
    printf("Ignition Sound\n");
}
void play_engine(int speed)
{
     printf("Engine Sound\n");

     int delay = 100-speed;
     struct timespec ts;
     ts.tv_sec=delay/1000;
     ts.tv_nsec=(delay%1000)*1000000;
     nanosleep(&ts,NULL);
}
void play_crash()
{
    printf("Crash Sound\n");
}
