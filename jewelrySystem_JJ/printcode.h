#pragma once
#include <Windows.h>
/*****************************************类说明***********************************************
*类名：POSTEK条码打印机条码打印类
*作者：penghongbin
*时间：2012-04-19 01:39
************************************************************************************************/
/*****************************************参数值***********************************************
*LPCTSTR m_printNmae:打印机名字
*int m_lHeight: 标签的高度，以点(dots)为单位，取值范围：0-65535
*int m_gapH:标签间的定位间隙/黑线/穿孔的高度，以点(dots)为单位，取值范围: 0-65535；
*int m_lWidth:标签的宽度，以点(dots)为单位
*int m_darkness:设置大雁塔发热温度,取值范围：0—20，缺省为10;此值并不是真正意义的温度数值,而是相对数值,0表示打印头工作在最低发热状态,20表示打印工作在最高发热状态. 
*int m_printSpeed:设置打印速度;取值范围为0 - 6，或者10 – 80。
*int m_x:设置打印文字x坐标;以点(dots)为单位
*int m_y:设置打印文字y坐标;以点(dots)为单位
*int m_fHeight:字型高度，以点(dots)为单位；
*int m_fWidth:字型宽度，以点(dots)为单位；	如果想打印正常比例的字体，需将FWidth设置为0；
*LPCTSTR m_fYupe:字型名称；
*int m_fSpin:字体旋转角度及文字相对坐标对齐方式；1 -> 居左0度, 2 -> 居左90度, 3 ->居左180度, 4 ->居左270度，5 ->居中0度, 6 ->居中90度, 7 ->居中270度, 8 ->居中270度
*int m_fWeight:字体粗细.
															0 and 400 -> 400 标准、
															100 -> 非常细、200 -> 极细、
															300 -> 细     、500 -> 中等、
															600 -> 半粗  、700 -> 粗  、
															800 -> 特粗  、900 -> 黑体。
*BOOL m_fItalic:斜体，0 -> FALSE、1 -> TRUE；
*BOOL m_fUnline:文字加底线，0 -> FALSE、1 -> TRUE；
*BOOL m_fStrikeOut:文字加删除线，0 -> FALSE、1 -> TRUE；
*LPCTSTR m_IdName:识别名称，因为一行TrueType文字将被转换成PCX格式数据以id_name作为PCX格式图形的名称存放到打印机内，在关机前都可以多次通过 PTK_DrawPcxGraphics( )调用id_name打印这行文字；
*LPCTSTR  m_text:字符串内容
*int m_codePx:设置X坐标,以点(dots)为单位.
*int m_codePy:设置Y坐标,以点(dots)为单位.
*int m_pdirec:选择条码的打印方向. 0—不旋转;1—旋转90°; 2—旋转180°; 3—旋转270°.
*LPTSTR  m_pCode:选择要打印的条码类型.
										P4值	条码类型
										0	         Code 128 UCC (shipping container code)
										1	         Code 128 AUTO
										1A	     Code 128 subset A
										1B	     Code 128 subset B
										1C	     Code 128 subset C
										1E	     UCC/EAN
										1F	     EAN 128 subset A
										1G	     EAN 128 subset B
										1H	     EAN 128 subset C
										2D	     Interleaved 2 of 5 with human readable check digit
										2G	     German Postcode
										2M	      Matrix 2 of 5
										2U	      UPC Interleaved 2 of 5
										3	          Code 3 of 9
										3C	      Code 3 of 9 with check sum digit
										3E	      Extended Code 3 of 9
										3F	      Extended Code 3 of 9 with check sum digit
										9	          Code93
										E30	      EAN-13
										E32	      EAN-13 2 digit add-on
										E35   	  EAN-13 5 digit add-on
										E80	      EAN-8
										E82	      EAN-8 2 digit add-on
										E-85	  EAN-8 5 digit add-on
										K	          Codabar
										P	          Postnet
										UA0	  UPC-A
										UA2	  UPC-A 2 digit add-on
										UA5	  UPC-A 5 digit add-on
										UE0	      UPC-E
										UE2	      UPC-E 2 digit add-on
										UE5	      UPC-E 5 digit add-on
*int m_narrowWidth:	设置条码中窄单元的宽度,以点(dots)为单位.
*int m_pHorizonta:设置条码中宽单元的宽度,以点(dots)为单位.
*int m_pVertical:设置条码高度,以点(dots)为单位.
*char m_pText:	选’N’则不打印条码下面的人可识别文字, ;选’B’则打印条码下面的人可识别文字.
*LPTSTR m_pStr;一个长度为1-100的字符串。
*int m_number:打印标签的数量，取值范围：1—65535;
*int m_cpNumber:每张标签的复制份数，取值范围：1—65535；如果cpnumber没有设置，那么默认为1。
*
************************************************************************************************/
class printCode
{
public:
	printCode(LPCTSTR m_printNmae = LPCTSTR("POSTEK C168 200S"),
							int m_lHeight = 600,
							int m_gapH = 20,
							int m_lWidth = 800,
							int m_darkness = 20,
							int m_printSpeed = 5,
							int m_x = 30,
							int m_y = 80,
							int m_fHeight = 40,
							int m_fWidth = 40,
							LPCTSTR m_fYupe = LPCTSTR("宋体"),
							int m_fSpin = 1,
							int m_fWeight = 400,
							BOOL m_fItalic = 0,
							BOOL m_fUnline = 0,
							BOOL m_fStrikeOut = 0,
							LPCTSTR m_IdName = LPCTSTR("1"),
							LPCTSTR  m_text =LPCTSTR("1234567890") ,
							int m_codePx = 20,
							int m_codePy = 1,
							int m_pdirec = 0,
							LPTSTR  m_pCode = LPTSTR("2D"),
							int m_narrowWidth = 2,
							int m_pHorizonta = 4,
							int m_pVertical = 30,
							char m_pText = 'N',
							LPTSTR m_pStr =LPTSTR("1234567890"),
							int m_number = 1,
							int m_cpNumber = 1);
	~printCode(void);
	
};
