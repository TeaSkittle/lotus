#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"  // ANSI color codes
#include "tul.h"    // Shell style commands
#include "game.h"   // Core gameplay

int main( void ) {
  Cls(); 
  Boot(); //Comment Boot() out to speed up testing, boot works already 100%
  Cls();
  ColorType( "open.txt", MAGENTA );
  printf( WHITE "type \"help\" to see commands\n\n" );
  while( 1 ) {
    printf( GREEN "lotusOS~> " WHITE);
    Input( a );
    Parse();
  } return 0;
}
