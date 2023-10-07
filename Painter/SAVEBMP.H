
// ������ ��� ����������� ���������� ���� � ����������� �� DWORD ������ �������� � DIB 
// Width - ����� ������ � ��������; BPP - ��� �� ������
#define BYTESPERLINE(Width, BPP) ((WORD)((((DWORD)(Width) * (DWORD)(BPP) + 31) >> 5)) << 2) 

BOOL SaveBitmapToBMPFile(CString &FileName, CBitmap &BMP, CDC &DC);
PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp);
