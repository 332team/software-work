

 **```**

```c++
#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")


int main()
{
	//输入图像
	GDALDataset* poSrcDS;
	//输出图像
	GDALDataset* poDstDS;
	//图像的宽度和高度

	int StartX1 = 100, StartY1 = 100;
	//区域宽度和高度
	int tmpXlen1 = 100, tmpYlen1 = 50;
	int imgXlen, imgYlen;
	//起始位置坐标
	int StartX2 = 500, StartY2 = 500;
	//区域宽度和高度
	int tmpXlen2 = 50, tmpYlen2 = 100;
	//输入图像路径
	char* srcPath = "trees.jpg";
	//输出图像路径
	char* dstPath = "res.tif";
	//图像内存存储,改变区域内存存储
	GByte* buffTmp, *buffTmp1;
	//图像波段数
	int i, j, bandNum;
	//注册驱动
	GDALAllRegister();
	//打开图像
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);
	//获取图像的宽度，高度和波段数
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();

	//根据图像的宽度和高度分配内存
	buffTmp1 = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	//创建输出图像
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	//将图片输出到新建的图片
	for (i = 0; i < bandNum; i++)
	{
		poSrcDS->GetRasterBand(i + 1)->RasterIO(
			GF_Read, 0, 0, imgXlen, imgYlen, buffTmp1, imgXlen, imgYlen, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(i + 1)->RasterIO(
			GF_Write, 0, 0, imgXlen, imgYlen, buffTmp1, imgXlen, imgYlen, GDT_Byte, 0, 0);


	}
	//分配内存
	buffTmp = (GByte*)CPLMalloc(tmpXlen1*tmpYlen1 * sizeof(GByte));
	//读取红色通道缓存在buffTmp中，只是为了获取该区域
	for (int n = 0; n < 3; n++)
	{
	poSrcDS->GetRasterBand(n+1)->RasterIO(GF_Read, StartX1, StartY1, tmpXlen1, tmpYlen1, buffTmp, tmpXlen1, tmpYlen1, GDT_Byte, 0, 0);
	//依次读取三个通道的像素
	//遍历区域，将新建图片该区域改变颜色
	for (j = 0; j < tmpYlen1; j++)
		for (i = 0; i < tmpXlen1; i++)
		{
			buffTmp[j * tmpXlen1 + i] = (GByte)255;
		}
	poDstDS->GetRasterBand(n+1)->RasterIO(GF_Write, StartX1, StartY1, tmpXlen1, tmpYlen1, buffTmp, tmpXlen1, tmpYlen1, GDT_Byte, 0, 0);

	}
	buffTmp = (GByte*)CPLMalloc(tmpXlen2*tmpYlen2 * sizeof(GByte));
	//读取红色通道缓存在buffTmp中，只是为了获取该区域
	for (int n = 0; n < 3; n++)
	{
		poSrcDS->GetRasterBand(n + 1)->RasterIO(GF_Read, StartX2, StartY2, tmpXlen2, tmpYlen2, buffTmp, tmpXlen2, tmpYlen2, GDT_Byte, 0, 0);
		//依次读取三个通道的像素
		//遍历区域，将新建图片该区域改变颜色
		for (j = 0; j < tmpYlen2; j++)
			for (i = 0; i < tmpXlen2; i++)
			{
				buffTmp[j * tmpXlen2 + i] = (GByte)0;
			}
		poDstDS->GetRasterBand(n + 1)->RasterIO(GF_Write, StartX2, StartY2, tmpXlen2, tmpYlen2, buffTmp, tmpXlen2, tmpYlen2, GDT_Byte, 0, 0);

	}
	//poSrcDS->GetRasterBand(2)->RasterIO(GF_Read, StartX1, StartY1, tmpXlen1, tmpYlen1, buffTmp, tmpXlen1, tmpYlen1, GDT_Byte, 0, 0);

	



	//清除内存
	CPLFree(buffTmp);
	CPLFree(buffTmp1);
	//关闭dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);
	system("PAUSE");
	return 0;
}

```