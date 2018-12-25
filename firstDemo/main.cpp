#include<iostream>
using namespace std;
#include"./gdal/gdal_priv.h"
#pragma comment(lib,"gdal_i.lib")

int main() {
	//����ͼ��
	GDALDataset* poSrcDS;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ��Ŀ��Ⱥ͸߶�
	int imgXlen, imgYlen;
	//���ͼ��·��
	char* srcPath = "May Wind.jpeg";
	//ͼ���ڲ��洢
	char* dstPath = "res.tif";
	//ͼ���ڲ��洢
	GByte* buffTmp;
	//ͼ�񲨶���
	int i, bandNum;

	//ע������
	GDALAllRegister();

	//��ͼ��
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);

	//��ȡͼ��Ŀ��ȡ��߶ȺͲ�������
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();
	//��ȡ����Ľ��
	cout << "Img X Length: " << imgXlen << endl;
	cout << "Img Y Length: " << imgYlen << endl;
	cout << "Band number: " << bandNum << endl;
	//����ͼ��Ŀ��Ⱥ͸߶ȷ����ڴ�
	buffTmp = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	//һ�������ε����룬Ȼ��һ�������ε����
	for (i = 0; i < bandNum; i++) {
		poSrcDS->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(i + 1)->RasterIO(GF_Write,
			0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);
		cout << "... ... band " << i << " processing ... ..." << endl;
	}

	//����ڴ�
	CPLFree(buffTmp);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);

	system("PAUSE");
	return 0;
}