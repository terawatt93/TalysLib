// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TalysLibDict
#define R__NO_DEPRECATION

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

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "TalysLib.hh"

// Header files passed via #pragma extra_include

namespace ROOT {

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TalysLibManager*)
   {
      ::TalysLibManager *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TalysLibManager >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TalysLibManager", ::TalysLibManager::Class_Version(), "TalysLib.hh", 78,
                  typeid(::TalysLibManager), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TalysLibManager::Dictionary, isa_proxy, 4,
                  sizeof(::TalysLibManager) );
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TalysLibManager*)
   {
      return GenerateInitInstanceLocal((::TalysLibManager*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TalysLibManager*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AdditionalInformationContainer(void *p = 0);
   static void *newArray_AdditionalInformationContainer(Long_t size, void *p);
   static void delete_AdditionalInformationContainer(void *p);
   static void deleteArray_AdditionalInformationContainer(void *p);
   static void destruct_AdditionalInformationContainer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AdditionalInformationContainer*)
   {
      ::AdditionalInformationContainer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AdditionalInformationContainer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AdditionalInformationContainer", ::AdditionalInformationContainer::Class_Version(), "TalysLib.hh", 97,
                  typeid(::AdditionalInformationContainer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AdditionalInformationContainer::Dictionary, isa_proxy, 4,
                  sizeof(::AdditionalInformationContainer) );
      instance.SetNew(&new_AdditionalInformationContainer);
      instance.SetNewArray(&newArray_AdditionalInformationContainer);
      instance.SetDelete(&delete_AdditionalInformationContainer);
      instance.SetDeleteArray(&deleteArray_AdditionalInformationContainer);
      instance.SetDestructor(&destruct_AdditionalInformationContainer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AdditionalInformationContainer*)
   {
      return GenerateInitInstanceLocal((::AdditionalInformationContainer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AdditionalInformationContainer*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TXlsxwriter(void *p = 0);
   static void *newArray_TXlsxwriter(Long_t size, void *p);
   static void delete_TXlsxwriter(void *p);
   static void deleteArray_TXlsxwriter(void *p);
   static void destruct_TXlsxwriter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TXlsxwriter*)
   {
      ::TXlsxwriter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TXlsxwriter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TXlsxwriter", ::TXlsxwriter::Class_Version(), "TalysLib.hh", 105,
                  typeid(::TXlsxwriter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TXlsxwriter::Dictionary, isa_proxy, 4,
                  sizeof(::TXlsxwriter) );
      instance.SetNew(&new_TXlsxwriter);
      instance.SetNewArray(&newArray_TXlsxwriter);
      instance.SetDelete(&delete_TXlsxwriter);
      instance.SetDeleteArray(&deleteArray_TXlsxwriter);
      instance.SetDestructor(&destruct_TXlsxwriter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TXlsxwriter*)
   {
      return GenerateInitInstanceLocal((::TXlsxwriter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TXlsxwriter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_OMPStorageData(void *p = 0);
   static void *newArray_OMPStorageData(Long_t size, void *p);
   static void delete_OMPStorageData(void *p);
   static void deleteArray_OMPStorageData(void *p);
   static void destruct_OMPStorageData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::OMPStorageData*)
   {
      ::OMPStorageData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::OMPStorageData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("OMPStorageData", ::OMPStorageData::Class_Version(), "TalysLib.hh", 145,
                  typeid(::OMPStorageData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::OMPStorageData::Dictionary, isa_proxy, 4,
                  sizeof(::OMPStorageData) );
      instance.SetNew(&new_OMPStorageData);
      instance.SetNewArray(&newArray_OMPStorageData);
      instance.SetDelete(&delete_OMPStorageData);
      instance.SetDeleteArray(&deleteArray_OMPStorageData);
      instance.SetDestructor(&destruct_OMPStorageData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::OMPStorageData*)
   {
      return GenerateInitInstanceLocal((::OMPStorageData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::OMPStorageData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_OMPStorage(void *p = 0);
   static void *newArray_OMPStorage(Long_t size, void *p);
   static void delete_OMPStorage(void *p);
   static void deleteArray_OMPStorage(void *p);
   static void destruct_OMPStorage(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::OMPStorage*)
   {
      ::OMPStorage *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::OMPStorage >(0);
      static ::ROOT::TGenericClassInfo 
         instance("OMPStorage", ::OMPStorage::Class_Version(), "TalysLib.hh", 157,
                  typeid(::OMPStorage), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::OMPStorage::Dictionary, isa_proxy, 4,
                  sizeof(::OMPStorage) );
      instance.SetNew(&new_OMPStorage);
      instance.SetNewArray(&newArray_OMPStorage);
      instance.SetDelete(&delete_OMPStorage);
      instance.SetDeleteArray(&deleteArray_OMPStorage);
      instance.SetDestructor(&destruct_OMPStorage);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::OMPStorage*)
   {
      return GenerateInitInstanceLocal((::OMPStorage*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::OMPStorage*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_OpticalModelParametersData(void *p = 0);
   static void *newArray_OpticalModelParametersData(Long_t size, void *p);
   static void delete_OpticalModelParametersData(void *p);
   static void deleteArray_OpticalModelParametersData(void *p);
   static void destruct_OpticalModelParametersData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::OpticalModelParametersData*)
   {
      ::OpticalModelParametersData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::OpticalModelParametersData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("OpticalModelParametersData", ::OpticalModelParametersData::Class_Version(), "TalysLib.hh", 204,
                  typeid(::OpticalModelParametersData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::OpticalModelParametersData::Dictionary, isa_proxy, 4,
                  sizeof(::OpticalModelParametersData) );
      instance.SetNew(&new_OpticalModelParametersData);
      instance.SetNewArray(&newArray_OpticalModelParametersData);
      instance.SetDelete(&delete_OpticalModelParametersData);
      instance.SetDeleteArray(&deleteArray_OpticalModelParametersData);
      instance.SetDestructor(&destruct_OpticalModelParametersData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::OpticalModelParametersData*)
   {
      return GenerateInitInstanceLocal((::OpticalModelParametersData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::OpticalModelParametersData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_OpticalModelParameters(void *p = 0);
   static void *newArray_OpticalModelParameters(Long_t size, void *p);
   static void delete_OpticalModelParameters(void *p);
   static void deleteArray_OpticalModelParameters(void *p);
   static void destruct_OpticalModelParameters(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::OpticalModelParameters*)
   {
      ::OpticalModelParameters *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::OpticalModelParameters >(0);
      static ::ROOT::TGenericClassInfo 
         instance("OpticalModelParameters", ::OpticalModelParameters::Class_Version(), "TalysLib.hh", 223,
                  typeid(::OpticalModelParameters), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::OpticalModelParameters::Dictionary, isa_proxy, 4,
                  sizeof(::OpticalModelParameters) );
      instance.SetNew(&new_OpticalModelParameters);
      instance.SetNewArray(&newArray_OpticalModelParameters);
      instance.SetDelete(&delete_OpticalModelParameters);
      instance.SetDeleteArray(&deleteArray_OpticalModelParameters);
      instance.SetDestructor(&destruct_OpticalModelParameters);
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

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SpinParity*)
   {
      ::SpinParity *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SpinParity >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SpinParity", ::SpinParity::Class_Version(), "TalysLib.hh", 283,
                  typeid(::SpinParity), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SpinParity::Dictionary, isa_proxy, 4,
                  sizeof(::SpinParity) );
      instance.SetNew(&new_SpinParity);
      instance.SetNewArray(&newArray_SpinParity);
      instance.SetDelete(&delete_SpinParity);
      instance.SetDeleteArray(&deleteArray_SpinParity);
      instance.SetDestructor(&destruct_SpinParity);
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

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GammaTransitionData*)
   {
      ::GammaTransitionData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GammaTransitionData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GammaTransitionData", ::GammaTransitionData::Class_Version(), "TalysLib.hh", 305,
                  typeid(::GammaTransitionData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GammaTransitionData::Dictionary, isa_proxy, 4,
                  sizeof(::GammaTransitionData) );
      instance.SetNew(&new_GammaTransitionData);
      instance.SetNewArray(&newArray_GammaTransitionData);
      instance.SetDelete(&delete_GammaTransitionData);
      instance.SetDeleteArray(&deleteArray_GammaTransitionData);
      instance.SetDestructor(&destruct_GammaTransitionData);
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

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GammaTransition*)
   {
      ::GammaTransition *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GammaTransition >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GammaTransition", ::GammaTransition::Class_Version(), "TalysLib.hh", 322,
                  typeid(::GammaTransition), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GammaTransition::Dictionary, isa_proxy, 4,
                  sizeof(::GammaTransition) );
      instance.SetNew(&new_GammaTransition);
      instance.SetNewArray(&newArray_GammaTransition);
      instance.SetDelete(&delete_GammaTransition);
      instance.SetDeleteArray(&deleteArray_GammaTransition);
      instance.SetDestructor(&destruct_GammaTransition);
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

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LevelData*)
   {
      ::LevelData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LevelData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LevelData", ::LevelData::Class_Version(), "TalysLib.hh", 364,
                  typeid(::LevelData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LevelData::Dictionary, isa_proxy, 4,
                  sizeof(::LevelData) );
      instance.SetNew(&new_LevelData);
      instance.SetNewArray(&newArray_LevelData);
      instance.SetDelete(&delete_LevelData);
      instance.SetDeleteArray(&deleteArray_LevelData);
      instance.SetDestructor(&destruct_LevelData);
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
   static void *new_LevelDeformationData(void *p = 0);
   static void *newArray_LevelDeformationData(Long_t size, void *p);
   static void delete_LevelDeformationData(void *p);
   static void deleteArray_LevelDeformationData(void *p);
   static void destruct_LevelDeformationData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LevelDeformationData*)
   {
      ::LevelDeformationData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LevelDeformationData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LevelDeformationData", ::LevelDeformationData::Class_Version(), "TalysLib.hh", 383,
                  typeid(::LevelDeformationData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LevelDeformationData::Dictionary, isa_proxy, 4,
                  sizeof(::LevelDeformationData) );
      instance.SetNew(&new_LevelDeformationData);
      instance.SetNewArray(&newArray_LevelDeformationData);
      instance.SetDelete(&delete_LevelDeformationData);
      instance.SetDeleteArray(&deleteArray_LevelDeformationData);
      instance.SetDestructor(&destruct_LevelDeformationData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LevelDeformationData*)
   {
      return GenerateInitInstanceLocal((::LevelDeformationData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::LevelDeformationData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LevelDeformation(void *p = 0);
   static void *newArray_LevelDeformation(Long_t size, void *p);
   static void delete_LevelDeformation(void *p);
   static void deleteArray_LevelDeformation(void *p);
   static void destruct_LevelDeformation(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LevelDeformation*)
   {
      ::LevelDeformation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LevelDeformation >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LevelDeformation", ::LevelDeformation::Class_Version(), "TalysLib.hh", 392,
                  typeid(::LevelDeformation), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LevelDeformation::Dictionary, isa_proxy, 4,
                  sizeof(::LevelDeformation) );
      instance.SetNew(&new_LevelDeformation);
      instance.SetNewArray(&newArray_LevelDeformation);
      instance.SetDelete(&delete_LevelDeformation);
      instance.SetDeleteArray(&deleteArray_LevelDeformation);
      instance.SetDestructor(&destruct_LevelDeformation);
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
   static void *new_DeformationData(void *p = 0);
   static void *newArray_DeformationData(Long_t size, void *p);
   static void delete_DeformationData(void *p);
   static void deleteArray_DeformationData(void *p);
   static void destruct_DeformationData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DeformationData*)
   {
      ::DeformationData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::DeformationData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("DeformationData", ::DeformationData::Class_Version(), "TalysLib.hh", 405,
                  typeid(::DeformationData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::DeformationData::Dictionary, isa_proxy, 4,
                  sizeof(::DeformationData) );
      instance.SetNew(&new_DeformationData);
      instance.SetNewArray(&newArray_DeformationData);
      instance.SetDelete(&delete_DeformationData);
      instance.SetDeleteArray(&deleteArray_DeformationData);
      instance.SetDestructor(&destruct_DeformationData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DeformationData*)
   {
      return GenerateInitInstanceLocal((::DeformationData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::DeformationData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Deformation(void *p = 0);
   static void *newArray_Deformation(Long_t size, void *p);
   static void delete_Deformation(void *p);
   static void deleteArray_Deformation(void *p);
   static void destruct_Deformation(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Deformation*)
   {
      ::Deformation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Deformation >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Deformation", ::Deformation::Class_Version(), "TalysLib.hh", 415,
                  typeid(::Deformation), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Deformation::Dictionary, isa_proxy, 4,
                  sizeof(::Deformation) );
      instance.SetNew(&new_Deformation);
      instance.SetNewArray(&newArray_Deformation);
      instance.SetDelete(&delete_Deformation);
      instance.SetDeleteArray(&deleteArray_Deformation);
      instance.SetDestructor(&destruct_Deformation);
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

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Level*)
   {
      ::Level *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Level >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Level", ::Level::Class_Version(), "TalysLib.hh", 435,
                  typeid(::Level), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Level::Dictionary, isa_proxy, 4,
                  sizeof(::Level) );
      instance.SetNew(&new_Level);
      instance.SetNewArray(&newArray_Level);
      instance.SetDelete(&delete_Level);
      instance.SetDeleteArray(&deleteArray_Level);
      instance.SetDestructor(&destruct_Level);
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

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::NucleusData*)
   {
      ::NucleusData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::NucleusData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("NucleusData", ::NucleusData::Class_Version(), "TalysLib.hh", 491,
                  typeid(::NucleusData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::NucleusData::Dictionary, isa_proxy, 4,
                  sizeof(::NucleusData) );
      instance.SetNew(&new_NucleusData);
      instance.SetNewArray(&newArray_NucleusData);
      instance.SetDelete(&delete_NucleusData);
      instance.SetDeleteArray(&deleteArray_NucleusData);
      instance.SetDestructor(&destruct_NucleusData);
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

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Nucleus*)
   {
      ::Nucleus *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Nucleus >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Nucleus", ::Nucleus::Class_Version(), "TalysLib.hh", 533,
                  typeid(::Nucleus), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Nucleus::Dictionary, isa_proxy, 4,
                  sizeof(::Nucleus) );
      instance.SetNew(&new_Nucleus);
      instance.SetNewArray(&newArray_Nucleus);
      instance.SetDelete(&delete_Nucleus);
      instance.SetDeleteArray(&deleteArray_Nucleus);
      instance.SetDestructor(&destruct_Nucleus);
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
   static void *new_Radionuclide(void *p = 0);
   static void *newArray_Radionuclide(Long_t size, void *p);
   static void delete_Radionuclide(void *p);
   static void deleteArray_Radionuclide(void *p);
   static void destruct_Radionuclide(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Radionuclide*)
   {
      ::Radionuclide *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Radionuclide >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Radionuclide", ::Radionuclide::Class_Version(), "TalysLib.hh", 645,
                  typeid(::Radionuclide), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Radionuclide::Dictionary, isa_proxy, 4,
                  sizeof(::Radionuclide) );
      instance.SetNew(&new_Radionuclide);
      instance.SetNewArray(&newArray_Radionuclide);
      instance.SetDelete(&delete_Radionuclide);
      instance.SetDeleteArray(&deleteArray_Radionuclide);
      instance.SetDestructor(&destruct_Radionuclide);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Radionuclide*)
   {
      return GenerateInitInstanceLocal((::Radionuclide*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Radionuclide*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TalysCalculation(void *p = 0);
   static void *newArray_TalysCalculation(Long_t size, void *p);
   static void delete_TalysCalculation(void *p);
   static void deleteArray_TalysCalculation(void *p);
   static void destruct_TalysCalculation(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TalysCalculation*)
   {
      ::TalysCalculation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TalysCalculation >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TalysCalculation", ::TalysCalculation::Class_Version(), "TalysLib.hh", 740,
                  typeid(::TalysCalculation), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TalysCalculation::Dictionary, isa_proxy, 4,
                  sizeof(::TalysCalculation) );
      instance.SetNew(&new_TalysCalculation);
      instance.SetNewArray(&newArray_TalysCalculation);
      instance.SetDelete(&delete_TalysCalculation);
      instance.SetDeleteArray(&deleteArray_TalysCalculation);
      instance.SetDestructor(&destruct_TalysCalculation);
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
   static void *new_TLMaterial(void *p = 0);
   static void *newArray_TLMaterial(Long_t size, void *p);
   static void delete_TLMaterial(void *p);
   static void deleteArray_TLMaterial(void *p);
   static void destruct_TLMaterial(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TLMaterial*)
   {
      ::TLMaterial *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TLMaterial >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TLMaterial", ::TLMaterial::Class_Version(), "TalysLib.hh", 776,
                  typeid(::TLMaterial), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TLMaterial::Dictionary, isa_proxy, 4,
                  sizeof(::TLMaterial) );
      instance.SetNew(&new_TLMaterial);
      instance.SetNewArray(&newArray_TLMaterial);
      instance.SetDelete(&delete_TLMaterial);
      instance.SetDeleteArray(&deleteArray_TLMaterial);
      instance.SetDestructor(&destruct_TLMaterial);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TLMaterial*)
   {
      return GenerateInitInstanceLocal((::TLMaterial*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TLMaterial*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SampleInformation(void *p = 0);
   static void *newArray_SampleInformation(Long_t size, void *p);
   static void delete_SampleInformation(void *p);
   static void deleteArray_SampleInformation(void *p);
   static void destruct_SampleInformation(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SampleInformation*)
   {
      ::SampleInformation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SampleInformation >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SampleInformation", ::SampleInformation::Class_Version(), "TalysLib.hh", 811,
                  typeid(::SampleInformation), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SampleInformation::Dictionary, isa_proxy, 4,
                  sizeof(::SampleInformation) );
      instance.SetNew(&new_SampleInformation);
      instance.SetNewArray(&newArray_SampleInformation);
      instance.SetDelete(&delete_SampleInformation);
      instance.SetDeleteArray(&deleteArray_SampleInformation);
      instance.SetDestructor(&destruct_SampleInformation);
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
atomic_TClass_ptr TalysLibManager::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TalysLibManager::Class_Name()
{
   return "TalysLibManager";
}

//______________________________________________________________________________
const char *TalysLibManager::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TalysLibManager*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TalysLibManager::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TalysLibManager*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TalysLibManager::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TalysLibManager*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TalysLibManager::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TalysLibManager*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AdditionalInformationContainer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AdditionalInformationContainer::Class_Name()
{
   return "AdditionalInformationContainer";
}

//______________________________________________________________________________
const char *AdditionalInformationContainer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AdditionalInformationContainer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AdditionalInformationContainer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AdditionalInformationContainer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AdditionalInformationContainer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AdditionalInformationContainer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AdditionalInformationContainer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AdditionalInformationContainer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TXlsxwriter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TXlsxwriter::Class_Name()
{
   return "TXlsxwriter";
}

//______________________________________________________________________________
const char *TXlsxwriter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TXlsxwriter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TXlsxwriter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TXlsxwriter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TXlsxwriter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TXlsxwriter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TXlsxwriter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TXlsxwriter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr OMPStorageData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *OMPStorageData::Class_Name()
{
   return "OMPStorageData";
}

//______________________________________________________________________________
const char *OMPStorageData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OMPStorageData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int OMPStorageData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OMPStorageData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *OMPStorageData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OMPStorageData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *OMPStorageData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OMPStorageData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr OMPStorage::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *OMPStorage::Class_Name()
{
   return "OMPStorage";
}

//______________________________________________________________________________
const char *OMPStorage::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OMPStorage*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int OMPStorage::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OMPStorage*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *OMPStorage::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OMPStorage*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *OMPStorage::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OMPStorage*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr OpticalModelParametersData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *OpticalModelParametersData::Class_Name()
{
   return "OpticalModelParametersData";
}

//______________________________________________________________________________
const char *OpticalModelParametersData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OpticalModelParametersData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int OpticalModelParametersData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OpticalModelParametersData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *OpticalModelParametersData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OpticalModelParametersData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *OpticalModelParametersData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OpticalModelParametersData*)0x0)->GetClass(); }
   return fgIsA;
}

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
atomic_TClass_ptr LevelDeformationData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LevelDeformationData::Class_Name()
{
   return "LevelDeformationData";
}

//______________________________________________________________________________
const char *LevelDeformationData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LevelDeformationData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LevelDeformationData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LevelDeformationData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LevelDeformationData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LevelDeformationData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LevelDeformationData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LevelDeformationData*)0x0)->GetClass(); }
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
atomic_TClass_ptr DeformationData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *DeformationData::Class_Name()
{
   return "DeformationData";
}

//______________________________________________________________________________
const char *DeformationData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DeformationData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int DeformationData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DeformationData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *DeformationData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::DeformationData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *DeformationData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::DeformationData*)0x0)->GetClass(); }
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
atomic_TClass_ptr Radionuclide::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Radionuclide::Class_Name()
{
   return "Radionuclide";
}

//______________________________________________________________________________
const char *Radionuclide::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Radionuclide*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Radionuclide::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Radionuclide*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Radionuclide::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Radionuclide*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Radionuclide::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Radionuclide*)0x0)->GetClass(); }
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
atomic_TClass_ptr TLMaterial::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TLMaterial::Class_Name()
{
   return "TLMaterial";
}

//______________________________________________________________________________
const char *TLMaterial::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TLMaterial*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TLMaterial::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TLMaterial*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TLMaterial::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TLMaterial*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TLMaterial::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TLMaterial*)0x0)->GetClass(); }
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
void TalysLibManager::Streamer(TBuffer &R__b)
{
   // Stream an object of class TalysLibManager.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TalysLibManager::Class(),this);
   } else {
      R__b.WriteClassBuffer(TalysLibManager::Class(),this);
   }
}

namespace ROOT {
} // end of namespace ROOT for class ::TalysLibManager

//______________________________________________________________________________
void AdditionalInformationContainer::Streamer(TBuffer &R__b)
{
   // Stream an object of class AdditionalInformationContainer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AdditionalInformationContainer::Class(),this);
   } else {
      R__b.WriteClassBuffer(AdditionalInformationContainer::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AdditionalInformationContainer(void *p) {
      return  p ? new(p) ::AdditionalInformationContainer : new ::AdditionalInformationContainer;
   }
   static void *newArray_AdditionalInformationContainer(Long_t nElements, void *p) {
      return p ? new(p) ::AdditionalInformationContainer[nElements] : new ::AdditionalInformationContainer[nElements];
   }
   // Wrapper around operator delete
   static void delete_AdditionalInformationContainer(void *p) {
      delete ((::AdditionalInformationContainer*)p);
   }
   static void deleteArray_AdditionalInformationContainer(void *p) {
      delete [] ((::AdditionalInformationContainer*)p);
   }
   static void destruct_AdditionalInformationContainer(void *p) {
      typedef ::AdditionalInformationContainer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AdditionalInformationContainer

//______________________________________________________________________________
void TXlsxwriter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TXlsxwriter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TXlsxwriter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TXlsxwriter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TXlsxwriter(void *p) {
      return  p ? new(p) ::TXlsxwriter : new ::TXlsxwriter;
   }
   static void *newArray_TXlsxwriter(Long_t nElements, void *p) {
      return p ? new(p) ::TXlsxwriter[nElements] : new ::TXlsxwriter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TXlsxwriter(void *p) {
      delete ((::TXlsxwriter*)p);
   }
   static void deleteArray_TXlsxwriter(void *p) {
      delete [] ((::TXlsxwriter*)p);
   }
   static void destruct_TXlsxwriter(void *p) {
      typedef ::TXlsxwriter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TXlsxwriter

//______________________________________________________________________________
void OMPStorageData::Streamer(TBuffer &R__b)
{
   // Stream an object of class OMPStorageData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(OMPStorageData::Class(),this);
   } else {
      R__b.WriteClassBuffer(OMPStorageData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_OMPStorageData(void *p) {
      return  p ? new(p) ::OMPStorageData : new ::OMPStorageData;
   }
   static void *newArray_OMPStorageData(Long_t nElements, void *p) {
      return p ? new(p) ::OMPStorageData[nElements] : new ::OMPStorageData[nElements];
   }
   // Wrapper around operator delete
   static void delete_OMPStorageData(void *p) {
      delete ((::OMPStorageData*)p);
   }
   static void deleteArray_OMPStorageData(void *p) {
      delete [] ((::OMPStorageData*)p);
   }
   static void destruct_OMPStorageData(void *p) {
      typedef ::OMPStorageData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::OMPStorageData

//______________________________________________________________________________
void OMPStorage::Streamer(TBuffer &R__b)
{
   // Stream an object of class OMPStorage.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(OMPStorage::Class(),this);
   } else {
      R__b.WriteClassBuffer(OMPStorage::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_OMPStorage(void *p) {
      return  p ? new(p) ::OMPStorage : new ::OMPStorage;
   }
   static void *newArray_OMPStorage(Long_t nElements, void *p) {
      return p ? new(p) ::OMPStorage[nElements] : new ::OMPStorage[nElements];
   }
   // Wrapper around operator delete
   static void delete_OMPStorage(void *p) {
      delete ((::OMPStorage*)p);
   }
   static void deleteArray_OMPStorage(void *p) {
      delete [] ((::OMPStorage*)p);
   }
   static void destruct_OMPStorage(void *p) {
      typedef ::OMPStorage current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::OMPStorage

//______________________________________________________________________________
void OpticalModelParametersData::Streamer(TBuffer &R__b)
{
   // Stream an object of class OpticalModelParametersData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(OpticalModelParametersData::Class(),this);
   } else {
      R__b.WriteClassBuffer(OpticalModelParametersData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_OpticalModelParametersData(void *p) {
      return  p ? new(p) ::OpticalModelParametersData : new ::OpticalModelParametersData;
   }
   static void *newArray_OpticalModelParametersData(Long_t nElements, void *p) {
      return p ? new(p) ::OpticalModelParametersData[nElements] : new ::OpticalModelParametersData[nElements];
   }
   // Wrapper around operator delete
   static void delete_OpticalModelParametersData(void *p) {
      delete ((::OpticalModelParametersData*)p);
   }
   static void deleteArray_OpticalModelParametersData(void *p) {
      delete [] ((::OpticalModelParametersData*)p);
   }
   static void destruct_OpticalModelParametersData(void *p) {
      typedef ::OpticalModelParametersData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::OpticalModelParametersData

//______________________________________________________________________________
void OpticalModelParameters::Streamer(TBuffer &R__b)
{
   // Stream an object of class OpticalModelParameters.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(OpticalModelParameters::Class(),this);
   } else {
      R__b.WriteClassBuffer(OpticalModelParameters::Class(),this);
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
} // end of namespace ROOT for class ::OpticalModelParameters

//______________________________________________________________________________
void SpinParity::Streamer(TBuffer &R__b)
{
   // Stream an object of class SpinParity.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SpinParity::Class(),this);
   } else {
      R__b.WriteClassBuffer(SpinParity::Class(),this);
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
} // end of namespace ROOT for class ::SpinParity

//______________________________________________________________________________
void GammaTransitionData::Streamer(TBuffer &R__b)
{
   // Stream an object of class GammaTransitionData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GammaTransitionData::Class(),this);
   } else {
      R__b.WriteClassBuffer(GammaTransitionData::Class(),this);
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
} // end of namespace ROOT for class ::GammaTransitionData

//______________________________________________________________________________
void GammaTransition::Streamer(TBuffer &R__b)
{
   // Stream an object of class GammaTransition.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GammaTransition::Class(),this);
   } else {
      R__b.WriteClassBuffer(GammaTransition::Class(),this);
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
} // end of namespace ROOT for class ::GammaTransition

//______________________________________________________________________________
void LevelData::Streamer(TBuffer &R__b)
{
   // Stream an object of class LevelData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LevelData::Class(),this);
   } else {
      R__b.WriteClassBuffer(LevelData::Class(),this);
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
} // end of namespace ROOT for class ::LevelData

//______________________________________________________________________________
void LevelDeformationData::Streamer(TBuffer &R__b)
{
   // Stream an object of class LevelDeformationData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LevelDeformationData::Class(),this);
   } else {
      R__b.WriteClassBuffer(LevelDeformationData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LevelDeformationData(void *p) {
      return  p ? new(p) ::LevelDeformationData : new ::LevelDeformationData;
   }
   static void *newArray_LevelDeformationData(Long_t nElements, void *p) {
      return p ? new(p) ::LevelDeformationData[nElements] : new ::LevelDeformationData[nElements];
   }
   // Wrapper around operator delete
   static void delete_LevelDeformationData(void *p) {
      delete ((::LevelDeformationData*)p);
   }
   static void deleteArray_LevelDeformationData(void *p) {
      delete [] ((::LevelDeformationData*)p);
   }
   static void destruct_LevelDeformationData(void *p) {
      typedef ::LevelDeformationData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LevelDeformationData

//______________________________________________________________________________
void LevelDeformation::Streamer(TBuffer &R__b)
{
   // Stream an object of class LevelDeformation.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LevelDeformation::Class(),this);
   } else {
      R__b.WriteClassBuffer(LevelDeformation::Class(),this);
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
} // end of namespace ROOT for class ::LevelDeformation

//______________________________________________________________________________
void DeformationData::Streamer(TBuffer &R__b)
{
   // Stream an object of class DeformationData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(DeformationData::Class(),this);
   } else {
      R__b.WriteClassBuffer(DeformationData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_DeformationData(void *p) {
      return  p ? new(p) ::DeformationData : new ::DeformationData;
   }
   static void *newArray_DeformationData(Long_t nElements, void *p) {
      return p ? new(p) ::DeformationData[nElements] : new ::DeformationData[nElements];
   }
   // Wrapper around operator delete
   static void delete_DeformationData(void *p) {
      delete ((::DeformationData*)p);
   }
   static void deleteArray_DeformationData(void *p) {
      delete [] ((::DeformationData*)p);
   }
   static void destruct_DeformationData(void *p) {
      typedef ::DeformationData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::DeformationData

//______________________________________________________________________________
void Deformation::Streamer(TBuffer &R__b)
{
   // Stream an object of class Deformation.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Deformation::Class(),this);
   } else {
      R__b.WriteClassBuffer(Deformation::Class(),this);
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
} // end of namespace ROOT for class ::Deformation

//______________________________________________________________________________
void Level::Streamer(TBuffer &R__b)
{
   // Stream an object of class Level.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Level::Class(),this);
   } else {
      R__b.WriteClassBuffer(Level::Class(),this);
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
} // end of namespace ROOT for class ::Level

//______________________________________________________________________________
void NucleusData::Streamer(TBuffer &R__b)
{
   // Stream an object of class NucleusData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(NucleusData::Class(),this);
   } else {
      R__b.WriteClassBuffer(NucleusData::Class(),this);
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
} // end of namespace ROOT for class ::NucleusData

//______________________________________________________________________________
void Nucleus::Streamer(TBuffer &R__b)
{
   // Stream an object of class Nucleus.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Nucleus::Class(),this);
   } else {
      R__b.WriteClassBuffer(Nucleus::Class(),this);
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
} // end of namespace ROOT for class ::Nucleus

//______________________________________________________________________________
void Radionuclide::Streamer(TBuffer &R__b)
{
   // Stream an object of class Radionuclide.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Radionuclide::Class(),this);
   } else {
      R__b.WriteClassBuffer(Radionuclide::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Radionuclide(void *p) {
      return  p ? new(p) ::Radionuclide : new ::Radionuclide;
   }
   static void *newArray_Radionuclide(Long_t nElements, void *p) {
      return p ? new(p) ::Radionuclide[nElements] : new ::Radionuclide[nElements];
   }
   // Wrapper around operator delete
   static void delete_Radionuclide(void *p) {
      delete ((::Radionuclide*)p);
   }
   static void deleteArray_Radionuclide(void *p) {
      delete [] ((::Radionuclide*)p);
   }
   static void destruct_Radionuclide(void *p) {
      typedef ::Radionuclide current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Radionuclide

//______________________________________________________________________________
void TalysCalculation::Streamer(TBuffer &R__b)
{
   // Stream an object of class TalysCalculation.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TalysCalculation::Class(),this);
   } else {
      R__b.WriteClassBuffer(TalysCalculation::Class(),this);
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
} // end of namespace ROOT for class ::TalysCalculation

//______________________________________________________________________________
void TLMaterial::Streamer(TBuffer &R__b)
{
   // Stream an object of class TLMaterial.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TLMaterial::Class(),this);
   } else {
      R__b.WriteClassBuffer(TLMaterial::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TLMaterial(void *p) {
      return  p ? new(p) ::TLMaterial : new ::TLMaterial;
   }
   static void *newArray_TLMaterial(Long_t nElements, void *p) {
      return p ? new(p) ::TLMaterial[nElements] : new ::TLMaterial[nElements];
   }
   // Wrapper around operator delete
   static void delete_TLMaterial(void *p) {
      delete ((::TLMaterial*)p);
   }
   static void deleteArray_TLMaterial(void *p) {
      delete [] ((::TLMaterial*)p);
   }
   static void destruct_TLMaterial(void *p) {
      typedef ::TLMaterial current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TLMaterial

//______________________________________________________________________________
void SampleInformation::Streamer(TBuffer &R__b)
{
   // Stream an object of class SampleInformation.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SampleInformation::Class(),this);
   } else {
      R__b.WriteClassBuffer(SampleInformation::Class(),this);
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
} // end of namespace ROOT for class ::SampleInformation

namespace ROOT {
   static TClass *vectorlEvectorlEfloatgRsPgR_Dictionary();
   static void vectorlEvectorlEfloatgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEfloatgRsPgR(void *p = 0);
   static void *newArray_vectorlEvectorlEfloatgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEfloatgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEfloatgRsPgR(void *p);
   static void destruct_vectorlEvectorlEfloatgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<float> >*)
   {
      vector<vector<float> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<float> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<float> >", -2, "vector", 216,
                  typeid(vector<vector<float> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEfloatgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<vector<float> >) );
      instance.SetNew(&new_vectorlEvectorlEfloatgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEfloatgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEfloatgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEfloatgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEfloatgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<float> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<vector<float> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEfloatgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<float> >*)0x0)->GetClass();
      vectorlEvectorlEfloatgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEfloatgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEfloatgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<float> > : new vector<vector<float> >;
   }
   static void *newArray_vectorlEvectorlEfloatgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<float> >[nElements] : new vector<vector<float> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEfloatgRsPgR(void *p) {
      delete ((vector<vector<float> >*)p);
   }
   static void deleteArray_vectorlEvectorlEfloatgRsPgR(void *p) {
      delete [] ((vector<vector<float> >*)p);
   }
   static void destruct_vectorlEvectorlEfloatgRsPgR(void *p) {
      typedef vector<vector<float> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<float> >

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
         instance("vector<unsigned int>", -2, "vector", 216,
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
         instance("vector<string>", -2, "vector", 216,
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
   static TClass *vectorlElxw_worksheetmUgR_Dictionary();
   static void vectorlElxw_worksheetmUgR_TClassManip(TClass*);
   static void *new_vectorlElxw_worksheetmUgR(void *p = 0);
   static void *newArray_vectorlElxw_worksheetmUgR(Long_t size, void *p);
   static void delete_vectorlElxw_worksheetmUgR(void *p);
   static void deleteArray_vectorlElxw_worksheetmUgR(void *p);
   static void destruct_vectorlElxw_worksheetmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<lxw_worksheet*>*)
   {
      vector<lxw_worksheet*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<lxw_worksheet*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<lxw_worksheet*>", -2, "vector", 216,
                  typeid(vector<lxw_worksheet*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlElxw_worksheetmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<lxw_worksheet*>) );
      instance.SetNew(&new_vectorlElxw_worksheetmUgR);
      instance.SetNewArray(&newArray_vectorlElxw_worksheetmUgR);
      instance.SetDelete(&delete_vectorlElxw_worksheetmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlElxw_worksheetmUgR);
      instance.SetDestructor(&destruct_vectorlElxw_worksheetmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<lxw_worksheet*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<lxw_worksheet*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlElxw_worksheetmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<lxw_worksheet*>*)0x0)->GetClass();
      vectorlElxw_worksheetmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlElxw_worksheetmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlElxw_worksheetmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<lxw_worksheet*> : new vector<lxw_worksheet*>;
   }
   static void *newArray_vectorlElxw_worksheetmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<lxw_worksheet*>[nElements] : new vector<lxw_worksheet*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlElxw_worksheetmUgR(void *p) {
      delete ((vector<lxw_worksheet*>*)p);
   }
   static void deleteArray_vectorlElxw_worksheetmUgR(void *p) {
      delete [] ((vector<lxw_worksheet*>*)p);
   }
   static void destruct_vectorlElxw_worksheetmUgR(void *p) {
      typedef vector<lxw_worksheet*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<lxw_worksheet*>

namespace ROOT {
   static TClass *vectorlElxw_formatmUgR_Dictionary();
   static void vectorlElxw_formatmUgR_TClassManip(TClass*);
   static void *new_vectorlElxw_formatmUgR(void *p = 0);
   static void *newArray_vectorlElxw_formatmUgR(Long_t size, void *p);
   static void delete_vectorlElxw_formatmUgR(void *p);
   static void deleteArray_vectorlElxw_formatmUgR(void *p);
   static void destruct_vectorlElxw_formatmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<lxw_format*>*)
   {
      vector<lxw_format*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<lxw_format*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<lxw_format*>", -2, "vector", 216,
                  typeid(vector<lxw_format*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlElxw_formatmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<lxw_format*>) );
      instance.SetNew(&new_vectorlElxw_formatmUgR);
      instance.SetNewArray(&newArray_vectorlElxw_formatmUgR);
      instance.SetDelete(&delete_vectorlElxw_formatmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlElxw_formatmUgR);
      instance.SetDestructor(&destruct_vectorlElxw_formatmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<lxw_format*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<lxw_format*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlElxw_formatmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<lxw_format*>*)0x0)->GetClass();
      vectorlElxw_formatmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlElxw_formatmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlElxw_formatmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<lxw_format*> : new vector<lxw_format*>;
   }
   static void *newArray_vectorlElxw_formatmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<lxw_format*>[nElements] : new vector<lxw_format*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlElxw_formatmUgR(void *p) {
      delete ((vector<lxw_format*>*)p);
   }
   static void deleteArray_vectorlElxw_formatmUgR(void *p) {
      delete [] ((vector<lxw_format*>*)p);
   }
   static void destruct_vectorlElxw_formatmUgR(void *p) {
      typedef vector<lxw_format*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<lxw_format*>

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
         instance("vector<int>", -2, "vector", 216,
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
         instance("vector<float>", -2, "vector", 216,
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
         instance("vector<double>", -2, "vector", 216,
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
         instance("vector<SpinParity>", -2, "vector", 216,
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
   static TClass *vectorlERadionuclidegR_Dictionary();
   static void vectorlERadionuclidegR_TClassManip(TClass*);
   static void *new_vectorlERadionuclidegR(void *p = 0);
   static void *newArray_vectorlERadionuclidegR(Long_t size, void *p);
   static void delete_vectorlERadionuclidegR(void *p);
   static void deleteArray_vectorlERadionuclidegR(void *p);
   static void destruct_vectorlERadionuclidegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Radionuclide>*)
   {
      vector<Radionuclide> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Radionuclide>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Radionuclide>", -2, "vector", 216,
                  typeid(vector<Radionuclide>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlERadionuclidegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Radionuclide>) );
      instance.SetNew(&new_vectorlERadionuclidegR);
      instance.SetNewArray(&newArray_vectorlERadionuclidegR);
      instance.SetDelete(&delete_vectorlERadionuclidegR);
      instance.SetDeleteArray(&deleteArray_vectorlERadionuclidegR);
      instance.SetDestructor(&destruct_vectorlERadionuclidegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Radionuclide> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Radionuclide>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlERadionuclidegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Radionuclide>*)0x0)->GetClass();
      vectorlERadionuclidegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlERadionuclidegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlERadionuclidegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Radionuclide> : new vector<Radionuclide>;
   }
   static void *newArray_vectorlERadionuclidegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Radionuclide>[nElements] : new vector<Radionuclide>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlERadionuclidegR(void *p) {
      delete ((vector<Radionuclide>*)p);
   }
   static void deleteArray_vectorlERadionuclidegR(void *p) {
      delete [] ((vector<Radionuclide>*)p);
   }
   static void destruct_vectorlERadionuclidegR(void *p) {
      typedef vector<Radionuclide> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Radionuclide>

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
         instance("vector<NucleusData>", -2, "vector", 216,
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
         instance("vector<Nucleus>", -2, "vector", 216,
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
   static TClass *vectorlENucleusmUgR_Dictionary();
   static void vectorlENucleusmUgR_TClassManip(TClass*);
   static void *new_vectorlENucleusmUgR(void *p = 0);
   static void *newArray_vectorlENucleusmUgR(Long_t size, void *p);
   static void delete_vectorlENucleusmUgR(void *p);
   static void deleteArray_vectorlENucleusmUgR(void *p);
   static void destruct_vectorlENucleusmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Nucleus*>*)
   {
      vector<Nucleus*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Nucleus*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Nucleus*>", -2, "vector", 216,
                  typeid(vector<Nucleus*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlENucleusmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Nucleus*>) );
      instance.SetNew(&new_vectorlENucleusmUgR);
      instance.SetNewArray(&newArray_vectorlENucleusmUgR);
      instance.SetDelete(&delete_vectorlENucleusmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlENucleusmUgR);
      instance.SetDestructor(&destruct_vectorlENucleusmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Nucleus*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Nucleus*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlENucleusmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Nucleus*>*)0x0)->GetClass();
      vectorlENucleusmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlENucleusmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlENucleusmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Nucleus*> : new vector<Nucleus*>;
   }
   static void *newArray_vectorlENucleusmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Nucleus*>[nElements] : new vector<Nucleus*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlENucleusmUgR(void *p) {
      delete ((vector<Nucleus*>*)p);
   }
   static void deleteArray_vectorlENucleusmUgR(void *p) {
      delete [] ((vector<Nucleus*>*)p);
   }
   static void destruct_vectorlENucleusmUgR(void *p) {
      typedef vector<Nucleus*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Nucleus*>

namespace ROOT {
   static TClass *vectorlELevelDeformationDatagR_Dictionary();
   static void vectorlELevelDeformationDatagR_TClassManip(TClass*);
   static void *new_vectorlELevelDeformationDatagR(void *p = 0);
   static void *newArray_vectorlELevelDeformationDatagR(Long_t size, void *p);
   static void delete_vectorlELevelDeformationDatagR(void *p);
   static void deleteArray_vectorlELevelDeformationDatagR(void *p);
   static void destruct_vectorlELevelDeformationDatagR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<LevelDeformationData>*)
   {
      vector<LevelDeformationData> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<LevelDeformationData>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<LevelDeformationData>", -2, "vector", 216,
                  typeid(vector<LevelDeformationData>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlELevelDeformationDatagR_Dictionary, isa_proxy, 0,
                  sizeof(vector<LevelDeformationData>) );
      instance.SetNew(&new_vectorlELevelDeformationDatagR);
      instance.SetNewArray(&newArray_vectorlELevelDeformationDatagR);
      instance.SetDelete(&delete_vectorlELevelDeformationDatagR);
      instance.SetDeleteArray(&deleteArray_vectorlELevelDeformationDatagR);
      instance.SetDestructor(&destruct_vectorlELevelDeformationDatagR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<LevelDeformationData> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<LevelDeformationData>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlELevelDeformationDatagR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<LevelDeformationData>*)0x0)->GetClass();
      vectorlELevelDeformationDatagR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlELevelDeformationDatagR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlELevelDeformationDatagR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<LevelDeformationData> : new vector<LevelDeformationData>;
   }
   static void *newArray_vectorlELevelDeformationDatagR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<LevelDeformationData>[nElements] : new vector<LevelDeformationData>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlELevelDeformationDatagR(void *p) {
      delete ((vector<LevelDeformationData>*)p);
   }
   static void deleteArray_vectorlELevelDeformationDatagR(void *p) {
      delete [] ((vector<LevelDeformationData>*)p);
   }
   static void destruct_vectorlELevelDeformationDatagR(void *p) {
      typedef vector<LevelDeformationData> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<LevelDeformationData>

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
         instance("vector<LevelDeformation>", -2, "vector", 216,
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
         instance("vector<LevelData>", -2, "vector", 216,
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
         instance("vector<Level>", -2, "vector", 216,
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
         instance("vector<Level*>", -2, "vector", 216,
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
         instance("vector<GammaTransitionData>", -2, "vector", 216,
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
         instance("vector<GammaTransition>", -2, "vector", 216,
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

namespace ROOT {
   static TClass *vectorlEGammaTransitionmUgR_Dictionary();
   static void vectorlEGammaTransitionmUgR_TClassManip(TClass*);
   static void *new_vectorlEGammaTransitionmUgR(void *p = 0);
   static void *newArray_vectorlEGammaTransitionmUgR(Long_t size, void *p);
   static void delete_vectorlEGammaTransitionmUgR(void *p);
   static void deleteArray_vectorlEGammaTransitionmUgR(void *p);
   static void destruct_vectorlEGammaTransitionmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GammaTransition*>*)
   {
      vector<GammaTransition*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GammaTransition*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GammaTransition*>", -2, "vector", 216,
                  typeid(vector<GammaTransition*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGammaTransitionmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<GammaTransition*>) );
      instance.SetNew(&new_vectorlEGammaTransitionmUgR);
      instance.SetNewArray(&newArray_vectorlEGammaTransitionmUgR);
      instance.SetDelete(&delete_vectorlEGammaTransitionmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEGammaTransitionmUgR);
      instance.SetDestructor(&destruct_vectorlEGammaTransitionmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GammaTransition*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<GammaTransition*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGammaTransitionmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<GammaTransition*>*)0x0)->GetClass();
      vectorlEGammaTransitionmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGammaTransitionmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGammaTransitionmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GammaTransition*> : new vector<GammaTransition*>;
   }
   static void *newArray_vectorlEGammaTransitionmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GammaTransition*>[nElements] : new vector<GammaTransition*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGammaTransitionmUgR(void *p) {
      delete ((vector<GammaTransition*>*)p);
   }
   static void deleteArray_vectorlEGammaTransitionmUgR(void *p) {
      delete [] ((vector<GammaTransition*>*)p);
   }
   static void destruct_vectorlEGammaTransitionmUgR(void *p) {
      typedef vector<GammaTransition*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<GammaTransition*>

namespace ROOT {
   static TClass *maplEstringcOdoublegR_Dictionary();
   static void maplEstringcOdoublegR_TClassManip(TClass*);
   static void *new_maplEstringcOdoublegR(void *p = 0);
   static void *newArray_maplEstringcOdoublegR(Long_t size, void *p);
   static void delete_maplEstringcOdoublegR(void *p);
   static void deleteArray_maplEstringcOdoublegR(void *p);
   static void destruct_maplEstringcOdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,double>*)
   {
      map<string,double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,double>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,double>", -2, "map", 99,
                  typeid(map<string,double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,double>) );
      instance.SetNew(&new_maplEstringcOdoublegR);
      instance.SetNewArray(&newArray_maplEstringcOdoublegR);
      instance.SetDelete(&delete_maplEstringcOdoublegR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOdoublegR);
      instance.SetDestructor(&destruct_maplEstringcOdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,double>*)0x0)->GetClass();
      maplEstringcOdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,double> : new map<string,double>;
   }
   static void *newArray_maplEstringcOdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,double>[nElements] : new map<string,double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOdoublegR(void *p) {
      delete ((map<string,double>*)p);
   }
   static void deleteArray_maplEstringcOdoublegR(void *p) {
      delete [] ((map<string,double>*)p);
   }
   static void destruct_maplEstringcOdoublegR(void *p) {
      typedef map<string,double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,double>

namespace ROOT {
   static TClass *listlETGraphgR_Dictionary();
   static void listlETGraphgR_TClassManip(TClass*);
   static void *new_listlETGraphgR(void *p = 0);
   static void *newArray_listlETGraphgR(Long_t size, void *p);
   static void delete_listlETGraphgR(void *p);
   static void deleteArray_listlETGraphgR(void *p);
   static void destruct_listlETGraphgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const list<TGraph>*)
   {
      list<TGraph> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(list<TGraph>));
      static ::ROOT::TGenericClassInfo 
         instance("list<TGraph>", -2, "list", 503,
                  typeid(list<TGraph>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &listlETGraphgR_Dictionary, isa_proxy, 0,
                  sizeof(list<TGraph>) );
      instance.SetNew(&new_listlETGraphgR);
      instance.SetNewArray(&newArray_listlETGraphgR);
      instance.SetDelete(&delete_listlETGraphgR);
      instance.SetDeleteArray(&deleteArray_listlETGraphgR);
      instance.SetDestructor(&destruct_listlETGraphgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< list<TGraph> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const list<TGraph>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *listlETGraphgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const list<TGraph>*)0x0)->GetClass();
      listlETGraphgR_TClassManip(theClass);
   return theClass;
   }

   static void listlETGraphgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_listlETGraphgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) list<TGraph> : new list<TGraph>;
   }
   static void *newArray_listlETGraphgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) list<TGraph>[nElements] : new list<TGraph>[nElements];
   }
   // Wrapper around operator delete
   static void delete_listlETGraphgR(void *p) {
      delete ((list<TGraph>*)p);
   }
   static void deleteArray_listlETGraphgR(void *p) {
      delete [] ((list<TGraph>*)p);
   }
   static void destruct_listlETGraphgR(void *p) {
      typedef list<TGraph> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class list<TGraph>

namespace {
  void TriggerDictionaryInitialization_TalysLibDict_Impl() {
    static const char* headers[] = {
"TalysLib.hh",
0
    };
    static const char* includePaths[] = {
"/home/terawatt/Programs/root/install/include/",
"/home/terawatt/Documents/TalysLib/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TalysLibDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  TalysLibManager;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  AdditionalInformationContainer;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  TXlsxwriter;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  OMPStorageData;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  OMPStorage;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  OpticalModelParametersData;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  OpticalModelParameters;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  SpinParity;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  GammaTransitionData;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  GammaTransition;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  LevelData;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  LevelDeformationData;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  LevelDeformation;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  DeformationData;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  Deformation;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  Level;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  NucleusData;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  Nucleus;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  Radionuclide;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  TalysCalculation;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  TLMaterial;
class __attribute__((annotate("$clingAutoload$TalysLib.hh")))  SampleInformation;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TalysLibDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TalysLib.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"AdditionalInformationContainer", payloadCode, "@",
"Deformation", payloadCode, "@",
"DeformationData", payloadCode, "@",
"GammaTransition", payloadCode, "@",
"GammaTransitionData", payloadCode, "@",
"Level", payloadCode, "@",
"LevelData", payloadCode, "@",
"LevelDeformation", payloadCode, "@",
"LevelDeformationData", payloadCode, "@",
"Nucleus", payloadCode, "@",
"NucleusData", payloadCode, "@",
"OMPStorage", payloadCode, "@",
"OMPStorageData", payloadCode, "@",
"OpticalModelParameters", payloadCode, "@",
"OpticalModelParametersData", payloadCode, "@",
"Radionuclide", payloadCode, "@",
"SampleInformation", payloadCode, "@",
"SpinParity", payloadCode, "@",
"TLMaterial", payloadCode, "@",
"TXlsxwriter", payloadCode, "@",
"TalysCalculation", payloadCode, "@",
"TalysLibManager", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TalysLibDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TalysLibDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TalysLibDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TalysLibDict() {
  TriggerDictionaryInitialization_TalysLibDict_Impl();
}
