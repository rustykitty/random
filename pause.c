#include <termios.h>
#include <unistd.h>
#include <stdio.h>

// Windows `pause`-like behavior
void wait_for_keypress() {
    struct termios original;
    tcgetattr(STDIN_FILENO, &original);
    struct termios mod = original;
    // disable canonical (line-by-line) mode and echo
    mod.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &mod);
    char c;
    read(STDIN_FILENO, &c, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &original); 
}

void io_pause() {
    fputs("Press any key to continue...", stdout);
    fflush(stdout);
    wait_for_keypress();
    fputs("\n", stdout);
    fflush(stdout);
}

int main() {
    io_pause();
    return 0;
}