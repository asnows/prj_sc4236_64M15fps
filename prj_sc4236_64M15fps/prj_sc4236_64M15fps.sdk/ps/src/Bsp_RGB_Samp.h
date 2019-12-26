// #include "Bsp_RGB_Samp.h"
#ifndef BSP_RGB_SAMP_H_
#define BSP_RGB_SAMP_H_

#define MAXLU           1   //�������·��
#define MAXDDRNUM       4
#define MAXRGBHORISIZE  1920    //֧�ֵ���� �����
#define MAXRGBVERTSIZE  1280     //֧�ֵ���� ������
#define ONERGBBUUFLEN   (MAXRGBHORISIZE * MAXRGBVERTSIZE * 4 + 0x800)  //1��ͼƬ��RGB��Ҫ�Ļ��� ÿ��ͼƬ��2K
#define RGBBUFFLEN      ((ONERGBBUUFLEN *MAXDDRNUM+0x100000) & 0xFFF00000)//RGB��Ҫ�����Ҫ�Ļ����С ��С��λ1M 8��+1M��С

/************************************************************************************************
 * ������void Bsp_RGBBuff_Init()
 * ���ܣ���ʼ��Buff,�޸����� ����PL��2��CPU�����Զ�ȡ
 ************************************************************************************************/
extern void Bsp_RGBBuff_Init(void);
/************************************************************************************************
 * ������void Bsp_GetpFrames(unsigned char **OutP,unsigned char Num)
 * ���ܣ� Ϊÿ֡RGBͼƬ�����Ӧ�Ļ���ָ��
 * ��Σ�**OutP ���뱣��ָ���ָ�� H: �����أ�V �� ����  Num ֡����
 * ע��    H<=MAXRGBHORISIZE    �������1
 *     V<=MAXRGBVERTSIZE    �������2
 *     Num ȡֵ 1-32          �������3
 ************************************************************************************************/
extern unsigned char Bsp_RGB_GetpFrames(unsigned int **OutP,unsigned int H,unsigned int V,unsigned char Num);
/************************************************************************************************
 * ������unsigned char * Bsp_ScanvaildFrame(void)
 * ���ܣ�  ������Ч��֡  1ms ֮�ڵ���һ��
 * ����ֵ��������Ч������֡���
 ************************************************************************************************/
extern unsigned char * Bsp_RGB_ScanvaildFrame(void);
extern unsigned char Bsp_RGB_ScanvaildFrameIndex(void);
/************************************************************************************************
 * ������void Bsp_RGB_FrameToCPU0(unsigned char *InBuff)
 * ���ܣ�  �����յ����ݰ��˵�CPU0ָ����DDR��
 * ����ֵ��
 ************************************************************************************************/
extern void Bsp_RGB_FrameToCPU0(unsigned char InDex);
extern unsigned char *Bsp_RGB_GetFrameP(unsigned char index);
extern unsigned int Bsp_RGB_GetFrameAddr(unsigned char index);
#endif
