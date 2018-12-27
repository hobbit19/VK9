// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

/*
"Honor the LORD with your wealth and with the firstfruits of all your produce; then your barns will be filled with plenty, and your vats will be bursting with wine." (Proverbs 3:9-10, ESV)
*/

#include <iostream>
#include "wtypes.h"

#include "C9.h"
#include "CDevice9.h"
#include "CSwapChain9.h"
#include "CSurface9.h"

#include "Utilities.h"

#define APP_SHORT_NAME "VK9"

#include "PrivateTypes.h"

C9::C9()
{
	mCommandStreamManager = std::make_shared<CommandStreamManager>();

	BOOST_LOG_TRIVIAL(info) << "C9::C9";
}

C9::~C9()
{
	WorkItem* workItem = mCommandStreamManager->GetWorkItem(nullptr);
	workItem->WorkItemType = WorkItemType::Instance_Destroy;
	workItem->Id = mId;
	mCommandStreamManager->RequestWorkAndWait(workItem);

	BOOST_LOG_TRIVIAL(info) << "C9::~C9";	
}

//IUnknown

ULONG STDMETHODCALLTYPE C9::AddRef(void)
{
	return InterlockedIncrement(&mReferenceCount);
}

HRESULT STDMETHODCALLTYPE C9::QueryInterface(REFIID riid,void  **ppv)
{
	if (ppv == nullptr)
	{
		return E_POINTER;
	}

	if (IsEqualGUID(riid, IID_IDirect3D9))
	{
		(*ppv) = this;
		this->AddRef();
		return S_OK;
	}

	if (IsEqualGUID(riid, IID_IUnknown))
	{
		(*ppv) = this;
		this->AddRef();
		return S_OK;
	}

	(*ppv) = nullptr;

	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE C9::Release(void)
{
	ULONG ref = InterlockedDecrement(&mReferenceCount);

	if (ref == 0)
	{
		delete this;
	}

	return ref;
}

//IDirect3D9

HRESULT STDMETHODCALLTYPE C9::CheckDepthStencilMatch(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat)
{
	if (DepthStencilFormat == D3DFMT_UNKNOWN || (ConvertFormat(AdapterFormat) != vk::Format::eUndefined && ConvertFormat(DepthStencilFormat) != vk::Format::eUndefined))
	{
		BOOST_LOG_TRIVIAL(warning) << "C9::CheckDepthStencilMatch (D3D_OK) AdapterFormat: " << AdapterFormat << " CheckFormat: " << DepthStencilFormat;

		return D3D_OK;
	}
	else
	{
		BOOST_LOG_TRIVIAL(warning) << "C9::CheckDepthStencilMatch (D3DERR_NOTAVAILABLE) AdapterFormat: " << AdapterFormat << " CheckFormat: " << DepthStencilFormat;

		return D3DERR_NOTAVAILABLE;
	}
}

HRESULT STDMETHODCALLTYPE C9::CheckDeviceFormat(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat)
{
	if (CheckFormat == D3DFMT_UNKNOWN || (ConvertFormat(AdapterFormat) != vk::Format::eUndefined && ConvertFormat(CheckFormat) != vk::Format::eUndefined))
	{
		BOOST_LOG_TRIVIAL(warning) << "C9::CheckDeviceFormat (D3D_OK) AdapterFormat: " << AdapterFormat << " CheckFormat: " << CheckFormat;

		return D3D_OK;
	}
	else
	{
		BOOST_LOG_TRIVIAL(warning) << "C9::CheckDeviceFormat (D3DERR_NOTAVAILABLE) AdapterFormat: " << AdapterFormat << " CheckFormat: " << CheckFormat;

		return D3DERR_NOTAVAILABLE;
	}
}


HRESULT STDMETHODCALLTYPE C9::CheckDeviceFormatConversion(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat)
{
	HRESULT result = S_OK;

	//TODO: Implement.

	BOOST_LOG_TRIVIAL(warning) << "C9::CheckDeviceFormatConversion is not implemented!";

	return result;
}


HRESULT STDMETHODCALLTYPE C9::CheckDeviceMultiSampleType(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD *pQualityLevels)
{
	if (Adapter >= mMonitors.size())
	{
		return D3DERR_INVALIDCALL;
	}

	if (MultiSampleType > 16)
	{
		return D3DERR_NOTAVAILABLE;
	}

	if (ConvertFormat(SurfaceFormat) == vk::Format::eUndefined)
	{
		return D3DERR_NOTAVAILABLE;
	}

	//TODO: Implement.

	BOOST_LOG_TRIVIAL(warning) << "C9::CheckDeviceMultiSampleType is not implemented!";

	if (pQualityLevels!= nullptr)
	{
		(*pQualityLevels) = 1;
	}

	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE C9::CheckDeviceType(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL Windowed)
{		
	//TODO: Implement.

	BOOST_LOG_TRIVIAL(warning) << "C9::CheckDeviceType is not implemented!";

	return S_OK;	
}

HRESULT STDMETHODCALLTYPE C9::CreateDevice(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS *pPresentationParameters,IDirect3DDevice9 **ppReturnedDeviceInterface)
{
	HRESULT result = S_OK;

	CDevice9* obj = new CDevice9(this,Adapter,DeviceType,hFocusWindow,BehaviorFlags,pPresentationParameters, nullptr);

	(*ppReturnedDeviceInterface) = (IDirect3DDevice9*)obj;

	obj->Init();

	return result;	
}

HRESULT STDMETHODCALLTYPE C9::EnumAdapterModes(UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE *pMode)
{
	if (Adapter >= mMonitors.size())
	{
		return D3DERR_INVALIDCALL;
	}

	if (Format != D3DFMT_X8R8G8B8)
	{
		return D3DERR_NOTAVAILABLE;
	}

	Monitor& monitor = mMonitors[Adapter];


	pMode->RefreshRate = monitor.RefreshRate;
	pMode->Format = D3DFMT_X8R8G8B8;

	switch (Mode)
	{
	case 0:
		pMode->Width = 1024;
		pMode->Height = 768;	
		break;
	case 1:
		pMode->Width = 1280;
		pMode->Height = 720;
		break;
	case 2:
		pMode->Width = 1920;
		pMode->Height = 1080;
		break;
	case 3:
		pMode->Width = 2560;
		pMode->Height = 1440;
		break;
	case 4:
		pMode->Width = 3840;
		pMode->Height = 2160;
		break;
	case 5:
		pMode->Width = 7680;
		pMode->Height = 4320;
		break;
	default:
			pMode->Width = monitor.Width;
			pMode->Height = monitor.Height;	
		break;
	}

	return D3D_OK;
}

UINT STDMETHODCALLTYPE C9::GetAdapterCount()
{
	BOOST_LOG_TRIVIAL(warning) << "C9::GetAdapterCount is not implemented!";

	return 1;
}

HRESULT STDMETHODCALLTYPE C9::GetAdapterDisplayMode(UINT Adapter,D3DDISPLAYMODE *pMode)
{
	Monitor& monitor = mMonitors[Adapter];

	pMode->RefreshRate = monitor.RefreshRate;
	pMode->Format = D3DFMT_X8R8G8B8;
	pMode->Height = monitor.Height;
	pMode->Width = monitor.Width;

	if (monitor.PixelBits != 32)
	{
		BOOST_LOG_TRIVIAL(info) << Adapter;
		BOOST_LOG_TRIVIAL(info) << monitor.RefreshRate;
		BOOST_LOG_TRIVIAL(info) << monitor.Height;
		BOOST_LOG_TRIVIAL(info) << monitor.Width;

		BOOST_LOG_TRIVIAL(info) << "C9::GetAdapterDisplayMode Unknown pixel bit format : " << monitor.PixelBits; //Revisit
	}

	return S_OK;	
}

HRESULT STDMETHODCALLTYPE C9::GetAdapterIdentifier(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9 *pIdentifier)
{		
	WorkItem* workItem = mCommandStreamManager->GetWorkItem(this);
	workItem->WorkItemType = WorkItemType::Instance_GetAdapterIdentifier;
	workItem->Id = mId;
	workItem->Argument1 = (void*)Adapter;
	workItem->Argument2 = (void*)Flags;
	workItem->Argument3 = (void*)pIdentifier;
	mCommandStreamManager->RequestWorkAndWait(workItem);

	return S_OK;	
}

UINT STDMETHODCALLTYPE C9::GetAdapterModeCount(UINT Adapter,D3DFORMAT Format)
{	
	//TODO: Implement.

	if (Format == D3DFMT_X8R8G8B8)
	{
		return 6;
	}

	return 0;	
}


HMONITOR STDMETHODCALLTYPE C9::GetAdapterMonitor(UINT Adapter)
{
	if ((mMonitors.size()-1) < Adapter)
	{
		return mMonitors[0].hMonitor;
	}
	else
	{
		return mMonitors[Adapter].hMonitor;
	}
}


HRESULT STDMETHODCALLTYPE C9::GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9 *pCaps)
{
	WorkItem* workItem = mCommandStreamManager->GetWorkItem(this);
	workItem->WorkItemType = WorkItemType::Instance_GetDeviceCaps;
	workItem->Id = mId;
	workItem->Argument1 = (void*)Adapter;
	workItem->Argument2 = (void*)DeviceType;
	workItem->Argument3 = (void*)pCaps;
	mCommandStreamManager->RequestWorkAndWait(workItem);

	return S_OK;	
}

HRESULT STDMETHODCALLTYPE C9::RegisterSoftwareDevice(void *pInitializeFunction)
{
	//TODO: Implement.

	BOOST_LOG_TRIVIAL(warning) << "C9::RegisterSoftwareDevice is not implemented!";

	return E_NOTIMPL;
}

UINT STDMETHODCALLTYPE C9::GetAdapterModeCountEx(UINT Adapter, const D3DDISPLAYMODEFILTER *pFilter)
{
	//TODO: Implement.

	BOOST_LOG_TRIVIAL(warning) << "C9::GetAdapterModeCountEx is not implemented!";

	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE C9::EnumAdapterModesEx(UINT Adapter, const D3DDISPLAYMODEFILTER *pFilter, UINT Mode, D3DDISPLAYMODEEX *pMode)
{
	//TODO: Implement.

	BOOST_LOG_TRIVIAL(warning) << "C9::EnumAdapterModesEx is not implemented!";

	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE C9::GetAdapterDisplayModeEx(UINT Adapter, D3DDISPLAYMODEEX *pMode, D3DDISPLAYROTATION *pRotation)
{
	//TODO: Implement.

	BOOST_LOG_TRIVIAL(warning) << "C9::GetAdapterDisplayModeEx is not implemented!";

	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE C9::CreateDeviceEx(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, D3DDISPLAYMODEEX *pFullscreenDisplayMode, IDirect3DDevice9Ex **ppReturnedDeviceInterface)
{
	HRESULT result = S_OK;

	CDevice9* obj = new CDevice9(this, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, pFullscreenDisplayMode);

	(*ppReturnedDeviceInterface) = (IDirect3DDevice9Ex*)obj;

	obj->Init();

	return result;
}

HRESULT STDMETHODCALLTYPE C9::GetAdapterLUID(UINT Adapter, LUID *pLUID)
{
	//TODO: Implement.

	BOOST_LOG_TRIVIAL(warning) << "C9::GetAdapterLUID is not implemented!";

	return E_NOTIMPL;
}

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	Monitor monitor;
	
	monitor.hMonitor = hMonitor;
	monitor.hdcMonitor = hdcMonitor;

	monitor.Height = ::GetDeviceCaps(monitor.hdcMonitor, HORZRES);
	monitor.Width = ::GetDeviceCaps(monitor.hdcMonitor, VERTRES);
	monitor.RefreshRate = ::GetDeviceCaps(monitor.hdcMonitor, VREFRESH);
	monitor.PixelBits = ::GetDeviceCaps(monitor.hdcMonitor, BITSPIXEL);
	monitor.ColorPlanes = ::GetDeviceCaps(monitor.hdcMonitor, PLANES);

	if (dwData != NULL)
	{
		if (hMonitor==0)
		{
			return false;
		}
		std::vector<Monitor>* monitors;
		monitors = (std::vector<Monitor>*)dwData;
		monitors->push_back(monitor);

		BOOST_LOG_TRIVIAL(info) << "MonitorEnumProc HMONITOR: " << monitor.hMonitor;
		BOOST_LOG_TRIVIAL(info) << "MonitorEnumProc HDC: " << monitor.hdcMonitor;

		BOOST_LOG_TRIVIAL(info) << "MonitorEnumProc Height: " << monitor.Height;
		BOOST_LOG_TRIVIAL(info) << "MonitorEnumProc Width: " << monitor.Width;
		BOOST_LOG_TRIVIAL(info) << "MonitorEnumProc RefreshRate: " << monitor.RefreshRate;

		BOOST_LOG_TRIVIAL(info) << "MonitorEnumProc PixelBits: " << monitor.PixelBits;
		BOOST_LOG_TRIVIAL(info) << "MonitorEnumProc ColorPlanes: " << monitor.ColorPlanes;

		return true;
	}
	else
	{
		BOOST_LOG_TRIVIAL(error) << "MonitorEnumProc: monitor vector is null.";
		return false;
	}	
}