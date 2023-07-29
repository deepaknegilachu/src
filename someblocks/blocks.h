//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/

	{" ", "sed 's/000$/°C/' /sys/class/thermal/thermal_zone0/temp",	10,		0},

	{" ", "date '+%d:%b:%y(%a)%I:%M%P'",					60,		0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
