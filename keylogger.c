/*
What we are breaking down.


#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "user32.lib")

// Define global hook
HHOOK hHook = NULL;


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam){

	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main(void){

	// Set Windows Hook
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
	// Make sure that hook is set
	if(hHook == NULL){
		//I should put something here...
		// I guess we can exit since its no good if we don't have this hook
		return 1;
	}

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0)){

	}

	return 0;
}

*/

//Start the break down 

#include <windows.h> 
/*import windows functions windows.h is a Windows-specific header file for the C and C++ programming 
languages which contains declarations for all of the functions in the Windows API*/

#include <stdio.h>  
/*import c standard I/O lib https://devdocs.io/c/io */

/********************************************************************************************************************************************************/

#pragma comment(lib, "user32.lib") 
/*
#pragma:
The pragma directive controls implementation-specific behavior of the compiler, such as disabling 
compiler warnings or changing alignment requirements. Any pragma that is not recognized is ignored.
https://devdocs.io/c/preprocessor/impl
*/

/*
comment(lib, "user32.lib"):

Tell the linker to look for this .lib  during the linking phase of compiling the 
program into an executeable
https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2010/7f0aews7(v=vs.100)
*/


/********************************************************************************************************************************************************/

HHOOK hHook = NULL; /*Define global hook*/
/*
A hook is used to change how a program interacts with the OS and other applications.
This is compareable to a program plugin/extension.
https://docs.microsoft.com/en-us/windows/win32/winmsg/using-hooks
*/

/********************************************************************************************************************************************************/

/*
----->LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)

LowLevelKeyboardProc:
An application-defined or library-defined callback function used with the SetWindowsHookEx function. The system calls
this function every time a new keyboard input event is about to be posted into a thread input queue.
Note When this callback function is called in response to a change in the state of a key, the callback
function is called before the asynchronous state of the key is updated. Consequently, the asynchronous state of
the key cannot be determined by calling GetAsyncKeyState from within the callback function. More details provided
in the following link.
https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms644985(v=vs.85)?redirectedfrom=MSDN
	
	LRESULT CALLBACK LowLevelKeyboardProc(
		_In_ int    nCode,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam
		);

*/

/*
int nCode:

A code the hook procedure uses to determine how to process the message. If nCode is less than zero, 
the hook procedure must pass the message to the CallNextHookEx function without further processing 
and should return the value returned by CallNextHookEx. 
*/

/*
WPARAM wParam:

A code the hook procedure uses to determine how to process the message. If nCode is less than zero, the 
hook procedure must pass the message to the CallNextHookEx function without further processing and should 
return the value returned by CallNextHookEx. This parameter can be one of the following values.
*/

/*
LPARAM lParam:

A pointer to a KBDLLHOOKSTRUCT structure.
KBDLLHOOKSTRUCT structure - Contains information about a low-level keyboard input event.
https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-kbdllhookstruct?redirectedfrom=MSDN
*/

/*
CALLBACK: 
https://docs.microsoft.com/en-us/dotnet/framework/interop/callback-functions
https://en.wikipedia.org/wiki/Callback_%28computer_programming%29#C
*/
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{ 
	
	/*
	LRESULT (return CallNextHookEx):

	Passes the hook information to the next hook procedure in the current hook chain. 
	A hook procedure can call this function either before or after processing the hook information.
	*/
	return CallNextHookEx(hHook, nCode, wParam, lParam); 
}


int main(void)
{

/********************************************************************************************************************************************************/

	
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0); /*Set windows hook*/
	/*
	SetWindowsHookEx: 
	Installs an application-defined hook procedure into a hook chain. You would install a hook procedure to monitor 
	the system for certain types of events. These events are associated either with a specific thread or with all threads in 
	the same desktop as the calling thread.
	https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowshookexa?redirectedfrom=MSDN
	see the note at bottom of linked web page 
	
	HHOOK SetWindowsHookEx(
	  int       idHook,
	  HOOKPROC  lpfn,
      HINSTANCE hmod,
	  DWORD     dwThreadId
	  );
	*/

	/*
	WH_KEYBOARD_LL (int idHook):

	The WH_KEYBOARD_LL hook enables you to monitor keyboard input events about to be posted in a thread input queue.
    For more information, see the LowLevelKeyboardProc callback function.
	https://docs.microsoft.com/en-us/windows/win32/winmsg/about-hooks?redirectedfrom=MSDN#wh_keyboard_ll
	*/

	/*
	LowLevelKeyboardProc (HOOKPROC  lpfn):

	A pointer to the hook procedure. If the dwThreadId parameter is zero or specifies the identifier of a thread created
	by a different process, the lpfn parameter must point to a hook procedure in a DLL. Otherwise, lpfn can point to a
	hook procedure in the code associated with the current process.
	*/

	/*
	NULL (HINSTANCE hmod):

	A handle to the DLL containing the hook procedure pointed to by the lpfn parameter. The hMod parameter must be set to NULL 
	if the dwThreadId parameter specifies a thread created by the current process and if the hook procedure is within the code
	associated with the current process.
	*/

	/*
	0 (DWORD dwThreadId):
	The identifier of the thread with which the hook procedure is to be associated. For desktop apps, if this parameter is zero, 
	the hook procedure is associated with all existing threads running in the same desktop as the calling thread. For Windows 
	Store apps, see the Remarks section in the following link.
	https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowshookexa?redirectedfrom=MSDN
	*/

	/*
	Return value:
	Type: HHOOK
	If the function succeeds, the return value is the handle to the hook procedure.
	If the function fails, the return value is NULL. To get extended error information, call GetLastError
	https://docs.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-getlasterror.
	*/

	//Make sure the hook is set
	if (hHook == NULL) {
		//I should put something here... aka error handling 
		// I guess we can exit since its no good if we don't have this hook

		return 1; // Error was raised treminate the program

/*********************************************************************************************************************************************************/

	MSG msg; // Contains message information from a thread's message queue. https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-msg

	while (GetMessage(&msg, NULL, 0, 0)) {

	}

	/*
	GetMessage: 
	Retrieves a message from the calling thread's message queue. The function dispatches 
	incoming sent messages until a posted message is available for retrieval.
	
	BOOL GetMessage(
	 LPMSG lpMsg,
	 HWND  hWnd,
	 UINT  wMsgFilterMin,
	 UINT  wMsgFilterMax
	);
	https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessage
	see link provided for more information on the parameters
	*/

	/*
	&msg (LPMSG lpMsg):

	A pointer to an MSG structure that receives message information from the thread's message queue.
	*/
	
	/*
	NULL (HWND  hWnd):

	A handle to the window whose messages are to be retrieved. The window must belong to the current thread.

	If hWnd is NULL, GetMessage retrieves messages for any window that belongs to the current thread, and any messages 
	on the current thread's message queue whose hwnd value is NULL (see the MSG structure). Therefore if hWnd is NULL, 
	both window messages and thread messages are processed.
	*/
	 
	/*
	0 (UINT  wMsgFilterMin):
	
	The integer value of the lowest message value to be retrieved.
	
	If wMsgFilterMin and wMsgFilterMax are both zero, GetMessage returns 
	all available messages (that is, no range filtering is performed).
	*/
	
	/*
	0 (UINT  wMsgFilterMax):

	The integer value of the highest message value to be retrieved.

	If wMsgFilterMin and wMsgFilterMax are both zero, GetMessage returns all 
	available messages (that is, no range filtering is performed).
	*/

/********************************************************************************************************************************************************/


	return 0; // Normal program terminataion 
}
//End of break down 