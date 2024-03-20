//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (https://www.swig.org).
// Version 4.2.1
//
// Do not make changes to this file unless you know what you are doing - modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace Xnor.Core {

public class FileManager : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal FileManager(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(FileManager obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  internal static global::System.Runtime.InteropServices.HandleRef swigRelease(FileManager obj) {
    if (obj != null) {
      if (!obj.swigCMemOwn)
        throw new global::System.ApplicationException("Cannot release ownership as memory is not owned");
      global::System.Runtime.InteropServices.HandleRef ptr = obj.swigCPtr;
      obj.swigCMemOwn = false;
      obj.Dispose();
      return ptr;
    } else {
      return new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
    }
  }

  ~FileManager() {
    Dispose(false);
  }

  public void Dispose() {
    Dispose(true);
    global::System.GC.SuppressFinalize(this);
  }

  protected virtual void Dispose(bool disposing) {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          throw new global::System.MethodAccessException("C++ destructor does not have public access");
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
    }
  }

  public static SWIGTYPE_p_XnorCore__PointerT_XnorCore__File_t Add(SWIGTYPE_p_std__filesystem__path path) {
    SWIGTYPE_p_XnorCore__PointerT_XnorCore__File_t ret = new SWIGTYPE_p_XnorCore__PointerT_XnorCore__File_t(CorePINVOKE.FileManager_Add(SWIGTYPE_p_std__filesystem__path.getCPtr(path)), true);
    if (CorePINVOKE.SWIGPendingException.Pending) throw CorePINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static SWIGTYPE_p_XnorCore__PointerT_XnorCore__File_t Load(SWIGTYPE_p_std__filesystem__path path) {
    SWIGTYPE_p_XnorCore__PointerT_XnorCore__File_t ret = new SWIGTYPE_p_XnorCore__PointerT_XnorCore__File_t(CorePINVOKE.FileManager_Load(SWIGTYPE_p_std__filesystem__path.getCPtr(path)), true);
    if (CorePINVOKE.SWIGPendingException.Pending) throw CorePINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static SWIGTYPE_p_XnorCore__PointerT_XnorCore__Directory_t AddDirectory(SWIGTYPE_p_std__filesystem__path path) {
    SWIGTYPE_p_XnorCore__PointerT_XnorCore__Directory_t ret = new SWIGTYPE_p_XnorCore__PointerT_XnorCore__Directory_t(CorePINVOKE.FileManager_AddDirectory(SWIGTYPE_p_std__filesystem__path.getCPtr(path)), true);
    if (CorePINVOKE.SWIGPendingException.Pending) throw CorePINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static SWIGTYPE_p_XnorCore__PointerT_XnorCore__Directory_t LoadDirectory(SWIGTYPE_p_std__filesystem__path path) {
    SWIGTYPE_p_XnorCore__PointerT_XnorCore__Directory_t ret = new SWIGTYPE_p_XnorCore__PointerT_XnorCore__Directory_t(CorePINVOKE.FileManager_LoadDirectory(SWIGTYPE_p_std__filesystem__path.getCPtr(path)), true);
    if (CorePINVOKE.SWIGPendingException.Pending) throw CorePINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static bool Contains(SWIGTYPE_p_std__filesystem__path path) {
    bool ret = CorePINVOKE.FileManager_Contains(SWIGTYPE_p_std__filesystem__path.getCPtr(path));
    if (CorePINVOKE.SWIGPendingException.Pending) throw CorePINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static void Rename(SWIGTYPE_p_std__filesystem__path path, SWIGTYPE_p_std__filesystem__path newPath) {
    CorePINVOKE.FileManager_Rename__SWIG_0(SWIGTYPE_p_std__filesystem__path.getCPtr(path), SWIGTYPE_p_std__filesystem__path.getCPtr(newPath));
    if (CorePINVOKE.SWIGPendingException.Pending) throw CorePINVOKE.SWIGPendingException.Retrieve();
  }

  public static void Rename(SWIGTYPE_p_XnorCore__PointerT_XnorCore__Entry_t entry, SWIGTYPE_p_std__filesystem__path newPath) {
    CorePINVOKE.FileManager_Rename__SWIG_1(SWIGTYPE_p_XnorCore__PointerT_XnorCore__Entry_t.getCPtr(entry), SWIGTYPE_p_std__filesystem__path.getCPtr(newPath));
    if (CorePINVOKE.SWIGPendingException.Pending) throw CorePINVOKE.SWIGPendingException.Retrieve();
  }

  public static void Unload(SWIGTYPE_p_std__filesystem__path path) {
    CorePINVOKE.FileManager_Unload__SWIG_0(SWIGTYPE_p_std__filesystem__path.getCPtr(path));
    if (CorePINVOKE.SWIGPendingException.Pending) throw CorePINVOKE.SWIGPendingException.Retrieve();
  }

  public static void Unload(SWIGTYPE_p_XnorCore__PointerT_XnorCore__Entry_t entry) {
    CorePINVOKE.FileManager_Unload__SWIG_1(SWIGTYPE_p_XnorCore__PointerT_XnorCore__Entry_t.getCPtr(entry));
    if (CorePINVOKE.SWIGPendingException.Pending) throw CorePINVOKE.SWIGPendingException.Retrieve();
  }

  public static void UnloadAll() {
    CorePINVOKE.FileManager_UnloadAll();
  }

}

}