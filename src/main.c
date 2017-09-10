#include "hdr/init.h"
   
int main(int argc, char* args[])
{
	open_sdl_shit();
	CORE game = {0};
	core_init(&game);
	launch_menu(&game);
	close_sdl_shit();
	return 0;
}
