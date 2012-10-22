#include "printcode.h"
#include "PTKPRN.h"

printCode::printCode(LPCTSTR m_printNmae,
					 int m_lHeight,
					 int m_gapH,
					 int m_lWidth,
					 int m_darkness,
					 int m_printSpeed,
					 int m_x,
					 int m_y,
					 int m_fHeight,
					 int m_fWidth,
					 LPCTSTR m_fYupe,
					 int m_fSpin,
					 int m_fWeight,
					 BOOL m_fItalic,
					 BOOL m_fUnline,
					 BOOL m_fStrikeOut,
					 LPCTSTR m_IdName,
					 LPCTSTR  m_text,
					 int m_codePx,
					 int m_codePy,
					 int m_pdirec,
					 LPTSTR  m_pCode,
					 int m_narrowWidth,
					 int m_pHorizonta,
					 int m_pVertical,
					 char m_pText,
					 LPTSTR m_pStr,
					 int m_number,
					 int m_cpNumber)
{
	HINSTANCE gt1 = NULL;

	gt1=LoadLibrary(L"winPSK.dll");
	if (gt1 == NULL)
	{
		return;
	}
	OpenPort = (fOpenPort)GetProcAddress(gt1,"OpenPort");
	ClosePort = (fClosePort)GetProcAddress(gt1,"ClosePort");
	PTK_DrawBarcode = (fPTK_DrawBarcode)GetProcAddress(gt1,"PTK_DrawBarcode");
	PTK_SetLabelHeight = (fPTK_SetLabelHeight)GetProcAddress(gt1,"PTK_SetLabelHeight");
	PTK_PrintLabel = (fPTK_PrintLabel)GetProcAddress(gt1,"PTK_PrintLabel");
	PTK_SetDarkness = (fPTK_SetDarkness)GetProcAddress(gt1,"PTK_SetDarkness");
	PTK_SetPrintSpeed = (fPTK_SetPrintSpeed)GetProcAddress(gt1,"PTK_SetPrintSpeed");
	PTK_SetLabelWidth = (fPTK_SetLabelWidth)GetProcAddress(gt1,"PTK_SetLabelWidth");
	PTK_ClearBuffer = (fPTK_ClearBuffer)GetProcAddress(gt1,"PTK_ClearBuffer");
	PTK_DrawTextTrueTypeW = (fPTK_DrawTextTrueTypeW)GetProcAddress(gt1,"PTK_DrawTextTrueTypeW");

	int errorcode = 0;
	int a = OpenPort(/*LPCTSTR("POSTEK C168 200S")*/m_printNmae);
	errorcode=PTK_ClearBuffer();	 
	if (errorcode!=0)  {return;}
	errorcode = PTK_SetLabelHeight (m_lHeight,m_gapH);
	if(errorcode != 0) {return;}
	errorcode = PTK_SetLabelWidth (m_lWidth);
	if(errorcode != 0) {return;}
	errorcode = PTK_SetDarkness( m_darkness );
	if(errorcode != 0) {return;}
	errorcode = PTK_SetPrintSpeed( m_printSpeed );
	if(errorcode != 0) {return;} 
	errorcode = PTK_DrawTextTrueTypeW (m_x,m_y,m_fHeight,m_fWidth,m_fYupe,m_fSpin,m_fWeight,m_fItalic,m_fUnline,m_fStrikeOut,m_IdName,m_text);
	if(errorcode != 0) {return;} 
	errorcode = PTK_DrawBarcode(m_codePx,m_codePy,m_pdirec,m_pCode,m_narrowWidth,m_pHorizonta,m_pVertical,m_pText,m_pStr); 
	if(errorcode != 0) {return;} 
	errorcode=PTK_PrintLabel(m_number,m_cpNumber);
	if (errorcode!=0)  {return;}
	ClosePort();
	FreeLibrary(gt1);
}

printCode::~printCode(void)
{
}
