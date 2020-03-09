//#include <string.h>
#include <matrix_hal/everloop.h>
#include <matrix_hal/everloop_image.h>
#include <matrix_hal/matrixio_bus.h>
#include <module/update_led.h>

extern "C" void update_led(char action, int led_array[NUM_LEDS][NUM_COLOURS] )
{
 
namespace hal = matrix_hal;

static hal::MatrixIOBus bus;
static hal::EverloopImage image1d(18);
static hal::Everloop everloop;

    if (action == INITIALIZE) {

        if (!bus.Init()) printf ("Error initialising LEDs");
        // this line just resizes the EverloopImage object to the number of LEDs on the board 

        everloop.Setup(&bus);

        for (int i=0;i<NUM_LEDS;i++) {

             image1d.leds[i].red = 0;
             image1d.leds[i].green = 0;
             image1d.leds[i].blue= 0;
             image1d.leds[i].white = 0;
        } 

    }
    else if (action == UPDATE) {   

             for (int i=0;i<NUM_LEDS;i++) {
                  image1d.leds[i].red = led_array[i][0];
                  image1d.leds[i].green = led_array[i][1];
                  image1d.leds[i].blue= led_array[i][2];
                  image1d.leds[i].white= led_array[i][3];
             }

    }

everloop.Write(&image1d);

}
