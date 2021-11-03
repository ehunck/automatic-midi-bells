#include "mbed.h"
#include "App.h"

EventQueue queue;
App app( queue );

int main()
{
    app.Init();

    queue.dispatch_forever();
}