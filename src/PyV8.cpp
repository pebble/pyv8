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
    extern bool FLAG_harmony_observation;
  }
}

BOOST_PYTHON_MODULE(_PyV8)
{
  v8::internal::FLAG_harmony_observation = true;
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
