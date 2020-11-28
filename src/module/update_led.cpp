//#include <string.h>
#include <matrix_hal/everloop.h>
#include <matrix_hal/everloop_image.h>
#include <matrix_hal/matrixio_bus.h>
#include <sink/snk_categories.h>

extern "C" void update_led(char action, snk_categories_obj * obj )
{
 
namespace hal = matrix_hal;

static hal::MatrixIOBus bus;
static hal::EverloopImage image1d(obj->interface->num_leds);
static hal::Everloop everloop;

int red[6] = {200,100,100,0,0,0};
int green[6] = {0,100,0,100,200,0};
int blue[6] = {0,0,100,100,0,200};

    if (action == 'i') {

        if (!bus.Init()) printf ("Error initialising LEDs");
        // this line just resizes the EverloopImage object to the number of LEDs on the board 

        everloop.Setup(&bus);
        // lite up all lights to show all working and parameters are right
        for (int i=0;i<obj->interface->num_leds;i+=2) {

             image1d.leds[i].red = 0;
             image1d.leds[i].green = 0;
             image1d.leds[i].blue= 0;
             image1d.leds[i].white = 00;
        } 


    }
    else if (action == 'u') {   

//      switch everything off

        for (int i=0;i<obj->interface->num_leds;i++){
            image1d.leds[i].red = 0;
            image1d.leds[i].green = 0;
            image1d.leds[i].blue= 0;

        }

// now switch on the talkers

        for (int i=1;i<=obj->num_participants;i++){
            if (obj->participant_is_talking[i] == 0x01) {
                int iLed = obj->participant_angle[i] * obj->interface->num_leds / 360;
                image1d.leds[iLed].red = red[i];
                image1d.leds[iLed].green = green[i];
                image1d.leds[iLed].blue= blue[i];

            } 
        }


    }

everloop.Write(&image1d);

}
