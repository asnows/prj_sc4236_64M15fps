//#include  "Bsp_VDMAframe.h"
#ifndef BSP_VDMAFRAME_H_
#define BSP_VDMAFRAME_H_
/********************************************************************
 * ������void Bsp_VDMAframe_init(void)
 * ���ܣ�����IO����
 *********************************************************************/
extern void Bsp_VDMAframe_init(void);
/********************************************************************
 * ������unsigned int Bsp_ReadfreamSno(void)
 * ���ܣ���ȡ��ǰ�����ڴ����֡��
 *********************************************************************/
extern unsigned int Bsp_ReadfreamSno(void);
/********************************************************************
 * ������void Bsp_SetSkipfreamSno(unsigned char Sno)
 * ���ܣ�������Ҫ������֡���
 * ���룺Sno  0 �ر�ͨ������  1~8 ��Ӧͨ������
 *********************************************************************/
extern void Bsp_SetSkipfreamSno(unsigned char Sno);
extern void Bsp_FPGAReset_init(void);
extern void Bsp_FPGAReset(void);
unsigned char Bsp_GetGrayCode(unsigned char sno);
#endif
