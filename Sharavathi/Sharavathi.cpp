// Sharavathi.cpp : Defines the initialization routines for the DLL.

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
#include "Sharavathi.h"
#include "..\headers\keyfuncts.h"
#include "..\headers\flags.h"
#include <windows.h>
#include <vector>

#define ANUSWARA 0
#define VOWELS 1
#define CONSONANTS 2

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

HINSTANCE ghInstance=0;
HOOKPROC glpfnHookProc=0;

HWND      myWnd;
int valr = 0;
int vk_flag = 1;
int oqueue[10] ={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
//---Structure of anuswara and visarga----//
struct anv_tab
{
	char key;								//----holds the character 
	int k_val[3];							//---holds the glyph codes of the corresponding above character eg; 
											//---for a 67 (first 3 values)for vowel and 192 for consonants (last value)
}anuswaranvisarga[3] = { '\0', {-1,-1},
	                     'M', {65,-1,-1 } ,
			             'H', {66,-1,-1 } ,
						 
};

//---Structure of vowles ----//
struct val_tab
{
	char key;								//----holds the character 
	int k_val[11];							//---holds the glyph codes of the corresponding above character eg;  
											//---for a 67 (first 3 values)for vowel and 192 for consonants (last value)
}vowels[17] =  {  'A', { 67, -1,-1,-1,-1,-1,-1,- 1,-1,-1} ,        
				  'a', { 68, -1,-1,193,-1 ,-1,-1,-1,-1 } ,
				  'i', { 69, -1,-1, -1,-1 ,-1,-1,-1,-1 } ,
				  'I', { 70, -1,-1, 195,-1 ,-1,-1,-1 ,-1} ,
				  'u', { 71, -1,-1,196,-1 ,-1,-1,197 ,-1} , 
				  'U', { 72, -1,-1,198,-1,-1,-1,199 ,-1} ,
				  '~', { 73,196,-1,-1,-1,-1,-1,-1,-1} ,
				  'e', { 74, -1,-1,201,-1 ,-1,-1,-1 ,-1} ,
				  'z', { 75, -1,-1,201,195 ,-1,-1 ,-1} ,
				  'Y', { 76, -1,-1,201,202,-1,-1  ,-1} ,			//--e+~----//
				  'o', { 77, -1,-1,201,198 ,-1,-1 ,201,199,-1} ,
				  'Z', { 78, -1,-1,201,198 ,195,-1,201,199,195,-1} , //---O----//
				  'V', { 79, -1,-1,203,-1,-1,-1,-1 ,-1} ,
				  'E', {-1,-1,-1,201,195,-1},
				  'O', {-1,-1,-1,201,198,195,-1,201,199,195,-1} ,
				  'R', {240,-1}
};


//---Structure of consonants ----//
struct con_tab
{
	char key;								//----holds the character 
	int k_val[7];							//---holds the glyph codes of the corresponding above character eg; 
										    //---- for a 67 (first 3 values)for vowel and 192 for consonants (last value)
}consonants[35] = { 'k', {80,192,-1,-1,-1,204 ,-1} ,            //---Kannada Character ka---//
				    'K', {82,-1,-1,-1,-1,205 ,-1} ,				//---Kannada Character Kha---//	
					'g', {85,192,-1,-1,-1,206 ,-1} ,			//---Kannada Character ga---//	
					'G', {87,192,-1,-1,-1,207,-1 } ,			//---Kannada Character Gha---//
					'c', {90,192,-1,-1,-1,209 ,-1} ,			//---Kannada Character cha---//	
					'C', {98,192,-1,-1,-1,210 ,-1} ,		    //---Kannada Character CHA---//
					'j', {100,-1,-1,-1,-1,211,-1 } ,			//---Kannada Character ja---//	
					'J', {103,192,104,196,-1,212,-1 } ,	        //---Kannada Character Jha---//  
				    'q', {108,-1,-1,-1,-1,214 ,-1} ,			//---Kannada Character Ta---//
					'Q', {111,192,-1,-1,-1,215 ,-1} ,			//---Kannada Character TA---//
					'w', {113,192,-1,-1,-1,216,-1 } ,			//---Kannada Character dha---//
					'W', {113,115,192,-1,-1,217 ,-1} ,			//---Kannada Character DHA---//
					'N', {116,-1,-1,-1,-1,218,-1 } ,			//---Kannada Character NA---//
					't', {118,192,-1,-1,-1,219 ,-1} ,			//---Kannada Character tha---//
					'T', {120,192,-1,-1,-1,220 ,-1} ,			//---Kannada Character THA---//
					'd', {122,192,-1,-1,-1,221 ,-1} ,			//---Kannada Character da---//
					'D', {122,115,192,-1,-1,222,-1 } ,			//---Kannada Character DA---//
					'n', {163,192,-1,-1,-1,223 ,-1} ,			//---Kannada Character na---//
					'p', {165,192,-1,-1,-1,224,-1} ,			//---Kannada Character pa---//
					'P', {165,115,192,-1,-1,225 ,-1} ,			//---Kannada Character PHA---//
					'b', {167,-1,-1,-1,-1,226 ,-1} ,			//---Kannada Character ba---//
					'B', {168,115,192,-1,-1,227,-1 } ,			//---Kannada Character BHA---//
					'm', {170,192,196,-1,-1,228 ,-1} ,			//---Kannada Character Ma---//	
					'y', {65,105,192,196,-1,229,-1 } ,          //---Kannada Character Ya---//
					'r', {103,192,-1,-1,-1,230,-1} ,		    //---Kannada Character ra---//
					'l', {174,-1,-1,-1,-1,232 ,-1} ,			//---Kannada Character la---// 	
					'v', {170,192,-1,-1,-1,233 ,-1} ,			//---Kannada Character va---//
					'S', {177,192,-1,-1,-1,234 ,-1} ,			//---Kannada Character SHA---//
					'x', {181,192,-1,-1,-1,235 ,-1} ,			//---Kannada Character sha---//
					's', {184,192,-1,-1,-1,236 ,-1} ,			//---Kannada Character sa---//
					'h', {186,192,-1,-1,-1,237 ,-1} ,			//---Kannada Character ha---//
					'L', {188,192,-1,-1,-1,238 ,-1} ,			//---Kannada Character LA---//
					'X', {107,-1,-1,-1,-1,213,-1},
					
};  

struct guni_tab
{
	char key;								//----holds the character 
	int k_val[4];							//---holds the glyph codes of the corresponding above character 
											//----eg;  for a 67 (first 3 values)for vowel and 192 for consonants (last value)

}gunisu[35] = {     'k', {81,-1,-1,-1} ,            //---Kannada Character ki---//
				    'K', {84,-1,-1,-1} ,			//---Kannada Character Khi---//	
					'g', {86,-1,-1,-1} ,			//---Kannada Character gi---//	
					'G', {88,-1,-1,-1} ,			//---Kannada Character Ghi---//
					'c', {97,-1,-1,-1} ,			//---Kannada Character chi---//	
					'C', {99,-1,-1,-1} ,		    //---Kannada Character CHi---//
					'j', {102,-1,-1,-1} ,			//---Kannada Character ji---//	
					'J', {106,104,196,-1} ,	        //---Kannada Character Jhi---//  
					'q', {110,-1,-1,-1} ,			//---Kannada Character Ti---//
					'Q', {112,-1,-1,-1} ,			//---Kannada Character Ti---//
					'w', {114,-1,-1,} ,				//---Kannada Character dhi---//
					'W', {114,252,-1,-1} ,			//---Kannada Character DHi---//
					'N', {116,194,-1,-1} ,			//---Kannada Character Ni---//
					't', {119,-1,-1,-1} ,			//---Kannada Character thi---//
					'T', {121,-1,-1,-1} ,			//---Kannada Character THi---//
					'd', {162,-1,-1,-1} ,			//---Kannada Character di---//
					'D', {162,252,-1,-1} ,			//---Kannada Character Di---//
					'n', {164,-1,-1,-1} ,			//---Kannada Character ni---//
					'p', {166,-1,-1,-1} ,			//---Kannada Character pi---//
					'P', {166,252,-1,-1} ,			//---Kannada Character PHi---//
					'b', {169,-1,-1,-1} ,			//---Kannada Character bi---//
					'B', {169,252,-1,-1 } ,			//---Kannada Character BHi---//
					'm', {171,196,-1,-1} ,			//---Kannada Character Mi---//	
					'y', {172,196,-1,196} ,         //---Kannada Character Yi---//
					'r', {106,-1,-1,-1} ,		    //---Kannada Character ri---//
					'l', {176,-1,-1,-1} ,			//---Kannada Character li---// 	
					'v', {171,-1,-1,-1} ,			//---Kannada Character vi---//
					'S', {178,-1,-1,-1} ,			//---Kannada Character SHi---//
					'x', {182,-1,-1,-1} ,			//---Kannada Character shi---//
					's', {185,-1,-1,-1} ,			//---Kannada Character si---//
					'h', {187,-1,-1,-1} ,			//---Kannada Character hi---//
					'L', {189,-1,-1,-1} ,			//---Kannada Character Li---//
};  


BEGIN_MESSAGE_MAP(CSharavathiApp, CWinApp)
	//{{AFX_MSG_MAP(CSharavathiApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()







//------------This-function-is-repeatedly-called-this-executes-when-a-key-is-pressed-on-the-keyboard---/
LRESULT EXPORTED_DLL_FUNCTION kbdHookProc(int nCode,WPARAM wParam,LPARAM lParam)
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
  
int c_bit = 0;
			BYTE ks[256];                                //---a byte for getting the keyboard ststus---//
		    WORD w;										 //---a word for holding the character value of the key---// 
			int r_bit  = 0;											 //pressed used by the ToAsccii where the value is set into this---//	
			UINT scan=0; int f=0;						
		         ::GetKeyboardState(ks);         
				 ::ToAscii(wParam,scan,ks,&w,0);
                  ch = char(w);

				  
	if((GetKeyState(VK_SCROLL ) & 0x0001))
	{
		if(wParam == (WPARAM)VK_SPACE  )
		{
			//MessageBox(NULL,"fdvdf","gbgf",MB_OK);
			vClear_All_Flags();
			kFlag.s_bit = 1;
			kFlag.space_bit = 1;

		}

		if(ispunct(ch) || isdigit(ch) || wParam == (WPARAM)VK_BACK)
		{
			vClear_All_Flags();
		}

	
	
		if( isalpha(ch) ||
			(ch == '~') ||
		    (ch == '`') ||
			(  (isalpha(ch) || (ch == '~') || (ch == '`')  )&& GetKeyState(VK_SHIFT))
		  )   //---If key is pressed and is not a control key---//
		{
			if((lParam & 0x80000000) == 0x00000000)   //---If key is pressed and is not a control key---//
			{

				FindCharacters(ch);									//---Find the glyph code--//
				PushBackspaces();

			}
			else // key released
			{
				PushKeys();
				kFlag.s_bit = FALSE;
				return TRUE;
			}
			
		}

		if(  isalpha(ch) || (ch == '~') ||(ch == '`') &&!(GetKeyState(VK_MENU) & 0x80))    //---If the key pressed is a alpha key and when not
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
BOOL EXPORTED_DLL_FUNCTION InstallKeyboardHook_Sharavathi (HWND hWnd) 
{
   BOOL bSuccess = FALSE;
    if( !ghKeyHook) 
	{
		ghWndMain = hWnd;
		glpfnHookProc = (HOOKPROC) kbdHookProc;
        bSuccess = (NULL != ( ghKeyHook = ::SetWindowsHookEx (WH_KEYBOARD, glpfnHookProc,ghInstance, NULL)));
		ghCallWndProcRetHook = ::SetWindowsHookEx (WH_CALLWNDPROCRET, (HOOKPROC)callWndRetProc,ghInstance, NULL);		
	}
	return bSuccess;
}


//---------------Un-Insatalls-the-Hook---//---This-is -called-by-the-.exe---//
BOOL EXPORTED_DLL_FUNCTION DeInstallKeyboardHook_Sharavathi()
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




CSharavathiApp::CSharavathiApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSharavathiApp object

CSharavathiApp theApp;



BOOL CSharavathiApp::InitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ghInstance = AfxGetInstanceHandle();
	return TRUE;

}

int CSharavathiApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	DeInstallKeyboardHook_Sharavathi();

	return CWinApp::ExitInstance();
}

BOOL CSharavathiApp::PreTranslateMessage(MSG* pMsg) 
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
//	HWND  myWnd;  //---------Window Handel---//
    int	v_bit = 0;
	int no_bs = 0;//-------number of back spae--------//
	int glp_pos = 0; //---Glyph position ----//
	BOOL bHandledKeystroke = FALSE;
	kFlag.found = 0;

	
	if(ch == '~' && (kFlag.previous_0 == 'P' || kFlag.previous_0 == 'j'))
	{
			if(kFlag.previous_0 == 'j')
			{
				DisplaySingleCharacter(243);
			}
			else
			{
				SendBackSpace(1);
				DisplayDoubleCharacter(243,192);
			}
			kFlag.lastglyph = TRUE;
			return bHandledKeystroke;
	}
  
    if(ch == 'I' || ch == 'O' || ch == 'E')
	{ 
		if(ch == 'I' && kFlag.s_bit == TRUE)
		{
			DisplaySingleCharacter(70);
			kFlag.s_bit = FALSE;
			return bHandledKeystroke;
		}
		else
			DisplaySingleCharacter(195);
		return bHandledKeystroke;

		switch(kFlag.previous_0)
		{
		case 'i':
		case 'o':
		case 'e':
		DisplaySingleCharacter(195);
		return bHandledKeystroke;
		}

	if(kFlag.ipressed == TRUE)
		{
		kFlag.ipressed = FALSE;
		}
	 kFlag.ipressed	= FALSE;
	}

	
	if(ch == '~')
	{
	/*	if(kFlag.ei_bit == TRUE)
		{
			
			DisplaySingleCharacter(247);
			DisplaySingleCharacter(202);
			kFlag.ei_bit = 0;
			return bHandledKeystroke;
		}
		if(kFlag.c_bit == 1 || kFlag.o_bit == 1)
		{   
			DisplaySingleCharacter(246);
			DisplaySingleCharacter(200);
			kFlag.c_bit = 0;
		}
		else*/
		{
			DisplayDoubleCharacter(73,196);
			kFlag.found = TRUE;
			return bHandledKeystroke;
		}

	}
	if(ch == '`')
	{
		
		//	DisplaySingleCharacter(246);
			DisplaySingleCharacter(200);
			kFlag.c_bit = 0;
			return bHandledKeystroke;
	}

     switch(ch)
	 {
	 case 'F' :	
		 if(kFlag.c_bit == 1)
		DisplayCharacters_f(ch) ;
		kFlag.c_bit = 0;
	break ;
	case 'R' :	
			DisplaySingleCharacter(240);
		return bHandledKeystroke;
	case 'f':
		 kFlag.f_bit = 1;
		 return bHandledKeystroke;
	 }
    

    for(int i=0;i<=2;i++)
		 if(ch==anuswaranvisarga[i].key)
		 {  kFlag.found = 1;
			
				DisplayCharacters(i,ANUSWARA,0);
		 }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if((ch == 'A'))
  {    

	  if(kFlag.c_bit == 1)
		  return bHandledKeystroke;
	  DisplaySingleCharacter(67);
	  kFlag.found = 1;
	  return bHandledKeystroke;
  }
  		 
		 
   if(kFlag.found == 0)
    for(int i=0;i<=16;i++)
	if(ch==vowels[i].key)
	 {  
		switch(ch)
		 {  
			 case 'a':
			 case 'I':
			 case 'i':
			 case 'u':
			 case 'U':
			 case 'e':
		     case 'o':
			 case 'Z':
			 case 'V':
			 case '~':
			 if((kFlag.space_bit== 1)&&(kFlag.c_bit == 0))
			 {
			 DisplayCharacters(i,VOWELS,0);
			 kFlag.found  = 1;
			 kFlag.c_bit = 0;
			 kFlag.space_bit = 0;
			 }
			 break;

			 case 'Y':
			 case 'z':
			 case 'R':
			 if(kFlag.c_bit == 0)
			 {
			 DisplayCharacters(i,VOWELS,0);
			 kFlag.found  = 1;
			 kFlag.c_bit = 0;
			 kFlag.space_bit = 0;
			 }
    		 break;
		}
	 if(kFlag.found == 0)
 	 if(kFlag.c_bit == 1)
	 {           
                            
							switch(ch)
							{	
							case  'u' :
							case  'U' :
							case  '~' :
								 kFlag.n_back = -1;
				
							break;
						    default :
							kFlag.n_back = 1;
							}//-------------End of Switch------------//

							switch(ch)
							{	
							case 'i':
							case 'o':
							    kFlag.ipressed		 = 1;
							break;
							case 'e' :
								kFlag.ipressed		 = 1;
								kFlag.ei_bit = 1;
							}
		
					       if(ch == '~')
						   {							
									kFlag.s_bit = 1;
									vowels[i].k_val[3] = 200;
									DisplayCharacters(i,VOWELS,3);
							}//----------------End of if(ch == R)-----------------//
						   else
							   
							if(ch == 'i' || ch == 'I')                   //---If an i is pressed after a consonant---//
							{   
								kFlag.ipressed		 = 1;
								kFlag.n_back = -1;
								DisplayGunisu(ch);
							}
							else

							switch (kFlag.previous_0)   
							{
	   						case 'b' :
								SetGlyphs(ch,167);					//This function sets the glyph 
								kFlag.n_back = -1;                    //---patterns for thes specified characters
								DisplayCharacters(i,VOWELS,3) ;
							break;
						    case 'K' :
								SetGlyphs(ch,82);					//This function sets the glyph 
								kFlag.n_back = -1;                    //---patterns for thes specified characters
								DisplayCharacters(i,VOWELS,3) ;
							break;
							case 'j' :
								SetGlyphs(ch,100);
								kFlag.n_back = 0;
								DisplayCharacters(i,VOWELS,3) ;
							break;
							case 'q' :
								SetGlyphs(ch,108);
								DisplayCharacters(i,VOWELS,3) ;
							break;
							case 'N' :
								SetGlyphs(ch,116);
								DisplayCharacters(i,VOWELS,3) ;
							break;
							case 'l' :
								SetGlyphs(ch,174);
								DisplayCharacters(i,VOWELS,3) ;
							break;
							case 'J' :					//----For the characters ya ,ma,Jha,---//
							case 'm' :
         										//---ch the character and i the position in the vowles tab
						       	SetGlyphs_for_jmy(ch,i);
							break;
							case 'y' :
								SetGlyphs_for_jmy(ch,i);
							break;
							default :	
								//---For all other characters---//
							glp_pos = 3;
							switch(kFlag.previous_0)  //---------For Characters hu,vu,pu,Pu-------//
							{
							case 'p':
							case 'P':
							case 'v':
							case 'h':
								if(ch=='u'||ch=='U'||ch=='o'||ch=='O')
									glp_pos = 7;
								else
									glp_pos = 3;
							break;//-------add this to netravathi also---------//
							}

						/*	if(ch == 'i'||ch == 'o' || ch == 'e')
							{
							kFlag.derg_bit 	= 1;
							kFlag.derg_count 	= 1;
							}*/

							 DisplayCharacters(i,VOWELS,glp_pos) ;		    //---Display --Glyphs from 3----//
						   }   									   ///----------pevious_0 value put to next line of c_bit
						   kFlag.c_bit = 0;									///-------------Changed from last 
	 } //--------End of if C_bit ==1---------------//
    kFlag.c_bit = 0;									///-------------Changed from last 
	kFlag.q_bit = 0; ///for second voottakshara ////
	kFlag.so_bit = 0; // to set default for ra votakshara
	}//-------------End of ch == vowels[i]----------------// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     if(kFlag.found == 0)
	 for(int i=0;i<=34;i++)
		 if(ch==consonants[i].key)
		 {   
			 kFlag.found = 1;
			
			    if(kFlag.f_bit == 1)
				{   
					if(kFlag.q_bit == TRUE)
					{
						DisplaySingleCharacter(246);
						kFlag.q_bit = 0;
					}
					
							 switch(ch)
							 {
							 case 'r':
								 if(kFlag.so_bit == 1)
								 {
							 	 kFlag.so_bit = 0;	
							 	 consonants[i].k_val[5] = 231;
								 }
								 else
								 {
								 consonants[i].k_val[5] = 230;
								 }
							 break;
							 default:
							  	kFlag.so_bit = 1;				//---------Otherwise it is second vttakshara ---------//
							 }
						 if(kFlag.previous_0 == 'Y') // if previous is an iitwa 
						 {
							 SendBackSpace(1);
							 DisplayCharacters(i,CONSONANTS,5);
							 DisplayDoubleCharacter(246,202);///display iitwa
						 }
						 else
						 if(kFlag.previous_1 == 'Y') // if previous is an iitwa 
						 {
							 SendBackSpace(2);
							 DisplayCharacters(i,CONSONANTS,5);
							 DisplayDoubleCharacter(246,202);///display iitwa
						 }
						 else
						 DisplayCharacters(i,CONSONANTS,5);
						 kFlag.f_bit = 0;
						 kFlag.c_bit = 0;
						 kFlag.o_bit = 1;
						 kFlag.q_bit = 1; ///for second voottakshara ////
				} //End Of kFlag.f_bit == 1
				else
				{  
					kFlag.c_bit = 1;
					DisplayCharacters(i,CONSONANTS,0);
					kFlag.ei_bit = 0;
					kFlag.o_bit = 0;
					kFlag.q_bit = 0; ///for second voottakshara ////
				}
		 }

    if(isalpha(ch)&&!(kFlag.f_bit)&&!(ch == 'F'))
	CopyPrevious(ch);
	if(isspace(ch))
	{
		kFlag.space_bit 		= 1;
		kFlag.c_bit = 0; //----------Add this and to above vowels for netravathi 
		kFlag.o_bit = 0;
		kFlag.f_bit = 0;
		kFlag.ipressed		 = 0;
		kFlag.ei_bit = 0;
	}
	if(!(isspace(ch))&&!(GetKeyState(VK_SHIFT)))
	 {
		 kFlag.space_bit 		= 0;
	     //c_bit = 0;
	 }
	return bHandledKeystroke;

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function Finds The Character in The Tables in Found Calls     /////////////////////////////
/////////////////////////////  The Display Functions With Position (i),and The Starting Position  /////////////////////////////
/////////////////////////////  Of The Of The Message To Be Posted The Argument 					  /////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void DisplayCharacters(int nval,int indicator,int j)   //indictor value is 0 for anuswara ,1 for vowels , 2 for consonants
{    
			int k = j ;   // --------index for glyph codes---// 
			 HWND myWnd;
	         myWnd =  GetActiveWindowHandel();


		while(kFlag.n_back>=1)
			{
			//::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
			AddKey(VK_BACK);
				kFlag.n_back--;
			}


		if(indicator==0)	
			{
			//::PostMessage(myWnd,WM_CHAR,(WPARAM)anuswaranvisarga[nval].k_val[0],(LPARAM)1);
			AddKey(anuswaranvisarga[nval].k_val[0]);
				kFlag.n_back = -1;
			}
		else
		   if(indicator==1)	
			{
			while(vowels[nval].k_val[k]!=-1)
				{
					   // ::PostMessage(myWnd,WM_CHAR,(WPARAM)vowels[nval].k_val[k],(LPARAM)1);
				AddKey(vowels[nval].k_val[k]);
						k++;
				}
			}
		else
		    if(indicator == 2)
			{
				while(consonants[nval].k_val[k]!=-1)
				{
					//	::PostMessage(myWnd,WM_CHAR,(WPARAM)consonants[nval].k_val[k],(LPARAM)1);
					AddKey(consonants[nval].k_val[k]);
						k++;
				}
			}
			kFlag.n_back = -1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// This Function Post the message for the ACTIVE window of the Specified Character  in "ch"  ////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--- ch ===>character ---//

void DisplayCharacters_f(char ch)  //-----While f is pressed
{    
			int nb = 0 ;
			int j = 0 ;   // --------index for glyph codes---// 
			HWND myWnd;
	         myWnd =  GetActiveWindowHandel();

		
			switch (kFlag.previous_0)
				{
				case 'z':
				case 'Z':
				   // ::PostMessage(myWnd,WM_CHAR,239,(LPARAM)1);
					DisplaySingleCharacter(239);
			    break;
				case 'K':
					//::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
					//::PostMessage(myWnd,WM_CHAR,83,(LPARAM)1);
					//::PostMessage(myWnd,WM_CHAR,239,(LPARAM)1);
					DisplayTripleCharacter(VK_BACK,82,239);
				break;
				case 'j':
				//	::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,101,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,239,(LPARAM)1);
					DisplayTripleCharacter(VK_BACK,101,239);
					break ;
				case 'J':
				case 'm':
				case 'y':
					//::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
					//::PostMessage(myWnd,WM_CHAR,105,(LPARAM)1);
					//::PostMessage(myWnd,WM_CHAR,239,(LPARAM)1);
					DisplayTripleCharacter(VK_BACK,105,239);
						break ;
				case 'q':
//					if(o_bit == 1)
//            		::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);//only for netaravthi
 						//::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
						//::PostMessage(myWnd,WM_CHAR,109,(LPARAM)1);
//					if(o_bit == 1)//only for netravathi
  //          		::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);//only for netravathi
	//					::PostMessage(myWnd,WM_CHAR,239,(LPARAM)1);
					DisplayTripleCharacter(VK_BACK,109,239);
						break ;
				case 'b':
				//	::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,168,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,239,(LPARAM)1);
						DisplayTripleCharacter(VK_BACK,168,239);
						break ;
				case 'l':
				//	::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,175,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,239,(LPARAM)1);
						DisplayTripleCharacter(VK_BACK,175,239);
						break ;
				case 'N':
				//	::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,117,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,239,(LPARAM)1);
						DisplayTripleCharacter(VK_BACK,117,239);
						break ;
    			default :
				//::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
			//	::PostMessage(myWnd,WM_CHAR,239,(LPARAM)1);
						DisplayDoubleCharacter(VK_BACK,239);
			}
kFlag.n_back = -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function Set The Glypha For Kha,ja,.... ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ch ===>character , gval ===> pevious_0 GlypH value//
void SetGlyphs(char ch,int gval)
{
			HWND myWnd;
	         myWnd =  GetActiveWindowHandel();

	switch (ch)
	{
	
	case 'A' :
	return ;
	case 'a' :
	case 'E' :	
	case 'e' :
	case 'Y' :
	case 'O' :
	case 'o' :
	case 'V' :
		if(kFlag.x_bit == 1)
	   SendBackSpace(1);
	   SendBackSpace(1);
		//::PostMessage(myWnd,WM_CHAR,(WPARAM)gval+1,(LPARAM)1);
	   DisplaySingleCharacter(gval+1);
		if(kFlag.x_bit ==1)
    	//::PostMessage(myWnd,WM_CHAR,(WPARAM)243,(LPARAM)1);
		DisplaySingleCharacter(243);
		if(kFlag.x_bit == 1)
			kFlag.x_bit = 0;
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
	HWND myWnd;
	 myWnd =  GetActiveWindowHandel();


		switch(kFlag.previous_0)
		{
		case 'y' :				//-----------For The Characters ya,ma-----------//
		case 'm' :
			switch(ch)
			{
				case 'a' :
				case 'V' :
				//	::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)105,(LPARAM)1);
					DisplayDoubleCharacter(VK_BACK,105);
				if(ch == 'a')
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)193,(LPARAM)1);
					DisplaySingleCharacter(193);
				else
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)203,(LPARAM)1);
				DisplaySingleCharacter(203);
				break;

				case 'u':
				case 'U':
					 DisplayCharacters(i,1,3) ;
					break;
			
				case 'e' :
					SendBackSpace(2);
					//::PostMessage(myWnd,WM_CHAR,(WPARAM)201,(LPARAM)1);
					//::PostMessage(myWnd,WM_CHAR,(WPARAM)196,(LPARAM)1);
					DisplayDoubleCharacter(201,196);
					break;

				case 'E' :
				case 'Y' :
					SendBackSpace(2);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)201,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)196,(LPARAM)1);
					DisplayDoubleCharacter(201,196);
				if(ch == 'E')
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)195,(LPARAM)1);
				DisplaySingleCharacter(195);
				else 
					if(ch == 'Y')
					//::PostMessage(myWnd,WM_CHAR,(WPARAM)202,(LPARAM)1);
					DisplaySingleCharacter(202);
				break;

				case 'o' :
					SendBackSpace(2);
					//::PostMessage(myWnd,WM_CHAR,(WPARAM)201,(LPARAM)1);
					//::PostMessage(myWnd,WM_CHAR,(WPARAM)198,(LPARAM)1);
					DisplayDoubleCharacter(201,198);
				break ;

				case  'O' :
					SendBackSpace(2);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)201,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)198,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)195,(LPARAM)1);
					DisplayTripleCharacter(201,198,195);
				break;
			}//---------End of Switch(ch)--for the characters ma,ya ------//
		 break; //---------------End of the case y , m instance 1
		 case 'J' :				//-----------For The Characters JHA-----------//
			switch(ch)
			{
				case 'a' :
				case 'V' :
				//	::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)105,(LPARAM)1);
					DisplayDoubleCharacter(VK_BACK,105);
				if(ch == 'a')
					//::PostMessage(myWnd,WM_CHAR,(WPARAM)193,(LPARAM)1);
					DisplaySingleCharacter(193);
				else
					//::PostMessage(myWnd,WM_CHAR,(WPARAM)203,(LPARAM)1)
					DisplaySingleCharacter(203);

				break;
				case 'u':
				case 'U':
					 DisplayCharacters(i,1,3) ;
					break;
				case 'e' :
					SendBackSpace(3);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)201,(LPARAM)1);
				///	::PostMessage(myWnd,WM_CHAR,(WPARAM)104,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)196,(LPARAM)1);
					DisplayTripleCharacter(201,104,196);
					break;

				case 'E' :
				case 'Y' :
					SendBackSpace(3);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)201,(LPARAM)1);
				///	::PostMessage(myWnd,WM_CHAR,(WPARAM)104,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)196,(LPARAM)1);
					DisplayTripleCharacter(201,104,196);
				if(ch == 'E')
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)195,(LPARAM)1);
				DisplaySingleCharacter(195);
				else 
					if(ch == 'Y')
					//::PostMessage(myWnd,WM_CHAR,(WPARAM)202,(LPARAM)1);
					DisplaySingleCharacter(202);
				break;

				case 'o' :
					SendBackSpace(3);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)201,(LPARAM)1);
				///	::PostMessage(myWnd,WM_CHAR,(WPARAM)104,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)198,(LPARAM)1);
					DisplayTripleCharacter(201,104,198);
				break ;

				case  'O' :
					SendBackSpace(3);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)201,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)104,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)198,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)195,(LPARAM)1);
					DisplayFourCharacter(201,104,198,195);
				break;
			}//-------------------End of Switch(ch)----for JHA ---------------//

		break ;
		}//---------End of Switch(pevious_0)--------//
kFlag.n_back = -1;
}//-------End OF The function SetGlyphs_for_jmy----------//

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// This Function Displays GuniSu for of the previosly entered character /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DisplayGunisu(char ch)
{
	int position = 0;
	int k = 0;
	char char_1;

	         HWND myWnd;
	         myWnd =  GetActiveWindowHandel();

char_1 = kFlag.previous_0;
		for(int i=0;i<=34;i++)
		if(char_1== consonants[i].key)		// ---search the structure 
											//for the key pressed
			{
				position = i;			
			    //::MessageBox(myWnd,"found",NULL,MB_OK);
			}
		switch(char_1)
		{
		case 'z' :				//---for these characters display 
								//---the corresponding Gunisu ---//
		case 'Z' :
		case 'N' :
			//::PostMessage(myWnd,WM_CHAR,194,(LPARAM)1);
			DisplaySingleCharacter(194);
		break;
		case 'K':				//---for these characters send a single 
								//---back space and display the corresponding Gunisu---//
		case 'j':
		//::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
			SendBackSpace(1);
			while(gunisu[position].k_val[k]!=-1)
				{
						//::PostMessage(myWnd,WM_CHAR,(WPARAM)gunisu[position].k_val[k],(LPARAM)1);
						AddKey(gunisu[position].k_val[k]);
						k++;
				}
			
		break ;
		case 'P':
			 SendBackSpace(3);
		    DisplaySingleCharacter(166);
			DisplaySingleCharacter(252);
	     break;
		case 'q':
		case 'b':
		case 'l':
			//::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
			SendBackSpace(1);
			while(gunisu[position].k_val[k]!=-1)
				{
						//::PostMessage(myWnd,WM_CHAR,(WPARAM)gunisu[position].k_val[k],(LPARAM)1);
						AddKey(gunisu[position].k_val[k]);
						k++;
				}
		break;
		case 'D' :
		SendBackSpace(3);
		DisplaySingleCharacter(162);
		DisplaySingleCharacter(252);
        break;

		case 'W' :
		SendBackSpace(3);
		DisplaySingleCharacter(114);
		DisplaySingleCharacter(252);
		break;
		case 'B' :
		case 'm' :	
		               //---for these characters send a triple back 
					    //---space and display the corresponding Gunisu---//
		SendBackSpace(3);
			while(gunisu[position].k_val[k]!=-1)
				{
					//	::PostMessage(myWnd,WM_CHAR,(WPARAM)gunisu[position].k_val[k],(LPARAM)1);
				AddKey(gunisu[position].k_val[k]);
						k++;
				}
		break;
	
		case 'J':		//---for these characters send a four back space 
						//---and display the corresponding Gunisu---//
		case 'y':
		SendBackSpace(4);
			while(gunisu[position].k_val[k]!=-1)
				{
					//	::PostMessage(myWnd,WM_CHAR,(WPARAM)gunisu[position].k_val[k],(LPARAM)1);
				AddKey(gunisu[position].k_val[k]);
						k++;
				}
		break;
		case 'd':
		SendBackSpace(2);
			while(gunisu[position].k_val[k]!=-1)
				{
					//	::PostMessage(myWnd,WM_CHAR,(WPARAM)gunisu[position].k_val[k],(LPARAM)1);
				AddKey(gunisu[position].k_val[k]);
						k++;
				}
		break;
		default :		//---for these characters send a double 
						//---back space and display the corresponding Gunisu---//
			SendBackSpace(2);//-----------replaced by 2 vk_back meassages-----------// 
			while(gunisu[position].k_val[k]!=-1)
				{
					//	::PostMessage(myWnd,WM_CHAR,(WPARAM)gunisu[position].k_val[k],(LPARAM)1);
				AddKey(gunisu[position].k_val[k]);
						k++;
				}
		}
		if(ch == 'I')
		{
			AddKey(195);
		}
kFlag.c_bit = 0;		
kFlag.n_back = -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function copies the character the in ch ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Set_for_fbit(char ch,int i)  //--------The Position i ,ch the character ---//
{
	int j = 0 ;
	switch(kFlag.previous_0)
	{
		case 'K' :
		case 'Z' :
		case 'j' :
		case 'z' :
		case 'q' :
		case 'N' :
		case 'b' :
		case 'l' :
			kFlag.n_back = 2;
			for(j=0;j<=34;j++)
					if(kFlag.previous_0==consonants[j].key)
					{
						DisplayCharacters(j,CONSONANTS,0);
					}
//		     	DisplayCharacters(i,CONSONANTS,5);
		break;
		case 'J' :
		case 'y' :
			kFlag.n_back = 5;
			for(j=0;j<=34;j++)
					if(kFlag.previous_0==consonants[j].key)
					{
						DisplayCharacters(j,CONSONANTS,0);
					}
//		     	DisplayCharacters(i,CONSONANTS,5);
			break;
		case 'm' :
			kFlag.n_back = 4;
			for(j=0;j<=34;j++)
					if(kFlag.previous_0==consonants[j].key)
					{
						DisplayCharacters(j,CONSONANTS,0);
					}
//		     	DisplayCharacters(i,CONSONANTS,5);
			break;
		default:
			kFlag.n_back = 1;
			DisplayCharacters(0,CONSONANTS,1) ;
//			DisplayCharacters(i,CONSONANTS,5) ;
	}
kFlag.f_bit = 0;
kFlag.o_bit = 1;
kFlag.n_back = -1;
} 

//-----------------------For P with ..--------------------------//
void DisplayCharacter_phi(char ch,int i)
{

	         HWND myWnd;
	         myWnd =  GetActiveWindowHandel();


		switch(ch)
			{
				case 'A' :
				case 'V' :
				case 'e' :
				case 'E' :
				case 'o' :
				case 'O' :
				case 'Y' :
					 SendBackSpace(4);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)165,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)243,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)115,(LPARAM)1);
				//	::PostMessage(myWnd,WM_CHAR,(WPARAM)192,(LPARAM)1);
					 DisplayFourCharacter(165,243,115,192);
				break;					

			}//------End of Switch(ch)-----//

}

void DisplayChar(char ch)
{
	         HWND myWnd;
	         myWnd =  GetActiveWindowHandel();

			for(int i=0;i<=34;i++)
				if(ch == consonants[i].key)
//::PostMessage(myWnd,WM_CHAR,(WPARAM)consonants[i].k_val,(LPARAM)1);
AddKey((WPARAM)consonants[i].k_val);

}


void CopyPrevious(char ch)
{   
	kFlag. previous_1 = kFlag.previous_0;
	kFlag.previous_0 = ch;
}





void DisplayQueue()
{
    myWnd = GetActiveWindowHandel();
	int i = 0;
    while(oqueue[i]!=-1)
	{
	//::PostMessage(myWnd,WM_CHAR,(WPARAM)oqueue[i],(LPARAM)1);
		AddKey(oqueue[i]);
    i++;
	}
	/*---For netravathi,nudi-------*/
//	if(so_bit == 1)
//	{
//	 so_bit = 0;
   // ::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
//	}
}

void ClearQueue()
{
	for (int i=0;i<=10;i++)
		oqueue[i] = -1;
	kFlag.o_count = 0;
}

