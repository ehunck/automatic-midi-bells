#include "mbed.h"
#include "App.h"

EventQueue queue;
App app( queue );
DigitalOut led(LED2);

int main()
{
    app.Init();

    queue.dispatch_forever();
}