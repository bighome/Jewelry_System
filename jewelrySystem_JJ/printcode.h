#pragma once
#include <Windows.h>
/*****************************************��˵��***********************************************
*������POSTEK�����ӡ�������ӡ��
*���ߣ�penghongbin
*ʱ�䣺2012-04-19 01:39
************************************************************************************************/
/*****************************************����ֵ***********************************************
*LPCTSTR m_printNmae:��ӡ������
*int m_lHeight: ��ǩ�ĸ߶ȣ��Ե�(dots)Ϊ��λ��ȡֵ��Χ��0-65535
*int m_gapH:��ǩ��Ķ�λ��϶/����/���׵ĸ߶ȣ��Ե�(dots)Ϊ��λ��ȡֵ��Χ: 0-65535��
*int m_lWidth:��ǩ�Ŀ�ȣ��Ե�(dots)Ϊ��λ
*int m_darkness:���ô����������¶�,ȡֵ��Χ��0��20��ȱʡΪ10;��ֵ����������������¶���ֵ,���������ֵ,0��ʾ��ӡͷ��������ͷ���״̬,20��ʾ��ӡ��������߷���״̬. 
*int m_printSpeed:���ô�ӡ�ٶ�;ȡֵ��ΧΪ0 - 6������10 �C 80��
*int m_x:���ô�ӡ����x����;�Ե�(dots)Ϊ��λ
*int m_y:���ô�ӡ����y����;�Ե�(dots)Ϊ��λ
*int m_fHeight:���͸߶ȣ��Ե�(dots)Ϊ��λ��
*int m_fWidth:���Ϳ�ȣ��Ե�(dots)Ϊ��λ��	������ӡ�������������壬�轫FWidth����Ϊ0��
*LPCTSTR m_fYupe:�������ƣ�
*int m_fSpin:������ת�Ƕȼ��������������뷽ʽ��1 -> ����0��, 2 -> ����90��, 3 ->����180��, 4 ->����270�ȣ�5 ->����0��, 6 ->����90��, 7 ->����270��, 8 ->����270��
*int m_fWeight:�����ϸ.
															0 and 400 -> 400 ��׼��
															100 -> �ǳ�ϸ��200 -> ��ϸ��
															300 -> ϸ     ��500 -> �еȡ�
															600 -> ���  ��700 -> ��  ��
															800 -> �ش�  ��900 -> ���塣
*BOOL m_fItalic:б�壬0 -> FALSE��1 -> TRUE��
*BOOL m_fUnline:���ּӵ��ߣ�0 -> FALSE��1 -> TRUE��
*BOOL m_fStrikeOut:���ּ�ɾ���ߣ�0 -> FALSE��1 -> TRUE��
*LPCTSTR m_IdName:ʶ�����ƣ���Ϊһ��TrueType���ֽ���ת����PCX��ʽ������id_name��ΪPCX��ʽͼ�ε����ƴ�ŵ���ӡ���ڣ��ڹػ�ǰ�����Զ��ͨ�� PTK_DrawPcxGraphics( )����id_name��ӡ�������֣�
*LPCTSTR  m_text:�ַ�������
*int m_codePx:����X����,�Ե�(dots)Ϊ��λ.
*int m_codePy:����Y����,�Ե�(dots)Ϊ��λ.
*int m_pdirec:ѡ������Ĵ�ӡ����. 0������ת;1����ת90��; 2����ת180��; 3����ת270��.
*LPTSTR  m_pCode:ѡ��Ҫ��ӡ����������.
										P4ֵ	��������
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
*int m_narrowWidth:	����������խ��Ԫ�Ŀ��,�Ե�(dots)Ϊ��λ.
*int m_pHorizonta:���������п�Ԫ�Ŀ��,�Ե�(dots)Ϊ��λ.
*int m_pVertical:��������߶�,�Ե�(dots)Ϊ��λ.
*char m_pText:	ѡ��N���򲻴�ӡ����������˿�ʶ������, ;ѡ��B�����ӡ����������˿�ʶ������.
*LPTSTR m_pStr;һ������Ϊ1-100���ַ�����
*int m_number:��ӡ��ǩ��������ȡֵ��Χ��1��65535;
*int m_cpNumber:ÿ�ű�ǩ�ĸ��Ʒ�����ȡֵ��Χ��1��65535�����cpnumberû�����ã���ôĬ��Ϊ1��
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
							LPCTSTR m_fYupe = LPCTSTR("����"),
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
