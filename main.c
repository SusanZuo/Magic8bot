/*

 * 3pi-messages - This code wil

 * 

 *

 * http://www.pololu.com/docs/0J21

 * http://www.pololu.com

 * http://forum.pololu.com

 *

 */




// The 3pi include file must be at the beginning of any program that

// uses the Pololu AVR library and 3pi.

#include <pololu/3pi.h>

#include <pololu/orangutan.h> // for servo




// This include file allows data to be stored in program space.  The

// ATmega168 has 16k of program space compared to 1k of RAM, so large

// pieces of static data should be stored in program space.

#include <avr/pgmspace.h>




// Introductory messages.  The "PROGMEM" identifier causes the data to

// go into program space.

const char welcome_line1[] PROGMEM = "Magic 8 ";

const char welcome_line2[] PROGMEM = "Bot";

const char demo_name_line1[] PROGMEM = "Jaime";

const char demo_name_line2[] PROGMEM = "Susan";




// A couple of simple tunes, stored in program space.

const char welcome[] PROGMEM = ">g32>>c32";

const char go[] PROGMEM = "L16 cdegreg4";




// Data for generating the characters used in load_custom_characters

// and display_readings.  By reading levels[] starting at various

// offsets, we can generate all of the 7 extra characters needed for a

// bargraph.  This is also stored in program space.

const char levels[] PROGMEM = {

	0b00000,

	0b00000,

	0b00000,

	0b00000,

	0b00000,

	0b00000,

	0b00000,

	0b11111,

	0b11111,

	0b11111,

	0b11111,

	0b11111,

	0b11111,

	0b11111

};




// This function loads custom characters into the LCD.  Up to 8

// characters can be loaded; we use them for 7 levels of a bar graph.

void load_custom_characters()

{

	lcd_load_custom_character(levels+0,0); // no offset, e.g. one bar

	lcd_load_custom_character(levels+1,1); // two bars

	lcd_load_custom_character(levels+2,2); // etc...

	lcd_load_custom_character(levels+3,3);

	lcd_load_custom_character(levels+4,4);

	lcd_load_custom_character(levels+5,5);

	lcd_load_custom_character(levels+6,6);

	clear(); // the LCD must be cleared for the characters to take effect

}




// This function displays the sensor readings using a bar graph.

void display_readings(const unsigned int *calibrated_values)

{

	unsigned char i;




	for(i=0;i<5;i++) {

		// Initialize the array of characters that we will use for the

		// graph.  Using the space, an extra copy of the one-bar

		// character, and character 255 (a full black box), we get 10

		// characters in the array.

		const char display_characters[10] = {' ',0,0,1,2,3,4,5,6,255};




		// The variable c will have values from 0 to 9, since

		// calibrated values are in the range of 0 to 1000, and

		// 1000/101 is 9 with integer math.

		char c = display_characters[calibrated_values[i]/101];




		// Display the bar graph character.

		print_character(c);

	}

}




// Initializes the 3pi, displays a welcome message, calibrates, and

// plays the initial music.

void initialize()

{

	//unsigned int counter; // used as a simple timer

	//unsigned int sensors[5]; // an array to hold sensor values




	// This must be called at the beginning of 3pi code, to set up the

	// sensors.  We use a value of 2000 for the timeout, which

	// corresponds to 2000*0.4 us = 0.8 ms on our 20 MHz processor.

	pololu_3pi_init(2000);

	//load_custom_characters(); // load the custom characters

	

	// Play welcome music and display a message

	print_from_program_space(welcome_line1);

	lcd_goto_xy(0,1);

	print_from_program_space(welcome_line2);

	//play_from_program_space(welcome);

	delay_ms(1000);




	clear();

	print_from_program_space(demo_name_line1);

	lcd_goto_xy(0,1);

	print_from_program_space(demo_name_line2);

	delay_ms(1000);




	// Display battery voltage and wait for button press

	while(!button_is_pressed(BUTTON_B))

	{

		int bat = read_battery_millivolts();




		clear();

		print_long(bat);

		print("mV");

		lcd_goto_xy(0,1);

		print("Press B");




		delay_ms(100);

	}




	// Always wait for the button to be released so that 3pi doesn't

	// start moving until your hand is away from it.

	wait_for_button_release(BUTTON_B);

	delay_ms(1000);

	clear();

}




void drop_pen(unsigned char servoNum){

	set_servo_speed_b(servoNum, 300);

	set_servo_target_b(servoNum, 600);	// start servo 0 moving

	delay_ms(1000);

	

}




void lift_pen(unsigned char servoNum){	

	set_servo_speed_b(servoNum, 100);	//no speed limit = 0

	set_servo_target_b(servoNum, 400);

	delay_ms(1000);

}




void as_if(){

	delay_ms(1000);

	//start 2/3 oval

	drop_pen(0);

	//drop

	set_motors(-20,20);

	delay_ms(1500);

	set_motors(-20,15);

	delay_ms(1500);

	set_motors(-20,20);

	delay_ms(1500);

	

	//last stroke

	set_motors(-10,20);

	delay_ms(1000);

	set_motors(-20,-20);

	delay_ms(1500);

	set_motors(20,20);

	delay_ms(2000);

	

	//moving to next cell

	//lift

	lift_pen(0);

	set_motors(0,20);

	delay_ms(1500);




	//"s"

	//entering cell

	set_motors(20,20);

	delay_ms(5000);

	set_motors(0,-20);

	delay_ms(2000);

	set_motors(-20,-20);

	delay_ms(2000);

	

	delay_ms(5000);

	//first oval

	drop_pen(0);

	set_motors(-20,20);

	delay_ms(1500);

	set_motors(0,20);

	delay_ms(2100);

	set_motors(-20,20);

	delay_ms(700);

	

	//second oval

	set_motors(-20,-25);

	delay_ms(1500);

	set_motors(-20,-40);

	delay_ms(1700);

	set_motors(-20,-25);

	delay_ms(2800);

	

	//move to next cell

	//lift

	lift_pen(0);

	set_motors(0,20);

	delay_ms(1500);


	//"i"

	//entering cell

	set_motors(20,20);

	delay_ms(5000);

	set_motors(0,-20);

	delay_ms(1500);

	

	// drop

	drop_pen(0);

	set_motors(-20,-20);

	delay_ms(1500);

	//lift

	lift_pen(0);

	set_motors(-20,-20);

	delay_ms(200);

	//drop

	drop_pen(0);

	set_motors(-20,20);

	delay_ms(300);

	set_motors(20,20);

	delay_ms(2000);

	

	//lift

	lift_pen(0);

	set_motors(0,20);

	delay_ms(1500);




	//"f"

	//entering cell

	set_motors(20,20);

	delay_ms(5000);

	set_motors(0,-20);

	delay_ms(1500);

	

	// drop

	drop_pen(0);

	set_motors(-20,-20);

	delay_ms(2000);

	set_motors(-20,-30);

	delay_ms(2650);

	//lift

	lift_pen(0);

	set_motors(0,-40);

	delay_ms(2300);

	

	set_motors(20,20);

	delay_ms(2000);

	set_motors(0,20);

	delay_ms(1650);

	set_motors(-20,-20);

	delay_ms(1500);

	set_motors(0,0);

	delay_ms(1000);

	//drop

	drop_pen(0);

	set_motors(-20,-20);

	delay_ms(2000);

	//lift

	lift_pen(0);

	set_motors(0,-20);

	delay_ms(1500);

	set_motors(-20,0);

	delay_ms(2000);

	set_motors(20,20);

	delay_ms(2000);

}

void duh(){
	//"d"
	//
	//start 2/3 oval
	//drop
	set_motors(0,-30);
	delay_ms(1100);
	drop_pen(0);
	set_motors(-25,25);
	delay_ms(1100);
	set_motors(-25,20);
	delay_ms(1100);
	set_motors(-25,25);
	delay_ms(900);
	
	//last stroke
	set_motors(-10,30);
	delay_ms(500);
	set_motors(20,20);
	delay_ms(500);
	set_motors(-25,-20);
	delay_ms(3000);
	set_motors(0,0);
	
	//moving to next cell
	//lift
	lift_pen(0);
	delay_ms(500);
	set_motors(-16,-34);
	delay_ms(2700);

	//"u"
	//drop
	
	set_motors(-25,-23);
	delay_ms(1000);
	set_motors(0,0);
	delay_ms(1000);
	drop_pen(0);
	set_motors(-25,-23);
	delay_ms(700);
	set_motors(-25,25);
	delay_ms(2000);
	set_motors(-26,-22);
	delay_ms(1000);
	set_motors(0,0);
	lift_pen(0);
	
	//"h"
	delay_ms(500);
	
	
	set_motors(-20,-27);
	delay_ms(1300);
	//set_motors(-20,-45);
	//delay_ms(2000);
	set_motors(-5,-30);
	delay_ms(1600);
	set_motors(0,0);
	delay_ms(500);
	//drop
	drop_pen(0);
	
	set_motors(-23,-20);
	delay_ms(3500);
	set_motors(24,20);
	delay_ms(1500);
	set_motors(25,-20);
	delay_ms(2500);
	set_motors(30,20);
	delay_ms(800);
	set_motors(0,0);
	delay_ms(500);
	lift_pen(0);
	set_motors(30,15);
	delay_ms(1500);
	set_motors(0,0);
	//lift
	
}

void no(){
	
	//drop
	drop_pen(0);
	set_motors(-23,-20);
	delay_ms(2000);
	set_motors(24,20);
	delay_ms(1500);
	set_motors(25,-20);
	delay_ms(2500);
	set_motors(30,20);
	delay_ms(800);
	//lift
	lift_pen(0);
	set_motors(0,0);
	delay_ms(500);
	set_motors(18,40);
	delay_ms(2100);
	set_motors(30,35);
	delay_ms(1400);
	set_motors(0,0);
	delay_ms(500);

	//"o"
	//drop
	drop_pen(0);
	set_motors(46,-46);
	delay_ms(1500);
	set_motors(0,0);
	lift_pen(0);
	
	set_motors(30,15);
	delay_ms(1500);
	set_motors(0,0);
}



// This is the main function, where the code starts.  All C programs

// must have a main() function defined somewhere.

int main() {


	int count = 0;
	int last = 0;

	// set up the 3pi

	initialize();




	const unsigned char servoPinsB[] = {IO_D0};

	servos_start_extended((unsigned char[]){}, 0, servoPinsB, sizeof(servoPinsB));

	set_servo_speed_b(0, 0);	// no speed limit (move as fast as possible)

	set_servo_target_b(0, 400);




	delay_us(1000);

	print("DROP");
	
	set_analog_mode(MODE_8_BIT);
	delay_ms(1000);
	start_analog_conversion(TRIMPOT);
	
	while(1){
		start_analog_conversion(TRIMPOT);
		if (!analog_is_converting()){
			if (analog_conversion_result() > 128){
				red_led(1);
				if (count == 0) count++;
				delay_ms(1000);
				red_led(0);
				delay_ms(1000);
			} else {
				if (count == 1){
					count--;
					if (last ==0){
						last = 1;
						no();
					}else if(last == 1){
						last = 2;
						no();
					}else if(last == 2){
						last = 3;
						no();
					}else if(last == 3){
						last = 0;
						duh();
					}
				}
				green_led(1);
				delay_ms(1000);
				green_led(0);
				delay_ms(1000);
				
			}
		}
	}
	
}


// Local Variables: **

// mode: C **

// c-basic-offset: 4 **

// tab-width: 4 **

// indent-tabs-mode: t **

// end: **