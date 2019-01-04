#include<iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")

int main()
{
	//����ͼ��
	GDALDataset* poSrcDS;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen, imgYlen;
	//����ͼ��·��
	char* srcPath = "May Wind.jpeg";
	//���ͼ���·��
	char* dstPath = "res2.tif";
	//ͼ���ڴ�洢
	GByte* buffTmp, *buffTmp1, *buffTmp2;
	//ͼ�񲨶���
	int i, bandNum;
	//���������꣬����������꣬�����ȣ�����߶�
	int StartX1, StartY1, StartX2, StartY2, tmpXlen1, tmpYlen1, tmpXlen2, tmpYlen2;

	//ע������
	GDALAllRegister();
	//��ͼ��
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);

	//��ȡͼ���ȣ��߶ȣ�������
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();
	//�����ȡ�Ľ��
	cout << "IMG  X Length:" << imgXlen << endl;
	cout << "IMG  Y Length:" << imgYlen << endl;
	cout << "Band Number:" << bandNum << endl;

	//����ͼ��Ŀ�Ⱥ͸߶ȷ����ڴ�
	buffTmp = (GByte*)CPLMalloc(imgXlen * imgYlen * sizeof(GByte));
	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);

	/**
	�����ض���������
	*/
	//�趨��ʼֵ
	StartX1 = 300;
	StartY1 = 300;
	tmpXlen1 = 100;
	tmpYlen1 = 50;
	StartX2 = 500;
	StartY2 = 500;
	tmpXlen2 = 50;
	tmpYlen2 = 100;
	//�����ڴ�
	buffTmp1 = (GByte*)CPLMalloc(tmpXlen1 * tmpYlen1 * sizeof(GByte));
	buffTmp2 = (GByte*)CPLMalloc(tmpXlen2 * tmpYlen2 * sizeof(GByte));
	//��ÿ�����θ�ֵ255��0����Ӧ���׺ʹ���
	for (i = 0; i < tmpYlen1; i++) {
		for (int j = 0; j < tmpXlen1; j++) {
			buffTmp1[i * tmpXlen1 + j] = (GByte)255;
		}
	}
	for (i = 0; i < tmpYlen2; i++) {
		for (int j = 0; j < tmpXlen2; j++) {
			buffTmp2[i * tmpXlen2 + j] = (GByte)0;
		}
	}

	//һ��һ���������롣һ��һ���������
	for (int i = 1; i <= bandNum; i++) {
		poSrcDS->GetRasterBand(i)->RasterIO(GF_Read,
			0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(i)->RasterIO(GF_Write,
			0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);
		//����ɫ����
		poDstDS->GetRasterBand(i)->RasterIO(GF_Write,
			StartX1, StartY1, tmpXlen1, tmpYlen1, buffTmp1, tmpXlen1, tmpYlen1, GDT_Byte, 0, 0);
		//����ɫ����
		poDstDS->GetRasterBand(i)->RasterIO(GF_Write,
			StartX2, StartY2, tmpXlen2, tmpYlen2, buffTmp2, tmpXlen2, tmpYlen2, GDT_Byte, 0, 0);
		printf("... ... band %d processing ... ...\n", i);
	}
	/*    //��ɫ����д��poDstDS
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write,
	StartX,StartY,tmpXlen,tmpYlen,buffTmp1,tmpXlen,tmpYlen,GDT_Byte,0,0);
	*/
	//����ڴ�
	CPLFree(buffTmp);
	CPLFree(buffTmp1);
	CPLFree(buffTmp2);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);
	return 0;
}