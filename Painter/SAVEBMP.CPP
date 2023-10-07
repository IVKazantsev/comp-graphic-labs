#include "stdafx.h"
#include "SaveBMP.h"


PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp)
{ 
    BITMAP bmp; 
    PBITMAPINFO pbmi; 
    WORD    cClrBits; 
 
    // �������� ������ �������� � ���������� ��� �� ������ (������ �����)
    if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)) 
        return NULL;
	
    // �������������� ������� ����� � ������������ ����� ���
	if(bmp.bmBitsPixel>24) bmp.bmBitsPixel=24;
    cClrBits = (WORD)(bmp.bmBitsPixel); 
    if (cClrBits == 1) 
        cClrBits = 1; 
    else if (cClrBits <= 4) 
        cClrBits = 4; 
    else if (cClrBits <= 8) 
        cClrBits = 8; 
	else if (cClrBits <= 16) 
        cClrBits = 16; 
    else 
        cClrBits = 24; 
    
    // �������� ������ ��� ���������  BITMAPINFO
	// � ������ ������� ��������� BITMAPINFOHEADER  
	if (cClrBits < 16)  // ��������� ����� ������� ������ (������ �������� RGBQUAD)
		pbmi = (PBITMAPINFO) new BYTE[	sizeof(BITMAPINFOHEADER) +
										sizeof(RGBQUAD) * (1<<cClrBits)];
    else  // ������� ���
		pbmi = (PBITMAPINFO) new BYTE[ sizeof(BITMAPINFOHEADER)];

  
    // ��������� ���� ��������� BITMAPINFO
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
    pbmi->bmiHeader.biWidth = bmp.bmWidth; 
    pbmi->bmiHeader.biHeight = bmp.bmHeight; 
    pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
    pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
	pbmi->bmiHeader.biXPelsPerMeter = 0;
	pbmi->bmiHeader.biYPelsPerMeter = 0; 

    if (cClrBits < 16) 
        pbmi->bmiHeader.biClrUsed = (1<<cClrBits);
     // ������� �������� �� ���������� - ������ ���� BI_RGB 
	pbmi->bmiHeader.biCompression = BI_RGB; 
 
	// ��������� ���������� ����, ��������� ��� �������� �����������
	// � ������ ���������� �������� � ��� �� ������.
    // � ����� BMP ������ ������ ���� ��������� �� ������� 4 ����,
	// ������� ����� ������ � ������ ������������ � ������� 
	// ������������ ������� (��. ���� savebmp.h)
    pbmi->bmiHeader.biSizeImage =	BYTESPERLINE(pbmi->bmiHeader.biWidth, cClrBits)*
									pbmi->bmiHeader.biHeight; 
 
    // ������� ��� ��� ����� ����� �������� ����� 
    pbmi->bmiHeader.biClrImportant = 0; 
 
    return pbmi; 
} 


BOOL SaveBitmapToBMPFile(CString &FileName, CBitmap &BMP, CDC &DC) 
 { 
 
    HANDLE hf=NULL;             // ��������� �� ����
    BITMAPFILEHEADER hdr;       // ��������� BMP �����
    PBITMAPINFOHEADER pbih;     // ��������� ��������
    BYTE * pBits=NULL;			// ��������� �� ��������� ������
    DWORD dwWidthBytes=0;       // ����� ������ ��������� ������ � ������
    DWORD dwTmp=0;			    // ��� ��������� ������������

	//������� ��������� - ��������� ������
	PBITMAPINFO pbmi=CreateBitmapInfoStruct((HBITMAP)BMP);
 
    pbih = (PBITMAPINFOHEADER) pbmi; 
	
	// �������� ������ ��� ��������� ������
	pBits =  new BYTE[pbih->biSizeImage];
    if (!pBits) return FALSE; 

    // �������� ��������� ������ 
	// � ������� ������ (������ �������� RGBQUAD) ���� ��� ����
	if (!GetDIBits(DC.m_hDC, (HBITMAP)BMP, 0, (WORD) pbih->biHeight, 
                   pBits, pbmi, DIB_RGB_COLORS)) 
       return FALSE; 
		
 
    // ������� ���� �� �����
    hf = CreateFile(FileName, 
                   GENERIC_READ | GENERIC_WRITE, 
                   (DWORD) 0, 
                   (LPSECURITY_ATTRIBUTES) NULL, 
                   CREATE_ALWAYS, 
                   FILE_ATTRIBUTE_NORMAL, 
                   (HANDLE) NULL); 
    if (hf == INVALID_HANDLE_VALUE) return FALSE; 
	// ������������� ���� ����� BMP: 0x42 = "B" 0x4d = "M"  
    hdr.bfType = 0x4d42;        
 
    // ������ ����� ����� ������ � ����������� � �������
    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
					pbih->biSize + pbih->biClrUsed 
					* sizeof(RGBQUAD) + pbih->biSizeImage); 
    hdr.bfReserved1 = 0; 
    hdr.bfReserved2 = 0; 
 
    // ��������� �������� �� ������ ��������� ������
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
                    pbih->biSize + pbih->biClrUsed 
                    * sizeof (RGBQUAD); 
 
    // ���������� ��������� ����� - ��������� BITMAPFILEHEADER
    if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
       (LPDWORD) &dwTmp, (LPOVERLAPPED) NULL)) 
       return FALSE;
 
    // ���������� ��������� �������� - ��������� BITMAPINFOHEADER
	// � ������� - ������ RGBQUAD 
 
    if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
                  + pbih->biClrUsed * sizeof (RGBQUAD), 
                  (LPDWORD) &dwTmp, (LPOVERLAPPED) NULL)) 
       return FALSE;
 
    // ���������� ��������� ������
	dwWidthBytes = BYTESPERLINE(pbih->biWidth, pbih->biBitCount);
	LONG i=0, j=0;
    BYTE	*pCurStr=NULL;		// ��������� �� ������� ������
	
	pCurStr=pBits;
	for(i=0; i<pbih->biHeight; i++) // ���������� �� �������
	{
		if (!WriteFile(hf, (LPSTR) pCurStr, (int) dwWidthBytes, 
                         (LPDWORD) &dwTmp, (LPOVERLAPPED) NULL)) 
			return FALSE;
		pCurStr+=dwWidthBytes;
    }
 
    // ��������� ����
     if (!CloseHandle(hf)) return FALSE; 
 
    // ����������� ������
    if(pBits!=NULL) delete[] pBits;
	if(pbmi!=NULL) delete[] pbmi;
	return TRUE;
} 
