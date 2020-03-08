#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define ANGLE_SPREAD 15  // Gives 30 degree window for each speaker
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
  static int num_participants;

  unsigned int i;
  int num_matches=0;
  int person_speaking=-1;
  int matched_angle_diff, angle_diff;

 for (i=0;i<num_participants;i++) {
     participant[i].talking = false ;  // store value  
   }

  int angle_xy = (atan2(*x,*y) * 180.0) / M_PI ;

   //check is angle already recorded

  for (i=0;i<num_participants;i++) {
  // check how far away it is from a known source
    angle_diff =  angle_xy - participant[i].angle;
    angle_diff += (angle_diff>180) ? -360 : (angle_diff<-180) ? 360 : 0;
    if (abs(angle_diff) < ANGLE_SPREAD) {
      ++num_matches;
      person_speaking = i;
      matched_angle_diff = angle_diff;
     }      
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
        ++num_participants;
       }
    };

   if (num_matches == 1) {
     participant[person_speaking].talking = true;
//     if (!participant[person_speaking].was_talking) {
//     ++participant[person_speaking].num_turns;
     participant[person_speaking].angle += matched_angle_diff / 2 ;
     if (participant[person_speaking].total_talk_time % 50 == 0) printf ("Angle diff = %d.  Person %d is now at %d and they talked for %ld at %3.2f\n", matched_angle_diff, 
       person_speaking, participant[person_speaking].angle, participant[person_speaking].total_talk_time,participant[person_speaking].freq);
//         }
     ++participant[person_speaking].total_talk_time;

     if (*freq > 0.0) participant[person_speaking].freq +=  (*freq - participant[person_speaking].freq)/participant[person_speaking].total_talk_time;
//     if (participant[person_speaking].total_talk_time % 100 == 0)  printf("freq %3.2f\n",participant[person_speaking].freq);
        
//   if (num_matches > 1) printf ("error overlap of %d people\n", num_matches);
    }
}
      

 


