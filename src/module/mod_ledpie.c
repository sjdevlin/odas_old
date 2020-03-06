#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//#include <matrix_hal/everloop.h>
//#include <matrix_hal/everloop_image.h>
//#include <matrix_hal/matrixio_bus.h>

#define ANGLE_SPREAD 15  // Gives 30 degree window for each speaker
// MAX_VALUE : max value of energy
#define MIN_THRESHOLD 50
// MAX_BRIGHTNESS: 0 - 20
#define MAX_BRIGHTNESS 12
// MAX_PARTICIPANTS: Max number of people in meeting
#define MAX_PARTICIPANTS 6

void update_meeting_data(float * x, float * y, float * freq, float * activity) {

   struct meeting_member {
     int led_num;
     int angle;
     bool talking; 
     bool was_talking; 
     long total_talk_time;
     char sex;
     int num_turns;
     float freq;};
  
  static struct meeting_member participant [MAX_PARTICIPANTS];
  static int num_participants = 0;

  int num_matches=0;
  int person_speaking=-1;
  int matched_angle_diff, angle_diff;

// set everyone talking to false but store if they were talking last time
  for (int i=0;i<num_participants;i++) {
     participant[i].was_talking = participant[i].talking ;  // store value  
     participant[i].talking = false; // then reset
   }
 
  // Convert x,y to angle. TODO: See why x axis from ODAS is inverted
  int angle_xy = (atan2(*x,*y) * 180.0) / M_PI ;
   //check is angle already recorded
  for (int i=0;i<num_participants;i++) {
  // check how far away it is from a known source
    angle_diff =  angle_xy - participant[i].angle;
    angle_diff += (angle_diff>180) ? -360 : (angle_diff<-180) ? 360 : 0;
    if (abs(angle_diff) < ANGLE_SPREAD) {
      ++num_matches;
      person_speaking = i;
      matched_angle_diff = angle_diff;}      
}
   if (num_matches == 0) {
   //then its a new participant
     participant[num_participants].angle = angle_xy;
     participant[num_participants].led_num = (180-angle_xy)/20;
     participant[num_participants].talking = true;
     participant[num_participants].num_turns = 1;
     participant[num_participants].total_talk_time = 0;
     printf ("new member %d at %3d degrees.   LED number: %d \n", num_participants,angle_xy, participant[num_participants].led_num);
     if (num_participants<MAX_PARTICIPANTS-1) {
// error processing here..
     ++num_participants;}
     
    };    

   if (num_matches == 1) {
// add to existing participant
//     participant[person_speaking].freq += f / participant[person_speaking].total_talk_time;
     participant[person_speaking].talking = true;
     if (!participant[person_speaking].was_talking) {
     ++participant[person_speaking].num_turns;
     participant[person_speaking].angle += matched_angle_diff / 2;
     printf ("Angle diff = %d.  Person %d is now at %d and they talked for %ld \n", matched_angle_diff, person_speaking, participant[person_speaking].angle, participant[person_speaking].total_talk_time);
         }
     ++participant[person_speaking].total_talk_time;
     if (*freq > 0.0) participant[person_speaking].freq +=  (*freq - participant[person_speaking].freq)/participant[person_speaking].total_talk_time;
     if (participant[person_speaking].total_talk_time % 30 == 0)  printf("freq %3.2f\n",*freq);
        
//   if (num_matches > 1) printf ("error overlap of %d people\n", num_matches);
    }
}
      

 


