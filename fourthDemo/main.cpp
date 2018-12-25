#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")

//�����1
int fun1()
{
	//����ͼ��
	GDALDataset* poSrcDS;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen, imgYlen;
	//����ͼ��·��
	char* srcPath = "lena.jpg";
	//���ͼ��·��
	char* dstPath = "firstgril.tif";

	GByte* buffTmpr;//ͼ���ɫͨ���ڴ�洢
	GByte* buffTmpg;//ͼ����ɫɫͨ���ڴ�洢
	GByte* buffTmpb;//ͼ����ɫͨ���ڴ�洢
					//ͼ�񲨶���
	int bandNum;

	//ע������
	GDALAllRegister();

	//��ͼ��
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);

	//��ȡͼ���ȣ��߶ȺͲ�������
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();

	//����ͼ��ĸ߶ȺͿ�ȷ����ڴ�
	buffTmpr = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	buffTmpg = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	buffTmpb = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));

	//ͼ����ͨ����Ϣ�����Ӧ�洢
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpr, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poSrcDS->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpg, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poSrcDS->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpb, imgXlen, imgYlen, GDT_Byte, 0, 0);

	//��ͨ�����
	for (int i = 1; i < imgXlen - 1; i++)
	{
		for (int j = 1; j < imgYlen - 1; j++)
		{
			buffTmpr[i * imgYlen + j] = (buffTmpr[(i - 1) * imgYlen + j] + buffTmpr[i * imgYlen + j - 1] + buffTmpr[i * imgYlen + j] + buffTmpr[i * imgYlen + j + 1] + buffTmpr[(i + 1) * imgYlen + j]) / 5;
			buffTmpg[i * imgYlen + j] = (buffTmpg[(i - 1) * imgYlen + j] + buffTmpg[i * imgYlen + j - 1] + buffTmpg[i * imgYlen + j] + buffTmpg[i * imgYlen + j + 1] + buffTmpg[(i + 1) * imgYlen + j]) / 5;
			buffTmpb[i * imgYlen + j] = (buffTmpb[(i - 1) * imgYlen + j] + buffTmpb[i * imgYlen + j - 1] + buffTmpb[i * imgYlen + j] + buffTmpb[i * imgYlen + j + 1] + buffTmpb[(i + 1) * imgYlen + j]) / 5;
		}
	}

	//��һ�У���ĩ������Ϊ0
	for (int i = 0; i < imgXlen; i++)
	{
		buffTmpr[i] = (GByte)0;
		buffTmpg[i] = (GByte)0;
		buffTmpb[i] = (GByte)0;

		buffTmpr[(imgYlen - 1) * imgXlen + i] = (GByte)0;
		buffTmpg[(imgYlen - 1) * imgXlen + i] = (GByte)0;
		buffTmpb[(imgYlen - 1) * imgXlen + i] = (GByte)0;
	}

	//��һ�У����һ������Ϊ0
	for (int i = 0; i < imgYlen; i++)
	{
		buffTmpr[i * imgXlen] = (GByte)0;
		buffTmpg[i * imgXlen] = (GByte)0;
		buffTmpb[i * imgXlen] = (GByte)0;

		buffTmpr[i * imgXlen + imgXlen - 1] = (GByte)0;
		buffTmpg[i * imgXlen + imgXlen - 1] = (GByte)0;
		buffTmpb[i * imgXlen + imgXlen - 1] = (GByte)0;
	}

	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);

	//���ͼ��
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpr, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpg, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpb, imgXlen, imgYlen, GDT_Byte, 0, 0);

	//����ڴ�
	CPLFree(buffTmpr);
	CPLFree(buffTmpg);
	CPLFree(buffTmpb);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);

	system("PAUSE");
	return 0;
}

//�����2
int fun2()
{
	//����ͼ��
	GDALDataset* poSrcDS;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen, imgYlen;
	//����ͼ��·��
	char* srcPath = "lena.jpg";
	//���ͼ��·��
	char* dstPath = "secondGril.tif";

	GByte* buffTmpr;//ͼ���ɫͨ���ڴ�洢
	GByte* buffTmpg;//ͼ����ɫɫͨ���ڴ�洢
	GByte* buffTmpb;//ͼ����ɫͨ���ڴ�洢
					//ͼ�񲨶���
	int bandNum;

	//ע������
	GDALAllRegister();

	//��ͼ��
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);

	//��ȡͼ���ȣ��߶ȺͲ�������
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();

	//����ͼ��ĸ߶ȺͿ�ȷ����ڴ�
	buffTmpr = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	buffTmpg = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	buffTmpb = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));

	//ͼ����ͨ����Ϣ�����Ӧ�洢
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpr, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poSrcDS->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpg, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poSrcDS->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpb, imgXlen, imgYlen, GDT_Byte, 0, 0);

	//��ͨ�����
	for (int i = 2; i < imgYlen - 2; i++)
	{
		for (int j = 2; j < imgXlen - 2; j++)
		{
			buffTmpr[i * imgXlen + j] = (buffTmpr[(i - 2) * imgXlen + j - 2] + buffTmpr[(i - 1) * imgXlen + j - 1] + buffTmpr[i * imgXlen + j] + buffTmpr[(i + 1) * imgXlen + j + 1] + buffTmpr[(i + 2) * imgXlen + j + 2]) / 5;
			buffTmpg[i * imgXlen + j] = (buffTmpg[(i - 2) * imgXlen + j - 2] + buffTmpg[(i - 1) * imgXlen + j - 1] + buffTmpg[i * imgXlen + j] + buffTmpg[(i + 1) * imgXlen + j + 1] + buffTmpg[(i + 2) * imgXlen + j + 2]) / 5;
			buffTmpb[i * imgXlen + j] = (buffTmpb[(i - 2) * imgXlen + j - 2] + buffTmpb[(i - 1) * imgXlen + j - 1] + buffTmpb[i * imgXlen + j] + buffTmpb[(i + 1) * imgXlen + j + 1] + buffTmpb[(i + 2) * imgXlen + j + 2]) / 5;
		}
	}

	//��һ�����У���ĩ�С������ڶ�������Ϊ0
	for (int i = 0; i < imgXlen; i++)
	{
		buffTmpr[i] = (GByte)0;
		buffTmpg[i] = (GByte)0;
		buffTmpb[i] = (GByte)0;
		buffTmpr[imgXlen + i] = (GByte)0;
		buffTmpg[imgXlen + i] = (GByte)0;
		buffTmpb[imgXlen + i] = (GByte)0;

		buffTmpr[(imgYlen - 1) * imgXlen + i] = (GByte)0;
		buffTmpg[(imgYlen - 1) * imgXlen + i] = (GByte)0;
		buffTmpb[(imgYlen - 1) * imgXlen + i] = (GByte)0;
		buffTmpr[(imgYlen - 2) * imgXlen + i] = (GByte)0;
		buffTmpg[(imgYlen - 2) * imgXlen + i] = (GByte)0;
		buffTmpb[(imgYlen - 2) * imgXlen + i] = (GByte)0;
	}

	//��һ�С��ڶ��У����һ�С������ڶ�������Ϊ0
	for (int i = 0; i < imgYlen; i++)
	{
		buffTmpr[i * imgXlen] = (GByte)0;
		buffTmpg[i * imgXlen] = (GByte)0;
		buffTmpb[i * imgXlen] = (GByte)0;
		buffTmpr[1 + i * imgXlen] = (GByte)0;
		buffTmpg[1 + i * imgXlen] = (GByte)0;
		buffTmpb[1 + i * imgXlen] = (GByte)0;

		buffTmpr[i * imgXlen + imgXlen - 1] = (GByte)0;
		buffTmpg[i * imgXlen + imgXlen - 1] = (GByte)0;
		buffTmpb[i * imgXlen + imgXlen - 1] = (GByte)0;
		buffTmpr[i * imgXlen + imgXlen - 2] = (GByte)0;
		buffTmpg[i * imgXlen + imgXlen - 2] = (GByte)0;
		buffTmpb[i * imgXlen + imgXlen - 2] = (GByte)0;
	}

	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);

	//���ͼ��
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpr, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpg, imgXlen, imgYlen, GDT_Byte, 0, 0);
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpb, imgXlen, imgYlen, GDT_Byte, 0, 0);

	//����ڴ�
	CPLFree(buffTmpr);
	CPLFree(buffTmpg);
	CPLFree(buffTmpb);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);

	system("PAUSE");
	return 0;
}

//�����3
int fun3()
{
	//����ͼ��
	GDALDataset* poSrcDS;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen, imgYlen;
	//����ͼ��·��
	char* srcPath = "lena.jpg";
	//���ͼ��·��
	char* dstPath = "thirdGril.tif";

	float* buffTmpr;//ԭͼ���ɫͨ���ڴ�洢
	float* buffTmpg;//ԭͼ����ɫɫͨ���ڴ�洢
	float* buffTmpb;//ԭͼ����ɫͨ���ڴ�洢

	float* buffTmprn;//�����ͼ���ɫͨ���ڴ�洢
	float* buffTmpgn;//�����ͼ����ɫͨ���ڴ�洢
	float* buffTmpbn;//�����ͼ����ɫͨ���ڴ�洢
					 //ͼ�񲨶���
	int bandNum;

	//ע������
	GDALAllRegister();

	//��ͼ��
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);

	//��ȡͼ���ȣ��߶ȺͲ�������
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();

	//����ͼ��ĸ߶ȺͿ�ȷ����ڴ�
	buffTmpr = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpg = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpb = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmprn = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpgn = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpbn = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));

	//ͼ����ͨ����Ϣ�����Ӧ�洢
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpr, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poSrcDS->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpg, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poSrcDS->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpb, imgXlen, imgYlen, GDT_Float32, 0, 0);



	/*��ͨ�����
	for (int i = 1; i < imgYlen - 1; i++)
	{
	for (int j = 1; j < imgXlen - 1; j++)
	{
	buffTmprn[i * imgXlen + j] = (buffTmpr[i * imgXlen + j] * 8 - buffTmpr[(i - 1) * imgXlen + j - 1] - buffTmpr[(i - 1) * imgXlen + j] - buffTmpr[(i - 1) * imgXlen + j + 1] - buffTmpr[i * imgXlen + j - 1] - buffTmpr[i * imgXlen + j + 1] - buffTmpr[(i + 1) * imgXlen + j - 1] - buffTmpr[(i + 1) * imgXlen + j] - buffTmpr[(i + 1) * imgXlen + j + 1])%256;
	buffTmpgn[i * imgXlen + j] = (buffTmpg[i * imgXlen + j] * 8 - buffTmpg[(i - 1) * imgXlen + j - 1] - buffTmpg[(i - 1) * imgXlen + j] - buffTmpg[(i - 1) * imgXlen + j + 1] - buffTmpg[i * imgXlen + j - 1] - buffTmpg[i * imgXlen + j + 1] - buffTmpg[(i + 1) * imgXlen + j - 1] - buffTmpg[(i + 1) * imgXlen + j] - buffTmpg[(i + 1) * imgXlen + j + 1])%256;
	buffTmpbn[i * imgXlen + j] = (buffTmpb[i * imgXlen + j] * 8 - buffTmpb[(i - 1) * imgXlen + j - 1] - buffTmpb[(i - 1) * imgXlen + j] - buffTmpb[(i - 1) * imgXlen + j + 1] - buffTmpb[i * imgXlen + j - 1] - buffTmpb[i * imgXlen + j + 1] - buffTmpb[(i + 1) * imgXlen + j - 1] - buffTmpb[(i + 1) * imgXlen + j] - buffTmpb[(i + 1) * imgXlen + j + 1])%256;
	}
	}*/
	//����
	for (int j = 1; j < imgYlen - 1; j++)
	{
		for (int i = 1; i < imgXlen - 1; i++)
		{
			buffTmprn[j*imgXlen + i] = (-buffTmpr[(j - 1)*imgXlen + i - 1]
				- buffTmpr[(j - 1)*imgXlen + i]
				- buffTmpr[(j - 1)*imgXlen + i + 1]
				- buffTmpr[j*imgXlen + i - 1]
				+ buffTmpr[j*imgXlen + i] * 8
				- buffTmpr[j*imgXlen + i + 1]
				- buffTmpr[(j + 1)*imgXlen + i - 1]
				- buffTmpr[(j + 1)*imgXlen + i]
				- buffTmpr[(j + 1)*imgXlen + i + 1]);

			buffTmpgn[j*imgXlen + i] = (-buffTmpg[(j - 1)*imgXlen + i - 1]
				- buffTmpg[(j - 1)*imgXlen + i]
				- buffTmpg[(j - 1)*imgXlen + i + 1]
				- buffTmpg[j*imgXlen + i - 1]
				+ buffTmpg[j*imgXlen + i] * 8
				- buffTmpg[j*imgXlen + i + 1]
				- buffTmpg[(j + 1)*imgXlen + i - 1]
				- buffTmpg[(j + 1)*imgXlen + i]
				- buffTmpg[(j + 1)*imgXlen + i + 1]);

			buffTmpbn[j*imgXlen + i] = (-buffTmpb[(j - 1)*imgXlen + i - 1]
				- buffTmpb[(j - 1)*imgXlen + i]
				- buffTmpb[(j - 1)*imgXlen + i + 1]
				- buffTmpb[j*imgXlen + i - 1]
				+ buffTmpb[j*imgXlen + i] * 8
				- buffTmpb[j*imgXlen + i + 1]
				- buffTmpb[(j + 1)*imgXlen + i - 1]
				- buffTmpb[(j + 1)*imgXlen + i]
				- buffTmpb[(j + 1)*imgXlen + i + 1]);
		}
	}

	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);

	//���ͼ��
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmprn, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpgn, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpbn, imgXlen, imgYlen, GDT_Float32, 0, 0);

	//����ڴ�
	CPLFree(buffTmpr);
	CPLFree(buffTmpg);
	CPLFree(buffTmpb);
	CPLFree(buffTmprn);
	CPLFree(buffTmpgn);
	CPLFree(buffTmpbn);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);

	system("PAUSE");
	return 0;
}

//�����4
int fun4()
{
	//����ͼ��
	GDALDataset* poSrcDS;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen, imgYlen;
	//����ͼ��·��
	char* srcPath = "lena.jpg";
	//���ͼ��·��
	char* dstPath = "forthGril.tif";

	float* buffTmpr;//ԭͼ���ɫͨ���ڴ�洢
	float* buffTmpg;//ԭͼ����ɫɫͨ���ڴ�洢
	float* buffTmpb;//ԭͼ����ɫͨ���ڴ�洢

	float* buffTmprn;//�����ͼ���ɫͨ���ڴ�洢
	float* buffTmpgn;//�����ͼ����ɫͨ���ڴ�洢
	float* buffTmpbn;//�����ͼ����ɫͨ���ڴ�洢
					 //ͼ�񲨶���
	int bandNum;

	//ע������
	GDALAllRegister();

	//��ͼ��
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);

	//��ȡͼ���ȣ��߶ȺͲ�������
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();

	//����ͼ��ĸ߶ȺͿ�ȷ����ڴ�
	buffTmpr = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpg = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpb = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmprn = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpgn = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpbn = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));

	//ͼ����ͨ����Ϣ�����Ӧ�洢
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpr, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poSrcDS->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpg, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poSrcDS->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpb, imgXlen, imgYlen, GDT_Float32, 0, 0);



	//��ͨ�����
	for (int i = 1; i < imgYlen - 1; i++)
	{
		for (int j = 1; j < imgXlen - 1; j++)
		{
			buffTmprn[i * imgXlen + j] = (buffTmpr[i * imgXlen + j] * 9 -
				buffTmpr[(i - 1) * imgXlen + j - 1] -
				buffTmpr[(i - 1) * imgXlen + j] -
				buffTmpr[(i - 1) * imgXlen + j + 1] -
				buffTmpr[i * imgXlen + j - 1] -
				buffTmpr[i * imgXlen + j + 1] -
				buffTmpr[(i + 1) * imgXlen + j - 1] -
				buffTmpr[(i + 1) * imgXlen + j] -
				buffTmpr[(i + 1) * imgXlen + j + 1]);
			buffTmpgn[i * imgXlen + j] = (buffTmpg[i * imgXlen + j] * 9 - buffTmpg[(i - 1) * imgXlen + j - 1] - buffTmpg[(i - 1) * imgXlen + j] - buffTmpg[(i - 1) * imgXlen + j + 1] - buffTmpg[i * imgXlen + j - 1] - buffTmpg[i * imgXlen + j + 1] - buffTmpg[(i + 1) * imgXlen + j - 1] - buffTmpg[(i + 1) * imgXlen + j] - buffTmpg[(i + 1) * imgXlen + j + 1]);
			buffTmpbn[i * imgXlen + j] = (buffTmpb[i * imgXlen + j] * 9 - buffTmpb[(i - 1) * imgXlen + j - 1] - buffTmpb[(i - 1) * imgXlen + j] - buffTmpb[(i - 1) * imgXlen + j + 1] - buffTmpb[i * imgXlen + j - 1] - buffTmpb[i * imgXlen + j + 1] - buffTmpb[(i + 1) * imgXlen + j - 1] - buffTmpb[(i + 1) * imgXlen + j] - buffTmpb[(i + 1) * imgXlen + j + 1]);
		}
	}

	/*
	//��һ�У���ĩ������Ϊ0
	for (int i = 0; i < imgXlen; i++)
	{
	buffTmprn[i] = 0;
	buffTmpgn[i] = 0;
	buffTmpbn[i] = 0;

	buffTmprn[(imgYlen - 1) * imgXlen + i] = 0;
	buffTmpgn[(imgYlen - 1) * imgXlen + i] = 0;
	buffTmpbn[(imgYlen - 1) * imgXlen + i] = 0;
	}

	//��һ�У����һ������Ϊ0
	for (int i = 0; i < imgYlen; i++)
	{
	buffTmprn[i * imgXlen] = 0;
	buffTmpgn[i * imgXlen] = 0;
	buffTmpbn[i * imgXlen] = 0;

	buffTmprn[i * imgXlen + imgXlen - 1] = 0;
	buffTmpgn[i * imgXlen + imgXlen - 1] = 0;
	buffTmpbn[i * imgXlen + imgXlen - 1] = 0;
	} */


	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);

	//���ͼ��
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmprn, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpgn, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpbn, imgXlen, imgYlen, GDT_Float32, 0, 0);

	//����ڴ�
	CPLFree(buffTmpr);
	CPLFree(buffTmpg);
	CPLFree(buffTmpb);
	CPLFree(buffTmprn);
	CPLFree(buffTmpgn);
	CPLFree(buffTmpbn);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);

	system("PAUSE");
	return 0;
}

//�����5
int fun5()
{
	//����ͼ��
	GDALDataset* poSrcDS;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen, imgYlen;
	//����ͼ��·��
	char* srcPath = "lena.jpg";
	//���ͼ��·��
	char* dstPath = "fifthGril.tif";

	float* buffTmpr;//ԭͼ���ɫͨ���ڴ�洢
	float* buffTmpg;//ԭͼ����ɫɫͨ���ڴ�洢
	float* buffTmpb;//ԭͼ����ɫͨ���ڴ�洢

	float* buffTmprn;//�����ͼ���ɫͨ���ڴ�洢
	float* buffTmpgn;//�����ͼ����ɫͨ���ڴ�洢
	float* buffTmpbn;//�����ͼ����ɫͨ���ڴ�洢
					 //ͼ�񲨶���
	int bandNum;

	//ע������
	GDALAllRegister();

	//��ͼ��
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);

	//��ȡͼ���ȣ��߶ȺͲ�������
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();

	//����ͼ��ĸ߶ȺͿ�ȷ����ڴ�
	buffTmpr = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpg = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpb = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmprn = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpgn = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpbn = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));

	//ͼ����ͨ����Ϣ�����Ӧ�洢
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpr, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poSrcDS->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpg, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poSrcDS->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpb, imgXlen, imgYlen, GDT_Float32, 0, 0);

	//��ͨ�����
	for (int i = 1; i < imgYlen - 1; i++)
	{
		for (int j = 1; j < imgXlen - 1; j++)
		{
			buffTmprn[j*imgXlen + i] = (-buffTmpr[(j - 1)*imgXlen + i - 1]
				- buffTmpr[(j - 1)*imgXlen + i]
				- buffTmpr[j*imgXlen + i - 1]
				+ buffTmpr[j*imgXlen + i + 1]
				+ buffTmpr[(j + 1)*imgXlen + i]
				+ buffTmpr[(j + 1)*imgXlen + i + 1]);
			buffTmpgn[j*imgXlen + i] = (-buffTmpg[(j - 1)*imgXlen + i - 1]
				- buffTmpg[(j - 1)*imgXlen + i]
				- buffTmpg[j*imgXlen + i - 1]
				+ buffTmpg[j*imgXlen + i + 1]
				+ buffTmpg[(j + 1)*imgXlen + i]
				+ buffTmpg[(j + 1)*imgXlen + i + 1]);
			buffTmpbn[j*imgXlen + i] = (-buffTmpb[(j - 1)*imgXlen + i - 1]
				- buffTmpb[(j - 1)*imgXlen + i]
				- buffTmpb[j*imgXlen + i - 1]
				+ buffTmpb[j*imgXlen + i + 1]
				+ buffTmpb[(j + 1)*imgXlen + i]
				+ buffTmpb[(j + 1)*imgXlen + i + 1]);
		}
	}

	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);

	//���ͼ��
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmprn, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpgn, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpbn, imgXlen, imgYlen, GDT_Float32, 0, 0);

	//����ڴ�
	CPLFree(buffTmpr);
	CPLFree(buffTmpg);
	CPLFree(buffTmpb);
	CPLFree(buffTmprn);
	CPLFree(buffTmpgn);
	CPLFree(buffTmpbn);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);

	system("PAUSE");
	return 0;
}

//�����6
int fun6()
{
	//����ͼ��
	GDALDataset* poSrcDS;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen, imgYlen;
	//����ͼ��·��
	char* srcPath = "lena.jpg";
	//���ͼ��·��
	char* dstPath = "sixthGril.tif";

	float* buffTmpr;//ԭͼ���ɫͨ���ڴ�洢
	float* buffTmpg;//ԭͼ����ɫɫͨ���ڴ�洢
	float* buffTmpb;//ԭͼ����ɫͨ���ڴ�洢

	float* buffTmprn;//�����ͼ���ɫͨ���ڴ�洢
	float* buffTmpgn;//�����ͼ����ɫͨ���ڴ�洢
	float* buffTmpbn;//�����ͼ����ɫͨ���ڴ�洢
					 //ͼ�񲨶���
	int bandNum;

	//ע������
	GDALAllRegister();

	//��ͼ��
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);

	//��ȡͼ���ȣ��߶ȺͲ�������
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();

	//����ͼ��ĸ߶ȺͿ�ȷ����ڴ�
	buffTmpr = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpg = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpb = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmprn = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpgn = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));
	buffTmpbn = (float*)CPLMalloc(imgXlen*imgYlen * sizeof(float));

	//ͼ����ͨ����Ϣ�����Ӧ�洢
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpr, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poSrcDS->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpg, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poSrcDS->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmpb, imgXlen, imgYlen, GDT_Float32, 0, 0);

	//��ͨ�����
	for (int i = 1; i < imgYlen - 1; i++)
	{
		for (int j = 1; j < imgXlen - 1; j++)
		{
			buffTmprn[j*imgXlen + i] = (0.0120*buffTmpr[(j - 2)*imgXlen + i - 2] +
				0.1253*buffTmpr[(j - 2)*imgXlen + i - 1] +
				0.2736*buffTmpr[(j - 2)*imgXlen + i] +
				0.1253*buffTmpr[(j - 2)*imgXlen + i + 1] +
				0.0120*buffTmpr[(j - 2)*imgXlen + i + 2] +
				0.1253*buffTmpr[(j - 1)*imgXlen + i - 2] +
				1.3054*buffTmpr[(j - 1)*imgXlen + i - 1] +
				2.8514*buffTmpr[(j - 1)*imgXlen + i] +
				1.3054*buffTmpr[(j - 1)*imgXlen + i + 1] +
				0.1253*buffTmpr[(j - 1)*imgXlen + i + 2] +
				0.2763*buffTmpr[j*imgXlen + i - 2] +
				2.8514*buffTmpr[j*imgXlen + i - 1] +
				6.2279*buffTmpr[j*imgXlen + i] +
				2.8514*buffTmpr[j*imgXlen + i + 1] +
				0.2763*buffTmpr[j*imgXlen + i + 2] +
				0.1253*buffTmpr[(j + 1)*imgXlen + i - 2] +
				1.3054*buffTmpr[(j + 1)*imgXlen + i - 1] +
				2.8514*buffTmpr[(j + 1)*imgXlen + i] +
				1.3054*buffTmpr[(j + 1)*imgXlen + i + 1] +
				0.1253*buffTmpr[(j + 1)*imgXlen + i + 2] +
				0.0120*buffTmpr[(j + 2)*imgXlen + i - 2] +
				0.1253*buffTmpr[(j + 2)*imgXlen + i - 1] +
				0.2736*buffTmpr[(j + 2)*imgXlen + i] +
				0.1253*buffTmpr[(j + 2)*imgXlen + i + 1] +
				0.0120*buffTmpr[(j + 2)*imgXlen + i + 2]) / 25.0f;
			buffTmpgn[j*imgXlen + i] = (0.0120*buffTmpg[(j - 2)*imgXlen + i - 2] +
				0.1253*buffTmpg[(j - 2)*imgXlen + i - 1] +
				0.2736*buffTmpg[(j - 2)*imgXlen + i] +
				0.1253*buffTmpg[(j - 2)*imgXlen + i + 1] +
				0.0120*buffTmpg[(j - 2)*imgXlen + i + 2] +
				0.1253*buffTmpg[(j - 1)*imgXlen + i - 2] +
				1.3054*buffTmpg[(j - 1)*imgXlen + i - 1] +
				2.8514*buffTmpg[(j - 1)*imgXlen + i] +
				1.3054*buffTmpg[(j - 1)*imgXlen + i + 1] +
				0.1253*buffTmpg[(j - 1)*imgXlen + i + 2] +
				0.2763*buffTmpg[j*imgXlen + i - 2] +
				2.8514*buffTmpg[j*imgXlen + i - 1] +
				6.2279*buffTmpg[j*imgXlen + i] +
				2.8514*buffTmpg[j*imgXlen + i + 1] +
				0.2763*buffTmpg[j*imgXlen + i + 2] +
				0.1253*buffTmpg[(j + 1)*imgXlen + i - 2] +
				1.3054*buffTmpg[(j + 1)*imgXlen + i - 1] +
				2.8514*buffTmpg[(j + 1)*imgXlen + i] +
				1.3054*buffTmpg[(j + 1)*imgXlen + i + 1] +
				0.1253*buffTmpg[(j + 1)*imgXlen + i + 2] +
				0.0120*buffTmpg[(j + 2)*imgXlen + i - 2] +
				0.1253*buffTmpg[(j + 2)*imgXlen + i - 1] +
				0.2736*buffTmpg[(j + 2)*imgXlen + i] +
				0.1253*buffTmpg[(j + 2)*imgXlen + i + 1] +
				0.0120*buffTmpg[(j + 2)*imgXlen + i + 2]) / 25.0f;
			buffTmpbn[j*imgXlen + i] = (0.0120*buffTmpb[(j - 2)*imgXlen + i - 2] +
				0.1253*buffTmpb[(j - 2)*imgXlen + i - 1] +
				0.2736*buffTmpb[(j - 2)*imgXlen + i] +
				0.1253*buffTmpb[(j - 2)*imgXlen + i + 1] +
				0.0120*buffTmpb[(j - 2)*imgXlen + i + 2] +
				0.1253*buffTmpb[(j - 1)*imgXlen + i - 2] +
				1.3054*buffTmpb[(j - 1)*imgXlen + i - 1] +
				2.8514*buffTmpb[(j - 1)*imgXlen + i] +
				1.3054*buffTmpb[(j - 1)*imgXlen + i + 1] +
				0.1253*buffTmpb[(j - 1)*imgXlen + i + 2] +
				0.2763*buffTmpb[j*imgXlen + i - 2] +
				2.8514*buffTmpb[j*imgXlen + i - 1] +
				6.2279*buffTmpb[j*imgXlen + i] +
				2.8514*buffTmpb[j*imgXlen + i + 1] +
				0.2763*buffTmpb[j*imgXlen + i + 2] +
				0.1253*buffTmpb[(j + 1)*imgXlen + i - 2] +
				1.3054*buffTmpb[(j + 1)*imgXlen + i - 1] +
				2.8514*buffTmpb[(j + 1)*imgXlen + i] +
				1.3054*buffTmpb[(j + 1)*imgXlen + i + 1] +
				0.1253*buffTmpb[(j + 1)*imgXlen + i + 2] +
				0.0120*buffTmpb[(j + 2)*imgXlen + i - 2] +
				0.1253*buffTmpb[(j + 2)*imgXlen + i - 1] +
				0.2736*buffTmpb[(j + 2)*imgXlen + i] +
				0.1253*buffTmpb[(j + 2)*imgXlen + i + 1] +
				0.0120*buffTmpb[(j + 2)*imgXlen + i + 2]) / 25.0f;
		}
	}

	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);

	//���ͼ��
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmprn, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpgn, imgXlen, imgYlen, GDT_Float32, 0, 0);
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmpbn, imgXlen, imgYlen, GDT_Float32, 0, 0);

	//����ڴ�
	CPLFree(buffTmpr);
	CPLFree(buffTmpg);
	CPLFree(buffTmpb);
	CPLFree(buffTmprn);
	CPLFree(buffTmpgn);
	CPLFree(buffTmpbn);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);
	return 0;
}

int main()
{
	//fun1();
	//fun2();
	//fun3();
	//fun4();
	fun5();
	//fun6();
	return 0;
}