<<<<<<< HEAD
#include <stdio.h>
#include "auto_tchar.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <bitset>
#include "SerialClass.h"	// Library described above

#if defined(_MSC_VER)
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#elif defined(__linux__)
#include <SDL2/SDL.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <errno.h>

#endif
using namespace std;

typedef struct {
  char end_1;
  char end_2;
  unsigned short x;
  unsigned short y;
} serial_format;

#ifdef __linux__
  typedef struct joyinfoex_tag {
    unsigned long dwSize;
    unsigned long dwFlags;
    unsigned long dwXpos;
    unsigned long dwYpos;
    unsigned long dwZpos;
    unsigned long dwRpos;
    unsigned long dwUpos;
    unsigned long dwVpos;
    unsigned long dwButtons;
    unsigned long dwButtonNumber;
    unsigned long dwPOV;
    unsigned long dwReserved1;
    unsigned long dwReserved2;
    } JOYINFOEX;
#endif

// application reads from the specified serial port and reports the collected data
int _tmain(int argc, _TCHAR* argv[])
{
// connect the COM
	printf("Welcome to the serial test app!\n\n");
#if defined (_MSC_VER)
	Serial* SP = new Serial("\\\\.\\COM6");    // adjust as needed
#elif defined (__linux__)
	Serial* SP = new Serial("/dev/ttyACM2");
	unsigned int JOYSTICKID1;
#endif

	if (SP->IsConnected())
		printf("We're connected!\n");

//data communication
	char incomingData[256] = "";			// don't forget to pre-
	int dataLengthin = 255;
	int readResult = 0;

	int angle=2048;
	const int encoder_resolution=4096;
	char outcomingData[6]="2048c";
	int speedDutycycle=0;
	const int fullDutycycle=255;
	char outSpeed[5]="001a";

//joystick initialize***********************

	joyinfoex_tag joyinfo;

#ifdef __linux__
    if (SDL_Init(SDL_INIT_JOYSTICK) < 0){
        cout << "Error initializing SDL!" << endl;
        return 1;
    }
	SDL_Joystick *joy;
    int CtrlNum = SDL_NumJoysticks();
    if (CtrlNum == 1)
        JOYSTICKID1 = 0;
    else{
        cout << "There are " << CtrlNum << " controllers found..." << endl;
        for(int i=0;i<CtrlNum;i++)
        {
            joy = SDL_JoystickOpen(i);
            printf("%s\n", SDL_JoystickName(joy));
        }
        cout << "Choose the one you wish to use: " << endl;
        cin >> JOYSTICKID1;
    }
    joy=SDL_JoystickOpen(JOYSTICKID1);
    if (joy) {
        printf("Opened Joystick %d\n",JOYSTICKID1);
        printf("Name: %s\n", SDL_JoystickNameForIndex(0));
        printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
        printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
        printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
    } else {
        printf("Couldn't open Joystick %d\n", JOYSTICKID1);
        return -1*JOYSTICKID1;
    }
#endif

//button status
	bool is_in_situ=false;
	bool is_any_direction=false;
	bool is_tradition=true;
	bool now_in_situ=false;
	bool now_any_direction=false;
	bool now_tradition=false;
	bool last_in_situ=false;
	bool last_any_direction=false;
	bool last_tradition=false;

	//int count = 0;
//start control
	bool action = 1;
	while(SP->IsConnected())                            // CYCLES HERE...
	{
		//acquire joystick info **********************
#if defined(_MSC_VER)
		joyGetPosEx(JOYSTICKID1, &joyinfo);
#elif defined(__linux__)
        joyinfo.dwXpos = SDL_JoystickGetAxis(joy,0);
		joyinfo.dwYpos = SDL_JoystickGetAxis(joy,1);
		joyinfo.dwZpos = SDL_JoystickGetAxis(joy,2);
		joyinfo.dwRpos = SDL_JoystickGetAxis(joy,3);
		//Only 4 axis.
		//joyinfo.dwUpos = SDL_JoystickGetAxis(joy,4);
		//joyinfo.dwVpos = SDL_JoystickGetAxis(joy,5);
#endif
		cout << "X Steering Wheel:" << joyinfo.dwXpos << endl;
		if(joyinfo.dwZpos != 32767)
			action = 0;
		if(action)
			cout << "Z Throttle:" << 65536 << endl; //油门 初始值65535，踩到底为0		
		else
			cout << "Z Throttle:" << joyinfo.dwZpos << endl; /*//油门 初始值65535，踩到底为0	
		cout << "R刹车:" << joyinfo.dwRpos << endl; //刹车 初始值65535，踩到底为0
		cout << "buttonNumber" << joyinfo.dwButtonNumber << endl;
		cout << "buttonStatus" << bitset<64>(joyinfo.dwButtons) << endl; //从右往左为从低位到高位
		now_in_situ=bitset<64>(joyinfo.dwButtons)[0];
		now_any_direction=bitset<64>(joyinfo.dwButtons)[3];
		now_tradition=bitset<64>(joyinfo.dwButtons)[1];
		cout << "is_in_situ:" << is_in_situ << endl;
		cout << "is_any_direction:" << is_any_direction << endl;
		cout << "is_tradition:" << is_tradition << endl;
		
		if(now_in_situ== true && last_in_situ ==false)
		{
			is_in_situ =true;
			is_any_direction =false;
			is_tradition =false;

			SP->WriteData("b",1);
		}

		if(now_any_direction== true && last_any_direction ==false)
		{
			is_in_situ =false;
			is_any_direction =true;
			is_tradition =false;

			SP->WriteData("f",1);

		}

		if(now_tradition== true && last_tradition ==false)
		{
			is_in_situ =false;
			is_any_direction =false;
			is_tradition =true;
			SP->WriteData("f",1);

		}

		last_in_situ =now_in_situ;
		last_any_direction =now_any_direction;
		last_tradition =now_tradition;*/
		if(action)//初始时默认是32767，要调成65535
			speedDutycycle = 0;
		else
			speedDutycycle = (int)((1-joyinfo.dwZpos/65535.0)*fullDutycycle);
			if(speedDutycycle>=0 && speedDutycycle<=255)
			{
				for (int k=0;k<3;k++)
				{
					outSpeed[2-k]=char(speedDutycycle%10 + '0');
					speedDutycycle=speedDutycycle/10;
				}
			}
		angle=(int)(joyinfo.dwXpos/65535.0*encoder_resolution);
			if(angle>=0 && angle<=encoder_resolution)
			{
				for (int k=0;k<4;k++)
				{
					outcomingData[3-k]=char(angle%10 + '0');
					angle=angle/10;
				}
			}
		
		printf("outSpeed:%s\n",outSpeed);
		bool isWriteSpeed = SP->WriteData((char*)&outSpeed, strlen(outSpeed));
		cout << "WriteSucceed?" << isWriteSpeed << endl;
		printf("outcomingData:%s\n",outcomingData);
		bool isWriteAngle = SP->WriteData((char*)&outcomingData, strlen(outcomingData));
#if defined(_MSC_VER)
		Sleep(1000);
#elif defined (__linux__)
		usleep(1000000);
#endif
		/*system("cls");*/
		readResult = SP->ReadData(incomingData,dataLengthin);

		///*if(readResult<2*sizeof(serial_format)){
		//	printf("No enough data received. Let's wait.\n");
		//	Sleep(1500);continue;
		//}*/

		int ptr=0;
		while(!(incomingData[ptr]==0x3f && incomingData[ptr+1]==0x3f) && ptr<readResult-sizeof(serial_format)) {
			ptr++;
		}
		serial_format* ptr_to_first_valid = (serial_format*) &incomingData[ptr];

		printf("RecX:%d\n",ptr_to_first_valid->x);
		printf("RecY:%d\n",ptr_to_first_valid->y);
		
	}
#ifdef __linux__
	SDL_JoystickClose(joy);
#endif
	system("pause");
	return 0;
}
=======
#include <stdio.h>
#include "auto_tchar.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <bitset>
#include "SerialClass.h"	// Library described above

#if defined(_MSC_VER)
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#elif defined(__linux__)
#include <SDL/SDL.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <errno.h>

#endif
using namespace std;

typedef struct {
  char end_1;
  char end_2;
  unsigned short x;
  unsigned short y;
} serial_format;

#ifdef __linux__
  typedef struct joyinfoex_tag {
    unsigned long dwSize;
    unsigned long dwFlags;
    unsigned long dwXpos;
    unsigned long dwYpos;
    unsigned long dwZpos;
    unsigned long dwRpos;
    unsigned long dwUpos;
    unsigned long dwVpos;
    unsigned long dwButtons;
    unsigned long dwButtonNumber;
    unsigned long dwPOV;
    unsigned long dwReserved1;
    unsigned long dwReserved2;
    } JOYINFOEX;
#endif

// application reads from the specified serial port and reports the collected data
int _tmain(int argc, _TCHAR* argv[])
{
// connect the COM
	printf("Welcome to the serial test app!\n\n");
#if defined (_MSC_VER)
	Serial* SP = new Serial("\\\\.\\COM6");    // adjust as needed
#elif defined (__linux__)
	Serial* SP = new Serial("/dev/ttyS6");
	unsigned int JOYSTICKID1;
#endif

	if (SP->IsConnected())
		printf("We're connected!\n");

//data communication
	char incomingData[256] = "";			// don't forget to pre-
	int dataLengthin = 255;
	int readResult = 0;

	int angle=2048;
	const int encoder_resolution=4096;
	char outcomingData[6]="2048c";
	int speedDutycycle=0;
	const int fullDutycycle=255;
	char outSpeed[5]="001a";

//joystick initialize***********************

	joyinfoex_tag joyinfo;

#ifdef __linux__
	SDL_Joystick *joy;
    int CtrlNum = SDL_NumJoysticks();
    if (CtrlNum == 1)
        JOYSTICKID1 = 0;
    else{
        cout << "There are " << CtrlNum << " controllers found..." << endl;
        for(int i=0;i<CtrlNum;i++)
            printf("%d%s\n", i, SDL_JoystickName(i));
        cout << "Choose the one you wish to use: " << endl;
        cin >> JOYSTICKID1;
    }
    joy=SDL_JoystickOpen(JOYSTICKID1);
    int JoystickFlag = SDL_JoystickOpened(JOYSTICKID1);
    if (JoystickFlag == 0){
        cout << "Controller Open Error!" << endl;
        return -1*JOYSTICKID1;
    }
#endif

//button status
	bool is_in_situ=false;
	bool is_any_direction=false;
	bool is_tradition=true;
	bool now_in_situ=false;
	bool now_any_direction=false;
	bool now_tradition=false;
	bool last_in_situ=false;
	bool last_any_direction=false;
	bool last_tradition=false;

	//int count = 0;
//start control
	bool action = 1;
	while(SP->IsConnected())                            // CYCLES HERE...
	{
		//acquire joystick info **********************
#if defined(_MSC_VER)
		joyGetPosEx(JOYSTICKID1, &joyinfo);
#elif defined(__linux__)
        joyinfo.dwXpos = SDL_JoystickGetAxis(joy,0);
		joyinfo.dwYpos = SDL_JoystickGetAxis(joy,1);
		joyinfo.dwZpos = SDL_JoystickGetAxis(joy,2);
		joyinfo.dwRpos = SDL_JoystickGetAxis(joy,3);
		joyinfo.dwUpos = SDL_JoystickGetAxis(joy,4);
		joyinfo.dwVpos = SDL_JoystickGetAxis(joy,5);
#endif
		cout << "X方向盘:" << joyinfo.dwXpos << endl;
		if(joyinfo.dwZpos != 32767)
			action = 0;
		if(action)
			cout << "Z油门:" << 65536 << endl; //油门 初始值65535，踩到底为0		
		else
			cout << "Z油门:" << joyinfo.dwZpos << endl; /*//油门 初始值65535，踩到底为0	
		cout << "R刹车:" << joyinfo.dwRpos << endl; //刹车 初始值65535，踩到底为0
		cout << "buttonNumber" << joyinfo.dwButtonNumber << endl;
		cout << "buttonStatus" << bitset<64>(joyinfo.dwButtons) << endl; //从右往左为从低位到高位
		now_in_situ=bitset<64>(joyinfo.dwButtons)[0];
		now_any_direction=bitset<64>(joyinfo.dwButtons)[3];
		now_tradition=bitset<64>(joyinfo.dwButtons)[1];
		cout << "is_in_situ:" << is_in_situ << endl;
		cout << "is_any_direction:" << is_any_direction << endl;
		cout << "is_tradition:" << is_tradition << endl;
		
		if(now_in_situ== true && last_in_situ ==false)
		{
			is_in_situ =true;
			is_any_direction =false;
			is_tradition =false;

			SP->WriteData("b",1);
		}

		if(now_any_direction== true && last_any_direction ==false)
		{
			is_in_situ =false;
			is_any_direction =true;
			is_tradition =false;

			SP->WriteData("f",1);

		}

		if(now_tradition== true && last_tradition ==false)
		{
			is_in_situ =false;
			is_any_direction =false;
			is_tradition =true;
			SP->WriteData("f",1);

		}

		last_in_situ =now_in_situ;
		last_any_direction =now_any_direction;
		last_tradition =now_tradition;*/
		if(action)//初始时默认是32767，要调成65535
			speedDutycycle = 0;
		else
			speedDutycycle = (int)((1-joyinfo.dwZpos/65535.0)*fullDutycycle);
			if(speedDutycycle>=0 && speedDutycycle<=255)
			{
				for (int k=0;k<3;k++)
				{
					outSpeed[2-k]=char(speedDutycycle%10 + '0');
					speedDutycycle=speedDutycycle/10;
				}
			}
		angle=(int)(joyinfo.dwXpos/65535.0*encoder_resolution);
			if(angle>=0 && angle<=encoder_resolution)
			{
				for (int k=0;k<4;k++)
				{
					outcomingData[3-k]=char(angle%10 + '0');
					angle=angle/10;
				}
			}
		
		printf("outSpeed:%s\n",outSpeed);
		bool isWriteSpeed = SP->WriteData((char*)&outSpeed, strlen(outSpeed));
		cout << "WriteSucceed?" << isWriteSpeed << endl;
		printf("outcomingData:%s\n",outcomingData);
		bool isWriteAngle = SP->WriteData((char*)&outcomingData, strlen(outcomingData));
#if defined(_MSC_VER)
		Sleep(1000);
#elif defined (__linux__)
		usleep(1000000);
#endif
		/*system("cls");*/
		readResult = SP->ReadData(incomingData,dataLengthin);

		///*if(readResult<2*sizeof(serial_format)){
		//	printf("No enough data received. Let's wait.\n");
		//	Sleep(1500);continue;
		//}*/

		int ptr=0;
		while(!(incomingData[ptr]==0x3f && incomingData[ptr+1]==0x3f) && ptr<readResult-sizeof(serial_format)) {
			ptr++;
		}
		serial_format* ptr_to_first_valid = (serial_format*) &incomingData[ptr];

		printf("RecX:%d\n",ptr_to_first_valid->x);
		printf("RecY:%d\n",ptr_to_first_valid->y);
		
	}
#ifdef __linux__
	SDL_JoystickClose(joy);
#endif
	system("pause");
	return 0;
}
>>>>>>> f22ec6c22c6fa5e43b341e05886f52a49472abd7
