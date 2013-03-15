/*=============================== String Streams ==============================

  PURPOSE - string streams allow the functionality of cin and cout but instead
            of working with the console,  allows work with C++ strings.
            This is a very simple and powerful way to create and extract text
            and other data types such as numbers.
            
     NOTE - When extracting text and converting to numbers and strings a 
            white space is the default separator.
          - try setting portb to 192 then running this program. 
*/
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>

using namespace std;

stringstream  stst;
string        strg ;
int           bit = 5 ;
int           portb_read ;

int cpp_do_ousb_command(string  *strg) //===========
{ FILE *fpipe ;
  if ( !(fpipe = (FILE*)popen(strg->c_str(),"r")))
   { cout << "pipe error" << endl ;
     exit(0) ;
   }
  char line[100] ;
  fgets( line, sizeof line, fpipe) ;
  pclose(fpipe) ;
  *strg = line ;        // caller can see returned text in strg.
  return( atoi(line)) ; // return int version of string.
}


int main(int argc, char *argv[]) //===============
{//--- read portb.
   strg = "ousb -r io portb\n" ;    // create command.
   cpp_do_ousb_command( &strg) ;    // execute command.
   stst.str( strg) ;                // get returned string str into stst.
   stst >> portb_read ;             // extract integer.
   cout << "   portb read was " << portb_read  << endl ; // tell screen.
   
 //--- set bit port b,  assume read value in variable portb_read.
   unsigned char mask = 1 << bit ;  // form OR mask.
   portb_read |= mask ;             // bitwise OR to set bit.
   stst.str("") ;                   // clear string.
   stst << "ousb io portb " << portb_read << endl ; // create command
   strg = stst.str() ;              // get command into strg
   cpp_do_ousb_command( &strg) ;    // execute command.
   cout << "   After bit set portb was " << portb_read << endl ;

 //--- clear next bit, assume previous portb held in variable portb.
   mask = ~(1 << ++bit) ;           // create AND mask.
   portb_read &= mask ;             // clear bit in variable.
   stst.str("") ;                   // clear string.
   stst << "ousb io portb " << portb_read << endl ; // create command
   strg = stst.str() ;              // get command into strg.
   cpp_do_ousb_command( &strg) ;    // execute command.
   cout << "   After bit clear portb was " << portb_read << endl ;
   

   return(0) ;
}
 
