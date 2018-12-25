#include<iostream>
using namespace std;
#include"./gdal/gdal_priv.h"
#pragma comment(lib,"gdal_i.lib")

int main() {
	//����ͼ��
	GDALDataset* poSrcDS1;
	GDALDataset* poSrcDS2;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen, imgYlen;
	//����Ŀ�Ⱥ͸߶�
	int tmpXlen, tmpYlen;
	//ͼ������������ʼ����
	int StartX, StartY;
	//����ͼ��·��
	char* srcPath1 = "American_MUL.bmp";
	char* srcPath2 = "American_PAN.bmp";
	//���ͼ��·��
	char* dstPath = "res.tif";

	//ͼ���ڲ��洢
	GByte* buffTmp[3];
	//ͼ�񲨶���
	int i, j, bandNum;
	//ע������
	GDALAllRegister();

	//��ͼ��
	poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2, GA_ReadOnly);
	//��ȡͼ��Ŀ�ȡ��߶ȺͲ�������
	imgXlen = poSrcDS1->GetRasterXSize();
	imgYlen = poSrcDS1->GetRasterYSize();
	bandNum = poSrcDS1->GetRasterCount();
	//��ȡ����Ľ��
	cout << "Img X Length: " << imgXlen << endl;
	cout << "Img Y Length: " << imgYlen << endl;
	cout << "Band number: " << bandNum << endl;
	//�����ڴ�
	for (int i = 0; i < 3; i++) {
		buffTmp[i] = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	}
	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	//�ֲ��λ�ȡͼ��  buffTmp 0 1 2 ȡAmerican_MUL.bmp
	for (i = 0; i < bandNum; i++) {
		poSrcDS1->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0, 0, imgXlen, imgYlen, buffTmp[i], imgXlen, imgYlen, GDT_Byte, 0, 0);
	
	}

}