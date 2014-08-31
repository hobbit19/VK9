/*
 * Copyright (C) 2014 Christopher Joseph Dean Schaefer
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */


#ifndef IDIRECT3DINDEXBUFFER9_H
#define IDIRECT3DINDEXBUFFER9_H

#include "IDirect3DResource9.h" // Base class: IDirect3DResource9

class IDirect3DIndexBuffer9 : public IDirect3DResource9
{
public:
	IDirect3DIndexBuffer9();
	~IDirect3DIndexBuffer9();

	/*
	 * Retrieves a description of the index buffer resource.
	 */
	virtual HRESULT GetDesc(D3DINDEXBUFFER_DESC *pDesc);
	
	/*
	 * Locks a range of index data obtains a pointer to the index buffer memory.
	 */
	virtual HRESULT Lock(UINT OffsetToLock,UINT SizeToLock,VOID **ppbData,DWORD Flags);
	
	/*
	 * Unlocks index data.
	 */
	virtual HRESULT Unlock();
};

#endif // IDIRECT3DINDEXBUFFER9_H