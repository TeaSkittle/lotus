#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"  // ANSI color codes
#include "tul.h"    // Shell style commands
#include "game.h"   // Core gameplay

int main( int argc, char *argv[] ) {
  // This is for testing, will remove when game is finished
  if(argc != 1){
    Cls(); 
    Boot();
    Cls();
  }
  Cls();
  ColorType( "open.txt", MAGENTA );
  printf( WHITE "type \"help\" to see commands\n\n" );
  while( 1 ) {
    printf( GREEN "lotusOS~> " WHITE);
    input( a );
    parse();
  } return 0;
}
