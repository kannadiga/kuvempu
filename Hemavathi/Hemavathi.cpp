// Hemavathi.cpp : Defines the initialization routines for the DLL.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////AUTHOR : Sudheer HS	sudheer316@gmail.com////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////DATE : 6-apr-2006							////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////COMPANY : Maruthi Software Developers.,HASSAN - 573201 ,KARANATAKA, INDIA     ////////////////////////////////////////////////////////////////
////////////////Description : This processes key inputs and emulates kannada characters for the key pressed		////////////////////////////////////////////////////////////////
////////////////			 this reads the key pressed and then produces the required characters for kannada languagge		////////////////////////////////////////////////////////////////
////////////////Compiler Used : Microsoft Visual C++ 6.0////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	////////////////////////////////////////////////////////////////	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////  This has been done as a project for Hampi University ,Hampi,INDIA ////////////////////////////////////////////////////////////////
////////////////  this is part of the free software Kuvempu Kannada Thantramsha,launched by Hampi University ////////////////////////////////////////////////////////////////
////////////////  This code as is with out any kind of warranty ,Using or modifing the code or the library without ////////////////////////////////////////////////////////////////
////////////////  the written permission by the university is prohibited,Any such illegal activities is punishable offence as per ////////////////////////////////////////////////////////////////
////////////////  the copy rights ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Hemavathi.h"
#include "..\headers\keyfuncts.h"
#include "..\headers\flags.h"
#include <vector>
#include <windows.h>


#define SINGLE 1
#define SLASH 2
#define EE 3
#define CAPITALS 4
#define KGUNITHA 5
#define NUMERALS
#define F_OTTU	7



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma data_seg(".SHARDAT")
static HWND ghWndMain = 0 ;
static HHOOK ghKeyHook = NULL ;
#pragma data_seg()

static HHOOK ghCallWndProcRetHook = NULL;

HINSTANCE ghInstance = 0;
HOOKPROC glpfnHookProc = 0;


char cConsonnants[10] = {'a','A','e','E','i','I','u','U','o','O'};
char cVot[24] = {'Q','W','R','T','Y','P','S','D','G','H','J','K','L','Z','C','X','C','V','B','N','M','<','_','^'};

struct val_tab
{
	char key;								//----holds the character 
	int k_val[6];							//---holds the glyph codes of the corresponding above character eg;  
											//---for a 67 (first 3 values)for vowel and 192 for vowels (last value)
}single_key[92] = {				//'`' , {33,-1},
								'!' , {33,-1},
   								'a' , {67,-1},
								'A' , {68,-1},
								'e' , {69,-1},
								'E' , {70,-1},
								'u' , {71,-1},
								'U' , {72,-1},
								'4' , {73,196,-1},
								'$' , {89,-1},
								'i' , {74,-1},
								'I' , {75,-1},
								'>' , {76,-1},
								'1' , {39,-1},
								'o' , {77,-1},
								'O' , {78,-1},
								'0' , {65,-1 },
								':' , {66,-1},
								'k' , {80,192,-1},
								'[' , {82,-1},
								'g' , {85,192,-1},
								'9' , {87,192,-1},
								'c' , {90,192,-1},
								'j' , {100,-1},
								'=' , {103,192,104,196,-1},
								't' , {108,-1},
								'5' , {111,192,-1},
								'%' , {215,-1},
								'd' , {113,192,-1},
								'z' , {116,-1},
								'w' , {118,192,-1},
								'3' , {120,192,-1},
								'#' , {220,-1},
								',' , {122,192,-1},
								'n' , {163,192,-1},
								'p' , {165,192,-1},
								'b' , {167,-1,-1},
								'm' , {170,192,196,-1},
								'y' , {65,105,192,196,-1},
								'r' , {103,192,-1},
								'l' , {174,-1},
								'v' , {170,192,-1},
								'q' , {177,192,-1},
								'\'', {181,192,-1},
								's' , {184,192,-1},
								'h' , {186,192,-1},
								'x' , {188,192,-1},
								'K' , {204,-1},
								'{' , {205,-1},
								'G' , {206,-1},
								'C' , {209,-1},
								'J' , {211,-1},
								'T' , {214,-1},
								'D' , {216,-1},
								'Z' , {218,-1},
								'W' , {219,-1},
							//	'?' , {221,-1},
								'N' , {223,-1},
								'P' , {224,-1},
								'B' , {226,-1},
								'M' , {228,-1},
								'Y' , {229,-1},
								'R' , {230,-1},
								'L' , {232,-1},
								'V' , {233,-1},
								'"' , {235,-1},
								'S' , {236,-1},
								'H' , {237,-1},
								'X' , {238,-1},
								';' , {195,-1},
								'Q' , {240,-1},
								'f' , {8,193,-1},
								']' , {-1,-1},
								'F' , {200,-1},
								'2' , {-1,-1},
								'6' , {107,-1},   //--------- --------//
								'^' , {213,-1},           //---------- -------//
								'7' , {170,192,197,-1},
								'8' , {165,192,197,-1},
								'-' , {98,192,-1},
								'_' , {210,-1},
								'(' , {207,-1},
								'<' , {221,-1},
								'?' , {63,-1},
								'/' , {47,-1},
							//	',' , {44,-1},
								'.' , {46,-1},
								'~' , {126,-1},
								'`' , {145,-1},
								'|' , {124,-1},
								'\\', {44,-1},
								'+' , {80,192,235,-1},
								'2' , {100,213,-1},
								')' , {0132,-1},
								'@' , {242,-1}
								
};

//-----singlekey_doubleglyph-----//
//---Structure of vowels ----//
struct double_ON_SLASH
{
	char key;								//----holds the character 
	int k_val[7];							//---holds the glyph codes of the corresponding above character eg; 
								   //---- for a 67 (first 3 values)for vowel and 192 for vowels (last value)
}double_key_slash[12] = {		

						'c' , {8,8,98,192,-1},
						'd' ,  {8,115,192,-1},
						',' , {8,115,192,-1},
						'p' , {8,115,192,-1},
						'b' , {8,168,115,192,-1},
						'<' , {8,222,-1},
						'8' , {8,8,115,192,197,-1},
						'D' , {8,217,-1},
						'B' , {8,227,-1},
						'P' , {8,225,-1},
						'<' , {8,222,-1},
						'C' , {8,210,-1}
						};
//-----singlekey_doubleglyph-----//
//---Structure of vowels ----//

struct double_ON_EE
{
	char key;								//----holds the character 
	int k_val[8];							//---holds the glyph codes of the corresponding above character eg; 
												//---- for a 67 (first 3 values)for vowel and 192 for vowels (last value)
}double_key_ee[32] = {		'k', {8,8,81,-1},
							'[', {8,84,-1},
							'g', {8,8,86,-1},
							'9', {8,8,88,-1},
							'c', {8,8,97,-1},
							'j', {8,102,-1},
							'=', {8,8,8,8,106,104,196,-1},
							't', {8,110,-1},
							'5', {8,8,112,-1},
							'd', {8,8,114,-1},
							'z', {194,-1},
							'w', {8,8,119,-1},
							'3', {8,8,121,-1},
							',', {8,8,162,-1},
							'n', {8,8,164,-1},
							'p', {8,8,166,-1},
							'b', {8,169,-1},
							'm', {8,8,8,171,196,-1},
							'y', {8,8,8,8,172,196,-1},
							'r', {8,8,106,-1},
							'l', {8,176,-1},
							'v', {8,8,171,-1},
							'q', {8,8,178,-1},
							'\'',{8,8,182,-1},
							's', {8,8,185,-1},
							'h', {8,8,187,-1} ,
							'x', {8,8,189,-1} ,
							'-', {8,8,99,-1} ,
							'+', {8,8,8,81,235,-1},
							'2', {8,8,102,213,-1},
	                        '6', {194,-1},
							'$', {194,-1}

};


struct double_ON_F
{
	char key;								//----holds the character 
	int k_val[8];							//---holds the glyph codes of the corresponding above character eg; 
												//---- for a 67 (first 3 values)for vowel and 192 for vowels (last value)
}double_key_F[22] = {
								'k' , {204,-1},
								'[' , {205,-1},
								'g' , {206,-1},
								'c' , {209,-1},
								'j' , {211,-1},
								't' , {214,-1},
								'd' , {216,-1},
								'z' , {218,-1},
								'w' , {219,-1},
								//'?' , {221,-1},
								'n' , {223,-1},
								'p' , {224,-1},
								'b' , {226,-1},
								'm' , {228,-1},
								'y' , {229,-1},
								'r' , {230,-1},
								'l' , {232,-1},
								'v' , {233,-1},
								'\'', {235,-1},
								's' , {236,-1},
								'h' , {237,-1},
								'x' , {238,-1},
	};
				
struct num_tab
{
	char key;								//----holds the character 
	int k_val[7];							//---holds the glyph codes of the corresponding above character eg; 
										   //---- for a 67 (first 3 values)for vowel and 192 for singlekey_doubleglyph (last value)
}numerals[43] = {				
				                '1', {49,-1,33,-1} ,            //---Kannada Character ka---//
				                '2', {50,-1,64,-1} ,			//---Kannada Character ga---//	
								'3', {51,-1,35,-1} ,			//---Kannada Character cha---//
								'4', {52,-1,36,-1},
								'5', {53,-1,37,-1} ,			//---Kannada Character dha---//
								'6', {54,-1,94,-1} ,			//---Kannada Character tha---//
								'7', {55,-1,38,-1} ,			//---Kannada Character da---//
								'8', {56,-1,42,-1} ,			//---Kannada Character na---//
								'9', {57,-1,40,-1} ,			//---Kannada Character pa---//
								'0', {48,-1,41,-1},
								'!', {33,-1,33,-1} ,            //---Kannada Character ka---//
				                '@', {64,-1} ,			//---Kannada Character ga---//	
								'#', {35,-1} ,			//---Kannada Character cha---//
								'$', {36,-1},
								'%', {37,-1} ,			//---Kannada Character dha---//
								'^', {94,-1} ,			//---Kannada Character tha---//
								'&', {38,-1} ,			//---Kannada Character da---//
								'*', {42,-1} ,			//---Kannada Character na---//
								'(', {40,-1} ,			//---Kannada Character pa---//
								')', {41,-1},
								'+', {43,-1},
								'=', {61,-1},
								'-', {45,-1},
								'_', {95,-1},
								'{', {123,-1},
								'}', {125,-1},
								'[', {91,-1},
								']', {93,-1},
								'|', {124,-1},
								'\\',{92,-1},
								':', {58,-1},
								';', {59,-1},
								'<', {60,-1},
								'>', {62,-1},
								'?', {63,-1},
								'/', {47,-1},
								',', {44,-1},
								'.', {46,-1},
								'~', {126,-1},
								'`', {96,-1},
								'e', {70,-1},
								'\'', {145,-1},
								'"' , {147,-1}
				};  

BEGIN_MESSAGE_MAP(CHemavathiApp, CWinApp)
	//{{AFX_MSG_MAP(CHemavathiApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHemavathiApp construction




//------------This-function-is-repeatedly-called-this-executes-when-a-key-is-pressed-on-the-keyboard---/
LRESULT EXPORTED_DLL_FUNCTION kbdHookProc_Hemavathi(int nCode,WPARAM wParam,LPARAM lParam)
{

if(nCode<0)												//---Do not process further if a system key is pressed---//
{ 
	return CallNextHookEx (ghKeyHook,nCode,wParam,lParam);   //---Call the next hook procedure in the hook chain---//
}
if(nCode==HC_NOREMOVE)
{
		return CallNextHookEx (ghKeyHook,nCode,wParam,lParam); 
}

			char ch;
			BYTE ks[256];                                //---a byte for getting the keyboard ststus---//
		    WORD w;										 //---a word for holding the character value of the key---// 
														 //pressed used by the ToAsccii where the value is set into this---//	
			UINT scan=0; 					
		    ::GetKeyboardState(ks);         
			::ToAscii(wParam,scan,ks,&w,0);
            ch = char(w);
LRESULT retval;

	if( isspace(ch) || wParam == VK_BACK)
	{
		vClear_All_Flags();
		kFlag.c_bit = FALSE;
		kFlag.found = FALSE;
		kFlag.s_bit = TRUE;
		kFlag.previous_0 = NULL;
	}

	

	if((GetKeyState(VK_SCROLL ) & 0x0001))
	{
		if(isnumpad(wParam))
		{
			return CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
		}
		if((isalpha(ch) || ispunct(ch) || isdigit(ch)))											 //---If key is pressed and is not a control key---//
		{
			if((lParam & 0x80000000) == 0x00000000)   //---If key is pressed and is not a control key---//
			{
				FindCharacters(ch);									//---Find the glyph code--//
				PushBackspaces();
			}
			else // key released
			{
			    PushKeys();
				retval = TRUE;
			}
		}
		else
		{
			retval = CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
			  //---Call the next hook procedure in the hook chain---//
		}


		if( (isalnum(ch) || ispunct(ch)) &&!(GetKeyState(VK_MENU) & 0x80))    //---If the key pressed is a alpha key and when not
		{                                                  //---- Alt is down posts only the the promted message--//
			 retval = TRUE;
		}
		else
		{
			retval = CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
			  //---Call the next hook procedure in the hook chain---//
		}

	}
	else 
		return CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
	if( ch == '.' ||  ch == '?' || ch == '!' || ch == '\\' || ch == '`' || ch == '|' || ch == '~') 
	{
//		vClear_All_Flags();
		kFlag.c_bit = FALSE;
//		kFlag.found = FALSE;
//		kFlag.s_bit = FALSE;
	//	kFlag.previous_0 = NULL;

	}
		return retval;
}



LRESULT EXPORTED_DLL_FUNCTION callWndRetProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	if(nCode<0)
	{
		return CallNextHookEx(ghCallWndProcRetHook,nCode,wParam,lParam);
	}

	CWPRETSTRUCT *p=(CWPRETSTRUCT*)lParam;
	if(p->message==WM_KEYDOWN)
	{
		if(p->wParam==VK_BACK)
		{
			PushKeys();
		}
	}
		LRESULT ret=CallNextHookEx(ghCallWndProcRetHook,nCode,wParam,lParam);

	return ret;
}


//---------------Insatalls-the-Hook---//---This-is -called-by-the-.exe---//
BOOL EXPORTED_DLL_FUNCTION InstallKeyboardHook_Hemavathi (HWND hWnd) 
{
   BOOL bSuccess = FALSE;
    if( !ghKeyHook) 
	{
		ghWndMain = hWnd;
		glpfnHookProc = (HOOKPROC) kbdHookProc_Hemavathi;
       bSuccess = (NULL != ( ghKeyHook = ::SetWindowsHookEx (WH_KEYBOARD, glpfnHookProc,ghInstance, NULL)));
		bSuccess = TRUE;
		  ghCallWndProcRetHook = ::SetWindowsHookEx (WH_CALLWNDPROCRET, (HOOKPROC)callWndRetProc,ghInstance, NULL);
		
	}
	return bSuccess;
}


//---------------Un-Insatalls-the-Hook---//---This-is -called-by-the-.exe---//
BOOL EXPORTED_DLL_FUNCTION DeInstallKeyboardHook_Hemavathi()
{
	if(ghKeyHook) 
	{
		if( TRUE == (0 != ::UnhookWindowsHookEx (ghKeyHook)))
		{
			ghKeyHook = NULL;
		}
	}
	if(ghCallWndProcRetHook) 
	{
		if( TRUE == (0 != ::UnhookWindowsHookEx (ghCallWndProcRetHook)))
		{
			ghCallWndProcRetHook = NULL;
		}
		
	}
   return (NULL == ghKeyHook);
}


CHemavathiApp::CHemavathiApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHemavathiApp object

CHemavathiApp theApp;



BOOL CHemavathiApp::InitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ghInstance = AfxGetInstanceHandle();
	return TRUE;

}


int CHemavathiApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	DeInstallKeyboardHook_Hemavathi();

	return CWinApp::ExitInstance();
}

BOOL CHemavathiApp::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
		return CWinApp::PreTranslateMessage(pMsg);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function Finds The Character in The Tables in Found Calls     /////////////////////////////
/////////////////////////////  The Display Functions With Position (i),and The Starting Position  /////////////////////////////
/////////////////////////////  Of The Of The Message To Be Posted The Argument 					  /////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FindCharacters(char ch) 
{       
   
	int no_bs = 0;//-------number of back spae--------//
	BOOL bHandledKeystroke = FALSE;
    kFlag.found = 0;
	no_bs = kFlag.o_count;
	kFlag.o_bit = FALSE;

	for(int i=0;i<24;i++)
	{
		if(ch == cVot[i])
		{   
			kFlag.o_bit = TRUE;
			if(kFlag.ei_bit == TRUE)
			{
				kFlag.ei_bit = FALSE;  // for second vottakshara
				DisplaySingleCharacter(246);
				if(ch == 'R')
				{
					DisplaySingleCharacter(231);
					return bHandledKeystroke;
				}

			}
			if(kFlag.f_bit == TRUE)
			{
				kFlag.f_bit = 0;
				kFlag.ei_bit = TRUE; // for second vottakshara
				
				if(ch == 'R')
				{
					DisplaySingleCharacter(231);
					return bHandledKeystroke;
				}
				DisplaySingleCharacter(246);
			}
			else
			{
				kFlag.f_bit = TRUE;
			}
		}
	}
	if(kFlag.o_bit == FALSE)
	{
		kFlag.f_bit = FALSE;
		kFlag.ei_bit = FALSE;
	}
	if(kFlag.s_bit == TRUE)
	{
		kFlag.s_bit = FALSE;
/*		if(ch == '>')
		{
			kFlag.found = TRUE;
			DisplayDoubleCharacter(100,213);
			CopyPrevious(ch);
			return bHandledKeystroke ;
		}
		for(int i=0;i<43;i++)
		{
			if(ch == numerals[i].key)
			{
				kFlag.found = TRUE;
				DisplaySingleCharacter(numerals[i].k_val[0]);
				return bHandledKeystroke ;
			}
		}*/
	}

if(kFlag.found == FALSE)
{

	if(ch == 'I')
	{
		for(int i = 0;i<24;i++)
		{
			if(cVot[i] == kFlag.previous_0)
			{
			DisplayDoubleCharacter(246,202);

				return bHandledKeystroke;
			}
		}
	}
	if(ch == 'F')
	{
		for(int i = 0;i<24;i++)
		{
			if(cVot[i] == kFlag.previous_0)
			{
			DisplaySingleCharacter(248);

				return bHandledKeystroke;
			}
		}
	}
   for(int i = 0;i<24;i++)
		{
			if(cVot[i] == ch && kFlag.previous_0 == '+' || kFlag.previous_0 == '=')
			{
				DisplaySingleCharacter(246);
				//return bHandledKeystroke;
			}
		}
	if(ch == 'e' && kFlag.previous_0 == '}' && kFlag.previous_1 == 'j')
	{
		SendBackSpace(2);
		DisplayDoubleCharacter(102,251);
		kFlag.found = TRUE;

	}
	else
	if(ch == 'O' && kFlag.previous_0 == 'o')
	{
		SendBackSpace(1);
		DisplaySingleCharacter(79);
		kFlag.found = TRUE;
	}
/*	else
	if(ch == 'f' && kFlag.previous_0 == '2')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(2);
	   DisplayTripleCharacter(101,193,213);
   }
   else*/
   if((ch == 'f' && kFlag.previous_0 == '7') )
   {
	   kFlag.found = TRUE;
	   SendBackSpace(1);
	   DisplaySingleCharacter(199);
   }
   else
   if(ch == 'f' && kFlag.previous_0 == 'e' && kFlag.previous_1 == 'm')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(2);
	   DisplayDoubleCharacter(171,198);
   }
   else
   if( (ch == 'f' && kFlag.previous_0 == '8') || ch == 'f' && kFlag.previous_0 == '/' && kFlag.previous_1 == '8')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(1);
	   DisplaySingleCharacter(199);
   }
 /*  else
   if(ch == 'f' && kFlag.previous_0 == 'u' && kFlag.c_bit == TRUE)
   {
	   kFlag.found = TRUE;
	   kFlag.c_bit = FALSE;
	   SendBackSpace(1);
	   DisplaySingleCharacter(198);
   }*/
   else 
   if(ch == 'e' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'd')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(3);
	   DisplayDoubleCharacter(114,115);
   }
   else
   if(ch == 'e' && kFlag.previous_0 == '/' && kFlag.previous_1 == ',')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(3);
	   DisplayDoubleCharacter(162,115);
   }
   else
   if(ch == 'e' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'p')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(3);
	   DisplayDoubleCharacter(166,252);
	   kFlag.lastglyph = TRUE;
   }
   else
   if(kFlag.lastglyph == TRUE)
   {
	   kFlag.found = TRUE;
	   //SendBackSpace(1);
	   DisplaySingleCharacter(251);
	   kFlag.lastglyph = FALSE;
   }
   else
   if(ch == 'e' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'b')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(3);
	   DisplayDoubleCharacter(169,252);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'C')/// for 200 ie votersuli
   {
	   kFlag.found = TRUE;
	 //  SendBackSpace(1);
	   DisplaySingleCharacter(200);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'D')
   {
	   kFlag.found = TRUE;
	   //SendBackSpace(1);
	   DisplaySingleCharacter(200);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '/' && kFlag.previous_1 == ',')
   {
	   kFlag.found = TRUE;
	  // SendBackSpace(1);
	   DisplaySingleCharacter(200);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'P')
   {
	   kFlag.found = TRUE;
	  // SendBackSpace(1);
	   DisplaySingleCharacter(200);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'B')
   {
	   kFlag.found = TRUE;
	  // SendBackSpace(1);
	   DisplaySingleCharacter(200);
   }
   else
   if(ch == 'e' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'c')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(2);
	   DisplaySingleCharacter(99);
   }
   else
 if(ch == '/' && kFlag.previous_0 == 'j')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(1);
	   DisplaySingleCharacter(212);
   }
   else
   if(ch == '}' && kFlag.previous_0 == 'o')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(1);
	   DisplaySingleCharacter(208);
   }
   else
   if(ch == '/' && kFlag.previous_0 == 'q')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(1);
	   DisplaySingleCharacter(234);
   }
   else
if(ch == '}' && kFlag.previous_0 == '/' &&kFlag.previous_1 == 'p')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(1);
	   DisplayDoubleCharacter(243,192);
   }
   else
if(ch == '}' && kFlag.previous_0 == 'j' )
   {
	   kFlag.found = TRUE;
	   //SendBackSpace(1);
	   DisplaySingleCharacter(243);
   }
   else
 /* if(ch == 'F' && kFlag.previous_0 == '=')
	{
		SendBackSpace(4);
		DisplaySingleCharacter(212);
	}
	else
	if(ch == 'F' && kFlag.previous_0 == '5')
	{
		SendBackSpace(2);
		DisplaySingleCharacter(215);   
	}
	else
	if(ch == 'F' && kFlag.previous_0 == '3')
	{
		SendBackSpace(2);
		DisplaySingleCharacter(220);
	}
   else*/
   if(ch == '/')
   {
	   for(int i=0;i<12;i++)
	   {
			if(kFlag.previous_0 == double_key_slash[i].key)
			{
				kFlag.found = TRUE;
				DisplayCharacters(i,SLASH,0);
			}
	   }

   }
  /*    
  else		// display the ottakshara of the previuously pressed key
  if(ch == 'F' && kFlag.c_bit == TRUE)
   {
	   for(int i=0;i<22;i++)
	   {
			if(kFlag.previous_0 == double_key_F[i].key)
			{
				kFlag.found = TRUE;
				DisplayCharacters(i,F_OTTU,0);
			}
	   }

   }
   else
   if(ch == 'e' || ch == ';')
   {
	   if(kFlag.s_bit == TRUE)
	   {
		   DisplaySingleCharacter(70);
		   kFlag.found = TRUE;
		   kFlag.s_bit = FALSE;
	   }
	   else
	   for(int i=0;i<28;i++)
	   {
			if(kFlag.previous_0 == double_key_ee[i].key)
			{
				kFlag.found = TRUE;
				DisplayCharacters(i,EE,0);
				if(ch == ';')
		        DisplaySingleCharacter(195); //only when gudisu is to bo displayed 
			}
	   }
	   
   }
}// kFlag.found == FALSE*/
   else
   if(ch == 'e' || ch == ';' )
   {
	   if(kFlag.s_bit == TRUE)
	   {
		   DisplaySingleCharacter(70);
		   kFlag.found = TRUE;
		   kFlag.s_bit = FALSE;
		   kFlag.c_bit = FALSE;
	   }
	   else
		   if(ch == ';')
		   {
			 if(kFlag.previous_0 == '/' && kFlag.previous_1 == 'p')
				{
                    kFlag.found = TRUE;
					SendBackSpace(3);
					DisplayTripleCharacter(166,252,195);
				}
			 if(kFlag.previous_0 == '/' && kFlag.previous_1 == 'c')
				{
                    kFlag.found = TRUE;
					SendBackSpace(3);
					DisplayDoubleCharacter(99,195);
				}
			 if(kFlag.previous_0 == '/' && kFlag.previous_1 == ',')
				{
                    kFlag.found = TRUE;
					SendBackSpace(3);
					DisplayTripleCharacter(162,252,195);
				}
			 if(kFlag.previous_0 == '/' && kFlag.previous_1 == 'd')
				{
                    kFlag.found = TRUE;
					SendBackSpace(3);
					DisplayTripleCharacter(114,252,195);
				}
			 if(kFlag.previous_0 == '/' && kFlag.previous_1 == 'b')
				{
                    kFlag.found = TRUE;
					SendBackSpace(3);
					DisplayTripleCharacter(169,252,195);
				}
			 kFlag.c_bit = FALSE;//----------dont use further next if vowel display vowel
		   }
	   if(kFlag.found == FALSE)
	   for(int i=0;i<32;i++)
	   {
			if(kFlag.previous_0 == double_key_ee[i].key)
			{
				kFlag.found = TRUE;
				DisplayCharacters(i,EE,0);
				if(ch == ';')
		        DisplaySingleCharacter(195); //only when gudisu is to bo displayed 
				kFlag.c_bit = FALSE;		
			}
	   }
   }
}

if(kFlag.found == FALSE)
{
	for(int i=0;i<92;i++)
	{
		if(ch == single_key[i].key)
		{
			kFlag.last_consonant = FALSE;
			kFlag.found = TRUE;

			if( (ch == 'f' || 
				 ch == 'u' ||
				 ch == 'U' || 
				 ch == 'I' || 
				 ch == 'i' || 
				 ch == 'o' || 
				 ch == 'O' || 
				 ch  == ']' 
				) &&   kFlag.c_bit == TRUE)
			{
					kFlag.c_bit = FALSE;
					vDisplayGunitakshara(ch);
					
			}
			else
			DisplayCharacters(i,SINGLE,0);


			for (int j = 0;j<10;j++)
			{
				if(ch == cConsonnants[j])
				{
					kFlag.u_bit = TRUE;
				}
			}

			if(kFlag.u_bit == FALSE )
			{
				kFlag.c_bit = TRUE;
			}
			else
			{
			    kFlag.u_bit = FALSE;
			}
		}
	}
}

if( isalpha(ch) || ispunct(ch) || isdigit(ch) )
CopyPrevious(ch);

kFlag.s_bit = FALSE;
return bHandledKeystroke;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function Finds The Character in The Tables in Found Calls     /////////////////////////////
/////////////////////////////  The Display Functions With Position (i),and The Starting Position  /////////////////////////////
/////////////////////////////  Of The Of The Message To Be Posted The Argument 					  /////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void DisplayCharacters(int nval,int indicator,int j)   //indictor value is 0 for anuswara ,1 for consonants , 2 for vowels
{    
			int k = j ;   // --------index for glyph codes---// 
			


		while(kFlag.n_back>=1)
			{
				AddKey(VK_BACK);
				kFlag.n_back--;
			}
		   if(indicator==SINGLE)	
			{
				while(single_key[nval].k_val[k]!=-1)
				{
						AddKey(single_key[nval].k_val[k]);
						k++;
				}
			}
		    else
		    if(indicator == SLASH)
			{
				while(double_key_slash[nval].k_val[k]!=-1)
				{
					   
						AddKey(double_key_slash[nval].k_val[k]);
						k++;
				}
			
			}
			else
		    if(indicator == EE)
			{
				while(double_key_ee[nval].k_val[k]!=-1)
				{
					  
						AddKey(double_key_ee[nval].k_val[k]);
						k++;
				}
			
			}
			else
		    if(indicator == F_OTTU)
			{
				while(double_key_F[nval].k_val[k]!=-1)
				{
					  
						AddKey(double_key_F[nval].k_val[k]);
						k++;
				}
			
			}
			
			kFlag.n_back = -1;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function Set The Glypha For Kha,ja,.... ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ch ===>character , gval ===> pevious_0 GlypH value//
void SetGlyphs(char ch,int gval)
{

	if(kFlag.previous_0 == '}')
	{
		SendBackSpace(2);
		DisplayDoubleCharacter(gval+1,243);
	}
	switch(kFlag.previous_0)
	{
	case '[' :
	case 'j' :	
	case 't' :
	case 'b' :
	case 'l' :
	case 'z' :
			 SendBackSpace(1);
			 DisplaySingleCharacter(gval+1);
	break;		 
	default :
	break; 
	
	}
	kFlag.n_back = -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function Set The Glypha For ma,JHa,ya.... ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ch ===>character , gval ===> pevious_0 GlypH value//
void SetGlyphs_for_jmy(char ch,int i)
{
		switch(kFlag.previous_0)
		{
		case 'y' :				//-----------For The Characters ya,ma-----------//
		case 'm' :
			switch(ch)
			{
				case 'f' :
				SendBackSpace(1);
				DisplayDoubleCharacter(105,193);
				break;
				case 'i' :
					SendBackSpace(2);
					DisplayDoubleCharacter(201,196);
				break;
				case 'I' :
					SendBackSpace(2);
					DisplayTripleCharacter(201,196,202);
				break;
				case 'o' :
					SendBackSpace(2);
					DisplayDoubleCharacter(201,198);
				break ;
				case  'O' :
					SendBackSpace(1);
					DisplayDoubleCharacter(105,203);
				break;

				case  ']' :
					SendBackSpace(1);
					DisplayDoubleCharacter(105,239);
				break;

			}//---------End of Switch(ch)--for the characters ma,ya ------//
		 break; //---------------End of the case y , m instance 1
		 case '=' :				//-----------For The Characters JHA-----------//
			switch(ch)
			{
				case 'f' :
				    SendBackSpace(1);
					DisplayDoubleCharacter(105,193);
				break;
				case 'i' :
					SendBackSpace(3);
					DisplayTripleCharacter(201,104,196);
				break;
				case 'I' :
					SendBackSpace(3);
					DisplayTripleCharacter(202,104,196);
				break;
				case 'o' :
					SendBackSpace(3);
					DisplayTripleCharacter(201,104,198);
				break ;
				case  'O' :
					SendBackSpace(1);
					DisplayDoubleCharacter(105,203);
				break;
				case  ']' :
					SendBackSpace(1);
					DisplayDoubleCharacter(105,239);
				break;
			}//-------------------End of Switch(ch)----for JHA ---------------//
		break ;
		}//---------End of Switch(pevious_0)--------//
		kFlag.slash_bit = 0;
kFlag.n_back = -1;
}//-------End OF The function SetGlyphs_for_jmy----------//

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function Set The Glypha For ma,JHa,ya.... ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ch ===>character , gval ===> pevious_0 GlypH value//
void SetGlyphs_for_kxha_gyna(char ch,int i)
{
		switch(kFlag.previous_0)
		{
		case '+':				//-----------For The Characters ya,ma-----------//
			switch(ch)
			{
				case 'f' :
					SendBackSpace(2);
					DisplayDoubleCharacter(193,235);
				break;

				case 'u' :
					SendBackSpace(2);
					DisplayDoubleCharacter(196,235);
				break;

				case 'U' :
					SendBackSpace(2);
					DisplayDoubleCharacter(198,235);
				break;

				case 'e' :
					SendBackSpace(2);
					DisplayDoubleCharacter(81,235);
				break;

				case 'i' :
					SendBackSpace(2);
					DisplayDoubleCharacter(201,235);
				break;
				case 'I' :
					SendBackSpace(2);
					DisplayFourCharacter(201,235,246,202);
				break;

				case 'o' :
					SendBackSpace(2);
					DisplayTripleCharacter(201,198,235);
				break ;

				case  'O' :
					SendBackSpace(2);
					DisplayDoubleCharacter(203,235);
				break;
				case  ']' :
					//SendBackSpace(1);
					DisplaySingleCharacter(239);
				break;
			}//---------End of Switch(ch)--for the characters ma,ya ------//
		 break; //---------------End of the case y , m instance 1Á
		 case '2' :				//-----------For The Characters JHA-----------//
			switch(ch)
			{
				case 'f' :
				    SendBackSpace(2);
					DisplayTripleCharacter(101,193,213);
				break;

				case 'u' :
					SendBackSpace(2);
					DisplayDoubleCharacter(196,213);
				break;

				case 'U' :
					SendBackSpace(2);
					DisplayDoubleCharacter(198,213);
				break;
				case 'e' :
					SendBackSpace(2);
					DisplayDoubleCharacter(102,213);
				break;

				case 'i' :
					SendBackSpace(2);
					DisplayTripleCharacter(101,201,213);
				break;
				case 'I' :
					SendBackSpace(3);
					DisplayTripleCharacter(101,202,213);
				break;

				case 'o' :
					SendBackSpace(2);
					//DisplayFourCharacter(101,201,198,213);
					DisplayFourCharacter(201,235,246,202);
				break ;

				case  'O' :
					SendBackSpace(2);
					DisplayTripleCharacter(101,203,213);
				break;
				case  ']' :
					//SendBackSpace(1);
					DisplaySingleCharacter(239);
				break;

			}//-------------------End of Switch(ch)----for JHA ---------------//
		break ;
		}//---------End of Switch(pevious_0)--------//
		kFlag.slash_bit = 0;
kFlag.n_back = -1;
}//-------End OF The function SetGlyphs_for_kxha_Gyna----------//


void SetGlyphs_nya_inya(char ch,int i)
{
			switch(ch)
			{
				case 'f' :
		//			SendBackSpace(2);
					DisplaySingleCharacter(193);
				break;

				case 'u' :
					//SendBackSpace(2);
					DisplaySingleCharacter(196);
				break;

				case 'U' :
					DisplaySingleCharacter(198);
				break;

				case 'e' :
					DisplaySingleCharacter(194);
				break;

				case 'i' :
					DisplaySingleCharacter(201);
				break;
				case 'I' :
					DisplayDoubleCharacter(201,202);
				break;

				case 'o' :
					DisplayDoubleCharacter(201,198);
				break ;

				case  'O' :
					DisplaySingleCharacter(203);
				break;
			}//---------End of Switch(ch)--for the characters ma,ya ------//
}// end of SetGlyphs_nya_inya

void SetGlyphs_BA_CA(char ch,int i)
{
		switch(kFlag.previous_1)
		{
		case 'c':				//-----------For The Characters ya,ma-----------//
			switch(ch)
			{
				case 'f' :
					SendBackSpace(1);
					DisplaySingleCharacter(193);
				break;

				case 'u' :
				//	SendBackSpace(2);
					DisplaySingleCharacter(196);
				break;

				case 'U' :
					//SendBackSpace(2);
					DisplaySingleCharacter(198);
				break;

				case 'e' :
					SendBackSpace(2);
					DisplaySingleCharacter(99);
				break;

				case 'i' :
					SendBackSpace(1);
					DisplaySingleCharacter(201);
				break;
				case 'I' :
					SendBackSpace(1);
					DisplayDoubleCharacter(201,202);
				break;

				case 'o' :
					SendBackSpace(1);
					DisplayDoubleCharacter(201,198);
				break ;

				case  'O' :
					SendBackSpace(1);
					DisplaySingleCharacter(203);
				break;
			}//---------End of Switch(ch)--for the characters ma,ya ------//
		 break; //---------------End of the case y , m instance 1Á
	}//---------End of Switch(pevious_0)--------//
		kFlag.slash_bit = 0;
kFlag.n_back = -1;

}
void CopyPrevious(char ch)
{   
	kFlag.previous_1 = kFlag.previous_0;
	kFlag.previous_0 = ch;
}



void vDisplayGunitakshara(char ch)
{

	kFlag.c_bit = FALSE; //no gunitakshara for next character
	switch(ch)
	{
	case 'u':
		switch(kFlag.previous_0)
		{
		case '+':
		case '2':
			SetGlyphs_for_kxha_gyna(ch,1);
		return ;
		default :
			if(kFlag.previous_0 == 'p' || kFlag.previous_0 == 'v' || kFlag.previous_0 == 'h')
				DisplaySingleCharacter(197);
			else
			if(kFlag.previous_0 == '/' && kFlag.previous_1 == 'p')
				DisplaySingleCharacter(197);
			else
		DisplaySingleCharacter(196);
		}
	break;

	case 'U':
		switch(kFlag.previous_0)
		{
		case '+':
		case '2':
			SetGlyphs_for_kxha_gyna(ch,1);
		return ;

		default:
			if(kFlag.previous_0 == 'p' || kFlag.previous_0 == 'v' || kFlag.previous_0 == 'h')
				DisplaySingleCharacter(199);
			else
			if(kFlag.previous_0 == '/' && kFlag.previous_1 == 'p')
				DisplaySingleCharacter(199);
			else
		DisplaySingleCharacter(198);
		}
	break;

	case 'f' :
		switch(kFlag.previous_0)
		{
		case '}' :
			SetGlyphs(ch,100);
			break;
		case '[' :
			SetGlyphs(ch,82);
			break;
		case 'j' :	
			SetGlyphs(ch,100);
			break;
		case 't' :
			SetGlyphs(ch,108);
			break;
		case 'b' :
			SetGlyphs(ch,167);
		break;
		case 'l' :
			SetGlyphs(ch,174);
		break;

		case '$' :
		case '6' :
			SetGlyphs_nya_inya(ch,1);
		return;

		case 'z' :
		 	SetGlyphs(ch,116);
		break;
	
		case '+':
		case '2':
			SetGlyphs_for_kxha_gyna(ch,1);
		return;

//		case '/' :
//			::MessageBox(NULL,"sdc","csdc",MB_OK);
//				SetGlyphs_BA_CA(ch,1);
//		return ;

		case '=' :
		case 'y' :
		case 'm' :
			SetGlyphs_for_jmy(ch,1);
		return;
	
	 default :
			SendBackSpace(1);
		}
		DisplaySingleCharacter(193);
	break;
  
   case 'o':
   switch(kFlag.previous_0)
	{
	   		case '}' :
			SetGlyphs(ch,100);
			break;
	case '[' :
			SetGlyphs(ch,82);
			break;
		case 'j' :	
			SetGlyphs(ch,100);
			break;
		case 't' :
			SetGlyphs(ch,108);
			break;
		case 'b' :
			SetGlyphs(ch,167);
		break;
		case 'l' :
			SetGlyphs(ch,174);
			break;
		case '$' :
		case '6' :
			SetGlyphs_nya_inya(ch,1);
		return;

			SetGlyphs(ch,174);
		break;

			
		case 'z' :
			SetGlyphs(ch,116);
		break;
		case '+':
		case '2':
		SetGlyphs_for_kxha_gyna(ch,1);
		return;
		case 'y' :
		case 'm' :
		case '=' :
			SetGlyphs_for_jmy(ch,1);
			return ;
		
//		case '/' :
//		SetGlyphs_BA_CA(ch,1);
//		return ;

         
		default :
			if(kFlag.previous_0 == 'p' || kFlag.previous_0 == 'v' || kFlag.previous_0 == 'h')
			{
				SendBackSpace(1);
				DisplayDoubleCharacter(201,199);
				return ;
			}
			else
			if(kFlag.previous_0 == '/' && kFlag.previous_1 == 'p')
			{
				SendBackSpace(1);
				DisplayDoubleCharacter(201,199);
				return ;
			}
			else
			{	
			 SendBackSpace(1);
			 }
		}
		DisplayDoubleCharacter(201,198);
	break;

	case 'O':
		switch(kFlag.previous_0)
		{
					case '}' :
			SetGlyphs(ch,100);
			break;
		case '[' :
			SetGlyphs(ch,82);
			break;
		case 'j' :	
			SetGlyphs(ch,100);
			break;
		case 't' :
			SetGlyphs(ch,108);
			break;
		case 'b' :
			SetGlyphs(ch,167);
		break;
		case 'l' :
			SetGlyphs(ch,174);
			break;
		case '$' :
		case '6' :
			SetGlyphs_nya_inya(ch,1);
		return;

				
		case 'z' :
			SetGlyphs(ch,116);
		break;
		
		case '+':
		case '2':
		SetGlyphs_for_kxha_gyna(ch,1);
		return;
		
		case 'y' :
		case 'm' :
		case '=' :
			SetGlyphs_for_jmy(ch,1);
		return ;
		
//		case '/' :
//		SetGlyphs_BA_CA(ch,1);
//		return ;

		
		default :
			SendBackSpace(1);
		}
		DisplaySingleCharacter(203);
	break;

	case 'I':
		switch(kFlag.previous_0)
		{
					case '}' :
			SetGlyphs(ch,100);
			break;
		case '[' :
			SetGlyphs(ch,82);
			break;
		case 'j' :	
			SetGlyphs(ch,100);
			break;
		case 't' :
			SetGlyphs(ch,108);
			break;
		case 'b' :
			SetGlyphs(ch,167);
		break;
		case 'l' :
			SetGlyphs(ch,174);
			break;
		case '$' :
		case '6' :
			SetGlyphs_nya_inya(ch,1);
		return;
		
		case 'z' :
			SetGlyphs(ch,116);
		break;

		case '+':
		case '2':
		SetGlyphs_for_kxha_gyna(ch,1);
		return;
		
		case 'y' :
		case 'm' :
		case '=' :
			SetGlyphs_for_jmy(ch,1);
		return ;
		 break;

//		case '/' :
//		SetGlyphs_BA_CA(ch,1);
//		return ;

		
		default :
			SendBackSpace(1);
		}
		DisplayDoubleCharacter(201,202);
		break;
		
		// to display eaatva//
	case 'i':
	switch(kFlag.previous_0)
		{
				case '}' :
			SetGlyphs(ch,100);
			break;
		case '[' :
			SetGlyphs(ch,82);
			break;
		case 'j' :	
			SetGlyphs(ch,100);
			break;
		case 't' :
			SetGlyphs(ch,108);
			break;
		case 'b' :
			SetGlyphs(ch,167);
		break;
		case 'l' :
			SetGlyphs(ch,174);
		break;
		case '$' :
		case '6' :
			SetGlyphs_nya_inya(ch,1);
		return;
		
		case 'z' :
			SetGlyphs(ch,116);
		break;

		case '+':
		case '2':
		SetGlyphs_for_kxha_gyna(ch,1);
		return;
		

		case 'y' :
		case 'm' :
		case '=' :
			SetGlyphs_for_jmy(ch,1);
			return ;

//		case '/' :
//		SetGlyphs_BA_CA(ch,1);
//		return ;
		
		
		default :
			SendBackSpace(1);
		}
		DisplaySingleCharacter(201);
		break;

	case ']': // ardakshara 
		switch(kFlag.previous_0)
		{
					case '}' :
			SetGlyphs(ch,100);
			break;
	case '[' :
			SetGlyphs(ch,82);
			break;
		case 'j' :	
			SetGlyphs(ch,100);
			break;
		case 't' :
			SetGlyphs(ch,108);
			break;
		case 'b' :
			SetGlyphs(ch,167);
		break;
		case 'l' :
			SetGlyphs(ch,174);
			break;
		case '$' :
		case '6' :
			SetGlyphs_nya_inya(ch,1);
		return;
		
		case 'z' :
			SetGlyphs(ch,116);
		break;

		case '+':
		case '2':
		SetGlyphs_for_kxha_gyna(ch,1);
		return;
		

		case 'y' :
		case 'm' :
		case '=' :
			SetGlyphs_for_jmy(ch,1);
			return ;

//		case '/' :
//		SetGlyphs_BA_CA(ch,1);
//		return ;

		
		default :
			SendBackSpace(1);
		}
		DisplaySingleCharacter(239);
		break;
	}
}


void ClearQueue()
{

}
