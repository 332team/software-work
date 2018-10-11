`首先，`**安装**

因为图形学课的需要把自己已经装好的vs2017卸掉了重新装vs2015，心里很忐忑，害怕因为2017没卸干净，导致出问题，但是锦鲤如我，没问题！（过两天我室友就出问题了。。。）

`干活`

安装好了后，就按照老师的步骤来呗，但是会出现问题，大概记不清了，大概就是main已经定义过了什么的，然后我发现2015和老师的2010不一样，不能建立后台程序，而是建立空项目，然后就一步一步往上爬，后来就在那个将.lib文件加到项目文件夹时出现了一点问题，我下载下来时是一个压缩的形式，我就解压了，然后放进去就不好使了，然后不解压就好了。

**代码**

#include <iostream>
using namespace std;
//#include "stdafx.h"
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")
int main()
{
	GDALDataset* poSrcDS;
	GDALDataset* poDstDS;
	int imgXlen, imgYlen;
	char* srcPath = "trees.jpg";
	char* dstPath = "res.tif";
	GByte* buffTmp;
	int i, bandNum;
	GDALAllRegister();
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();
	printf("Image X length:%d", imgXlen);
	printf("\n");
	printf("Image Y length:%d", imgYlen);
	printf("\n");
	printf("Band number:%d", bandNum);
	printf("\n");
	buffTmp = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	for (i = 0; i < bandNum; i++)
	{
		poSrcDS->GetRasterBand(i + 1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);
		poSrcDS->GetRasterBand(i + 1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);
		printf("......band %d processing......\n", i);
	}
	CPLFree(buffTmp);
	GDALClose(poDstDS);
	GDALClose(poSrcDS);
	system("PAUSE");
	return 0;
}

`运行结果截图`

![reslut](C:\Users\lenovo\Desktop)