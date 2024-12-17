//#include <SFML/Graphics.hpp>
#include "app.h"
using namespace amc;

int main()
{
    
    App amc;
    
   

    if (amc.Construct(800, 600, "Another Minecraft Clone"))
    {
        amc.Run();
    }

    return 0;
}