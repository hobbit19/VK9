/*
Copyright(c) 2016 Christopher Joseph Dean Schaefer

This software is provided 'as-is', without any express or implied
warranty.In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions :

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software.If you use this software
in a product, an acknowledgement in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
 
#ifndef CINDEXBUFFER9_H
#define CINDEXBUFFER9_H

#include "d3d9.h" // Base class: IDirect3DIndexBuffer9
#include <vulkan/vulkan.h>
#include "CResource9.h"

class CIndexBuffer9 : public IDirect3DIndexBuffer9,CResource9
{
private:
	CDevice9* mDevice;
	UINT mLength;
	DWORD mUsage;
	D3DFORMAT mFormat; 
	D3DPOOL mPool;
	HANDLE* mSharedHandle;
public:
	CIndexBuffer9(CDevice9* device, UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, HANDLE* pSharedHandle);
	~CIndexBuffer9();

	int mReferenceCount;
	VkResult mResult;
	void* mData;
	size_t mSize;
	size_t mCapacity;
	bool mIsDirty;
	int mLockCount;

	VkMemoryRequirements mMemoryRequirements;
	VkBuffer mBuffer;
	VkDeviceMemory mMemory;
	VkIndexType mIndexType;

public:
	//IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void  **ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);	
	virtual ULONG STDMETHODCALLTYPE Release(void);

	//IDirect3DResource9
	virtual HRESULT STDMETHODCALLTYPE GetDevice(IDirect3DDevice9** ppDevice){(*ppDevice)=(IDirect3DDevice9*)mDevice; return S_OK;}
	virtual HRESULT STDMETHODCALLTYPE FreePrivateData(REFGUID refguid);
	virtual DWORD STDMETHODCALLTYPE GetPriority();
	virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData);
	virtual D3DRESOURCETYPE STDMETHODCALLTYPE GetType();
	virtual void STDMETHODCALLTYPE PreLoad();
	virtual DWORD STDMETHODCALLTYPE SetPriority(DWORD PriorityNew);
	virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID refguid, const void* pData, DWORD SizeOfData, DWORD Flags);

	//IDirect3DIndexBuffer9
	virtual HRESULT STDMETHODCALLTYPE GetDesc(D3DINDEXBUFFER_DESC* pDesc);
	virtual HRESULT STDMETHODCALLTYPE Lock(UINT OffsetToLock, UINT SizeToLock, VOID** ppbData, DWORD Flags);
	virtual HRESULT STDMETHODCALLTYPE Unlock();
};

#endif // CINDEXBUFFER9_H
