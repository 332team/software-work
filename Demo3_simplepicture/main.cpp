#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")


int main()
{
	//����ͼ��space.jpg
	GDALDataset* poSrcDS1;
	GDALDataset* poSrcDS;
	//����ͼ��superman.jpg
	GDALDataset* poSrcDS2;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen1, imgYlen1;
	int imgXlen2, imgYlen2;
	
	//����ͼ��·��
	char* srcPath1 = "space.jpg";
	char* srcPath2 = "superman.jpg";
	//���ͼ��·��
	char* dstPath = "res.tif";
	//ͼ���ڴ�洢,�ı������ڴ�洢
	GByte *buffTmp,*buffTmpR1,*buffTmpR2,*buffTmpG1,*buffTmpG2,*buffTmpB1,*buffTmpB2;
	//ͼ�񲨶���
	int i, j, bandNum1,bandNum2;
	//ע������
	GDALAllRegister();
	//��ͼ��
	poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2, GA_ReadOnly);
	//��ȡͼ��Ŀ�ȣ��߶ȺͲ�����
	imgXlen1 = poSrcDS1->GetRasterXSize();
	imgYlen1 = poSrcDS1->GetRasterYSize();
	imgXlen2 = poSrcDS2->GetRasterXSize();
	imgYlen2 = poSrcDS2->GetRasterYSize();
	bandNum1 = poSrcDS1->GetRasterCount();
	bandNum2 = poSrcDS2->GetRasterCount();
	//����ͼ��Ŀ�Ⱥ͸߶ȷ����ڴ�
	//buffTmp = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath, imgXlen1, imgYlen1, bandNum1, GDT_Byte, NULL);
	//��ͼƬ������½���ͼƬ
/*	for (i = 0; i < bandNum1; i++)
	{
		poSrcDS->GetRasterBand(i + 1)->RasterIO(
			GF_Read, 0, 0, imgXlen1, imgYlen1, buffTmp, imgXlen1, imgYlen1, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(i + 1)->RasterIO(
			GF_Write, 0, 0, imgXlen1, imgYlen1, buffTmp, imgXlen1, imgYlen1, GDT_Byte, 0, 0);


	}*/
	//�����ڴ�
	
	//��ȡ��ɫͨ��������buffTmp�У�ֻ��Ϊ�˻�ȡ������
	buffTmpR1 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
	buffTmpB1 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
	buffTmpG1 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
		poSrcDS1->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen1, imgYlen1, buffTmpR1, imgXlen1, imgYlen1, GDT_Byte, 0, 0);
		//���ζ�ȡ����ͨ��������
		poSrcDS1->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen1, imgYlen1, buffTmpG1, imgXlen1, imgYlen1, GDT_Byte, 0, 0);
		poSrcDS1->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen1, imgYlen1, buffTmpB1, imgXlen1, imgYlen1, GDT_Byte, 0, 0);
		buffTmpR2 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
		buffTmpB2 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
		buffTmpG2 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
		poSrcDS2->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen2, imgYlen2, buffTmpR2, imgXlen2, imgYlen2, GDT_Byte, 0, 0);
		//���ζ�ȡ����ͨ��������
		poSrcDS2->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen2, imgYlen2, buffTmpG2, imgXlen2, imgYlen2, GDT_Byte, 0, 0);
		poSrcDS2->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen2, imgYlen2, buffTmpB2, imgXlen2, imgYlen2, GDT_Byte, 0, 0);
		//�������򣬽��½�ͼƬ������ı���ɫ

		for (j = 0; j < imgYlen2; j++)
			for (i = 0; i < imgXlen2; i++)
			{
				if (!(buffTmpR2[j*imgXlen2 + i] < 160 && buffTmpR2[j*imgXlen2 + i]>10 && buffTmpG2[j*imgXlen2 + i] > 100 && buffTmpG2[j*imgXlen2 + i] < 220 && buffTmpB2[j*imgXlen2 + i] > 10 && buffTmpB2[j*imgXlen2 + i] < 110))

				{
					buffTmpR1[j * imgXlen1 + i] = buffTmpR2[j * imgXlen1 + i];
					buffTmpG1[j * imgXlen1 + i] = buffTmpG2[j * imgXlen1 + i];
					buffTmpB1[j * imgXlen1 + i] = buffTmpB2[j * imgXlen1 + i];
				}

			}
		
	

		poDstDS->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, imgXlen1, imgYlen1, buffTmpR1, imgXlen1, imgYlen1, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 0, 0, imgXlen1, imgYlen1, buffTmpG1, imgXlen1, imgYlen1, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 0, 0, imgXlen1, imgYlen1, buffTmpB1, imgXlen1, imgYlen1, GDT_Byte, 0, 0);


	//����ڴ�
	//CPLFree(buffTmp);
	CPLFree(buffTmpR1);
	CPLFree(buffTmpG1);
	CPLFree(buffTmpB1);
	CPLFree(buffTmpR2);
	CPLFree(buffTmpB2);
	CPLFree(buffTmpG2);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);
	system("PAUSE");
	return 0;
}