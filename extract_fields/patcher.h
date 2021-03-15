#pragma once
#include "external.h"
/*
class Patcher
{
public:
	static void* LoadSingleBandRasterIntoMemory(string strRasterFile)
	{
		GDALDataset* poInputDS = (GDALDataset*)GDALOpen((strRasterFile).c_str(), GA_ReadOnly);
		if (!poInputDS) return 0;

		GDALDataType ePixelType = poInputDS->GetRasterBand(1)->GetRasterDataType();
		void* pOutputData = 0;

		unsigned int nPixeCount = poInputDS->GetRasterXSize()*poInputDS->GetRasterYSize();

		switch (ePixelType)
		{
			case GDT_Byte:
				pOutputData = new char[nPixeCount];
				break;
			case GDT_UInt16:
				pOutputData = new uint16_t[nPixeCount];
				break;
			case GDT_Int16:
				pOutputData = new int16_t[nPixeCount];
				break;
			case GDT_UInt32:
				pOutputData = new uint32_t[nPixeCount];
				break;
			case GDT_Int32:
				pOutputData = new int32_t[nPixeCount];
				break;
			case GDT_Float32:
				pOutputData = new float[nPixeCount];
				break;
			case GDT_Float64:
				pOutputData = new double[nPixeCount];
				break;

			default:
				pOutputData = new char[nPixeCount];
				break;
		};
		
		poInputDS->RasterIO(GF_Read, 0,0, poInputDS->GetRasterXSize(), poInputDS->GetRasterYSize(),
			pOutputData, poInputDS->GetRasterXSize(), poInputDS->GetRasterYSize(), ePixelType, 1, 0, 0, 0, 0);

		GDALClose(poInputDS);

		return pOutputData;
	}

	static bool ExtractMetadata(string strRasterFile, 
								double* dblGeoTransform, 
								OGRSpatialReference* &poSRS,
								unsigned int &nWidth,
								unsigned int &nHeight,
								GDALDataType &ePixelType
								)
	{
		GDALDataset* poInputDS = (GDALDataset*)GDALOpen((strRasterFile).c_str(), GA_ReadOnly);
		if (!poInputDS) return false;

		poInputDS->GetGeoTransform(dblGeoTransform);
		poSRS = poInputDS->GetSpatialRef()->Clone();

		nWidth = poInputDS->GetRasterXSize();
		nHeight = poInputDS->GetRasterYSize();
		ePixelType = poInputDS->GetRasterBand(1)->GetRasterDataType();

		GDALClose(poInputDS);
		return true;
	}

	static bool SaveGeoRefSingleBandRaster(string strOutputRaster,
		void* pPixelData,
		GDALDataType ePixelType,
		unsigned int nWidth,
		unsigned int nHeight,
		double dblGeotransform[6],
		OGRSpatialReference* poSRS)
	{
		GDALDataset* poOutputDS = (GDALDataset*)GDALCreate(
			GDALGetDriverByName("GTiff"),
			strOutputRaster.c_str(),
			nWidth,nHeight, 1, ePixelType, 0);

		poOutputDS->SetSpatialRef(poSRS);
		poOutputDS->SetGeoTransform(dblGeotransform);
		poOutputDS->GetRasterBand(1)->SetNoDataValue(0);

		poOutputDS->RasterIO(GF_Write, 0, 0, nWidth, nHeight,
			pPixelData, nWidth, nHeight,
			ePixelType, 1, 0, 0, 0, 0);

		GDALClose(poOutputDS);
		return true;
	}

	static unsigned int CalcPotentialPatches(unsigned int nMaxWidth, double dblThreshold)
	{
		unsigned int nPos = 0;
		unsigned int nCount = 0;
		for (unsigned int i = 0; i < m_nWidth; i++)
		{
			for (unsigned int j = 0; j < m_nHeight; j++)
			{
				nPos = j * m_nWidth + i;
				if (m_pafInputEdgesData[nPos] < dblThreshold)
				{

				}
			}
		}
	}

	static bool Patch(string strInputEdges,
						string strCropMaskFile,
						string strOutputPatchedEdges,
						double dblThreshold,
						unsigned int nMaxWidth = 2)
	{
		m_panCropMaskData = (uint16_t*)LoadSingleBandRasterIntoMemory(strCropMaskFile);
		if (!m_panCropMaskData)
		{
			std::cout << "ERROR: can't read raster data from: " << strCropMaskFile << std::endl;
			return false;
		}
		m_pafInputEdgesData = (float*)LoadSingleBandRasterIntoMemory(strInputEdges);
		if (!m_pafInputEdgesData)
		{
			std::cout << "ERROR: can't read raster data from: " << strInputEdges << std::endl;
			delete[]m_panCropMaskData;
			return false;
		}

		double dblGeoTransform[6];
		OGRSpatialReference* poSRS;
		GDALDataType ePixelType;
		if (!ExtractMetadata(strInputEdges, dblGeoTransform, poSRS, m_nWidth, m_nHeight, ePixelType))
		{
			std::cout << "ERROR: can't read georeference from: " << strInputEdges << std::endl;
			delete[]m_panCropMaskData;
			delete[]m_pafInputEdgesData;
			return false;
		}

		m_pafOutputPatchedEdges = new float[m_nWidth * m_nHeight];
	
		SaveGeoRefSingleBandRaster(strOutputPatchedEdges,
			m_pafOutputPatchedEdges,
			ePixelType,
			m_nWidth,
			m_nHeight,
			dblGeoTransform,
			poSRS);

		OSRDestroySpatialReference(poSRS);
		delete[]m_panCropMaskData;
		delete[]m_pafInputEdgesData;
		delete[]m_pafOutputPatchedEdges;


		//load input raster and CropMask into memory
		//run processing
		//save output
		return true;
	}

	public:
		static unsigned int m_nWidth, m_nHeight;
		static float* m_pafOutputPatchedEdges;
		static uint16_t* m_panCropMaskData;
		static float* m_pafInputEdgesData
};
*/