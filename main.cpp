#include "mbed.h"
#include "App.h"
#include "rtos_idle.h"

EventQueue queue;
App app( queue );

int main()
{
    app.Init();

    queue.dispatch_forever();
}