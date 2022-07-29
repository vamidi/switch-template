#include <cstring>
#include <cstdio>
#include <iostream>

#include <switch.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/**
 * To test out with nxlink, do the following.
 *
 * nxlink <-a switch_ip> nxlink_stdio.nro -s <arguments>
 *
 * -s or --server tells nxlink to open a socket nxlink can connect to.
 *
 */

int main(int argc, char **argv)
{
    // This example uses a text console, as a simple way to output text to the screen.
    // If you want to write a software-rendered graphics application,
    //   take a look at the graphics/simplegfx example, which uses the libnx Framebuffer API instead.
    // If on the other hand you want to write an OpenGL based application,
    //   take a look at the graphics/opengl set of examples, which uses EGL instead.
    consoleInit(nullptr);

    // Configure our supported input layout: a single player with standard controller styles
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    // Initialize the default gamepad (which reads handheld mode inputs as well as the first connected controller)
    PadState pad;
    padInitializeDefault(&pad);

    // Other initialization goes here. As a demonstration, we print hello world.
    printf("Hello World!\n");

    // Initialise sockets
    socketInitializeDefault();

    // Display arguments sent from nxlink
    printf("%d arguments\n", argc);

    // the host ip where nxlink was launched
    printf("nxlink host is %s\n", inet_ntoa(__nxlink_host));

    auto libnxRes = nxlinkStdio();
    if (libnxRes <= 0)
        std::cout << "Failed to call nxlinkStdio with result: " << libnxRes << std::endl;

    // this text should display on nxlink host
    printf("printf output now goes to nxlink server\n");

    // main loop
    while(appletMainLoop())
    {
        // Scan the gamepad. This should be done once for each frame
        padUpdate(&pad);

        // padGetButtonsDown returns the set of buttons that have been
        // newly pressed in this frame compared to the previous one
        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus) {
            break; // break in order to return to hbmenu
        }

        // Your code goes here

        // Update the console, sending a new frame to the display
        consoleUpdate(nullptr);
    }

    socketExit();
    consoleExit(nullptr);
    return 0;
}
