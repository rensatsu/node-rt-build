  
BitmapBounds = (function () {
  var cls = function BitmapBounds() {
      this.x = new Number();
      this.y = new Number();
      this.width = new Number();
      this.height = new Number();
    };
  return cls;
}) ();
exports.BitmapBounds = BitmapBounds;


  
MediaTimeRange = (function () {
  var cls = function MediaTimeRange() {
      this.start = new Number();
      this.end = new Number();
    };
  return cls;
}) ();
exports.MediaTimeRange = MediaTimeRange;


  
MediaControlContract = (function () {
  var cls = function MediaControlContract() {
    };
  return cls;
}) ();
exports.MediaControlContract = MediaControlContract;


_AudioBufferAccessMode = function () {
  this.read = 0;
  this.readWrite = 1;
  this.write = 2;
}
exports.AudioBufferAccessMode = new _AudioBufferAccessMode();

_SoundLevel = function () {
  this.muted = 0;
  this.low = 1;
  this.full = 2;
}
exports.SoundLevel = new _SoundLevel();

_MediaPlaybackType = function () {
  this.unknown = 0;
  this.music = 1;
  this.video = 2;
  this.image = 3;
}
exports.MediaPlaybackType = new _MediaPlaybackType();

_MediaPlaybackAutoRepeatMode = function () {
  this.none = 0;
  this.track = 1;
  this.list = 2;
}
exports.MediaPlaybackAutoRepeatMode = new _MediaPlaybackAutoRepeatMode();

_MediaPlaybackStatus = function () {
  this.closed = 0;
  this.changing = 1;
  this.stopped = 2;
  this.playing = 3;
  this.paused = 4;
}
exports.MediaPlaybackStatus = new _MediaPlaybackStatus();

_SystemMediaTransportControlsButton = function () {
  this.play = 0;
  this.pause = 1;
  this.stop = 2;
  this.record = 3;
  this.fastForward = 4;
  this.rewind = 5;
  this.next = 6;
  this.previous = 7;
  this.channelUp = 8;
  this.channelDown = 9;
}
exports.SystemMediaTransportControlsButton = new _SystemMediaTransportControlsButton();

_SystemMediaTransportControlsProperty = function () {
  this.soundLevel = 0;
}
exports.SystemMediaTransportControlsProperty = new _SystemMediaTransportControlsProperty();

_MediaTimelineControllerState = function () {
  this.paused = 0;
  this.running = 1;
  this.stalled = 2;
  this.error = 3;
}
exports.MediaTimelineControllerState = new _MediaTimelineControllerState();

_AudioProcessing = function () {
  this.default = 0;
  this.raw = 1;
}
exports.AudioProcessing = new _AudioProcessing();

MediaProcessingTriggerDetails = (function () {
  var cls = function MediaProcessingTriggerDetails() {
    this.arguments = new Object();
  };
  

  return cls;
}) ();
exports.MediaProcessingTriggerDetails = MediaProcessingTriggerDetails;

IMediaFrame = (function () {
  var cls = function IMediaFrame() {
    this.duration = new Number();
    this.extendedProperties = new Object();
    this.isDiscontinuous = new Boolean();
    this.isReadOnly = new Boolean();
    this.relativeTime = new Number();
    this.systemRelativeTime = new Number();
    this.type = new String();
  };
  

  return cls;
}) ();
exports.IMediaFrame = IMediaFrame;

VideoFrame = (function () {
  var cls = function VideoFrame() {
    this.systemRelativeTime = new Number();
    this.relativeTime = new Number();
    this.isDiscontinuous = new Boolean();
    this.duration = new Number();
    this.extendedProperties = new Object();
    this.isReadOnly = new Boolean();
    this.type = new String();
    this.direct3DSurface = new Object();
    this.softwareBitmap = new Object();
  };
  
var cls = function VideoFrame(format, width, height) {
      this.systemRelativeTime = new Number();
      this.relativeTime = new Number();
      this.isDiscontinuous = new Boolean();
      this.duration = new Number();
      this.extendedProperties = new Object();
      this.isReadOnly = new Boolean();
      this.type = new String();
      this.direct3DSurface = new Object();
      this.softwareBitmap = new Object();
};

var cls = function VideoFrame(format, width, height, alpha) {
      this.systemRelativeTime = new Number();
      this.relativeTime = new Number();
      this.isDiscontinuous = new Boolean();
      this.duration = new Number();
      this.extendedProperties = new Object();
      this.isReadOnly = new Boolean();
      this.type = new String();
      this.direct3DSurface = new Object();
      this.softwareBitmap = new Object();
};


  cls.prototype.copyToAsync = function copyToAsync(frame, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="frame" type="VideoFrame">A param.</param>
    /// </signature>
  }

cls.prototype.copyToAsync = function copyToAsync(frame, sourceBounds, destinationBounds, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="frame" type="VideoFrame">A param.</param>
    /// <param name="sourceBounds" type="BitmapBounds">A param.</param>
    /// <param name="destinationBounds" type="BitmapBounds">A param.</param>
    /// </signature>
  }


  cls.prototype.close = function close() {
}


  cls.createAsDirect3D11SurfaceBacked = function createAsDirect3D11SurfaceBacked(format, width, height) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="format" type="Number">A param.</param>
    /// <param name="width" type="Number">A param.</param>
    /// <param name="height" type="Number">A param.</param>
    /// <returns type="VideoFrame" />
    /// </signature>
    return new VideoFrame();
  }

cls.createAsDirect3D11SurfaceBacked = function createAsDirect3D11SurfaceBacked(format, width, height, device) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="format" type="Number">A param.</param>
    /// <param name="width" type="Number">A param.</param>
    /// <param name="height" type="Number">A param.</param>
    /// <param name="device" type="Object">A param.</param>
    /// <returns type="VideoFrame" />
    /// </signature>
    return new VideoFrame();
  }


  cls.createWithSoftwareBitmap = function createWithSoftwareBitmap(bitmap) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="bitmap" type="Object">A param.</param>
    /// <returns type="VideoFrame" />
    /// </signature>
    return new VideoFrame();
  }


  cls.createWithDirect3D11Surface = function createWithDirect3D11Surface(surface) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="surface" type="Object">A param.</param>
    /// <returns type="VideoFrame" />
    /// </signature>
    return new VideoFrame();
  }


  return cls;
}) ();
exports.VideoFrame = VideoFrame;

AudioBuffer = (function () {
  var cls = function AudioBuffer() {
    this.length = new Number();
    this.capacity = new Number();
  };
  

  cls.prototype.createReference = function createReference() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.AudioBuffer = AudioBuffer;

AudioFrame = (function () {
  var cls = function AudioFrame() {
    this.systemRelativeTime = new Number();
    this.relativeTime = new Number();
    this.isDiscontinuous = new Boolean();
    this.duration = new Number();
    this.extendedProperties = new Object();
    this.isReadOnly = new Boolean();
    this.type = new String();
  };
  
var cls = function AudioFrame(capacity) {
      this.systemRelativeTime = new Number();
      this.relativeTime = new Number();
      this.isDiscontinuous = new Boolean();
      this.duration = new Number();
      this.extendedProperties = new Object();
      this.isReadOnly = new Boolean();
      this.type = new String();
};


  cls.prototype.lockBuffer = function lockBuffer(mode) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="AudioBufferAccessMode">A param.</param>
    /// <returns type="AudioBuffer" />
    /// </signature>
    return new AudioBuffer();
  }


  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.AudioFrame = AudioFrame;

IMediaMarker = (function () {
  var cls = function IMediaMarker() {
    this.mediaMarkerType = new String();
    this.text = new String();
    this.time = new Number();
  };
  

  return cls;
}) ();
exports.IMediaMarker = IMediaMarker;

IMediaMarkers = (function () {
  var cls = function IMediaMarkers() {
    this.markers = new Object();
  };
  

  return cls;
}) ();
exports.IMediaMarkers = IMediaMarkers;

MediaMarkerTypes = (function () {
  var cls = function MediaMarkerTypes() {
  };
  

  cls.bookmark = new String();
  return cls;
}) ();
exports.MediaMarkerTypes = MediaMarkerTypes;

SystemMediaTransportControlsTimelineProperties = (function () {
  var cls = function SystemMediaTransportControlsTimelineProperties() {
    this.startTime = new Number();
    this.position = new Number();
    this.minSeekTime = new Number();
    this.maxSeekTime = new Number();
    this.endTime = new Number();
  };
  

  return cls;
}) ();
exports.SystemMediaTransportControlsTimelineProperties = SystemMediaTransportControlsTimelineProperties;

MusicDisplayProperties = (function () {
  var cls = function MusicDisplayProperties() {
    this.title = new String();
    this.artist = new String();
    this.albumArtist = new String();
    this.trackNumber = new Number();
    this.albumTitle = new String();
    this.genres = new Object();
    this.albumTrackCount = new Number();
  };
  

  return cls;
}) ();
exports.MusicDisplayProperties = MusicDisplayProperties;

VideoDisplayProperties = (function () {
  var cls = function VideoDisplayProperties() {
    this.title = new String();
    this.subtitle = new String();
    this.genres = new Object();
  };
  

  return cls;
}) ();
exports.VideoDisplayProperties = VideoDisplayProperties;

ImageDisplayProperties = (function () {
  var cls = function ImageDisplayProperties() {
    this.title = new String();
    this.subtitle = new String();
  };
  

  return cls;
}) ();
exports.ImageDisplayProperties = ImageDisplayProperties;

SystemMediaTransportControlsDisplayUpdater = (function () {
  var cls = function SystemMediaTransportControlsDisplayUpdater() {
    this.type = new MediaPlaybackType();
    this.thumbnail = new Object();
    this.appMediaId = new String();
    this.imageProperties = new ImageDisplayProperties();
    this.musicProperties = new MusicDisplayProperties();
    this.videoProperties = new VideoDisplayProperties();
  };
  

  cls.prototype.copyFromFileAsync = function copyFromFileAsync(type, source, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="type" type="MediaPlaybackType">A param.</param>
    /// <param name="source" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.clearAll = function clearAll() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.update = function update() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.SystemMediaTransportControlsDisplayUpdater = SystemMediaTransportControlsDisplayUpdater;

SystemMediaTransportControlsButtonPressedEventArgs = (function () {
  var cls = function SystemMediaTransportControlsButtonPressedEventArgs() {
    this.button = new SystemMediaTransportControlsButton();
  };
  

  return cls;
}) ();
exports.SystemMediaTransportControlsButtonPressedEventArgs = SystemMediaTransportControlsButtonPressedEventArgs;

SystemMediaTransportControlsPropertyChangedEventArgs = (function () {
  var cls = function SystemMediaTransportControlsPropertyChangedEventArgs() {
    this.property = new SystemMediaTransportControlsProperty();
  };
  

  return cls;
}) ();
exports.SystemMediaTransportControlsPropertyChangedEventArgs = SystemMediaTransportControlsPropertyChangedEventArgs;

PlaybackPositionChangeRequestedEventArgs = (function () {
  var cls = function PlaybackPositionChangeRequestedEventArgs() {
    this.requestedPlaybackPosition = new Number();
  };
  

  return cls;
}) ();
exports.PlaybackPositionChangeRequestedEventArgs = PlaybackPositionChangeRequestedEventArgs;

PlaybackRateChangeRequestedEventArgs = (function () {
  var cls = function PlaybackRateChangeRequestedEventArgs() {
    this.requestedPlaybackRate = new Number();
  };
  

  return cls;
}) ();
exports.PlaybackRateChangeRequestedEventArgs = PlaybackRateChangeRequestedEventArgs;

ShuffleEnabledChangeRequestedEventArgs = (function () {
  var cls = function ShuffleEnabledChangeRequestedEventArgs() {
    this.requestedShuffleEnabled = new Boolean();
  };
  

  return cls;
}) ();
exports.ShuffleEnabledChangeRequestedEventArgs = ShuffleEnabledChangeRequestedEventArgs;

AutoRepeatModeChangeRequestedEventArgs = (function () {
  var cls = function AutoRepeatModeChangeRequestedEventArgs() {
    this.requestedAutoRepeatMode = new MediaPlaybackAutoRepeatMode();
  };
  

  return cls;
}) ();
exports.AutoRepeatModeChangeRequestedEventArgs = AutoRepeatModeChangeRequestedEventArgs;

SystemMediaTransportControls = (function () {
  var cls = function SystemMediaTransportControls() {
    this.isPlayEnabled = new Boolean();
    this.isPauseEnabled = new Boolean();
    this.isNextEnabled = new Boolean();
    this.isPreviousEnabled = new Boolean();
    this.isEnabled = new Boolean();
    this.isChannelDownEnabled = new Boolean();
    this.isFastForwardEnabled = new Boolean();
    this.isChannelUpEnabled = new Boolean();
    this.playbackStatus = new MediaPlaybackStatus();
    this.isStopEnabled = new Boolean();
    this.isRewindEnabled = new Boolean();
    this.isRecordEnabled = new Boolean();
    this.displayUpdater = new SystemMediaTransportControlsDisplayUpdater();
    this.soundLevel = new SoundLevel();
    this.shuffleEnabled = new Boolean();
    this.playbackRate = new Number();
    this.autoRepeatMode = new MediaPlaybackAutoRepeatMode();
  };
  

  cls.prototype.updateTimelineProperties = function updateTimelineProperties(timelineProperties) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="timelineProperties" type="SystemMediaTransportControlsTimelineProperties">A param.</param>
    /// </signature>
  }


  cls.getForCurrentView = function getForCurrentView() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="SystemMediaTransportControls" />
    /// </signature>
    return new SystemMediaTransportControls();
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.SystemMediaTransportControls = SystemMediaTransportControls;

MediaTimelineController = (function () {
  var cls = function MediaTimelineController() {
    this.position = new Number();
    this.clockRate = new Number();
    this.state = new MediaTimelineControllerState();
    this.isLoopingEnabled = new Boolean();
    this.duration = new Number();
  };
  

  cls.prototype.start = function start() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.resume = function resume() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.pause = function pause() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.MediaTimelineController = MediaTimelineController;

MediaTimelineControllerFailedEventArgs = (function () {
  var cls = function MediaTimelineControllerFailedEventArgs() {
    this.extendedError = new Number();
  };
  

  return cls;
}) ();
exports.MediaTimelineControllerFailedEventArgs = MediaTimelineControllerFailedEventArgs;

IMediaExtension = (function () {
  var cls = function IMediaExtension() {
  };
  

  cls.prototype.setProperties = function setProperties(configuration) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="configuration" type="Object">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.IMediaExtension = IMediaExtension;

MediaExtensionManager = (function () {
  var cls = function MediaExtensionManager() {
  };
  

  cls.prototype.registerSchemeHandler = function registerSchemeHandler(activatableClassId, scheme) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="activatableClassId" type="String">A param.</param>
    /// <param name="scheme" type="String">A param.</param>
    /// </signature>
  }

cls.prototype.registerSchemeHandler = function registerSchemeHandler(activatableClassId, scheme, configuration) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="activatableClassId" type="String">A param.</param>
    /// <param name="scheme" type="String">A param.</param>
    /// <param name="configuration" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.registerByteStreamHandler = function registerByteStreamHandler(activatableClassId, fileExtension, mimeType) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="activatableClassId" type="String">A param.</param>
    /// <param name="fileExtension" type="String">A param.</param>
    /// <param name="mimeType" type="String">A param.</param>
    /// </signature>
  }

cls.prototype.registerByteStreamHandler = function registerByteStreamHandler(activatableClassId, fileExtension, mimeType, configuration) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="activatableClassId" type="String">A param.</param>
    /// <param name="fileExtension" type="String">A param.</param>
    /// <param name="mimeType" type="String">A param.</param>
    /// <param name="configuration" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.registerAudioDecoder = function registerAudioDecoder(activatableClassId, inputSubtype, outputSubtype) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="activatableClassId" type="String">A param.</param>
    /// <param name="inputSubtype" type="String">A param.</param>
    /// <param name="outputSubtype" type="String">A param.</param>
    /// </signature>
  }

cls.prototype.registerAudioDecoder = function registerAudioDecoder(activatableClassId, inputSubtype, outputSubtype, configuration) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="activatableClassId" type="String">A param.</param>
    /// <param name="inputSubtype" type="String">A param.</param>
    /// <param name="outputSubtype" type="String">A param.</param>
    /// <param name="configuration" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.registerAudioEncoder = function registerAudioEncoder(activatableClassId, inputSubtype, outputSubtype) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="activatableClassId" type="String">A param.</param>
    /// <param name="inputSubtype" type="String">A param.</param>
    /// <param name="outputSubtype" type="String">A param.</param>
    /// </signature>
  }

cls.prototype.registerAudioEncoder = function registerAudioEncoder(activatableClassId, inputSubtype, outputSubtype, configuration) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="activatableClassId" type="String">A param.</param>
    /// <param name="inputSubtype" type="String">A param.</param>
    /// <param name="outputSubtype" type="String">A param.</param>
    /// <param name="configuration" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.registerVideoDecoder = function registerVideoDecoder(activatableClassId, inputSubtype, outputSubtype) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="activatableClassId" type="String">A param.</param>
    /// <param name="inputSubtype" type="String">A param.</param>
    /// <param name="outputSubtype" type="String">A param.</param>
    /// </signature>
  }

cls.prototype.registerVideoDecoder = function registerVideoDecoder(activatableClassId, inputSubtype, outputSubtype, configuration) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="activatableClassId" type="String">A param.</param>
    /// <param name="inputSubtype" type="String">A param.</param>
    /// <param name="outputSubtype" type="String">A param.</param>
    /// <param name="configuration" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.registerVideoEncoder = function registerVideoEncoder(activatableClassId, inputSubtype, outputSubtype) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="activatableClassId" type="String">A param.</param>
    /// <param name="inputSubtype" type="String">A param.</param>
    /// <param name="outputSubtype" type="String">A param.</param>
    /// </signature>
  }

cls.prototype.registerVideoEncoder = function registerVideoEncoder(activatableClassId, inputSubtype, outputSubtype, configuration) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="activatableClassId" type="String">A param.</param>
    /// <param name="inputSubtype" type="String">A param.</param>
    /// <param name="outputSubtype" type="String">A param.</param>
    /// <param name="configuration" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.registerMediaExtensionForAppService = function registerMediaExtensionForAppService(extension, connection) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="extension" type="IMediaExtension">A param.</param>
    /// <param name="connection" type="Object">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.MediaExtensionManager = MediaExtensionManager;

VideoEffects = (function () {
  var cls = function VideoEffects() {
  };
  

  cls.videoStabilization = new String();
  return cls;
}) ();
exports.VideoEffects = VideoEffects;

MediaControl = (function () {
  var cls = function MediaControl() {
  };
  

  cls.trackName = new String();
  cls.isPlaying = new Boolean();
  cls.artistName = new String();
  cls.albumArt = new Object();
  cls.soundLevel = new SoundLevel();
    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.MediaControl = MediaControl;

