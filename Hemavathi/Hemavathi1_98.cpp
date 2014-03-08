// Hemavathi.cpp : Defines the initialization routines for the DLL.
//

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


char cConsonnants[10] = {'a','A','e','E','i','I','u','U','o','O' };


struct val_tab
{
	char key;								//----holds the character 
	int k_val[6];							//---holds the glyph codes of the corresponding above character eg;  
											//---for a 67 (first 3 values)for vowel and 192 for vowels (last value)
}single_key[80] = {		    	'a' , {67,-1} ,
								'A' , {68,-1},
								'e' , {69,-1},
								'E' , {100,213,-1},
								'u' , {71,-1},
								'U' , {72,-1},
								'4' , {73,196,-1},
								'i' , {74,-1},
								'I' , {75,-1},
								'>' , {76,-1},
								'1' , {215,-1},
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
								'd' , {113,192,-1},
								'z' , {116,-1},
								'w' , {118,192,-1},
								'3' , {120,192,-1},
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
								'?' , {221,-1},
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
								'6' , {112,-1},
								'7' , {170,192,197,-1},
								'8' , {165,192,197,-1},
								'-' , {98,192,-1},
								'_' , {210,-1},
								'(' , {207,-1},
								'<' , {221,-1},
								
};

//-----singlekey_doubleglyph-----//
//---Structure of vowels ----//
struct double_ON_SLASH
{
	char key;								//----holds the character 
	int k_val[7];							//---holds the glyph codes of the corresponding above character eg; 
								   //---- for a 67 (first 3 values)for vowel and 192 for vowels (last value)
}double_key_slash[8] = {		

						'c' , {8,8,98,192,-1},
						'd',  {8,115,192,-1},
						',' , {8,115,192,-1},
						'p' , {8,115,192,-1},
						'b' , {8,168,105,192,-1},
						'<' , {8,222,-1},
						'8' , {8,8,115,192,197,-1},
						};
//-----singlekey_doubleglyph-----//
//---Structure of vowels ----//

struct double_ON_EE
{
	char key;								//----holds the character 
	int k_val[8];							//---holds the glyph codes of the corresponding above character eg; 
												//---- for a 67 (first 3 values)for vowel and 192 for vowels (last value)
}double_key_ee[28] = {		'k', {8,8,81,-1},
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
							'-', {8,8,99,-1}
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
								'x' , {238,-1}
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


	if(isspace(ch))
	{
		kFlag.c_bit = FALSE;
		kFlag.found = FALSE;
		kFlag.s_bit = TRUE;
	}


	if((GetKeyState(VK_SCROLL ) & 0x0001))
	{
		if(isalpha(ch) || ispunct(ch) || isdigit(ch) )											 //---If key is pressed and is not a control key---//
		{
			//::MessageBox(NULL,"bgfbg","bgfbgfb",MB_OK);
			if((lParam & 0x80000000) == 0x00000000)   //---If key is pressed and is not a control key---//
			{
				FindCharacters(ch);									//---Find the glyph code--//
				PushBackspaces();
			}
			else // key released
			{
				PushKeys();
				return TRUE;
			}
		}

		if( (isalnum(ch) || ispunct(ch)) &&!(GetKeyState(VK_MENU) & 0x80))    //---If the key pressed is a alpha key and when not
		{                                                  //---- Alt is down posts only the the promted message--//
			 return TRUE;
		}
		else
		{
			return CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
			  //---Call the next hook procedure in the hook chain---//
		}

	}

		return CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
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



	if(kFlag.s_bit == TRUE)
	{
		kFlag.s_bit = FALSE;
		if(kFlag.previous_0 == '>')
		{
			kFlag.found = TRUE;
			DisplayDoubleCharacter(100,213);
			return bHandledKeystroke ;
		}
/*		for(int i=0;i<43;i++)
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
   if((ch == 'f' && kFlag.previous_0 == '7') )
   {
	   kFlag.found = TRUE;
	   SendBackSpace(1);
	   DisplaySingleCharacter(199);
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
   }
   else
   if(ch == 'e' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'b')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(3);
	   DisplayDoubleCharacter(169,252);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'C')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(1);
	   DisplaySingleCharacter(210);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'D')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(1);
	   DisplaySingleCharacter(217);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '/' && kFlag.previous_1 == ',')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(1);
	   DisplaySingleCharacter(222);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'P')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(1);
	   DisplaySingleCharacter(225);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'B')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(1);
	   DisplaySingleCharacter(227);
   }
   else
   if(ch == 'e' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'c')
   {
	   kFlag.found = TRUE;
	   SendBackSpace(2);
	   DisplaySingleCharacter(99);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '=')
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
   else
   if(ch == '/')
   {
	   for(int i=0;i<8;i++)
	   {
			if(kFlag.previous_0 == double_key_slash[i].key)
			{
				kFlag.found = TRUE;
				DisplayCharacters(i,SLASH,0);
			}
	   }

   }
  /*    else
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
	   }
	   else
	   for(int i=0;i<28;i++)
	   {
			if(kFlag.previous_0 == double_key_ee[i].key)
			{
				kFlag.found = TRUE;
				DisplayCharacters(i,EE,0);
			}
	   }
   }
}

if(kFlag.found == FALSE)
{
	for(int i=0;i<80;i++)
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
				) &&  
				 kFlag.c_bit == TRUE)
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

if((isalnum(ch))||(ispunct(ch))&&(!(GetKeyState(VK_SPACE))||!(GetKeyState(VK_SHIFT))))
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
	switch(kFlag.previous_0)
	{
	case '[' :
	case 'j' :	
	case 't' :
	case 'b' :
	case 'l' :
	
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
			}//-------------------End of Switch(ch)----for JHA ---------------//
		break ;
		}//---------End of Switch(pevious_0)--------//
		kFlag.slash_bit = 0;
kFlag.n_back = -1;
}//-------End OF The function SetGlyphs_for_jmy----------//




void CopyPrevious(char ch)
{   
	kFlag.previous_1 = kFlag.previous_0;
	kFlag.previous_0 = ch;
}



void vDisplayGunitakshara(char ch)
{
	switch(ch)
	{
	case 'u':
		DisplaySingleCharacter(196);
	break;
	case 'U':
		DisplaySingleCharacter(198);
	break;
	case 'f' :
		switch(kFlag.previous_0)
		{
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
		case 'y' :
		case 'm' :
		case '=' :
			SetGlyphs_for_jmy(ch,1);
			return ;
		default :
			SendBackSpace(1);
		}
		DisplayDoubleCharacter(201,198);
		break;
	case 'O':
		switch(kFlag.previous_0)
		{
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
		case 'y' :
		case 'm' :
		case '=' :
			SetGlyphs_for_jmy(ch,1);
			return ;
		default :
			SendBackSpace(1);
		}
		DisplaySingleCharacter(203);
		break;
	case 'I':
		switch(kFlag.previous_0)
		{
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
		case 'y' :
		case 'm' :
		case '=' :
			SetGlyphs_for_jmy(ch,1);
			return ;
		 break;
		default :
			SendBackSpace(1);
		}
		DisplayDoubleCharacter(201,202);
		break;
		// to display aatva//
		case 'i':
	switch(kFlag.previous_0)
		{
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
		case 'l' :
			SetGlyphs(ch,117);
			break;
		
		case 'y' :
		case 'm' :
		case '=' :
			SetGlyphs_for_jmy(ch,1);
			return ;
		default :
			SendBackSpace(1);
		}
		DisplaySingleCharacter(201);
		break;

	case ']':
		switch(kFlag.previous_0)
		{
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
		case 'y' :
		case 'm' :
		case '=' :
			SetGlyphs_for_jmy(ch,1);
			return ;
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
