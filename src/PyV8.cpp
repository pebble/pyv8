// PyV8.cpp : Defines the entry point for the DLL application.
//
#include "Config.h"
#include "Engine.h"
#include "Debug.h"
#include "Locker.h"

#ifdef SUPPORT_AST
  #include "AST.h"
#endif

// So we can enable stuff that makes v8 support things we need.
namespace v8 {
  namespace internal {
    extern bool FLAG_harmony_proxies;
  }
}

class MallocArrayBufferAllocator : public v8::ArrayBuffer::Allocator {
public:
  virtual void* Allocate(size_t length) { void* foo = malloc(length); memset(foo, 0, length); return foo; }
  virtual void* AllocateUninitialized(size_t length) { return malloc(length); }
  virtual void Free(void* data, size_t length) { free(data); }
};

BOOST_PYTHON_MODULE(_PyV8)
{
  v8::internal::FLAG_harmony_proxies = true;
  V8::SetArrayBufferAllocator(new MallocArrayBufferAllocator());
  CJavascriptException::Expose();
  CWrapper::Expose(); 
  CContext::Expose();
#ifdef SUPPORT_AST
  CAstNode::Expose();
#endif
  CEngine::Expose();
  CDebug::Expose();  
  CLocker::Expose();
}
