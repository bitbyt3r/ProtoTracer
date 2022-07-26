#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>


#include "Include/Animation/Test/SpyroAnimation.h"
#include "Include/Controllers/RPI_Parallel_Controller.h"

#include "Include/Utils/utils.h"

//Terminal Interrupt
volatile bool interrupt_received = false;
static void InterruptHandler(int signo)
{
	interrupt_received = true;
}

const uint8_t maxBrightness = 10; 
uint64_t prevTime = 0;

RPI_LED_Matrix_Controller controller = RPI_LED_Matrix_Controller(maxBrightness);
SpyroAnimation anim;

int main(int argc, char *argv[])
{
	signal(SIGTERM, InterruptHandler);
	signal(SIGINT, InterruptHandler);
	
	initializeTimers();
	
	controller.Initialize();

	while (!interrupt_received)
	{
		float ratio = (float)(millis() % 5000) / 5000.0f;

		prevTime = micros();
		
		anim.Update(ratio);
		controller.Render(anim.GetScene());
		controller.Display();

		uint64_t renderTime = 1000000 / (micros() - prevTime);
		printf("\033[2J\033[1;1H");
		printf("Frames Per Second: %.2f \n", (float)renderTime);

	}

	return 0;
}