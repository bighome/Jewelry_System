//CDFPSK.DLL函数声明头文件
#ifndef _PCDFPSK_H
#define _PCDFPSK_H
//CDFPSK DLL Function Declaration start
typedef int (__stdcall *fOpenPort)(LPCTSTR printername);
typedef int (__stdcall *fPTK_SetDarkness)(unsigned  int id);
typedef int (__stdcall *fPTK_SetPrintSpeed)(unsigned int px);
typedef int (__stdcall *fClosePort)(void);
typedef int (__stdcall *fPTK_PrintLabel)(unsigned int number,
		                                 unsigned int cpnumber);
typedef int (__stdcall *fPTK_DrawBarcode)(unsigned  int px,
		                        unsigned int  py,
								unsigned int  pdirec,
								LPTSTR        pCode,
								unsigned int  pHorizontal,
								unsigned int  pVertical,
								unsigned int pbright,
								char ptext,
								LPTSTR pstr);
typedef int (__stdcall *fPTK_DrawTextTrueTypeW)
		                            (int x,int y,int FHeight,
									int FWidth,LPCTSTR FType,
                                    int Fspin,int FWeight,
									BOOL FItalic,BOOL FUnline,
                                    BOOL FStrikeOut,
									LPCTSTR id_name,
									LPCTSTR data);
typedef int (__stdcall *fPTK_SetLabelHeight)
		                (unsigned int lheight, unsigned int gapH);
typedef int (__stdcall *fPTK_SetLabelWidth)(unsigned int lwidth);
typedef int (__stdcall *fPTK_ClearBuffer)();

fOpenPort OpenPort = NULL;
fPTK_SetDarkness PTK_SetDarkness = NULL;
fPTK_DrawTextTrueTypeW PTK_DrawTextTrueTypeW = NULL;
fPTK_SetPrintSpeed PTK_SetPrintSpeed = NULL;
fClosePort ClosePort = NULL;
fPTK_PrintLabel PTK_PrintLabel = NULL;
fPTK_DrawBarcode PTK_DrawBarcode = NULL;
fPTK_SetLabelHeight PTK_SetLabelHeight = NULL;
fPTK_SetLabelWidth PTK_SetLabelWidth = NULL;
fPTK_ClearBuffer PTK_ClearBuffer = NULL;
//CDFPSK DLL Function Declaration end
#endif