// Header file for shell commands
// Author: Travis Dowd
// Date: 9-20-19
#include <unistd.h> // for sleep()

// Cat out file
const char *Type( const char *filename ) {
  static int c;
  FILE *f = fopen( filename, "r" );
  if( f ) {
    while( (c = getc(f)) != EOF)
	putchar( c );
      fclose( f );
  } else {
    printf( "Can't open file.\n" );
  } return 0;
}
// Cat out file in color (color.h)
const char *ColorType( const char *filename, const char *color ) {
  FILE *f = fopen( filename, "r" );
  if( f ) {
    printf( color );
    Type( filename );
  } return 0;
}
// Append text to file
const char *Append( const char *filename, char *str ) {
  FILE *f = fopen( filename, "a" );
  if( f ) {
      fprintf( f, str );
      fclose( f );
  } else {
    printf("Can't append to file.\n");
  } return 0;
}

// Copy file
const char *Cp( const char *source, const char *target ) {
  static char ch;
  FILE *file1 = fopen( source, "r" );
  FILE *file2 = fopen( target, "w" );
  if( file1 ) {
      while( (ch = fgetc(file1)) != EOF ) {
	  fputc( ch, file2 );
	}
      fclose(file1);
      fclose(file2);
  } return 0;
}

// Move file
const char *Move( const char *source, const char *target ) {
  Cp( source, target );
  remove( source ); // Removes orignal file, function in C stdlib
  return 0;
}

// Delete specific line in file
const char *Del_line( const char *source, const char *target ) {
  static char ch;
  static int line, i = 1;
  Type( source );
  printf( "Enter line number to delete: \n" );
  scanf( "%d", &line );
  FILE *file1, *file2; 
  file1 = fopen( source, "r" );
  file2 = fopen( target, "w" );
  while ( ch != EOF ) {
      ch = getc( file1 );
      if ( ch == '\n' ) {
	  i++;
	  if( i != line ) {
	      putc( ch, file2 );
	    }
	}
    }
  // Bug where ascii 152 is being paced at end of file, can't fix :(
  fclose( file1 );
  fclose( file2 );
  return 0;
}

//Clears screen, but leaves prompt at bottom
const char *Cls() {
  printf( "\033[2J\033[H" );
  return 0;
}

const char *Echo( const char *str ) {
  printf( "%s\n", str );
  return 0;
}

