/*
 * Copyright (C) 2004-2014 ZNC, see the NOTICE file for details.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Parts of SWIG are used here.
 */

/***************************************************************************
 * This file is generated automatically using codegen.pl from functions.in *
 * Don't change it manually.                                               *
 ***************************************************************************/

namespace {
/*	template<class T>
	struct pyobj_to_ptr {
		CString m_sType;
		SvToPtr(const CString& sType) {
			m_sType = sType;
		}
		bool operator()(PyObject* py, T** result) {
			T* x = NULL;
			int res = SWIG_ConvertPtr(sv, (void**)&x, SWIG_TypeQuery(m_sType.c_str()), 0);
			if (SWIG_IsOK(res)) {
				*result = x;
				return true;
			}
			DEBUG("modpython: ");
			return false;
		}
	};

	CModule::EModRet SvToEModRet(PyObject* py, CModule::EModRet* result) {
		long int x = PyLong_AsLong();
		return static_cast<CModule::EModRet>(SvUV(sv));
	}*/

	inline swig_type_info* SWIG_pchar_descriptor(void) {
		static int init = 0;
		static swig_type_info* info = 0;
		if (!init) {
			info = SWIG_TypeQuery("_p_char");
			init = 1;
		}
		return info;
	}

	inline int SWIG_AsCharPtrAndSize(PyObject *obj, char** cptr, size_t* psize, int *alloc) {
#if PY_VERSION_HEX>=0x03000000
		if (PyUnicode_Check(obj))
#else
			if (PyString_Check(obj))
#endif
			{
				char *cstr; Py_ssize_t len;
#if PY_VERSION_HEX>=0x03000000
				if (!alloc && cptr) {
					/* We can't allow converting without allocation, since the internal
					   representation of string in Python 3 is UCS-2/UCS-4 but we require
					   a UTF-8 representation.
					   TODO(bhy) More detailed explanation */
					return SWIG_RuntimeError;
				}
				obj = PyUnicode_AsUTF8String(obj);
				PyBytes_AsStringAndSize(obj, &cstr, &len);
				if(alloc) *alloc = SWIG_NEWOBJ;
#else
				PyString_AsStringAndSize(obj, &cstr, &len);
#endif
				if (cptr) {
					if (alloc) {
						/*
						   In python the user should not be able to modify the inner
						   string representation. To warranty that, if you define
						   SWIG_PYTHON_SAFE_CSTRINGS, a new/copy of the python string
						   buffer is always returned.

						   The default behavior is just to return the pointer value,
						   so, be careful.
						 */
#if defined(SWIG_PYTHON_SAFE_CSTRINGS)
						if (*alloc != SWIG_OLDOBJ)
#else
							if (*alloc == SWIG_NEWOBJ)
#endif
							{
								*cptr = (char *)memcpy((char *)malloc((len + 1)*sizeof(char)), cstr, sizeof(char)*(len + 1));
								*alloc = SWIG_NEWOBJ;
							}
							else {
								*cptr = cstr;
								*alloc = SWIG_OLDOBJ;
							}
					} else {
#if PY_VERSION_HEX>=0x03000000
						assert(0); /* Should never reach here in Python 3 */
#endif
						*cptr = SWIG_Python_str_AsChar(obj);
					}
				}
				if (psize) *psize = len + 1;
#if PY_VERSION_HEX>=0x03000000
				Py_XDECREF(obj);
#endif
				return SWIG_OK;
			} else {
				swig_type_info* pchar_descriptor = SWIG_pchar_descriptor();
				if (pchar_descriptor) {
					void* vptr = 0;
					if (SWIG_ConvertPtr(obj, &vptr, pchar_descriptor, 0) == SWIG_OK) {
						if (cptr) *cptr = (char *) vptr;
						if (psize) *psize = vptr ? (strlen((char *)vptr) + 1) : 0;
						if (alloc) *alloc = SWIG_OLDOBJ;
						return SWIG_OK;
					}
				}
			}
		return SWIG_TypeError;
	}

	inline int SWIG_AsPtr_std_string (PyObject * obj, CString **val) {
		char* buf = 0 ; size_t size = 0; int alloc = SWIG_OLDOBJ;
		if (SWIG_IsOK((SWIG_AsCharPtrAndSize(obj, &buf, &size, &alloc)))) {
			if (buf) {
				if (val) *val = new CString(buf, size - 1);
				if (alloc == SWIG_NEWOBJ) free((char*)buf);
				return SWIG_NEWOBJ;
			} else {
				if (val) *val = 0;
				return SWIG_OLDOBJ;
			}
		} else {
			static int init = 0;
			static swig_type_info* descriptor = 0;
			if (!init) {
				descriptor = SWIG_TypeQuery("CString" " *");
				init = 1;
			}
			if (descriptor) {
				CString *vptr;
				int res = SWIG_ConvertPtr(obj, (void**)&vptr, descriptor, 0);
				if (SWIG_IsOK(res) && val) *val = vptr;
				return res;
			}
		}
		return SWIG_ERROR;
	}
}

bool CPyModule::OnBoot() {
	PyObject* pyName = Py_BuildValue("s", "OnBoot");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnBoot: can't convert string 'OnBoot' to PyObject: " << sPyErr);
		return true;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnBoot failed: " << sPyErr);
		Py_CLEAR(pyName);
		return true;
	}
	Py_CLEAR(pyName);
	bool result;
	if (pyRes == Py_None) {
		result = true;
	} else {
		int x = PyObject_IsTrue(pyRes);
		if (-1 == x) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnBoot was expected to return EModRet but: " << sPyErr);
			result = true;
		} else result = x ? true : false;
	}
	Py_CLEAR(pyRes);
	return result;
}

bool CPyModule::WebRequiresLogin() {
	PyObject* pyName = Py_BuildValue("s", "WebRequiresLogin");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/WebRequiresLogin: can't convert string 'WebRequiresLogin' to PyObject: " << sPyErr);
		return true;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/WebRequiresLogin failed: " << sPyErr);
		Py_CLEAR(pyName);
		return true;
	}
	Py_CLEAR(pyName);
	bool result;
	if (pyRes == Py_None) {
		result = true;
	} else {
		int x = PyObject_IsTrue(pyRes);
		if (-1 == x) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/WebRequiresLogin was expected to return EModRet but: " << sPyErr);
			result = true;
		} else result = x ? true : false;
	}
	Py_CLEAR(pyRes);
	return result;
}

bool CPyModule::WebRequiresAdmin() {
	PyObject* pyName = Py_BuildValue("s", "WebRequiresAdmin");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/WebRequiresAdmin: can't convert string 'WebRequiresAdmin' to PyObject: " << sPyErr);
		return false;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/WebRequiresAdmin failed: " << sPyErr);
		Py_CLEAR(pyName);
		return false;
	}
	Py_CLEAR(pyName);
	bool result;
	if (pyRes == Py_None) {
		result = false;
	} else {
		int x = PyObject_IsTrue(pyRes);
		if (-1 == x) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/WebRequiresAdmin was expected to return EModRet but: " << sPyErr);
			result = false;
		} else result = x ? true : false;
	}
	Py_CLEAR(pyRes);
	return result;
}

CString CPyModule::GetWebMenuTitle() {
	PyObject* pyName = Py_BuildValue("s", "GetWebMenuTitle");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/GetWebMenuTitle: can't convert string 'GetWebMenuTitle' to PyObject: " << sPyErr);
		return "";
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/GetWebMenuTitle failed: " << sPyErr);
		Py_CLEAR(pyName);
		return "";
	}
	Py_CLEAR(pyName);
	CString result;
	if (pyRes == Py_None) {
		result = "";
	} else {
		CString* p = NULL;
		int res = SWIG_AsPtr_std_string(pyRes, &p);
		if (!SWIG_IsOK(res)) {
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/GetWebMenuTitle was expected to return 'CString' but error=" << res);
			result = "";
		} else if (!p) {
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/GetWebMenuTitle was expected to return 'CString' but returned NULL");
			result = "";
		} else result = *p;
		if (SWIG_IsNewObj(res)) free((char*)p); // Don't ask me, that's how SWIG works...
	}
	Py_CLEAR(pyRes);
	return result;
}

bool CPyModule::OnWebPreRequest(CWebSock& WebSock, const CString& sPageName) {
	PyObject* pyName = Py_BuildValue("s", "OnWebPreRequest");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnWebPreRequest: can't convert string 'OnWebPreRequest' to PyObject: " << sPyErr);
		return false;
	}
	PyObject* pyArg_WebSock = SWIG_NewInstanceObj(const_cast<CWebSock*>(&WebSock), SWIG_TypeQuery("CWebSock*"), 0);
	if (!pyArg_WebSock) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnWebPreRequest: can't convert parameter 'WebSock' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return false;
	}
	PyObject* pyArg_sPageName = Py_BuildValue("s", sPageName.c_str());
	if (!pyArg_sPageName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnWebPreRequest: can't convert parameter 'sPageName' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_WebSock);
		return false;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_WebSock, pyArg_sPageName, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnWebPreRequest failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_WebSock);
		Py_CLEAR(pyArg_sPageName);
		return false;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_WebSock);
	Py_CLEAR(pyArg_sPageName);
	bool result;
	if (pyRes == Py_None) {
		result = false;
	} else {
		int x = PyObject_IsTrue(pyRes);
		if (-1 == x) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnWebPreRequest was expected to return EModRet but: " << sPyErr);
			result = false;
		} else result = x ? true : false;
	}
	Py_CLEAR(pyRes);
	return result;
}

bool CPyModule::OnWebRequest(CWebSock& WebSock, const CString& sPageName, CTemplate& Tmpl) {
	PyObject* pyName = Py_BuildValue("s", "OnWebRequest");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnWebRequest: can't convert string 'OnWebRequest' to PyObject: " << sPyErr);
		return false;
	}
	PyObject* pyArg_WebSock = SWIG_NewInstanceObj(const_cast<CWebSock*>(&WebSock), SWIG_TypeQuery("CWebSock*"), 0);
	if (!pyArg_WebSock) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnWebRequest: can't convert parameter 'WebSock' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return false;
	}
	PyObject* pyArg_sPageName = Py_BuildValue("s", sPageName.c_str());
	if (!pyArg_sPageName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnWebRequest: can't convert parameter 'sPageName' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_WebSock);
		return false;
	}
	PyObject* pyArg_Tmpl = SWIG_NewInstanceObj(const_cast<CTemplate*>(&Tmpl), SWIG_TypeQuery("CTemplate*"), 0);
	if (!pyArg_Tmpl) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnWebRequest: can't convert parameter 'Tmpl' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_WebSock);
		Py_CLEAR(pyArg_sPageName);
		return false;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_WebSock, pyArg_sPageName, pyArg_Tmpl, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnWebRequest failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_WebSock);
		Py_CLEAR(pyArg_sPageName);
		Py_CLEAR(pyArg_Tmpl);
		return false;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_WebSock);
	Py_CLEAR(pyArg_sPageName);
	Py_CLEAR(pyArg_Tmpl);
	bool result;
	if (pyRes == Py_None) {
		result = false;
	} else {
		int x = PyObject_IsTrue(pyRes);
		if (-1 == x) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnWebRequest was expected to return EModRet but: " << sPyErr);
			result = false;
		} else result = x ? true : false;
	}
	Py_CLEAR(pyRes);
	return result;
}

VWebSubPages* CPyModule::_GetSubPages() {
	PyObject* pyName = Py_BuildValue("s", "_GetSubPages");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/_GetSubPages: can't convert string '_GetSubPages' to PyObject: " << sPyErr);
		return (VWebSubPages*)NULL;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/_GetSubPages failed: " << sPyErr);
		Py_CLEAR(pyName);
		return (VWebSubPages*)NULL;
	}
	Py_CLEAR(pyName);
	VWebSubPages* result;
	if (pyRes == Py_None) {
		result = (VWebSubPages*)NULL;
	} else {
		int res = SWIG_ConvertPtr(pyRes, (void**)&result, SWIG_TypeQuery("VWebSubPages*"), 0);
		if (!SWIG_IsOK(res)) {
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/_GetSubPages was expected to return 'VWebSubPages*' but error=" << res);
			result = (VWebSubPages*)NULL;
		}
	}
	Py_CLEAR(pyRes);
	return result;
}

void CPyModule::OnPreRehash() {
	PyObject* pyName = Py_BuildValue("s", "OnPreRehash");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPreRehash: can't convert string 'OnPreRehash' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPreRehash failed: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyRes);
}

void CPyModule::OnPostRehash() {
	PyObject* pyName = Py_BuildValue("s", "OnPostRehash");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPostRehash: can't convert string 'OnPostRehash' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPostRehash failed: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyRes);
}

void CPyModule::OnIRCDisconnected() {
	PyObject* pyName = Py_BuildValue("s", "OnIRCDisconnected");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCDisconnected: can't convert string 'OnIRCDisconnected' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCDisconnected failed: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyRes);
}

void CPyModule::OnIRCConnected() {
	PyObject* pyName = Py_BuildValue("s", "OnIRCConnected");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCConnected: can't convert string 'OnIRCConnected' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCConnected failed: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyRes);
}

CModule::EModRet CPyModule::OnIRCConnecting(CIRCSock *pIRCSock) {
	PyObject* pyName = Py_BuildValue("s", "OnIRCConnecting");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCConnecting: can't convert string 'OnIRCConnecting' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_pIRCSock = SWIG_NewInstanceObj(const_cast<CIRCSock *>(pIRCSock), SWIG_TypeQuery("CIRCSock *"), 0);
	if (!pyArg_pIRCSock) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCConnecting: can't convert parameter 'pIRCSock' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_pIRCSock, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCConnecting failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pIRCSock);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_pIRCSock);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCConnecting was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

void CPyModule::OnIRCConnectionError(CIRCSock *pIRCSock) {
	PyObject* pyName = Py_BuildValue("s", "OnIRCConnectionError");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCConnectionError: can't convert string 'OnIRCConnectionError' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_pIRCSock = SWIG_NewInstanceObj(const_cast<CIRCSock *>(pIRCSock), SWIG_TypeQuery("CIRCSock *"), 0);
	if (!pyArg_pIRCSock) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCConnectionError: can't convert parameter 'pIRCSock' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_pIRCSock, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCConnectionError failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pIRCSock);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_pIRCSock);
	Py_CLEAR(pyRes);
}

CModule::EModRet CPyModule::OnIRCRegistration(CString& sPass, CString& sNick, CString& sIdent, CString& sRealName) {
	PyObject* pyName = Py_BuildValue("s", "OnIRCRegistration");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCRegistration: can't convert string 'OnIRCRegistration' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_sPass = CPyRetString::wrap(sPass);
	if (!pyArg_sPass) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCRegistration: can't convert parameter 'sPass' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sNick = CPyRetString::wrap(sNick);
	if (!pyArg_sNick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCRegistration: can't convert parameter 'sNick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sPass);
		return CONTINUE;
	}
	PyObject* pyArg_sIdent = CPyRetString::wrap(sIdent);
	if (!pyArg_sIdent) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCRegistration: can't convert parameter 'sIdent' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sPass);
		Py_CLEAR(pyArg_sNick);
		return CONTINUE;
	}
	PyObject* pyArg_sRealName = CPyRetString::wrap(sRealName);
	if (!pyArg_sRealName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCRegistration: can't convert parameter 'sRealName' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sPass);
		Py_CLEAR(pyArg_sNick);
		Py_CLEAR(pyArg_sIdent);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sPass, pyArg_sNick, pyArg_sIdent, pyArg_sRealName, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCRegistration failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sPass);
		Py_CLEAR(pyArg_sNick);
		Py_CLEAR(pyArg_sIdent);
		Py_CLEAR(pyArg_sRealName);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sPass);
	Py_CLEAR(pyArg_sNick);
	Py_CLEAR(pyArg_sIdent);
	Py_CLEAR(pyArg_sRealName);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnIRCRegistration was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnBroadcast(CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnBroadcast");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnBroadcast: can't convert string 'OnBroadcast' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnBroadcast: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnBroadcast failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnBroadcast was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

void CPyModule::OnChanPermission(const CNick& OpNick, const CNick& Nick, CChan& Channel, unsigned char uMode, bool bAdded, bool bNoChange) {
	PyObject* pyName = Py_BuildValue("s", "OnChanPermission");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanPermission: can't convert string 'OnChanPermission' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_OpNick = SWIG_NewInstanceObj(const_cast< CNick*>(&OpNick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_OpNick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanPermission: can't convert parameter 'OpNick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast< CNick*>(&Nick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanPermission: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		return ;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanPermission: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		return ;
	}
	PyObject* pyArg_uMode = Py_BuildValue("B", uMode);
	if (!pyArg_uMode) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanPermission: can't convert parameter 'uMode' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		return ;
	}
	PyObject* pyArg_bAdded = Py_BuildValue("l", (long int)bAdded);
	if (!pyArg_bAdded) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanPermission: can't convert parameter 'bAdded' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_uMode);
		return ;
	}
	PyObject* pyArg_bNoChange = Py_BuildValue("l", (long int)bNoChange);
	if (!pyArg_bNoChange) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanPermission: can't convert parameter 'bNoChange' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_uMode);
		Py_CLEAR(pyArg_bAdded);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_OpNick, pyArg_Nick, pyArg_Channel, pyArg_uMode, pyArg_bAdded, pyArg_bNoChange, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanPermission failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_uMode);
		Py_CLEAR(pyArg_bAdded);
		Py_CLEAR(pyArg_bNoChange);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_OpNick);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_Channel);
	Py_CLEAR(pyArg_uMode);
	Py_CLEAR(pyArg_bAdded);
	Py_CLEAR(pyArg_bNoChange);
	Py_CLEAR(pyRes);
}

void CPyModule::OnOp(const CNick& OpNick, const CNick& Nick, CChan& Channel, bool bNoChange) {
	PyObject* pyName = Py_BuildValue("s", "OnOp");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnOp: can't convert string 'OnOp' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_OpNick = SWIG_NewInstanceObj(const_cast< CNick*>(&OpNick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_OpNick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnOp: can't convert parameter 'OpNick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast< CNick*>(&Nick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnOp: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		return ;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnOp: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		return ;
	}
	PyObject* pyArg_bNoChange = Py_BuildValue("l", (long int)bNoChange);
	if (!pyArg_bNoChange) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnOp: can't convert parameter 'bNoChange' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_OpNick, pyArg_Nick, pyArg_Channel, pyArg_bNoChange, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnOp failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_bNoChange);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_OpNick);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_Channel);
	Py_CLEAR(pyArg_bNoChange);
	Py_CLEAR(pyRes);
}

void CPyModule::OnDeop(const CNick& OpNick, const CNick& Nick, CChan& Channel, bool bNoChange) {
	PyObject* pyName = Py_BuildValue("s", "OnDeop");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDeop: can't convert string 'OnDeop' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_OpNick = SWIG_NewInstanceObj(const_cast< CNick*>(&OpNick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_OpNick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDeop: can't convert parameter 'OpNick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast< CNick*>(&Nick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDeop: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		return ;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDeop: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		return ;
	}
	PyObject* pyArg_bNoChange = Py_BuildValue("l", (long int)bNoChange);
	if (!pyArg_bNoChange) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDeop: can't convert parameter 'bNoChange' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_OpNick, pyArg_Nick, pyArg_Channel, pyArg_bNoChange, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDeop failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_bNoChange);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_OpNick);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_Channel);
	Py_CLEAR(pyArg_bNoChange);
	Py_CLEAR(pyRes);
}

void CPyModule::OnVoice(const CNick& OpNick, const CNick& Nick, CChan& Channel, bool bNoChange) {
	PyObject* pyName = Py_BuildValue("s", "OnVoice");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnVoice: can't convert string 'OnVoice' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_OpNick = SWIG_NewInstanceObj(const_cast< CNick*>(&OpNick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_OpNick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnVoice: can't convert parameter 'OpNick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast< CNick*>(&Nick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnVoice: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		return ;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnVoice: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		return ;
	}
	PyObject* pyArg_bNoChange = Py_BuildValue("l", (long int)bNoChange);
	if (!pyArg_bNoChange) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnVoice: can't convert parameter 'bNoChange' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_OpNick, pyArg_Nick, pyArg_Channel, pyArg_bNoChange, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnVoice failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_bNoChange);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_OpNick);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_Channel);
	Py_CLEAR(pyArg_bNoChange);
	Py_CLEAR(pyRes);
}

void CPyModule::OnDevoice(const CNick& OpNick, const CNick& Nick, CChan& Channel, bool bNoChange) {
	PyObject* pyName = Py_BuildValue("s", "OnDevoice");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDevoice: can't convert string 'OnDevoice' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_OpNick = SWIG_NewInstanceObj(const_cast< CNick*>(&OpNick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_OpNick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDevoice: can't convert parameter 'OpNick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast< CNick*>(&Nick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDevoice: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		return ;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDevoice: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		return ;
	}
	PyObject* pyArg_bNoChange = Py_BuildValue("l", (long int)bNoChange);
	if (!pyArg_bNoChange) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDevoice: can't convert parameter 'bNoChange' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_OpNick, pyArg_Nick, pyArg_Channel, pyArg_bNoChange, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDevoice failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_bNoChange);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_OpNick);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_Channel);
	Py_CLEAR(pyArg_bNoChange);
	Py_CLEAR(pyRes);
}

void CPyModule::OnMode(const CNick& OpNick, CChan& Channel, char uMode, const CString& sArg, bool bAdded, bool bNoChange) {
	PyObject* pyName = Py_BuildValue("s", "OnMode");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnMode: can't convert string 'OnMode' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_OpNick = SWIG_NewInstanceObj(const_cast< CNick*>(&OpNick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_OpNick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnMode: can't convert parameter 'OpNick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnMode: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		return ;
	}
	PyObject* pyArg_uMode = Py_BuildValue("b", uMode);
	if (!pyArg_uMode) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnMode: can't convert parameter 'uMode' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Channel);
		return ;
	}
	PyObject* pyArg_sArg = Py_BuildValue("s", sArg.c_str());
	if (!pyArg_sArg) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnMode: can't convert parameter 'sArg' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_uMode);
		return ;
	}
	PyObject* pyArg_bAdded = Py_BuildValue("l", (long int)bAdded);
	if (!pyArg_bAdded) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnMode: can't convert parameter 'bAdded' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_uMode);
		Py_CLEAR(pyArg_sArg);
		return ;
	}
	PyObject* pyArg_bNoChange = Py_BuildValue("l", (long int)bNoChange);
	if (!pyArg_bNoChange) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnMode: can't convert parameter 'bNoChange' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_uMode);
		Py_CLEAR(pyArg_sArg);
		Py_CLEAR(pyArg_bAdded);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_OpNick, pyArg_Channel, pyArg_uMode, pyArg_sArg, pyArg_bAdded, pyArg_bNoChange, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnMode failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_uMode);
		Py_CLEAR(pyArg_sArg);
		Py_CLEAR(pyArg_bAdded);
		Py_CLEAR(pyArg_bNoChange);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_OpNick);
	Py_CLEAR(pyArg_Channel);
	Py_CLEAR(pyArg_uMode);
	Py_CLEAR(pyArg_sArg);
	Py_CLEAR(pyArg_bAdded);
	Py_CLEAR(pyArg_bNoChange);
	Py_CLEAR(pyRes);
}

void CPyModule::OnRawMode(const CNick& OpNick, CChan& Channel, const CString& sModes, const CString& sArgs) {
	PyObject* pyName = Py_BuildValue("s", "OnRawMode");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnRawMode: can't convert string 'OnRawMode' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_OpNick = SWIG_NewInstanceObj(const_cast< CNick*>(&OpNick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_OpNick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnRawMode: can't convert parameter 'OpNick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnRawMode: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		return ;
	}
	PyObject* pyArg_sModes = Py_BuildValue("s", sModes.c_str());
	if (!pyArg_sModes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnRawMode: can't convert parameter 'sModes' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Channel);
		return ;
	}
	PyObject* pyArg_sArgs = Py_BuildValue("s", sArgs.c_str());
	if (!pyArg_sArgs) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnRawMode: can't convert parameter 'sArgs' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_sModes);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_OpNick, pyArg_Channel, pyArg_sModes, pyArg_sArgs, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnRawMode failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_sModes);
		Py_CLEAR(pyArg_sArgs);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_OpNick);
	Py_CLEAR(pyArg_Channel);
	Py_CLEAR(pyArg_sModes);
	Py_CLEAR(pyArg_sArgs);
	Py_CLEAR(pyRes);
}

CModule::EModRet CPyModule::OnRaw(CString& sLine) {
	PyObject* pyName = Py_BuildValue("s", "OnRaw");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnRaw: can't convert string 'OnRaw' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_sLine = CPyRetString::wrap(sLine);
	if (!pyArg_sLine) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnRaw: can't convert parameter 'sLine' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sLine, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnRaw failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sLine);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sLine);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnRaw was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnStatusCommand(CString& sCommand) {
	PyObject* pyName = Py_BuildValue("s", "OnStatusCommand");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnStatusCommand: can't convert string 'OnStatusCommand' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_sCommand = CPyRetString::wrap(sCommand);
	if (!pyArg_sCommand) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnStatusCommand: can't convert parameter 'sCommand' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sCommand, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnStatusCommand failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sCommand);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sCommand);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnStatusCommand was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

void CPyModule::OnModCommand(const CString& sCommand) {
	PyObject* pyName = Py_BuildValue("s", "OnModCommand");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModCommand: can't convert string 'OnModCommand' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_sCommand = Py_BuildValue("s", sCommand.c_str());
	if (!pyArg_sCommand) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModCommand: can't convert parameter 'sCommand' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sCommand, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModCommand failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sCommand);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sCommand);
	Py_CLEAR(pyRes);
}

void CPyModule::OnModNotice(const CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnModNotice");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModNotice: can't convert string 'OnModNotice' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_sMessage = Py_BuildValue("s", sMessage.c_str());
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModNotice: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModNotice failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sMessage);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sMessage);
	Py_CLEAR(pyRes);
}

void CPyModule::OnModCTCP(const CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnModCTCP");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModCTCP: can't convert string 'OnModCTCP' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_sMessage = Py_BuildValue("s", sMessage.c_str());
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModCTCP: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModCTCP failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sMessage);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sMessage);
	Py_CLEAR(pyRes);
}

void CPyModule::OnQuit(const CNick& Nick, const CString& sMessage, const vector<CChan*>& vChans) {
	PyObject* pyName = Py_BuildValue("s", "OnQuit");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnQuit: can't convert string 'OnQuit' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast< CNick*>(&Nick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnQuit: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_sMessage = Py_BuildValue("s", sMessage.c_str());
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnQuit: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		return ;
	}
	PyObject* pyArg_vChans = PyList_New(0);
	if (!pyArg_vChans) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnQuit: can't convert parameter 'vChans' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_sMessage);
		return ;
	}
	for (vector<CChan*>::const_iterator i = vChans.begin(); i != vChans.end(); ++i) {
		PyObject* pyVecEl = SWIG_NewInstanceObj(*i, SWIG_TypeQuery("CChan*"), 0);
		if (!pyVecEl) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnQuit: can't convert element of vector 'vChans' to PyObject: " << sPyErr);
			Py_CLEAR(pyName);
			Py_CLEAR(pyArg_Nick);
			Py_CLEAR(pyArg_sMessage);
			Py_CLEAR(pyArg_vChans);
			return ;
		}
		if (PyList_Append(pyArg_vChans, pyVecEl)) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnQuit: can't add element of vector 'vChans' to PyObject: " << sPyErr);
			Py_CLEAR(pyVecEl);
			Py_CLEAR(pyName);
			Py_CLEAR(pyArg_Nick);
			Py_CLEAR(pyArg_sMessage);
			Py_CLEAR(pyArg_vChans);
			return ;
		}
		Py_CLEAR(pyVecEl);
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Nick, pyArg_sMessage, pyArg_vChans, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnQuit failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_sMessage);
		Py_CLEAR(pyArg_vChans);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_sMessage);
	Py_CLEAR(pyArg_vChans);
	Py_CLEAR(pyRes);
}

void CPyModule::OnNick(const CNick& Nick, const CString& sNewNick, const vector<CChan*>& vChans) {
	PyObject* pyName = Py_BuildValue("s", "OnNick");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnNick: can't convert string 'OnNick' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast< CNick*>(&Nick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnNick: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_sNewNick = Py_BuildValue("s", sNewNick.c_str());
	if (!pyArg_sNewNick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnNick: can't convert parameter 'sNewNick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		return ;
	}
	PyObject* pyArg_vChans = PyList_New(0);
	if (!pyArg_vChans) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnNick: can't convert parameter 'vChans' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_sNewNick);
		return ;
	}
	for (vector<CChan*>::const_iterator i = vChans.begin(); i != vChans.end(); ++i) {
		PyObject* pyVecEl = SWIG_NewInstanceObj(*i, SWIG_TypeQuery("CChan*"), 0);
		if (!pyVecEl) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnNick: can't convert element of vector 'vChans' to PyObject: " << sPyErr);
			Py_CLEAR(pyName);
			Py_CLEAR(pyArg_Nick);
			Py_CLEAR(pyArg_sNewNick);
			Py_CLEAR(pyArg_vChans);
			return ;
		}
		if (PyList_Append(pyArg_vChans, pyVecEl)) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnNick: can't add element of vector 'vChans' to PyObject: " << sPyErr);
			Py_CLEAR(pyVecEl);
			Py_CLEAR(pyName);
			Py_CLEAR(pyArg_Nick);
			Py_CLEAR(pyArg_sNewNick);
			Py_CLEAR(pyArg_vChans);
			return ;
		}
		Py_CLEAR(pyVecEl);
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Nick, pyArg_sNewNick, pyArg_vChans, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnNick failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_sNewNick);
		Py_CLEAR(pyArg_vChans);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_sNewNick);
	Py_CLEAR(pyArg_vChans);
	Py_CLEAR(pyRes);
}

void CPyModule::OnKick(const CNick& OpNick, const CString& sKickedNick, CChan& Channel, const CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnKick");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnKick: can't convert string 'OnKick' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_OpNick = SWIG_NewInstanceObj(const_cast< CNick*>(&OpNick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_OpNick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnKick: can't convert parameter 'OpNick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_sKickedNick = Py_BuildValue("s", sKickedNick.c_str());
	if (!pyArg_sKickedNick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnKick: can't convert parameter 'sKickedNick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		return ;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnKick: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_sKickedNick);
		return ;
	}
	PyObject* pyArg_sMessage = Py_BuildValue("s", sMessage.c_str());
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnKick: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_sKickedNick);
		Py_CLEAR(pyArg_Channel);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_OpNick, pyArg_sKickedNick, pyArg_Channel, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnKick failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_OpNick);
		Py_CLEAR(pyArg_sKickedNick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_sMessage);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_OpNick);
	Py_CLEAR(pyArg_sKickedNick);
	Py_CLEAR(pyArg_Channel);
	Py_CLEAR(pyArg_sMessage);
	Py_CLEAR(pyRes);
}

void CPyModule::OnJoin(const CNick& Nick, CChan& Channel) {
	PyObject* pyName = Py_BuildValue("s", "OnJoin");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnJoin: can't convert string 'OnJoin' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast< CNick*>(&Nick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnJoin: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnJoin: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Nick, pyArg_Channel, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnJoin failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_Channel);
	Py_CLEAR(pyRes);
}

void CPyModule::OnPart(const CNick& Nick, CChan& Channel, const CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnPart");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPart: can't convert string 'OnPart' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast< CNick*>(&Nick), SWIG_TypeQuery(" CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPart: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPart: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		return ;
	}
	PyObject* pyArg_sMessage = Py_BuildValue("s", sMessage.c_str());
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPart: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Nick, pyArg_Channel, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPart failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_sMessage);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_Channel);
	Py_CLEAR(pyArg_sMessage);
	Py_CLEAR(pyRes);
}

CModule::EModRet CPyModule::OnChanBufferStarting(CChan& Chan, CClient& Client) {
	PyObject* pyName = Py_BuildValue("s", "OnChanBufferStarting");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferStarting: can't convert string 'OnChanBufferStarting' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Chan = SWIG_NewInstanceObj(const_cast<CChan*>(&Chan), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Chan) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferStarting: can't convert parameter 'Chan' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_Client = SWIG_NewInstanceObj(const_cast<CClient*>(&Client), SWIG_TypeQuery("CClient*"), 0);
	if (!pyArg_Client) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferStarting: can't convert parameter 'Client' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Chan);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Chan, pyArg_Client, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferStarting failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Chan);
		Py_CLEAR(pyArg_Client);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Chan);
	Py_CLEAR(pyArg_Client);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferStarting was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnChanBufferEnding(CChan& Chan, CClient& Client) {
	PyObject* pyName = Py_BuildValue("s", "OnChanBufferEnding");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferEnding: can't convert string 'OnChanBufferEnding' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Chan = SWIG_NewInstanceObj(const_cast<CChan*>(&Chan), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Chan) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferEnding: can't convert parameter 'Chan' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_Client = SWIG_NewInstanceObj(const_cast<CClient*>(&Client), SWIG_TypeQuery("CClient*"), 0);
	if (!pyArg_Client) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferEnding: can't convert parameter 'Client' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Chan);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Chan, pyArg_Client, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferEnding failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Chan);
		Py_CLEAR(pyArg_Client);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Chan);
	Py_CLEAR(pyArg_Client);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferEnding was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnChanBufferPlayLine(CChan& Chan, CClient& Client, CString& sLine) {
	PyObject* pyName = Py_BuildValue("s", "OnChanBufferPlayLine");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferPlayLine: can't convert string 'OnChanBufferPlayLine' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Chan = SWIG_NewInstanceObj(const_cast<CChan*>(&Chan), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Chan) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferPlayLine: can't convert parameter 'Chan' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_Client = SWIG_NewInstanceObj(const_cast<CClient*>(&Client), SWIG_TypeQuery("CClient*"), 0);
	if (!pyArg_Client) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferPlayLine: can't convert parameter 'Client' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Chan);
		return CONTINUE;
	}
	PyObject* pyArg_sLine = CPyRetString::wrap(sLine);
	if (!pyArg_sLine) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferPlayLine: can't convert parameter 'sLine' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Chan);
		Py_CLEAR(pyArg_Client);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Chan, pyArg_Client, pyArg_sLine, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferPlayLine failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Chan);
		Py_CLEAR(pyArg_Client);
		Py_CLEAR(pyArg_sLine);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Chan);
	Py_CLEAR(pyArg_Client);
	Py_CLEAR(pyArg_sLine);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanBufferPlayLine was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnPrivBufferPlayLine(CClient& Client, CString& sLine) {
	PyObject* pyName = Py_BuildValue("s", "OnPrivBufferPlayLine");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivBufferPlayLine: can't convert string 'OnPrivBufferPlayLine' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Client = SWIG_NewInstanceObj(const_cast<CClient*>(&Client), SWIG_TypeQuery("CClient*"), 0);
	if (!pyArg_Client) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivBufferPlayLine: can't convert parameter 'Client' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sLine = CPyRetString::wrap(sLine);
	if (!pyArg_sLine) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivBufferPlayLine: can't convert parameter 'sLine' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Client);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Client, pyArg_sLine, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivBufferPlayLine failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Client);
		Py_CLEAR(pyArg_sLine);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Client);
	Py_CLEAR(pyArg_sLine);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivBufferPlayLine was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

void CPyModule::OnClientLogin() {
	PyObject* pyName = Py_BuildValue("s", "OnClientLogin");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientLogin: can't convert string 'OnClientLogin' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientLogin failed: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyRes);
}

void CPyModule::OnClientDisconnect() {
	PyObject* pyName = Py_BuildValue("s", "OnClientDisconnect");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientDisconnect: can't convert string 'OnClientDisconnect' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientDisconnect failed: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyRes);
}

CModule::EModRet CPyModule::OnUserRaw(CString& sLine) {
	PyObject* pyName = Py_BuildValue("s", "OnUserRaw");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserRaw: can't convert string 'OnUserRaw' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_sLine = CPyRetString::wrap(sLine);
	if (!pyArg_sLine) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserRaw: can't convert parameter 'sLine' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sLine, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserRaw failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sLine);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sLine);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserRaw was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnUserCTCPReply(CString& sTarget, CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnUserCTCPReply");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserCTCPReply: can't convert string 'OnUserCTCPReply' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_sTarget = CPyRetString::wrap(sTarget);
	if (!pyArg_sTarget) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserCTCPReply: can't convert parameter 'sTarget' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserCTCPReply: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sTarget);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sTarget, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserCTCPReply failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sTarget);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sTarget);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserCTCPReply was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnUserCTCP(CString& sTarget, CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnUserCTCP");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserCTCP: can't convert string 'OnUserCTCP' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_sTarget = CPyRetString::wrap(sTarget);
	if (!pyArg_sTarget) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserCTCP: can't convert parameter 'sTarget' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserCTCP: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sTarget);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sTarget, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserCTCP failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sTarget);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sTarget);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserCTCP was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnUserAction(CString& sTarget, CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnUserAction");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserAction: can't convert string 'OnUserAction' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_sTarget = CPyRetString::wrap(sTarget);
	if (!pyArg_sTarget) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserAction: can't convert parameter 'sTarget' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserAction: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sTarget);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sTarget, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserAction failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sTarget);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sTarget);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserAction was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnUserMsg(CString& sTarget, CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnUserMsg");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserMsg: can't convert string 'OnUserMsg' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_sTarget = CPyRetString::wrap(sTarget);
	if (!pyArg_sTarget) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserMsg: can't convert parameter 'sTarget' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserMsg: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sTarget);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sTarget, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserMsg failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sTarget);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sTarget);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserMsg was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnUserNotice(CString& sTarget, CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnUserNotice");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserNotice: can't convert string 'OnUserNotice' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_sTarget = CPyRetString::wrap(sTarget);
	if (!pyArg_sTarget) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserNotice: can't convert parameter 'sTarget' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserNotice: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sTarget);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sTarget, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserNotice failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sTarget);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sTarget);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserNotice was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnUserJoin(CString& sChannel, CString& sKey) {
	PyObject* pyName = Py_BuildValue("s", "OnUserJoin");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserJoin: can't convert string 'OnUserJoin' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_sChannel = CPyRetString::wrap(sChannel);
	if (!pyArg_sChannel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserJoin: can't convert parameter 'sChannel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sKey = CPyRetString::wrap(sKey);
	if (!pyArg_sKey) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserJoin: can't convert parameter 'sKey' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sChannel);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sChannel, pyArg_sKey, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserJoin failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sChannel);
		Py_CLEAR(pyArg_sKey);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sChannel);
	Py_CLEAR(pyArg_sKey);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserJoin was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnUserPart(CString& sChannel, CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnUserPart");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserPart: can't convert string 'OnUserPart' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_sChannel = CPyRetString::wrap(sChannel);
	if (!pyArg_sChannel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserPart: can't convert parameter 'sChannel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserPart: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sChannel);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sChannel, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserPart failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sChannel);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sChannel);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserPart was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnUserTopic(CString& sChannel, CString& sTopic) {
	PyObject* pyName = Py_BuildValue("s", "OnUserTopic");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserTopic: can't convert string 'OnUserTopic' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_sChannel = CPyRetString::wrap(sChannel);
	if (!pyArg_sChannel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserTopic: can't convert parameter 'sChannel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sTopic = CPyRetString::wrap(sTopic);
	if (!pyArg_sTopic) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserTopic: can't convert parameter 'sTopic' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sChannel);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sChannel, pyArg_sTopic, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserTopic failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sChannel);
		Py_CLEAR(pyArg_sTopic);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sChannel);
	Py_CLEAR(pyArg_sTopic);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserTopic was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnUserTopicRequest(CString& sChannel) {
	PyObject* pyName = Py_BuildValue("s", "OnUserTopicRequest");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserTopicRequest: can't convert string 'OnUserTopicRequest' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_sChannel = CPyRetString::wrap(sChannel);
	if (!pyArg_sChannel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserTopicRequest: can't convert parameter 'sChannel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sChannel, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserTopicRequest failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sChannel);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sChannel);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUserTopicRequest was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnCTCPReply(CNick& Nick, CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnCTCPReply");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnCTCPReply: can't convert string 'OnCTCPReply' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast<CNick*>(&Nick), SWIG_TypeQuery("CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnCTCPReply: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnCTCPReply: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Nick, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnCTCPReply failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnCTCPReply was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnPrivCTCP(CNick& Nick, CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnPrivCTCP");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivCTCP: can't convert string 'OnPrivCTCP' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast<CNick*>(&Nick), SWIG_TypeQuery("CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivCTCP: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivCTCP: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Nick, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivCTCP failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivCTCP was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnChanCTCP(CNick& Nick, CChan& Channel, CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnChanCTCP");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanCTCP: can't convert string 'OnChanCTCP' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast<CNick*>(&Nick), SWIG_TypeQuery("CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanCTCP: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanCTCP: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanCTCP: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Nick, pyArg_Channel, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanCTCP failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_Channel);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanCTCP was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnPrivAction(CNick& Nick, CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnPrivAction");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivAction: can't convert string 'OnPrivAction' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast<CNick*>(&Nick), SWIG_TypeQuery("CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivAction: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivAction: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Nick, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivAction failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivAction was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnChanAction(CNick& Nick, CChan& Channel, CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnChanAction");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanAction: can't convert string 'OnChanAction' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast<CNick*>(&Nick), SWIG_TypeQuery("CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanAction: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanAction: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanAction: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Nick, pyArg_Channel, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanAction failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_Channel);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanAction was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnPrivMsg(CNick& Nick, CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnPrivMsg");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivMsg: can't convert string 'OnPrivMsg' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast<CNick*>(&Nick), SWIG_TypeQuery("CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivMsg: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivMsg: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Nick, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivMsg failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivMsg was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnChanMsg(CNick& Nick, CChan& Channel, CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnChanMsg");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanMsg: can't convert string 'OnChanMsg' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast<CNick*>(&Nick), SWIG_TypeQuery("CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanMsg: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanMsg: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanMsg: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Nick, pyArg_Channel, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanMsg failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_Channel);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanMsg was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnPrivNotice(CNick& Nick, CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnPrivNotice");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivNotice: can't convert string 'OnPrivNotice' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast<CNick*>(&Nick), SWIG_TypeQuery("CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivNotice: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivNotice: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Nick, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivNotice failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnPrivNotice was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnChanNotice(CNick& Nick, CChan& Channel, CString& sMessage) {
	PyObject* pyName = Py_BuildValue("s", "OnChanNotice");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanNotice: can't convert string 'OnChanNotice' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast<CNick*>(&Nick), SWIG_TypeQuery("CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanNotice: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanNotice: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		return CONTINUE;
	}
	PyObject* pyArg_sMessage = CPyRetString::wrap(sMessage);
	if (!pyArg_sMessage) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanNotice: can't convert parameter 'sMessage' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Nick, pyArg_Channel, pyArg_sMessage, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanNotice failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_sMessage);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_Channel);
	Py_CLEAR(pyArg_sMessage);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnChanNotice was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnTopic(CNick& Nick, CChan& Channel, CString& sTopic) {
	PyObject* pyName = Py_BuildValue("s", "OnTopic");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnTopic: can't convert string 'OnTopic' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Nick = SWIG_NewInstanceObj(const_cast<CNick*>(&Nick), SWIG_TypeQuery("CNick*"), 0);
	if (!pyArg_Nick) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnTopic: can't convert parameter 'Nick' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnTopic: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		return CONTINUE;
	}
	PyObject* pyArg_sTopic = CPyRetString::wrap(sTopic);
	if (!pyArg_sTopic) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnTopic: can't convert parameter 'sTopic' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Nick, pyArg_Channel, pyArg_sTopic, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnTopic failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Nick);
		Py_CLEAR(pyArg_Channel);
		Py_CLEAR(pyArg_sTopic);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Nick);
	Py_CLEAR(pyArg_Channel);
	Py_CLEAR(pyArg_sTopic);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnTopic was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

bool CPyModule::OnServerCapAvailable(const CString& sCap) {
	PyObject* pyName = Py_BuildValue("s", "OnServerCapAvailable");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnServerCapAvailable: can't convert string 'OnServerCapAvailable' to PyObject: " << sPyErr);
		return false;
	}
	PyObject* pyArg_sCap = Py_BuildValue("s", sCap.c_str());
	if (!pyArg_sCap) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnServerCapAvailable: can't convert parameter 'sCap' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return false;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sCap, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnServerCapAvailable failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sCap);
		return false;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sCap);
	bool result;
	if (pyRes == Py_None) {
		result = false;
	} else {
		int x = PyObject_IsTrue(pyRes);
		if (-1 == x) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnServerCapAvailable was expected to return EModRet but: " << sPyErr);
			result = false;
		} else result = x ? true : false;
	}
	Py_CLEAR(pyRes);
	return result;
}

void CPyModule::OnServerCapResult(const CString& sCap, bool bSuccess) {
	PyObject* pyName = Py_BuildValue("s", "OnServerCapResult");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnServerCapResult: can't convert string 'OnServerCapResult' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_sCap = Py_BuildValue("s", sCap.c_str());
	if (!pyArg_sCap) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnServerCapResult: can't convert parameter 'sCap' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_bSuccess = Py_BuildValue("l", (long int)bSuccess);
	if (!pyArg_bSuccess) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnServerCapResult: can't convert parameter 'bSuccess' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sCap);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sCap, pyArg_bSuccess, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnServerCapResult failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sCap);
		Py_CLEAR(pyArg_bSuccess);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sCap);
	Py_CLEAR(pyArg_bSuccess);
	Py_CLEAR(pyRes);
}

CModule::EModRet CPyModule::OnTimerAutoJoin(CChan& Channel) {
	PyObject* pyName = Py_BuildValue("s", "OnTimerAutoJoin");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnTimerAutoJoin: can't convert string 'OnTimerAutoJoin' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Channel = SWIG_NewInstanceObj(const_cast<CChan*>(&Channel), SWIG_TypeQuery("CChan*"), 0);
	if (!pyArg_Channel) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnTimerAutoJoin: can't convert parameter 'Channel' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Channel, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnTimerAutoJoin failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Channel);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Channel);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnTimerAutoJoin was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

bool CPyModule::OnEmbeddedWebRequest(CWebSock& WebSock, const CString& sPageName, CTemplate& Tmpl) {
	PyObject* pyName = Py_BuildValue("s", "OnEmbeddedWebRequest");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnEmbeddedWebRequest: can't convert string 'OnEmbeddedWebRequest' to PyObject: " << sPyErr);
		return false;
	}
	PyObject* pyArg_WebSock = SWIG_NewInstanceObj(const_cast<CWebSock*>(&WebSock), SWIG_TypeQuery("CWebSock*"), 0);
	if (!pyArg_WebSock) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnEmbeddedWebRequest: can't convert parameter 'WebSock' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return false;
	}
	PyObject* pyArg_sPageName = Py_BuildValue("s", sPageName.c_str());
	if (!pyArg_sPageName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnEmbeddedWebRequest: can't convert parameter 'sPageName' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_WebSock);
		return false;
	}
	PyObject* pyArg_Tmpl = SWIG_NewInstanceObj(const_cast<CTemplate*>(&Tmpl), SWIG_TypeQuery("CTemplate*"), 0);
	if (!pyArg_Tmpl) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnEmbeddedWebRequest: can't convert parameter 'Tmpl' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_WebSock);
		Py_CLEAR(pyArg_sPageName);
		return false;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_WebSock, pyArg_sPageName, pyArg_Tmpl, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnEmbeddedWebRequest failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_WebSock);
		Py_CLEAR(pyArg_sPageName);
		Py_CLEAR(pyArg_Tmpl);
		return false;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_WebSock);
	Py_CLEAR(pyArg_sPageName);
	Py_CLEAR(pyArg_Tmpl);
	bool result;
	if (pyRes == Py_None) {
		result = false;
	} else {
		int x = PyObject_IsTrue(pyRes);
		if (-1 == x) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnEmbeddedWebRequest was expected to return EModRet but: " << sPyErr);
			result = false;
		} else result = x ? true : false;
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnAddNetwork(CIRCNetwork& Network, CString& sErrorRet) {
	PyObject* pyName = Py_BuildValue("s", "OnAddNetwork");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnAddNetwork: can't convert string 'OnAddNetwork' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Network = SWIG_NewInstanceObj(const_cast<CIRCNetwork*>(&Network), SWIG_TypeQuery("CIRCNetwork*"), 0);
	if (!pyArg_Network) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnAddNetwork: can't convert parameter 'Network' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sErrorRet = CPyRetString::wrap(sErrorRet);
	if (!pyArg_sErrorRet) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnAddNetwork: can't convert parameter 'sErrorRet' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Network);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Network, pyArg_sErrorRet, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnAddNetwork failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Network);
		Py_CLEAR(pyArg_sErrorRet);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Network);
	Py_CLEAR(pyArg_sErrorRet);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnAddNetwork was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnDeleteNetwork(CIRCNetwork& Network) {
	PyObject* pyName = Py_BuildValue("s", "OnDeleteNetwork");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDeleteNetwork: can't convert string 'OnDeleteNetwork' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Network = SWIG_NewInstanceObj(const_cast<CIRCNetwork*>(&Network), SWIG_TypeQuery("CIRCNetwork*"), 0);
	if (!pyArg_Network) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDeleteNetwork: can't convert parameter 'Network' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Network, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDeleteNetwork failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Network);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Network);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDeleteNetwork was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnAddUser(CUser& User, CString& sErrorRet) {
	PyObject* pyName = Py_BuildValue("s", "OnAddUser");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnAddUser: can't convert string 'OnAddUser' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_User = SWIG_NewInstanceObj(const_cast<CUser*>(&User), SWIG_TypeQuery("CUser*"), 0);
	if (!pyArg_User) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnAddUser: can't convert parameter 'User' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sErrorRet = CPyRetString::wrap(sErrorRet);
	if (!pyArg_sErrorRet) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnAddUser: can't convert parameter 'sErrorRet' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_User);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_User, pyArg_sErrorRet, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnAddUser failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_User);
		Py_CLEAR(pyArg_sErrorRet);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_User);
	Py_CLEAR(pyArg_sErrorRet);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnAddUser was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnDeleteUser(CUser& User) {
	PyObject* pyName = Py_BuildValue("s", "OnDeleteUser");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDeleteUser: can't convert string 'OnDeleteUser' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_User = SWIG_NewInstanceObj(const_cast<CUser*>(&User), SWIG_TypeQuery("CUser*"), 0);
	if (!pyArg_User) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDeleteUser: can't convert parameter 'User' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_User, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDeleteUser failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_User);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_User);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnDeleteUser was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

void CPyModule::OnClientConnect(CZNCSock* pSock, const CString& sHost, unsigned short uPort) {
	PyObject* pyName = Py_BuildValue("s", "OnClientConnect");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientConnect: can't convert string 'OnClientConnect' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_pSock = SWIG_NewInstanceObj(const_cast<CZNCSock*>(pSock), SWIG_TypeQuery("CZNCSock*"), 0);
	if (!pyArg_pSock) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientConnect: can't convert parameter 'pSock' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_sHost = Py_BuildValue("s", sHost.c_str());
	if (!pyArg_sHost) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientConnect: can't convert parameter 'sHost' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pSock);
		return ;
	}
	PyObject* pyArg_uPort = Py_BuildValue("H", uPort);
	if (!pyArg_uPort) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientConnect: can't convert parameter 'uPort' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pSock);
		Py_CLEAR(pyArg_sHost);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_pSock, pyArg_sHost, pyArg_uPort, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientConnect failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pSock);
		Py_CLEAR(pyArg_sHost);
		Py_CLEAR(pyArg_uPort);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_pSock);
	Py_CLEAR(pyArg_sHost);
	Py_CLEAR(pyArg_uPort);
	Py_CLEAR(pyRes);
}

void CPyModule::OnFailedLogin(const CString& sUsername, const CString& sRemoteIP) {
	PyObject* pyName = Py_BuildValue("s", "OnFailedLogin");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnFailedLogin: can't convert string 'OnFailedLogin' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_sUsername = Py_BuildValue("s", sUsername.c_str());
	if (!pyArg_sUsername) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnFailedLogin: can't convert parameter 'sUsername' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_sRemoteIP = Py_BuildValue("s", sRemoteIP.c_str());
	if (!pyArg_sRemoteIP) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnFailedLogin: can't convert parameter 'sRemoteIP' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sUsername);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sUsername, pyArg_sRemoteIP, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnFailedLogin failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sUsername);
		Py_CLEAR(pyArg_sRemoteIP);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sUsername);
	Py_CLEAR(pyArg_sRemoteIP);
	Py_CLEAR(pyRes);
}

CModule::EModRet CPyModule::OnUnknownUserRaw(CClient* pClient, CString& sLine) {
	PyObject* pyName = Py_BuildValue("s", "OnUnknownUserRaw");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUnknownUserRaw: can't convert string 'OnUnknownUserRaw' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_pClient = SWIG_NewInstanceObj(const_cast<CClient*>(pClient), SWIG_TypeQuery("CClient*"), 0);
	if (!pyArg_pClient) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUnknownUserRaw: can't convert parameter 'pClient' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sLine = CPyRetString::wrap(sLine);
	if (!pyArg_sLine) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUnknownUserRaw: can't convert parameter 'sLine' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pClient);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_pClient, pyArg_sLine, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUnknownUserRaw failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pClient);
		Py_CLEAR(pyArg_sLine);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_pClient);
	Py_CLEAR(pyArg_sLine);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnUnknownUserRaw was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

bool CPyModule::IsClientCapSupported(CClient* pClient, const CString& sCap, bool bState) {
	PyObject* pyName = Py_BuildValue("s", "IsClientCapSupported");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/IsClientCapSupported: can't convert string 'IsClientCapSupported' to PyObject: " << sPyErr);
		return false;
	}
	PyObject* pyArg_pClient = SWIG_NewInstanceObj(const_cast<CClient*>(pClient), SWIG_TypeQuery("CClient*"), 0);
	if (!pyArg_pClient) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/IsClientCapSupported: can't convert parameter 'pClient' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return false;
	}
	PyObject* pyArg_sCap = Py_BuildValue("s", sCap.c_str());
	if (!pyArg_sCap) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/IsClientCapSupported: can't convert parameter 'sCap' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pClient);
		return false;
	}
	PyObject* pyArg_bState = Py_BuildValue("l", (long int)bState);
	if (!pyArg_bState) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/IsClientCapSupported: can't convert parameter 'bState' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pClient);
		Py_CLEAR(pyArg_sCap);
		return false;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_pClient, pyArg_sCap, pyArg_bState, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/IsClientCapSupported failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pClient);
		Py_CLEAR(pyArg_sCap);
		Py_CLEAR(pyArg_bState);
		return false;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_pClient);
	Py_CLEAR(pyArg_sCap);
	Py_CLEAR(pyArg_bState);
	bool result;
	if (pyRes == Py_None) {
		result = false;
	} else {
		int x = PyObject_IsTrue(pyRes);
		if (-1 == x) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/IsClientCapSupported was expected to return EModRet but: " << sPyErr);
			result = false;
		} else result = x ? true : false;
	}
	Py_CLEAR(pyRes);
	return result;
}

void CPyModule::OnClientCapRequest(CClient* pClient, const CString& sCap, bool bState) {
	PyObject* pyName = Py_BuildValue("s", "OnClientCapRequest");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientCapRequest: can't convert string 'OnClientCapRequest' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_pClient = SWIG_NewInstanceObj(const_cast<CClient*>(pClient), SWIG_TypeQuery("CClient*"), 0);
	if (!pyArg_pClient) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientCapRequest: can't convert parameter 'pClient' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_sCap = Py_BuildValue("s", sCap.c_str());
	if (!pyArg_sCap) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientCapRequest: can't convert parameter 'sCap' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pClient);
		return ;
	}
	PyObject* pyArg_bState = Py_BuildValue("l", (long int)bState);
	if (!pyArg_bState) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientCapRequest: can't convert parameter 'bState' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pClient);
		Py_CLEAR(pyArg_sCap);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_pClient, pyArg_sCap, pyArg_bState, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientCapRequest failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pClient);
		Py_CLEAR(pyArg_sCap);
		Py_CLEAR(pyArg_bState);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_pClient);
	Py_CLEAR(pyArg_sCap);
	Py_CLEAR(pyArg_bState);
	Py_CLEAR(pyRes);
}

CModule::EModRet CPyModule::OnModuleLoading(const CString& sModName, const CString& sArgs, CModInfo::EModuleType eType, bool& bSuccess, CString& sRetMsg) {
	PyObject* pyName = Py_BuildValue("s", "OnModuleLoading");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModuleLoading: can't convert string 'OnModuleLoading' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_sModName = Py_BuildValue("s", sModName.c_str());
	if (!pyArg_sModName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModuleLoading: can't convert parameter 'sModName' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sArgs = Py_BuildValue("s", sArgs.c_str());
	if (!pyArg_sArgs) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModuleLoading: can't convert parameter 'sArgs' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sModName);
		return CONTINUE;
	}
	PyObject* pyArg_eType = Py_BuildValue("i", (int)eType);
	if (!pyArg_eType) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModuleLoading: can't convert parameter 'eType' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sModName);
		Py_CLEAR(pyArg_sArgs);
		return CONTINUE;
	}
	PyObject* pyArg_bSuccess = CPyRetBool::wrap(bSuccess);
	if (!pyArg_bSuccess) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModuleLoading: can't convert parameter 'bSuccess' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sModName);
		Py_CLEAR(pyArg_sArgs);
		Py_CLEAR(pyArg_eType);
		return CONTINUE;
	}
	PyObject* pyArg_sRetMsg = CPyRetString::wrap(sRetMsg);
	if (!pyArg_sRetMsg) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModuleLoading: can't convert parameter 'sRetMsg' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sModName);
		Py_CLEAR(pyArg_sArgs);
		Py_CLEAR(pyArg_eType);
		Py_CLEAR(pyArg_bSuccess);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_sModName, pyArg_sArgs, pyArg_eType, pyArg_bSuccess, pyArg_sRetMsg, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModuleLoading failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_sModName);
		Py_CLEAR(pyArg_sArgs);
		Py_CLEAR(pyArg_eType);
		Py_CLEAR(pyArg_bSuccess);
		Py_CLEAR(pyArg_sRetMsg);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_sModName);
	Py_CLEAR(pyArg_sArgs);
	Py_CLEAR(pyArg_eType);
	Py_CLEAR(pyArg_bSuccess);
	Py_CLEAR(pyArg_sRetMsg);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModuleLoading was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnModuleUnloading(CModule* pModule, bool& bSuccess, CString& sRetMsg) {
	PyObject* pyName = Py_BuildValue("s", "OnModuleUnloading");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModuleUnloading: can't convert string 'OnModuleUnloading' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_pModule = SWIG_NewInstanceObj(const_cast<CModule*>(pModule), SWIG_TypeQuery("CModule*"), 0);
	if (!pyArg_pModule) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModuleUnloading: can't convert parameter 'pModule' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_bSuccess = CPyRetBool::wrap(bSuccess);
	if (!pyArg_bSuccess) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModuleUnloading: can't convert parameter 'bSuccess' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pModule);
		return CONTINUE;
	}
	PyObject* pyArg_sRetMsg = CPyRetString::wrap(sRetMsg);
	if (!pyArg_sRetMsg) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModuleUnloading: can't convert parameter 'sRetMsg' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pModule);
		Py_CLEAR(pyArg_bSuccess);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_pModule, pyArg_bSuccess, pyArg_sRetMsg, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModuleUnloading failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pModule);
		Py_CLEAR(pyArg_bSuccess);
		Py_CLEAR(pyArg_sRetMsg);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_pModule);
	Py_CLEAR(pyArg_bSuccess);
	Py_CLEAR(pyArg_sRetMsg);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnModuleUnloading was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

CModule::EModRet CPyModule::OnGetModInfo(CModInfo& ModInfo, const CString& sModule, bool& bSuccess, CString& sRetMsg) {
	PyObject* pyName = Py_BuildValue("s", "OnGetModInfo");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnGetModInfo: can't convert string 'OnGetModInfo' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_ModInfo = SWIG_NewInstanceObj(const_cast<CModInfo*>(&ModInfo), SWIG_TypeQuery("CModInfo*"), 0);
	if (!pyArg_ModInfo) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnGetModInfo: can't convert parameter 'ModInfo' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyArg_sModule = Py_BuildValue("s", sModule.c_str());
	if (!pyArg_sModule) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnGetModInfo: can't convert parameter 'sModule' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_ModInfo);
		return CONTINUE;
	}
	PyObject* pyArg_bSuccess = CPyRetBool::wrap(bSuccess);
	if (!pyArg_bSuccess) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnGetModInfo: can't convert parameter 'bSuccess' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_ModInfo);
		Py_CLEAR(pyArg_sModule);
		return CONTINUE;
	}
	PyObject* pyArg_sRetMsg = CPyRetString::wrap(sRetMsg);
	if (!pyArg_sRetMsg) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnGetModInfo: can't convert parameter 'sRetMsg' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_ModInfo);
		Py_CLEAR(pyArg_sModule);
		Py_CLEAR(pyArg_bSuccess);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_ModInfo, pyArg_sModule, pyArg_bSuccess, pyArg_sRetMsg, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnGetModInfo failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_ModInfo);
		Py_CLEAR(pyArg_sModule);
		Py_CLEAR(pyArg_bSuccess);
		Py_CLEAR(pyArg_sRetMsg);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_ModInfo);
	Py_CLEAR(pyArg_sModule);
	Py_CLEAR(pyArg_bSuccess);
	Py_CLEAR(pyArg_sRetMsg);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnGetModInfo was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

void CPyModule::OnGetAvailableMods(std::set<CModInfo>& ssMods, CModInfo::EModuleType eType) {
	PyObject* pyName = Py_BuildValue("s", "OnGetAvailableMods");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnGetAvailableMods: can't convert string 'OnGetAvailableMods' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_ssMods = SWIG_NewInstanceObj(const_cast<std::set<CModInfo>*>(&ssMods), SWIG_TypeQuery("std::set<CModInfo>*"), 0);
	if (!pyArg_ssMods) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnGetAvailableMods: can't convert parameter 'ssMods' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_eType = Py_BuildValue("i", (int)eType);
	if (!pyArg_eType) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnGetAvailableMods: can't convert parameter 'eType' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_ssMods);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_ssMods, pyArg_eType, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnGetAvailableMods failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_ssMods);
		Py_CLEAR(pyArg_eType);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_ssMods);
	Py_CLEAR(pyArg_eType);
	Py_CLEAR(pyRes);
}

void CPyModule::OnClientCapLs(CClient* pClient, SCString& ssCaps) {
	PyObject* pyName = Py_BuildValue("s", "OnClientCapLs");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientCapLs: can't convert string 'OnClientCapLs' to PyObject: " << sPyErr);
		return ;
	}
	PyObject* pyArg_pClient = SWIG_NewInstanceObj(const_cast<CClient*>(pClient), SWIG_TypeQuery("CClient*"), 0);
	if (!pyArg_pClient) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientCapLs: can't convert parameter 'pClient' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return ;
	}
	PyObject* pyArg_ssCaps = SWIG_NewInstanceObj(const_cast<SCString*>(&ssCaps), SWIG_TypeQuery("SCString*"), 0);
	if (!pyArg_ssCaps) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientCapLs: can't convert parameter 'ssCaps' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pClient);
		return ;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_pClient, pyArg_ssCaps, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnClientCapLs failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_pClient);
		Py_CLEAR(pyArg_ssCaps);
		return ;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_pClient);
	Py_CLEAR(pyArg_ssCaps);
	Py_CLEAR(pyRes);
}

CModule::EModRet CPyModule::OnLoginAttempt(CSmartPtr<CAuthBase> Auth) {
	PyObject* pyName = Py_BuildValue("s", "OnLoginAttempt");
	if (!pyName) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnLoginAttempt: can't convert string 'OnLoginAttempt' to PyObject: " << sPyErr);
		return CONTINUE;
	}
	PyObject* pyArg_Auth = SWIG_NewInstanceObj(new CSmartPtr<CAuthBase>(Auth), SWIG_TypeQuery("CSmartPtr<CAuthBase>*"), SWIG_POINTER_OWN);
	if (!pyArg_Auth) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnLoginAttempt: can't convert parameter 'Auth' to PyObject: " << sPyErr);
		Py_CLEAR(pyName);
		return CONTINUE;
	}
	PyObject* pyRes = PyObject_CallMethodObjArgs(m_pyObj, pyName, pyArg_Auth, NULL);
	if (!pyRes) {
		CString sPyErr = m_pModPython->GetPyExceptionStr();
		DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnLoginAttempt failed: " << sPyErr);
		Py_CLEAR(pyName);
		Py_CLEAR(pyArg_Auth);
		return CONTINUE;
	}
	Py_CLEAR(pyName);
	Py_CLEAR(pyArg_Auth);
	CModule::EModRet result;
	if (pyRes == Py_None) {
		result = CONTINUE;
	} else {
		long int x = PyLong_AsLong(pyRes);
		if (PyErr_Occurred()) {
			CString sPyErr = m_pModPython->GetPyExceptionStr();
			DEBUG("modpython: " << (GetUser() ? GetUser()->GetUserName() : CString("<no user>")) << "/" << GetModName() << "/OnLoginAttempt was expected to return EModRet but: " << sPyErr);
			result = CONTINUE;
		} else { result = (CModule::EModRet)x; }
	}
	Py_CLEAR(pyRes);
	return result;
}

