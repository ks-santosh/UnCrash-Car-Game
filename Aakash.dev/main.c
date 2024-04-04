#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Functions for Sound Effects in the Game
void play_ignition();
void play_engine(int speed);
void play_crash();

int main()
{
    int running = 1; //Game Loop

    play_ignition(); //Play Ignition Sound

    while (running) //For Sound at Different Car Speed
    {

    int speed = rand()%100; //Random Speed Between 0 and 99

    play_engine(speed); // Engine Sound based on Speed

    //To be Replaced by Crash Detection Codes
    char choice=getchar();
    if(choice == 'c' || choice =='C')
    {
        play_crash();
        running=0; // Stop the Game Loop
    }
    }
    printf("Game Over!\n");
    return 0;
}
void play_ignition() //Function to play Engine Sound based on Speed in the Game
{
    printf("Ignition Sound\n");// Simulate Engine Sound
}
void play_engine(int speed)
{
     printf("Engine Sound\n");

     // Simulate Delay Based on Speed
     int delay = 100-speed;
     struct timespec ts;
     ts.tv_sec=delay/1000;
     ts.tv_nsec=(delay%1000)*1000000;
     nanosleep(&ts,NULL);
}
void play_crash() //Function to play Crash Sound in the Game
{
    printf("Crash Sound\n");
}
