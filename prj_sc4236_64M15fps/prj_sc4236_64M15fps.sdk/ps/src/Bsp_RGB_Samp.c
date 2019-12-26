/**************************************************************************************************
 * �ļ���Bsp_RGB_Samp.c
 * ���ܣ���RGB���ݽ��в���������CPU1�������ݽ���
 * 	   1������32֡���RGB���ݵĿռ�
 *************************************************************************************************/
#include "Bsp_RGB_Samp.h"
#include "xil_mmu.h"
#include "string.h"
typedef struct RGBSamp_
{
	unsigned int *Framesp[MAXDDRNUM];
	unsigned char FrmaeNum;
}RGBSampstr;

#define RGBBuff  (0x1EE00000-8*0x1000000)

//unsigned char RGBBuff[RGBBUFFLEN] __attribute__ ((aligned (0x100000)));
RGBSampstr RGBSamp;
/************************************************************************************************
 * ������void Bsp_RGBBuff_Init()
 * ���ܣ���ʼ��Buff,�޸����� ����PL��2��CPU�����Զ�ȡ
 ************************************************************************************************/
void Bsp_RGBBuff_Init(void)
{
	unsigned int i;
	signed int addr;
	addr = (signed int)RGBBuff;
	//i=RGBBUFFLEN;
	//i&=0xfff00000;  //ȷ��i��0x10000�ı���
	//if (i==0)return ;
	i=128;
	while(i--)
	{
		Xil_SetTlbAttributes((signed int)addr, 0xc02); // addr, attr
		addr = addr + 0x100000;
		//i = i-0x100000;
	}
	for (i=0;i<MAXDDRNUM ;i++)
	{
		RGBSamp.Framesp[i]=0;
	}
}
/************************************************************************************************
 * ������void Bsp_GetpFrames(unsigned char **OutP,unsigned char Num)
 * ���ܣ� Ϊÿ֡RGBͼƬ�����Ӧ�Ļ���ָ��
 * ��Σ�**OutP ���뱣��ָ���ָ�� H: �����أ�V �� ����  Num ֡����
 * ע��    H<=MAXRGBHORISIZE    �������1
 *     V<=MAXRGBVERTSIZE    �������2
 *     Num ȡֵ 1-32          �������3
 ************************************************************************************************/
unsigned char Bsp_RGB_GetpFrames(unsigned int **OutP,unsigned int H,unsigned int V,unsigned char Num)
{
		unsigned int L;
		unsigned int addr;
		unsigned int fristaddr;
		unsigned char i;

		if (H>MAXRGBHORISIZE)return  1;
		if (V>MAXRGBVERTSIZE)return  2;
		if((Num>MAXDDRNUM)||(Num==0))return  3;

		L= H *V *1;//һ֡RGBռ�õ�Buff ��
		L =L & 0xFFFFFFF0;//16�ֶ���
		L= L + 0x800;//ÿ��ͼƬ����2K�Ŀռ䣬���ڱ���������Ϣ
		//L = L+0x100000;//1M
		//L = L&0xfffE0000;//1M����
		fristaddr = (unsigned int)RGBBuff +0x800;//ƫ��2K
		for(i=0;i<Num;i++)
		{
			addr =fristaddr+i*L;

			*OutP=addr;
			RGBSamp.Framesp[i]=(unsigned char*) addr;
			OutP +=1;
		}
		RGBSamp.FrmaeNum=Num;
		return 0;
}

