#include "Arduino.h"
#include "innerWdt.h"

/* Are you fed up to pay for hardware at an above-than-acceptable price 
 *  and only get a shitty documentation? 
 *  Me too, and I don't have high standards
*/

// WDT = Watch Dog Timer (that would kill them to write it down, am I right?)

  /* Enable the WDT. 
  * The wdt about every 1.4 seconds generates an interrupt, 
  * Two unserviced interrupts lead to a system reset(i.e. at the third match). 
  * The max feed time shoud be 2.8 seconds.
  * autoFeed = false: do not auto feed wdt.
  * autoFeed = true : it auto feed the wdt in every interrupt.
  */

#define SERIAL_BAUDRATE   115200
#define LOOP_DELAY_MS     2800
#define WDT_COUNT_MAX     3

bool autoFeed = false;

void setup() 
{

  Serial.begin(SERIAL_BAUDRATE);

  /* The next line makes sure the connection between 
   * the PC and the uController is established before 
   * blasting some text
  */
  while (!Serial){} 

  
  Serial.println("*******************************************");
  Serial.println("Start of the script");


  innerWdtEnable(autoFeed);
}

uint8_t feedCnt = 0; // Init 

void loop() {

  Serial.println("------------------------------------------");
  Serial.println("The ""loop"" is still running");
  
  if(autoFeed == false)
  {
    //feed the wdt if the counter is below the threshold
    if(feedCnt < WDT_COUNT_MAX)
    {
      feedInnerWdt();
      
      Serial.println("Incrementing the WDT counter...");
      feedCnt++;
      Serial.print(feedCnt);
      Serial.print('/');
      Serial.println(WDT_COUNT_MAX);
        
    }
    else
    {

      Serial.println("This time we don't call the function ""feedInnerWdt()"" ");
      
      Serial.println(); // I just add a blank line here for nicer console display
      Serial.print("Since the counter has reached the user-defined ");
      Serial.print("threshold (i.e. ");
      Serial.print(WDT_COUNT_MAX);
      Serial.println(")");
      Serial.println("The watch dog is going to trigger a reset just now...");
    }
  }

  delay(LOOP_DELAY_MS); // This line simulates the execution of some code
  
}

// END OF SCRIPT
