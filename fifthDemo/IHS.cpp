#include<iostream>
using namespace std;
#include"./gdal/gdal_priv.h"
#pragma comment(lib,"gdal_i.lib")

int main() {
	//输入图像
	GDALDataset* poSrcDS1;
	GDALDataset* poSrcDS2;
	//输出图像
	GDALDataset* poDstDS;
	//图像的宽度和高度
	int imgXlen, imgYlen;
	//区域的宽度和高度
	int tmpXlen, tmpYlen;
	//图像更改区域的起始坐标
	int StartX, StartY;
	//输入图像路径
	char* srcPath1 = "American_MUL.bmp";
	char* srcPath2 = "American_PAN.bmp";
	//输出图像路径
	char* dstPath = "res.tif";

	//图像内部存储
	GByte* buffTmp[3];
	//图像波段数
	int i, j, bandNum;
	//注册驱动
	GDALAllRegister();

	//打开图像
	poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2, GA_ReadOnly);
	//获取图像的宽度、高度和波段数量
	imgXlen = poSrcDS1->GetRasterXSize();
	imgYlen = poSrcDS1->GetRasterYSize();
	bandNum = poSrcDS1->GetRasterCount();
	//获取输出的结果
	cout << "Img X Length: " << imgXlen << endl;
	cout << "Img Y Length: " << imgYlen << endl;
	cout << "Band number: " << bandNum << endl;
	//分配内存
	for (int i = 0; i < 3; i++) {
		buffTmp[i] = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	}
	//创建输出图像
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	//分波段获取图像  buffTmp 0 1 2 取American_MUL.bmp
	for (i = 0; i < bandNum; i++) {
		poSrcDS1->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0, 0, imgXlen, imgYlen, buffTmp[i], imgXlen, imgYlen, GDT_Byte, 0, 0);
	
	}

}