/*==================  UDP Alarm Lab Exam  =====================================

PURPOSE     This file is a proforma for the UDP Alarm lab exam.  It defines
            the assignment - there is no other documentation.

BACKGROUND  Networked devices are extensively used in engineering systems.
            The following system represents a 3 stage steam turbine and
            generator.  Each of the 4 items has its own temperature sensor
            that is connected to a private IP network.

                            SYSTEM BLOCK DIAGRAM

                   .     .     .
                   |\    |\    |\         .-----------.
                   | \   | \   | \    .---'           '---.
            .------'  \--'  \--'  \---'                   |--.
            '------.  /--   /--.  /---.                   |--'
                   | /   | /   | /    '---.           .---'
                   |'    |'    |'         '-----------'
                   t1    t2    t3             g1
                   .     .     .              .
                   .---------------------------  <-private LAN
                        |
                  .-----+------------.    .--------------------.
                  | your embedded PC +====+ Open-USB-IO board  |
                  '-----+------------'    |   drives displays. |
                        |                 '--------------------'
                  .-----+-----------------.
                  | control room computer |
                  '-----------------------'


            Each sensor sends out a packet approximately every 10 seconds
            that contains the temperature in degrees centigrade as a text
            string.  This packet is sent to your embedded PC using UDP
            where a program you write takes action.

            Your program runs on this embedded PC connected to an Open-USB-IO
            board.  If any temperature sensor goes over limit then the
            appropriate LED is turned on and a UDP alarm packet is sent to
            a control room computer.


SPECIFIC REQUIREMENTS 

         * You must use the Eclipse IDE to develop and run all programs.
	   Normally you will develop and submit with debugging turned off.
	   In the Project Manager window right click on the top (head) of
	   the project and select Build Configurations->Set Active and 
	   then select Release. If you need to debug then use the same
	   process but choose Debug.
	   >>> Your submitted binary code MUST be release mode.

         * Your code will run on one PC, the real sensors and control room
           computer will be simulated using the udp_talker and udp_listener
           projects already in Eclipse.

                                SOFTWARE BLOCK DIAGRAM

                                    .-------------.-------.
                                    | Open-USB-IO >  LEDs |
                                    '------+------'-------'
                                           |
                                           ^
                                           |
             .----------------.     .------+--------.     .---------------.
             |                |     |               |     |               |
             | UDP talker     | UDP | Code written  | UDP | UDP listener  |
             | program sends  +->---+ for this lab  +->---+ display the   |
             | packets you    |     |               |     | UDP you       |
             | define         |     |               |     | generate.     |
             |                |     '---------------'     |               |
             '----------------'                           '---------------'
   TYPICAL IP:Port                     -->-127.0.0.1:55555   -->-127.0.0.2:44444


         * Your program must handle one sensor ( If more than one sensor
           was to be handled then your program would be started multiple
           times with different command line parameters.)

         * The program will be started from the command line as follows-
           ./your_code own_ip own_port control_name  control_port temp_limit ousb_LED
           where
                own_ip   = IP address of this computer.
                own_port = port number to listen on.
                   note the temperature sensor is setup to send to the above.
                control_name = IP of control room computer.
                control_port = port on control room computer.
                temp_limit = degrees C that temperature must not exceed.
                             If temperature goes above this then declare an alarm.
                ousb_LED   = LED number 0-7 to control on alarm panel.

           Example ./your_code 127.0.0.1 55555 127.0.0.2 44444 120 0
           (If you are using Eclipse do not put ./your_code in the parameter list.)

         * The parameters can be assumed to all exist and have no errors.
           You do not need to check for errors.

         * On startup your program must turn off the Open-USB-IO LED
           for this sensor.
           Multiple copies of your code could be running and each can control
           one LED on the Open-USB-IO board.  Each active program must not
           interfere with the other LEDs.
           After adjusting the LEDs the program can start listening for packets.

         * A sensor will send a data packet formatted as follows-
             <2 letters name><one space><3 digits of temperature as deg. C>
           Example: the t3 sensor packet reading 10 degC would be "t3 010".

         * When the packet is received the program must print to the command
           line the word RX then a line feed (note the case).
           It must then compare the temperature to the limit set on program start up.

           If over limit then the LED  must be turned on, if under or on limit
           the LED must be turned off.  No other LEDS can be altered.

           If over limit your program must then print to the command line 
           the word OVER then a line feed (again note the case).

           If the temperature is over limit then a UDP packet must be sent to
           the control room computer.  The format is-
             <TEMP_ALARM><one space><2 letter sensor name>
           Continuing the example above "TEMP_ALARM t3"

         * If your program is started with no parameters then it must self
           identify as shown at the start of the code below and then terminate.
           You must change the id to your own id.

         * Your code should not loop forever (as the real code would).  It should
           listen for a packet,  act on the packet,  and then terminate.

         * In the lab exam submit the executable code,  not the source code.
           Copy the executable into /home/user/Documents and rename it-
             lab1_1234567
           where you should replace 1234567 with your own student number.
           Next hit the submit button on the desktop and answer thew questions.




SPECIFIC HINTS

         * Remember to cut and paste the auto-identification lines below into
           your new program,  which you will likely create by copying the
           existing Eclipse project udp_listener then altering the code.

         * The existing Eclipse projects udp_talker and udp_listener can be
           modified to help test your program.
           To start off copy udp_listener to your own project s1234567_lab1
           and rename the listener_main.cpp file to alarm_main.cpp.  To copy
             - In Eclipse ensure you have just one project open in the
               Project Explorer.
             - Right click on the project head and select copy, right
               click again and select paste,  supply a meaningful name.
             - Close the old working project, and start working on the
               new one.

         * You must use the Eclipse IDE to develop and run all programs.
           Most likely you will have three projects active at the same time-
              - your program to implement the above functionality.
              - a udp_talker for sending UDP packets to your code.
              - a udp_listener to listen to the output of your code.

         * Review bitwise operations especially using AND, OR and invert 
           to read the LEDS, change one, and write back to the hardware
           such that only the one LED is altered.
           Tutorials will help you on this topic.

         * Most of the code you need is on the live-DVD,  you need to know
           where the examples are and cut & paste into your code.

             /home/play/public_examples/sockets for UDP examples and
             especially the UDP_class* files as a start for your own code
             and to provide packet senders and receivers to test your code.

             /home/play/public_examples/cpp_review for command line IO.

             /home/user/projects/open-usb-io_command_line/access...
               for functions to send commands to Open-USB-IO.
             This can also be found in the Open-USB-IO reference on the 
             desktop.  Note the -r option which means the command returns
             just a number without all the explanatory text.

           The lectures will walk through some of this code.

         * Use C++ strings to simplify text usage,  use atoi() to convert
           strings to numbers.  Note how strings are used in adc_read.cpp
           when controlling Open-USB-IO.
           Review C++ member functions such as substr(), and operators
           such as +.

         * Modify the udp_talker and udp_listener projects to send and
           receive the packets you need to test your code.
           Suggestion:
               udp_talker should send to 127.0.0.1:55555,
               start your program to listen on this IP and port.
               UDP_class_usage_listener.cpp should listen on 
               port 127.0.0.2:44444, your program should send to this.

         * Test your code in Eclipse by-
              - Ctrl-B to build all.
              - Click on head of modified listener, from menu select run.
              - Click on head of your alarm code, from menu select run.
              - Click on head of modified talker code and select run.
              - Check result from various terminals.

         * If you start a listener multiple times then of course the binding
           to the port will fail because the first instantiation gets the port
           and later ones fail.  Click on the console tab in eclipse,  click 
           on the double cross symbol to kill all running programs.

         * Some students have reported the live-DVD crashes when compiling
           with debugging on. To move between the debug and release modes
           select the Eclipse menu option Project->Make Target, Build then
           double click or Release or Debug.
           You may need to add a space to the .cpp file and save to force
           the build to recompile.



POSSIBLE EXAM QUESTIONS

         * Given that the designers could have chosen TCP or UDP is UDP
           a good thing to use?  If not why not.

         * If a UDP listener is opened with a specific IP address will
           it receive from other IP addresses?  If not how can a listener
           be started so it listens to any IP on a host?

         * What type of errors can occur when setting up a socket?



GENERAL INFORMATION

  * Practice at home:  you will need to practice this lab at home 
    quite a lot to get it right.
    If you know where to cut and paste from then it is not that bad.

  * It's all so complex, where do I start?
    This is a major part of the project,  working out where to start.
    You will have to start on bits you can understand, then as
    you understand more move onto other bits.
    Make good use of the lectures, labs and tutorials.

  * To help debugging create a macro called TEST which can be blank for
    testing-
           #define TEST
    or as below for delivery (the next statement after a TEST eg cout
    will not be executed)
           #define TEST if (0)
    This will allow a single change to move you between testing and delivery mode.
       TEST  cout << "message << endl ; // one line of code.
       TEST { ; ; ; ; } // several lines of code.

  * Your code must output EXACTLY what is asked for in the specification
    and nothing more.  If your code should output "RX" and your answer is
    "Received RX" then you will be marked as wrong.

  * A plagiarism detector will be used on all student code so don't
    bother copying.
    The exam will focus on project work so copying is a stupid idea.
    For a variety of reasons marking may have a competitive element
    ( listen in the lectures about this).  If you give good code away
    then your final mark being lower.

  * If time permits code will be inspected for readability so code 
    with good coding style from the start of development.

  * In most cases there is a form of negative marking.  If there are
    N possible answers the marking is usually +N for right and -1 for 
    wrong. This makes it pointless to always return one answer in 
    the hope of getting some marks.
*/

#define TEST
//#define TEST if (0)

#include <iostream>
#include <cstdlib>
#include <string>
#include "UDP_class.h"

using namespace std;



//====== MAIN ==========================================================

int main(int argc, char *argv[])
{//--- When no command line parameters MUST print id string in CSV format.
	   if (argc == 1)  // no parameters.
	     { cout << "s3314308, s3314308@student.rmit.edu.au, Troy Dack" << endl ;
	       return(0) ;
	     }

	   if (argc != 7)
	   {
		   cout << "Not enough parameters" << endl;
		   return(0);
	   }

	   // Have enough parameters, get them all
	   /*
	                own_ip   = IP address of this computer.
	                own_port = port number to listen on.
	                   note the temperature sensor is setup to send to the above.
	                control_name = IP of control room computer.
	                control_port = port on control room computer.
	                temp_limit = degrees C that temperature must not exceed.
	                             If temperature goes above this then declare an alarm.
	                ousb_LED   = LED number 0-7 to control on alarm panel.

	           Example ./your_code 127.0.0.1 55555 127.0.0.2 44444 120 0
	    *
	    */
	   string own_ip = argv[1];
	   int own_port = atoi(argv[2]);
	   string control_ip = argv[3];
	   int control_port = atoi(argv[4]);
	   int temp_limit = atoi(argv[5]);
	   int ousb_LED = atoi(argv[6]);

	   // Turn off ousb_LED

	   Tudp_handler rx_udp( own_ip, own_port) ;
	   Tudp_handler tx_udp( control_ip, control_port) ;

	   if (rx_udp.wait_receive_udp () )
	     {//--- got an error
	        cout << "   Send error: " << rx_udp.error_message << endl << endl ;
	        return(-1) ;
	     }

	   string rxd = rx_udp.rcv_str;
	   string sensor = rxd.substr(0,2);
	   int temp = atoi(rxd.substr(3,3).c_str());
	   cout << "RX" << endl;

	   if (temp > temp_limit)
	   {
		   cout << "OVER" << endl;
		   // Turn on ousb_LED

		   // send UDP packet: "TEMP_ALARM " << sensor
		   tx_udp.send_str = "TEMP_ALARM " + sensor;
		   if ( tx_udp.send_udp() )
		      {//--- got an error
		         cout << "   Send error: " << tx_udp.error_message << endl ;
		         return(-1) ;
		      }
	   }
	   else if (temp <= temp_limit)
	   {
		   // Turn off ousb_LED
	   }

	   return(0);
}


