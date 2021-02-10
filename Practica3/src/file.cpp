#include "file.h"

#include "stdio.h"
#include "assert.h"

//-------------------------
void* OpenFile(const char* _sFileName, const char* _sMode)
{
	assert(_sFileName != nullptr);
	if (_sFileName != nullptr)
	{
		FILE* pFile(nullptr);
		fopen_s(&pFile, _sFileName, _sMode);
		return pFile;
	}
	return nullptr;
}

//-------------------------
int CloseFile(void* _pFile)
{
	assert(_pFile != nullptr);
	if (_pFile != nullptr)
	{
		return fclose(static_cast<FILE*>(_pFile));
	}
	return EOF;
}

//-------------------------
unsigned int ReadFile(void* _pFile, char* pBuffer_, unsigned int _uBufferSize)
{
	assert(_pFile != nullptr);
	assert(pBuffer_ != nullptr);
	if (_pFile != nullptr && pBuffer_ != nullptr)
	{
		return fread(pBuffer_, sizeof(char), _uBufferSize, static_cast<FILE*>(_pFile));
	}
	return 0;
}

//-------------------------
unsigned int WriteFile(void* _pFile, const char* _pBuffer, unsigned int _uBufferSize)
{
	assert(_pFile != nullptr);
	assert(_pBuffer != nullptr);
	if (_pFile != nullptr && _pBuffer != nullptr)
	{
		return fwrite(_pBuffer, sizeof(char), _uBufferSize, static_cast<FILE*>(_pFile));
	}
	return 0;
}