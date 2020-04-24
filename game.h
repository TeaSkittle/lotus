// Core gameplay for LotusOS
#define MAX 1024                      // Size for input values
static char a[ MAX ], b[ MAX ];       // Input a and b
struct Commands;                      // Struct of shell commands for game
static int loc = 4;                   // Start player in Home directory
static const char Dir[ 10 ][ 50 ];    // Directory/File structure of PC's in game
static char *token;                   // Used in Input function, random variable name
static int current_pc = 0;            // Which PC player is connected to

struct Commands {                     // Commands
  const char *description;            // Description of commands
  const char *tag;                    // Name or tag of commands
};
struct Commands cmds[ 11 ];
struct Commands cmds[ 11 ] = {
  { "print working directory", "pwd" },
  { "pop diectory", "popd" },
  { "list", "ls" },
  { "help file", "help" },
  { "remove file", "rm" },
  { "show contents of file", "cat" },
  { "connect to another computer", "ssh" },
  { "clear screen", "clear" },
  { "disconnect from computer", "exit" },
  { "push diectory", "pushd" },
  { "print string to stdout", "echo" }
};

static const char Dir[ 10 ][ 50 ] = {  // File Structure
  "/",
  "/bin",
  "/sys",
  "/home",
  "/home/user",
  "/home/user/Documents",
};

int connect( const char *other_pc ) {   // Connect(ssh) to another PC
  if ( strcmp(other_pc, "127.0.0.1") == 0 ) {
      current_pc = 0;
      printf(" Welcome home.\n" );
      loc = 4;                          // Start player in same location for each new pc
    } else if ( strcmp(other_pc, "192.168.10.5") == 0 ) {
      current_pc = 1;
      printf( "Connecting...\n" );
      loc = 4;
    } else if ( strcmp(other_pc, "192.168.0.2") == 0 ) {
      current_pc = 2;
      printf( "Connecting...\n" );
      loc = 4;
    } return 0;
}

// Use Type from tul.h, but open from a subfoler.
// Story files are located in story folder
int Write( const char *dir, const char *name ) {
  static char subdir[ MAX ], file[ MAX ];
  strcpy( subdir, dir );
  strcpy( file, name );
  Type( strcat(subdir, file) );
  return 0;
}

// This is for 'ls' and shows certain files
// depending on location in pc, and what pc
int Files() {
  static const int *pc = &current_pc;
  static const int *dir = &loc;
  if ( *pc == 0 ) {
    if ( *dir == 4 ) {
	  printf("readme.txt");
    } else if ( *dir == 5 ) {
	  printf("empire.txt");
    } else if ( *pc == 1 ) {
      if ( *dir == 4 ) {
	printf("format.txt");  // Need to add new story file here
      } 
    }
  } return 0;
}

// Parser, can only take two arguements,
//   ex: "cat open.txt"
int Parse( void ) {
  const char *verb = strtok( a, " \n" );
  const char *noun = strtok( b, " \n" );
  if ( verb != NULL ) {
    if ( strcmp(verb, "exit") == 0 ) {        // Disconnect from current pc
      printf("exit\n");
      printf("Disconnecting...\n");
    } if ( strcmp(verb, "quit") == 0 ) {      // Exit game, for testing
      exit( 0 );
    } if ( strcmp(verb, "pwd") == 0 ) {       // Print working directory
      printf("%s\n", Dir[loc]);
    } if ( strcmp(verb, "popd") == 0 ) {      // Pop directory
      loc--;
      printf("%s\n", Dir[loc]);
    }  if ( strcmp(verb, "pushd") == 0 ) {    // Push directory
      loc++;
      printf("%s\n", Dir[loc]);
    } if ( strcmp(verb, "ls") == 0 ) {        // List files in current directory
      Files();
      printf("\n");
    } if ( strcmp(verb, "rm") == 0 ) {        // Remove file
      printf("%s\n", cmds[5].description);
    } if ( strcmp(verb, "cat") == 0 ) {       // Print out file
      Write( "story/", noun );
      printf("\n");                           
    } if ( strcmp(verb, "ssh") == 0 ) {       // Connect to another pc via ip address
      connect(noun);
    } if ( strcmp(verb, "help") == 0 ) {      // List Commands with "help"
      for(int x = 0; x < 11; x++) {
	printf("%s\t\t- %s\n", cmds[x].tag, cmds[x].description);
      }
    } if ( strcmp(verb, "echo") == 0 ) {      // Echo text
      Echo(noun);
    } if ( strcmp(verb, "clear") == 0 ) {     // Clear screen
      Cls();
    } 
  } else {
    //Can do error handling here, may leave blank
  }
  return 0;
}

// Remove spaces from b
void RemoveSpaces( char *source ) {
  char *i = source;
  char *j = source;
  while ( *j != 0 ) {
      *i = *j++;
      if( *i != ' ' ) {
	  i++;
        }
    } *i = 0;
}

// User Input
int Input( char *str ) {
  char split[ MAX ] = " ";
  char *ptr = b; 
  memset( &ptr[0], 0, MAX );
  fgets( str, MAX, stdin );                 // get user input, string a
  int j = 0;
  if ( strchr(str, ' ') != NULL ) {         // get string b
    while( strchr(str, ' ') != NULL ) {
      strncpy( ptr, str, strlen(a) );
      token = strtok( str, split );
      while( ptr[j] != '\n' ) {
	memmove( ptr, ptr+1, strlen(str) );
	j++;
      } RemoveSpaces( ptr );
    }
  }   
  return 0;
}

// Virtualized boot sequence
void Boot() {
  printf( RED "Lotus 6502 VGA BIOS. Version 1.0.0\n" );
  sleep( 1 );
  printf( YELLOW "Kernel Version 1.0.0\n\n" WHITE);
  sleep( 1 );
  printf( "Testing RAM...\n" );
  sleep( 1 );
  printf( "Testing CPU...\n" );
  sleep( 1 );
  printf( "Testing HDD...\n" );
  sleep( 1 );
  printf( "Checking for boot data...\n" );
  sleep( 1 );
  printf( "Boot data found... \n" );
  sleep( 1 );
  printf( "Booting from floppy drive...\n" );
  sleep( 1 );
  printf( "Sarting network interface: 192.168.0.1\n" );
  sleep( 1 );
  printf( GREEN "--Complete--\n" WHITE );
  sleep( 1 );
}
