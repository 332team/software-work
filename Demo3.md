

 **```**

```c++
 #include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")


int main()
{
	//输入图像space.jpg
	GDALDataset* poSrcDS1;
	GDALDataset* poSrcDS;
	//输入图像superman.jpg
	GDALDataset* poSrcDS2;
	//输出图像
	GDALDataset* poDstDS;
	//图像的宽度和高度
	int imgXlen1, imgYlen1;
	int imgXlen2, imgYlen2;
	
	//输入图像路径
	char* srcPath1 = "space.jpg";
	char* srcPath2 = "superman.jpg";
	//输出图像路径
	char* dstPath = "res.tif";
	//图像内存存储,改变区域内存存储
	GByte *buffTmp,*buffTmpR1,*buffTmpR2,*buffTmpG1,*buffTmpG2,*buffTmpB1,*buffTmpB2;
	//图像波段数
	int i, j, bandNum1,bandNum2;
	//注册驱动
	GDALAllRegister();
	//打开图像
	poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2, GA_ReadOnly);
	//获取图像的宽度，高度和波段数
	imgXlen1 = poSrcDS1->GetRasterXSize();
	imgYlen1 = poSrcDS1->GetRasterYSize();
	imgXlen2 = poSrcDS2->GetRasterXSize();
	imgYlen2 = poSrcDS2->GetRasterYSize();
	bandNum1 = poSrcDS1->GetRasterCount();
	bandNum2 = poSrcDS2->GetRasterCount();
	//根据图像的宽度和高度分配内存
	//buffTmp = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
	//创建输出图像
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath, imgXlen1, imgYlen1, bandNum1, GDT_Byte, NULL);
	//将图片输出到新建的图片
/*	for (i = 0; i < bandNum1; i++)
	{
		poSrcDS->GetRasterBand(i + 1)->RasterIO(
			GF_Read, 0, 0, imgXlen1, imgYlen1, buffTmp, imgXlen1, imgYlen1, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(i + 1)->RasterIO(
			GF_Write, 0, 0, imgXlen1, imgYlen1, buffTmp, imgXlen1, imgYlen1, GDT_Byte, 0, 0);


	}*/
	//分配内存
	
	//读取红色通道缓存在buffTmp中，只是为了获取该区域
	buffTmpR1 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
	buffTmpB1 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
	buffTmpG1 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
		poSrcDS1->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen1, imgYlen1, buffTmpR1, imgXlen1, imgYlen1, GDT_Byte, 0, 0);
		//依次读取三个通道的像素
		poSrcDS1->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen1, imgYlen1, buffTmpG1, imgXlen1, imgYlen1, GDT_Byte, 0, 0);
		poSrcDS1->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen1, imgYlen1, buffTmpB1, imgXlen1, imgYlen1, GDT_Byte, 0, 0);
		buffTmpR2 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
		buffTmpB2 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
		buffTmpG2 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
		poSrcDS2->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen2, imgYlen2, buffTmpR2, imgXlen2, imgYlen2, GDT_Byte, 0, 0);
		//依次读取三个通道的像素
		poSrcDS2->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen2, imgYlen2, buffTmpG2, imgXlen2, imgYlen2, GDT_Byte, 0, 0);
		poSrcDS2->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen2, imgYlen2, buffTmpB2, imgXlen2, imgYlen2, GDT_Byte, 0, 0);
		//遍历区域，将新建图片该区域改变颜色

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


	//清除内存
	//CPLFree(buffTmp);
	CPLFree(buffTmpR1);
	CPLFree(buffTmpG1);
	CPLFree(buffTmpB1);
	CPLFree(buffTmpR2);
	CPLFree(buffTmpB2);
	CPLFree(buffTmpG2);
	//关闭dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);
	system("PAUSE");
	return 0;
}
```