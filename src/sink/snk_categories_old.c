
   /**
    * \file     snk_categories.c
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
    
    #include <sink/snk_categories.h>
    #include <module/update_led.h>
    

    snk_categories_obj * snk_categories_construct(const snk_categories_cfg * snk_categories_config, const msg_categories_cfg * msg_categories_config) {

        snk_categories_obj * obj;

        obj = (snk_categories_obj *) malloc(sizeof(snk_categories_obj));

        obj->timeStamp = 0;

        obj->nChannels = msg_categories_config->nChannels;
        obj->fS = snk_categories_config->fS;
// meet pie
        obj->max_num_participants = snk_categories_config->max_num_participants;
        obj->num_participants = 0;
        obj->last_talker = 0;
        obj->meeting_duration = 0;
        obj->angle_spread = snk_categories_config->angle_spread;
        obj->energy_min = snk_categories_config->energy_min;
//
        obj->format = format_clone(snk_categories_config->format);
        obj->interface = interface_clone(snk_categories_config->interface);

        if (!(((obj->interface->type == interface_blackhole)  && (obj->format->type == format_undefined)) ||
              ((obj->interface->type == interface_file)  && (obj->format->type == format_text_json)) ||
              ((obj->interface->type == interface_socket) && (obj->format->type == format_text_json)) ||
              ((obj->interface->type == interface_led)  && (obj->format->type == format_meetpie)) ||
              ((obj->interface->type == interface_terminal) && (obj->format->type == format_text_json)))) {
            
            printf("Sink categories: Invalid interface and/or format.\n");
            exit(EXIT_FAILURE);

        }

        obj->buffer = (char *) malloc(sizeof(char) * 1024);
        memset(obj->buffer, 0x00, sizeof(char) * 1024);
        obj->bufferSize = 0;

// meet pie - set everything to 0 for participants
        obj->angle_array = (unsigned int *) malloc(sizeof(unsigned int) * 360);
        memset(obj->angle_array, 0x00, sizeof(unsigned int) * 360);
        obj->participant_is_talking = (unsigned int *) malloc(sizeof(unsigned int) * snk_categories_config->max_num_participants);
        memset(obj->participant_is_talking, 0x00, sizeof(unsigned int) * snk_categories_config->max_num_participants);
        obj->participant_total_talk_time = (unsigned int *) malloc(sizeof(unsigned int) * snk_categories_config->max_num_participants);
        memset(obj->participant_total_talk_time, 0x00, sizeof(unsigned int) * snk_categories_config->max_num_participants);
        obj->participant_angle = (unsigned int *) malloc(sizeof(unsigned int) * snk_categories_config->max_num_participants);
        memset(obj->participant_angle, 0x00, sizeof(unsigned int) * snk_categories_config->max_num_participants);


//

        obj->in = (msg_categories_obj *) NULL;

        return obj;

    }

    void snk_categories_destroy(snk_categories_obj * obj) {

        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj->buffer);
        free((void *) obj->angle_array);
        free((void *) obj->participant_angle);
        free((void *) obj->participant_is_talking);
        free((void *) obj->participant_total_talk_time);

        free((void *) obj);

    }

    void snk_categories_connect(snk_categories_obj * obj, msg_categories_obj * in) {

        obj->in = in;

    }

    void snk_categories_disconnect(snk_categories_obj * obj) {

        obj->in = (msg_categories_obj *) NULL;

    }

    void snk_categories_open(snk_categories_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                snk_categories_open_interface_blackhole(obj);

            break;

            case interface_file:

                snk_categories_open_interface_file(obj);

            break;

            case interface_led:

                snk_categories_open_interface_led(obj);

            break;

            case interface_socket:

                snk_categories_open_interface_socket(obj);

            break;

            case interface_terminal:

                snk_categories_open_interface_terminal(obj);

            break;

            default:

                printf("Sink categories: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;           

        }

    }

    void snk_categories_open_interface_blackhole(snk_categories_obj * obj) {

        // Empty

    }

    void snk_categories_open_interface_file(snk_categories_obj * obj) {

        obj->fp = fopen(obj->interface->fileName, "wb");

        if (obj->fp == NULL) {
            printf("Cannot open file %s\n",obj->interface->fileName);
            exit(EXIT_FAILURE);
        }        

    }

    void snk_categories_open_interface_led(snk_categories_obj * obj) {

// meet pie will need reworking
// this calls led module for first time just to initialize it 
        update_led('i', obj); 
//
    }



    void snk_categories_open_interface_socket(snk_categories_obj * obj) {

        memset(&(obj->sserver), 0x00, sizeof(struct sockaddr_in));

        obj->sserver.sin_family = AF_INET;
        obj->sserver.sin_addr.s_addr = inet_addr(obj->interface->ip);
        obj->sserver.sin_port = htons(obj->interface->port);
        obj->sid = socket(AF_INET, SOCK_STREAM, 0);

        if ( (connect(obj->sid, (struct sockaddr *) &(obj->sserver), sizeof(obj->sserver))) < 0 ) {

            printf("Sink categories: Cannot connect to server\n");
            exit(EXIT_FAILURE);

        }          

    }

    void snk_categories_open_interface_terminal(snk_categories_obj * obj) {

        // Empty

    }  

    void snk_categories_close(snk_categories_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                snk_categories_close_interface_blackhole(obj);

            break;

// meet pie

            case interface_led:

                snk_categories_close_interface_led(obj);

            break;
//
            case interface_file:

                snk_categories_close_interface_file(obj);

            break;

            case interface_socket:

                snk_categories_close_interface_socket(obj);

            break;

            case interface_terminal:

                snk_categories_close_interface_terminal(obj);

            break;

            default:

                printf("Sink categories: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    void snk_categories_close_interface_blackhole(snk_categories_obj * obj) {

        // Empty

    }

    void snk_categories_close_interface_led(snk_categories_obj * obj) {

        // Not sure what to do here.  Could free up Update LED mem ?

    }
    void snk_categories_close_interface_file(snk_categories_obj * obj) {

        fclose(obj->fp);

    }

    void snk_categories_close_interface_socket(snk_categories_obj * obj) {

        close(obj->sid);

    }

    void snk_categories_close_interface_terminal(snk_categories_obj * obj) {

        // Empty

    }

    int snk_categories_process(snk_categories_obj * obj) {

        int rtnValue;

        if (obj->in->timeStamp != 0) {

            switch(obj->format->type) {

                case format_text_json:

                    snk_categories_process_format_text_json(obj);

                break;

                case format_undefined:                

                    snk_categories_process_format_undefined(obj);

                break;

                case format_meetpie:                

                    snk_categories_process_format_meetpie(obj);

                break;


                default:

                    printf("Sink categories: Invalid format type.\n");
                    exit(EXIT_FAILURE);

                break;

            }

            switch(obj->interface->type) {

                case interface_blackhole:

                    snk_categories_process_interface_blackhole(obj);

                break;  
// meet pie
                case interface_led:

                    snk_categories_process_interface_led(obj);

                break;  
//
                case interface_file:

                    snk_categories_process_interface_file(obj);

                break;

                case interface_socket:

                    snk_categories_process_interface_socket(obj);

                break;

                case interface_terminal:

                    snk_categories_process_interface_terminal(obj);

                break;

                default:

                    printf("Sink categories: Invalid interface type.\n");
                    exit(EXIT_FAILURE);

                break;

            }

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    void snk_categories_process_interface_blackhole(snk_categories_obj * obj) {

        // Empty

    }

    void snk_categories_process_interface_file(snk_categories_obj * obj) {

        fwrite(obj->buffer, sizeof(char), obj->bufferSize, obj->fp);

    }

    void snk_categories_process_interface_led(snk_categories_obj * obj) {
        
        update_led('u', obj); 

    }


    void snk_categories_process_interface_socket(snk_categories_obj * obj) {

        if (send(obj->sid, obj->buffer, obj->bufferSize, 0) < 0) {
            printf("Sink categories: Could not send message.\n");
            exit(EXIT_FAILURE);
        }

    }

    void snk_categories_process_interface_terminal(snk_categories_obj * obj) {

        printf("%s",obj->buffer);

    }

    void snk_categories_process_format_text_json(snk_categories_obj * obj) {

        unsigned int iChannel;

        obj->buffer[0] = 0x00;

        sprintf(obj->buffer,"%s{\n",obj->buffer);
        sprintf(obj->buffer,"%s    \"timeStamp\": %llu,\n",obj->buffer,obj->in->timeStamp);
        sprintf(obj->buffer,"%s    \"src\": [\n",obj->buffer);

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            switch(obj->in->categories->array[iChannel]) {

                case 0x01:

                    sprintf(obj->buffer,"%s        { \"category\": \"speech\" }",obj->buffer);

                break;

                case 0x00:

                    sprintf(obj->buffer,"%s        { \"category\": \"nonspeech\" }",obj->buffer);

                break;

                default:

                    sprintf(obj->buffer,"%s        { \"category\": \"undefined\" }",obj->buffer);

                break;

            }

            if (iChannel != (obj->nChannels - 1)) {

                sprintf(obj->buffer,"%s,",obj->buffer);

            }

            sprintf(obj->buffer,"%s\n",obj->buffer);

        }
        
        sprintf(obj->buffer,"%s    ]\n",obj->buffer);
        sprintf(obj->buffer,"%s}\n",obj->buffer);

        obj->bufferSize = strlen(obj->buffer);

    }

    void snk_categories_process_format_undefined(snk_categories_obj * obj) {

        obj->buffer[0] = 0x00;
        obj->bufferSize = 0;

    }

// meet pie

    void snk_categories_process_format_meetpie(snk_categories_obj * obj) {

        unsigned int iChannel;
        unsigned int iAngle;
        unsigned int target_angle;
        unsigned int i;

        for (i=1;i<=obj->num_participants;i++){
            obj->participant_is_talking[i] = 0x00;
        }



        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {
            if (obj->in->categories->energy_array[iChannel] > obj->energy_min && obj->in->categories->array[iChannel]==0x01){
                    target_angle=obj->in->categories->angle_xy_array[iChannel];
                    if (obj->angle_array[target_angle] == 0x00) {
                    // new member
                    obj->num_participants++;
                    //printf("new");
                    // set angle location = to meeting person number
                    obj->angle_array[target_angle]=obj->num_participants;
                    // write a buffer around them
                    for (iAngle=0;iAngle<obj->angle_spread;iAngle++){
                        if (target_angle+iAngle<360){
                            // could check if already set here - but for now will just overwrite
                            // 360 is for going round the clock face
                            obj->angle_array[target_angle+iAngle]=obj->num_participants;
                        } 
                        else {
                            obj->angle_array[iAngle-1]=obj->num_participants;
                        }
                        if (target_angle-iAngle>0){
                            // could check if already set here - but for now will just overwrite
                            // 360 is for going round the clock face
                            obj->angle_array[target_angle-iAngle]=obj->num_participants;
                        } 
                        else {
                            obj->angle_array[360-iAngle]=obj->num_participants;
                        }

                    }
                    obj->participant_is_talking[obj->angle_array[target_angle]]=0x01;   
                    obj->last_talker=obj->num_participants;

                }
                else // its an existing talker we're hearing
                {
                    
                    i=angle_array[target_angle];
                    obj->last_talker=i;
//                    this is to start getting an average angle
//                    obj->participant[obj->buffer[target_angle]].angle = .9 * new_sample + (.1) * ma_old;
//
                    obj->participant[i].is_talking=0x01;
                    obj->participant[i].total_talk_time++;
                }

            }

        }
    }
//

    snk_categories_cfg * snk_categories_cfg_construct(void) {

        snk_categories_cfg * cfg;

        cfg = (snk_categories_cfg *) malloc(sizeof(snk_categories_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;
        cfg->angle_spread = 0;
        cfg->max_num_participants = 0;
        cfg->energy_min = 0.0;

        return cfg;

    }

    void snk_categories_cfg_destroy(snk_categories_cfg * snk_categories_config) {

        if (snk_categories_config->format != NULL) {
            format_destroy(snk_categories_config->format);
        }
        if (snk_categories_config->interface != NULL) {
            interface_destroy(snk_categories_config->interface);
        }

        free((void *) snk_categories_config);

    }
