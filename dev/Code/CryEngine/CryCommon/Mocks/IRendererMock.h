/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
#pragma once

#include <IRenderer.h>
#include <IImage.h>
#include <gmock/gmock.h>

// the following was generated using google's python script to autogenerate mocks.
// however, it needed some hand-editing to make it work, so if you add functions to IRenderer,
// it will probably be better to just manually add them here than try to run the script again
// hand-edits are marked with 'hand-edit'.  Everything else was autogenerated.

#if defined(AZ_COMPILER_MSVC) 
    // 4373 is generated by google mock on VS2015 only.  It warns that this code is not going to compile
    // on VS2013 and earlier.  Becuase VS2015 was a transitionary VS, MS added a bunch of warnings like this, 
    // warning developers when they were writing code that would not be backwards compatible with the non-standard
    // VS2013 and earlier.  Google mock generates code that falls in this category but this is something we can
    // safely ignore, as our software is for versions later than that.
    #pragma warning(push)
    #pragma warning(disable:4373) 
#endif // AZ_COMPILER_MSVC

class IRendererMock
    : public IRenderer
{
public:
    MOCK_METHOD1(AddRenderDebugListener,
        void(IRenderDebugListener * pRenderDebugListener));
    MOCK_METHOD1(RemoveRenderDebugListener,
        void(IRenderDebugListener * pRenderDebugListener));
    MOCK_CONST_METHOD0(GetRenderType,
        ERenderType());

    // Hand-edit: Googlemock cannot handle 14 param functions.
    WIN_HWND Init(int, int, int, int, unsigned int, int, int, bool, bool, WIN_HINSTANCE, WIN_HWND = 0,
        bool = false, const SCustomRenderInitArgs*  = 0, bool = false) override { return nullptr; }

    MOCK_METHOD0(PostInit,
        void());
    MOCK_CONST_METHOD0(IsPost3DRendererEnabled,
        bool());
    MOCK_METHOD0(GetFeatures,
        int());

    // Hand-edit: Googlemock doesn't like 'const void' as a return type:
    const void SetApiVersion(const AZStd::string&) override {}
    const void SetAdapterDescription(const AZStd::string&) override {}

    MOCK_CONST_METHOD0(GetApiVersion,
        const AZStd::string& ());
    MOCK_CONST_METHOD0(GetAdapterDescription,
        const AZStd::string& ());
    MOCK_METHOD3(GetVideoMemoryUsageStats,
        void(size_t&, size_t&, bool));
    MOCK_METHOD0(GetNumGeomInstances,
        int());
    MOCK_METHOD0(GetNumGeomInstanceDrawCalls,
        int());
    MOCK_METHOD0(GetCurrentNumberOfDrawCalls,
        int());
    MOCK_METHOD2(GetCurrentNumberOfDrawCalls,
        void(int& nGeneral, int& nShadowGen));
    MOCK_METHOD1(GetCurrentNumberOfDrawCalls,
        int(const uint32 EFSListMask));
    MOCK_METHOD1(GetCurrentDrawCallRTTimes,
        float(const uint32 EFSListMask));
    MOCK_METHOD1(SetDebugRenderNode,
        void(IRenderNode * pRenderNode));
    MOCK_CONST_METHOD1(IsDebugRenderNode,
        bool(IRenderNode * pRenderNode));
    MOCK_METHOD1(DeleteContext,
        bool(WIN_HWND hWnd));
    MOCK_METHOD4(CreateContext,
        bool(WIN_HWND, bool, int, int));
    MOCK_METHOD1(SetCurrentContext,
        bool(WIN_HWND hWnd));
    MOCK_METHOD0(MakeMainContextActive,
        void());
    MOCK_METHOD0(GetCurrentContextHWND,
        WIN_HWND());
    MOCK_METHOD0(IsCurrentContextMainVP,
        bool());
    MOCK_CONST_METHOD0(GetCurrentContextViewportHeight,
        int());
    MOCK_CONST_METHOD0(GetCurrentContextViewportWidth,
        int());
    MOCK_METHOD1(ShutDown,
        void(bool));
    MOCK_METHOD0(ShutDownFast,
        void());
    MOCK_METHOD1(EnumDisplayFormats,
        int(SDispFormat * Formats));
    MOCK_METHOD1(EnumAAFormats,
        int(SAAFormat * Formats));
    MOCK_METHOD6(ChangeResolution,
        bool(int nNewWidth, int nNewHeight, int nNewColDepth, int nNewRefreshHZ, bool bFullScreen, bool bForceReset));
    MOCK_METHOD0(BeginFrame,
        void());
    MOCK_METHOD1(InitSystemResources,
        void(int nFlags));
    MOCK_METHOD0(InitTexturesSemantics,
        void());
    MOCK_METHOD1(FreeResources,
        void(int nFlags));
    MOCK_METHOD0(Release,
        void());
    MOCK_METHOD1(RenderDebug,
        void(bool));
    MOCK_METHOD0(EndFrame,
        void());
    MOCK_METHOD0(ForceSwapBuffers,
        void());
    MOCK_METHOD0(TryFlush,
        void());
    MOCK_CONST_METHOD4(GetViewport,
        void(int* x, int* y, int* width, int* height));
    MOCK_METHOD5(SetViewport,
        void(int, int, int, int, int));
    MOCK_METHOD4(SetRenderTile,
        void(f32, f32, f32, f32));
    MOCK_METHOD4(SetScissor,
        void(int, int, int, int));
    MOCK_METHOD0(GetViewProjectionMatrix,
        Matrix44A & ());
    MOCK_METHOD1(SetTranspOrigCameraProjMatrix,
        void(Matrix44A & matrix));
    MOCK_METHOD2(GetScreenAspect,
        EScreenAspectRatio(int nWidth, int nHeight));
    MOCK_METHOD2(SetViewportDownscale,
        Vec2(float xscale, float yscale));
    MOCK_METHOD1(SetViewParameters,
        void(const CameraViewParameters& viewParameters));
    MOCK_METHOD1(ApplyViewParameters,
        void(const CameraViewParameters& viewParameters));
    MOCK_METHOD5(DrawDynVB,
        void(SVF_P3F_C4B_T2F * pBuf, uint16 * pInds, int nVerts, int nInds, const PublicRenderPrimitiveType nPrimType));

    // Hand-edit: google mock has issues with DynUiPrimitiveList
    void DrawDynUiPrimitiveList(DynUiPrimitiveList& primitives, int totalNumVertices, int totalNumIndices) override { return; }

    MOCK_METHOD1(SetCamera,
        void(const CCamera& cam));
    MOCK_METHOD0(GetCamera,
        const CCamera& ());
    MOCK_METHOD1(GetRenderViewForThread,
        CRenderView * (int nThreadID));
    MOCK_METHOD1(SetGammaDelta,
        bool(const float fGamma));
    MOCK_METHOD0(RestoreGamma,
        void(void));
    MOCK_METHOD3(ChangeDisplay,
        bool(unsigned int width, unsigned int height, unsigned int cbpp));
    MOCK_METHOD5(ChangeViewport,
        void(unsigned int, unsigned int, unsigned int, unsigned int, bool));
    MOCK_CONST_METHOD6(SaveTga,
        bool(unsigned char* sourcedata, int sourceformat, int w, int h, const char* filename, bool flip));
    MOCK_METHOD1(SetTexture,
        void(int tnum));
    MOCK_METHOD2(SetTexture,
        void(int tnum, int nUnit));
    MOCK_METHOD0(SetWhiteTexture,
        void());
    MOCK_CONST_METHOD0(GetWhiteTextureId,
        int());
    MOCK_CONST_METHOD0(GetBlackTextureId,
        int());

    // Hand-edit: google mock can only do up to 10 parameters
    void Draw2dImage(float, float, float, float, int, float, float, float, float, float, float, float, float, float, float) override {};
    MOCK_METHOD1(Draw2dImageStretchMode,
        void(bool stretch));

    // Hand-edit: google mock can only do up to 10 parameters
    void Push2dImage(float, float, float, float, int, float, float, float, float, float, float, float, float, float, float, float) override {};

    MOCK_METHOD0(Draw2dImageList,
        void());

    // Hand-edit:  Hand-edit: google mock can only do up to 10 parameters
    void DrawImage(float, float, float, float, int, float, float, float, float, float, float, float, float, bool) override {}

    // Hand-edit: google mock can only do up to 10 parameters
    void DrawImageWithUV(float, float, float, float, float, int, float*, float*, float, float, float, float, bool) override {}

    MOCK_METHOD1(PushWireframeMode,
        void(int mode));
    MOCK_METHOD0(PopWireframeMode,
        void());
    MOCK_CONST_METHOD0(GetHeight,
        int());
    MOCK_CONST_METHOD0(GetWidth,
        int());
    MOCK_CONST_METHOD0(GetPixelAspectRatio,
        float());
    MOCK_CONST_METHOD0(GetOverlayHeight,
        int());
    MOCK_CONST_METHOD0(GetOverlayWidth,
        int());
    MOCK_CONST_METHOD0(GetMaxSquareRasterDimension,
        int());
    MOCK_METHOD0(SwitchToNativeResolutionBackbuffer,
        void());
    MOCK_METHOD1(GetMemoryUsage,
        void(ICrySizer * Sizer));
    MOCK_METHOD1(GetBandwidthStats,
        void(float* fBandwidthRequested));
    MOCK_METHOD1(SetTextureStreamListener,
        void(ITextureStreamListener * pListener));
    MOCK_METHOD2(GetOcclusionBuffer,
        int(uint16 * pOutOcclBuffer, Matrix44 * pmCamBuffer));
    MOCK_METHOD2(ScreenShot,
        bool(const char*, int));
    MOCK_METHOD0(GetColorBpp,
        int());
    MOCK_METHOD0(GetDepthBpp,
        int());
    MOCK_METHOD0(GetStencilBpp,
        int());
    MOCK_CONST_METHOD0(IsStereoEnabled,
        bool());
    MOCK_CONST_METHOD0(GetNearestRangeMax,
        float());
    MOCK_METHOD0(GetPerInstanceConstantBufferPoolPointer,
        PerInstanceConstantBufferPool * ());
    MOCK_METHOD6(ProjectToScreen,
        bool(float ptx, float pty, float ptz, float* sx, float* sy, float* sz));
    MOCK_METHOD9(UnProject,
        int(float sx, float sy, float sz, float* px, float* py, float* pz, const float modelMatrix[16], const float projMatrix[16], const int viewport[4]));
    MOCK_METHOD6(UnProjectFromScreen,
        int(float sx, float sy, float sz, float* px, float* py, float* pz));
    MOCK_METHOD1(GetModelViewMatrix,
        void(float* mat));
    MOCK_METHOD1(GetProjectionMatrix,
        void(float* mat));
    MOCK_METHOD7(WriteDDS,
        bool(const byte * dat, int wdt, int hgt, int Size, const char* name, ETEX_Format eF, int NumMips));
    MOCK_METHOD6(WriteTGA,
        bool(const byte * dat, int wdt, int hgt, const char* name, int src_bits_per_pixel, int dest_bits_per_pixel));
    MOCK_METHOD6(WriteJPG,
        bool(const byte*, int, int, char*, int, int));
    MOCK_METHOD6(FontCreateTexture,
        int(int, int, byte*, ETEX_Format, bool, const char*));
    MOCK_METHOD6(FontUpdateTexture,
        bool(int nTexId, int X, int Y, int USize, int VSize, byte * pData));
    MOCK_METHOD2(FontSetTexture,
        void(int nTexId, int nFilterMode));
    MOCK_METHOD2(FontSetRenderingState,
        void(bool overrideViewProjMatrices, TransformationMatrices & backupMatrices));
    MOCK_METHOD3(FontSetBlending,
        void(int src, int dst, int baseState));
    MOCK_METHOD2(FontRestoreRenderingState,
        void(bool overrideViewProjMatrices, const TransformationMatrices& restoringMatrices));
    MOCK_METHOD3(FlushRTCommands,
        bool(bool bWait, bool bImmediatelly, bool bForce));
    MOCK_CONST_METHOD7(DrawStringU,
        void(IFFont_RenderProxy * pFont, float x, float y, float z, const char* pStr, const bool asciiMultiLine, const STextDrawContext& ctx));
    MOCK_METHOD0(RT_CurThreadList,
        int());
    MOCK_METHOD6(EF_PrecacheResource,
        bool(SShaderItem*, float, float, int, int, int));
    MOCK_METHOD4(EF_PrecacheResource,
        bool(IShader * pSH, float fMipFactor, float fTimeToReady, int Flags));
    MOCK_METHOD6(EF_PrecacheResource,
        bool(ITexture*, float, float, int, int, int));
    MOCK_METHOD6(EF_PrecacheResource,
        bool(IRenderMesh * pPB, _smart_ptr<IMaterial> pMaterial, float fMipFactor, float fTimeToReady, int Flags, int nUpdateId));
    MOCK_METHOD5(EF_PrecacheResource,
        bool(CDLight * pLS, float fMipFactor, float fTimeToReady, int Flags, int nUpdateId));

    // Hand-edit: google mock can only do up to 10 parameters
    ITexture* EF_CreateCompositeTexture(int type, const char* szName, int nWidth, int nHeight, int nDepth, int nMips, int nFlags, ETEX_Format eTF, const STexComposition* pCompositions, size_t nCompositions, int8 nPriority = -1) override { return nullptr; }

    MOCK_METHOD0(PostLevelLoading,
        void());
    MOCK_METHOD0(PostLevelUnload,
        void());
    MOCK_METHOD3(EF_AddMultipleParticlesToScene,
        void(const SAddParticlesToSceneJob * jobs, size_t numJobs, const SRenderingPassInfo& passInfo));
    MOCK_METHOD1(GetMemoryUsageParticleREs,
        void(ICrySizer * pSizer));
    MOCK_METHOD10(EF_AddPolygonToScene,
        CRenderObject * (SShaderItem & si, int numPts, const SVF_P3F_C4B_T2F * verts, const SPipTangents * tangs, CRenderObject * obj, const SRenderingPassInfo& passInfo, uint16 * inds, int ninds, int nAW, const SRendItemSorter& rendItemSorter));
    MOCK_METHOD10(EF_AddPolygonToScene,
        CRenderObject * (SShaderItem & si, CRenderObject * obj, const SRenderingPassInfo& passInfo, int numPts, int ninds, SVF_P3F_C4B_T2F * &verts, SPipTangents * &tangs, uint16 * &inds, int nAW, const SRendItemSorter& rendItemSorter));
    MOCK_METHOD0(ForceUpdateGlobalShaderParameters,
        void());
    MOCK_METHOD1(EF_SetShaderMissCallback,
        void(ShaderCacheMissCallback callback));
    MOCK_METHOD0(EF_GetShaderMissLogPath,
        const char*());
    MOCK_METHOD1(EF_GetShaderNames,
        string * (int& nNumShaders));
    MOCK_METHOD1(EF_ReloadFile,
        bool(const char* szFileName));
    MOCK_METHOD1(EF_ReloadFile_Request,
        bool(const char* szFileName));
    MOCK_METHOD2(EF_LoadImage,
        _smart_ptr<IImageFile>(const char* szFileName, uint32 nFlags));
    MOCK_METHOD3(EF_GetRemapedShaderMaskGen,
        uint64(const char*, uint64, bool));
    MOCK_METHOD3(EF_GetShaderGlobalMaskGenFromString,
        uint64(const char*, const char*, uint64));
    MOCK_METHOD2(EF_GetStringFromShaderGlobalMaskGen,
        AZStd::string(const char*, uint64));
    MOCK_CONST_METHOD1(GetShaderProfile,
        const SShaderProfile& (EShaderType eST));
    MOCK_METHOD2(EF_SetShaderQuality,
        void(EShaderType eST, EShaderQuality eSQ));
    MOCK_CONST_METHOD0(EF_GetRenderQuality,
        ERenderQuality());
    MOCK_METHOD1(EF_GetShaderQuality,
        EShaderQuality(EShaderType eST));
    MOCK_METHOD5(EF_LoadShaderItem,
        SShaderItem(const char*, bool, int, SInputShaderResources*, uint64));
    MOCK_METHOD3(EF_LoadShader,
        IShader * (const char*, int, uint64));
    MOCK_METHOD1(EF_ReloadShaderFiles,
        void(int nCategory));
    MOCK_METHOD0(EF_ReloadTextures,
        void());
    MOCK_METHOD1(EF_GetTextureByID,
        ITexture * (int Id));
    MOCK_METHOD2(EF_GetTextureByName,
        ITexture * (const char*, uint32));
    MOCK_METHOD2(EF_LoadTexture,
        ITexture * (const char*, uint32));
    MOCK_METHOD2(EF_LoadCubemapTexture,
        ITexture * (const char*, uint32));
    MOCK_METHOD1(EF_LoadDefaultTexture,
        ITexture * (const char* nameTex));
    MOCK_METHOD1(EF_LoadLightmap,
        int(const char* name));
    MOCK_METHOD3(EF_RenderEnvironmentCubeHDR,
        bool(int size, Vec3 & Pos, TArray<unsigned short>&vecData));
    MOCK_METHOD1(EF_CreateRE,
        IRenderElement * (EDataType edt));
    MOCK_METHOD1(EF_StartEf,
        void(const SRenderingPassInfo& passInfo));
    MOCK_METHOD3(EF_GetObjData,
        SRenderObjData * (CRenderObject * pObj, bool bCreate, int nThreadID));
    MOCK_METHOD1(EF_GetObject_Temp,
        CRenderObject * (int nThreadID));
    MOCK_METHOD2(EF_DuplicateRO,
        CRenderObject * (CRenderObject * pObj, const SRenderingPassInfo& passInfo));
    MOCK_METHOD7(EF_AddEf,
        void(IRenderElement * pRE, SShaderItem & pSH, CRenderObject * pObj, const SRenderingPassInfo& passInfo, int nList, int nAW, const SRendItemSorter& rendItemSorter));
    MOCK_METHOD4(EF_EndEf3D,
        void(const int nFlags, const int nPrecacheUpdateId, const int nNearPrecacheUpdateId, const SRenderingPassInfo& passInfo));
    MOCK_METHOD1(EF_InvokeShadowMapRenderJobs,
        void(const int nFlags));
    MOCK_METHOD1(EF_IsFakeDLight,
        bool(const CDLight * Source));
    MOCK_METHOD2(EF_ADDDlight,
        void(CDLight * Source, const SRenderingPassInfo& passInfo));
    MOCK_METHOD1(EF_UpdateDLight,
        bool(SRenderLight * pDL));
    MOCK_METHOD1(EF_AddDeferredDecal,
        bool(const SDeferredDecal& rDecal));
    MOCK_METHOD4(EF_AddDeferredLight,
        int(const CDLight& pLight, float fMult, const SRenderingPassInfo& passInfo, const SRendItemSorter& rendItemSorter));
    MOCK_METHOD1(EF_GetDeferredLightsNum,
        uint32(eDeferredLightType));
    MOCK_METHOD0(EF_ClearDeferredLightsList,
        void());
    MOCK_METHOD2(EF_GetDeferredLights,
        TArray<SRenderLight>*(const SRenderingPassInfo&, const eDeferredLightType));
    MOCK_METHOD1(EF_AddDeferredClipVolume,
        uint8(const IClipVolume * pClipVolume));
    MOCK_METHOD2(EF_SetDeferredClipVolumeBlendData,
        bool(const IClipVolume * pClipVolume, const SClipVolumeBlendInfo& blendInfo));
    MOCK_METHOD0(EF_ClearDeferredClipVolumesList,
        void());
    MOCK_METHOD0(EF_ReleaseDeferredData,
        void());
    MOCK_METHOD1(EF_ReleaseInputShaderResource,
        void(SInputShaderResources * pRes));
    MOCK_METHOD3(EF_SetPostEffectParam,
        void(const char*, float, bool));
    MOCK_METHOD3(EF_SetPostEffectParamVec4,
        void(const char*, const Vec4&, bool));
    MOCK_METHOD2(EF_SetPostEffectParamString,
        void(const char* pParam, const char* pszArg));
    MOCK_METHOD2(EF_GetPostEffectParam,
        void(const char* pParam, float& fValue));
    MOCK_METHOD2(EF_GetPostEffectParamVec4,
        void(const char* pParam, Vec4 & pValue));
    MOCK_METHOD2(EF_GetPostEffectParamString,
        void(const char* pParam, const char* & pszArg));
    MOCK_METHOD1(EF_GetPostEffectID,
        int32(const char* pPostEffectName));
    MOCK_METHOD1(EF_ResetPostEffects,
        void(bool));
    MOCK_METHOD0(SyncPostEffects,
        void());
    MOCK_METHOD0(EF_DisableTemporalEffects,
        void());
    MOCK_METHOD3(EF_AddWaterSimHit,
        void(const Vec3& vPos, const float scale, const float strength));
    MOCK_METHOD0(EF_DrawWaterSimHits,
        void());
    MOCK_METHOD1(EF_EndEf2D,
        void(const bool bSort));
    MOCK_METHOD0(ForceGC,
        void());
    MOCK_METHOD0(GetPolyCount,
        int());
    MOCK_METHOD2(GetPolyCount,
        void(int& nPolygons, int& nShadowVolPolys));
    MOCK_METHOD1(SetClearColor,
        void(const Vec3& vColor));
    MOCK_METHOD1(SetClearBackground,
        void(bool bClearBackground));
    MOCK_METHOD4(CreateRenderMesh,
        _smart_ptr<IRenderMesh>(const char*, const char*, IRenderMesh::SInitParamerers*, ERenderMeshType));

    // Hand-edit: google mock can only do up to 10 parameters
    virtual _smart_ptr<IRenderMesh> CreateRenderMeshInitialized(
        const void*, int, const AZ::Vertex::Format&, const vtx_idx*, int, const PublicRenderPrimitiveType,
        const char*, const char*, ERenderMeshType = eRMT_Static, int = 1, int = 0,
        bool (* PrepareBufferCallback)(IRenderMesh*, bool) = nullptr, void* = nullptr, bool = false, bool = true,
        const SPipTangents* = nullptr, bool = false, Vec3* = nullptr)
    {
        return _smart_ptr<IRenderMesh>();
    }

    MOCK_METHOD1(GetFrameID,
        int(bool));
    MOCK_CONST_METHOD0(GetCameraFrameID,
        int());
    MOCK_CONST_METHOD0(IsRenderToTextureActive,
        bool());
    MOCK_METHOD4(MakeMatrix,
        void(const Vec3& pos, const Vec3& angles, const Vec3& scale, Matrix34 * mat));
    MOCK_METHOD4(DrawTextQueued,
        void(Vec3 pos, SDrawTextInfo & ti, const char* format, va_list args));
    MOCK_METHOD3(DrawTextQueued,
        void(Vec3 pos, SDrawTextInfo & ti, const char* text));
    MOCK_CONST_METHOD1(ScaleCoordX,
        float(float value));
    MOCK_CONST_METHOD1(ScaleCoordY,
        float(float value));
    MOCK_CONST_METHOD2(ScaleCoord,
        void(float& x, float& y));
    MOCK_METHOD2(SetState,
        void(int, int));
    MOCK_METHOD1(SetCullMode,
        void(int));
    MOCK_METHOD5(SetStencilState,
        void(int, uint32, uint32, uint32, bool));
    MOCK_METHOD1(PushProfileMarker,
        void(const char* label));
    MOCK_METHOD1(PopProfileMarker,
        void(const char* label));
    MOCK_METHOD1(EnableFog,
        bool(bool enable));
    MOCK_METHOD1(SetFogColor,
        void(const ColorF& color));
    MOCK_METHOD4(SetColorOp,
        void(byte eCo, byte eAo, byte eCa, byte eAa));
    MOCK_METHOD1(SetSrgbWrite,
        void(bool srgbWrite));
    MOCK_METHOD1(RequestFlushAllPendingTextureStreamingJobs,
        void(int nFrames));
    MOCK_METHOD1(SetTexturesStreamingGlobalMipFactor,
        void(float fFactor));
    MOCK_METHOD1(GetIRenderAuxGeom,
        IRenderAuxGeom * (void*));
    MOCK_METHOD0(GetISvoRenderer,
        ISvoRenderer * ());
    MOCK_METHOD0(GetIColorGradingController,
        IColorGradingController * ());
    MOCK_METHOD0(GetIStereoRenderer,
        IStereoRenderer * ());
    MOCK_METHOD7(Create2DTexture,
        ITexture * (const char* name, int width, int height, int numMips, int flags, unsigned char* data, ETEX_Format format));

    void TextToScreen(float x, float y, const char* format, ...) override {}
    void TextToScreenColor(int x, int y, float r, float g, float b, float a, const char* format, ...) override {}

    MOCK_METHOD0(ResetToDefault,
        void());
    MOCK_METHOD4(SetMaterialColor,
        void(float r, float g, float b, float a));
    MOCK_METHOD0(SetDefaultRenderStates,
        void());
    MOCK_METHOD10(Graph,
        void(byte * g, int x, int y, int wdt, int hgt, int nC, int type, const char* text, ColorF & color, float fScale));
    MOCK_METHOD0(EF_RenderTextMessages,
        void());
    MOCK_METHOD1(ClearTargetsImmediately,
        void(uint32 nFlags));
    MOCK_METHOD3(ClearTargetsImmediately,
        void(uint32 nFlags, const ColorF& Colors, float fDepth));
    MOCK_METHOD2(ClearTargetsImmediately,
        void(uint32 nFlags, const ColorF& Colors));
    MOCK_METHOD2(ClearTargetsImmediately,
        void(uint32 nFlags, float fDepth));
    MOCK_METHOD1(ClearTargetsLater,
        void(uint32 nFlags));
    MOCK_METHOD3(ClearTargetsLater,
        void(uint32 nFlags, const ColorF& Colors, float fDepth));
    MOCK_METHOD2(ClearTargetsLater,
        void(uint32 nFlags, const ColorF& Colors));
    MOCK_METHOD2(ClearTargetsLater,
        void(uint32 nFlags, float fDepth));
    MOCK_METHOD8(ReadFrameBuffer,
        void(unsigned char*, int, int, int, ERB_Type, bool, int, int));
    MOCK_METHOD4(ReadFrameBufferFast,
        void(uint32*, int, int, bool));
    MOCK_METHOD1(EnableVSync,
        void(bool enable));
    MOCK_METHOD1(CreateResourceAsync,
        void(SResourceAsync * Resource));
    MOCK_METHOD1(ReleaseResourceAsync,
        void(SResourceAsync * Resource));

    // Hand-edit: google mock can only do up to 10 parameters
    unsigned int DownLoadToVideoMemory(const byte*, int, int, ETEX_Format, ETEX_Format, int, bool  = true,
        int  = FILTER_BILINEAR, int  = 0, const char*  = nullptr, int  = 0, EEndian  = eLittleEndian,
        RectI*  = nullptr, bool  = false) override { return 0; }

    unsigned int DownLoadToVideoMemory3D(const byte*, int, int, int d, ETEX_Format, ETEX_Format, int, bool  = true,
        int  = FILTER_BILINEAR, int  = 0, const char*  = nullptr, int  = 0, EEndian  = eLittleEndian,
        RectI*  = nullptr, bool  = false) override { return 0; }

    unsigned int DownLoadToVideoMemoryCube(const byte*, int, int, ETEX_Format, ETEX_Format, int, bool  = true,
        int  = FILTER_BILINEAR, int  = 0, const char*  = nullptr, int  = 0, EEndian  = eLittleEndian,
        RectI*  = nullptr, bool  = false) override { return 0; }

    MOCK_METHOD9(UpdateTextureInVideoMemory,
        void(uint32, const byte*, int, int, int, int, ETEX_Format, int, int));
    MOCK_METHOD8(DXTCompress,
        bool(const byte * raw_data, int nWidth, int nHeight, ETEX_Format eTF, bool bUseHW, bool bGenMips, int nSrcBytesPerPix, MIPDXTcallback callback));
    MOCK_METHOD9(DXTDecompress,
        bool(const byte * srcData, const size_t srcFileSize, byte * dstData, int nWidth, int nHeight, int nMips, ETEX_Format eSrcTF, bool bUseHW, int nDstBytesPerPix));
    MOCK_METHOD1(RemoveTexture,
        void(unsigned int TextureId));
    MOCK_METHOD1(DeleteFont,
        void(IFFont * font));
    MOCK_METHOD2(BakeMesh,
        bool(const SMeshBakingInputParams * pInputParams, SMeshBakingOutput * pReturnValues));
    MOCK_METHOD3(CaptureFrameBufferFast,
        bool(unsigned char* pDstRGBA8, int destinationWidth, int destinationHeight));
    MOCK_METHOD3(CopyFrameBufferFast,
        bool(unsigned char* pDstRGBA8, int destinationWidth, int destinationHeight));
    MOCK_METHOD1(RegisterCaptureFrame,
        bool(ICaptureFrameListener * pCapture));
    MOCK_METHOD1(UnRegisterCaptureFrame,
        bool(ICaptureFrameListener * pCapture));
    MOCK_METHOD2(InitCaptureFrameBufferFast,
        bool(uint32, uint32));
    MOCK_METHOD0(CloseCaptureFrameBufferFast,
        void(void));
    MOCK_METHOD0(CaptureFrameBufferCallBack,
        void(void));
    MOCK_METHOD1(RegisterSyncWithMainListener,
        void(ISyncMainWithRenderListener * pListener));
    MOCK_METHOD1(RemoveSyncWithMainListener,
        void(const ISyncMainWithRenderListener * pListener));
    MOCK_METHOD5(Set2DMode,
        void(uint32, uint32, TransformationMatrices&, float, float));
    MOCK_METHOD1(Unset2DMode,
        void(const TransformationMatrices& restoringMatrices));
    MOCK_METHOD7(Set2DModeNonZeroTopLeft,
        void(float, float, float, float, TransformationMatrices&, float, float));
    MOCK_METHOD1(ScreenToTexture,
        int(int nTexID));
    MOCK_METHOD1(EnableSwapBuffers,
        void(bool bEnable));
    MOCK_METHOD0(GetHWND,
        WIN_HWND());
    MOCK_METHOD1(SetWindowIcon,
        bool(const char* path));
    MOCK_METHOD1(OnEntityDeleted,
        void(struct IRenderNode* pRenderNode));
    MOCK_METHOD5(CreateRenderTarget,
        int(const char* name, int nWidth, int nHeight, const ColorF& clearColor, ETEX_Format eTF));
    MOCK_METHOD1(DestroyRenderTarget,
        bool(int nHandle));
    MOCK_METHOD3(ResizeRenderTarget,
        bool(int nHandle, int nWidth, int nHeight));
    MOCK_METHOD2(SetRenderTarget,
        bool(int, SDepthTexture*));
    MOCK_METHOD3(CreateDepthSurface,
        SDepthTexture * (int, int, bool));
    MOCK_METHOD1(DestroyDepthSurface,
        void(SDepthTexture * pDepthSurf));
    MOCK_CONST_METHOD1(CreateOptics,
        IOpticsElementBase * (EFlareType type));
    MOCK_METHOD1(PauseTimer,
        void(bool bPause));
    MOCK_METHOD0(CreateShaderPublicParams,
        IShaderPublicParams * ());
    MOCK_CONST_METHOD2(GetThreadIDs,
        void(threadID & mainThreadID, threadID & renderThreadID));
    MOCK_METHOD1(EnableGPUTimers2,
        void(bool bEnabled));
    MOCK_METHOD1(AllowGPUTimers2,
        void(bool bAllow));
    MOCK_METHOD2(GetRPPStats,
        const RPProfilerStats * (ERenderPipelineProfilerStats, bool));
    MOCK_METHOD1(GetRPPStatsArray,
        const RPProfilerStats * (bool));
    MOCK_METHOD4(GetPolygonCountByType,
        int(uint32, EVertexCostTypes, uint32, bool));
    MOCK_METHOD5(SetCloudShadowsParams,
        void(int nTexID, const Vec3& speed, float tiling, bool invert, float brightness));
    MOCK_METHOD2(PushFogVolumeContribution,
        uint16(const SFogVolumeData& fogVolData, const SRenderingPassInfo& passInfo));
    MOCK_METHOD2(PushFogVolume,
        void(class CREFogVolume * pFogVolume, const SRenderingPassInfo& passInfo));
    MOCK_METHOD0(GetMaxTextureSize,
        int());
    MOCK_METHOD1(GetTextureFormatName,
        const char*(ETEX_Format eTF));
    MOCK_METHOD5(GetTextureFormatDataSize,
        int(int nWidth, int nHeight, int nDepth, int nMips, ETEX_Format eTF));
    MOCK_METHOD2(SetDefaultMaterials,
        void(_smart_ptr<IMaterial> pDefMat, _smart_ptr<IMaterial> pTerrainDefMat));
    MOCK_CONST_METHOD0(GetGPUParticleEngine,
        IGPUParticleEngine * ());
    MOCK_CONST_METHOD0(GetActiveGPUCount,
        uint32());
    MOCK_METHOD0(GetShadowFrustumMGPUCache,
        ShadowFrustumMGPUCache * ());

    MOCK_CONST_METHOD0(GetCachedShadowsResolution,
        const StaticArray<int, MAX_GSM_LODS_NUM>&());

    MOCK_METHOD1(SetCachedShadowsResolution,
        void(const StaticArray<int, MAX_GSM_LODS_NUM>&arrResolutions));
    MOCK_CONST_METHOD1(UpdateCachedShadowsLodCount,
        void(int nGsmLods));
    MOCK_METHOD1(SetTexturePrecaching,
        void(bool stat));
    MOCK_METHOD2(RT_InsertGpuCallback,
        void(uint32 context, GpuCallbackFunc callback));
    MOCK_METHOD1(EnablePipelineProfiler,
        void(bool bEnable));
    MOCK_METHOD1(GetRenderTimes,
        void(SRenderTimes & outTimes));
    MOCK_METHOD0(GetGPUFrameTime,
        float());
    MOCK_METHOD1(EnableBatchMode,
        void(bool enable));
    MOCK_METHOD1(EnableLevelUnloading,
        void(bool enable));
    MOCK_METHOD0(OnLevelLoadFailed,
        void());
#if !defined(_RELEASE)
    MOCK_METHOD1(GetDrawCallsInfoPerMesh,
        RNDrawcallsMapMesh & (bool));
    MOCK_METHOD1(GetDrawCallsPerNode,
        int(IRenderNode * pRenderNode));
    MOCK_METHOD1(ForceRemoveNodeFromDrawCallsMap,
        void(IRenderNode * pNode));
#endif
    MOCK_METHOD1(CollectDrawCallsInfo,
        void(bool status));
    MOCK_METHOD1(CollectDrawCallsInfoPerNode,
        void(bool status));
    MOCK_METHOD0(HasLoadedDefaultResources,
        bool());
    MOCK_METHOD3(EF_CreateSkinningData,
        SSkinningData * (uint32, bool, bool));
    MOCK_METHOD4(EF_CreateRemappedSkinningData,
        SSkinningData * (uint32 nNumBones, SSkinningData * pSourceSkinningData, uint32 nCustomDataSize, uint32 pairGuid));
    MOCK_METHOD0(EF_ClearSkinningDataPool,
        void());
    MOCK_METHOD0(EF_GetSkinningPoolID,
        int());
    MOCK_METHOD1(ClearShaderItem,
        void(SShaderItem * pShaderItem));
    MOCK_METHOD2(UpdateShaderItem,
        void(SShaderItem * pShaderItem, _smart_ptr<IMaterial> pMaterial));
    MOCK_METHOD2(ForceUpdateShaderItem,
        void(SShaderItem * pShaderItem, _smart_ptr<IMaterial> pMaterial));
    MOCK_METHOD2(RefreshShaderResourceConstants,
        void(SShaderItem * pShaderItem, _smart_ptr<IMaterial> pMaterial));
    MOCK_METHOD0(IsStereoModeChangePending,
        bool());
    MOCK_METHOD0(SyncComputeVerticesJobs,
        void());
    MOCK_METHOD1(LockParticleVideoMemory,
        void(uint32 nId));
    MOCK_METHOD1(UnLockParticleVideoMemory,
        void(uint32 nId));
    MOCK_METHOD1(BeginSpawningGeneratingRendItemJobs,
        void(int nThreadID));
    MOCK_METHOD1(BeginSpawningShadowGeneratingRendItemJobs,
        void(int nThreadID));
    MOCK_METHOD0(EndSpawningGeneratingRendItemJobs,
        void());
    MOCK_METHOD0(GetGenerateRendItemJobExecutor,
        AZ::LegacyJobExecutor*());
    MOCK_METHOD0(GetGenerateShadowRendItemJobExecutor,
        AZ::LegacyJobExecutor*());
    MOCK_METHOD0(GetGenerateRendItemJobExecutorPreProcess,
        AZ::LegacyJobExecutor*());
    MOCK_METHOD1(GetFinalizeRendItemJobExecutor,
        AZ::LegacyJobExecutor*(int nThreadID));
    MOCK_METHOD1(GetFinalizeShadowRendItemJobExecutor,
        AZ::LegacyJobExecutor*(int nThreadID));
    MOCK_METHOD0(FlushPendingTextureTasks,
        void());
    MOCK_METHOD1(SetShadowJittering,
        void(float fShadowJittering));
    MOCK_CONST_METHOD0(GetShadowJittering,
        float());
    MOCK_METHOD0(LoadShaderStartupCache,
        bool());
    MOCK_METHOD0(UnloadShaderStartupCache,
        void());
    MOCK_METHOD0(LoadShaderLevelCache,
        bool());
    MOCK_METHOD0(UnloadShaderLevelCache,
        void());
    MOCK_METHOD1(StartScreenShot,
        void(int e_ScreenShot));
    MOCK_METHOD1(EndScreenShot,
        void(int e_ScreenShot));
    MOCK_METHOD3(SetRendererCVar,
        void(ICVar*, const char*, const bool));
    MOCK_METHOD0(GetRenderPipeline,
        SRenderPipeline * ());
    MOCK_METHOD0(GetShaderManager,
        CShaderMan * ());
    MOCK_METHOD0(GetRenderThread,
        SRenderThread * ());
    MOCK_METHOD0(GetWhiteTexture,
        ITexture * ());
    MOCK_METHOD3(GetTextureForName,
        ITexture * (const char* name, uint32 nFlags, ETEX_Format eFormat));
    MOCK_METHOD0(GetViewParameters,
        const CameraViewParameters& ());
    MOCK_METHOD0(GetFrameReset,
        uint32());
    MOCK_METHOD0(GetDepthBufferOrig,
        SDepthTexture * ());
    MOCK_METHOD0(GetBackBufferWidth,
        uint32());
    MOCK_METHOD0(GetBackBufferHeight,
        uint32());
    MOCK_METHOD0(GetDeviceBufferManager,
        CDeviceBufferManager * ());
    MOCK_CONST_METHOD0(GetRenderTileInfo,
        const SRenderTileInfo * ());
    MOCK_METHOD0(GetIdentityMatrix,
        Matrix44A());
    MOCK_CONST_METHOD0(RT_GetCurrGpuID,
        int32());
    MOCK_METHOD0(GenerateTextureId,
        int());
    MOCK_METHOD2(SetCull,
        void(ECull, bool));
    MOCK_METHOD9(DrawQuad3D,
        void(const Vec3& v0, const Vec3& v1, const Vec3& v2, const Vec3& v3, const ColorF& color, float ftx0, float fty0, float ftx1, float fty1));
    MOCK_METHOD0(FX_ResetPipe,
        void());
    MOCK_METHOD4(FX_GetDepthSurface,
        SDepthTexture * (int, int, bool, bool));
    MOCK_METHOD5(FX_CheckOverflow,
        void(int, int, IRenderElement*, int*, int*));
    MOCK_METHOD1(FX_PreRender,
        void(int Stage));
    MOCK_METHOD0(FX_PostRender,
        void());
    MOCK_METHOD3(FX_SetState,
        void(int, int, int));
    MOCK_METHOD3(FX_CommitStates,
        void(const SShaderTechnique * pTech, const SShaderPass * pPass, bool bUseMaterialState));
    MOCK_METHOD1(FX_Commit,
        void(bool));
    MOCK_METHOD2(FX_SetVertexDeclaration,
        long(int StreamMask, const AZ::Vertex::Format& vertexFormat));
    MOCK_METHOD7(FX_DrawIndexedPrimitive,
        void(eRenderPrimitiveType, int, int, int, int, int, bool));
    MOCK_METHOD3(FX_SetIStream,
        long(const void* pB, uint32 nOffs, RenderIndexType idxType));
    MOCK_METHOD5(FX_SetVStream,
        long(int, const void*, uint32, uint32, uint32));
    MOCK_METHOD4(FX_DrawPrimitive,
        void(eRenderPrimitiveType, int, int, int));
    MOCK_METHOD1(FX_ClearTarget,
        void(ITexture * pTex));
    MOCK_METHOD1(FX_ClearTarget,
        void(SDepthTexture * pTex));
    MOCK_METHOD4(FX_SetRenderTarget,
        bool(int, void*, SDepthTexture*, uint32));
    MOCK_METHOD4(FX_PushRenderTarget,
        bool(int, void*, SDepthTexture*, uint32));
    MOCK_METHOD7(FX_SetRenderTarget,
        bool(int, CTexture*, SDepthTexture*, bool, int, bool, uint32));
    MOCK_METHOD6(FX_PushRenderTarget,
        bool(int, CTexture*, SDepthTexture*, int, bool, uint32));
    MOCK_METHOD1(FX_RestoreRenderTarget,
        bool(int nTarget));
    MOCK_METHOD1(FX_PopRenderTarget,
        bool(int nTarget));
    MOCK_METHOD4(FX_Start,
        void(CShader * ef, int nTech, CShaderResources * Res, IRenderElement * re));
    MOCK_METHOD1(RT_PopRenderTarget,
        void(int nTarget));
    MOCK_METHOD5(RT_SetViewport,
        void(int, int, int, int, int));
    MOCK_METHOD4(RT_PushRenderTarget,
        void(int nTarget, CTexture * pTex, SDepthTexture * pDS, int nS));
    MOCK_METHOD5(EF_Scissor,
        void(bool bEnable, int sX, int sY, int sWdt, int sHgt));

#ifdef SUPPORT_HW_MOUSE_CURSOR
    MOCK_METHOD0(GetIHWMouseCursor,
        IHWMouseCursor * ());
#endif

    MOCK_METHOD0(GetRecursionLevel,
        int());
    MOCK_METHOD2(GetIntegerConfigurationValue,
        int(const char* varName, int defaultValue));
    MOCK_METHOD2(GetFloatConfigurationValue,
        float(const char* varName, float defaultValue));
    MOCK_METHOD2(GetBooleanConfigurationValue,
        bool(const char* varName, bool defaultValue));
    MOCK_METHOD3(ApplyDepthTextureState,
        void(int unit, int nFilter, bool clamp));
    MOCK_METHOD0(GetZTargetTexture,
        ITexture * ());
    MOCK_METHOD1(GetTextureState,
        int(const STexState& TS));
    MOCK_METHOD7(TextureDataSize,
        uint32(uint32, uint32, uint32, uint32, uint32, ETEX_Format, ETEX_TileMode));
    MOCK_METHOD6(ApplyForID,
        void(int nID, int nTUnit, int nTState, int nTexMaterialSlot, int nSUnit, bool useWhiteDefault));
    MOCK_METHOD9(Create3DTexture,
        ITexture * (const char* szName, int nWidth, int nHeight, int nDepth, int nMips, int nFlags, const byte * pData, ETEX_Format eTFSrc, ETEX_Format eTFDst));
    MOCK_METHOD1(IsTextureExist,
        bool(const ITexture * pTex));
    MOCK_METHOD1(NameForTextureFormat,
        const char*(ETEX_Format eTF));
    MOCK_METHOD1(NameForTextureType,
        const char*(ETEX_Type eTT));
    MOCK_METHOD0(IsVideoThreadModeEnabled,
        bool());
    MOCK_METHOD5(CreateDynTexture2,
        IDynTexture * (uint32 nWidth, uint32 nHeight, uint32 nTexFlags, const char* szSource, ETexPool eTexPool));
    MOCK_METHOD0(GetCurrentTextureAtlasSize,
        uint32());
    MOCK_METHOD5(EF_QueryImpl,
        void(ERenderQueryTypes eQuery, void* pInOut0, uint32 nInOutSize0, void* pInOut1, uint32 nInOutSize1));
};

#if defined(AZ_COMPILER_MSVC) 
    #pragma warning(pop)
#endif // AZ_COMPILER MSVC

