#define INITIALIZE  'i'
#define UPDATE 'u'
#define NUM_LEDS 18
#define NUM_COLOURS 4
#define MAX_PARTICIPANTS 6
#define ANGLE_SPREAD 35
#define MAX_BRIGHT 120
#define MED_BRIGHT 60
#define MIN_BRIGHT 30
#define RED {MAX_BRIGHT,0,0,0}
#define GREEN {0,MAX_BRIGHT,0,0}
#define BLUE {0,0,MED_BRIGHT,0}
#define YELLOW {MED_BRIGHT,MED_BRIGHT,0,0}
#define CYAN {0,MED_BRIGHT,MED_BRIGHT,0}
#define PURPLE {MED_BRIGHT,0,MED_BRIGHT,0}
#define PROVISIONAL 'p'
#define CONFIRMED 'c'




#ifdef __cplusplus
extern "C" {
#endif

void update_led (char, int [NUM_LEDS][NUM_COLOURS] );

#ifdef __cplusplus
}
#endif
