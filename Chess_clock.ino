/* Chess clock
ESP 32 S2 mini - Sewerman_cz
--------------
pinout
EN    1   |   | 40  39
3     2   |   | 38  37
5     4   |   | 36  35
7     6   |   | 34  33
9     8   |   | 21  18
11    10  |   | 17  16    
12    13  |   | GND GND
3,3V  14  |   | 12  VBUS
Reset      |  | 0 
          USB C


This project use displays with TM1613 drivers
---------------------------------------------
Segments
   -      A
 |   |  F   B
   -      G
 |   |  E   C
   -  .   D   DP
The main functions include:

setSegments() – Set the raw value of the segments of each digit
showNumberDec() – Display a decimal number
showNumberDecEx() – Display a decimal number with decimal points or colon
setBrightness() – Set the brightness of the display
clear() – Clear the display


*/

// Libraries
#include <Arduino.h>
#include <TM1637Display.h> // For displays
#include <ButtonDebounce.h> // For buttons


// Definition
// First display the connections pins
#define CLK_1 8
#define DIO_1 9
// Second display the connections pins
#define CLK_2 6
#define DIO_2 7
//Buttons
ButtonDebounce button_1(4, 50); // Button on pin 4
ButtonDebounce button_2(5, 50); // Button on pin 5

//Initialization
long start_time = 5*60 ; //Starting time 5 minute
int set_time = 5; // Time for setting timer
long set_timer = 15; // Timer for setting
long player_1_timer = start_time;
int player_1_time;
long player_2_timer = start_time;
int player_2_time;
int player = 0; // 0 = set, 1 = player_1, 2 = player_2, 10 = befor start
int dots = 0; //variable for displaying colon
int prev_time=0;
uint8_t vypis[] = { 0, 0, 0, 0 };


// an array that sets individual segments per digit to display the word "set"
const uint8_t set[] = {
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,  // S
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,          // E
  SEG_D | SEG_E | SEG_F | SEG_G ,  // t

};

// Create display object of type TM1637Display:
TM1637Display display_1(CLK_1, DIO_1);
TM1637Display display_2(CLK_2, DIO_2);

//Functions
// Function for displaying numbers
void show_time(int x, long time){

  vypis[0] = display_1.encodeDigit((time/60)/10);
  vypis[1] = display_1.encodeDigit((time/60)%10);
  vypis[2] = display_1.encodeDigit((time%60)/10);
  vypis[3] = display_1.encodeDigit((time%60)%10);

  //displaying colons
  if (dots == 1){
    vypis[1] = vypis[1]+128;
  }

  if (x==1)
{
  // information on the display
  display_1.setSegments(vypis);
} else if (x==2){
  // information on the display
  display_2.setSegments(vypis);
}

  return;
}

void setup() {
  // brightness adjustment in the range 0-7
  display_1.setBrightness(5);  
  display_2.setBrightness(5);
  display_1.clear();
  display_2.clear();

}

void loop()
{
  //getting time from start
  long time = millis()/1000;
  
  // Updating state of  the buttons
  button_1.update();
  button_2.update();

  // displaying colon every seccond
  if (prev_time < time) {
    prev_time = time + 1;
    if (dots == 0){
      dots = 1;
    } else {
      dots = 0;
    }
  } 

  // Reset program
  if ((button_1.state() == 0) && (button_2.state() == 0)){
    set_timer = set_time + time;
    player = 0;
    display_1.setBrightness(5);  
    display_2.setBrightness(5);
    display_1.clear();
    display_2.clear();
  }


  switch (player){
    case 0: // Setting playing time
      display_1.setSegments(set,3,1);
      if (button_1.state() == 0) {
        start_time += 60;
        while (button_1.state() == 0) {
          button_1.update();
        }
        set_timer = set_time + time;
      }
      if (button_2.state() == 0) {
        if (start_time >=60){
          start_time -= 60;
          while (button_2.state() == 0) {
            button_2.update();
          }
          set_timer = set_time + time;
        }
      }
      show_time(2,start_time);
      if (set_timer < time){
        player = 10;
      }
      break;


    case 1: // Player 1 play
      if (player_1_timer - (time - player_1_time) <=0){
        display_1.setBrightness(0);  
        display_2.setBrightness(7);
        player = 11;
      } else {    
        display_1.setBrightness(7);  
        display_2.setBrightness(0);
      }
      show_time(1,(player_1_timer - (time - player_1_time)));
      show_time(2, player_2_timer);




      if (button_1.state() == 0) {
       player = 2;
       player_1_timer = player_1_timer - (time - player_1_time);
       player_2_time = time;

      }
      break;


    case 2:  //Player 2 play
      if (player_2_timer - (time - player_2_time) <=0){
        display_1.setBrightness(7);  
        display_2.setBrightness(0);
        player = 12;
      } else {
        display_1.setBrightness(0);  
        display_2.setBrightness(7);
      }
      show_time(1, player_1_timer);
      show_time(2,(player_2_timer - (time - player_2_time)));
      


      if (button_2.state() == 0) {
       player = 1;
       player_2_timer = player_2_timer - (time - player_2_time);
       player_1_time = time;

      }
      
      break;

    case 10: //time befor start
      display_1.setBrightness(0);  
      display_2.setBrightness(0);
      show_time(1,start_time);
      show_time(2,start_time);
      player_1_timer = start_time;
      player_2_timer = start_time;

      if (button_1.state() == 0) {
        while (button_1.state() == 0) {
          button_1.update();
        }
       player = 1;
       player_1_time = time;
      }
      if (button_2.state() == 0) {
        while (button_2.state() == 0) {
          button_2.update();
        }
       player = 2;
       player_2_time = time;
      }
      break;
   
  }

}
