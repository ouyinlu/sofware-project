#include<iostream>
using namespace std;
#include"./gdal/gdal_priv.h"
#pragma comment(lib,"gdal_i.lib")

int main() {
	//输入图像
	GDALDataset* poSrcDS;
	//输出图像
	GDALDataset* poDstDS;
	//图像的宽度和高度
	int imgXlen, imgYlen;
	//区域的宽度和高度
	int tmpXlen, tmpYlen;
	//图像更改区域的起始坐标
	int StartX, StartY;
	//输入图像路径
	char* srcPath = "May Wind.jpeg";
	//输出图像路径
	char* dstPath = "res.tif";
	//图像内部存储
	GByte* buffTmp;
	//图像内部存储
	GByte* buffTmp1;
	//图像波段数
	int i,j, bandNum;
	//注册驱动
	GDALAllRegister();

	//打开图像
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);
	//获取图像的宽度、高度和波段数量
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();
	//获取输出的结果
	cout << "Img X Length: " << imgXlen << endl;
	cout << "Img Y Length: " << imgYlen << endl;
	cout << "Band number: " << bandNum << endl;
	//分配内存
	buffTmp1= (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	//创建输出图像
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	//一个个波段的输入，然后一个个波段的输出
	for (i = 0; i < bandNum; i++) {
		poSrcDS->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0, 0, imgXlen, imgYlen, buffTmp1, imgXlen, imgYlen, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(i + 1)->RasterIO(GF_Write,
			0, 0, imgXlen, imgYlen, buffTmp1, imgXlen, imgYlen, GDT_Byte, 0, 0);
		cout << "... ... band " << i << " processing ... ..." << endl;
	}

	//起始位置坐标
	StartX = 100;
	StartY = 100;
	//区域宽度和高度
	tmpXlen = 200;
	tmpYlen = 150;
	buffTmp = (GByte*)CPLMalloc(tmpXlen*tmpYlen * sizeof(GByte));
	//读取红色通道缓存在buffTmp中
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read,
		StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//遍历区域，逐像素置为255
	for (j = 0; j < tmpYlen; j++) {
		for (i = 0; i < tmpXlen; i++) {
			buffTmp[j*tmpXlen + i] = (GByte)255;
		}
	}
	//数据写入poDstDS
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write,
		StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);

	//清除内存
	CPLFree(buffTmp);
	CPLFree(buffTmp1);
	//关闭dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);

	system("PAUSE");
	return 0;
}