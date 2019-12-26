/***********************************************************************
 * �ļ���Bsp_TwoCPU.C
 * ���ܣ�2��CPU֮���ͨ�Ŵ���
 ***********************************************************************/

#include "Bsp_TwoCPU.h"
//#include "Bsp_RGB_Samp.h"
#include "xil_mmu.h"
#include "string.h"
#include "xil_io.h"

 struct CPUTX_{
	 unsigned int CPU0CMD;
	 unsigned int CPU0USESTATS1;
	 unsigned int CPU0USESTATS2;
	 unsigned int CPU0USESTATS3;
	 unsigned int CPU0USESTATS4;
 }CPU0TX;
 struct Image_tj_{    //ͼƬ���� ͳ�ƽṹ
	 unsigned int RECUSE;
	 unsigned int BMPMAX;
	 unsigned int SNO;
 };
 struct Image_DDR_{    //ͼƬ��������λ����Ϣ
	 unsigned int DADDR;
	 unsigned int DADDRCS;
	 unsigned int TEMP;
	 unsigned int STATS;
 };
 struct CPU1TX_{
	 unsigned int CPU1CMD;
	 unsigned int DOBMPMAX ;
	 struct Image_tj_  ITJ[MAXLU];//ÿ·��ͳ����Ϣ
	 struct Image_DDR_ IDDR[MAXLU][MAXDDRNUM];//ͼƬ��������λ����Ϣ
 }CPU1TX;

void Bsp_TwoCPU_Init(void)
{
	Xil_SetTlbAttributes(0xffff0000,0x14de2);
}
/*************************************************************************
* ������unsigned int Bsp_GetDDRBaseAddr(unsigned char Lu,unsigned char Kuai)
* ��ȡ��ÿ·��Ϣ�׵�ַ
* ��Σ�Lu ����· 1~MAXLU   Kuai:DDR�Ŀ��  1~MAXDDRNUM
************************************************************************* */
unsigned int Bsp_GetDDRBaseAddr(unsigned char Lu,unsigned char Kuai)
{
	unsigned int Readdr;
	switch(Lu)
	{
		case 1:Readdr=D1DDRBASE;break;
#if MAXLU > 1
		case 2:Readdr=D2DDRBASE;break;
#endif

#if MAXLU > 2
		case 3:Readdr=D3DDRBASE;break;
#endif

#if MAXLU > 3
		case 4:Readdr=D4DDRBASE;break;
#endif
		default:return 0;
	}
	if(Kuai==0)return 0;
	if(Kuai>MAXDDRNUM)return 0;
	Readdr +=16*(Kuai-1);
	return Readdr;
}

/*************************************************************************
* ����  void Bsp_GetCPU0TX(void)
* ��ȡ�� ��ȡCPU0 ��ͨѶ����
************************************************************************* */
void Bsp_GetCPU0TX(void)
{
	CPU0TX.CPU0CMD=Xil_In32(CPU0CMDADDR);
	CPU0TX.CPU0USESTATS1=Xil_In32(USESTATS1ADDR);
	CPU0TX.CPU0USESTATS2=Xil_In32(USESTATS2ADDR);
	CPU0TX.CPU0USESTATS3=Xil_In32(USESTATS3ADDR);
	CPU0TX.CPU0USESTATS4=Xil_In32(USESTATS4ADDR);
}

/*************************************************************************
* ����  unsigned int Bsp_ReadCPU0CMD(void)
* ��ȡ�� ��ȡCPU0����������
************************************************************************* */
unsigned int Bsp_ReadCPU0CMD(void)
{
	CPU0TX.CPU0CMD=Xil_In32(CPU0CMDADDR);//��ȡCPU0������

	if(CPU0TX.CPU0CMD!=CPU1TX.CPU1CMD)//hui
	{
		CPU1TX.CPU1CMD=CPU0TX.CPU0CMD;
		Xil_Out32(CPU1CMDADDR,CPU1TX.CPU1CMD);
		return CPU1TX.CPU1CMD;

	}
	return 0;
}
/*************************************************************************
* ������ unsigned int Bsp_ReadCPU0USESTATS(unsigned char Lu)
* ��ȡ�� ��ȡ��ǰCPU0 ����ʹ���Ŀ�DDR
************************************************************************* */
unsigned int Bsp_ReadCPU0USESTATS(unsigned char Lu)
{
	 switch(Lu)
	 {
		 case 1:CPU0TX.CPU0USESTATS1=Xil_In32(USESTATS1ADDR);return CPU0TX.CPU0USESTATS1;
		 case 2:CPU0TX.CPU0USESTATS2=Xil_In32(USESTATS2ADDR);return CPU0TX.CPU0USESTATS2;
		 case 3:CPU0TX.CPU0USESTATS3=Xil_In32(USESTATS3ADDR);return CPU0TX.CPU0USESTATS3;
		 case 4:CPU0TX.CPU0USESTATS4=Xil_In32(USESTATS4ADDR);return CPU0TX.CPU0USESTATS4;
	 }
	 return 0;
}
 /*************************************************************************
* ����  void Bsp_WriteCPU1SNO(unsigned char Lu,unsigned int SNO2)
* ��ȡ����Ӧ·���������� ͳ��
************************************************************************* */
void Bsp_WriteCPU1SNO(unsigned char Lu,unsigned int SNO2)
{
	switch(Lu)
	{
		case 1:CPU1TX.ITJ[0].SNO+=SNO2;Xil_Out32(SNO1ADDR,CPU1TX.ITJ[0].SNO);break;
		case 2:CPU1TX.ITJ[1].SNO+=SNO2;Xil_Out32(SNO2ADDR,CPU1TX.ITJ[1].SNO);break;
		case 3:CPU1TX.ITJ[2].SNO+=SNO2;Xil_Out32(SNO3ADDR,CPU1TX.ITJ[2].SNO);break;
		case 4:CPU1TX.ITJ[3].SNO+=SNO2;Xil_Out32(SNO4ADDR,CPU1TX.ITJ[3].SNO);break;
	}
	//xil_printf("--%d\r\n", CPU1TX.ITJ[0].SNO);
}
/*************************************************************************
* ����  void Bsp_WriteCPU1RECUSE(unsigned char Lu,unsigned int RECUSE)
* ��ȡ�� ��ǰ����· ����ʹ���Ŀ�DDR��������
************************************************************************* */
void Bsp_WriteCPU1RECUSE(unsigned char Lu,unsigned int RECUSE)
{
	switch(Lu)
	{
		case 1:CPU1TX.ITJ[0].RECUSE=RECUSE;Xil_Out32(RECUSE1ADDR,RECUSE);break;
		case 2:CPU1TX.ITJ[1].RECUSE=RECUSE;Xil_Out32(RECUSE2ADDR,RECUSE);break;
		case 3:CPU1TX.ITJ[2].RECUSE=RECUSE;Xil_Out32(RECUSE3ADDR,RECUSE);break;
		case 4:CPU1TX.ITJ[3].RECUSE=RECUSE;Xil_Out32(RECUSE4ADDR,RECUSE);break;
	}
}
/*************************************************************************
* ����  void Bsp_WriteCPU1RECUSE(unsigned char Lu,unsigned int RECUSE)
* ��ȡ��д��ÿ��ͨ������������ [���漸��ͼƬ--ѭ������]
************************************************************************* */
void Bsp_WriteCPU1BMPMAX(unsigned char Lu,unsigned int BMPMAX)
{
	switch(Lu)
	{
		case 1:CPU1TX.ITJ[0].BMPMAX=BMPMAX;Xil_Out32(BMPMAX1ADDR,BMPMAX);break;
		case 2:CPU1TX.ITJ[1].BMPMAX=BMPMAX;Xil_Out32(BMPMAX2ADDR,BMPMAX);break;
		case 3:CPU1TX.ITJ[2].BMPMAX=BMPMAX;Xil_Out32(BMPMAX3ADDR,BMPMAX);break;
		case 4:CPU1TX.ITJ[3].BMPMAX=BMPMAX;Xil_Out32(BMPMAX4ADDR,BMPMAX);break;
	}
}
/*************************************************************************
* ������void Bsp_WriteCPU1DOBMPMAX (unsigned int DOBMPMAX )
* ��ȡ��д�����ݲ�����·��
************************************************************************* */
void Bsp_WriteCPU1DOBMPMAX (unsigned int DOBMPMAX )
{
	CPU1TX.DOBMPMAX=DOBMPMAX;
	Xil_Out32(DOBMPMAXADDR,DOBMPMAX);
}
/*************************************************************************
* ������void Bsp_WriteCPU1CPU1CMD (unsigned int CPU1CMD )
* ��ȡ��д��CPU1��ִ�й�������
************************************************************************* */
void Bsp_WriteCPU1CPU1CMD (unsigned int CPU1CMD )
{
	CPU1TX.CPU1CMD=CPU1CMD;
	Xil_Out32(CPU1CMDADDR,CPU1CMD);
}
/*************************************************************************
* ������void Bsp_ReadCPU1CPU1CMD (unsigned int CPU1CMD )
* ��ȡ����ȡCPU1��ִ�й�������
************************************************************************* */
unsigned int Bsp_ReadCPU1CPU1CMD (unsigned int CPU1CMD )
{
	CPU1TX.CPU1CMD=Xil_In32(CPU1CMDADDR);
	return  CPU1TX.CPU1CMD;
}
/*************************************************************************
* ������void Bsp_WriteCPU1LuDDR (unsigned char Lu,unsigned char Kuai,unsigned int addr )
* ���ܣ�д��ͼƬ����ĵ�ַ
************************************************************************* */
void Bsp_WriteCPU1LuDDR (unsigned char Lu,unsigned char Kuai,unsigned int addr )
{
	unsigned int SaveAddr;
	SaveAddr=Bsp_GetDDRBaseAddr(Lu,Kuai);
	if(SaveAddr>0)
	{
		CPU1TX.IDDR[Lu-1][Kuai-1].DADDR=addr;
		CPU1TX.IDDR[Lu-1][Kuai-1].DADDRCS=0xffffffff-CPU1TX.IDDR[Lu-1][Kuai-1].DADDR;
		CPU1TX.IDDR[Lu-1][Kuai-1].TEMP=0;
		CPU1TX.IDDR[Lu-1][Kuai-1].STATS=0;
		Xil_Out32(SaveAddr+Doffse,    CPU1TX.IDDR[Lu-1][Kuai-1].DADDR);
		Xil_Out32(SaveAddr+DCSoffse,  CPU1TX.IDDR[Lu-1][Kuai-1].DADDRCS);
		Xil_Out32(SaveAddr+TEMPSoffse,CPU1TX.IDDR[Lu-1][Kuai-1].TEMP);
		Xil_Out32(SaveAddr+STATSoffse,CPU1TX.IDDR[Lu-1][Kuai-1].STATS);
	}
}
/*************************************************************************
* ������void Bsp_WriteCPU1STATS (unsigned char Lu,unsigned char Kuai,unsigned int stats )
* ���ܣ�д��ͼƬ����ĵ�ַ״̬
*      1->����д��  2 ->д�����
************************************************************************* */
void Bsp_WriteCPU1STATS (unsigned char Lu,unsigned char Kuai,unsigned int stats )
{
	unsigned int SaveAddr;
	SaveAddr=Bsp_GetDDRBaseAddr(Lu,Kuai);
	if(SaveAddr>0)
	{
		CPU1TX.IDDR[Lu-1][Kuai-1].STATS=stats;
		Xil_Out32(SaveAddr+STATSoffse,CPU1TX.IDDR[Lu-1][Kuai-1].STATS);
	}
}


/****************************************************
 * unsigned char CPU0_NETEN(void)
 * CPU0,�Ƿ��ܿ���NET DMA
 * ����1��CPU0 ���� 0��CPU1����
 ****************************************************/
unsigned char CPU0_NETEN(void)
{
	if(0xa5a5!=Xil_In32(CPU1CMD_NETEN))return 1;
	return 0;
}
/****************************************************
 * int CPUO_NETtxCMD(void)
 * CPU0֪ͨCPU1����������Ҫ����

 ****************************************************/
void CPUO_NETtxCMD(void)
{
	Xil_Out32(CPU0CMD_NETTX,Xil_In32(CPU0CMD_NETTX)+1);
}
