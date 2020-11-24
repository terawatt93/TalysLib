// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME LevelsDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "Levels.hh"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_OpticalModelParameters(void *p = 0);
   static void *newArray_OpticalModelParameters(Long_t size, void *p);
   static void delete_OpticalModelParameters(void *p);
   static void deleteArray_OpticalModelParameters(void *p);
   static void destruct_OpticalModelParameters(void *p);
   static void streamer_OpticalModelParameters(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::OpticalModelParameters*)
   {
      ::OpticalModelParameters *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::OpticalModelParameters >(0);
      static ::ROOT::TGenericClassInfo 
         instance("OpticalModelParameters", ::OpticalModelParameters::Class_Version(), "Levels.hh", 49,
                  typeid(::OpticalModelParameters), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::OpticalModelParameters::Dictionary, isa_proxy, 16,
                  sizeof(::OpticalModelParameters) );
      instance.SetNew(&new_OpticalModelParameters);
      instance.SetNewArray(&newArray_OpticalModelParameters);
      instance.SetDelete(&delete_OpticalModelParameters);
      instance.SetDeleteArray(&deleteArray_OpticalModelParameters);
      instance.SetDestructor(&destruct_OpticalModelParameters);
      instance.SetStreamerFunc(&streamer_OpticalModelParameters);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::OpticalModelParameters*)
   {
      return GenerateInitInstanceLocal((::OpticalModelParameters*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::OpticalModelParameters*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SpinParity(void *p = 0);
   static void *newArray_SpinParity(Long_t size, void *p);
   static void delete_SpinParity(void *p);
   static void deleteArray_SpinParity(void *p);
   static void destruct_SpinParity(void *p);
   static void streamer_SpinParity(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SpinParity*)
   {
      ::SpinParity *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SpinParity >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SpinParity", ::SpinParity::Class_Version(), "Levels.hh", 94,
                  typeid(::SpinParity), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SpinParity::Dictionary, isa_proxy, 16,
                  sizeof(::SpinParity) );
      instance.SetNew(&new_SpinParity);
      instance.SetNewArray(&newArray_SpinParity);
      instance.SetDelete(&delete_SpinParity);
      instance.SetDeleteArray(&deleteArray_SpinParity);
      instance.SetDestructor(&destruct_SpinParity);
      instance.SetStreamerFunc(&streamer_SpinParity);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SpinParity*)
   {
      return GenerateInitInstanceLocal((::SpinParity*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::SpinParity*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_GammaTransitionData(void *p = 0);
   static void *newArray_GammaTransitionData(Long_t size, void *p);
   static void delete_GammaTransitionData(void *p);
   static void deleteArray_GammaTransitionData(void *p);
   static void destruct_GammaTransitionData(void *p);
   static void streamer_GammaTransitionData(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GammaTransitionData*)
   {
      ::GammaTransitionData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GammaTransitionData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GammaTransitionData", ::GammaTransitionData::Class_Version(), "Levels.hh", 112,
                  typeid(::GammaTransitionData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GammaTransitionData::Dictionary, isa_proxy, 16,
                  sizeof(::GammaTransitionData) );
      instance.SetNew(&new_GammaTransitionData);
      instance.SetNewArray(&newArray_GammaTransitionData);
      instance.SetDelete(&delete_GammaTransitionData);
      instance.SetDeleteArray(&deleteArray_GammaTransitionData);
      instance.SetDestructor(&destruct_GammaTransitionData);
      instance.SetStreamerFunc(&streamer_GammaTransitionData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GammaTransitionData*)
   {
      return GenerateInitInstanceLocal((::GammaTransitionData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GammaTransitionData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_GammaTransition(void *p = 0);
   static void *newArray_GammaTransition(Long_t size, void *p);
   static void delete_GammaTransition(void *p);
   static void deleteArray_GammaTransition(void *p);
   static void destruct_GammaTransition(void *p);
   static void streamer_GammaTransition(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GammaTransition*)
   {
      ::GammaTransition *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GammaTransition >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GammaTransition", ::GammaTransition::Class_Version(), "Levels.hh", 123,
                  typeid(::GammaTransition), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GammaTransition::Dictionary, isa_proxy, 16,
                  sizeof(::GammaTransition) );
      instance.SetNew(&new_GammaTransition);
      instance.SetNewArray(&newArray_GammaTransition);
      instance.SetDelete(&delete_GammaTransition);
      instance.SetDeleteArray(&deleteArray_GammaTransition);
      instance.SetDestructor(&destruct_GammaTransition);
      instance.SetStreamerFunc(&streamer_GammaTransition);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GammaTransition*)
   {
      return GenerateInitInstanceLocal((::GammaTransition*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GammaTransition*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LevelData(void *p = 0);
   static void *newArray_LevelData(Long_t size, void *p);
   static void delete_LevelData(void *p);
   static void deleteArray_LevelData(void *p);
   static void destruct_LevelData(void *p);
   static void streamer_LevelData(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LevelData*)
   {
      ::LevelData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LevelData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LevelData", ::LevelData::Class_Version(), "Levels.hh", 156,
                  typeid(::LevelData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LevelData::Dictionary, isa_proxy, 16,
                  sizeof(::LevelData) );
      instance.SetNew(&new_LevelData);
      instance.SetNewArray(&newArray_LevelData);
      instance.SetDelete(&delete_LevelData);
      instance.SetDeleteArray(&deleteArray_LevelData);
      instance.SetDestructor(&destruct_LevelData);
      instance.SetStreamerFunc(&streamer_LevelData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LevelData*)
   {
      return GenerateInitInstanceLocal((::LevelData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::LevelData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LevelDeformation(void *p = 0);
   static void *newArray_LevelDeformation(Long_t size, void *p);
   static void delete_LevelDeformation(void *p);
   static void deleteArray_LevelDeformation(void *p);
   static void destruct_LevelDeformation(void *p);
   static void streamer_LevelDeformation(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LevelDeformation*)
   {
      ::LevelDeformation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LevelDeformation >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LevelDeformation", ::LevelDeformation::Class_Version(), "Levels.hh", 170,
                  typeid(::LevelDeformation), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LevelDeformation::Dictionary, isa_proxy, 16,
                  sizeof(::LevelDeformation) );
      instance.SetNew(&new_LevelDeformation);
      instance.SetNewArray(&newArray_LevelDeformation);
      instance.SetDelete(&delete_LevelDeformation);
      instance.SetDeleteArray(&deleteArray_LevelDeformation);
      instance.SetDestructor(&destruct_LevelDeformation);
      instance.SetStreamerFunc(&streamer_LevelDeformation);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LevelDeformation*)
   {
      return GenerateInitInstanceLocal((::LevelDeformation*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::LevelDeformation*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Deformation(void *p = 0);
   static void *newArray_Deformation(Long_t size, void *p);
   static void delete_Deformation(void *p);
   static void deleteArray_Deformation(void *p);
   static void destruct_Deformation(void *p);
   static void streamer_Deformation(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Deformation*)
   {
      ::Deformation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Deformation >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Deformation", ::Deformation::Class_Version(), "Levels.hh", 184,
                  typeid(::Deformation), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Deformation::Dictionary, isa_proxy, 16,
                  sizeof(::Deformation) );
      instance.SetNew(&new_Deformation);
      instance.SetNewArray(&newArray_Deformation);
      instance.SetDelete(&delete_Deformation);
      instance.SetDeleteArray(&deleteArray_Deformation);
      instance.SetDestructor(&destruct_Deformation);
      instance.SetStreamerFunc(&streamer_Deformation);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Deformation*)
   {
      return GenerateInitInstanceLocal((::Deformation*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Deformation*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Level(void *p = 0);
   static void *newArray_Level(Long_t size, void *p);
   static void delete_Level(void *p);
   static void deleteArray_Level(void *p);
   static void destruct_Level(void *p);
   static void streamer_Level(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Level*)
   {
      ::Level *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Level >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Level", ::Level::Class_Version(), "Levels.hh", 203,
                  typeid(::Level), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Level::Dictionary, isa_proxy, 16,
                  sizeof(::Level) );
      instance.SetNew(&new_Level);
      instance.SetNewArray(&newArray_Level);
      instance.SetDelete(&delete_Level);
      instance.SetDeleteArray(&deleteArray_Level);
      instance.SetDestructor(&destruct_Level);
      instance.SetStreamerFunc(&streamer_Level);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Level*)
   {
      return GenerateInitInstanceLocal((::Level*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Level*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_NucleusData(void *p = 0);
   static void *newArray_NucleusData(Long_t size, void *p);
   static void delete_NucleusData(void *p);
   static void deleteArray_NucleusData(void *p);
   static void destruct_NucleusData(void *p);
   static void streamer_NucleusData(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::NucleusData*)
   {
      ::NucleusData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::NucleusData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("NucleusData", ::NucleusData::Class_Version(), "Levels.hh", 248,
                  typeid(::NucleusData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::NucleusData::Dictionary, isa_proxy, 16,
                  sizeof(::NucleusData) );
      instance.SetNew(&new_NucleusData);
      instance.SetNewArray(&newArray_NucleusData);
      instance.SetDelete(&delete_NucleusData);
      instance.SetDeleteArray(&deleteArray_NucleusData);
      instance.SetDestructor(&destruct_NucleusData);
      instance.SetStreamerFunc(&streamer_NucleusData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::NucleusData*)
   {
      return GenerateInitInstanceLocal((::NucleusData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::NucleusData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Nucleus(void *p = 0);
   static void *newArray_Nucleus(Long_t size, void *p);
   static void delete_Nucleus(void *p);
   static void deleteArray_Nucleus(void *p);
   static void destruct_Nucleus(void *p);
   static void streamer_Nucleus(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Nucleus*)
   {
      ::Nucleus *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Nucleus >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Nucleus", ::Nucleus::Class_Version(), "Levels.hh", 267,
                  typeid(::Nucleus), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Nucleus::Dictionary, isa_proxy, 16,
                  sizeof(::Nucleus) );
      instance.SetNew(&new_Nucleus);
      instance.SetNewArray(&newArray_Nucleus);
      instance.SetDelete(&delete_Nucleus);
      instance.SetDeleteArray(&deleteArray_Nucleus);
      instance.SetDestructor(&destruct_Nucleus);
      instance.SetStreamerFunc(&streamer_Nucleus);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Nucleus*)
   {
      return GenerateInitInstanceLocal((::Nucleus*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Nucleus*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TalysCalculation(void *p = 0);
   static void *newArray_TalysCalculation(Long_t size, void *p);
   static void delete_TalysCalculation(void *p);
   static void deleteArray_TalysCalculation(void *p);
   static void destruct_TalysCalculation(void *p);
   static void streamer_TalysCalculation(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TalysCalculation*)
   {
      ::TalysCalculation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TalysCalculation >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TalysCalculation", ::TalysCalculation::Class_Version(), "Levels.hh", 335,
                  typeid(::TalysCalculation), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TalysCalculation::Dictionary, isa_proxy, 16,
                  sizeof(::TalysCalculation) );
      instance.SetNew(&new_TalysCalculation);
      instance.SetNewArray(&newArray_TalysCalculation);
      instance.SetDelete(&delete_TalysCalculation);
      instance.SetDeleteArray(&deleteArray_TalysCalculation);
      instance.SetDestructor(&destruct_TalysCalculation);
      instance.SetStreamerFunc(&streamer_TalysCalculation);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TalysCalculation*)
   {
      return GenerateInitInstanceLocal((::TalysCalculation*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TalysCalculation*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SampleInformation(void *p = 0);
   static void *newArray_SampleInformation(Long_t size, void *p);
   static void delete_SampleInformation(void *p);
   static void deleteArray_SampleInformation(void *p);
   static void destruct_SampleInformation(void *p);
   static void streamer_SampleInformation(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SampleInformation*)
   {
      ::SampleInformation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SampleInformation >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SampleInformation", ::SampleInformation::Class_Version(), "Levels.hh", 362,
                  typeid(::SampleInformation), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SampleInformation::Dictionary, isa_proxy, 16,
                  sizeof(::SampleInformation) );
      instance.SetNew(&new_SampleInformation);
      instance.SetNewArray(&newArray_SampleInformation);
      instance.SetDelete(&delete_SampleInformation);
      instance.SetDeleteArray(&deleteArray_SampleInformation);
      instance.SetDestructor(&destruct_SampleInformation);
      instance.SetStreamerFunc(&streamer_SampleInformation);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SampleInformation*)
   {
      return GenerateInitInstanceLocal((::SampleInformation*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::SampleInformation*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr OpticalModelParameters::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *OpticalModelParameters::Class_Name()
{
   return "OpticalModelParameters";
}

//______________________________________________________________________________
const char *OpticalModelParameters::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OpticalModelParameters*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int OpticalModelParameters::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OpticalModelParameters*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *OpticalModelParameters::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OpticalModelParameters*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *OpticalModelParameters::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OpticalModelParameters*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SpinParity::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SpinParity::Class_Name()
{
   return "SpinParity";
}

//______________________________________________________________________________
const char *SpinParity::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SpinParity*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SpinParity::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SpinParity*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SpinParity::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SpinParity*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SpinParity::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SpinParity*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr GammaTransitionData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *GammaTransitionData::Class_Name()
{
   return "GammaTransitionData";
}

//______________________________________________________________________________
const char *GammaTransitionData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GammaTransitionData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GammaTransitionData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GammaTransitionData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GammaTransitionData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GammaTransitionData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GammaTransitionData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GammaTransitionData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr GammaTransition::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *GammaTransition::Class_Name()
{
   return "GammaTransition";
}

//______________________________________________________________________________
const char *GammaTransition::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GammaTransition*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GammaTransition::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GammaTransition*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GammaTransition::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GammaTransition*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GammaTransition::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GammaTransition*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LevelData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LevelData::Class_Name()
{
   return "LevelData";
}

//______________________________________________________________________________
const char *LevelData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LevelData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LevelData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LevelData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LevelData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LevelData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LevelData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LevelData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LevelDeformation::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LevelDeformation::Class_Name()
{
   return "LevelDeformation";
}

//______________________________________________________________________________
const char *LevelDeformation::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LevelDeformation*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LevelDeformation::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LevelDeformation*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LevelDeformation::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LevelDeformation*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LevelDeformation::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LevelDeformation*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Deformation::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Deformation::Class_Name()
{
   return "Deformation";
}

//______________________________________________________________________________
const char *Deformation::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Deformation*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Deformation::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Deformation*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Deformation::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Deformation*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Deformation::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Deformation*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Level::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Level::Class_Name()
{
   return "Level";
}

//______________________________________________________________________________
const char *Level::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Level*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Level::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Level*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Level::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Level*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Level::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Level*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr NucleusData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *NucleusData::Class_Name()
{
   return "NucleusData";
}

//______________________________________________________________________________
const char *NucleusData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::NucleusData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int NucleusData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::NucleusData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *NucleusData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::NucleusData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *NucleusData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::NucleusData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Nucleus::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Nucleus::Class_Name()
{
   return "Nucleus";
}

//______________________________________________________________________________
const char *Nucleus::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Nucleus*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Nucleus::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Nucleus*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Nucleus::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Nucleus*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Nucleus::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Nucleus*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TalysCalculation::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TalysCalculation::Class_Name()
{
   return "TalysCalculation";
}

//______________________________________________________________________________
const char *TalysCalculation::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TalysCalculation*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TalysCalculation::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TalysCalculation*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TalysCalculation::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TalysCalculation*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TalysCalculation::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TalysCalculation*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SampleInformation::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SampleInformation::Class_Name()
{
   return "SampleInformation";
}

//______________________________________________________________________________
const char *SampleInformation::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SampleInformation*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SampleInformation::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SampleInformation*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SampleInformation::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SampleInformation*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SampleInformation::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SampleInformation*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void OpticalModelParameters::Streamer(TBuffer &R__b)
{
   // Stream an object of class OpticalModelParameters.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> Vv;
      R__b >> Wv;
      R__b >> Rv;
      R__b >> Av;
      R__b >> Wd;
      R__b >> Rd;
      R__b >> Ad;
      R__b >> Vso;
      R__b >> Wso;
      R__b >> Rso;
      R__b >> Aso;
      R__b >> Rc;
      R__b >> v1;
      R__b >> v2;
      R__b >> v3;
      R__b >> v4;
      R__b >> w1;
      R__b >> w2;
      R__b >> d1;
      R__b >> d2;
      R__b >> d3;
      R__b >> vso1;
      R__b >> vso2;
      R__b >> wso1;
      R__b >> wso2;
      R__b >> A;
      R__b >> N;
      R__b >> Z;
      R__b >> ProjectileEnergy;
      R__b >> Ef;
      R__b >> Vc;
      R__b >> NormalisationMode;
      R__b >> Read;
      R__b >> JLM_flag;
      R__b >> goriely;
      R__b >> hilaire;
      R__b >> Koning;
      { TString R__str; R__str.Streamer(R__b); Projectile = R__str.Data(); }
      R__b >> Nuclide;
      R__b.CheckByteCount(R__s, R__c, OpticalModelParameters::IsA());
   } else {
      R__c = R__b.WriteVersion(OpticalModelParameters::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << Vv;
      R__b << Wv;
      R__b << Rv;
      R__b << Av;
      R__b << Wd;
      R__b << Rd;
      R__b << Ad;
      R__b << Vso;
      R__b << Wso;
      R__b << Rso;
      R__b << Aso;
      R__b << Rc;
      R__b << v1;
      R__b << v2;
      R__b << v3;
      R__b << v4;
      R__b << w1;
      R__b << w2;
      R__b << d1;
      R__b << d2;
      R__b << d3;
      R__b << vso1;
      R__b << vso2;
      R__b << wso1;
      R__b << wso2;
      R__b << A;
      R__b << N;
      R__b << Z;
      R__b << ProjectileEnergy;
      R__b << Ef;
      R__b << Vc;
      R__b << NormalisationMode;
      R__b << Read;
      R__b << JLM_flag;
      R__b << goriely;
      R__b << hilaire;
      R__b << Koning;
      { TString R__str = Projectile.c_str(); R__str.Streamer(R__b);}
      R__b << Nuclide;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_OpticalModelParameters(void *p) {
      return  p ? new(p) ::OpticalModelParameters : new ::OpticalModelParameters;
   }
   static void *newArray_OpticalModelParameters(Long_t nElements, void *p) {
      return p ? new(p) ::OpticalModelParameters[nElements] : new ::OpticalModelParameters[nElements];
   }
   // Wrapper around operator delete
   static void delete_OpticalModelParameters(void *p) {
      delete ((::OpticalModelParameters*)p);
   }
   static void deleteArray_OpticalModelParameters(void *p) {
      delete [] ((::OpticalModelParameters*)p);
   }
   static void destruct_OpticalModelParameters(void *p) {
      typedef ::OpticalModelParameters current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_OpticalModelParameters(TBuffer &buf, void *obj) {
      ((::OpticalModelParameters*)obj)->::OpticalModelParameters::Streamer(buf);
   }
} // end of namespace ROOT for class ::OpticalModelParameters

//______________________________________________________________________________
void SpinParity::Streamer(TBuffer &R__b)
{
   // Stream an object of class SpinParity.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> J;
      R__b >> Parity;
      R__b.CheckByteCount(R__s, R__c, SpinParity::IsA());
   } else {
      R__c = R__b.WriteVersion(SpinParity::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << J;
      R__b << Parity;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SpinParity(void *p) {
      return  p ? new(p) ::SpinParity : new ::SpinParity;
   }
   static void *newArray_SpinParity(Long_t nElements, void *p) {
      return p ? new(p) ::SpinParity[nElements] : new ::SpinParity[nElements];
   }
   // Wrapper around operator delete
   static void delete_SpinParity(void *p) {
      delete ((::SpinParity*)p);
   }
   static void deleteArray_SpinParity(void *p) {
      delete [] ((::SpinParity*)p);
   }
   static void destruct_SpinParity(void *p) {
      typedef ::SpinParity current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_SpinParity(TBuffer &buf, void *obj) {
      ((::SpinParity*)obj)->::SpinParity::Streamer(buf);
   }
} // end of namespace ROOT for class ::SpinParity

//______________________________________________________________________________
void GammaTransitionData::Streamer(TBuffer &R__b)
{
   // Stream an object of class GammaTransitionData.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> Energy;
      R__b >> EnergyErr;
      R__b >> Intensity;
      R__b >> CrossSection;
      R__b >> E_in;
      R__b >> Tolerancy;
      R__b >> Rel_Cs;
      R__b >> TalysCrossSection;
      R__b >> TalysE_i;
      R__b >> TalysE_f;
      TalysJP_i.Streamer(R__b);
      TalysJP_f.Streamer(R__b);
      {
         vector<SpinParity> &R__stl =  TalysMultipolarity;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            SpinParity R__t;
            R__t.Streamer(R__b);
            R__stl.push_back(R__t);
         }
      }
      { TString R__str; R__str.Streamer(R__b); Multipolarity = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); nuclide = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); reaction = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); Origin = R__str.Data(); }
      R__b.CheckByteCount(R__s, R__c, GammaTransitionData::IsA());
   } else {
      R__c = R__b.WriteVersion(GammaTransitionData::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << Energy;
      R__b << EnergyErr;
      R__b << Intensity;
      R__b << CrossSection;
      R__b << E_in;
      R__b << Tolerancy;
      R__b << Rel_Cs;
      R__b << TalysCrossSection;
      R__b << TalysE_i;
      R__b << TalysE_f;
      TalysJP_i.Streamer(R__b);
      TalysJP_f.Streamer(R__b);
      {
         vector<SpinParity> &R__stl =  TalysMultipolarity;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<SpinParity>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            ((SpinParity&)(*R__k)).Streamer(R__b);
            }
         }
      }
      { TString R__str = Multipolarity.c_str(); R__str.Streamer(R__b);}
      { TString R__str = nuclide.c_str(); R__str.Streamer(R__b);}
      { TString R__str = reaction.c_str(); R__str.Streamer(R__b);}
      { TString R__str = Origin.c_str(); R__str.Streamer(R__b);}
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GammaTransitionData(void *p) {
      return  p ? new(p) ::GammaTransitionData : new ::GammaTransitionData;
   }
   static void *newArray_GammaTransitionData(Long_t nElements, void *p) {
      return p ? new(p) ::GammaTransitionData[nElements] : new ::GammaTransitionData[nElements];
   }
   // Wrapper around operator delete
   static void delete_GammaTransitionData(void *p) {
      delete ((::GammaTransitionData*)p);
   }
   static void deleteArray_GammaTransitionData(void *p) {
      delete [] ((::GammaTransitionData*)p);
   }
   static void destruct_GammaTransitionData(void *p) {
      typedef ::GammaTransitionData current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_GammaTransitionData(TBuffer &buf, void *obj) {
      ((::GammaTransitionData*)obj)->::GammaTransitionData::Streamer(buf);
   }
} // end of namespace ROOT for class ::GammaTransitionData

//______________________________________________________________________________
void GammaTransition::Streamer(TBuffer &R__b)
{
   // Stream an object of class GammaTransition.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      GammaTransitionData::Streamer(R__b);
      CSGraph.Streamer(R__b);
      R__b >> InitLevelNumber;
      R__b >> FinalLevelNumber;
      R__b >> fLevel;
      R__b >> fFinalLevel;
      R__b.CheckByteCount(R__s, R__c, GammaTransition::IsA());
   } else {
      R__c = R__b.WriteVersion(GammaTransition::IsA(), kTRUE);
      GammaTransitionData::Streamer(R__b);
      CSGraph.Streamer(R__b);
      R__b << InitLevelNumber;
      R__b << FinalLevelNumber;
      R__b << fLevel;
      R__b << fFinalLevel;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GammaTransition(void *p) {
      return  p ? new(p) ::GammaTransition : new ::GammaTransition;
   }
   static void *newArray_GammaTransition(Long_t nElements, void *p) {
      return p ? new(p) ::GammaTransition[nElements] : new ::GammaTransition[nElements];
   }
   // Wrapper around operator delete
   static void delete_GammaTransition(void *p) {
      delete ((::GammaTransition*)p);
   }
   static void deleteArray_GammaTransition(void *p) {
      delete [] ((::GammaTransition*)p);
   }
   static void destruct_GammaTransition(void *p) {
      typedef ::GammaTransition current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_GammaTransition(TBuffer &buf, void *obj) {
      ((::GammaTransition*)obj)->::GammaTransition::Streamer(buf);
   }
} // end of namespace ROOT for class ::GammaTransition

//______________________________________________________________________________
void LevelData::Streamer(TBuffer &R__b)
{
   // Stream an object of class LevelData.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      { TString R__str; R__str.Streamer(R__b); Nuclide = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); HalfLife = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); HalfLifeErr = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); JP = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); Origin = R__str.Data(); }
      {
         vector<SpinParity> &R__stl =  JP_values;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            SpinParity R__t;
            R__t.Streamer(R__b);
            R__stl.push_back(R__t);
         }
      }
      {
         vector<GammaTransitionData> &R__stl =  GammasData;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            GammaTransitionData R__t;
            R__t.Streamer(R__b);
            R__stl.push_back(R__t);
         }
      }
      R__b >> Mark;
      R__b >> Energy;
      R__b >> EnergyErr;
      R__b >> TalysCS;
      R__b >> TalysCSCompound;
      R__b >> TalysCSDirect;
      R__b >> OutgoingParticleEnergy;
      TalysJP.Streamer(R__b);
      {
         vector<float> &R__stl =  ADTot;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            float R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      {
         vector<float> &R__stl =  ADDirect;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            float R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      {
         vector<float> &R__stl =  ADCompound;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            float R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      {
         vector<float> &R__stl =  Angle;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            float R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      {
         vector<float> &R__stl =  Branching;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            float R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      {
         vector<unsigned int> &R__stl =  NumbersOfFinalLevels;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            unsigned int R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      R__b.CheckByteCount(R__s, R__c, LevelData::IsA());
   } else {
      R__c = R__b.WriteVersion(LevelData::IsA(), kTRUE);
      TObject::Streamer(R__b);
      { TString R__str = Nuclide.c_str(); R__str.Streamer(R__b);}
      { TString R__str = HalfLife.c_str(); R__str.Streamer(R__b);}
      { TString R__str = HalfLifeErr.c_str(); R__str.Streamer(R__b);}
      { TString R__str = JP.c_str(); R__str.Streamer(R__b);}
      { TString R__str = Origin.c_str(); R__str.Streamer(R__b);}
      {
         vector<SpinParity> &R__stl =  JP_values;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<SpinParity>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            ((SpinParity&)(*R__k)).Streamer(R__b);
            }
         }
      }
      {
         vector<GammaTransitionData> &R__stl =  GammasData;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<GammaTransitionData>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            ((GammaTransitionData&)(*R__k)).Streamer(R__b);
            }
         }
      }
      R__b << Mark;
      R__b << Energy;
      R__b << EnergyErr;
      R__b << TalysCS;
      R__b << TalysCSCompound;
      R__b << TalysCSDirect;
      R__b << OutgoingParticleEnergy;
      TalysJP.Streamer(R__b);
      {
         vector<float> &R__stl =  ADTot;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<float>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      {
         vector<float> &R__stl =  ADDirect;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<float>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      {
         vector<float> &R__stl =  ADCompound;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<float>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      {
         vector<float> &R__stl =  Angle;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<float>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      {
         vector<float> &R__stl =  Branching;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<float>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      {
         vector<unsigned int> &R__stl =  NumbersOfFinalLevels;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<unsigned int>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LevelData(void *p) {
      return  p ? new(p) ::LevelData : new ::LevelData;
   }
   static void *newArray_LevelData(Long_t nElements, void *p) {
      return p ? new(p) ::LevelData[nElements] : new ::LevelData[nElements];
   }
   // Wrapper around operator delete
   static void delete_LevelData(void *p) {
      delete ((::LevelData*)p);
   }
   static void deleteArray_LevelData(void *p) {
      delete [] ((::LevelData*)p);
   }
   static void destruct_LevelData(void *p) {
      typedef ::LevelData current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_LevelData(TBuffer &buf, void *obj) {
      ((::LevelData*)obj)->::LevelData::Streamer(buf);
   }
} // end of namespace ROOT for class ::LevelData

//______________________________________________________________________________
void LevelDeformation::Streamer(TBuffer &R__b)
{
   // Stream an object of class LevelDeformation.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> TypeOfLevel;
      R__b >> TypeOfDeformation;
      R__b >> NumberOfBand;
      R__b >> NumberOfLevel;
      R__b >> LOfBand;
      R__b >> NumberOfPhonons;
      R__b >> MagneticNumber;
      {
         vector<float> &R__stl =  Beta;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            float R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      R__b >> fLevel;
      R__b >> fDeformation;
      R__b.CheckByteCount(R__s, R__c, LevelDeformation::IsA());
   } else {
      R__c = R__b.WriteVersion(LevelDeformation::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << TypeOfLevel;
      R__b << TypeOfDeformation;
      R__b << NumberOfBand;
      R__b << NumberOfLevel;
      R__b << LOfBand;
      R__b << NumberOfPhonons;
      R__b << MagneticNumber;
      {
         vector<float> &R__stl =  Beta;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<float>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      R__b << fLevel;
      R__b << fDeformation;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LevelDeformation(void *p) {
      return  p ? new(p) ::LevelDeformation : new ::LevelDeformation;
   }
   static void *newArray_LevelDeformation(Long_t nElements, void *p) {
      return p ? new(p) ::LevelDeformation[nElements] : new ::LevelDeformation[nElements];
   }
   // Wrapper around operator delete
   static void delete_LevelDeformation(void *p) {
      delete ((::LevelDeformation*)p);
   }
   static void deleteArray_LevelDeformation(void *p) {
      delete [] ((::LevelDeformation*)p);
   }
   static void destruct_LevelDeformation(void *p) {
      typedef ::LevelDeformation current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_LevelDeformation(TBuffer &buf, void *obj) {
      ((::LevelDeformation*)obj)->::LevelDeformation::Streamer(buf);
   }
} // end of namespace ROOT for class ::LevelDeformation

//______________________________________________________________________________
void Deformation::Streamer(TBuffer &R__b)
{
   // Stream an object of class Deformation.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> A;
      R__b >> Z;
      R__b >> NLevels;
      R__b >> TypeOfCollectivity;
      R__b >> TypeOfDeformation;
      {
         vector<LevelDeformation> &R__stl =  LevelDeformations;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            LevelDeformation R__t;
            R__t.Streamer(R__b);
            R__stl.push_back(R__t);
         }
      }
      {
         vector<string> &R__stl =  ContentOfFile;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            string R__t;
            {TString R__str;
             R__str.Streamer(R__b);
             R__t = R__str.Data();}
            R__stl.push_back(R__t);
         }
      }
      R__b >> PointToPastChangedDeformation;
      R__b.CheckByteCount(R__s, R__c, Deformation::IsA());
   } else {
      R__c = R__b.WriteVersion(Deformation::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << A;
      R__b << Z;
      R__b << NLevels;
      R__b << TypeOfCollectivity;
      R__b << TypeOfDeformation;
      {
         vector<LevelDeformation> &R__stl =  LevelDeformations;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<LevelDeformation>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            ((LevelDeformation&)(*R__k)).Streamer(R__b);
            }
         }
      }
      {
         vector<string> &R__stl =  ContentOfFile;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<string>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            {TString R__str((*R__k).c_str());
             R__str.Streamer(R__b);};
            }
         }
      }
      R__b << PointToPastChangedDeformation;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Deformation(void *p) {
      return  p ? new(p) ::Deformation : new ::Deformation;
   }
   static void *newArray_Deformation(Long_t nElements, void *p) {
      return p ? new(p) ::Deformation[nElements] : new ::Deformation[nElements];
   }
   // Wrapper around operator delete
   static void delete_Deformation(void *p) {
      delete ((::Deformation*)p);
   }
   static void deleteArray_Deformation(void *p) {
      delete [] ((::Deformation*)p);
   }
   static void destruct_Deformation(void *p) {
      typedef ::Deformation current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Deformation(TBuffer &buf, void *obj) {
      ((::Deformation*)obj)->::Deformation::Streamer(buf);
   }
} // end of namespace ROOT for class ::Deformation

//______________________________________________________________________________
void Level::Streamer(TBuffer &R__b)
{
   // Stream an object of class Level.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      LevelData::Streamer(R__b);
      {
         vector<Level*> &R__stl =  SimilarLevels;
         R__stl.clear();
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class Level *));
         if (R__tcl1==0) {
            Error("SimilarLevels streamer","Missing the TClass object for class Level *!");
            return;
         }
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            Level* R__t;
            R__t = (Level*)R__b.ReadObjectAny(R__tcl1);
            R__stl.push_back(R__t);
         }
      }
      R__b >> deformation;
      R__b >> PlottedADist;
      AdistTotalTalys.Streamer(R__b);
      AdistCompoundTalys.Streamer(R__b);
      AdistDirectTalys.Streamer(R__b);
      CSGraph.Streamer(R__b);
      CSCompoundGraph.Streamer(R__b);
      CSDirectGraph.Streamer(R__b);
      R__b >> Number;
      {
         vector<GammaTransition> &R__stl =  Gammas;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            GammaTransition R__t;
            R__t.Streamer(R__b);
            R__stl.push_back(R__t);
         }
      }
      R__b >> fNucleus;
      R__b.CheckByteCount(R__s, R__c, Level::IsA());
   } else {
      R__c = R__b.WriteVersion(Level::IsA(), kTRUE);
      LevelData::Streamer(R__b);
      {
         vector<Level*> &R__stl =  SimilarLevels;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<Level*>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      R__b << deformation;
      R__b << PlottedADist;
      AdistTotalTalys.Streamer(R__b);
      AdistCompoundTalys.Streamer(R__b);
      AdistDirectTalys.Streamer(R__b);
      CSGraph.Streamer(R__b);
      CSCompoundGraph.Streamer(R__b);
      CSDirectGraph.Streamer(R__b);
      R__b << Number;
      {
         vector<GammaTransition> &R__stl =  Gammas;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<GammaTransition>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            ((GammaTransition&)(*R__k)).Streamer(R__b);
            }
         }
      }
      R__b << fNucleus;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Level(void *p) {
      return  p ? new(p) ::Level : new ::Level;
   }
   static void *newArray_Level(Long_t nElements, void *p) {
      return p ? new(p) ::Level[nElements] : new ::Level[nElements];
   }
   // Wrapper around operator delete
   static void delete_Level(void *p) {
      delete ((::Level*)p);
   }
   static void deleteArray_Level(void *p) {
      delete [] ((::Level*)p);
   }
   static void destruct_Level(void *p) {
      typedef ::Level current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Level(TBuffer &buf, void *obj) {
      ((::Level*)obj)->::Level::Streamer(buf);
   }
} // end of namespace ROOT for class ::Level

//______________________________________________________________________________
void NucleusData::Streamer(TBuffer &R__b)
{
   // Stream an object of class NucleusData.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      { TString R__str; R__str.Streamer(R__b); Name = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); Reaction = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); Projectile = R__str.Data(); }
      R__b >> A;
      R__b >> Z;
      {
         vector<LevelData> &R__stl =  LevelsData;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            LevelData R__t;
            R__t.Streamer(R__b);
            R__stl.push_back(R__t);
         }
      }
      {
         vector<NucleusData> &R__stl =  ProductsData;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            NucleusData R__t;
            R__t.Streamer(R__b);
            R__stl.push_back(R__t);
         }
      }
      R__b >> TalysCalculated;
      R__b >> Abundance;
      R__b >> ProjectileEnergy;
      {
         vector<float> &R__stl =  Angle;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            float R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      {
         vector<float> &R__stl =  ElTot;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            float R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      {
         vector<float> &R__stl =  ElCompound;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            float R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      {
         vector<float> &R__stl =  ElDirect;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            float R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      R__b >> TOTGamProd;
      R__b >> TOTNProd;
      R__b >> TOTPProd;
      R__b >> TOTDProd;
      R__b >> TOTAProd;
      R__b >> TotElastic;
      R__b >> CompoundElastic;
      R__b >> DirectElastic;
      R__b >> TotInelastic;
      R__b >> CompoundInelastic;
      R__b >> DirectInelastic;
      R__b >> TotTalys;
      R__b >> BNECS_g;
      R__b >> BNECS_n;
      R__b >> BNECS_p;
      R__b >> BNECS_d;
      R__b >> BNECS_t;
      R__b >> BNECS_tau;
      R__b >> BNECS_a;
      R__b >> TEISTot;
      R__b >> TEISCont;
      R__b >> TEISDiscr;
      R__b.CheckByteCount(R__s, R__c, NucleusData::IsA());
   } else {
      R__c = R__b.WriteVersion(NucleusData::IsA(), kTRUE);
      TObject::Streamer(R__b);
      { TString R__str = Name.c_str(); R__str.Streamer(R__b);}
      { TString R__str = Reaction.c_str(); R__str.Streamer(R__b);}
      { TString R__str = Projectile.c_str(); R__str.Streamer(R__b);}
      R__b << A;
      R__b << Z;
      {
         vector<LevelData> &R__stl =  LevelsData;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<LevelData>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            ((LevelData&)(*R__k)).Streamer(R__b);
            }
         }
      }
      {
         vector<NucleusData> &R__stl =  ProductsData;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<NucleusData>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            ((NucleusData&)(*R__k)).Streamer(R__b);
            }
         }
      }
      R__b << TalysCalculated;
      R__b << Abundance;
      R__b << ProjectileEnergy;
      {
         vector<float> &R__stl =  Angle;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<float>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      {
         vector<float> &R__stl =  ElTot;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<float>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      {
         vector<float> &R__stl =  ElCompound;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<float>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      {
         vector<float> &R__stl =  ElDirect;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<float>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      R__b << TOTGamProd;
      R__b << TOTNProd;
      R__b << TOTPProd;
      R__b << TOTDProd;
      R__b << TOTAProd;
      R__b << TotElastic;
      R__b << CompoundElastic;
      R__b << DirectElastic;
      R__b << TotInelastic;
      R__b << CompoundInelastic;
      R__b << DirectInelastic;
      R__b << TotTalys;
      R__b << BNECS_g;
      R__b << BNECS_n;
      R__b << BNECS_p;
      R__b << BNECS_d;
      R__b << BNECS_t;
      R__b << BNECS_tau;
      R__b << BNECS_a;
      R__b << TEISTot;
      R__b << TEISCont;
      R__b << TEISDiscr;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_NucleusData(void *p) {
      return  p ? new(p) ::NucleusData : new ::NucleusData;
   }
   static void *newArray_NucleusData(Long_t nElements, void *p) {
      return p ? new(p) ::NucleusData[nElements] : new ::NucleusData[nElements];
   }
   // Wrapper around operator delete
   static void delete_NucleusData(void *p) {
      delete ((::NucleusData*)p);
   }
   static void deleteArray_NucleusData(void *p) {
      delete [] ((::NucleusData*)p);
   }
   static void destruct_NucleusData(void *p) {
      typedef ::NucleusData current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_NucleusData(TBuffer &buf, void *obj) {
      ((::NucleusData*)obj)->::NucleusData::Streamer(buf);
   }
} // end of namespace ROOT for class ::NucleusData

//______________________________________________________________________________
void Nucleus::Streamer(TBuffer &R__b)
{
   // Stream an object of class Nucleus.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      NucleusData::Streamer(R__b);
      R__b >> PlottedADist;
      {
         vector<Level> &R__stl =  Levels;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            Level R__t;
            R__t.Streamer(R__b);
            R__stl.push_back(R__t);
         }
      }
      {
         vector<Level*> &R__stl =  LevelsFromTalys;
         R__stl.clear();
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class Level *));
         if (R__tcl1==0) {
            Error("LevelsFromTalys streamer","Missing the TClass object for class Level *!");
            return;
         }
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            Level* R__t;
            R__t = (Level*)R__b.ReadObjectAny(R__tcl1);
            R__stl.push_back(R__t);
         }
      }
      {
         vector<Level*> &R__stl =  LevelsFromENSDF;
         R__stl.clear();
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class Level *));
         if (R__tcl1==0) {
            Error("LevelsFromENSDF streamer","Missing the TClass object for class Level *!");
            return;
         }
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            Level* R__t;
            R__t = (Level*)R__b.ReadObjectAny(R__tcl1);
            R__stl.push_back(R__t);
         }
      }
      {
         vector<string> &R__stl =  TalysOptions;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            string R__t;
            {TString R__str;
             R__str.Streamer(R__b);
             R__t = R__str.Data();}
            R__stl.push_back(R__t);
         }
      }
      Def.Streamer(R__b);
      ElacticTotTalys.Streamer(R__b);
      ElasticDirectTalys.Streamer(R__b);
      ElasticCompoundTalys.Streamer(R__b);
      InelasticTotTalysV.Streamer(R__b);
      InelasticDirectTalysV.Streamer(R__b);
      InelasticCompoundTalysV.Streamer(R__b);
      ElasticTotTalysV.Streamer(R__b);
      ElasticDirectTalysV.Streamer(R__b);
      ElasticCompoundTalysV.Streamer(R__b);
      TotTalysV.Streamer(R__b);
      BNECS_gamma.Streamer(R__b);
      BNECS_neutron.Streamer(R__b);
      BNECS_proton.Streamer(R__b);
      BNECS_deuteron.Streamer(R__b);
      BNECS_triton.Streamer(R__b);
      BNECS_3He.Streamer(R__b);
      BNECS_alpha.Streamer(R__b);
      TEISGraphTot.Streamer(R__b);
      TEISGraphCont.Streamer(R__b);
      TEISGraphDiscr.Streamer(R__b);
      R__b >> TalysGroundStateExsists;
      R__b >> fMotherNucleus;
      {
         vector<Nucleus> &R__stl =  Products;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            Nucleus R__t;
            R__t.Streamer(R__b);
            R__stl.push_back(R__t);
         }
      }
      R__b.CheckByteCount(R__s, R__c, Nucleus::IsA());
   } else {
      R__c = R__b.WriteVersion(Nucleus::IsA(), kTRUE);
      NucleusData::Streamer(R__b);
      R__b << PlottedADist;
      {
         vector<Level> &R__stl =  Levels;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<Level>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            ((Level&)(*R__k)).Streamer(R__b);
            }
         }
      }
      {
         vector<Level*> &R__stl =  LevelsFromTalys;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<Level*>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      {
         vector<Level*> &R__stl =  LevelsFromENSDF;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<Level*>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      {
         vector<string> &R__stl =  TalysOptions;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<string>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            {TString R__str((*R__k).c_str());
             R__str.Streamer(R__b);};
            }
         }
      }
      Def.Streamer(R__b);
      ElacticTotTalys.Streamer(R__b);
      ElasticDirectTalys.Streamer(R__b);
      ElasticCompoundTalys.Streamer(R__b);
      InelasticTotTalysV.Streamer(R__b);
      InelasticDirectTalysV.Streamer(R__b);
      InelasticCompoundTalysV.Streamer(R__b);
      ElasticTotTalysV.Streamer(R__b);
      ElasticDirectTalysV.Streamer(R__b);
      ElasticCompoundTalysV.Streamer(R__b);
      TotTalysV.Streamer(R__b);
      BNECS_gamma.Streamer(R__b);
      BNECS_neutron.Streamer(R__b);
      BNECS_proton.Streamer(R__b);
      BNECS_deuteron.Streamer(R__b);
      BNECS_triton.Streamer(R__b);
      BNECS_3He.Streamer(R__b);
      BNECS_alpha.Streamer(R__b);
      TEISGraphTot.Streamer(R__b);
      TEISGraphCont.Streamer(R__b);
      TEISGraphDiscr.Streamer(R__b);
      R__b << TalysGroundStateExsists;
      R__b << fMotherNucleus;
      {
         vector<Nucleus> &R__stl =  Products;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<Nucleus>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            ((Nucleus&)(*R__k)).Streamer(R__b);
            }
         }
      }
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Nucleus(void *p) {
      return  p ? new(p) ::Nucleus : new ::Nucleus;
   }
   static void *newArray_Nucleus(Long_t nElements, void *p) {
      return p ? new(p) ::Nucleus[nElements] : new ::Nucleus[nElements];
   }
   // Wrapper around operator delete
   static void delete_Nucleus(void *p) {
      delete ((::Nucleus*)p);
   }
   static void deleteArray_Nucleus(void *p) {
      delete [] ((::Nucleus*)p);
   }
   static void destruct_Nucleus(void *p) {
      typedef ::Nucleus current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Nucleus(TBuffer &buf, void *obj) {
      ((::Nucleus*)obj)->::Nucleus::Streamer(buf);
   }
} // end of namespace ROOT for class ::Nucleus

//______________________________________________________________________________
void TalysCalculation::Streamer(TBuffer &R__b)
{
   // Stream an object of class TalysCalculation.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      {
         vector<Nucleus> &R__stl =  Results;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            Nucleus R__t;
            R__t.Streamer(R__b);
            R__stl.push_back(R__t);
         }
      }
      R__b >> FinalResult;
      { TString R__str; R__str.Streamer(R__b); Target = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); Proj = R__str.Data(); }
      {
         vector<string> &R__stl =  TalysOptions;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            string R__t;
            {TString R__str;
             R__str.Streamer(R__b);
             R__t = R__str.Data();}
            R__stl.push_back(R__t);
         }
      }
      { TString R__str; R__str.Streamer(R__b); Variable = R__str.Data(); }
      Elastic.Streamer(R__b);
      Inelastic.Streamer(R__b);
      {
         vector<double> &R__stl =  VarValues;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            double R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      R__b >> ProjectileEnergy;
      R__b.CheckByteCount(R__s, R__c, TalysCalculation::IsA());
   } else {
      R__c = R__b.WriteVersion(TalysCalculation::IsA(), kTRUE);
      TObject::Streamer(R__b);
      {
         vector<Nucleus> &R__stl =  Results;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<Nucleus>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            ((Nucleus&)(*R__k)).Streamer(R__b);
            }
         }
      }
      R__b << FinalResult;
      { TString R__str = Target.c_str(); R__str.Streamer(R__b);}
      { TString R__str = Proj.c_str(); R__str.Streamer(R__b);}
      {
         vector<string> &R__stl =  TalysOptions;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<string>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            {TString R__str((*R__k).c_str());
             R__str.Streamer(R__b);};
            }
         }
      }
      { TString R__str = Variable.c_str(); R__str.Streamer(R__b);}
      Elastic.Streamer(R__b);
      Inelastic.Streamer(R__b);
      {
         vector<double> &R__stl =  VarValues;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<double>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      R__b << ProjectileEnergy;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TalysCalculation(void *p) {
      return  p ? new(p) ::TalysCalculation : new ::TalysCalculation;
   }
   static void *newArray_TalysCalculation(Long_t nElements, void *p) {
      return p ? new(p) ::TalysCalculation[nElements] : new ::TalysCalculation[nElements];
   }
   // Wrapper around operator delete
   static void delete_TalysCalculation(void *p) {
      delete ((::TalysCalculation*)p);
   }
   static void deleteArray_TalysCalculation(void *p) {
      delete [] ((::TalysCalculation*)p);
   }
   static void destruct_TalysCalculation(void *p) {
      typedef ::TalysCalculation current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TalysCalculation(TBuffer &buf, void *obj) {
      ((::TalysCalculation*)obj)->::TalysCalculation::Streamer(buf);
   }
} // end of namespace ROOT for class ::TalysCalculation

//______________________________________________________________________________
void SampleInformation::Streamer(TBuffer &R__b)
{
   // Stream an object of class SampleInformation.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> SizeX;
      R__b >> SizeY;
      R__b >> SizeZ;
      R__b >> PositionX;
      R__b >> PositionY;
      R__b >> PositionZ;
      R__b >> Density;
      {
         vector<NucleusData> &R__stl =  Nuclei;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            NucleusData R__t;
            R__t.Streamer(R__b);
            R__stl.push_back(R__t);
         }
      }
      {
         vector<NucleusData> &R__stl =  NucleiInMedia;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            NucleusData R__t;
            R__t.Streamer(R__b);
            R__stl.push_back(R__t);
         }
      }
      { TString R__str; R__str.Streamer(R__b); Substance = R__str.Data(); }
      {
         vector<string> &R__stl =  Elements;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            string R__t;
            {TString R__str;
             R__str.Streamer(R__b);
             R__t = R__str.Data();}
            R__stl.push_back(R__t);
         }
      }
      {
         vector<string> &R__stl =  ElementsInMedia;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            string R__t;
            {TString R__str;
             R__str.Streamer(R__b);
             R__t = R__str.Data();}
            R__stl.push_back(R__t);
         }
      }
      {
         vector<int> &R__stl =  Quantities;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            int R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      { TString R__str; R__str.Streamer(R__b); Name = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); SampleType = R__str.Data(); }
      R__b.CheckByteCount(R__s, R__c, SampleInformation::IsA());
   } else {
      R__c = R__b.WriteVersion(SampleInformation::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << SizeX;
      R__b << SizeY;
      R__b << SizeZ;
      R__b << PositionX;
      R__b << PositionY;
      R__b << PositionZ;
      R__b << Density;
      {
         vector<NucleusData> &R__stl =  Nuclei;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<NucleusData>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            ((NucleusData&)(*R__k)).Streamer(R__b);
            }
         }
      }
      {
         vector<NucleusData> &R__stl =  NucleiInMedia;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<NucleusData>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            ((NucleusData&)(*R__k)).Streamer(R__b);
            }
         }
      }
      { TString R__str = Substance.c_str(); R__str.Streamer(R__b);}
      {
         vector<string> &R__stl =  Elements;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<string>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            {TString R__str((*R__k).c_str());
             R__str.Streamer(R__b);};
            }
         }
      }
      {
         vector<string> &R__stl =  ElementsInMedia;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<string>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            {TString R__str((*R__k).c_str());
             R__str.Streamer(R__b);};
            }
         }
      }
      {
         vector<int> &R__stl =  Quantities;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<int>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      { TString R__str = Name.c_str(); R__str.Streamer(R__b);}
      { TString R__str = SampleType.c_str(); R__str.Streamer(R__b);}
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SampleInformation(void *p) {
      return  p ? new(p) ::SampleInformation : new ::SampleInformation;
   }
   static void *newArray_SampleInformation(Long_t nElements, void *p) {
      return p ? new(p) ::SampleInformation[nElements] : new ::SampleInformation[nElements];
   }
   // Wrapper around operator delete
   static void delete_SampleInformation(void *p) {
      delete ((::SampleInformation*)p);
   }
   static void deleteArray_SampleInformation(void *p) {
      delete [] ((::SampleInformation*)p);
   }
   static void destruct_SampleInformation(void *p) {
      typedef ::SampleInformation current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_SampleInformation(TBuffer &buf, void *obj) {
      ((::SampleInformation*)obj)->::SampleInformation::Streamer(buf);
   }
} // end of namespace ROOT for class ::SampleInformation

namespace ROOT {
   static TClass *vectorlEunsignedsPintgR_Dictionary();
   static void vectorlEunsignedsPintgR_TClassManip(TClass*);
   static void *new_vectorlEunsignedsPintgR(void *p = 0);
   static void *newArray_vectorlEunsignedsPintgR(Long_t size, void *p);
   static void delete_vectorlEunsignedsPintgR(void *p);
   static void deleteArray_vectorlEunsignedsPintgR(void *p);
   static void destruct_vectorlEunsignedsPintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<unsigned int>*)
   {
      vector<unsigned int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<unsigned int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<unsigned int>", -2, "vector", 214,
                  typeid(vector<unsigned int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEunsignedsPintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<unsigned int>) );
      instance.SetNew(&new_vectorlEunsignedsPintgR);
      instance.SetNewArray(&newArray_vectorlEunsignedsPintgR);
      instance.SetDelete(&delete_vectorlEunsignedsPintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEunsignedsPintgR);
      instance.SetDestructor(&destruct_vectorlEunsignedsPintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<unsigned int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<unsigned int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEunsignedsPintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<unsigned int>*)0x0)->GetClass();
      vectorlEunsignedsPintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEunsignedsPintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEunsignedsPintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned int> : new vector<unsigned int>;
   }
   static void *newArray_vectorlEunsignedsPintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned int>[nElements] : new vector<unsigned int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEunsignedsPintgR(void *p) {
      delete ((vector<unsigned int>*)p);
   }
   static void deleteArray_vectorlEunsignedsPintgR(void *p) {
      delete [] ((vector<unsigned int>*)p);
   }
   static void destruct_vectorlEunsignedsPintgR(void *p) {
      typedef vector<unsigned int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<unsigned int>

namespace ROOT {
   static TClass *vectorlEstringgR_Dictionary();
   static void vectorlEstringgR_TClassManip(TClass*);
   static void *new_vectorlEstringgR(void *p = 0);
   static void *newArray_vectorlEstringgR(Long_t size, void *p);
   static void delete_vectorlEstringgR(void *p);
   static void deleteArray_vectorlEstringgR(void *p);
   static void destruct_vectorlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<string>*)
   {
      vector<string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<string>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<string>", -2, "vector", 214,
                  typeid(vector<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<string>) );
      instance.SetNew(&new_vectorlEstringgR);
      instance.SetNewArray(&newArray_vectorlEstringgR);
      instance.SetDelete(&delete_vectorlEstringgR);
      instance.SetDeleteArray(&deleteArray_vectorlEstringgR);
      instance.SetDestructor(&destruct_vectorlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<string> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<string>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<string>*)0x0)->GetClass();
      vectorlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string> : new vector<string>;
   }
   static void *newArray_vectorlEstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string>[nElements] : new vector<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEstringgR(void *p) {
      delete ((vector<string>*)p);
   }
   static void deleteArray_vectorlEstringgR(void *p) {
      delete [] ((vector<string>*)p);
   }
   static void destruct_vectorlEstringgR(void *p) {
      typedef vector<string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<string>

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 214,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = 0);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 214,
                  typeid(vector<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<float>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float>*)0x0)->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete ((vector<float>*)p);
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] ((vector<float>*)p);
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 214,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlESpinParitygR_Dictionary();
   static void vectorlESpinParitygR_TClassManip(TClass*);
   static void *new_vectorlESpinParitygR(void *p = 0);
   static void *newArray_vectorlESpinParitygR(Long_t size, void *p);
   static void delete_vectorlESpinParitygR(void *p);
   static void deleteArray_vectorlESpinParitygR(void *p);
   static void destruct_vectorlESpinParitygR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<SpinParity>*)
   {
      vector<SpinParity> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<SpinParity>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<SpinParity>", -2, "vector", 214,
                  typeid(vector<SpinParity>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlESpinParitygR_Dictionary, isa_proxy, 0,
                  sizeof(vector<SpinParity>) );
      instance.SetNew(&new_vectorlESpinParitygR);
      instance.SetNewArray(&newArray_vectorlESpinParitygR);
      instance.SetDelete(&delete_vectorlESpinParitygR);
      instance.SetDeleteArray(&deleteArray_vectorlESpinParitygR);
      instance.SetDestructor(&destruct_vectorlESpinParitygR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<SpinParity> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<SpinParity>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlESpinParitygR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<SpinParity>*)0x0)->GetClass();
      vectorlESpinParitygR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlESpinParitygR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlESpinParitygR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<SpinParity> : new vector<SpinParity>;
   }
   static void *newArray_vectorlESpinParitygR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<SpinParity>[nElements] : new vector<SpinParity>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlESpinParitygR(void *p) {
      delete ((vector<SpinParity>*)p);
   }
   static void deleteArray_vectorlESpinParitygR(void *p) {
      delete [] ((vector<SpinParity>*)p);
   }
   static void destruct_vectorlESpinParitygR(void *p) {
      typedef vector<SpinParity> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<SpinParity>

namespace ROOT {
   static TClass *vectorlENucleusDatagR_Dictionary();
   static void vectorlENucleusDatagR_TClassManip(TClass*);
   static void *new_vectorlENucleusDatagR(void *p = 0);
   static void *newArray_vectorlENucleusDatagR(Long_t size, void *p);
   static void delete_vectorlENucleusDatagR(void *p);
   static void deleteArray_vectorlENucleusDatagR(void *p);
   static void destruct_vectorlENucleusDatagR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<NucleusData>*)
   {
      vector<NucleusData> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<NucleusData>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<NucleusData>", -2, "vector", 214,
                  typeid(vector<NucleusData>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlENucleusDatagR_Dictionary, isa_proxy, 0,
                  sizeof(vector<NucleusData>) );
      instance.SetNew(&new_vectorlENucleusDatagR);
      instance.SetNewArray(&newArray_vectorlENucleusDatagR);
      instance.SetDelete(&delete_vectorlENucleusDatagR);
      instance.SetDeleteArray(&deleteArray_vectorlENucleusDatagR);
      instance.SetDestructor(&destruct_vectorlENucleusDatagR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<NucleusData> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<NucleusData>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlENucleusDatagR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<NucleusData>*)0x0)->GetClass();
      vectorlENucleusDatagR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlENucleusDatagR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlENucleusDatagR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<NucleusData> : new vector<NucleusData>;
   }
   static void *newArray_vectorlENucleusDatagR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<NucleusData>[nElements] : new vector<NucleusData>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlENucleusDatagR(void *p) {
      delete ((vector<NucleusData>*)p);
   }
   static void deleteArray_vectorlENucleusDatagR(void *p) {
      delete [] ((vector<NucleusData>*)p);
   }
   static void destruct_vectorlENucleusDatagR(void *p) {
      typedef vector<NucleusData> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<NucleusData>

namespace ROOT {
   static TClass *vectorlENucleusgR_Dictionary();
   static void vectorlENucleusgR_TClassManip(TClass*);
   static void *new_vectorlENucleusgR(void *p = 0);
   static void *newArray_vectorlENucleusgR(Long_t size, void *p);
   static void delete_vectorlENucleusgR(void *p);
   static void deleteArray_vectorlENucleusgR(void *p);
   static void destruct_vectorlENucleusgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Nucleus>*)
   {
      vector<Nucleus> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Nucleus>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Nucleus>", -2, "vector", 214,
                  typeid(vector<Nucleus>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlENucleusgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Nucleus>) );
      instance.SetNew(&new_vectorlENucleusgR);
      instance.SetNewArray(&newArray_vectorlENucleusgR);
      instance.SetDelete(&delete_vectorlENucleusgR);
      instance.SetDeleteArray(&deleteArray_vectorlENucleusgR);
      instance.SetDestructor(&destruct_vectorlENucleusgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Nucleus> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Nucleus>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlENucleusgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Nucleus>*)0x0)->GetClass();
      vectorlENucleusgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlENucleusgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlENucleusgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Nucleus> : new vector<Nucleus>;
   }
   static void *newArray_vectorlENucleusgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Nucleus>[nElements] : new vector<Nucleus>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlENucleusgR(void *p) {
      delete ((vector<Nucleus>*)p);
   }
   static void deleteArray_vectorlENucleusgR(void *p) {
      delete [] ((vector<Nucleus>*)p);
   }
   static void destruct_vectorlENucleusgR(void *p) {
      typedef vector<Nucleus> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Nucleus>

namespace ROOT {
   static TClass *vectorlELevelDeformationgR_Dictionary();
   static void vectorlELevelDeformationgR_TClassManip(TClass*);
   static void *new_vectorlELevelDeformationgR(void *p = 0);
   static void *newArray_vectorlELevelDeformationgR(Long_t size, void *p);
   static void delete_vectorlELevelDeformationgR(void *p);
   static void deleteArray_vectorlELevelDeformationgR(void *p);
   static void destruct_vectorlELevelDeformationgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<LevelDeformation>*)
   {
      vector<LevelDeformation> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<LevelDeformation>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<LevelDeformation>", -2, "vector", 214,
                  typeid(vector<LevelDeformation>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlELevelDeformationgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<LevelDeformation>) );
      instance.SetNew(&new_vectorlELevelDeformationgR);
      instance.SetNewArray(&newArray_vectorlELevelDeformationgR);
      instance.SetDelete(&delete_vectorlELevelDeformationgR);
      instance.SetDeleteArray(&deleteArray_vectorlELevelDeformationgR);
      instance.SetDestructor(&destruct_vectorlELevelDeformationgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<LevelDeformation> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<LevelDeformation>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlELevelDeformationgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<LevelDeformation>*)0x0)->GetClass();
      vectorlELevelDeformationgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlELevelDeformationgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlELevelDeformationgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<LevelDeformation> : new vector<LevelDeformation>;
   }
   static void *newArray_vectorlELevelDeformationgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<LevelDeformation>[nElements] : new vector<LevelDeformation>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlELevelDeformationgR(void *p) {
      delete ((vector<LevelDeformation>*)p);
   }
   static void deleteArray_vectorlELevelDeformationgR(void *p) {
      delete [] ((vector<LevelDeformation>*)p);
   }
   static void destruct_vectorlELevelDeformationgR(void *p) {
      typedef vector<LevelDeformation> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<LevelDeformation>

namespace ROOT {
   static TClass *vectorlELevelDatagR_Dictionary();
   static void vectorlELevelDatagR_TClassManip(TClass*);
   static void *new_vectorlELevelDatagR(void *p = 0);
   static void *newArray_vectorlELevelDatagR(Long_t size, void *p);
   static void delete_vectorlELevelDatagR(void *p);
   static void deleteArray_vectorlELevelDatagR(void *p);
   static void destruct_vectorlELevelDatagR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<LevelData>*)
   {
      vector<LevelData> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<LevelData>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<LevelData>", -2, "vector", 214,
                  typeid(vector<LevelData>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlELevelDatagR_Dictionary, isa_proxy, 0,
                  sizeof(vector<LevelData>) );
      instance.SetNew(&new_vectorlELevelDatagR);
      instance.SetNewArray(&newArray_vectorlELevelDatagR);
      instance.SetDelete(&delete_vectorlELevelDatagR);
      instance.SetDeleteArray(&deleteArray_vectorlELevelDatagR);
      instance.SetDestructor(&destruct_vectorlELevelDatagR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<LevelData> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<LevelData>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlELevelDatagR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<LevelData>*)0x0)->GetClass();
      vectorlELevelDatagR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlELevelDatagR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlELevelDatagR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<LevelData> : new vector<LevelData>;
   }
   static void *newArray_vectorlELevelDatagR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<LevelData>[nElements] : new vector<LevelData>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlELevelDatagR(void *p) {
      delete ((vector<LevelData>*)p);
   }
   static void deleteArray_vectorlELevelDatagR(void *p) {
      delete [] ((vector<LevelData>*)p);
   }
   static void destruct_vectorlELevelDatagR(void *p) {
      typedef vector<LevelData> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<LevelData>

namespace ROOT {
   static TClass *vectorlELevelgR_Dictionary();
   static void vectorlELevelgR_TClassManip(TClass*);
   static void *new_vectorlELevelgR(void *p = 0);
   static void *newArray_vectorlELevelgR(Long_t size, void *p);
   static void delete_vectorlELevelgR(void *p);
   static void deleteArray_vectorlELevelgR(void *p);
   static void destruct_vectorlELevelgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Level>*)
   {
      vector<Level> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Level>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Level>", -2, "vector", 214,
                  typeid(vector<Level>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlELevelgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Level>) );
      instance.SetNew(&new_vectorlELevelgR);
      instance.SetNewArray(&newArray_vectorlELevelgR);
      instance.SetDelete(&delete_vectorlELevelgR);
      instance.SetDeleteArray(&deleteArray_vectorlELevelgR);
      instance.SetDestructor(&destruct_vectorlELevelgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Level> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Level>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlELevelgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Level>*)0x0)->GetClass();
      vectorlELevelgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlELevelgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlELevelgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Level> : new vector<Level>;
   }
   static void *newArray_vectorlELevelgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Level>[nElements] : new vector<Level>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlELevelgR(void *p) {
      delete ((vector<Level>*)p);
   }
   static void deleteArray_vectorlELevelgR(void *p) {
      delete [] ((vector<Level>*)p);
   }
   static void destruct_vectorlELevelgR(void *p) {
      typedef vector<Level> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Level>

namespace ROOT {
   static TClass *vectorlELevelmUgR_Dictionary();
   static void vectorlELevelmUgR_TClassManip(TClass*);
   static void *new_vectorlELevelmUgR(void *p = 0);
   static void *newArray_vectorlELevelmUgR(Long_t size, void *p);
   static void delete_vectorlELevelmUgR(void *p);
   static void deleteArray_vectorlELevelmUgR(void *p);
   static void destruct_vectorlELevelmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Level*>*)
   {
      vector<Level*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Level*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Level*>", -2, "vector", 214,
                  typeid(vector<Level*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlELevelmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Level*>) );
      instance.SetNew(&new_vectorlELevelmUgR);
      instance.SetNewArray(&newArray_vectorlELevelmUgR);
      instance.SetDelete(&delete_vectorlELevelmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlELevelmUgR);
      instance.SetDestructor(&destruct_vectorlELevelmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Level*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Level*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlELevelmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Level*>*)0x0)->GetClass();
      vectorlELevelmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlELevelmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlELevelmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Level*> : new vector<Level*>;
   }
   static void *newArray_vectorlELevelmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Level*>[nElements] : new vector<Level*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlELevelmUgR(void *p) {
      delete ((vector<Level*>*)p);
   }
   static void deleteArray_vectorlELevelmUgR(void *p) {
      delete [] ((vector<Level*>*)p);
   }
   static void destruct_vectorlELevelmUgR(void *p) {
      typedef vector<Level*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Level*>

namespace ROOT {
   static TClass *vectorlEGammaTransitionDatagR_Dictionary();
   static void vectorlEGammaTransitionDatagR_TClassManip(TClass*);
   static void *new_vectorlEGammaTransitionDatagR(void *p = 0);
   static void *newArray_vectorlEGammaTransitionDatagR(Long_t size, void *p);
   static void delete_vectorlEGammaTransitionDatagR(void *p);
   static void deleteArray_vectorlEGammaTransitionDatagR(void *p);
   static void destruct_vectorlEGammaTransitionDatagR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GammaTransitionData>*)
   {
      vector<GammaTransitionData> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GammaTransitionData>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GammaTransitionData>", -2, "vector", 214,
                  typeid(vector<GammaTransitionData>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGammaTransitionDatagR_Dictionary, isa_proxy, 0,
                  sizeof(vector<GammaTransitionData>) );
      instance.SetNew(&new_vectorlEGammaTransitionDatagR);
      instance.SetNewArray(&newArray_vectorlEGammaTransitionDatagR);
      instance.SetDelete(&delete_vectorlEGammaTransitionDatagR);
      instance.SetDeleteArray(&deleteArray_vectorlEGammaTransitionDatagR);
      instance.SetDestructor(&destruct_vectorlEGammaTransitionDatagR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GammaTransitionData> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<GammaTransitionData>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGammaTransitionDatagR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<GammaTransitionData>*)0x0)->GetClass();
      vectorlEGammaTransitionDatagR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGammaTransitionDatagR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGammaTransitionDatagR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GammaTransitionData> : new vector<GammaTransitionData>;
   }
   static void *newArray_vectorlEGammaTransitionDatagR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GammaTransitionData>[nElements] : new vector<GammaTransitionData>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGammaTransitionDatagR(void *p) {
      delete ((vector<GammaTransitionData>*)p);
   }
   static void deleteArray_vectorlEGammaTransitionDatagR(void *p) {
      delete [] ((vector<GammaTransitionData>*)p);
   }
   static void destruct_vectorlEGammaTransitionDatagR(void *p) {
      typedef vector<GammaTransitionData> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<GammaTransitionData>

namespace ROOT {
   static TClass *vectorlEGammaTransitiongR_Dictionary();
   static void vectorlEGammaTransitiongR_TClassManip(TClass*);
   static void *new_vectorlEGammaTransitiongR(void *p = 0);
   static void *newArray_vectorlEGammaTransitiongR(Long_t size, void *p);
   static void delete_vectorlEGammaTransitiongR(void *p);
   static void deleteArray_vectorlEGammaTransitiongR(void *p);
   static void destruct_vectorlEGammaTransitiongR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GammaTransition>*)
   {
      vector<GammaTransition> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GammaTransition>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GammaTransition>", -2, "vector", 214,
                  typeid(vector<GammaTransition>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGammaTransitiongR_Dictionary, isa_proxy, 0,
                  sizeof(vector<GammaTransition>) );
      instance.SetNew(&new_vectorlEGammaTransitiongR);
      instance.SetNewArray(&newArray_vectorlEGammaTransitiongR);
      instance.SetDelete(&delete_vectorlEGammaTransitiongR);
      instance.SetDeleteArray(&deleteArray_vectorlEGammaTransitiongR);
      instance.SetDestructor(&destruct_vectorlEGammaTransitiongR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GammaTransition> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<GammaTransition>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGammaTransitiongR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<GammaTransition>*)0x0)->GetClass();
      vectorlEGammaTransitiongR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGammaTransitiongR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGammaTransitiongR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GammaTransition> : new vector<GammaTransition>;
   }
   static void *newArray_vectorlEGammaTransitiongR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GammaTransition>[nElements] : new vector<GammaTransition>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGammaTransitiongR(void *p) {
      delete ((vector<GammaTransition>*)p);
   }
   static void deleteArray_vectorlEGammaTransitiongR(void *p) {
      delete [] ((vector<GammaTransition>*)p);
   }
   static void destruct_vectorlEGammaTransitiongR(void *p) {
      typedef vector<GammaTransition> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<GammaTransition>

namespace {
  void TriggerDictionaryInitialization_LevelsDict_Impl() {
    static const char* headers[] = {
"Levels.hh",
0
    };
    static const char* includePaths[] = {
"/home/terawatt/Programs/root/root-install/include",
"/home/terawatt/server/RAID1/Ing-27-Alpatov/macro/dec_reader/Levels_new_version/Lib/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "LevelsDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$Levels.hh")))  OpticalModelParameters;
class __attribute__((annotate("$clingAutoload$Levels.hh")))  SpinParity;
class __attribute__((annotate("$clingAutoload$Levels.hh")))  GammaTransitionData;
class __attribute__((annotate("$clingAutoload$Levels.hh")))  GammaTransition;
class __attribute__((annotate("$clingAutoload$Levels.hh")))  LevelData;
class __attribute__((annotate("$clingAutoload$Levels.hh")))  LevelDeformation;
class __attribute__((annotate("$clingAutoload$Levels.hh")))  Deformation;
class __attribute__((annotate("$clingAutoload$Levels.hh")))  Level;
class __attribute__((annotate("$clingAutoload$Levels.hh")))  NucleusData;
class __attribute__((annotate("$clingAutoload$Levels.hh")))  Nucleus;
class __attribute__((annotate("$clingAutoload$Levels.hh")))  TalysCalculation;
class __attribute__((annotate("$clingAutoload$Levels.hh")))  SampleInformation;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "LevelsDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "Levels.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Deformation", payloadCode, "@",
"GammaTransition", payloadCode, "@",
"GammaTransitionData", payloadCode, "@",
"Level", payloadCode, "@",
"LevelData", payloadCode, "@",
"LevelDeformation", payloadCode, "@",
"Nucleus", payloadCode, "@",
"NucleusData", payloadCode, "@",
"OpticalModelParameters", payloadCode, "@",
"SampleInformation", payloadCode, "@",
"SpinParity", payloadCode, "@",
"TalysCalculation", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("LevelsDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_LevelsDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_LevelsDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_LevelsDict() {
  TriggerDictionaryInitialization_LevelsDict_Impl();
}
