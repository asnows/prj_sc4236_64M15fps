/***********************************************
 * ��2��CPU֮���ͨѶ������RAM��ʽ

 * ����ַ0xffff0000
 * д�룺Xil_Out32
 * ��ȡ ��Xil_In32
 * �����
 * -----------------ͼ�����ݰ�����Ϣ��---------------------------begin
 *
 * -----------------------CPU0д������-------------------------------Begin
 *  64*4
 *
 *  Vaid   0~3       --> ��ЧCPU0 д�룬4~7 Ϊ���ջ���ĵ�ַ
 *  D1     4~7       --> ���ջ���ĵ�ַ   -->
 *  D2     8~11      --> ���ջ������֤   --> D1+D2 =0xFFFFFFFF
 *  USE    12~15     --> 1->�������ڶ�����       2->�����Ѿ��������   ָ����DDRλ�á�D1�����Ա�CPU1��������
 *  SNO              --> RGB��� (SNO2 !=SNO)&&(USE2==2) ��ʼ���� �������SNO=SNO2
 *  -----------------------CPU0д������-------------------------------end
 *
 *  -----------------------CPU1д������-------------------------------Begin
 *  64*4
 *  Err    0~3       --> ֪ͨCPU0 ����������D1+D2 У�����
 *  USE2   4~7       --> 1 ->��������д��D1,2->�����Ѿ�д����� CPU0���԰���
 *  SNO2             --> RGB���  �ۼ�+1
 *  LEN              --> RGB�ĳ���
 *  VV               --> RGB������                   ��
 *  HH               --> RGB���������� ����  ��
 *  -----------------------CPU1д������-------------------------------End
 * �������̣�
 * CPU0��ʼ������
 *    ���ٻ��壺�������ͼƬ  ���ѵ�ַ����D1,D2=0xFFFFFFFF-D1 д        Vaid=0x55555555  USE=2
 * CPU1д�빤��
 * 	  1��    Vaid=0x55555555    USE!=0      ��ַ��Ч�Լ��
 * 	  2   USE2=1 ��������
 * 	  3   SNO2++��USE2=2
 * CPU0��ȡ���ݹ���
 *   1��     USE2=2��SNO2!=SNO Err=0  ��ַ��Ч�Լ��
 *   2   USE=1���������ݣ� SNO=SNO2 USE=2
 *   3
 * ��ַ��Ч�Լ�� ʧ�ܴ���
 *      ��Ҫ���³�ʼ��
 ***********************************************/
//#include "Bsp_TwoCPU.h"
#ifndef BSP_TWOCPU_H_
#define BSP_TWOCPU_H_
#include "Bsp_RGB_Samp.h"
#define MAXLU         1   //�������·��
#define MAXDDRNUM     8   //����DDR���·��  Bsp_RGB_Samp.h�ж���

#define CPU0TXBASE          0xffff0000
#define CPU0CMDADDR         (CPU0TXBASE+0)
#define USESTATS1ADDR 		(CPU0TXBASE+16*4)    //
#define USESTATS2ADDR 		(CPU0TXBASE+16*4*2)
#define USESTATS3ADDR 		(CPU0TXBASE+16*4*3)
#define USESTATS4ADDR       (CPU0TXBASE+16*4*4)

//#define READ_REG_ADDR (CPU0TXBASE+16*4*5)//���������������ʾ����λ����Ҫ��ȡ�Ĵ�����ֵʱ������Ҫ��ȡ�ļĴ�����ֵ,����ʱ����Ҫ���䣬ʹ��ԭ������ķ����������ݵ���Ϣ����ǰ2���ֽڣ���������֪ͨ����


#define SENSORADDR           (CPU0TXBASE+128*4)
#define SENSORLEN            (64*4)

#define FGPAADDR             (SENSORADDR+SENSORLEN)
#define FGPALEN              (8*32)

#define NETCONTROL           (CPU0TXBASE+0x0ff8)
#define CPU1CMD_NETEN        NETCONTROL
#define CPU0CMD_NETTX        (NETCONTROL+4)

//---------------------------------------CPU1 д����----------------------Begin
#define CPU1TXBASE      (0xffff1000)
#define D1DDRBASE       (0xffff1000 + 128*4)
#define D2DDRBASE       (0xffff1000 + 128*4*2)
#define D3DDRBASE       (0xffff1000 + 128*4*3)
#define D4DDRBASE       (0xffff1000 + 128*4*4)

#define READ_DATA_ADDR (0xffff1000 + 128*4*5)//�����ȡreg���ݵĴ�������б�Ҫ���룬ͨ������֪ͨcpu0

//-----------------------��Ϣ��----------------------Begin
#define CPU1CMDADDR 	(CPU1TXBASE+0)
#define	DOBMPMAXADDR    (CPU1TXBASE+4)

#define FSignBASE       (CPU1TXBASE+16*4)
#define SSignBASE       (CPU1TXBASE+16*4*2)
#define TSignBASE       (CPU1TXBASE+16*4*3)
#define LSignBASE       (CPU1TXBASE+16*4*4)

#define RECUSE1ADDR    (FSignBASE+0)
#define BMPMAX1ADDR    (FSignBASE+4)
#define SNO1ADDR       (FSignBASE+8)


#define RECUSE2ADDR    (SSignBASE+0)
#define BMPMAX2ADDR    (SSignBASE+4)
#define SNO2ADDR       (SSignBASE+8)


#define RECUSE3ADDR    (TSignBASE+0)
#define BMPMAX3ADDR    (TSignBASE+4)
#define SNO3ADDR       (TSignBASE+8)


#define RECUSE4ADDR    (LSignBASE+0)
#define BMPMAX4ADDR    (LSignBASE+4)
#define SNO4ADDR       (LSignBASE+8)
//-----------------------��Ϣ��----------------------End
#define Doffse         0
#define DCSoffse       4
#define TEMPSoffse     8
#define STATSoffse     12
//  ��Ҫͨ������ ���� ʵ�ʵ������ַ

//---------------------------------------CPU1 д����----------------------End

extern void Bsp_TwoCPU_Init(void);
/*************************************************************************
* ������unsigned int Bsp_GetDDRBaseAddr(unsigned char Lu,unsigned char Kuai)
* ��ȡ��ÿ·��Ϣ�׵�ַ
* ��Σ�Lu ����· 1~MAXLU   Kuai:DDR�Ŀ��  1~MAXDDRNUM
************************************************************************* */
extern unsigned int Bsp_GetDDRBaseAddr(unsigned char Lu,unsigned char Kuai);

/*************************************************************************
* ����  void Bsp_GetCPU0TX(void)
* ��ȡ�� ��ȡCPU0 ��ͨѶ����
************************************************************************* */
extern void Bsp_GetCPU0TX(void);

/*************************************************************************
* ����  unsigned int Bsp_ReadCPU0CMD(void)
* ��ȡ�� ��ȡCPU����������
************************************************************************* */
extern unsigned int Bsp_ReadCPU0CMD(void);
/*************************************************************************
* ������ unsigned int Bsp_ReadCPU0USESTATS(unsigned char Lu)
* ��ȡ�� ��ȡ��ǰCPU0 ����ʹ���Ŀ�DDR
************************************************************************* */
extern unsigned int Bsp_ReadCPU0USESTATS(unsigned char Lu);
 /*************************************************************************
* ����  void Bsp_WriteCPU1SNO(unsigned char Lu,unsigned int SNO2)
* ��ȡ����Ӧ·���������� ͳ��
************************************************************************* */
extern void Bsp_WriteCPU1SNO(unsigned char Lu,unsigned int SNO2);
/*************************************************************************
* ����  void Bsp_WriteCPU1RECUSE(unsigned char Lu,unsigned int RECUSE)
* ��ȡ����Ӧ·�����ĵ�ǰ��������ͨ����
************************************************************************* */
extern void Bsp_WriteCPU1RECUSE(unsigned char Lu,unsigned int RECUSE);
/*************************************************************************
* ����  void Bsp_WriteCPU1RECUSE(unsigned char Lu,unsigned int RECUSE)
* ��ȡ��д��ÿ��ͨ������������
************************************************************************* */
extern void Bsp_WriteCPU1BMPMAX(unsigned char Lu,unsigned int BMPMAX);
/*************************************************************************
* ������void Bsp_WriteCPU1DOBMPMAX (unsigned int DOBMPMAX )
* ��ȡ��д�����ݲ�����·��
************************************************************************* */
extern void Bsp_WriteCPU1DOBMPMAX (unsigned int DOBMPMAX );
/*************************************************************************
* ������void Bsp_WriteCPU1CPU1CMD (unsigned int CPU1CMD )
* ��ȡ��д��CPU1��ִ�й�������
************************************************************************* */
extern void Bsp_WriteCPU1CPU1CMD (unsigned int CPU1CMD );
/*************************************************************************
* ������void Bsp_ReadCPU1CPU1CMD (unsigned int CPU1CMD )
* ��ȡ����ȡCPU1��ִ�й�������
************************************************************************* */
extern unsigned int Bsp_ReadCPU1CPU1CMD (unsigned int CPU1CMD );
/*************************************************************************
* ������void Bsp_WriteCPU1LuDDR (unsigned char Lu,unsigned char Kuai,unsigned int addr )
* ���ܣ�д��ͼƬ����ĵ�ַ
************************************************************************* */
extern void Bsp_WriteCPU1LuDDR (unsigned char Lu,unsigned char Kuai,unsigned int addr );
/*************************************************************************
* ������void Bsp_WriteCPU1STATS (unsigned char Lu,unsigned char Kuai,unsigned int stats )
* ���ܣ�д��ͼƬ����ĵ�ַ״̬
*      1->����д��  2 ->д�����
************************************************************************* */
extern void Bsp_WriteCPU1STATS (unsigned char Lu,unsigned char Kuai,unsigned int stats );
/*��ȡcpu0���ڶ�ȡ��֡�ţ��Ա�֪ͨpl����*/
extern unsigned int get_cpu0_using_frame(void);
#endif
