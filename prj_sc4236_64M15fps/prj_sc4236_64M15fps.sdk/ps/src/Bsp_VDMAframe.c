#include "xparameters.h"
#include "xil_io.h"
#include  "Bsp_VDMAframe.h"

#define    VDMACONTROLIOADDR     XPAR_AXI_GPIO_0_BASEADDR   //vdma buffer IO
#define    GPIO2_DATA_ADDR       (VDMACONTROLIOADDR+0)
#define    GPIO2_TRI_ADDR        (VDMACONTROLIOADDR+4)

#define    GPIO1_DATA_ADDR       (VDMACONTROLIOADDR+8)
#define    GPIO1_TRI_ADDR        (VDMACONTROLIOADDR+12)

const unsigned char GrayCode[16]=
{
		0,1,3,2,7,6,4,5,
		7,6,4,5,0,1,3,2
};
const unsigned char FANGrayCode[8]=
{
		0,1,3,2,6,7,5,4,
};
/********************************************************************
 * ������void Bsp_VDMAframe_init(void)
 * ���ܣ�����IO����
 *********************************************************************/
void Bsp_VDMAframe_init(void)
{
	Xil_Out32(GPIO1_TRI_ADDR,0x3f);       // 1����Ϊ����
	//Xil_Out32(GPIO1_DATA_ADDR,0x8);    //
	Xil_Out32(GPIO2_TRI_ADDR,0);    // 2 ����Ϊ����
}
/********************************************************************
 * ������unsigned char Bsp_GetGrayCode(unsigned char sno)
 * ���ܣ����֡��
 *********************************************************************/
unsigned char Bsp_GetGrayCode(unsigned char sno)
{
	return GrayCode[sno];
}
/********************************************************************
 * ������unsigned int Bsp_ReadfreamSno(void)
 * ���ܣ���ȡ��ǰ�����ڴ����֡��
 *********************************************************************/
unsigned int Bsp_ReadfreamSno(void)
{
	unsigned int re;
	re=Xil_In32(GPIO1_DATA_ADDR);
	re = re&0x0f;
	//return GrayCode[re];
	return re;
}


/********************************************************************
 * ������void Bsp_SetSkipfreamSno(unsigned char Sno)
 * ���ܣ�������Ҫ������֡���
 * ���룺Sno  0 �ر�ͨ������  1~8 ��Ӧͨ������
 *********************************************************************/
void Bsp_SetSkipfreamSno(unsigned char Sno )
{
	//Sno--;
	Sno &=0xf;
	Xil_Out32(GPIO2_DATA_ADDR, Sno);   //
	//Xil_Out32(GPIO1_DATA_ADDR,FANGrayCode[Sno&7]);   //
}
/*�ú�����ȡcpu0���ڶ�ȡ��֡��Ȼ�󽫸�֡��֪ͨpl��������֡
 *
 * */
unsigned int get_cpu0_using_frame(void)
{

	unsigned int frame_no;
	frame_no = Bsp_ReadfreamSno();
	Bsp_SetSkipfreamSno(frame_no);
	return frame_no;
}
