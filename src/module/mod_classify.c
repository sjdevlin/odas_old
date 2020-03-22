 
   /**
    * \file     mod_classify.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */
    
    #include <module/mod_classify.h>
    #include <module/update_led.h>

    mod_classify_obj * mod_classify_construct(const mod_classify_cfg * mod_classify_config, const msg_hops_cfg * msg_hops_config, const msg_tracks_cfg * msg_tracks_config, const msg_categories_cfg * msg_categories_config) {


        mod_classify_obj * obj;

        obj = (mod_classify_obj *) malloc(sizeof(mod_classify_obj));

        obj->hop2frame = hop2frame_construct_zero(msg_hops_config->hopSize, 
                                                  mod_classify_config->frameSize,
                                                  msg_hops_config->nChannels);

        obj->frames = frames_construct_zero(msg_hops_config->nChannels, 
                                            mod_classify_config->frameSize);

        obj->frame2freq = frame2freq_construct_zero(mod_classify_config->frameSize, 
                                                    (mod_classify_config->frameSize)/2+1);

        obj->freqs = freqs_construct_zero(msg_hops_config->nChannels, 
                                          (mod_classify_config->frameSize)/2+1);

        obj->freq2acorr = freq2acorr_construct_zero(msg_hops_config->nChannels, 
                                                    (mod_classify_config->frameSize)/2+1);

        obj->acorrs = acorrs_construct_zero(msg_hops_config->nChannels, 
                                            (mod_classify_config->frameSize)/2+1);

        obj->acorr2pitch = acorr2pitch_construct_zero(msg_hops_config->nChannels, 
                                                      (mod_classify_config->frameSize)/2+1, 
                                                      mod_classify_config->winSize);

        obj->pitches = pitches_construct_zero(msg_hops_config->nChannels);

        obj->pitch2category = pitch2category_construct_zero(msg_hops_config->nChannels, 
                                                            mod_classify_config->tauMin, 
                                                            mod_classify_config->tauMax, 
                                                            mod_classify_config->deltaTauMax, 
                                                            mod_classify_config->alpha, 
                                                            mod_classify_config->gamma, 
                                                            mod_classify_config->phiMin, 
                                                            mod_classify_config->r0);

        obj->in1 = (msg_hops_obj *) NULL;
        obj->in2 = (msg_tracks_obj *) NULL;
        obj->out = (msg_categories_obj *) NULL;

        obj->enabled = 0;

// create led driver object
        int empty_array[NUM_LEDS][NUM_COLOURS];
        update_led(INITIALIZE, empty_array); 

// put some error processing in here...

        return obj;

    }

    void mod_classify_destroy(mod_classify_obj * obj) {

        hop2frame_destroy(obj->hop2frame);
        frames_destroy(obj->frames);
        frame2freq_destroy(obj->frame2freq);
        freqs_destroy(obj->freqs);
        freq2acorr_destroy(obj->freq2acorr);
        acorrs_destroy(obj->acorrs);
        acorr2pitch_destroy(obj->acorr2pitch);
        pitches_destroy(obj->pitches);
        pitch2category_destroy(obj->pitch2category);

        free((void *) obj);

    }

    int mod_classify_process(mod_classify_obj * obj) {


        static struct meeting_member participant [MAX_PARTICIPANTS];
        static int num_participants;
        

        unsigned int i;
        unsigned int num_matches=0;
        int person_speaking=-1;
        int angle_xy, matched_angle_diff, angle_diff;

        int rtnValue;
        unsigned int iTrack;
        const int rgbw_value[MAX_PARTICIPANTS][NUM_COLOURS] = {RED,BLUE,GREEN,YELLOW,CYAN,PURPLE}; 
        int led_array [NUM_LEDS][NUM_COLOURS];

        for (i=0;i<NUM_LEDS;i++) {
             led_array[i][0] = 0;
             led_array[i][1] = 0;
             led_array[i][2] = 0;
             led_array[i][3] = 0;}


        if (obj->in1->timeStamp != obj->in2->timeStamp) {
            printf("Time stamp mismatch.\n");
            exit(EXIT_FAILURE);
        }

        if (msg_hops_isZero(obj->in1) == 0) {

            if (obj->enabled == 1) {

                hop2frame_process(obj->hop2frame, obj->in1->hops, obj->frames);
                frame2freq_process(obj->frame2freq, obj->frames, obj->freqs);
                freq2acorr_process(obj->freq2acorr, obj->freqs, obj->acorrs);
                acorr2pitch_process(obj->acorr2pitch, obj->acorrs, obj->pitches);

                // store value about last state for each participant and then set all to not talking


                for (iTrack=0;iTrack < obj->in2->tracks->nTracks;iTrack++){

//                     if (obj->in1->timeStamp%100 == 0) printf ("Track: %d, Track id: %d, Pitch: %3.2f, Act: %1.2f \n", 
//                         iTrack, obj->in2->tracks->ids[iTrack], obj->pitches->array[iTrack],obj->in2->tracks->activity[iTrack]);  

                     if (obj->in2->tracks->ids[iTrack] != 0) {  

                      //insert code here to check if ID is in use (cycle through particpants)
                      // if it is in use then simply increment
                      // if it is not in use then might e new talker OR new talk from old talker
                      // how to age a provisional so that it is retired ? 
                                           
                      // cycle through timestamps - if last time stamp is old and still provisional then
                      // reture that person will it always be the last person added ?  Probably
                      
                         angle_xy = (atan2 ( obj->in2->tracks->array[iTrack+1] , obj->in2->tracks->array[iTrack+0]  ) * 180.0) / M_PI ;

                        //check is angle already recorded
                         num_matches = 0;

                      
                      
                         for (i=0;i<num_participants;i++) {
                             // check how far away it is from a known source - minimum angle
                              angle_diff =  angle_xy - participant[i].angle;
                              angle_diff += (angle_diff>180) ? -360 : (angle_diff<-180) ? 360 : 0;

                              if (abs(angle_diff) < ANGLE_SPREAD) {
 
                                  ++num_matches;
                                  person_speaking = i;
                                  matched_angle_diff = angle_diff;
                              }      

                         }

                         if (num_matches == 0 &&  obj->pitches->array[iTrack] > 50.0) {

                           //then its a new participant
                             participant[num_participants].angle = angle_xy;
                             participant[num_participants].led_num = (180-angle_xy)*360/NUM_LEDS;
                             participant[num_participants].status = PROVISIONAL;
                             participant[num_participants].last_trackID = obj->in2->tracks->ids[iTrack];
                             participant[num_participants].num_turns = 1;
                             participant[num_participants].total_talk_time = 0;
                             printf ("new member %d at %3d degrees.   LED number: %d \n", num_participants,angle_xy, participant[num_participants].led_num);
                       
                             if (num_participants <= MAX_PARTICIPANTS) {
                                 // error processing here..
                                ++num_participants;
                             }
                         }

                         else if (num_matches == 1 ) {

                                 if (obj->pitches->array[iTrack] > 50.0 && obj->pitches->array[iTrack] < 300.0) {

                                     ++participant[person_speaking].total_talk_time;
                                     participant[person_speaking].timestamp_last_heard = obj->in1->timeStamp;
                                     participant[person_speaking].angle += matched_angle_diff / 2 ;
                           
                                     if (obj->pitches->array[iTrack] > 0.0) participant[person_speaking].freq +=  
                                         (obj->pitches->array[iTrack] - participant[person_speaking].freq)/participant[person_speaking].total_talk_time;
                                         
                                     if (participant[person_speaking].status = PROVISIONAL) {
                                          && 
                                         participant[person_speaking].total_talk_time > 200
                                         if (participant[person_speaking].last_trackID = obj->in2->tracks->ids[iTrack]) &&
                                         
                                  
                                         led_array[participant[person_speaking].led_num][0] = rgbw_value[person_speaking][0];
                                         led_array[participant[person_speaking].led_num][1] = rgbw_value[person_speaking][1];
                                         led_array[participant[person_speaking].led_num][2] = rgbw_value[person_speaking][2];
                                         led_array[participant[person_speaking].led_num][3] = rgbw_value[person_speaking][3];
                                     }
                                          

                                     if ( participant[person_speaking].total_talk_time %100 == 0 ) printf ("Angle diff = %d.  Person %d is now at %d and they talked for %ld at %3.2f\n", matched_angle_diff, 
                                          person_speaking, participant[person_speaking].angle, participant[person_speaking].total_talk_time,
                                          participant[person_speaking].freq);
                                 }

                         }


                     }

                }

                update_led(UPDATE, led_array);

            }

            else {

                categories_zero(obj->out->categories);

            }

            obj->out->timeStamp = obj->in1->timeStamp;

            rtnValue = 0;

        }

        else {

            msg_categories_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;

    }

    void mod_classify_connect(mod_classify_obj * obj, msg_hops_obj * in1, msg_tracks_obj * in2, msg_categories_obj * out) {

        obj->in1 = in1;
        obj->in2 = in2;
        obj->out = out;

    }

    void mod_classify_disconnect(mod_classify_obj * obj) {

        obj->in1 = (msg_hops_obj *) NULL;
        obj->in2 = (msg_tracks_obj *) NULL;
        obj->out = (msg_categories_obj *) NULL;

    }

    void mod_classify_enable(mod_classify_obj * obj) {

        obj->enabled = 1;

    }

    void mod_classify_disable(mod_classify_obj * obj) {

        obj->enabled = 0;

    }

    mod_classify_cfg * mod_classify_cfg_construct(void) {

        mod_classify_cfg * cfg;

        cfg = (mod_classify_cfg *) malloc(sizeof(mod_classify_cfg));

        return cfg;

    }

    void mod_classify_cfg_destroy(mod_classify_cfg * cfg) {

        free((void *) cfg);

    }

    void mod_classify_cfg_printf(const mod_classify_cfg * cfg) {

    }
