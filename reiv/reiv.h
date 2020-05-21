#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned ReivBool32;

typedef enum ReivCullMode {
  REIV_CULL_MODE_NONE           = 0,
  REIV_CULL_MODE_FRONT          = 0x0404,
  REIV_CULL_MODE_BACK           = 0x0405,
  REIV_CULL_MODE_FRONT_AND_BACK = 0x0408,
} ReivCullMode;

typedef enum ReivFrontFace {
  REIV_FRONT_FACE_COUNTER_CLOCKWISE = 0x0901,
  REIV_FRONT_FACE_CLOCKWISE         = 0x0900,
} ReivFrontFace;

typedef enum ReivCompareOp {
  REIV_COMPARE_OP_NEVER            = 0x0200,
  REIV_COMPARE_OP_LESS             = 0x0201,
  REIV_COMPARE_OP_EQUAL            = 0x0202,
  REIV_COMPARE_OP_LESS_OR_EQUAL    = 0x0203,
  REIV_COMPARE_OP_GREATER          = 0x0204,
  REIV_COMPARE_OP_NOT_EQUAL        = 0x0205,
  REIV_COMPARE_OP_GREATER_OR_EQUAL = 0x0206,
  REIV_COMPARE_OP_ALWAYS           = 0x0207,
} ReivCompareOp;

typedef enum ReivStencilOp {
  REIV_STENCIL_OP_KEEP                = 0x1E00,
  REIV_STENCIL_OP_ZERO                = 0,
  REIV_STENCIL_OP_REPLACE             = 0x1E01,
  REIV_STENCIL_OP_INCREMENT_AND_CLAMP = 0x1E02,
  REIV_STENCIL_OP_DECREMENT_AND_CLAMP = 0x1E03,
  REIV_STENCIL_OP_INVERT              = 0x150A,
} ReivStencilOp;

typedef enum ReivLogicOp {
  REIV_LOGIC_OP_CLEAR         = 0x1500,
  REIV_LOGIC_OP_AND           = 0x1501,
  REIV_LOGIC_OP_AND_REVERSE   = 0x1502,
  REIV_LOGIC_OP_COPY          = 0x1503,
  REIV_LOGIC_OP_AND_INVERTED  = 0x1504,
  REIV_LOGIC_OP_NO_OP         = 0x1505,
  REIV_LOGIC_OP_XOR           = 0x1506,
  REIV_LOGIC_OP_OR            = 0x1507,
  REIV_LOGIC_OP_NOR           = 0x1508,
  REIV_LOGIC_OP_EQUIVALENT    = 0x1509,
  REIV_LOGIC_OP_INVERT        = 0x150A,
  REIV_LOGIC_OP_OR_REVERSE    = 0x150B,
  REIV_LOGIC_OP_COPY_INVERTED = 0x150C,
  REIV_LOGIC_OP_OR_INVERTED   = 0x150D,
  REIV_LOGIC_OP_NAND          = 0x150E,
  REIV_LOGIC_OP_SET           = 0x150F,
} ReivLogicOp;

typedef enum ReivBlendFactor {
  REIV_BLEND_FACTOR_ZERO                     = 0,
  REIV_BLEND_FACTOR_ONE                      = 1,
  REIV_BLEND_FACTOR_SOURCE_COLOR             = 0x0300,
  REIV_BLEND_FACTOR_ONE_MINUS_SOURCE_COLOR   = 0x0301,
  REIV_BLEND_FACTOR_TARGET_COLOR             = 0x0306,
  REIV_BLEND_FACTOR_ONE_MINUS_TARGET_COLOR   = 0x0307,
  REIV_BLEND_FACTOR_SOURCE_ALPHA             = 0x0302,
  REIV_BLEND_FACTOR_ONE_MINUS_SOURCE_ALPHA   = 0x0303,
  REIV_BLEND_FACTOR_TARGET_ALPHA             = 0x0304,
  REIV_BLEND_FACTOR_ONE_MINUS_TARGET_ALPHA   = 0x0305,
  REIV_BLEND_FACTOR_CONSTANT_COLOR           = 0x8001,
  REIV_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR = 0x8002,
  REIV_BLEND_FACTOR_CONSTANT_ALPHA           = 0x8003,
  REIV_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA = 0x8004,
  REIV_BLEND_FACTOR_SOURCE_ALPHA_SATURATE    = 0x0308,
} ReivBlendFactor;

typedef enum ReivBlendOp {
  REIV_BLEND_OP_ADD              = 0x8006,
  REIV_BLEND_OP_SUBTRACT         = 0x800A,
  REIV_BLEND_OP_REVERSE_SUBTRACT = 0x800B,
  REIV_BLEND_OP_MIN              = 0x8007,
  REIV_BLEND_OP_MAX              = 0x8008,
} ReivBlendOp;

typedef enum ReivPixelsType {
  REIV_PIXELS_TYPE_NONE = 0,
  REIV_PIXELS_TYPE_2D   = 1,
  REIV_PIXELS_TYPE_CUBE = 2,
} ReivPixelsType;

typedef enum ReivSamplerState {
  REIV_SAMPLER_STATE_NEAREST        = 0,
  REIV_SAMPLER_STATE_LINEAR         = 1,
  REIV_SAMPLER_STATE_ANISOTROPIC_2  = 2,
  REIV_SAMPLER_STATE_ANISOTROPIC_4  = 3,
  REIV_SAMPLER_STATE_ANISOTROPIC_8  = 4,
  REIV_SAMPLER_STATE_ANISOTROPIC_16 = 5,
} ReivSamplerState;

typedef struct ReivPipelineState {
  unsigned         _[2];
  ReivBool32       rasterizationDepthClampEnable;
  ReivCullMode     rasterizationCullMode;
  ReivFrontFace    rasterizationFrontFace;
  ReivBool32       rasterizationDepthBiasEnable;
  float            rasterizationDepthBiasConstantFactor;
  float            rasterizationDepthBiasSlopeFactor;
  ReivBool32       multisampleEnable;
  ReivBool32       multisampleAlphaToCoverageEnable;
  ReivBool32       multisampleAlphaToOneEnable;
  ReivBool32       depthTestEnable;
  ReivBool32       depthTestDepthWriteEnable;
  ReivCompareOp    depthTestDepthCompareOp;
  ReivBool32       stencilTestEnable;
  ReivStencilOp    stencilTestFrontStencilTestFailOp;
  ReivStencilOp    stencilTestFrontStencilTestPassDepthTestPassOp;
  ReivStencilOp    stencilTestFrontStencilTestPassDepthTestFailOp;
  ReivCompareOp    stencilTestFrontCompareOp;
  unsigned         stencilTestFrontCompareMask;
  unsigned         stencilTestFrontWriteMask;
  unsigned         stencilTestFrontReference;
  ReivStencilOp    stencilTestBackStencilTestFailOp;
  ReivStencilOp    stencilTestBackStencilTestPassDepthTestPassOp;
  ReivStencilOp    stencilTestBackStencilTestPassDepthTestFailOp;
  ReivCompareOp    stencilTestBackCompareOp;
  unsigned         stencilTestBackCompareMask;
  unsigned         stencilTestBackWriteMask;
  unsigned         stencilTestBackReference;
  ReivBool32       blendLogicOpEnable;
  ReivLogicOp      blendLogicOp;
  float            blendConstants[4];
  ReivBool32       outputColorWriteEnableR;
  ReivBool32       outputColorWriteEnableG;
  ReivBool32       outputColorWriteEnableB;
  ReivBool32       outputColorWriteEnableA;
  ReivBool32       outputColorBlendEnable;
  ReivBlendFactor  outputColorBlendColorFactorSource;
  ReivBlendFactor  outputColorBlendColorFactorTarget;
  ReivBlendOp      outputColorBlendColorOp;
  ReivBlendFactor  outputColorBlendAlphaFactorSource;
  ReivBlendFactor  outputColorBlendAlphaFactorTarget;
  ReivBlendOp      outputColorBlendAlphaOp;
  const char *     codeVertex;
  const char *     codeFragment;
  ReivPixelsType   pixelsType[4];
  ReivSamplerState pixelsSamplerState[4];
} ReivPipelineState;

typedef enum ReivRegister {
  REIV_REGISTER_VIEWPORT = 4294967295 - 0,
  REIV_REGISTER_SCISSOR  = 4294967295 - 1,
  REIV_REGISTER_CLEAR    = 4294967295 - 2,
} ReivRegister;

typedef struct ReivRegisterViewport {
  int x;
  int y;
  int w;
  int h;
} ReivRegisterViewport;

typedef struct ReivRegisterScissor {
  int x;
  int y;
  int w;
  int h;
} ReivRegisterScissor;

typedef struct ReivRegisterClear {
  ReivBool32 clearDepth;
  ReivBool32 clearStencil;
  ReivBool32 clearColor;
  float      depth;
  unsigned   stencil;
  float      color[4];
} ReivRegisterClear;

typedef struct ReivBatchPixels {
  unsigned pixelsIndex;
  unsigned allocateLevelsCount;
  unsigned level;
  unsigned x;
  unsigned y;
  unsigned w;
  unsigned h;
  const unsigned char * rgba[6];
} ReivBatchPixels;

typedef struct ReivBatchMeshAos {
  unsigned meshIndex;
  unsigned vertexesFirst;
  unsigned vertexesCount;
  const float * xyzw[4];
} ReivBatchMeshAos;

typedef struct ReivBatchMeshSoa {
  unsigned meshIndex;
  unsigned vertexesFirst;
  unsigned vertexesCount;
  const float * x[4];
  const float * y[4];
  const float * z[4];
  const float * w[4];
} ReivBatchMeshSoa;

typedef struct ReivBatchPipeline {
  unsigned pipelineIndex;
  const ReivPipelineState * state;
} ReivBatchPipeline;

typedef struct ReivBatchDraw {
  unsigned registerIndex;
  unsigned register32BitValuesCount;
  const void * register32BitValues;
  unsigned meshIndex;
  unsigned pipelineIndex;
  unsigned pixelsIndexes[4];
  unsigned instancesCount;
} ReivBatchDraw;

typedef struct ReivBatchReadback {
  unsigned x;
  unsigned y;
  unsigned w;
  unsigned h;
  unsigned char * outRgba;
} ReivBatchReadback;

void reivMark(const char * group64Chars, const char * label64Chars);
void reivWindow(unsigned w, unsigned h, const void * displayOrHinstance, const void * windowOrHwnd);
void reivResources(unsigned meshAosBatchesCount, const ReivBatchMeshAos * meshAosBatches, unsigned meshSoaBatchesCount, const ReivBatchMeshSoa * meshSoaBatches, unsigned pixelsBatchesCount, const ReivBatchPixels * pixelsBatches, unsigned pipelineBatchesCount, const ReivBatchPipeline * pipelineBatches);
void reivDraw(unsigned batchesCount, const ReivBatchDraw * batches);
void reivReadback(unsigned batchesCount, ReivBatchReadback * batches);
void reivPresent(void);
void reivDestroyEverything(void);

#ifdef __cplusplus
}
#endif
