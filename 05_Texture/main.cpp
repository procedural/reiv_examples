#include "../reiv/reiv.h"
#define GLFW_INCLUDE_NONE
#include "../glfw/include/glfw3.h"

#include <stdio.h>
#include <math.h>

#define _countof(staticArray) (sizeof(staticArray) / sizeof((staticArray)[0]))

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_RESIZABLE, 0);
  GLFWwindow * window = glfwCreateWindow(700, 700, "", NULL, NULL);

  reivWindow(0, 0, NULL, window);

  typedef struct {
    unsigned char r, g, b, a;
  } color;

  const color colors[] = {
    {  0,   0,   0, 255},
    {255,   0,   0, 255},
    {  0, 255,   0, 255},
    {  0,   0, 255, 255},
    {255,   0, 255, 255},
  };

#define _ 0

  const int image0[] = {
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,2,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,3,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,4,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
  };

  const int image1[] = {
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,2,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,3,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,4,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
  };

#undef _

  color texture0[_countof(image0)];
  for (int i = 0; i < _countof(image0); i += 1) {
    texture0[i] = colors[image0[i]];
  }

  color texture1[_countof(image1)];
  for (int i = 0; i < _countof(image1); i += 1) {
    texture1[i] = colors[image1[i]];
  }

  float vertexesFloats[3 * 4] = {};
  vertexesFloats[0 * 4 + 0] = -1;
  vertexesFloats[0 * 4 + 1] = 3;
  vertexesFloats[0 * 4 + 2] = 0;
  vertexesFloats[0 * 4 + 3] = 1;
  vertexesFloats[1 * 4 + 0] = -1;
  vertexesFloats[1 * 4 + 1] = -1;
  vertexesFloats[1 * 4 + 2] = 0;
  vertexesFloats[1 * 4 + 3] = 1;
  vertexesFloats[2 * 4 + 0] = 3;
  vertexesFloats[2 * 4 + 1] = -1;
  vertexesFloats[2 * 4 + 2] = 0;
  vertexesFloats[2 * 4 + 3] = 1;

  ReivBatchMeshAos mesh = {};
  mesh.meshIndex     = 0;
  mesh.vertexesFirst = 0;
  mesh.vertexesCount = _countof(vertexesFloats) / 4;
  mesh.xyzw[0]       = NULL;
  mesh.xyzw[1]       = NULL;
  mesh.xyzw[2]       = NULL;
  mesh.xyzw[3]       = vertexesFloats;

  ReivBatchPixels pixels[2] = {};

  pixels[0].pixelsIndex         = 0;
  pixels[0].allocateLevelsCount = 1;
  pixels[0].level               = 0;
  pixels[0].x                   = 0;
  pixels[0].y                   = 0;
  pixels[0].w                   = (int)sqrtf(_countof(image0)); // Assuming square texture
  pixels[0].h                   = (int)sqrtf(_countof(image0)); // Assuming square texture
  pixels[0].rgba[0]             = &texture0[0].r;

  pixels[1].pixelsIndex         = 1;
  pixels[1].allocateLevelsCount = 1;
  pixels[1].level               = 0;
  pixels[1].x                   = 0;
  pixels[1].y                   = 0;
  pixels[1].w                   = (int)sqrtf(_countof(image1)); // Assuming square texture
  pixels[1].h                   = (int)sqrtf(_countof(image1)); // Assuming square texture
  pixels[1].rgba[0]             = &texture1[0].r;

  char codeVertex[] =
    "!!ARBvp1.0"
    "TEMP R0;"
    "MAD R0.xy, vertex.position, 0.5, 0.5;"
    "MOV result.texcoord[0].x, R0;"
    "ADD result.texcoord[0].y,-R0, 1;"
    "MOV result.position, vertex.position;"
    "END";

  char codeFragment[] =
    "!!ARBfp1.0"
    "TEX result.color, fragment.texcoord[0], texture[0], 2D;"
    "END";

  ReivPipelineState state                              = {};
  state.codeVertex                                     = codeVertex;
  state.codeFragment                                   = codeFragment;
  state.rasterizationDepthClampEnable                  = 0;
  state.rasterizationCullMode                          = REIV_CULL_MODE_NONE;
  state.rasterizationFrontFace                         = REIV_FRONT_FACE_COUNTER_CLOCKWISE;
  state.rasterizationDepthBiasEnable                   = 0;
  state.rasterizationDepthBiasConstantFactor           = 0;
  state.rasterizationDepthBiasSlopeFactor              = 0;
  state.multisampleEnable                              = 0;
  state.multisampleAlphaToCoverageEnable               = 0;
  state.multisampleAlphaToOneEnable                    = 0;
  state.depthTestEnable                                = 0;
  state.depthTestDepthWriteEnable                      = 0;
  state.depthTestDepthCompareOp                        = REIV_COMPARE_OP_GREATER_OR_EQUAL;
  state.stencilTestEnable                              = 0;
  state.stencilTestFrontStencilTestFailOp              = REIV_STENCIL_OP_KEEP;
  state.stencilTestFrontStencilTestPassDepthTestPassOp = REIV_STENCIL_OP_KEEP;
  state.stencilTestFrontStencilTestPassDepthTestFailOp = REIV_STENCIL_OP_KEEP;
  state.stencilTestFrontCompareOp                      = REIV_COMPARE_OP_NEVER;
  state.stencilTestFrontCompareMask                    = 0;
  state.stencilTestFrontWriteMask                      = 0;
  state.stencilTestFrontReference                      = 0;
  state.stencilTestBackStencilTestFailOp               = REIV_STENCIL_OP_KEEP;
  state.stencilTestBackStencilTestPassDepthTestPassOp  = REIV_STENCIL_OP_KEEP;
  state.stencilTestBackStencilTestPassDepthTestFailOp  = REIV_STENCIL_OP_KEEP;
  state.stencilTestBackCompareOp                       = REIV_COMPARE_OP_NEVER;
  state.stencilTestBackCompareMask                     = 0;
  state.stencilTestBackWriteMask                       = 0;
  state.stencilTestBackReference                       = 0;
  state.blendLogicOpEnable                             = 0;
  state.blendLogicOp                                   = REIV_LOGIC_OP_CLEAR;
  state.blendConstants[0]                              = 0;
  state.blendConstants[1]                              = 0;
  state.blendConstants[2]                              = 0;
  state.blendConstants[3]                              = 0;
  state.outputColorWriteEnableR                        = 1;
  state.outputColorWriteEnableG                        = 1;
  state.outputColorWriteEnableB                        = 1;
  state.outputColorWriteEnableA                        = 1;
  state.outputColorBlendEnable                         = 0;
  state.outputColorBlendColorFactorSource              = REIV_BLEND_FACTOR_ZERO;
  state.outputColorBlendColorFactorTarget              = REIV_BLEND_FACTOR_ZERO;
  state.outputColorBlendColorOp                        = REIV_BLEND_OP_ADD;
  state.outputColorBlendAlphaFactorSource              = REIV_BLEND_FACTOR_ZERO;
  state.outputColorBlendAlphaFactorTarget              = REIV_BLEND_FACTOR_ZERO;
  state.outputColorBlendAlphaOp                        = REIV_BLEND_OP_ADD;
  state.pixelsType[0]                                  = REIV_PIXELS_TYPE_2D;
  state.pixelsType[1]                                  = REIV_PIXELS_TYPE_NONE;
  state.pixelsType[2]                                  = REIV_PIXELS_TYPE_NONE;
  state.pixelsType[3]                                  = REIV_PIXELS_TYPE_NONE;
  state.pixelsSamplerState[0]                          = REIV_SAMPLER_STATE_NEAREST;
  state.pixelsSamplerState[1]                          = REIV_SAMPLER_STATE_NEAREST;
  state.pixelsSamplerState[2]                          = REIV_SAMPLER_STATE_NEAREST;
  state.pixelsSamplerState[3]                          = REIV_SAMPLER_STATE_NEAREST;

  ReivBatchPipeline pipeline = {};
  pipeline.pipelineIndex = 0;
  pipeline.state         = &state;

  reivResources(1, &mesh, 0, NULL, 2, pixels, 1, &pipeline);

  ReivRegisterViewport viewport = {};
  viewport.x = 0;
  viewport.y = 0;
  viewport.w = 700;
  viewport.h = 700;

  ReivRegisterScissor scissor = {};
  scissor.x = 0;
  scissor.y = 0;
  scissor.w = 700;
  scissor.h = 700;

  ReivRegisterClear clear = {};
  clear.clearDepth   = 0;
  clear.clearStencil = 0;
  clear.clearColor   = 1;
  clear.depth        = 0.f;
  clear.stencil      = 0;
  clear.color[0]     = 0.f;
  clear.color[1]     = 0.f;
  clear.color[2]     = 0.f;
  clear.color[3]     = 1.f;

  ReivBatchDraw draws0[4] = {};

  draws0[0].registerIndex       = REIV_REGISTER_VIEWPORT;
  draws0[0].register32BitValues = &viewport;

  draws0[1].registerIndex       = REIV_REGISTER_SCISSOR;
  draws0[1].register32BitValues = &scissor;

  draws0[2].registerIndex       = REIV_REGISTER_CLEAR;
  draws0[2].register32BitValues = &clear;

  draws0[3].meshIndex        = 0;
  draws0[3].pipelineIndex    = 0;
  draws0[3].pixelsIndexes[0] = 0;
  draws0[3].pixelsIndexes[1] = 0;
  draws0[3].pixelsIndexes[2] = 0;
  draws0[3].pixelsIndexes[3] = 0;
  draws0[3].instancesCount   = 1;

  ReivBatchDraw draws1[4] = {};

  draws1[0].registerIndex       = REIV_REGISTER_VIEWPORT;
  draws1[0].register32BitValues = &viewport;

  draws1[1].registerIndex       = REIV_REGISTER_SCISSOR;
  draws1[1].register32BitValues = &scissor;

  draws1[2].registerIndex       = REIV_REGISTER_CLEAR;
  draws1[2].register32BitValues = &clear;

  draws1[3].meshIndex        = 0;
  draws1[3].pipelineIndex    = 0;
  draws1[3].pixelsIndexes[0] = 1;
  draws1[3].pixelsIndexes[1] = 0;
  draws1[3].pixelsIndexes[2] = 0;
  draws1[3].pixelsIndexes[3] = 0;
  draws1[3].instancesCount   = 1;

  unsigned frame = 0;

  for (; glfwWindowShouldClose(window) == 0;) {
    glfwPollEvents();

    frame % 2 ? reivDraw(_countof(draws0), draws0) : reivDraw(_countof(draws1), draws1);

    reivPresent();

    frame += 1;
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
