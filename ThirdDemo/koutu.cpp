#include<iostream>
using namespace std;
#include"./gdal/gdal_priv.h"
#pragma comment(lib,"gdal_i.lib")
/*
	条件1：10<r<160; 条件2：100<g<220; 条件3：10<b<110；
*/
int main() {
	//输入图像 

	GDALDataset* poSrcDS;

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
	char* srcPath = "superman.jpg";

	char* srcPath2 = "space.jpg";
	//输出图像路径
	char* dstPath = "res.tif";
	//图像内部存储
	GByte* buffTmp[6];
	//图像波段数
	int i, j, bandNum;
	//注册驱动
	GDALAllRegister();

	int r[2] = { 10,160 }, g[2] = { 100,220 }, b[2] = { 10,110 };
	//打开图像 
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);

	poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2, GA_ReadOnly);


	//获取图像的宽度、高度和波段数量
	imgXlen = poSrcDS2->GetRasterXSize();
	imgYlen = poSrcDS2->GetRasterYSize();
	bandNum = poSrcDS2->GetRasterCount();

	//获取输出的结果
	cout << "Img X Length: " << imgXlen << endl;
	cout << "Img Y Length: " << imgYlen << endl;
	cout << "Band number: " << bandNum << endl;


	//分配内存
	for (int k = 0; k < 6; k++) {
		buffTmp[k] = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	}

	//创建输出图像
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);

	//分波段获取图像  buffTmp 0 1 2 取superman..jpg  buffTmp 3 4 5 取space.jpg  
	for (i = 0; i < bandNum; i++) {
		poSrcDS->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0, 0, imgXlen, imgYlen, buffTmp[i], imgXlen, imgYlen, GDT_Byte, 0, 0);
		poSrcDS2->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0, 0, imgXlen, imgYlen, buffTmp[i + 3], imgXlen, imgYlen, GDT_Byte, 0, 0);
	}

	for (int j = 0; j < imgYlen; j++) {
		for (int k = 0; k < imgXlen; k++) {
			//判断是否是目标图像,如果是就将对应区域的像素替换
			if (buffTmp[0][j * imgXlen + k] > r[0] && buffTmp[0][j * imgXlen + k] < r[1] &&
				buffTmp[1][j * imgXlen + k] > g[0] && buffTmp[1][j * imgXlen + k] < g[1] &&
				buffTmp[2][j * imgXlen + k] > b[0] && buffTmp[2][j * imgXlen + k] < b[1]) 
			{
				for (i = 0; i < 3; i++) 
				{
					buffTmp[i][j * imgXlen + k] = buffTmp[i + 3][j * imgXlen + k];
				}
			}
		}
	}

	//将合成好的图像存入输出路径
	for (int i = 1; i <= bandNum; i++) {
		poDstDS->GetRasterBand(i)->RasterIO(GF_Write,
			0, 0, imgXlen, imgYlen, buffTmp[i - 1], imgXlen, imgYlen, GDT_Byte, 0, 0);
		printf("... ... band %d processing ... ...\n", i);
	}

	//清除内存
	CPLFree(buffTmp);
	//关闭dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);
	GDALClose(poSrcDS2);

	system("PAUSE");
	return 0;
}
