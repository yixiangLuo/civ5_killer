#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include <TlHelp32.h>

#pragma comment(lib, "winmm.lib")

/*
TlHelp32.h for
    PROCESSENTRY32
    CreateToolhelp32Snapshot()
    Process32First()
    Process32Next()
*/

int main(int argc, char const *argv[])
{
	int hour, minute;
	int wait_time;
	int notice_before_1 = 10*60;	//seconds before killing when first notice
	int notice_before_2 = 3*60;		//seconds before killing when second notice
	char str[3];
	char pro_name[50];

	// set the end time
	if(argc == 1) strncpy(str, "00", 2);	//default end time 00:XX
	else strncpy(str, argv[1], 2);
	str[2]='\0';
	hour = atoi(str);
	if(hour>23) hour=23;

	if(argc == 1) strncpy(str, "00", 2);	//default end time XX:00
	else strncpy(str, argv[1]+3, 2);
	str[2]='\0';
	minute = atoi(str);
	if(minute>59) minute=59;
	
	if(argc==3) strcpy(pro_name, argv[2]);
	else strcpy(pro_name, "CivilizationV");	//default target process: CivilizationV
	strlwr(pro_name);

	time_t time_p, time_e;		//present time, end time
	struct tm *time_now, *time_end;
	time(&time_p);
	time_now = localtime(&time_p);
	if(time_now->tm_hour*60 + time_now->tm_min > hour*60 + minute)
		time_e = time_p+24*60*60;
	else time_e = time_p;
	time_end = localtime(&time_e);
	time_end->tm_hour = hour;
	time_end->tm_min = minute;
	time_e = mktime(time_end);
	wait_time = time_e-time_p;

	printf("The process \"%s\" will be killed in %2d hours and %2d minutes.\n", pro_name, wait_time/3600, wait_time/60%60);

	// wait
	if(wait_time > notice_before_1){
		Sleep((wait_time-notice_before_1)*1000);

		// first notice
		PlaySound(TEXT("alert_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Sleep(6000);
		
		wait_time = notice_before_1;
	}
	
	if(wait_time > notice_before_2){
		Sleep((wait_time-notice_before_2)*1000);

		// second notice
		PlaySound(TEXT("alert_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Sleep(6000);
		
		wait_time = notice_before_2;
	}

	Sleep(wait_time*1000);

	// kill the process
	HANDLE hSnapshot;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	
	hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if( hSnapshot == INVALID_HANDLE_VALUE )
	{
		printf( "CreateToolhelp32Snapshot (of processes) fails!" );
		return 0;
	}
	
	pe32.dwSize = sizeof( PROCESSENTRY32 );

	if( !Process32First( hSnapshot, &pe32 ) )
	{
	printf( "Process32First() Fails.\n" );
	CloseHandle( hSnapshot );
	return 0;
	}

	do {
		if(strstr(strlwr(pe32.szExeFile), pro_name) != NULL){
			hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, (DWORD)pe32.th32ProcessID );
			TerminateProcess(hProcess, 0); // kill the process
		}

	} while( Process32Next( hSnapshot, &pe32 ) );

	CloseHandle( hSnapshot );

	return 0;
}
