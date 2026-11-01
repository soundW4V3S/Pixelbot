#include <iostream>
#include <windows.h>   // Using for GetPixel()


int main()
{

	//
	// -- New update allows for best color-checking
	//


	POINT pt{ 960, 135 };														// Get point information here

	HDC screenDC = GetDC(nullptr);												// Entire desktop, No need for validity checking
	COLORREF c = GetPixel(screenDC, pt.x, pt.y);
	while (1)																	// Scan forever
	{
		c = GetPixel(screenDC, pt.x, pt.y);										// Get Pixel Hex value
		std::cout << "TOTAL RGB VALUE: 0x00" << std::hex << c << std::endl;		// Print curr ENTIRE value to Console
		int r = (int)GetRValue(c);
		int g = (int)GetGValue(c);												// Number isolating here
		int b = (int)GetBValue(c);
		std::cout << "Red: " << std::hex << r << "\t\t";						// need to cast to "int" type to properly work first
		std::cout << "Green: " << std::hex << g << "\t";						// Print necessary values individually
		std::cout << "Blue: " << std::hex << b << std::endl;



		// --
		// -- MATH CONDITIONAL TIME
		// --


		// RED-CHECKING

		if ((r == 0xFF) && (g == 0x7E) && (b == 0x86))
		{
			std::cout << "!! LIGHT DETECTED !! STEADY YOUR AIM !!" << std::endl;
		}


		// GREEN-CHECKING

		if ((r == 0x06) && (g == 0xD6) && (b == 0x38))			// If our value is ABSOLUTELY high enough AND Not matching other bit values
		{
			Sleep(25);											// Brief Server Debounce pause
			int briefFlag = 0;									// Flag for clicking
			while (1)											// Get caught over here, spam click
			{

				std::cout << "SHOOTING!!!" << std::endl;		// Console spamming text

				INPUT inp[2]{};									// Input Object

				inp[0].type = INPUT_MOUSE;						// Pressing
				inp[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

				inp[1].type = INPUT_MOUSE;						// Releasing
				inp[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

				SendInput(2, inp, sizeof(INPUT));
				Sleep(10);										// Very brief pause, for processor resources
				briefFlag++;
				if (briefFlag == 30)							// Flag for knowing when to terminate clicking. Less resource-intensive
				{
					std::cout << "thanks for using." << std::endl;
					ReleaseDC(nullptr, screenDC);
					return 0;
				}
			}
		}

		Sleep(15);

	}

	return 0;
}
