/*
 * Ersteller: Johannes Heidelbach
 * Windows/Linux specific functions to set colors for console
 */

#ifdef _WIN32
// color is two byte XY
// X defines background
// Y defines foreground
// 0 BLACK
// 1 DARK_BLUE
// 2 DARK_GREEN
// 3 DARK_CYAN
// 4 DARK_RED
// 5 DARK_PURPLE
// 6 BROWN
// 7 GRAY
// 8 DARK_GRAY
// 9 BLUE
// A GREEN
// B CYAN
// C RED
// D PURPLE
// E YELLOW
// F WHITE
enum Color
{
	BLACK, DARK_BLUE, DARK_GREEN, DARK_CYAN, DARK_RED, DARK_PURPLE, BROWN, GRAY, 
	DARK_GRAY, BLUE, GREEN, CYAN, RED, PURPLE, YELLOW, WHITE
};
#elif defined __linux__
enum Color
{
	BLACK=30, DARK_RED, DARK_GREEN, BROWN, DARK_YELLOW, DARK_BLUE, DARK_PURPLE, DARK_CYAN, GRAY, 
	DARK_GRAY=90, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE
};
#else
#error "Unknown System"
#endif

void resetColors();

// sets the low byte
void setFGColor(int colorFG);

// sets the high byte
void setBGColor(int colorBG);


// foreground

#define setFGBlack() setFGColor(BLACK)

// DARK_*

#define setFGLGray() setFGColor(GRAY)

#define setFGGray() setFGColor(DARK_GRAY)

#define setFGBlue() setFGColor(BLUE)

#define setFGGreen() setFGColor(GREEN)

#define setFGCyan() setFGColor(CYAN)

#define setFGRed() setFGColor(RED)

#define setFGPurple() setFGColor(PURPLE)

#define setFGYellow() setFGColor(YELLOW)

#define setFGWhite() setFGColor(WHITE)

// background

#define setBGBlack() setBGColor(BLACK)

#define setBGGray() setBGColor(DARK_GRAY)

#define setBGLGray() setBGColor(GRAY)

#define setBGBlue() setBGColor(BLUE)

#define setBGGreen() setBGColor(GREEN)

#define setBGCyan() setBGColor(CYAN)

#define setBGRed() setBGColor(RED)

#define setBGPurple() setBGColor(PURPLE)

#define setBGYellow() setBGColor(YELLOW)

#define setBGWhite() setBGColor(WHITE)

