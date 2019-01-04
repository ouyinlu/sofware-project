#include<iostream>
using namespace std;
#include"./gdal/gdal_priv.h"
#pragma comment(lib,"gdal_i.lib")
/*
	����1��10<r<160; ����2��100<g<220; ����3��10<b<110��
*/
int main() {
	//����ͼ�� 

	GDALDataset* poSrcDS;

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
	char* srcPath = "superman.jpg";

	char* srcPath2 = "space.jpg";
	//���ͼ��·��
	char* dstPath = "res.tif";
	//ͼ���ڲ��洢
	GByte* buffTmp[6];
	//ͼ�񲨶���
	int i, j, bandNum;
	//ע������
	GDALAllRegister();

	int r[2] = { 10,160 }, g[2] = { 100,220 }, b[2] = { 10,110 };
	//��ͼ�� 
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);

	poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2, GA_ReadOnly);


	//��ȡͼ��Ŀ�ȡ��߶ȺͲ�������
	imgXlen = poSrcDS2->GetRasterXSize();
	imgYlen = poSrcDS2->GetRasterYSize();
	bandNum = poSrcDS2->GetRasterCount();

	//��ȡ����Ľ��
	cout << "Img X Length: " << imgXlen << endl;
	cout << "Img Y Length: " << imgYlen << endl;
	cout << "Band number: " << bandNum << endl;


	//�����ڴ�
	for (int k = 0; k < 6; k++) {
		buffTmp[k] = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	}

	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);

	//�ֲ��λ�ȡͼ��  buffTmp 0 1 2 ȡsuperman..jpg  buffTmp 3 4 5 ȡspace.jpg  
	for (i = 0; i < bandNum; i++) {
		poSrcDS->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0, 0, imgXlen, imgYlen, buffTmp[i], imgXlen, imgYlen, GDT_Byte, 0, 0);
		poSrcDS2->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0, 0, imgXlen, imgYlen, buffTmp[i + 3], imgXlen, imgYlen, GDT_Byte, 0, 0);
	}

	for (int j = 0; j < imgYlen; j++) {
		for (int k = 0; k < imgXlen; k++) {
			//�ж��Ƿ���Ŀ��ͼ��,����Ǿͽ���Ӧ����������滻
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

	//���ϳɺõ�ͼ��������·��
	for (int i = 1; i <= bandNum; i++) {
		poDstDS->GetRasterBand(i)->RasterIO(GF_Write,
			0, 0, imgXlen, imgYlen, buffTmp[i - 1], imgXlen, imgYlen, GDT_Byte, 0, 0);
		printf("... ... band %d processing ... ...\n", i);
	}

	//����ڴ�
	CPLFree(buffTmp);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);
	GDALClose(poSrcDS2);

	system("PAUSE");
	return 0;
}
