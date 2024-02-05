/********************************************
*
*  Name:
*  Email:
*  Section:
*  Assignment: Lab 4 - Up/Down counter on LCD display
*
********************************************/

#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

enum states { UP, DOWN, PAUSE };

int main(void) {

    // Setup DDR and PORT bits for the 3 input buttons as necessary
    PINC |= (1 << PC2) | (1 << PC4);
    PINB |= (1 << PB3);

    // Initialize the LCD
    lcd_init();

    // Use a state machine approach to organize your code
    //   - Declare and initialize a variable to track what state you
    //     are in by assigning the values UP, DOWN or PAUSE to that variable.
    char my_counter_state = UP; char cnt = 0; int delayCnt = 0;
    
    while (1) {               // Loop forever
        // Use "if" statements to read the buttons and determine which
        // state you are in
        if ((PINC & (1 << PC2)) == 0) { // Up is pressed
            my_counter_state = UP;
        }
        else if ((PINC & (1 << PC4)) == 0) { // Down is pressed
            my_counter_state = DOWN;
        }
        else if ((PINB & (1 << PB3)) == 0) { // Pause is pressed
            my_counter_state = PAUSE;
        }
        if (delayCnt == 10){
            // Based on the current state, determine the new count value
            if(my_counter_state == UP) {
                cnt++;
                if(my_counter_state == UP && cnt == 10) { // Reached end of UP iteration
                    cnt = 0;
                }
                lcd_writecommand(2);
                lcd_writedata(cnt + '0');
            } else if(my_counter_state == DOWN) {
                cnt--;
                if(my_counter_state == DOWN && cnt == -1) { // Reached end of Down iteration
                cnt = 9;
                }
                lcd_writecommand(2);
                lcd_writedata(cnt + '0');
            }
            delayCnt = 0;
        }

	// Perform the output operations if necessary
        // lcd_writecommand(2);
        // lcd_writedata(cnt + '0');
        // Delay before we go to the next iteration of the loop
        _delay_ms(50);
        delayCnt++;
    }

    return 0;   /* never reached */
}