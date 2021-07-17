declare module "windows.media" {
  export class BitmapBounds {
    x: Number;
    y: Number;
    width: Number;
    height: Number;
    constructor();
  }

  export class MediaTimeRange {
    start: Number;
    end: Number;
    constructor();
  }

  export class MediaControlContract {
    constructor();
  }

  export enum AudioBufferAccessMode {
    read,
    readWrite,
    write,
  }

  export enum SoundLevel {
    muted,
    low,
    full,
  }

  export enum MediaPlaybackType {
    unknown,
    music,
    video,
    image,
  }

  export enum MediaPlaybackAutoRepeatMode {
    none,
    track,
    list,
  }

  export enum MediaPlaybackStatus {
    closed,
    changing,
    stopped,
    playing,
    paused,
  }

  export enum SystemMediaTransportControlsButton {
    play,
    pause,
    stop,
    record,
    fastForward,
    rewind,
    next,
    previous,
    channelUp,
    channelDown,
  }

  export enum SystemMediaTransportControlsProperty {
    soundLevel,
  }

  export enum MediaTimelineControllerState {
    paused,
    running,
    stalled,
    error,
  }

  export enum AudioProcessing {
    default,
    raw,
  }

  export class MediaProcessingTriggerDetails {
    arguments: Object;
    constructor();

  }

  export class IMediaFrame {
    duration: Number;
    extendedProperties: Object;
    isDiscontinuous: Boolean;
    isReadOnly: Boolean;
    relativeTime: Number;
    systemRelativeTime: Number;
    type: String;
    constructor();

  }

  export class VideoFrame {
    systemRelativeTime: Number;
    relativeTime: Number;
    isDiscontinuous: Boolean;
    duration: Number;
    extendedProperties: Object;
    isReadOnly: Boolean;
    type: String;
    direct3DSurface: Object;
    softwareBitmap: Object;
    constructor();
    constructor(format: Number, width: Number, height: Number);
    constructor(format: Number, width: Number, height: Number, alpha: Number);

    static createAsDirect3D11SurfaceBacked(format: Number, width: Number, height: Number): VideoFrame;
    static createAsDirect3D11SurfaceBacked(format: Number, width: Number, height: Number, device: Object): VideoFrame;


    static createWithSoftwareBitmap(bitmap: Object): VideoFrame;


    static createWithDirect3D11Surface(surface: Object): VideoFrame;


    copyToAsync(frame: VideoFrame, callback: (error: Error) => void): void ;
    copyToAsync(frame: VideoFrame, sourceBounds: BitmapBounds, destinationBounds: BitmapBounds, callback: (error: Error) => void): void ;

    close(): void;
  }

  export class AudioBuffer {
    length: Number;
    capacity: Number;
    constructor();

    createReference(): Object;

    close(): void;
  }

  export class AudioFrame {
    systemRelativeTime: Number;
    relativeTime: Number;
    isDiscontinuous: Boolean;
    duration: Number;
    extendedProperties: Object;
    isReadOnly: Boolean;
    type: String;
    constructor();
    constructor(capacity: Number);

    lockBuffer(mode: AudioBufferAccessMode): AudioBuffer;

    close(): void;
  }

  export class IMediaMarker {
    mediaMarkerType: String;
    text: String;
    time: Number;
    constructor();

  }

  export class IMediaMarkers {
    markers: Object;
    constructor();

  }

  export class MediaMarkerTypes {
    static bookmark: String;
    constructor();

  }

  export class SystemMediaTransportControlsTimelineProperties {
    startTime: Number;
    position: Number;
    minSeekTime: Number;
    maxSeekTime: Number;
    endTime: Number;
    constructor();

  }

  export class MusicDisplayProperties {
    title: String;
    artist: String;
    albumArtist: String;
    trackNumber: Number;
    albumTitle: String;
    genres: Object;
    albumTrackCount: Number;
    constructor();

  }

  export class VideoDisplayProperties {
    title: String;
    subtitle: String;
    genres: Object;
    constructor();

  }

  export class ImageDisplayProperties {
    title: String;
    subtitle: String;
    constructor();

  }

  export class SystemMediaTransportControlsDisplayUpdater {
    type: MediaPlaybackType;
    thumbnail: Object;
    appMediaId: String;
    imageProperties: ImageDisplayProperties;
    musicProperties: MusicDisplayProperties;
    videoProperties: VideoDisplayProperties;
    constructor();

    copyFromFileAsync(type: MediaPlaybackType, source: Object, callback: (error: Error, result: Boolean) => void): void ;

    clearAll(): void;

    update(): void;

  }

  export class SystemMediaTransportControlsButtonPressedEventArgs {
    button: SystemMediaTransportControlsButton;
    constructor();

  }

  export class SystemMediaTransportControlsPropertyChangedEventArgs {
    property: SystemMediaTransportControlsProperty;
    constructor();

  }

  export class PlaybackPositionChangeRequestedEventArgs {
    requestedPlaybackPosition: Number;
    constructor();

  }

  export class PlaybackRateChangeRequestedEventArgs {
    requestedPlaybackRate: Number;
    constructor();

  }

  export class ShuffleEnabledChangeRequestedEventArgs {
    requestedShuffleEnabled: Boolean;
    constructor();

  }

  export class AutoRepeatModeChangeRequestedEventArgs {
    requestedAutoRepeatMode: MediaPlaybackAutoRepeatMode;
    constructor();

  }

  export class SystemMediaTransportControls {
    isPlayEnabled: Boolean;
    isPauseEnabled: Boolean;
    isNextEnabled: Boolean;
    isPreviousEnabled: Boolean;
    isEnabled: Boolean;
    isChannelDownEnabled: Boolean;
    isFastForwardEnabled: Boolean;
    isChannelUpEnabled: Boolean;
    playbackStatus: MediaPlaybackStatus;
    isStopEnabled: Boolean;
    isRewindEnabled: Boolean;
    isRecordEnabled: Boolean;
    displayUpdater: SystemMediaTransportControlsDisplayUpdater;
    soundLevel: SoundLevel;
    shuffleEnabled: Boolean;
    playbackRate: Number;
    autoRepeatMode: MediaPlaybackAutoRepeatMode;
    constructor();

    static getForCurrentView(): SystemMediaTransportControls;


    updateTimelineProperties(timelineProperties: SystemMediaTransportControlsTimelineProperties): void;

    addListener(type: "ButtonPressed", listener: (ev: Event) => void): void ;
    removeListener(type: "ButtonPressed", listener: (ev: Event) => void): void ;
    on(type: "ButtonPressed", listener: (ev: Event) => void): void ;
    off(type: "ButtonPressed", listener: (ev: Event) => void): void ;
    
    addListener(type: "PropertyChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "PropertyChanged", listener: (ev: Event) => void): void ;
    on(type: "PropertyChanged", listener: (ev: Event) => void): void ;
    off(type: "PropertyChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: "AutoRepeatModeChangeRequested", listener: (ev: Event) => void): void ;
    removeListener(type: "AutoRepeatModeChangeRequested", listener: (ev: Event) => void): void ;
    on(type: "AutoRepeatModeChangeRequested", listener: (ev: Event) => void): void ;
    off(type: "AutoRepeatModeChangeRequested", listener: (ev: Event) => void): void ;
    
    addListener(type: "PlaybackPositionChangeRequested", listener: (ev: Event) => void): void ;
    removeListener(type: "PlaybackPositionChangeRequested", listener: (ev: Event) => void): void ;
    on(type: "PlaybackPositionChangeRequested", listener: (ev: Event) => void): void ;
    off(type: "PlaybackPositionChangeRequested", listener: (ev: Event) => void): void ;
    
    addListener(type: "PlaybackRateChangeRequested", listener: (ev: Event) => void): void ;
    removeListener(type: "PlaybackRateChangeRequested", listener: (ev: Event) => void): void ;
    on(type: "PlaybackRateChangeRequested", listener: (ev: Event) => void): void ;
    off(type: "PlaybackRateChangeRequested", listener: (ev: Event) => void): void ;
    
    addListener(type: "ShuffleEnabledChangeRequested", listener: (ev: Event) => void): void ;
    removeListener(type: "ShuffleEnabledChangeRequested", listener: (ev: Event) => void): void ;
    on(type: "ShuffleEnabledChangeRequested", listener: (ev: Event) => void): void ;
    off(type: "ShuffleEnabledChangeRequested", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class MediaTimelineController {
    position: Number;
    clockRate: Number;
    state: MediaTimelineControllerState;
    isLoopingEnabled: Boolean;
    duration: Number;
    constructor();

    start(): void;

    resume(): void;

    pause(): void;

    addListener(type: "PositionChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "PositionChanged", listener: (ev: Event) => void): void ;
    on(type: "PositionChanged", listener: (ev: Event) => void): void ;
    off(type: "PositionChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: "StateChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "StateChanged", listener: (ev: Event) => void): void ;
    on(type: "StateChanged", listener: (ev: Event) => void): void ;
    off(type: "StateChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: "Ended", listener: (ev: Event) => void): void ;
    removeListener(type: "Ended", listener: (ev: Event) => void): void ;
    on(type: "Ended", listener: (ev: Event) => void): void ;
    off(type: "Ended", listener: (ev: Event) => void): void ;
    
    addListener(type: "Failed", listener: (ev: Event) => void): void ;
    removeListener(type: "Failed", listener: (ev: Event) => void): void ;
    on(type: "Failed", listener: (ev: Event) => void): void ;
    off(type: "Failed", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class MediaTimelineControllerFailedEventArgs {
    extendedError: Number;
    constructor();

  }

  export class IMediaExtension {
    constructor();

    setProperties(configuration: Object): void;

  }

  export class MediaExtensionManager {
    constructor();

    registerSchemeHandler(activatableClassId: String, scheme: String): void;
    registerSchemeHandler(activatableClassId: String, scheme: String, configuration: Object): void;

    registerByteStreamHandler(activatableClassId: String, fileExtension: String, mimeType: String): void;
    registerByteStreamHandler(activatableClassId: String, fileExtension: String, mimeType: String, configuration: Object): void;

    registerAudioDecoder(activatableClassId: String, inputSubtype: String, outputSubtype: String): void;
    registerAudioDecoder(activatableClassId: String, inputSubtype: String, outputSubtype: String, configuration: Object): void;

    registerAudioEncoder(activatableClassId: String, inputSubtype: String, outputSubtype: String): void;
    registerAudioEncoder(activatableClassId: String, inputSubtype: String, outputSubtype: String, configuration: Object): void;

    registerVideoDecoder(activatableClassId: String, inputSubtype: String, outputSubtype: String): void;
    registerVideoDecoder(activatableClassId: String, inputSubtype: String, outputSubtype: String, configuration: Object): void;

    registerVideoEncoder(activatableClassId: String, inputSubtype: String, outputSubtype: String): void;
    registerVideoEncoder(activatableClassId: String, inputSubtype: String, outputSubtype: String, configuration: Object): void;

    registerMediaExtensionForAppService(extension: IMediaExtension, connection: Object): void;

  }

  export class VideoEffects {
    static videoStabilization: String;
    constructor();

  }

  export class MediaControl {
    static trackName: String;
    static isPlaying: Boolean;
    static artistName: String;
    static albumArt: Object;
    static soundLevel: SoundLevel;
    constructor();

    addListener(type: "ChannelDownPressed", listener: (ev: Event) => void): void ;
    removeListener(type: "ChannelDownPressed", listener: (ev: Event) => void): void ;
    on(type: "ChannelDownPressed", listener: (ev: Event) => void): void ;
    off(type: "ChannelDownPressed", listener: (ev: Event) => void): void ;
    
    addListener(type: "ChannelUpPressed", listener: (ev: Event) => void): void ;
    removeListener(type: "ChannelUpPressed", listener: (ev: Event) => void): void ;
    on(type: "ChannelUpPressed", listener: (ev: Event) => void): void ;
    off(type: "ChannelUpPressed", listener: (ev: Event) => void): void ;
    
    addListener(type: "FastForwardPressed", listener: (ev: Event) => void): void ;
    removeListener(type: "FastForwardPressed", listener: (ev: Event) => void): void ;
    on(type: "FastForwardPressed", listener: (ev: Event) => void): void ;
    off(type: "FastForwardPressed", listener: (ev: Event) => void): void ;
    
    addListener(type: "NextTrackPressed", listener: (ev: Event) => void): void ;
    removeListener(type: "NextTrackPressed", listener: (ev: Event) => void): void ;
    on(type: "NextTrackPressed", listener: (ev: Event) => void): void ;
    off(type: "NextTrackPressed", listener: (ev: Event) => void): void ;
    
    addListener(type: "PausePressed", listener: (ev: Event) => void): void ;
    removeListener(type: "PausePressed", listener: (ev: Event) => void): void ;
    on(type: "PausePressed", listener: (ev: Event) => void): void ;
    off(type: "PausePressed", listener: (ev: Event) => void): void ;
    
    addListener(type: "PlayPauseTogglePressed", listener: (ev: Event) => void): void ;
    removeListener(type: "PlayPauseTogglePressed", listener: (ev: Event) => void): void ;
    on(type: "PlayPauseTogglePressed", listener: (ev: Event) => void): void ;
    off(type: "PlayPauseTogglePressed", listener: (ev: Event) => void): void ;
    
    addListener(type: "PlayPressed", listener: (ev: Event) => void): void ;
    removeListener(type: "PlayPressed", listener: (ev: Event) => void): void ;
    on(type: "PlayPressed", listener: (ev: Event) => void): void ;
    off(type: "PlayPressed", listener: (ev: Event) => void): void ;
    
    addListener(type: "PreviousTrackPressed", listener: (ev: Event) => void): void ;
    removeListener(type: "PreviousTrackPressed", listener: (ev: Event) => void): void ;
    on(type: "PreviousTrackPressed", listener: (ev: Event) => void): void ;
    off(type: "PreviousTrackPressed", listener: (ev: Event) => void): void ;
    
    addListener(type: "RecordPressed", listener: (ev: Event) => void): void ;
    removeListener(type: "RecordPressed", listener: (ev: Event) => void): void ;
    on(type: "RecordPressed", listener: (ev: Event) => void): void ;
    off(type: "RecordPressed", listener: (ev: Event) => void): void ;
    
    addListener(type: "RewindPressed", listener: (ev: Event) => void): void ;
    removeListener(type: "RewindPressed", listener: (ev: Event) => void): void ;
    on(type: "RewindPressed", listener: (ev: Event) => void): void ;
    off(type: "RewindPressed", listener: (ev: Event) => void): void ;
    
    addListener(type: "SoundLevelChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "SoundLevelChanged", listener: (ev: Event) => void): void ;
    on(type: "SoundLevelChanged", listener: (ev: Event) => void): void ;
    off(type: "SoundLevelChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: "StopPressed", listener: (ev: Event) => void): void ;
    removeListener(type: "StopPressed", listener: (ev: Event) => void): void ;
    on(type: "StopPressed", listener: (ev: Event) => void): void ;
    off(type: "StopPressed", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

}



