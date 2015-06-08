#include <cstdlib>
#include <ctime>
#include <iostream>

#include <signal.h>

#include "game/game_sdl2.h"

bool RELOAD = false;

// TODO : this signal stuff is only for debug builds
static void sig_handler(int signum) {
  std::cout << "Reload\n";
  RELOAD = true;
}

// TODO : easing functions for natural movement
int main(int argc, char* argv[])
{
  if (signal(SIGUSR1, sig_handler) == SIG_ERR) {
    std::cerr << "Failed to setup signal handler. " << std::endl;
    return 1;
  }

  std::srand(std::time(0));

  std::unique_ptr<game::GameSDL2> game = game::make_game();
  while (game->running) {
    if (RELOAD) {
      game->reload();
      RELOAD = false;
    }
    game->step();
  }

  return 0;
}
