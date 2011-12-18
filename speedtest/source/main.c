////////////////////////////
// PAlib project template //
////////////////////////////

// Include PAlib so that you can use it
#include <PA9.h>
#define TIME 50

int vie=5000000;
// Function: main()
int main(int argc, char ** argv)
{
    PA_Init();    // Initializes PA_Lib
    PA_InitVBL(); // Initializes a standard VBL

    PA_InitText(0, 0);
    PA_InitRand();

    int i, totaltime[2];

        PA_OutputText(0, 0, 1,"%d",PA_RTC.Seconds);
    while(PA_RTC.Seconds){PA_OutputText(0, 0, 1,"%d",PA_RTC.Seconds);PA_UpdateRTC();}

    for (i=0; TIME>PA_RTC.Seconds; i++) //i<5000000000000;i++)
    {
        PA_UpdateRTC();
        vie-=PA_RandMinMax(38,49);
    }
    totaltime[0]=i;



    vie=50000000;
    while(PA_RTC.Seconds){PA_OutputText(0, 0, 1,"%d",PA_RTC.Seconds);PA_UpdateRTC();}

    for (i=0; TIME>PA_RTC.Seconds; i++) //i<5000000000000;i++)
    {
        PA_UpdateRTC();
        vie-=43;
    }
    totaltime[1]=i;
    PA_OutputText(0, 0, 4, "%01 : %08d times", totaltime[0]);
    PA_OutputText(0, 0, 5, "%02 : %08d times", totaltime[1]);
    PA_OutputText(0, 0, 6, "second is %d %% time faster", 100*(totaltime[1]-totaltime[0])/totaltime[1]);
    // Infinite loop to keep the program running
    while (1)
    {



        PA_WaitForVBL();
    }

    return 0;
} // End of main()
