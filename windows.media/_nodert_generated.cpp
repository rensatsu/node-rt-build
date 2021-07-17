// Copyright (c) The NodeRT Contributors
// All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the ""License""); you may
// not use this file except in compliance with the License. You may obtain a
// copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS
// OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY
// IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
// MERCHANTABLITY OR NON-INFRINGEMENT.
//
// See the Apache Version 2.0 License for specific language governing permissions
// and limitations under the License.

// TODO: Verify that this is is still needed..
#define NTDDI_VERSION 0x06010000

#include <v8.h>
#include "nan.h"
#include <string>
#include <ppltasks.h>
#include "CollectionsConverter.h"
#include "CollectionsWrap.h"
#include "node-async.h"
#include "NodeRtUtils.h"
#include "OpaqueWrapper.h"
#include "WrapperBase.h"

#using <Windows.WinMD>

// this undefs fixes the issues of compiling Windows.Data.Json, Windows.Storag.FileProperties, and Windows.Stroage.Search
// Some of the node header files brings windows definitions with the same names as some of the WinRT methods
#undef DocumentProperties
#undef GetObject
#undef CreateEvent
#undef FindText
#undef SendMessage

const char* REGISTRATION_TOKEN_MAP_PROPERTY_NAME = "__registrationTokenMap__";

using v8::Array;
using v8::String;
using v8::Value;
using v8::Boolean;
using v8::Integer;
using v8::FunctionTemplate;
using v8::Object;
using v8::Local;
using v8::Function;
using v8::Date;
using v8::Number;
using v8::PropertyAttribute;
using v8::Primitive;
using Nan::HandleScope;
using Nan::Persistent;
using Nan::Undefined;
using Nan::True;
using Nan::False;
using Nan::Null;
using Nan::MaybeLocal;
using Nan::EscapableHandleScope;
using Nan::HandleScope;
using Nan::TryCatch;
using namespace concurrency;

namespace NodeRT { namespace Windows { namespace Media { 
  v8::Local<v8::Value> WrapMediaProcessingTriggerDetails(::Windows::Media::MediaProcessingTriggerDetails^ wintRtInstance);
  ::Windows::Media::MediaProcessingTriggerDetails^ UnwrapMediaProcessingTriggerDetails(Local<Value> value);
  
  v8::Local<v8::Value> WrapIMediaFrame(::Windows::Media::IMediaFrame^ wintRtInstance);
  ::Windows::Media::IMediaFrame^ UnwrapIMediaFrame(Local<Value> value);
  
  v8::Local<v8::Value> WrapVideoFrame(::Windows::Media::VideoFrame^ wintRtInstance);
  ::Windows::Media::VideoFrame^ UnwrapVideoFrame(Local<Value> value);
  
  v8::Local<v8::Value> WrapAudioBuffer(::Windows::Media::AudioBuffer^ wintRtInstance);
  ::Windows::Media::AudioBuffer^ UnwrapAudioBuffer(Local<Value> value);
  
  v8::Local<v8::Value> WrapAudioFrame(::Windows::Media::AudioFrame^ wintRtInstance);
  ::Windows::Media::AudioFrame^ UnwrapAudioFrame(Local<Value> value);
  
  v8::Local<v8::Value> WrapIMediaMarker(::Windows::Media::IMediaMarker^ wintRtInstance);
  ::Windows::Media::IMediaMarker^ UnwrapIMediaMarker(Local<Value> value);
  
  v8::Local<v8::Value> WrapIMediaMarkers(::Windows::Media::IMediaMarkers^ wintRtInstance);
  ::Windows::Media::IMediaMarkers^ UnwrapIMediaMarkers(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaMarkerTypes(::Windows::Media::MediaMarkerTypes^ wintRtInstance);
  ::Windows::Media::MediaMarkerTypes^ UnwrapMediaMarkerTypes(Local<Value> value);
  
  v8::Local<v8::Value> WrapSystemMediaTransportControlsTimelineProperties(::Windows::Media::SystemMediaTransportControlsTimelineProperties^ wintRtInstance);
  ::Windows::Media::SystemMediaTransportControlsTimelineProperties^ UnwrapSystemMediaTransportControlsTimelineProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapMusicDisplayProperties(::Windows::Media::MusicDisplayProperties^ wintRtInstance);
  ::Windows::Media::MusicDisplayProperties^ UnwrapMusicDisplayProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapVideoDisplayProperties(::Windows::Media::VideoDisplayProperties^ wintRtInstance);
  ::Windows::Media::VideoDisplayProperties^ UnwrapVideoDisplayProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapImageDisplayProperties(::Windows::Media::ImageDisplayProperties^ wintRtInstance);
  ::Windows::Media::ImageDisplayProperties^ UnwrapImageDisplayProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapSystemMediaTransportControlsDisplayUpdater(::Windows::Media::SystemMediaTransportControlsDisplayUpdater^ wintRtInstance);
  ::Windows::Media::SystemMediaTransportControlsDisplayUpdater^ UnwrapSystemMediaTransportControlsDisplayUpdater(Local<Value> value);
  
  v8::Local<v8::Value> WrapSystemMediaTransportControlsButtonPressedEventArgs(::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^ wintRtInstance);
  ::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^ UnwrapSystemMediaTransportControlsButtonPressedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapSystemMediaTransportControlsPropertyChangedEventArgs(::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^ wintRtInstance);
  ::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^ UnwrapSystemMediaTransportControlsPropertyChangedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapPlaybackPositionChangeRequestedEventArgs(::Windows::Media::PlaybackPositionChangeRequestedEventArgs^ wintRtInstance);
  ::Windows::Media::PlaybackPositionChangeRequestedEventArgs^ UnwrapPlaybackPositionChangeRequestedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapPlaybackRateChangeRequestedEventArgs(::Windows::Media::PlaybackRateChangeRequestedEventArgs^ wintRtInstance);
  ::Windows::Media::PlaybackRateChangeRequestedEventArgs^ UnwrapPlaybackRateChangeRequestedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapShuffleEnabledChangeRequestedEventArgs(::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^ wintRtInstance);
  ::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^ UnwrapShuffleEnabledChangeRequestedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapAutoRepeatModeChangeRequestedEventArgs(::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^ wintRtInstance);
  ::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^ UnwrapAutoRepeatModeChangeRequestedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapSystemMediaTransportControls(::Windows::Media::SystemMediaTransportControls^ wintRtInstance);
  ::Windows::Media::SystemMediaTransportControls^ UnwrapSystemMediaTransportControls(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaTimelineController(::Windows::Media::MediaTimelineController^ wintRtInstance);
  ::Windows::Media::MediaTimelineController^ UnwrapMediaTimelineController(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaTimelineControllerFailedEventArgs(::Windows::Media::MediaTimelineControllerFailedEventArgs^ wintRtInstance);
  ::Windows::Media::MediaTimelineControllerFailedEventArgs^ UnwrapMediaTimelineControllerFailedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapIMediaExtension(::Windows::Media::IMediaExtension^ wintRtInstance);
  ::Windows::Media::IMediaExtension^ UnwrapIMediaExtension(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaExtensionManager(::Windows::Media::MediaExtensionManager^ wintRtInstance);
  ::Windows::Media::MediaExtensionManager^ UnwrapMediaExtensionManager(Local<Value> value);
  
  v8::Local<v8::Value> WrapVideoEffects(::Windows::Media::VideoEffects^ wintRtInstance);
  ::Windows::Media::VideoEffects^ UnwrapVideoEffects(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaControl(::Windows::Media::MediaControl^ wintRtInstance);
  ::Windows::Media::MediaControl^ UnwrapMediaControl(Local<Value> value);
  



  static void InitAudioBufferAccessModeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("AudioBufferAccessMode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("read").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::AudioBufferAccessMode::Read)));
    Nan::Set(enumObject, Nan::New<String>("readWrite").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::AudioBufferAccessMode::ReadWrite)));
    Nan::Set(enumObject, Nan::New<String>("write").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::AudioBufferAccessMode::Write)));
  }

  static void InitSoundLevelEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("SoundLevel").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("muted").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::SoundLevel::Muted)));
    Nan::Set(enumObject, Nan::New<String>("low").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::SoundLevel::Low)));
    Nan::Set(enumObject, Nan::New<String>("full").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::SoundLevel::Full)));
  }

  static void InitMediaPlaybackTypeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("MediaPlaybackType").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("unknown").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaPlaybackType::Unknown)));
    Nan::Set(enumObject, Nan::New<String>("music").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaPlaybackType::Music)));
    Nan::Set(enumObject, Nan::New<String>("video").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaPlaybackType::Video)));
    Nan::Set(enumObject, Nan::New<String>("image").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaPlaybackType::Image)));
  }

  static void InitMediaPlaybackAutoRepeatModeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("MediaPlaybackAutoRepeatMode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaPlaybackAutoRepeatMode::None)));
    Nan::Set(enumObject, Nan::New<String>("track").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaPlaybackAutoRepeatMode::Track)));
    Nan::Set(enumObject, Nan::New<String>("list").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaPlaybackAutoRepeatMode::List)));
  }

  static void InitMediaPlaybackStatusEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("MediaPlaybackStatus").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("closed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaPlaybackStatus::Closed)));
    Nan::Set(enumObject, Nan::New<String>("changing").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaPlaybackStatus::Changing)));
    Nan::Set(enumObject, Nan::New<String>("stopped").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaPlaybackStatus::Stopped)));
    Nan::Set(enumObject, Nan::New<String>("playing").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaPlaybackStatus::Playing)));
    Nan::Set(enumObject, Nan::New<String>("paused").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaPlaybackStatus::Paused)));
  }

  static void InitSystemMediaTransportControlsButtonEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("SystemMediaTransportControlsButton").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("play").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::SystemMediaTransportControlsButton::Play)));
    Nan::Set(enumObject, Nan::New<String>("pause").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::SystemMediaTransportControlsButton::Pause)));
    Nan::Set(enumObject, Nan::New<String>("stop").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::SystemMediaTransportControlsButton::Stop)));
    Nan::Set(enumObject, Nan::New<String>("record").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::SystemMediaTransportControlsButton::Record)));
    Nan::Set(enumObject, Nan::New<String>("fastForward").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::SystemMediaTransportControlsButton::FastForward)));
    Nan::Set(enumObject, Nan::New<String>("rewind").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::SystemMediaTransportControlsButton::Rewind)));
    Nan::Set(enumObject, Nan::New<String>("next").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::SystemMediaTransportControlsButton::Next)));
    Nan::Set(enumObject, Nan::New<String>("previous").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::SystemMediaTransportControlsButton::Previous)));
    Nan::Set(enumObject, Nan::New<String>("channelUp").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::SystemMediaTransportControlsButton::ChannelUp)));
    Nan::Set(enumObject, Nan::New<String>("channelDown").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::SystemMediaTransportControlsButton::ChannelDown)));
  }

  static void InitSystemMediaTransportControlsPropertyEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("SystemMediaTransportControlsProperty").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("soundLevel").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::SystemMediaTransportControlsProperty::SoundLevel)));
  }

  static void InitMediaTimelineControllerStateEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("MediaTimelineControllerState").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("paused").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaTimelineControllerState::Paused)));
    Nan::Set(enumObject, Nan::New<String>("running").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaTimelineControllerState::Running)));
    Nan::Set(enumObject, Nan::New<String>("stalled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaTimelineControllerState::Stalled)));
    Nan::Set(enumObject, Nan::New<String>("error").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::MediaTimelineControllerState::Error)));
  }

  static void InitAudioProcessingEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("AudioProcessing").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("default").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::AudioProcessing::Default)));
    Nan::Set(enumObject, Nan::New<String>("raw").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::AudioProcessing::Raw)));
  }

  static bool IsMediaTimeRangeJsObject(Local<Value> value) {
    if (!value->IsObject()) {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    symbol = Nan::New<String>("start").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsNumber()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("end").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsNumber()) {
        return false;
      }
    }
    
    return true;
  }

  ::Windows::Media::MediaTimeRange MediaTimeRangeFromJsObject(Local<Value> value) {
    HandleScope scope;
    ::Windows::Media::MediaTimeRange returnValue;

    if (!value->IsObject()) {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    symbol = Nan::New<String>("start").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.Start = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("end").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.End = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    return returnValue;
  }

  Local<Value> MediaTimeRangeToJsObject(::Windows::Media::MediaTimeRange value) {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    Nan::Set(obj, Nan::New<String>("start").ToLocalChecked(), Nan::New<Number>(value.Start.Duration/10000.0));
    Nan::Set(obj, Nan::New<String>("end").ToLocalChecked(), Nan::New<Number>(value.End.Duration/10000.0));

    return scope.Escape(obj);
  }
  static bool IsMediaControlContractJsObject(Local<Value> value) {
    if (!value->IsObject()) {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::Media::MediaControlContract MediaControlContractFromJsObject(Local<Value> value) {
    HandleScope scope;
    ::Windows::Media::MediaControlContract returnValue;

    if (!value->IsObject()) {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> MediaControlContractToJsObject(::Windows::Media::MediaControlContract value) {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();


    return scope.Escape(obj);
  }

  static bool IsBitmapBoundsJsObject(Local<Value> value) {
    if (!value->IsObject()) {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    symbol = Nan::New<String>("x").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsUint32()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("y").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsUint32()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("width").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsUint32()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("height").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsUint32()) {
        return false;
      }
    }
    
    return true;
  }

  ::Windows::Graphics::Imaging::BitmapBounds BitmapBoundsFromJsObject(Local<Value> value) {
    HandleScope scope;
    ::Windows::Graphics::Imaging::BitmapBounds returnValue;

    if (!value->IsObject()) {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    symbol = Nan::New<String>("x").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.X = static_cast<unsigned int>(Nan::To<uint32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("y").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.Y = static_cast<unsigned int>(Nan::To<uint32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("width").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.Width = static_cast<unsigned int>(Nan::To<uint32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("height").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.Height = static_cast<unsigned int>(Nan::To<uint32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    return returnValue;
  }

  Local<Value> BitmapBoundsToJsObject(::Windows::Graphics::Imaging::BitmapBounds value) {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    Nan::Set(obj, Nan::New<String>("x").ToLocalChecked(), Nan::New<Integer>(value.X));
    Nan::Set(obj, Nan::New<String>("y").ToLocalChecked(), Nan::New<Integer>(value.Y));
    Nan::Set(obj, Nan::New<String>("width").ToLocalChecked(), Nan::New<Integer>(value.Width));
    Nan::Set(obj, Nan::New<String>("height").ToLocalChecked(), Nan::New<Integer>(value.Height));

    return scope.Escape(obj);
  }

  class MediaProcessingTriggerDetails : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaProcessingTriggerDetails").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("arguments").ToLocalChecked(), ArgumentsGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaProcessingTriggerDetails").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaProcessingTriggerDetails(::Windows::Media::MediaProcessingTriggerDetails^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::MediaProcessingTriggerDetails^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaProcessingTriggerDetails^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::MediaProcessingTriggerDetails^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaProcessingTriggerDetails *wrapperInstance = new MediaProcessingTriggerDetails(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaProcessingTriggerDetails^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::MediaProcessingTriggerDetails^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::MediaProcessingTriggerDetails^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaProcessingTriggerDetails(winRtInstance));
    }





    static void ArgumentsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaProcessingTriggerDetails^>(info.This())) {
        return;
      }

      MediaProcessingTriggerDetails *wrapper = MediaProcessingTriggerDetails::Unwrap<MediaProcessingTriggerDetails>(info.This());

      try  {
        ::Windows::Foundation::Collections::ValueSet^ result = wrapper->_instance->Arguments;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "ValueSet", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::MediaProcessingTriggerDetails^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaProcessingTriggerDetails(::Windows::Media::MediaProcessingTriggerDetails^ wintRtInstance);
      friend ::Windows::Media::MediaProcessingTriggerDetails^ UnwrapMediaProcessingTriggerDetails(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaProcessingTriggerDetails::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaProcessingTriggerDetails(::Windows::Media::MediaProcessingTriggerDetails^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaProcessingTriggerDetails::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::MediaProcessingTriggerDetails^ UnwrapMediaProcessingTriggerDetails(Local<Value> value) {
     return MediaProcessingTriggerDetails::Unwrap<MediaProcessingTriggerDetails>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaProcessingTriggerDetails(Local<Object> exports) {
    MediaProcessingTriggerDetails::Init(exports);
  }

  class IMediaFrame : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IMediaFrame").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("duration").ToLocalChecked(), DurationGetter, DurationSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedProperties").ToLocalChecked(), ExtendedPropertiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isDiscontinuous").ToLocalChecked(), IsDiscontinuousGetter, IsDiscontinuousSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isReadOnly").ToLocalChecked(), IsReadOnlyGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("relativeTime").ToLocalChecked(), RelativeTimeGetter, RelativeTimeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("systemRelativeTime").ToLocalChecked(), SystemRelativeTimeGetter, SystemRelativeTimeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("type").ToLocalChecked(), TypeGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IMediaFrame").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IMediaFrame(::Windows::Media::IMediaFrame^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::IMediaFrame^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaFrame^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::IMediaFrame^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IMediaFrame *wrapperInstance = new IMediaFrame(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaFrame^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::IMediaFrame^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::IMediaFrame^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIMediaFrame(winRtInstance));
    }





    static void DurationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaFrame^>(info.This())) {
        return;
      }

      IMediaFrame *wrapper = IMediaFrame::Unwrap<IMediaFrame>(info.This());

      try  {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->Duration;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DurationSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaFrame^>(info.This())) {
        return;
      }

      IMediaFrame *wrapper = IMediaFrame::Unwrap<IMediaFrame>(info.This());

      try {

        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::TimeSpan>(NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0)));

        wrapper->_instance->Duration = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void ExtendedPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaFrame^>(info.This())) {
        return;
      }

      IMediaFrame *wrapper = IMediaFrame::Unwrap<IMediaFrame>(info.This());

      try  {
        ::Windows::Foundation::Collections::IPropertySet^ result = wrapper->_instance->ExtendedProperties;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IPropertySet", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsDiscontinuousGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaFrame^>(info.This())) {
        return;
      }

      IMediaFrame *wrapper = IMediaFrame::Unwrap<IMediaFrame>(info.This());

      try  {
        bool result = wrapper->_instance->IsDiscontinuous;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsDiscontinuousSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaFrame^>(info.This())) {
        return;
      }

      IMediaFrame *wrapper = IMediaFrame::Unwrap<IMediaFrame>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsDiscontinuous = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsReadOnlyGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaFrame^>(info.This())) {
        return;
      }

      IMediaFrame *wrapper = IMediaFrame::Unwrap<IMediaFrame>(info.This());

      try  {
        bool result = wrapper->_instance->IsReadOnly;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void RelativeTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaFrame^>(info.This())) {
        return;
      }

      IMediaFrame *wrapper = IMediaFrame::Unwrap<IMediaFrame>(info.This());

      try  {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->RelativeTime;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void RelativeTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaFrame^>(info.This())) {
        return;
      }

      IMediaFrame *wrapper = IMediaFrame::Unwrap<IMediaFrame>(info.This());

      try {

        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::TimeSpan>(NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0)));

        wrapper->_instance->RelativeTime = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void SystemRelativeTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaFrame^>(info.This())) {
        return;
      }

      IMediaFrame *wrapper = IMediaFrame::Unwrap<IMediaFrame>(info.This());

      try  {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->SystemRelativeTime;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SystemRelativeTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaFrame^>(info.This())) {
        return;
      }

      IMediaFrame *wrapper = IMediaFrame::Unwrap<IMediaFrame>(info.This());

      try {

        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::TimeSpan>(NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0)));

        wrapper->_instance->SystemRelativeTime = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void TypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaFrame^>(info.This())) {
        return;
      }

      IMediaFrame *wrapper = IMediaFrame::Unwrap<IMediaFrame>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Type;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::IMediaFrame^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIMediaFrame(::Windows::Media::IMediaFrame^ wintRtInstance);
      friend ::Windows::Media::IMediaFrame^ UnwrapIMediaFrame(Local<Value> value);
  };

  Persistent<FunctionTemplate> IMediaFrame::s_constructorTemplate;

  v8::Local<v8::Value> WrapIMediaFrame(::Windows::Media::IMediaFrame^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IMediaFrame::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::IMediaFrame^ UnwrapIMediaFrame(Local<Value> value) {
     return IMediaFrame::Unwrap<IMediaFrame>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIMediaFrame(Local<Object> exports) {
    IMediaFrame::Init(exports);
  }

  class VideoFrame : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("VideoFrame").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;

          
            Nan::SetPrototypeMethod(localRef, "close", Close);
          

          
            Nan::SetPrototypeMethod(localRef, "copyToAsync", CopyToAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("systemRelativeTime").ToLocalChecked(), SystemRelativeTimeGetter, SystemRelativeTimeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("relativeTime").ToLocalChecked(), RelativeTimeGetter, RelativeTimeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isDiscontinuous").ToLocalChecked(), IsDiscontinuousGetter, IsDiscontinuousSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("duration").ToLocalChecked(), DurationGetter, DurationSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedProperties").ToLocalChecked(), ExtendedPropertiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isReadOnly").ToLocalChecked(), IsReadOnlyGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("type").ToLocalChecked(), TypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("direct3DSurface").ToLocalChecked(), Direct3DSurfaceGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("softwareBitmap").ToLocalChecked(), SoftwareBitmapGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "createAsDirect3D11SurfaceBacked", CreateAsDirect3D11SurfaceBacked);
        Nan::SetMethod(constructor, "createWithSoftwareBitmap", CreateWithSoftwareBitmap);
        Nan::SetMethod(constructor, "createWithDirect3D11Surface", CreateWithDirect3D11Surface);


        Nan::Set(exports, Nan::New<String>("VideoFrame").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      VideoFrame(::Windows::Media::VideoFrame^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::VideoFrame^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::VideoFrame^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && info[2]->IsInt32())
      {
        try {
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg0 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          int arg1 = static_cast<int>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          int arg2 = static_cast<int>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Media::VideoFrame(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && info[2]->IsInt32()
        && info[3]->IsInt32())
      {
        try {
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg0 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          int arg1 = static_cast<int>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          int arg2 = static_cast<int>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapAlphaMode arg3 = static_cast<::Windows::Graphics::Imaging::BitmapAlphaMode>(Nan::To<int32_t>(info[3]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Media::VideoFrame(arg0,arg1,arg2,arg3);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      VideoFrame *wrapperInstance = new VideoFrame(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::VideoFrame^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::VideoFrame^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapVideoFrame(winRtInstance));
    }

    static void CopyToAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      VideoFrame *wrapper = VideoFrame::Unwrap<VideoFrame>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info[0]))
      {
        try
        {
          ::Windows::Media::VideoFrame^ arg0 = UnwrapVideoFrame(info[0]);
          
          op = wrapper->_instance->CopyToAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info[0])
        && IsBitmapBoundsJsObject(info[1])
        && IsBitmapBoundsJsObject(info[2]))
      {
        try
        {
          ::Windows::Media::VideoFrame^ arg0 = UnwrapVideoFrame(info[0]);
          ::Platform::IBox<::Windows::Graphics::Imaging::BitmapBounds>^ arg1 = ref new ::Platform::Box<::Windows::Graphics::Imaging::BitmapBounds>(BitmapBoundsFromJsObject(info[1]));
          ::Platform::IBox<::Windows::Graphics::Imaging::BitmapBounds>^ arg2 = ref new ::Platform::Box<::Windows::Graphics::Imaging::BitmapBounds>(BitmapBoundsFromJsObject(info[2]));
          
          op = wrapper->_instance->CopyToAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }


    static void Close(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info.This())) {
        return;
      }

      VideoFrame *wrapper = VideoFrame::Unwrap<VideoFrame>(info.This());

      if (info.Length() == 0) {
        try {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      } else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void CreateAsDirect3D11SurfaceBacked(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Graphics::DirectX::DirectXPixelFormat arg0 = static_cast<::Windows::Graphics::DirectX::DirectXPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          int arg1 = static_cast<int>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          int arg2 = static_cast<int>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          ::Windows::Media::VideoFrame^ result;
          result = ::Windows::Media::VideoFrame::CreateAsDirect3D11SurfaceBacked(arg0, arg1, arg2);
          info.GetReturnValue().Set(WrapVideoFrame(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && info[2]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice^>(info[3]))
      {
        try
        {
          ::Windows::Graphics::DirectX::DirectXPixelFormat arg0 = static_cast<::Windows::Graphics::DirectX::DirectXPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          int arg1 = static_cast<int>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          int arg2 = static_cast<int>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          ::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice^ arg3 = dynamic_cast<::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice^>(NodeRT::Utils::GetObjectInstance(info[3]));
          
          ::Windows::Media::VideoFrame^ result;
          result = ::Windows::Media::VideoFrame::CreateAsDirect3D11SurfaceBacked(arg0, arg1, arg2, arg3);
          info.GetReturnValue().Set(WrapVideoFrame(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void CreateWithSoftwareBitmap(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info[0]))
      {
        try
        {
          ::Windows::Graphics::Imaging::SoftwareBitmap^ arg0 = dynamic_cast<::Windows::Graphics::Imaging::SoftwareBitmap^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Media::VideoFrame^ result;
          result = ::Windows::Media::VideoFrame::CreateWithSoftwareBitmap(arg0);
          info.GetReturnValue().Set(WrapVideoFrame(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void CreateWithDirect3D11Surface(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(info[0]))
      {
        try
        {
          ::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^ arg0 = dynamic_cast<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Media::VideoFrame^ result;
          result = ::Windows::Media::VideoFrame::CreateWithDirect3D11Surface(arg0);
          info.GetReturnValue().Set(WrapVideoFrame(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void SystemRelativeTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info.This())) {
        return;
      }

      VideoFrame *wrapper = VideoFrame::Unwrap<VideoFrame>(info.This());

      try  {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->SystemRelativeTime;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SystemRelativeTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info.This())) {
        return;
      }

      VideoFrame *wrapper = VideoFrame::Unwrap<VideoFrame>(info.This());

      try {

        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::TimeSpan>(NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0)));

        wrapper->_instance->SystemRelativeTime = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void RelativeTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info.This())) {
        return;
      }

      VideoFrame *wrapper = VideoFrame::Unwrap<VideoFrame>(info.This());

      try  {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->RelativeTime;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void RelativeTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info.This())) {
        return;
      }

      VideoFrame *wrapper = VideoFrame::Unwrap<VideoFrame>(info.This());

      try {

        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::TimeSpan>(NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0)));

        wrapper->_instance->RelativeTime = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsDiscontinuousGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info.This())) {
        return;
      }

      VideoFrame *wrapper = VideoFrame::Unwrap<VideoFrame>(info.This());

      try  {
        bool result = wrapper->_instance->IsDiscontinuous;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsDiscontinuousSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info.This())) {
        return;
      }

      VideoFrame *wrapper = VideoFrame::Unwrap<VideoFrame>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsDiscontinuous = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void DurationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info.This())) {
        return;
      }

      VideoFrame *wrapper = VideoFrame::Unwrap<VideoFrame>(info.This());

      try  {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->Duration;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DurationSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info.This())) {
        return;
      }

      VideoFrame *wrapper = VideoFrame::Unwrap<VideoFrame>(info.This());

      try {

        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::TimeSpan>(NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0)));

        wrapper->_instance->Duration = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void ExtendedPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info.This())) {
        return;
      }

      VideoFrame *wrapper = VideoFrame::Unwrap<VideoFrame>(info.This());

      try  {
        ::Windows::Foundation::Collections::IPropertySet^ result = wrapper->_instance->ExtendedProperties;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IPropertySet", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsReadOnlyGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info.This())) {
        return;
      }

      VideoFrame *wrapper = VideoFrame::Unwrap<VideoFrame>(info.This());

      try  {
        bool result = wrapper->_instance->IsReadOnly;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info.This())) {
        return;
      }

      VideoFrame *wrapper = VideoFrame::Unwrap<VideoFrame>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Type;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void Direct3DSurfaceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info.This())) {
        return;
      }

      VideoFrame *wrapper = VideoFrame::Unwrap<VideoFrame>(info.This());

      try  {
        ::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^ result = wrapper->_instance->Direct3DSurface;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Graphics.DirectX.Direct3D11", "IDirect3DSurface", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SoftwareBitmapGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoFrame^>(info.This())) {
        return;
      }

      VideoFrame *wrapper = VideoFrame::Unwrap<VideoFrame>(info.This());

      try  {
        ::Windows::Graphics::Imaging::SoftwareBitmap^ result = wrapper->_instance->SoftwareBitmap;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Graphics.Imaging", "SoftwareBitmap", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::VideoFrame^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapVideoFrame(::Windows::Media::VideoFrame^ wintRtInstance);
      friend ::Windows::Media::VideoFrame^ UnwrapVideoFrame(Local<Value> value);
  };

  Persistent<FunctionTemplate> VideoFrame::s_constructorTemplate;

  v8::Local<v8::Value> WrapVideoFrame(::Windows::Media::VideoFrame^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(VideoFrame::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::VideoFrame^ UnwrapVideoFrame(Local<Value> value) {
     return VideoFrame::Unwrap<VideoFrame>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitVideoFrame(Local<Object> exports) {
    VideoFrame::Init(exports);
  }

  class AudioBuffer : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("AudioBuffer").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "createReference", CreateReference);
            Nan::SetPrototypeMethod(localRef, "close", Close);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("length").ToLocalChecked(), LengthGetter, LengthSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("capacity").ToLocalChecked(), CapacityGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("AudioBuffer").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      AudioBuffer(::Windows::Media::AudioBuffer^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::AudioBuffer^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioBuffer^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::AudioBuffer^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      AudioBuffer *wrapperInstance = new AudioBuffer(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioBuffer^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::AudioBuffer^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::AudioBuffer^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapAudioBuffer(winRtInstance));
    }


    static void CreateReference(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioBuffer^>(info.This())) {
        return;
      }

      AudioBuffer *wrapper = AudioBuffer::Unwrap<AudioBuffer>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::IMemoryBufferReference^ result;
          result = wrapper->_instance->CreateReference();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "IMemoryBufferReference", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void Close(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioBuffer^>(info.This())) {
        return;
      }

      AudioBuffer *wrapper = AudioBuffer::Unwrap<AudioBuffer>(info.This());

      if (info.Length() == 0) {
        try {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      } else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void LengthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioBuffer^>(info.This())) {
        return;
      }

      AudioBuffer *wrapper = AudioBuffer::Unwrap<AudioBuffer>(info.This());

      try  {
        unsigned int result = wrapper->_instance->Length;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LengthSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsUint32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioBuffer^>(info.This())) {
        return;
      }

      AudioBuffer *wrapper = AudioBuffer::Unwrap<AudioBuffer>(info.This());

      try {

        unsigned int winRtValue = static_cast<unsigned int>(Nan::To<uint32_t>(value).FromMaybe(0));

        wrapper->_instance->Length = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void CapacityGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioBuffer^>(info.This())) {
        return;
      }

      AudioBuffer *wrapper = AudioBuffer::Unwrap<AudioBuffer>(info.This());

      try  {
        unsigned int result = wrapper->_instance->Capacity;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::AudioBuffer^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapAudioBuffer(::Windows::Media::AudioBuffer^ wintRtInstance);
      friend ::Windows::Media::AudioBuffer^ UnwrapAudioBuffer(Local<Value> value);
  };

  Persistent<FunctionTemplate> AudioBuffer::s_constructorTemplate;

  v8::Local<v8::Value> WrapAudioBuffer(::Windows::Media::AudioBuffer^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(AudioBuffer::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::AudioBuffer^ UnwrapAudioBuffer(Local<Value> value) {
     return AudioBuffer::Unwrap<AudioBuffer>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitAudioBuffer(Local<Object> exports) {
    AudioBuffer::Init(exports);
  }

  class AudioFrame : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("AudioFrame").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "lockBuffer", LockBuffer);
            Nan::SetPrototypeMethod(localRef, "close", Close);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("systemRelativeTime").ToLocalChecked(), SystemRelativeTimeGetter, SystemRelativeTimeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("relativeTime").ToLocalChecked(), RelativeTimeGetter, RelativeTimeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isDiscontinuous").ToLocalChecked(), IsDiscontinuousGetter, IsDiscontinuousSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("duration").ToLocalChecked(), DurationGetter, DurationSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedProperties").ToLocalChecked(), ExtendedPropertiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isReadOnly").ToLocalChecked(), IsReadOnlyGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("type").ToLocalChecked(), TypeGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("AudioFrame").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      AudioFrame(::Windows::Media::AudioFrame^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::AudioFrame^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioFrame^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::AudioFrame^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Media::AudioFrame(arg0);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      AudioFrame *wrapperInstance = new AudioFrame(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioFrame^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::AudioFrame^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::AudioFrame^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapAudioFrame(winRtInstance));
    }


    static void LockBuffer(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioFrame^>(info.This())) {
        return;
      }

      AudioFrame *wrapper = AudioFrame::Unwrap<AudioFrame>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Media::AudioBufferAccessMode arg0 = static_cast<::Windows::Media::AudioBufferAccessMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Media::AudioBuffer^ result;
          result = wrapper->_instance->LockBuffer(arg0);
          info.GetReturnValue().Set(WrapAudioBuffer(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void Close(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioFrame^>(info.This())) {
        return;
      }

      AudioFrame *wrapper = AudioFrame::Unwrap<AudioFrame>(info.This());

      if (info.Length() == 0) {
        try {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      } else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void SystemRelativeTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioFrame^>(info.This())) {
        return;
      }

      AudioFrame *wrapper = AudioFrame::Unwrap<AudioFrame>(info.This());

      try  {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->SystemRelativeTime;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SystemRelativeTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioFrame^>(info.This())) {
        return;
      }

      AudioFrame *wrapper = AudioFrame::Unwrap<AudioFrame>(info.This());

      try {

        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::TimeSpan>(NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0)));

        wrapper->_instance->SystemRelativeTime = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void RelativeTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioFrame^>(info.This())) {
        return;
      }

      AudioFrame *wrapper = AudioFrame::Unwrap<AudioFrame>(info.This());

      try  {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->RelativeTime;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void RelativeTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioFrame^>(info.This())) {
        return;
      }

      AudioFrame *wrapper = AudioFrame::Unwrap<AudioFrame>(info.This());

      try {

        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::TimeSpan>(NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0)));

        wrapper->_instance->RelativeTime = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsDiscontinuousGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioFrame^>(info.This())) {
        return;
      }

      AudioFrame *wrapper = AudioFrame::Unwrap<AudioFrame>(info.This());

      try  {
        bool result = wrapper->_instance->IsDiscontinuous;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsDiscontinuousSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioFrame^>(info.This())) {
        return;
      }

      AudioFrame *wrapper = AudioFrame::Unwrap<AudioFrame>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsDiscontinuous = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void DurationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioFrame^>(info.This())) {
        return;
      }

      AudioFrame *wrapper = AudioFrame::Unwrap<AudioFrame>(info.This());

      try  {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->Duration;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DurationSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioFrame^>(info.This())) {
        return;
      }

      AudioFrame *wrapper = AudioFrame::Unwrap<AudioFrame>(info.This());

      try {

        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::TimeSpan>(NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0)));

        wrapper->_instance->Duration = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void ExtendedPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioFrame^>(info.This())) {
        return;
      }

      AudioFrame *wrapper = AudioFrame::Unwrap<AudioFrame>(info.This());

      try  {
        ::Windows::Foundation::Collections::IPropertySet^ result = wrapper->_instance->ExtendedProperties;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IPropertySet", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsReadOnlyGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioFrame^>(info.This())) {
        return;
      }

      AudioFrame *wrapper = AudioFrame::Unwrap<AudioFrame>(info.This());

      try  {
        bool result = wrapper->_instance->IsReadOnly;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AudioFrame^>(info.This())) {
        return;
      }

      AudioFrame *wrapper = AudioFrame::Unwrap<AudioFrame>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Type;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::AudioFrame^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapAudioFrame(::Windows::Media::AudioFrame^ wintRtInstance);
      friend ::Windows::Media::AudioFrame^ UnwrapAudioFrame(Local<Value> value);
  };

  Persistent<FunctionTemplate> AudioFrame::s_constructorTemplate;

  v8::Local<v8::Value> WrapAudioFrame(::Windows::Media::AudioFrame^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(AudioFrame::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::AudioFrame^ UnwrapAudioFrame(Local<Value> value) {
     return AudioFrame::Unwrap<AudioFrame>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitAudioFrame(Local<Object> exports) {
    AudioFrame::Init(exports);
  }

  class IMediaMarker : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IMediaMarker").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("mediaMarkerType").ToLocalChecked(), MediaMarkerTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("text").ToLocalChecked(), TextGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("time").ToLocalChecked(), TimeGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IMediaMarker").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IMediaMarker(::Windows::Media::IMediaMarker^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::IMediaMarker^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaMarker^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::IMediaMarker^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IMediaMarker *wrapperInstance = new IMediaMarker(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaMarker^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::IMediaMarker^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::IMediaMarker^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIMediaMarker(winRtInstance));
    }





    static void MediaMarkerTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaMarker^>(info.This())) {
        return;
      }

      IMediaMarker *wrapper = IMediaMarker::Unwrap<IMediaMarker>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->MediaMarkerType;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaMarker^>(info.This())) {
        return;
      }

      IMediaMarker *wrapper = IMediaMarker::Unwrap<IMediaMarker>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Text;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaMarker^>(info.This())) {
        return;
      }

      IMediaMarker *wrapper = IMediaMarker::Unwrap<IMediaMarker>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->Time;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::IMediaMarker^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIMediaMarker(::Windows::Media::IMediaMarker^ wintRtInstance);
      friend ::Windows::Media::IMediaMarker^ UnwrapIMediaMarker(Local<Value> value);
  };

  Persistent<FunctionTemplate> IMediaMarker::s_constructorTemplate;

  v8::Local<v8::Value> WrapIMediaMarker(::Windows::Media::IMediaMarker^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IMediaMarker::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::IMediaMarker^ UnwrapIMediaMarker(Local<Value> value) {
     return IMediaMarker::Unwrap<IMediaMarker>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIMediaMarker(Local<Object> exports) {
    IMediaMarker::Init(exports);
  }

  class IMediaMarkers : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IMediaMarkers").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("markers").ToLocalChecked(), MarkersGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IMediaMarkers").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IMediaMarkers(::Windows::Media::IMediaMarkers^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::IMediaMarkers^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaMarkers^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::IMediaMarkers^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IMediaMarkers *wrapperInstance = new IMediaMarkers(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaMarkers^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::IMediaMarkers^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::IMediaMarkers^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIMediaMarkers(winRtInstance));
    }





    static void MarkersGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaMarkers^>(info.This())) {
        return;
      }

      IMediaMarkers *wrapper = IMediaMarkers::Unwrap<IMediaMarkers>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Media::IMediaMarker^>^ result = wrapper->_instance->Markers;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Media::IMediaMarker^>::CreateVectorViewWrapper(result, 
            [](::Windows::Media::IMediaMarker^ val) -> Local<Value> {
              return WrapIMediaMarker(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaMarker^>(value);
            },
            [](Local<Value> value) -> ::Windows::Media::IMediaMarker^ {
              return UnwrapIMediaMarker(value);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::IMediaMarkers^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIMediaMarkers(::Windows::Media::IMediaMarkers^ wintRtInstance);
      friend ::Windows::Media::IMediaMarkers^ UnwrapIMediaMarkers(Local<Value> value);
  };

  Persistent<FunctionTemplate> IMediaMarkers::s_constructorTemplate;

  v8::Local<v8::Value> WrapIMediaMarkers(::Windows::Media::IMediaMarkers^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IMediaMarkers::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::IMediaMarkers^ UnwrapIMediaMarkers(Local<Value> value) {
     return IMediaMarkers::Unwrap<IMediaMarkers>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIMediaMarkers(Local<Object> exports) {
    IMediaMarkers::Init(exports);
  }

  class MediaMarkerTypes : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaMarkerTypes").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);






        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetAccessor(constructor, Nan::New<String>("bookmark").ToLocalChecked(), BookmarkGetter);


        Nan::Set(exports, Nan::New<String>("MediaMarkerTypes").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaMarkerTypes(::Windows::Media::MediaMarkerTypes^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::MediaMarkerTypes^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaMarkerTypes^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::MediaMarkerTypes^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaMarkerTypes *wrapperInstance = new MediaMarkerTypes(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaMarkerTypes^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::MediaMarkerTypes^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::MediaMarkerTypes^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaMarkerTypes(winRtInstance));
    }







    static void BookmarkGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Media::MediaMarkerTypes::Bookmark;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    private:
      ::Windows::Media::MediaMarkerTypes^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaMarkerTypes(::Windows::Media::MediaMarkerTypes^ wintRtInstance);
      friend ::Windows::Media::MediaMarkerTypes^ UnwrapMediaMarkerTypes(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaMarkerTypes::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaMarkerTypes(::Windows::Media::MediaMarkerTypes^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaMarkerTypes::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::MediaMarkerTypes^ UnwrapMediaMarkerTypes(Local<Value> value) {
     return MediaMarkerTypes::Unwrap<MediaMarkerTypes>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaMarkerTypes(Local<Object> exports) {
    MediaMarkerTypes::Init(exports);
  }

  class SystemMediaTransportControlsTimelineProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SystemMediaTransportControlsTimelineProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("startTime").ToLocalChecked(), StartTimeGetter, StartTimeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("position").ToLocalChecked(), PositionGetter, PositionSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("minSeekTime").ToLocalChecked(), MinSeekTimeGetter, MinSeekTimeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("maxSeekTime").ToLocalChecked(), MaxSeekTimeGetter, MaxSeekTimeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("endTime").ToLocalChecked(), EndTimeGetter, EndTimeSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("SystemMediaTransportControlsTimelineProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SystemMediaTransportControlsTimelineProperties(::Windows::Media::SystemMediaTransportControlsTimelineProperties^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::SystemMediaTransportControlsTimelineProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsTimelineProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::SystemMediaTransportControlsTimelineProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try {
          winRtInstance = ref new ::Windows::Media::SystemMediaTransportControlsTimelineProperties();
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SystemMediaTransportControlsTimelineProperties *wrapperInstance = new SystemMediaTransportControlsTimelineProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsTimelineProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::SystemMediaTransportControlsTimelineProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::SystemMediaTransportControlsTimelineProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSystemMediaTransportControlsTimelineProperties(winRtInstance));
    }





    static void StartTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsTimelineProperties^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsTimelineProperties *wrapper = SystemMediaTransportControlsTimelineProperties::Unwrap<SystemMediaTransportControlsTimelineProperties>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->StartTime;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StartTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsTimelineProperties^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsTimelineProperties *wrapper = SystemMediaTransportControlsTimelineProperties::Unwrap<SystemMediaTransportControlsTimelineProperties>(info.This());

      try {

        ::Windows::Foundation::TimeSpan winRtValue = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0));

        wrapper->_instance->StartTime = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void PositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsTimelineProperties^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsTimelineProperties *wrapper = SystemMediaTransportControlsTimelineProperties::Unwrap<SystemMediaTransportControlsTimelineProperties>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->Position;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PositionSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsTimelineProperties^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsTimelineProperties *wrapper = SystemMediaTransportControlsTimelineProperties::Unwrap<SystemMediaTransportControlsTimelineProperties>(info.This());

      try {

        ::Windows::Foundation::TimeSpan winRtValue = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0));

        wrapper->_instance->Position = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void MinSeekTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsTimelineProperties^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsTimelineProperties *wrapper = SystemMediaTransportControlsTimelineProperties::Unwrap<SystemMediaTransportControlsTimelineProperties>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->MinSeekTime;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void MinSeekTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsTimelineProperties^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsTimelineProperties *wrapper = SystemMediaTransportControlsTimelineProperties::Unwrap<SystemMediaTransportControlsTimelineProperties>(info.This());

      try {

        ::Windows::Foundation::TimeSpan winRtValue = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0));

        wrapper->_instance->MinSeekTime = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void MaxSeekTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsTimelineProperties^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsTimelineProperties *wrapper = SystemMediaTransportControlsTimelineProperties::Unwrap<SystemMediaTransportControlsTimelineProperties>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->MaxSeekTime;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void MaxSeekTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsTimelineProperties^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsTimelineProperties *wrapper = SystemMediaTransportControlsTimelineProperties::Unwrap<SystemMediaTransportControlsTimelineProperties>(info.This());

      try {

        ::Windows::Foundation::TimeSpan winRtValue = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0));

        wrapper->_instance->MaxSeekTime = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void EndTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsTimelineProperties^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsTimelineProperties *wrapper = SystemMediaTransportControlsTimelineProperties::Unwrap<SystemMediaTransportControlsTimelineProperties>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->EndTime;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void EndTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsTimelineProperties^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsTimelineProperties *wrapper = SystemMediaTransportControlsTimelineProperties::Unwrap<SystemMediaTransportControlsTimelineProperties>(info.This());

      try {

        ::Windows::Foundation::TimeSpan winRtValue = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0));

        wrapper->_instance->EndTime = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Media::SystemMediaTransportControlsTimelineProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSystemMediaTransportControlsTimelineProperties(::Windows::Media::SystemMediaTransportControlsTimelineProperties^ wintRtInstance);
      friend ::Windows::Media::SystemMediaTransportControlsTimelineProperties^ UnwrapSystemMediaTransportControlsTimelineProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> SystemMediaTransportControlsTimelineProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapSystemMediaTransportControlsTimelineProperties(::Windows::Media::SystemMediaTransportControlsTimelineProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SystemMediaTransportControlsTimelineProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::SystemMediaTransportControlsTimelineProperties^ UnwrapSystemMediaTransportControlsTimelineProperties(Local<Value> value) {
     return SystemMediaTransportControlsTimelineProperties::Unwrap<SystemMediaTransportControlsTimelineProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSystemMediaTransportControlsTimelineProperties(Local<Object> exports) {
    SystemMediaTransportControlsTimelineProperties::Init(exports);
  }

  class MusicDisplayProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MusicDisplayProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("title").ToLocalChecked(), TitleGetter, TitleSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("artist").ToLocalChecked(), ArtistGetter, ArtistSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("albumArtist").ToLocalChecked(), AlbumArtistGetter, AlbumArtistSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("trackNumber").ToLocalChecked(), TrackNumberGetter, TrackNumberSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("albumTitle").ToLocalChecked(), AlbumTitleGetter, AlbumTitleSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("genres").ToLocalChecked(), GenresGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("albumTrackCount").ToLocalChecked(), AlbumTrackCountGetter, AlbumTrackCountSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MusicDisplayProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MusicDisplayProperties(::Windows::Media::MusicDisplayProperties^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::MusicDisplayProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MusicDisplayProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::MusicDisplayProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MusicDisplayProperties *wrapperInstance = new MusicDisplayProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MusicDisplayProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::MusicDisplayProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::MusicDisplayProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMusicDisplayProperties(winRtInstance));
    }





    static void TitleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MusicDisplayProperties^>(info.This())) {
        return;
      }

      MusicDisplayProperties *wrapper = MusicDisplayProperties::Unwrap<MusicDisplayProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Title;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TitleSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MusicDisplayProperties^>(info.This())) {
        return;
      }

      MusicDisplayProperties *wrapper = MusicDisplayProperties::Unwrap<MusicDisplayProperties>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->Title = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void ArtistGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MusicDisplayProperties^>(info.This())) {
        return;
      }

      MusicDisplayProperties *wrapper = MusicDisplayProperties::Unwrap<MusicDisplayProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Artist;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ArtistSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MusicDisplayProperties^>(info.This())) {
        return;
      }

      MusicDisplayProperties *wrapper = MusicDisplayProperties::Unwrap<MusicDisplayProperties>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->Artist = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void AlbumArtistGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MusicDisplayProperties^>(info.This())) {
        return;
      }

      MusicDisplayProperties *wrapper = MusicDisplayProperties::Unwrap<MusicDisplayProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->AlbumArtist;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AlbumArtistSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MusicDisplayProperties^>(info.This())) {
        return;
      }

      MusicDisplayProperties *wrapper = MusicDisplayProperties::Unwrap<MusicDisplayProperties>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->AlbumArtist = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void TrackNumberGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MusicDisplayProperties^>(info.This())) {
        return;
      }

      MusicDisplayProperties *wrapper = MusicDisplayProperties::Unwrap<MusicDisplayProperties>(info.This());

      try  {
        unsigned int result = wrapper->_instance->TrackNumber;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TrackNumberSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsUint32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MusicDisplayProperties^>(info.This())) {
        return;
      }

      MusicDisplayProperties *wrapper = MusicDisplayProperties::Unwrap<MusicDisplayProperties>(info.This());

      try {

        unsigned int winRtValue = static_cast<unsigned int>(Nan::To<uint32_t>(value).FromMaybe(0));

        wrapper->_instance->TrackNumber = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void AlbumTitleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MusicDisplayProperties^>(info.This())) {
        return;
      }

      MusicDisplayProperties *wrapper = MusicDisplayProperties::Unwrap<MusicDisplayProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->AlbumTitle;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AlbumTitleSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MusicDisplayProperties^>(info.This())) {
        return;
      }

      MusicDisplayProperties *wrapper = MusicDisplayProperties::Unwrap<MusicDisplayProperties>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->AlbumTitle = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void GenresGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MusicDisplayProperties^>(info.This())) {
        return;
      }

      MusicDisplayProperties *wrapper = MusicDisplayProperties::Unwrap<MusicDisplayProperties>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVector<::Platform::String^>^ result = wrapper->_instance->Genres;
        info.GetReturnValue().Set(NodeRT::Collections::VectorWrapper<::Platform::String^>::CreateVectorWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AlbumTrackCountGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MusicDisplayProperties^>(info.This())) {
        return;
      }

      MusicDisplayProperties *wrapper = MusicDisplayProperties::Unwrap<MusicDisplayProperties>(info.This());

      try  {
        unsigned int result = wrapper->_instance->AlbumTrackCount;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AlbumTrackCountSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsUint32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MusicDisplayProperties^>(info.This())) {
        return;
      }

      MusicDisplayProperties *wrapper = MusicDisplayProperties::Unwrap<MusicDisplayProperties>(info.This());

      try {

        unsigned int winRtValue = static_cast<unsigned int>(Nan::To<uint32_t>(value).FromMaybe(0));

        wrapper->_instance->AlbumTrackCount = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Media::MusicDisplayProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMusicDisplayProperties(::Windows::Media::MusicDisplayProperties^ wintRtInstance);
      friend ::Windows::Media::MusicDisplayProperties^ UnwrapMusicDisplayProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> MusicDisplayProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapMusicDisplayProperties(::Windows::Media::MusicDisplayProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MusicDisplayProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::MusicDisplayProperties^ UnwrapMusicDisplayProperties(Local<Value> value) {
     return MusicDisplayProperties::Unwrap<MusicDisplayProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMusicDisplayProperties(Local<Object> exports) {
    MusicDisplayProperties::Init(exports);
  }

  class VideoDisplayProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("VideoDisplayProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("title").ToLocalChecked(), TitleGetter, TitleSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("subtitle").ToLocalChecked(), SubtitleGetter, SubtitleSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("genres").ToLocalChecked(), GenresGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("VideoDisplayProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      VideoDisplayProperties(::Windows::Media::VideoDisplayProperties^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::VideoDisplayProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoDisplayProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::VideoDisplayProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      VideoDisplayProperties *wrapperInstance = new VideoDisplayProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoDisplayProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::VideoDisplayProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::VideoDisplayProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapVideoDisplayProperties(winRtInstance));
    }





    static void TitleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoDisplayProperties^>(info.This())) {
        return;
      }

      VideoDisplayProperties *wrapper = VideoDisplayProperties::Unwrap<VideoDisplayProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Title;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TitleSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoDisplayProperties^>(info.This())) {
        return;
      }

      VideoDisplayProperties *wrapper = VideoDisplayProperties::Unwrap<VideoDisplayProperties>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->Title = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void SubtitleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoDisplayProperties^>(info.This())) {
        return;
      }

      VideoDisplayProperties *wrapper = VideoDisplayProperties::Unwrap<VideoDisplayProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Subtitle;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SubtitleSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoDisplayProperties^>(info.This())) {
        return;
      }

      VideoDisplayProperties *wrapper = VideoDisplayProperties::Unwrap<VideoDisplayProperties>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->Subtitle = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void GenresGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoDisplayProperties^>(info.This())) {
        return;
      }

      VideoDisplayProperties *wrapper = VideoDisplayProperties::Unwrap<VideoDisplayProperties>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVector<::Platform::String^>^ result = wrapper->_instance->Genres;
        info.GetReturnValue().Set(NodeRT::Collections::VectorWrapper<::Platform::String^>::CreateVectorWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::VideoDisplayProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapVideoDisplayProperties(::Windows::Media::VideoDisplayProperties^ wintRtInstance);
      friend ::Windows::Media::VideoDisplayProperties^ UnwrapVideoDisplayProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> VideoDisplayProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapVideoDisplayProperties(::Windows::Media::VideoDisplayProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(VideoDisplayProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::VideoDisplayProperties^ UnwrapVideoDisplayProperties(Local<Value> value) {
     return VideoDisplayProperties::Unwrap<VideoDisplayProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitVideoDisplayProperties(Local<Object> exports) {
    VideoDisplayProperties::Init(exports);
  }

  class ImageDisplayProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("ImageDisplayProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("title").ToLocalChecked(), TitleGetter, TitleSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("subtitle").ToLocalChecked(), SubtitleGetter, SubtitleSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("ImageDisplayProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      ImageDisplayProperties(::Windows::Media::ImageDisplayProperties^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::ImageDisplayProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::ImageDisplayProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::ImageDisplayProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ImageDisplayProperties *wrapperInstance = new ImageDisplayProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::ImageDisplayProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::ImageDisplayProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::ImageDisplayProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapImageDisplayProperties(winRtInstance));
    }





    static void TitleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::ImageDisplayProperties^>(info.This())) {
        return;
      }

      ImageDisplayProperties *wrapper = ImageDisplayProperties::Unwrap<ImageDisplayProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Title;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TitleSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::ImageDisplayProperties^>(info.This())) {
        return;
      }

      ImageDisplayProperties *wrapper = ImageDisplayProperties::Unwrap<ImageDisplayProperties>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->Title = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void SubtitleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::ImageDisplayProperties^>(info.This())) {
        return;
      }

      ImageDisplayProperties *wrapper = ImageDisplayProperties::Unwrap<ImageDisplayProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Subtitle;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SubtitleSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::ImageDisplayProperties^>(info.This())) {
        return;
      }

      ImageDisplayProperties *wrapper = ImageDisplayProperties::Unwrap<ImageDisplayProperties>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->Subtitle = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Media::ImageDisplayProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapImageDisplayProperties(::Windows::Media::ImageDisplayProperties^ wintRtInstance);
      friend ::Windows::Media::ImageDisplayProperties^ UnwrapImageDisplayProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> ImageDisplayProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapImageDisplayProperties(::Windows::Media::ImageDisplayProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ImageDisplayProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::ImageDisplayProperties^ UnwrapImageDisplayProperties(Local<Value> value) {
     return ImageDisplayProperties::Unwrap<ImageDisplayProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitImageDisplayProperties(Local<Object> exports) {
    ImageDisplayProperties::Init(exports);
  }

  class SystemMediaTransportControlsDisplayUpdater : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SystemMediaTransportControlsDisplayUpdater").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;

          
            Nan::SetPrototypeMethod(localRef, "clearAll", ClearAll);
            Nan::SetPrototypeMethod(localRef, "update", Update);
          

          
            Nan::SetPrototypeMethod(localRef, "copyFromFileAsync", CopyFromFileAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("type").ToLocalChecked(), TypeGetter, TypeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("thumbnail").ToLocalChecked(), ThumbnailGetter, ThumbnailSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("appMediaId").ToLocalChecked(), AppMediaIdGetter, AppMediaIdSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("imageProperties").ToLocalChecked(), ImagePropertiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("musicProperties").ToLocalChecked(), MusicPropertiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("videoProperties").ToLocalChecked(), VideoPropertiesGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("SystemMediaTransportControlsDisplayUpdater").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SystemMediaTransportControlsDisplayUpdater(::Windows::Media::SystemMediaTransportControlsDisplayUpdater^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::SystemMediaTransportControlsDisplayUpdater^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsDisplayUpdater^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::SystemMediaTransportControlsDisplayUpdater^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SystemMediaTransportControlsDisplayUpdater *wrapperInstance = new SystemMediaTransportControlsDisplayUpdater(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsDisplayUpdater^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::SystemMediaTransportControlsDisplayUpdater^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::SystemMediaTransportControlsDisplayUpdater^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSystemMediaTransportControlsDisplayUpdater(winRtInstance));
    }

    static void CopyFromFileAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsDisplayUpdater^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      SystemMediaTransportControlsDisplayUpdater *wrapper = SystemMediaTransportControlsDisplayUpdater::Unwrap<SystemMediaTransportControlsDisplayUpdater>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;


      if (info.Length() == 3
        && info[0]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info[1]))
      {
        try
        {
          ::Windows::Media::MediaPlaybackType arg0 = static_cast<::Windows::Media::MediaPlaybackType>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Storage::StorageFile^ arg1 = dynamic_cast<::Windows::Storage::StorageFile^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          op = wrapper->_instance->CopyFromFileAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void ClearAll(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsDisplayUpdater^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsDisplayUpdater *wrapper = SystemMediaTransportControlsDisplayUpdater::Unwrap<SystemMediaTransportControlsDisplayUpdater>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->ClearAll();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Update(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsDisplayUpdater^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsDisplayUpdater *wrapper = SystemMediaTransportControlsDisplayUpdater::Unwrap<SystemMediaTransportControlsDisplayUpdater>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Update();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void TypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsDisplayUpdater^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsDisplayUpdater *wrapper = SystemMediaTransportControlsDisplayUpdater::Unwrap<SystemMediaTransportControlsDisplayUpdater>(info.This());

      try  {
        ::Windows::Media::MediaPlaybackType result = wrapper->_instance->Type;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TypeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsDisplayUpdater^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsDisplayUpdater *wrapper = SystemMediaTransportControlsDisplayUpdater::Unwrap<SystemMediaTransportControlsDisplayUpdater>(info.This());

      try {

        ::Windows::Media::MediaPlaybackType winRtValue = static_cast<::Windows::Media::MediaPlaybackType>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->Type = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void ThumbnailGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsDisplayUpdater^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsDisplayUpdater *wrapper = SystemMediaTransportControlsDisplayUpdater::Unwrap<SystemMediaTransportControlsDisplayUpdater>(info.This());

      try  {
        ::Windows::Storage::Streams::RandomAccessStreamReference^ result = wrapper->_instance->Thumbnail;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "RandomAccessStreamReference", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ThumbnailSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamReference^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsDisplayUpdater^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsDisplayUpdater *wrapper = SystemMediaTransportControlsDisplayUpdater::Unwrap<SystemMediaTransportControlsDisplayUpdater>(info.This());

      try {

        ::Windows::Storage::Streams::RandomAccessStreamReference^ winRtValue = dynamic_cast<::Windows::Storage::Streams::RandomAccessStreamReference^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Thumbnail = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void AppMediaIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsDisplayUpdater^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsDisplayUpdater *wrapper = SystemMediaTransportControlsDisplayUpdater::Unwrap<SystemMediaTransportControlsDisplayUpdater>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->AppMediaId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AppMediaIdSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsDisplayUpdater^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsDisplayUpdater *wrapper = SystemMediaTransportControlsDisplayUpdater::Unwrap<SystemMediaTransportControlsDisplayUpdater>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->AppMediaId = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void ImagePropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsDisplayUpdater^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsDisplayUpdater *wrapper = SystemMediaTransportControlsDisplayUpdater::Unwrap<SystemMediaTransportControlsDisplayUpdater>(info.This());

      try  {
        ::Windows::Media::ImageDisplayProperties^ result = wrapper->_instance->ImageProperties;
        info.GetReturnValue().Set(WrapImageDisplayProperties(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void MusicPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsDisplayUpdater^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsDisplayUpdater *wrapper = SystemMediaTransportControlsDisplayUpdater::Unwrap<SystemMediaTransportControlsDisplayUpdater>(info.This());

      try  {
        ::Windows::Media::MusicDisplayProperties^ result = wrapper->_instance->MusicProperties;
        info.GetReturnValue().Set(WrapMusicDisplayProperties(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void VideoPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsDisplayUpdater^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsDisplayUpdater *wrapper = SystemMediaTransportControlsDisplayUpdater::Unwrap<SystemMediaTransportControlsDisplayUpdater>(info.This());

      try  {
        ::Windows::Media::VideoDisplayProperties^ result = wrapper->_instance->VideoProperties;
        info.GetReturnValue().Set(WrapVideoDisplayProperties(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::SystemMediaTransportControlsDisplayUpdater^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSystemMediaTransportControlsDisplayUpdater(::Windows::Media::SystemMediaTransportControlsDisplayUpdater^ wintRtInstance);
      friend ::Windows::Media::SystemMediaTransportControlsDisplayUpdater^ UnwrapSystemMediaTransportControlsDisplayUpdater(Local<Value> value);
  };

  Persistent<FunctionTemplate> SystemMediaTransportControlsDisplayUpdater::s_constructorTemplate;

  v8::Local<v8::Value> WrapSystemMediaTransportControlsDisplayUpdater(::Windows::Media::SystemMediaTransportControlsDisplayUpdater^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SystemMediaTransportControlsDisplayUpdater::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::SystemMediaTransportControlsDisplayUpdater^ UnwrapSystemMediaTransportControlsDisplayUpdater(Local<Value> value) {
     return SystemMediaTransportControlsDisplayUpdater::Unwrap<SystemMediaTransportControlsDisplayUpdater>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSystemMediaTransportControlsDisplayUpdater(Local<Object> exports) {
    SystemMediaTransportControlsDisplayUpdater::Init(exports);
  }

  class SystemMediaTransportControlsButtonPressedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SystemMediaTransportControlsButtonPressedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("button").ToLocalChecked(), ButtonGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("SystemMediaTransportControlsButtonPressedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SystemMediaTransportControlsButtonPressedEventArgs(::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SystemMediaTransportControlsButtonPressedEventArgs *wrapperInstance = new SystemMediaTransportControlsButtonPressedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSystemMediaTransportControlsButtonPressedEventArgs(winRtInstance));
    }





    static void ButtonGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsButtonPressedEventArgs *wrapper = SystemMediaTransportControlsButtonPressedEventArgs::Unwrap<SystemMediaTransportControlsButtonPressedEventArgs>(info.This());

      try  {
        ::Windows::Media::SystemMediaTransportControlsButton result = wrapper->_instance->Button;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSystemMediaTransportControlsButtonPressedEventArgs(::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^ wintRtInstance);
      friend ::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^ UnwrapSystemMediaTransportControlsButtonPressedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> SystemMediaTransportControlsButtonPressedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapSystemMediaTransportControlsButtonPressedEventArgs(::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SystemMediaTransportControlsButtonPressedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^ UnwrapSystemMediaTransportControlsButtonPressedEventArgs(Local<Value> value) {
     return SystemMediaTransportControlsButtonPressedEventArgs::Unwrap<SystemMediaTransportControlsButtonPressedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSystemMediaTransportControlsButtonPressedEventArgs(Local<Object> exports) {
    SystemMediaTransportControlsButtonPressedEventArgs::Init(exports);
  }

  class SystemMediaTransportControlsPropertyChangedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SystemMediaTransportControlsPropertyChangedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("property").ToLocalChecked(), PropertyGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("SystemMediaTransportControlsPropertyChangedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SystemMediaTransportControlsPropertyChangedEventArgs(::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SystemMediaTransportControlsPropertyChangedEventArgs *wrapperInstance = new SystemMediaTransportControlsPropertyChangedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSystemMediaTransportControlsPropertyChangedEventArgs(winRtInstance));
    }





    static void PropertyGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^>(info.This())) {
        return;
      }

      SystemMediaTransportControlsPropertyChangedEventArgs *wrapper = SystemMediaTransportControlsPropertyChangedEventArgs::Unwrap<SystemMediaTransportControlsPropertyChangedEventArgs>(info.This());

      try  {
        ::Windows::Media::SystemMediaTransportControlsProperty result = wrapper->_instance->Property;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSystemMediaTransportControlsPropertyChangedEventArgs(::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^ wintRtInstance);
      friend ::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^ UnwrapSystemMediaTransportControlsPropertyChangedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> SystemMediaTransportControlsPropertyChangedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapSystemMediaTransportControlsPropertyChangedEventArgs(::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SystemMediaTransportControlsPropertyChangedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^ UnwrapSystemMediaTransportControlsPropertyChangedEventArgs(Local<Value> value) {
     return SystemMediaTransportControlsPropertyChangedEventArgs::Unwrap<SystemMediaTransportControlsPropertyChangedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSystemMediaTransportControlsPropertyChangedEventArgs(Local<Object> exports) {
    SystemMediaTransportControlsPropertyChangedEventArgs::Init(exports);
  }

  class PlaybackPositionChangeRequestedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("PlaybackPositionChangeRequestedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("requestedPlaybackPosition").ToLocalChecked(), RequestedPlaybackPositionGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("PlaybackPositionChangeRequestedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      PlaybackPositionChangeRequestedEventArgs(::Windows::Media::PlaybackPositionChangeRequestedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::PlaybackPositionChangeRequestedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::PlaybackPositionChangeRequestedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::PlaybackPositionChangeRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PlaybackPositionChangeRequestedEventArgs *wrapperInstance = new PlaybackPositionChangeRequestedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::PlaybackPositionChangeRequestedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::PlaybackPositionChangeRequestedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::PlaybackPositionChangeRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapPlaybackPositionChangeRequestedEventArgs(winRtInstance));
    }





    static void RequestedPlaybackPositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::PlaybackPositionChangeRequestedEventArgs^>(info.This())) {
        return;
      }

      PlaybackPositionChangeRequestedEventArgs *wrapper = PlaybackPositionChangeRequestedEventArgs::Unwrap<PlaybackPositionChangeRequestedEventArgs>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->RequestedPlaybackPosition;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::PlaybackPositionChangeRequestedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapPlaybackPositionChangeRequestedEventArgs(::Windows::Media::PlaybackPositionChangeRequestedEventArgs^ wintRtInstance);
      friend ::Windows::Media::PlaybackPositionChangeRequestedEventArgs^ UnwrapPlaybackPositionChangeRequestedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> PlaybackPositionChangeRequestedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapPlaybackPositionChangeRequestedEventArgs(::Windows::Media::PlaybackPositionChangeRequestedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PlaybackPositionChangeRequestedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::PlaybackPositionChangeRequestedEventArgs^ UnwrapPlaybackPositionChangeRequestedEventArgs(Local<Value> value) {
     return PlaybackPositionChangeRequestedEventArgs::Unwrap<PlaybackPositionChangeRequestedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPlaybackPositionChangeRequestedEventArgs(Local<Object> exports) {
    PlaybackPositionChangeRequestedEventArgs::Init(exports);
  }

  class PlaybackRateChangeRequestedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("PlaybackRateChangeRequestedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("requestedPlaybackRate").ToLocalChecked(), RequestedPlaybackRateGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("PlaybackRateChangeRequestedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      PlaybackRateChangeRequestedEventArgs(::Windows::Media::PlaybackRateChangeRequestedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::PlaybackRateChangeRequestedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::PlaybackRateChangeRequestedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::PlaybackRateChangeRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PlaybackRateChangeRequestedEventArgs *wrapperInstance = new PlaybackRateChangeRequestedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::PlaybackRateChangeRequestedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::PlaybackRateChangeRequestedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::PlaybackRateChangeRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapPlaybackRateChangeRequestedEventArgs(winRtInstance));
    }





    static void RequestedPlaybackRateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::PlaybackRateChangeRequestedEventArgs^>(info.This())) {
        return;
      }

      PlaybackRateChangeRequestedEventArgs *wrapper = PlaybackRateChangeRequestedEventArgs::Unwrap<PlaybackRateChangeRequestedEventArgs>(info.This());

      try  {
        double result = wrapper->_instance->RequestedPlaybackRate;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::PlaybackRateChangeRequestedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapPlaybackRateChangeRequestedEventArgs(::Windows::Media::PlaybackRateChangeRequestedEventArgs^ wintRtInstance);
      friend ::Windows::Media::PlaybackRateChangeRequestedEventArgs^ UnwrapPlaybackRateChangeRequestedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> PlaybackRateChangeRequestedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapPlaybackRateChangeRequestedEventArgs(::Windows::Media::PlaybackRateChangeRequestedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PlaybackRateChangeRequestedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::PlaybackRateChangeRequestedEventArgs^ UnwrapPlaybackRateChangeRequestedEventArgs(Local<Value> value) {
     return PlaybackRateChangeRequestedEventArgs::Unwrap<PlaybackRateChangeRequestedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPlaybackRateChangeRequestedEventArgs(Local<Object> exports) {
    PlaybackRateChangeRequestedEventArgs::Init(exports);
  }

  class ShuffleEnabledChangeRequestedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("ShuffleEnabledChangeRequestedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("requestedShuffleEnabled").ToLocalChecked(), RequestedShuffleEnabledGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("ShuffleEnabledChangeRequestedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      ShuffleEnabledChangeRequestedEventArgs(::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ShuffleEnabledChangeRequestedEventArgs *wrapperInstance = new ShuffleEnabledChangeRequestedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapShuffleEnabledChangeRequestedEventArgs(winRtInstance));
    }





    static void RequestedShuffleEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^>(info.This())) {
        return;
      }

      ShuffleEnabledChangeRequestedEventArgs *wrapper = ShuffleEnabledChangeRequestedEventArgs::Unwrap<ShuffleEnabledChangeRequestedEventArgs>(info.This());

      try  {
        bool result = wrapper->_instance->RequestedShuffleEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapShuffleEnabledChangeRequestedEventArgs(::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^ wintRtInstance);
      friend ::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^ UnwrapShuffleEnabledChangeRequestedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> ShuffleEnabledChangeRequestedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapShuffleEnabledChangeRequestedEventArgs(::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ShuffleEnabledChangeRequestedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^ UnwrapShuffleEnabledChangeRequestedEventArgs(Local<Value> value) {
     return ShuffleEnabledChangeRequestedEventArgs::Unwrap<ShuffleEnabledChangeRequestedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitShuffleEnabledChangeRequestedEventArgs(Local<Object> exports) {
    ShuffleEnabledChangeRequestedEventArgs::Init(exports);
  }

  class AutoRepeatModeChangeRequestedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("AutoRepeatModeChangeRequestedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("requestedAutoRepeatMode").ToLocalChecked(), RequestedAutoRepeatModeGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("AutoRepeatModeChangeRequestedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      AutoRepeatModeChangeRequestedEventArgs(::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      AutoRepeatModeChangeRequestedEventArgs *wrapperInstance = new AutoRepeatModeChangeRequestedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapAutoRepeatModeChangeRequestedEventArgs(winRtInstance));
    }





    static void RequestedAutoRepeatModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^>(info.This())) {
        return;
      }

      AutoRepeatModeChangeRequestedEventArgs *wrapper = AutoRepeatModeChangeRequestedEventArgs::Unwrap<AutoRepeatModeChangeRequestedEventArgs>(info.This());

      try  {
        ::Windows::Media::MediaPlaybackAutoRepeatMode result = wrapper->_instance->RequestedAutoRepeatMode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapAutoRepeatModeChangeRequestedEventArgs(::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^ wintRtInstance);
      friend ::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^ UnwrapAutoRepeatModeChangeRequestedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> AutoRepeatModeChangeRequestedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapAutoRepeatModeChangeRequestedEventArgs(::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(AutoRepeatModeChangeRequestedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^ UnwrapAutoRepeatModeChangeRequestedEventArgs(Local<Value> value) {
     return AutoRepeatModeChangeRequestedEventArgs::Unwrap<AutoRepeatModeChangeRequestedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitAutoRepeatModeChangeRequestedEventArgs(Local<Object> exports) {
    AutoRepeatModeChangeRequestedEventArgs::Init(exports);
  }

  class SystemMediaTransportControls : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SystemMediaTransportControls").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "updateTimelineProperties", UpdateTimelineProperties);
          


          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isPlayEnabled").ToLocalChecked(), IsPlayEnabledGetter, IsPlayEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isPauseEnabled").ToLocalChecked(), IsPauseEnabledGetter, IsPauseEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isNextEnabled").ToLocalChecked(), IsNextEnabledGetter, IsNextEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isPreviousEnabled").ToLocalChecked(), IsPreviousEnabledGetter, IsPreviousEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isEnabled").ToLocalChecked(), IsEnabledGetter, IsEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isChannelDownEnabled").ToLocalChecked(), IsChannelDownEnabledGetter, IsChannelDownEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isFastForwardEnabled").ToLocalChecked(), IsFastForwardEnabledGetter, IsFastForwardEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isChannelUpEnabled").ToLocalChecked(), IsChannelUpEnabledGetter, IsChannelUpEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("playbackStatus").ToLocalChecked(), PlaybackStatusGetter, PlaybackStatusSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isStopEnabled").ToLocalChecked(), IsStopEnabledGetter, IsStopEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isRewindEnabled").ToLocalChecked(), IsRewindEnabledGetter, IsRewindEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isRecordEnabled").ToLocalChecked(), IsRecordEnabledGetter, IsRecordEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayUpdater").ToLocalChecked(), DisplayUpdaterGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("soundLevel").ToLocalChecked(), SoundLevelGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("shuffleEnabled").ToLocalChecked(), ShuffleEnabledGetter, ShuffleEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("playbackRate").ToLocalChecked(), PlaybackRateGetter, PlaybackRateSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("autoRepeatMode").ToLocalChecked(), AutoRepeatModeGetter, AutoRepeatModeSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "getForCurrentView", GetForCurrentView);


        Nan::Set(exports, Nan::New<String>("SystemMediaTransportControls").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SystemMediaTransportControls(::Windows::Media::SystemMediaTransportControls^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::SystemMediaTransportControls^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::SystemMediaTransportControls^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SystemMediaTransportControls *wrapperInstance = new SystemMediaTransportControls(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::SystemMediaTransportControls^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::SystemMediaTransportControls^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSystemMediaTransportControls(winRtInstance));
    }


    static void UpdateTimelineProperties(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControlsTimelineProperties^>(info[0]))
      {
        try
        {
          ::Windows::Media::SystemMediaTransportControlsTimelineProperties^ arg0 = UnwrapSystemMediaTransportControlsTimelineProperties(info[0]);
          
          wrapper->_instance->UpdateTimelineProperties(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void GetForCurrentView(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Media::SystemMediaTransportControls^ result;
          result = ::Windows::Media::SystemMediaTransportControls::GetForCurrentView();
          info.GetReturnValue().Set(WrapSystemMediaTransportControls(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void IsPlayEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        bool result = wrapper->_instance->IsPlayEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsPlayEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsPlayEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsPauseEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        bool result = wrapper->_instance->IsPauseEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsPauseEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsPauseEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsNextEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        bool result = wrapper->_instance->IsNextEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsNextEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsNextEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsPreviousEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        bool result = wrapper->_instance->IsPreviousEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsPreviousEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsPreviousEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        bool result = wrapper->_instance->IsEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsChannelDownEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        bool result = wrapper->_instance->IsChannelDownEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsChannelDownEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsChannelDownEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsFastForwardEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        bool result = wrapper->_instance->IsFastForwardEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsFastForwardEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsFastForwardEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsChannelUpEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        bool result = wrapper->_instance->IsChannelUpEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsChannelUpEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsChannelUpEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void PlaybackStatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        ::Windows::Media::MediaPlaybackStatus result = wrapper->_instance->PlaybackStatus;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PlaybackStatusSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try {

        ::Windows::Media::MediaPlaybackStatus winRtValue = static_cast<::Windows::Media::MediaPlaybackStatus>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->PlaybackStatus = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsStopEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        bool result = wrapper->_instance->IsStopEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsStopEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsStopEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsRewindEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        bool result = wrapper->_instance->IsRewindEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsRewindEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsRewindEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsRecordEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        bool result = wrapper->_instance->IsRecordEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsRecordEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsRecordEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void DisplayUpdaterGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        ::Windows::Media::SystemMediaTransportControlsDisplayUpdater^ result = wrapper->_instance->DisplayUpdater;
        info.GetReturnValue().Set(WrapSystemMediaTransportControlsDisplayUpdater(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SoundLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        ::Windows::Media::SoundLevel result = wrapper->_instance->SoundLevel;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ShuffleEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        bool result = wrapper->_instance->ShuffleEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ShuffleEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->ShuffleEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void PlaybackRateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        double result = wrapper->_instance->PlaybackRate;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PlaybackRateSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try {

        double winRtValue = Nan::To<double>(value).FromMaybe(0.0);

        wrapper->_instance->PlaybackRate = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void AutoRepeatModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try  {
        ::Windows::Media::MediaPlaybackAutoRepeatMode result = wrapper->_instance->AutoRepeatMode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AutoRepeatModeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This())) {
        return;
      }

      SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());

      try {

        ::Windows::Media::MediaPlaybackAutoRepeatMode winRtValue = static_cast<::Windows::Media::MediaPlaybackAutoRepeatMode>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->AutoRepeatMode = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"buttonPressed", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->ButtonPressed::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::SystemMediaTransportControls^, ::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^>(
            [callbackObjPtr](::Windows::Media::SystemMediaTransportControls^ arg0, ::Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapSystemMediaTransportControls(arg0);
                  wrappedArg1 = WrapSystemMediaTransportControlsButtonPressedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"propertyChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PropertyChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::SystemMediaTransportControls^, ::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^>(
            [callbackObjPtr](::Windows::Media::SystemMediaTransportControls^ arg0, ::Windows::Media::SystemMediaTransportControlsPropertyChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapSystemMediaTransportControls(arg0);
                  wrappedArg1 = WrapSystemMediaTransportControlsPropertyChangedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"autoRepeatModeChangeRequested", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->AutoRepeatModeChangeRequested::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::SystemMediaTransportControls^, ::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^>(
            [callbackObjPtr](::Windows::Media::SystemMediaTransportControls^ arg0, ::Windows::Media::AutoRepeatModeChangeRequestedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapSystemMediaTransportControls(arg0);
                  wrappedArg1 = WrapAutoRepeatModeChangeRequestedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"playbackPositionChangeRequested", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PlaybackPositionChangeRequested::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::SystemMediaTransportControls^, ::Windows::Media::PlaybackPositionChangeRequestedEventArgs^>(
            [callbackObjPtr](::Windows::Media::SystemMediaTransportControls^ arg0, ::Windows::Media::PlaybackPositionChangeRequestedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapSystemMediaTransportControls(arg0);
                  wrappedArg1 = WrapPlaybackPositionChangeRequestedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"playbackRateChangeRequested", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PlaybackRateChangeRequested::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::SystemMediaTransportControls^, ::Windows::Media::PlaybackRateChangeRequestedEventArgs^>(
            [callbackObjPtr](::Windows::Media::SystemMediaTransportControls^ arg0, ::Windows::Media::PlaybackRateChangeRequestedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapSystemMediaTransportControls(arg0);
                  wrappedArg1 = WrapPlaybackRateChangeRequestedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"shuffleEnabledChangeRequested", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->ShuffleEnabledChangeRequested::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::SystemMediaTransportControls^, ::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^>(
            [callbackObjPtr](::Windows::Media::SystemMediaTransportControls^ arg0, ::Windows::Media::ShuffleEnabledChangeRequestedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapSystemMediaTransportControls(arg0);
                  wrappedArg1 = WrapShuffleEnabledChangeRequestedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"buttonPressed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"propertyChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"autoRepeatModeChangeRequested", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"playbackPositionChangeRequested", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"playbackRateChangeRequested", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"shuffleEnabledChangeRequested", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"buttonPressed", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());
          wrapper->_instance->ButtonPressed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"propertyChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());
          wrapper->_instance->PropertyChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"autoRepeatModeChangeRequested", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());
          wrapper->_instance->AutoRepeatModeChangeRequested::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"playbackPositionChangeRequested", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());
          wrapper->_instance->PlaybackPositionChangeRequested::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"playbackRateChangeRequested", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());
          wrapper->_instance->PlaybackRateChangeRequested::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"shuffleEnabledChangeRequested", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::SystemMediaTransportControls^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          SystemMediaTransportControls *wrapper = SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(info.This());
          wrapper->_instance->ShuffleEnabledChangeRequested::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Media::SystemMediaTransportControls^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSystemMediaTransportControls(::Windows::Media::SystemMediaTransportControls^ wintRtInstance);
      friend ::Windows::Media::SystemMediaTransportControls^ UnwrapSystemMediaTransportControls(Local<Value> value);
  };

  Persistent<FunctionTemplate> SystemMediaTransportControls::s_constructorTemplate;

  v8::Local<v8::Value> WrapSystemMediaTransportControls(::Windows::Media::SystemMediaTransportControls^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SystemMediaTransportControls::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::SystemMediaTransportControls^ UnwrapSystemMediaTransportControls(Local<Value> value) {
     return SystemMediaTransportControls::Unwrap<SystemMediaTransportControls>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSystemMediaTransportControls(Local<Object> exports) {
    SystemMediaTransportControls::Init(exports);
  }

  class MediaTimelineController : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaTimelineController").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "start", Start);
            Nan::SetPrototypeMethod(localRef, "resume", Resume);
            Nan::SetPrototypeMethod(localRef, "pause", Pause);
          


          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("position").ToLocalChecked(), PositionGetter, PositionSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("clockRate").ToLocalChecked(), ClockRateGetter, ClockRateSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("state").ToLocalChecked(), StateGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isLoopingEnabled").ToLocalChecked(), IsLoopingEnabledGetter, IsLoopingEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("duration").ToLocalChecked(), DurationGetter, DurationSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaTimelineController").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaTimelineController(::Windows::Media::MediaTimelineController^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::MediaTimelineController^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::MediaTimelineController^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try {
          winRtInstance = ref new ::Windows::Media::MediaTimelineController();
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaTimelineController *wrapperInstance = new MediaTimelineController(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::MediaTimelineController^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::MediaTimelineController^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaTimelineController(winRtInstance));
    }


    static void Start(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This())) {
        return;
      }

      MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Start();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Resume(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This())) {
        return;
      }

      MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Resume();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Pause(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This())) {
        return;
      }

      MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Pause();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void PositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This())) {
        return;
      }

      MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->Position;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PositionSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This())) {
        return;
      }

      MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());

      try {

        ::Windows::Foundation::TimeSpan winRtValue = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0));

        wrapper->_instance->Position = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void ClockRateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This())) {
        return;
      }

      MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());

      try  {
        double result = wrapper->_instance->ClockRate;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ClockRateSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This())) {
        return;
      }

      MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());

      try {

        double winRtValue = Nan::To<double>(value).FromMaybe(0.0);

        wrapper->_instance->ClockRate = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void StateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This())) {
        return;
      }

      MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());

      try  {
        ::Windows::Media::MediaTimelineControllerState result = wrapper->_instance->State;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsLoopingEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This())) {
        return;
      }

      MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());

      try  {
        bool result = wrapper->_instance->IsLoopingEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsLoopingEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This())) {
        return;
      }

      MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsLoopingEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void DurationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This())) {
        return;
      }

      MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());

      try  {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->Duration;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DurationSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This())) {
        return;
      }

      MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());

      try {

        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::TimeSpan>(NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0)));

        wrapper->_instance->Duration = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"positionChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PositionChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::MediaTimelineController^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::MediaTimelineController^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaTimelineController(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"stateChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->StateChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::MediaTimelineController^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::MediaTimelineController^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaTimelineController(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"ended", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->Ended::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::MediaTimelineController^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::MediaTimelineController^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaTimelineController(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"failed", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->Failed::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::MediaTimelineController^, ::Windows::Media::MediaTimelineControllerFailedEventArgs^>(
            [callbackObjPtr](::Windows::Media::MediaTimelineController^ arg0, ::Windows::Media::MediaTimelineControllerFailedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaTimelineController(arg0);
                  wrappedArg1 = WrapMediaTimelineControllerFailedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"positionChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"stateChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"ended", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"failed", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"positionChanged", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());
          wrapper->_instance->PositionChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"stateChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());
          wrapper->_instance->StateChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"ended", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());
          wrapper->_instance->Ended::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"failed", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaTimelineController *wrapper = MediaTimelineController::Unwrap<MediaTimelineController>(info.This());
          wrapper->_instance->Failed::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Media::MediaTimelineController^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaTimelineController(::Windows::Media::MediaTimelineController^ wintRtInstance);
      friend ::Windows::Media::MediaTimelineController^ UnwrapMediaTimelineController(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaTimelineController::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaTimelineController(::Windows::Media::MediaTimelineController^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaTimelineController::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::MediaTimelineController^ UnwrapMediaTimelineController(Local<Value> value) {
     return MediaTimelineController::Unwrap<MediaTimelineController>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaTimelineController(Local<Object> exports) {
    MediaTimelineController::Init(exports);
  }

  class MediaTimelineControllerFailedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaTimelineControllerFailedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaTimelineControllerFailedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaTimelineControllerFailedEventArgs(::Windows::Media::MediaTimelineControllerFailedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::MediaTimelineControllerFailedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineControllerFailedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::MediaTimelineControllerFailedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaTimelineControllerFailedEventArgs *wrapperInstance = new MediaTimelineControllerFailedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineControllerFailedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::MediaTimelineControllerFailedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::MediaTimelineControllerFailedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaTimelineControllerFailedEventArgs(winRtInstance));
    }





    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineControllerFailedEventArgs^>(info.This())) {
        return;
      }

      MediaTimelineControllerFailedEventArgs *wrapper = MediaTimelineControllerFailedEventArgs::Unwrap<MediaTimelineControllerFailedEventArgs>(info.This());

      try  {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::MediaTimelineControllerFailedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaTimelineControllerFailedEventArgs(::Windows::Media::MediaTimelineControllerFailedEventArgs^ wintRtInstance);
      friend ::Windows::Media::MediaTimelineControllerFailedEventArgs^ UnwrapMediaTimelineControllerFailedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaTimelineControllerFailedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaTimelineControllerFailedEventArgs(::Windows::Media::MediaTimelineControllerFailedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaTimelineControllerFailedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::MediaTimelineControllerFailedEventArgs^ UnwrapMediaTimelineControllerFailedEventArgs(Local<Value> value) {
     return MediaTimelineControllerFailedEventArgs::Unwrap<MediaTimelineControllerFailedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaTimelineControllerFailedEventArgs(Local<Object> exports) {
    MediaTimelineControllerFailedEventArgs::Init(exports);
  }

  class IMediaExtension : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IMediaExtension").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "setProperties", SetProperties);
          




        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IMediaExtension").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IMediaExtension(::Windows::Media::IMediaExtension^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::IMediaExtension^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaExtension^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::IMediaExtension^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IMediaExtension *wrapperInstance = new IMediaExtension(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaExtension^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::IMediaExtension^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::IMediaExtension^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIMediaExtension(winRtInstance));
    }


    static void SetProperties(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaExtension^>(info.This())) {
        return;
      }

      IMediaExtension *wrapper = IMediaExtension::Unwrap<IMediaExtension>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IPropertySet^>(info[0]))
      {
        try
        {
          ::Windows::Foundation::Collections::IPropertySet^ arg0 = dynamic_cast<::Windows::Foundation::Collections::IPropertySet^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          wrapper->_instance->SetProperties(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





    private:
      ::Windows::Media::IMediaExtension^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIMediaExtension(::Windows::Media::IMediaExtension^ wintRtInstance);
      friend ::Windows::Media::IMediaExtension^ UnwrapIMediaExtension(Local<Value> value);
  };

  Persistent<FunctionTemplate> IMediaExtension::s_constructorTemplate;

  v8::Local<v8::Value> WrapIMediaExtension(::Windows::Media::IMediaExtension^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IMediaExtension::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::IMediaExtension^ UnwrapIMediaExtension(Local<Value> value) {
     return IMediaExtension::Unwrap<IMediaExtension>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIMediaExtension(Local<Object> exports) {
    IMediaExtension::Init(exports);
  }

  class MediaExtensionManager : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaExtensionManager").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "registerSchemeHandler", RegisterSchemeHandler);
            Nan::SetPrototypeMethod(localRef, "registerByteStreamHandler", RegisterByteStreamHandler);
            Nan::SetPrototypeMethod(localRef, "registerAudioDecoder", RegisterAudioDecoder);
            Nan::SetPrototypeMethod(localRef, "registerAudioEncoder", RegisterAudioEncoder);
            Nan::SetPrototypeMethod(localRef, "registerVideoDecoder", RegisterVideoDecoder);
            Nan::SetPrototypeMethod(localRef, "registerVideoEncoder", RegisterVideoEncoder);
            Nan::SetPrototypeMethod(localRef, "registerMediaExtensionForAppService", RegisterMediaExtensionForAppService);
          




        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaExtensionManager").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaExtensionManager(::Windows::Media::MediaExtensionManager^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::MediaExtensionManager^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaExtensionManager^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::MediaExtensionManager^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try {
          winRtInstance = ref new ::Windows::Media::MediaExtensionManager();
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaExtensionManager *wrapperInstance = new MediaExtensionManager(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaExtensionManager^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::MediaExtensionManager^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::MediaExtensionManager^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaExtensionManager(winRtInstance));
    }


    static void RegisterSchemeHandler(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaExtensionManager^>(info.This())) {
        return;
      }

      MediaExtensionManager *wrapper = MediaExtensionManager::Unwrap<MediaExtensionManager>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && info[1]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          wrapper->_instance->RegisterSchemeHandler(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IPropertySet^>(info[2]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          ::Windows::Foundation::Collections::IPropertySet^ arg2 = dynamic_cast<::Windows::Foundation::Collections::IPropertySet^>(NodeRT::Utils::GetObjectInstance(info[2]));
          
          wrapper->_instance->RegisterSchemeHandler(arg0, arg1, arg2);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RegisterByteStreamHandler(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaExtensionManager^>(info.This())) {
        return;
      }

      MediaExtensionManager *wrapper = MediaExtensionManager::Unwrap<MediaExtensionManager>(info.This());

      if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsString()
        && info[2]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[2])));
          
          wrapper->_instance->RegisterByteStreamHandler(arg0, arg1, arg2);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsString()
        && info[1]->IsString()
        && info[2]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IPropertySet^>(info[3]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[2])));
          ::Windows::Foundation::Collections::IPropertySet^ arg3 = dynamic_cast<::Windows::Foundation::Collections::IPropertySet^>(NodeRT::Utils::GetObjectInstance(info[3]));
          
          wrapper->_instance->RegisterByteStreamHandler(arg0, arg1, arg2, arg3);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RegisterAudioDecoder(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaExtensionManager^>(info.This())) {
        return;
      }

      MediaExtensionManager *wrapper = MediaExtensionManager::Unwrap<MediaExtensionManager>(info.This());

      if (info.Length() == 3
        && info[0]->IsString()
        && NodeRT::Utils::IsGuid(info[1])
        && NodeRT::Utils::IsGuid(info[2]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Guid arg1 = NodeRT::Utils::GuidFromJs(info[1]);
          ::Platform::Guid arg2 = NodeRT::Utils::GuidFromJs(info[2]);
          
          wrapper->_instance->RegisterAudioDecoder(arg0, arg1, arg2);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsString()
        && NodeRT::Utils::IsGuid(info[1])
        && NodeRT::Utils::IsGuid(info[2])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IPropertySet^>(info[3]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Guid arg1 = NodeRT::Utils::GuidFromJs(info[1]);
          ::Platform::Guid arg2 = NodeRT::Utils::GuidFromJs(info[2]);
          ::Windows::Foundation::Collections::IPropertySet^ arg3 = dynamic_cast<::Windows::Foundation::Collections::IPropertySet^>(NodeRT::Utils::GetObjectInstance(info[3]));
          
          wrapper->_instance->RegisterAudioDecoder(arg0, arg1, arg2, arg3);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RegisterAudioEncoder(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaExtensionManager^>(info.This())) {
        return;
      }

      MediaExtensionManager *wrapper = MediaExtensionManager::Unwrap<MediaExtensionManager>(info.This());

      if (info.Length() == 3
        && info[0]->IsString()
        && NodeRT::Utils::IsGuid(info[1])
        && NodeRT::Utils::IsGuid(info[2]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Guid arg1 = NodeRT::Utils::GuidFromJs(info[1]);
          ::Platform::Guid arg2 = NodeRT::Utils::GuidFromJs(info[2]);
          
          wrapper->_instance->RegisterAudioEncoder(arg0, arg1, arg2);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsString()
        && NodeRT::Utils::IsGuid(info[1])
        && NodeRT::Utils::IsGuid(info[2])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IPropertySet^>(info[3]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Guid arg1 = NodeRT::Utils::GuidFromJs(info[1]);
          ::Platform::Guid arg2 = NodeRT::Utils::GuidFromJs(info[2]);
          ::Windows::Foundation::Collections::IPropertySet^ arg3 = dynamic_cast<::Windows::Foundation::Collections::IPropertySet^>(NodeRT::Utils::GetObjectInstance(info[3]));
          
          wrapper->_instance->RegisterAudioEncoder(arg0, arg1, arg2, arg3);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RegisterVideoDecoder(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaExtensionManager^>(info.This())) {
        return;
      }

      MediaExtensionManager *wrapper = MediaExtensionManager::Unwrap<MediaExtensionManager>(info.This());

      if (info.Length() == 3
        && info[0]->IsString()
        && NodeRT::Utils::IsGuid(info[1])
        && NodeRT::Utils::IsGuid(info[2]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Guid arg1 = NodeRT::Utils::GuidFromJs(info[1]);
          ::Platform::Guid arg2 = NodeRT::Utils::GuidFromJs(info[2]);
          
          wrapper->_instance->RegisterVideoDecoder(arg0, arg1, arg2);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsString()
        && NodeRT::Utils::IsGuid(info[1])
        && NodeRT::Utils::IsGuid(info[2])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IPropertySet^>(info[3]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Guid arg1 = NodeRT::Utils::GuidFromJs(info[1]);
          ::Platform::Guid arg2 = NodeRT::Utils::GuidFromJs(info[2]);
          ::Windows::Foundation::Collections::IPropertySet^ arg3 = dynamic_cast<::Windows::Foundation::Collections::IPropertySet^>(NodeRT::Utils::GetObjectInstance(info[3]));
          
          wrapper->_instance->RegisterVideoDecoder(arg0, arg1, arg2, arg3);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RegisterVideoEncoder(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaExtensionManager^>(info.This())) {
        return;
      }

      MediaExtensionManager *wrapper = MediaExtensionManager::Unwrap<MediaExtensionManager>(info.This());

      if (info.Length() == 3
        && info[0]->IsString()
        && NodeRT::Utils::IsGuid(info[1])
        && NodeRT::Utils::IsGuid(info[2]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Guid arg1 = NodeRT::Utils::GuidFromJs(info[1]);
          ::Platform::Guid arg2 = NodeRT::Utils::GuidFromJs(info[2]);
          
          wrapper->_instance->RegisterVideoEncoder(arg0, arg1, arg2);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsString()
        && NodeRT::Utils::IsGuid(info[1])
        && NodeRT::Utils::IsGuid(info[2])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IPropertySet^>(info[3]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Guid arg1 = NodeRT::Utils::GuidFromJs(info[1]);
          ::Platform::Guid arg2 = NodeRT::Utils::GuidFromJs(info[2]);
          ::Windows::Foundation::Collections::IPropertySet^ arg3 = dynamic_cast<::Windows::Foundation::Collections::IPropertySet^>(NodeRT::Utils::GetObjectInstance(info[3]));
          
          wrapper->_instance->RegisterVideoEncoder(arg0, arg1, arg2, arg3);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RegisterMediaExtensionForAppService(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaExtensionManager^>(info.This())) {
        return;
      }

      MediaExtensionManager *wrapper = MediaExtensionManager::Unwrap<MediaExtensionManager>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::IMediaExtension^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppService::AppServiceConnection^>(info[1]))
      {
        try
        {
          ::Windows::Media::IMediaExtension^ arg0 = UnwrapIMediaExtension(info[0]);
          ::Windows::ApplicationModel::AppService::AppServiceConnection^ arg1 = dynamic_cast<::Windows::ApplicationModel::AppService::AppServiceConnection^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          wrapper->_instance->RegisterMediaExtensionForAppService(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





    private:
      ::Windows::Media::MediaExtensionManager^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaExtensionManager(::Windows::Media::MediaExtensionManager^ wintRtInstance);
      friend ::Windows::Media::MediaExtensionManager^ UnwrapMediaExtensionManager(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaExtensionManager::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaExtensionManager(::Windows::Media::MediaExtensionManager^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaExtensionManager::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::MediaExtensionManager^ UnwrapMediaExtensionManager(Local<Value> value) {
     return MediaExtensionManager::Unwrap<MediaExtensionManager>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaExtensionManager(Local<Object> exports) {
    MediaExtensionManager::Init(exports);
  }

  class VideoEffects : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("VideoEffects").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);






        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetAccessor(constructor, Nan::New<String>("videoStabilization").ToLocalChecked(), VideoStabilizationGetter);


        Nan::Set(exports, Nan::New<String>("VideoEffects").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      VideoEffects(::Windows::Media::VideoEffects^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::VideoEffects^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoEffects^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::VideoEffects^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      VideoEffects *wrapperInstance = new VideoEffects(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::VideoEffects^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::VideoEffects^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::VideoEffects^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapVideoEffects(winRtInstance));
    }







    static void VideoStabilizationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Media::VideoEffects::VideoStabilization;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    private:
      ::Windows::Media::VideoEffects^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapVideoEffects(::Windows::Media::VideoEffects^ wintRtInstance);
      friend ::Windows::Media::VideoEffects^ UnwrapVideoEffects(Local<Value> value);
  };

  Persistent<FunctionTemplate> VideoEffects::s_constructorTemplate;

  v8::Local<v8::Value> WrapVideoEffects(::Windows::Media::VideoEffects^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(VideoEffects::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::VideoEffects^ UnwrapVideoEffects(Local<Value> value) {
     return VideoEffects::Unwrap<VideoEffects>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitVideoEffects(Local<Object> exports) {
    VideoEffects::Init(exports);
  }

  class MediaControl : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaControl").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);






        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetAccessor(constructor, Nan::New<String>("trackName").ToLocalChecked(), TrackNameGetter, TrackNameSetter);
        Nan::SetAccessor(constructor, Nan::New<String>("isPlaying").ToLocalChecked(), IsPlayingGetter, IsPlayingSetter);
        Nan::SetAccessor(constructor, Nan::New<String>("artistName").ToLocalChecked(), ArtistNameGetter, ArtistNameSetter);
        Nan::SetAccessor(constructor, Nan::New<String>("albumArt").ToLocalChecked(), AlbumArtGetter, AlbumArtSetter);
        Nan::SetAccessor(constructor, Nan::New<String>("soundLevel").ToLocalChecked(), SoundLevelGetter);
        
              Local<Function> addListenerFunc = Nan::GetFunction(Nan::New<FunctionTemplate>(AddListener)).ToLocalChecked();
              Nan::Set(constructor, Nan::New<String>("addListener").ToLocalChecked(), addListenerFunc);
              Nan::Set(constructor, Nan::New<String>("on").ToLocalChecked(), addListenerFunc);
              Local<Function> removeListenerFunc = Nan::GetFunction(Nan::New<FunctionTemplate>(RemoveListener)).ToLocalChecked();
              Nan::Set(constructor, Nan::New<String>("removeListener").ToLocalChecked(), removeListenerFunc);
              Nan::Set(constructor, Nan::New<String>("off").ToLocalChecked(), removeListenerFunc);


        Nan::Set(exports, Nan::New<String>("MediaControl").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaControl(::Windows::Media::MediaControl^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::MediaControl^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaControl^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::MediaControl^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaControl *wrapperInstance = new MediaControl(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaControl^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::MediaControl^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::MediaControl^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaControl(winRtInstance));
    }







    static void TrackNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Media::MediaControl::TrackName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TrackNameSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      try {


        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        ::Windows::Media::MediaControl::TrackName = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      

    static void IsPlayingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        bool result = ::Windows::Media::MediaControl::IsPlaying;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void IsPlayingSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      try {


        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        ::Windows::Media::MediaControl::IsPlaying = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      

    static void ArtistNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Media::MediaControl::ArtistName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ArtistNameSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      try {


        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        ::Windows::Media::MediaControl::ArtistName = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      

    static void AlbumArtGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Foundation::Uri^ result = ::Windows::Media::MediaControl::AlbumArt;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void AlbumArtSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      try {


        ::Windows::Foundation::Uri^ winRtValue = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));

        ::Windows::Media::MediaControl::AlbumArt = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      

    static void SoundLevelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Media::SoundLevel result = ::Windows::Media::MediaControl::SoundLevel;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"channelDownPressed", str))
      {
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = ::Windows::Media::MediaControl::ChannelDownPressed::add(
            ref new ::Windows::Foundation::EventHandler<::Platform::Object^>(
            [callbackObjPtr](::Platform::Object^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = CreateOpaqueWrapper(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"channelUpPressed", str))
      {
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = ::Windows::Media::MediaControl::ChannelUpPressed::add(
            ref new ::Windows::Foundation::EventHandler<::Platform::Object^>(
            [callbackObjPtr](::Platform::Object^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = CreateOpaqueWrapper(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"fastForwardPressed", str))
      {
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = ::Windows::Media::MediaControl::FastForwardPressed::add(
            ref new ::Windows::Foundation::EventHandler<::Platform::Object^>(
            [callbackObjPtr](::Platform::Object^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = CreateOpaqueWrapper(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"nextTrackPressed", str))
      {
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = ::Windows::Media::MediaControl::NextTrackPressed::add(
            ref new ::Windows::Foundation::EventHandler<::Platform::Object^>(
            [callbackObjPtr](::Platform::Object^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = CreateOpaqueWrapper(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"pausePressed", str))
      {
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = ::Windows::Media::MediaControl::PausePressed::add(
            ref new ::Windows::Foundation::EventHandler<::Platform::Object^>(
            [callbackObjPtr](::Platform::Object^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = CreateOpaqueWrapper(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"playPauseTogglePressed", str))
      {
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = ::Windows::Media::MediaControl::PlayPauseTogglePressed::add(
            ref new ::Windows::Foundation::EventHandler<::Platform::Object^>(
            [callbackObjPtr](::Platform::Object^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = CreateOpaqueWrapper(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"playPressed", str))
      {
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = ::Windows::Media::MediaControl::PlayPressed::add(
            ref new ::Windows::Foundation::EventHandler<::Platform::Object^>(
            [callbackObjPtr](::Platform::Object^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = CreateOpaqueWrapper(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"previousTrackPressed", str))
      {
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = ::Windows::Media::MediaControl::PreviousTrackPressed::add(
            ref new ::Windows::Foundation::EventHandler<::Platform::Object^>(
            [callbackObjPtr](::Platform::Object^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = CreateOpaqueWrapper(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"recordPressed", str))
      {
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = ::Windows::Media::MediaControl::RecordPressed::add(
            ref new ::Windows::Foundation::EventHandler<::Platform::Object^>(
            [callbackObjPtr](::Platform::Object^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = CreateOpaqueWrapper(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"rewindPressed", str))
      {
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = ::Windows::Media::MediaControl::RewindPressed::add(
            ref new ::Windows::Foundation::EventHandler<::Platform::Object^>(
            [callbackObjPtr](::Platform::Object^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = CreateOpaqueWrapper(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"soundLevelChanged", str))
      {
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = ::Windows::Media::MediaControl::SoundLevelChanged::add(
            ref new ::Windows::Foundation::EventHandler<::Platform::Object^>(
            [callbackObjPtr](::Platform::Object^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = CreateOpaqueWrapper(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"stopPressed", str))
      {
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = ::Windows::Media::MediaControl::StopPressed::add(
            ref new ::Windows::Foundation::EventHandler<::Platform::Object^>(
            [callbackObjPtr](::Platform::Object^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = CreateOpaqueWrapper(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"channelDownPressed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"channelUpPressed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"fastForwardPressed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"nextTrackPressed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"pausePressed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"playPauseTogglePressed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"playPressed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"previousTrackPressed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"recordPressed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"rewindPressed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"soundLevelChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"stopPressed", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"channelDownPressed", str)) {
          ::Windows::Media::MediaControl::ChannelDownPressed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"channelUpPressed", str))
        {
          ::Windows::Media::MediaControl::ChannelUpPressed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"fastForwardPressed", str))
        {
          ::Windows::Media::MediaControl::FastForwardPressed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"nextTrackPressed", str))
        {
          ::Windows::Media::MediaControl::NextTrackPressed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"pausePressed", str))
        {
          ::Windows::Media::MediaControl::PausePressed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"playPauseTogglePressed", str))
        {
          ::Windows::Media::MediaControl::PlayPauseTogglePressed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"playPressed", str))
        {
          ::Windows::Media::MediaControl::PlayPressed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"previousTrackPressed", str))
        {
          ::Windows::Media::MediaControl::PreviousTrackPressed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"recordPressed", str))
        {
          ::Windows::Media::MediaControl::RecordPressed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"rewindPressed", str))
        {
          ::Windows::Media::MediaControl::RewindPressed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"soundLevelChanged", str))
        {
          ::Windows::Media::MediaControl::SoundLevelChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"stopPressed", str))
        {
          ::Windows::Media::MediaControl::StopPressed::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Media::MediaControl^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaControl(::Windows::Media::MediaControl^ wintRtInstance);
      friend ::Windows::Media::MediaControl^ UnwrapMediaControl(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaControl::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaControl(::Windows::Media::MediaControl^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaControl::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::MediaControl^ UnwrapMediaControl(Local<Value> value) {
     return MediaControl::Unwrap<MediaControl>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaControl(Local<Object> exports) {
    MediaControl::Init(exports);
  }


} } } 

NAN_MODULE_INIT(init) {
  // We ignore failures for now since it probably means that
  // the initialization already happened for STA, and that's cool

  CoInitializeEx(nullptr, COINIT_MULTITHREADED);

  /*
  if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
    Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"error in CoInitializeEx()")));
    return;
  }
  */

      NodeRT::Windows::Media::InitAudioBufferAccessModeEnum(target);
      NodeRT::Windows::Media::InitSoundLevelEnum(target);
      NodeRT::Windows::Media::InitMediaPlaybackTypeEnum(target);
      NodeRT::Windows::Media::InitMediaPlaybackAutoRepeatModeEnum(target);
      NodeRT::Windows::Media::InitMediaPlaybackStatusEnum(target);
      NodeRT::Windows::Media::InitSystemMediaTransportControlsButtonEnum(target);
      NodeRT::Windows::Media::InitSystemMediaTransportControlsPropertyEnum(target);
      NodeRT::Windows::Media::InitMediaTimelineControllerStateEnum(target);
      NodeRT::Windows::Media::InitAudioProcessingEnum(target);
      NodeRT::Windows::Media::InitMediaProcessingTriggerDetails(target);
      NodeRT::Windows::Media::InitIMediaFrame(target);
      NodeRT::Windows::Media::InitVideoFrame(target);
      NodeRT::Windows::Media::InitAudioBuffer(target);
      NodeRT::Windows::Media::InitAudioFrame(target);
      NodeRT::Windows::Media::InitIMediaMarker(target);
      NodeRT::Windows::Media::InitIMediaMarkers(target);
      NodeRT::Windows::Media::InitMediaMarkerTypes(target);
      NodeRT::Windows::Media::InitSystemMediaTransportControlsTimelineProperties(target);
      NodeRT::Windows::Media::InitMusicDisplayProperties(target);
      NodeRT::Windows::Media::InitVideoDisplayProperties(target);
      NodeRT::Windows::Media::InitImageDisplayProperties(target);
      NodeRT::Windows::Media::InitSystemMediaTransportControlsDisplayUpdater(target);
      NodeRT::Windows::Media::InitSystemMediaTransportControlsButtonPressedEventArgs(target);
      NodeRT::Windows::Media::InitSystemMediaTransportControlsPropertyChangedEventArgs(target);
      NodeRT::Windows::Media::InitPlaybackPositionChangeRequestedEventArgs(target);
      NodeRT::Windows::Media::InitPlaybackRateChangeRequestedEventArgs(target);
      NodeRT::Windows::Media::InitShuffleEnabledChangeRequestedEventArgs(target);
      NodeRT::Windows::Media::InitAutoRepeatModeChangeRequestedEventArgs(target);
      NodeRT::Windows::Media::InitSystemMediaTransportControls(target);
      NodeRT::Windows::Media::InitMediaTimelineController(target);
      NodeRT::Windows::Media::InitMediaTimelineControllerFailedEventArgs(target);
      NodeRT::Windows::Media::InitIMediaExtension(target);
      NodeRT::Windows::Media::InitMediaExtensionManager(target);
      NodeRT::Windows::Media::InitVideoEffects(target);
      NodeRT::Windows::Media::InitMediaControl(target);


  NodeRT::Utils::RegisterNameSpace("Windows.Media", target);
}



NODE_MODULE(binding, init)
