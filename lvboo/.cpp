#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")
int  a[3][3] = { 0,1,0,1,1,1,0,1,0 };
int b[5][5] = { 1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1 };
int c[3][3] = { -1,-1,-1,-1,8,-1,-1,-1,-1 };
int d[3][3] = { -1,-1,-1,-1,9,-1,-1,-1,-1 };
double e[3][3] = { -1,-1,0,-1,0,1,0,1,1 };
float f[5][5] = { 0.0120,0.1253,0.2736,0.1253,0.0120,0.1253,1.3054,2.8514,1.3054,0.1253,2.2736,2.8514,6.2279,2.8514,0.2736,0.1253,1.3054,2.8514,1.3054,0.1253,0.0120,0.1253,0.2736,0.1253,0.0120 };
int boxFilter(float* imgIn, float* imgOut, int imgXlen, int imgYlen);
// The second conv filter
int motionFilter(float* imgIn, float* imgOut, int imgXlen, int imgYlen);
// The third conv filter
int edgeFilter(float* imgIn, float* imgOut, int imgXlen, int imgYlen);
// The fourth conv filter
int sharpenFilter(float* imgIn, float* imgOut, int imgXlen, int imgYlen);
// The fifth conv filter
int embossFilter(float* imgIn, float* imgOut, int imgXlen, int imgYlen);
// The sixth conv filter
int gaussFilter(float* imgIn, float* imgOut, int imgXlen, int imgYlen);
int imFilter(char* pathIn, char* pathOut, int flag);
int imFilter(char * pathIn, char * pathOut, int flag)
{
	int imgXlen1, imgYlen1,bandNum;
	GDALDataset* poDstDS;
	GDALDataset* poSrcDS;
	poSrcDS = (GDALDataset*)GDALOpenShared(pathIn, GA_ReadOnly);
	imgXlen1 = poSrcDS->GetRasterXSize();
	imgYlen1 = poSrcDS->GetRasterYSize();

	bandNum = poSrcDS->GetRasterCount();

	//根据图像的宽度和高度分配内存
GByte *buffTmpR1, *buffTmpB1, *buffTmpG1, *bufftmp1, *bufftmp2, *bufftmp3;
	//创建输出图像
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		pathOut, imgXlen1, imgYlen1, bandNum, GDT_Byte, NULL);
	//将图片输出到新建的图片
	buffTmpR1 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
	buffTmpB1 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
	buffTmpG1 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
	bufftmp1 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
	bufftmp2 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
	bufftmp3 = (GByte*)CPLMalloc(imgXlen1*imgYlen1 * sizeof(GByte));
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen1, imgYlen1, buffTmpR1, imgXlen1, imgYlen1, GDT_Float32, 0, 0);
	//依次读取三个通道的像素
	poSrcDS->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen1, imgYlen1, buffTmpG1, imgXlen1, imgYlen1, GDT_Float32, 0, 0);
	poSrcDS->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen1, imgYlen1, buffTmpB1, imgXlen1, imgYlen1, GDT_Float32, 0, 0);
	int i, j;

	//遍历区域，将新建图片该区域改变颜色

	if (flag == 1)
	{
		double tempR = 0;
		double tempG = 0;
		double tempB = 0;
		for (j = 0; j < imgYlen1; j++)
			for (i = 0; i < imgXlen1; i++)
			{
				if (j == 0 || i == 0 || j == imgYlen1 - 1 || i == imgXlen1 - 1)
				{
					tempR = 0;
					tempG = 0;
					tempB = 0;
				}
				else
				{
					tempR = 0;
					tempG = 0;
					tempB = 0;
					for (int m = 0; m < 3; m++)//第一个卷积核
					{
						for (int n = 0; n < 3; n++)
						{
							tempR += (double)buffTmpR1[(j + m - 1) * imgXlen1 + (i + n - 1)] * a[m][n];
							tempG += (double)buffTmpG1[(j + m - 1) * imgXlen1 + (i + n - 1)] * a[m][n];
							tempB += (double)buffTmpB1[(j + m - 1) * imgXlen1 + (i + n - 1)] * a[m][n];

						}
					}
				}
				bufftmp1[j * imgXlen1 + i] = tempR*0.2;
		bufftmp2[j * imgXlen1 + i] = tempG*0.2;
		bufftmp3[j * imgXlen1 + i] = tempB*0.2;
			}
		

	}
	else if (flag == 2)
	{
		double tempR = 0;
		double tempG = 0;
		double tempB = 0;
		for (j = 0; j < imgYlen1; j++)
			for (i = 0; i < imgXlen1; i++)
			{
				if (j == 0 || i == 0 || j == imgYlen1 - 1 || i == imgXlen1 - 1)
				{
					tempR = 0;
					tempG = 0;
					tempB = 0;
				}
				else
				{
					tempR = 0;
					tempG = 0;
					tempB = 0;
					for (int m = 0; m < 5; m++)//第一个卷积核
					{
						for (int n = 0; n < 5; n++)
						{
							tempR += (double)buffTmpR1[(j + m - 1) * imgXlen1 + (i + n - 1)] * b[m][n];
							tempG += (double)buffTmpG1[(j + m - 1) * imgXlen1 + (i + n - 1)] * b[m][n];
							tempB += (double)buffTmpB1[(j + m - 1) * imgXlen1 + (i + n - 1)] * b[m][n];

						}
					}
				}
				bufftmp1[j * imgXlen1 + i] = tempR*0.2;
		bufftmp2[j * imgXlen1 + i] = tempG*0.2;
		bufftmp3[j * imgXlen1 + i] = tempB*0.2;
			}
		
	}
	else if (flag == 3)
	{
		double tempR = 0;
		double tempG = 0;
		double tempB = 0;
		for (j = 0; j < imgYlen1; j++)
			for (i = 0; i < imgXlen1; i++)
			{
				if (j == 0 || i == 0 || j == imgYlen1 - 1 || i == imgXlen1 - 1)
				{
					tempR = 0;
					tempG = 0;
					tempB = 0;
				}
				else
				{
					tempR = 0;
					tempG = 0;
					tempB = 0;
					for (int m = 0; m < 3; m++)//第一个卷积核
					{
						for (int n = 0; n < 3; n++)
						{
							tempR += (double)buffTmpR1[(j + m - 1) * imgXlen1 + (i + n - 1)] * c[m][n];
							tempG += (double)buffTmpG1[(j + m - 1) * imgXlen1 + (i + n - 1)] * c[m][n];
							tempB += (double)buffTmpB1[(j + m - 1) * imgXlen1 + (i + n - 1)] * c[m][n];

						}
					}
				}
				bufftmp1[j * imgXlen1 + i] = tempR;
		bufftmp2[j * imgXlen1 + i] = tempG;
		bufftmp3[j * imgXlen1 + i] = tempB;
			}
		

	}
	else if (flag == 4)
	{
		double tempR = 0;
		double tempG = 0;
		double tempB = 0;
		for (j = 0; j < imgYlen1; j++)
			for (i = 0; i < imgXlen1; i++)
			{
				if (j == 0 || i == 0 || j == imgYlen1 - 1 || i == imgXlen1 - 1)
				{
					tempR = 0;
					tempG = 0;
					tempB = 0;
				}
				else
				{
					tempR = 0;
					tempG = 0;
					tempB = 0;
					for (int m = 0; m < 3; m++)//第一个卷积核
					{
						for (int n = 0; n < 3; n++)
						{
							tempR += (double)buffTmpR1[(j + m - 1) * imgXlen1 + (i + n - 1)] * d[m][n];
							tempG += (double)buffTmpG1[(j + m - 1) * imgXlen1 + (i + n - 1)] * d[m][n];
							tempB += (double)buffTmpB1[(j + m - 1) * imgXlen1 + (i + n - 1)] * d[m][n];

						}
					}
				}
				bufftmp1[j * imgXlen1 + i] = tempR;
		bufftmp2[j * imgXlen1 + i] = tempG;
		bufftmp3[j * imgXlen1 + i] = tempB;
			}
		
	}
	else if (flag == 5)
	{
		double tempR = 0;
		double tempG = 0;
		double tempB = 0;
		for (j = 0; j < imgYlen1; j++)
			for (i = 0; i < imgXlen1; i++)
			{
				if (j == 0 || i == 0 || j == imgYlen1 - 1 || i == imgXlen1 - 1)
				{
					tempR = 0;
					tempG = 0;
					tempB = 0;
				}
				else
				{
					tempR = 0;
					tempG = 0;
					tempB = 0;
					for (int m = 0; m < 3; m++)//第一个卷积核
					{
						for (int n = 0; n < 3; n++)
						{
							tempR += (double)buffTmpR1[(j + m - 1) * imgXlen1 + (i + n - 1)] * e[m][n];
							tempG += (double)buffTmpG1[(j + m - 1) * imgXlen1 + (i + n - 1)] * e[m][n];
							tempB += (double)buffTmpB1[(j + m - 1) * imgXlen1 + (i + n - 1)] * e[m][n];

						}
					}
		
				}bufftmp1[j * imgXlen1 + i] = tempR+128;
		bufftmp2[j * imgXlen1 + i] = tempG+128;
		bufftmp3[j * imgXlen1 + i] = tempB+128;
			}
		
	}
	else if (flag == 6)
	{
		double tempR = 0;
		double tempG = 0;
		double tempB = 0;
		for (j = 0; j < imgYlen1; j++)
			for (i = 0; i < imgXlen1; i++)
			{
				if (j == 0 || i == 0 || j == imgYlen1 - 1 || i == imgXlen1 - 1)
				{
					tempR = 0;
					tempG = 0;
					tempB = 0;
				}
				else
				{
					tempR = 0;
					tempG = 0;
					tempB = 0;
					for (int m = 0; m < 5; m++)//第一个卷积核
					{
						for (int n = 0; n < 5; n++)
						{
							tempR += (double)buffTmpR1[(j + m - 1) * imgXlen1 + (i + n - 1)] * f[m][n];
							tempG += (double)buffTmpG1[(j + m - 1) * imgXlen1 + (i + n - 1)] * f[m][n];
							tempB += (double)buffTmpB1[(j + m - 1) * imgXlen1 + (i + n - 1)] * f[m][n];

						}
					}
					
					
				}
				bufftmp1[j * imgXlen1 + i] = tempR/25;
		bufftmp2[j * imgXlen1 + i] = tempG/25;
		bufftmp3[j * imgXlen1 + i] = tempB/25;
			}
		
	}
	else
	{
		double tempR = 0;
		double tempG = 0;
		double tempB = 0;
		for (j = 0; j < imgYlen1; j++)
			for (i = 0; i < imgXlen1; i++)
			{
				if (j == 0 || i == 0 || j == imgYlen1 - 1 || i == imgXlen1 - 1)
				{
					tempR = 0;
					tempG = 0;
					tempB = 0;
				}
				else
				{
					tempR = 0;
					tempG = 0;
					tempB = 0;
					for (int m = 0; m < 5; m++)//第一个卷积核
					{
						for (int n = 0; n < 5; n++)
						{
							tempR += (double)buffTmpR1[(j + m - 1) * imgXlen1 + (i + n - 1)] * f[m][n];
							tempG += (double)buffTmpG1[(j + m - 1) * imgXlen1 + (i + n - 1)] * f[m][n];
							tempB += (double)buffTmpB1[(j + m - 1) * imgXlen1 + (i + n - 1)] * f[m][n];

						}
					}
				}bufftmp1[j * imgXlen1 + i] = tempR / 25;
		bufftmp2[j * imgXlen1 + i] = tempG / 25;
		bufftmp3[j * imgXlen1 + i] = tempB / 25;
			}
		
	}
	
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, imgXlen1, imgYlen1, bufftmp1, imgXlen1, imgYlen1, GDT_Float32 , 0, 0);
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 0, 0, imgXlen1, imgYlen1, bufftmp2, imgXlen1, imgYlen1, GDT_Float32, 0, 0);
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 0, 0, imgXlen1, imgYlen1, bufftmp3, imgXlen1, imgYlen1, GDT_Float32, 0, 0);
	CPLFree(buffTmpR1);
	CPLFree(buffTmpG1);
	CPLFree(buffTmpB1);
	CPLFree(bufftmp1);
	CPLFree(bufftmp2);
	CPLFree(bufftmp3);

	//关闭dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);
	system("PAUSE");
	return 0;
}
int boxFilter(float * imgIn, float * imgOut, int imgXlen, int imgYlen)
{
	return 0;
}
int motionFilter(float * imgIn, float * imgOut, int imgXlen, int imgYlen)
{
	return 0;
}
int edgeFilter(float * imgIn, float * imgOut, int imgXlen, int imgYlen)
{
	return 0;
}
int sharpenFilter(float * imgIn, float * imgOut, int imgXlen, int imgYlen)
{
	return 0;
}
int embossFilter(float * imgIn, float * imgOut, int imgXlen, int imgYlen)
{
	return 0;
}
int gaussFilter(float * imgIn, float * imgOut, int imgXlen, int imgYlen)
{
	return 0;
}
int main()
{
	int  a[3][3] = { 0,1,0,1,1,1,0,1,0 };
	int b[5][5] = {1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1};
	int c[3][3] = { -1,-1,-1,-1,8,-1,-1,-1,-1};
	int d[3][3] = { -1,-1,-1,-1,9,-1,-1,-1,-1 };
	double e[3][3] = {-1,-1,0,-1,0,1,0,1,1};
	float f[5][5] = { 0.0120,0.1253,0.2736,0.1253,0.0120,0.1253,1.3054,2.8514,1.3054,0.1253,2.2736,2.8514,6.2279,2.8514,0.2736,0.1253,1.3054,2.8514,1.3054,0.1253,0.0120,0.1253,0.2736,0.1253,0.0120 };
	//输入图像space.jpg




	//输出图像

	//图像的宽度和高度
	//int imgXlen1, imgYlen1;


	//输入图像路径
	char* srcPath = "lina.jpg";
	GDALAllRegister();
	imFilter(srcPath, "resc1.tif", 1);
	imFilter(srcPath, "resc2.tif", 2);
	imFilter(srcPath, "resc3.tif", 3);
	imFilter(srcPath, "resc4.tif",4);
	imFilter(srcPath, "resc5.tif", 5);
	imFilter(srcPath, "resc6.tif", 6);
	return 0;
}



