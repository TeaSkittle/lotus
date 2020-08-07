#define MAX 1024                      // Size for input values
static char a[ MAX ], b[ MAX ];       // Input a and b
struct Commands;                      // Struct of shell commands for game
static int loc = 4;                   // Start player in Home directory
static const char dir[ 10 ][ 50 ];    // Directory/File structure of PC's in game
static const char ip[ 3 ][ 15 ];      // Array of ip addresses
static char *token;                   // Used in Input function, random variable name
int current_pc = 0;                   // Which PC player is connected to
void prompt( char hostname[10] );     // Command prompt

struct Commands {                     // Commands
  const char *description;            // Description of commands
  const char *tag;                    // Name or tag of commands
};
struct Commands cmds[ 11 ];
struct Commands cmds[ 11 ] = {
  { "show list of commands", "help" },
  { "print working directory", "pwd" },
  { "move one directory down", "pop" },
  { "move one directory up", "push" },
  { "list", "ls" },
  { "show contents of file", "cat" },
  { "connect to another computer", "ssh" },
  { "disconnect from computer", "exit" },
  { "show current ip", "ip" },
  { "clear screen", "clear" },  
  { "quit game", "quit" }
};

static const char dir[ 10 ][ 50 ] = {  // File Structure
  "/",
  "/bin",
  "/sys",
  "/home",
  "/home/user",
  "/home/user/Documents",
};

void connect_prompt() {
  printf( CYAN "Connecting...\n" );
  loc = 4;
}

int view_ip( int pc ) {
  printf( "%s\n", ip[ pc ] );
  return pc;
}

// Array of pcs player will connect to
static const char ip[ 3 ][ 15 ] = {
  "192.168.0.1",  // Home, starting pc
  "192.168.10.5",
  "127.0.2.12"
};

// This is for 'ls' and shows certain files
int Files() {
  if ( current_pc == 0 ) {  // 192.168.0.1
    if ( loc == 4 ) { printf( "readme.txt\n" ); }
    else if ( loc == 5 ) { printf( "empire.txt\n" ); }
  }
  else if ( current_pc == 1 ) {  // 192.168.10.5
    if ( loc == 4 ) { printf( "format.txt\n" ); } // Need to add new story file here 
  } return loc; 
}

void connect( const char *other_pc ) {   // Connect(ssh) to another PC
  if ( other_pc != NULL ) {
    if ( strcmp(other_pc, ip[0] ) == 0 ) {
      current_pc = 0;
      connect_prompt();
    } else if ( strcmp(other_pc, ip[1] ) == 0 ) {
      current_pc = 1;
      connect_prompt();
    } else if ( strcmp(other_pc, ip[2] ) == 0 ) {
      current_pc = 2;
      connect_prompt();
  } else {
    printf( RED "Unkown ip\n" );
    }
  } else { printf( RED "No argument supplied\n" ); }      
}

// Use Type from tul.h, but open from a subfoler.
void Write( const char *dir, const char *name ) {
  static char subdir[ MAX ], file[ MAX ];
  strcpy( subdir, dir );
  strcpy( file, name );
  Type( strcat(subdir, file) );
}

// Parser, can only take two arguements,
void parse( void ) {
  const char *verb = strtok( a, " \n" );
  const char *noun = strtok( b, " \n" );
  if ( verb != NULL ) {
    if ( strcmp(verb, "exit") == 0 ) {        // Disconnect from current pc
      if ( current_pc != 0 ) {
	printf( CYAN "Disconnecting...\n" );
	current_pc = 0;
      } else { printf( RED "At home ip\n" ); }
    } if ( strcmp(verb, "quit") == 0 ) {      // Exit game, for testing
      exit( 0 );
    } if ( strcmp(verb, "pwd") == 0 ) {       // Print working directory
      printf("%s\n", dir[loc]);
    } if ( strcmp(verb, "pop") == 0 ) {      // Pop directory
      if ( loc > 0 ) { 
	loc--;
	printf("%s\n", dir[loc]);
      } else { printf( RED "On bottom of directory stack\n" ); }
    }  if ( strcmp(verb, "push") == 0 ) {    // Push directory
      if ( loc < 5 ) {
	loc++;
	printf("%s\n", dir[loc]);
      } else { printf( RED "On top of directory stack\n" ); }
    } if ( strcmp(verb, "ls") == 0 ) {        // List files in current directory
      Files();
    } if ( strcmp(verb, "cat") == 0 ) {       // Print out file
      if ( noun != NULL ) {
	Write( "story/", noun );
	printf("\n");
      } else { printf( RED "No argument supplied\n" ); }
    } if ( strcmp(verb, "ssh") == 0 ) {       // Connect to another pc via ip address
      connect(noun);
    } if ( strcmp(verb, "help") == 0 ) {      // List Commands with "help"
      for(int x = 0; x < 11; x++) {
	printf("%s\t\t- %s\n", cmds[x].tag, cmds[x].description);
      }
    } if ( strcmp(verb, "clear") == 0 ) {     // Clear screen
      Cls();
    } if ( strcmp(verb, "ip") == 0) {
      view_ip( current_pc );
      }
  } else {}
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
void input( char *str ) {
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

void prompt( char hostname[10] ){
    printf( GREEN "%s", hostname );
    printf( WHITE "\n" );
    input( a );
    printf( "\n" );
    parse();
    printf( "\n" );
}

