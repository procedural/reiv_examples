#include "../reiv/reiv.h"
#define GLFW_INCLUDE_NONE
#include "../glfw/include/glfw3.h"

#include <stdio.h>

const float meshVertexesFloats[] = {
#include "mesh_vertices.h"
};

#define _countof(staticArray) (sizeof(staticArray) / sizeof((staticArray)[0]))

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_RESIZABLE, 0);
  GLFWwindow * window = glfwCreateWindow(700, 700, "", NULL, NULL);

  reivWindow(0, 0, NULL, window);

  float meshVertexesColors[_countof(meshVertexesFloats)] = {};
  for (int i = 0, meshVertexesCount = _countof(meshVertexesFloats) / 4; i < meshVertexesCount; i += 1) {
    meshVertexesColors[i * 4 + 0] = i * 0.00025f;
    meshVertexesColors[i * 4 + 1] = 0.f;
    meshVertexesColors[i * 4 + 2] = 0.1f;
    meshVertexesColors[i * 4 + 3] = 1.f;
  }

  ReivBatchMeshAos mesh = {};
  mesh.meshIndex     = 0;
  mesh.vertexesFirst = 0;
  mesh.vertexesCount = _countof(meshVertexesFloats) / 4;
  mesh.xyzw[0]       = meshVertexesColors;
  mesh.xyzw[1]       = NULL;
  mesh.xyzw[2]       = NULL;
  mesh.xyzw[3]       = meshVertexesFloats;

  char codeVertex[] =
    "!!ARBvp1.0"
    "MOV result.texcoord[0], vertex.texcoord[0];"
    "MOV result.position, vertex.position;"
    "END";

  char codeFragment[] =
    "!!ARBfp1.0"
    "MOV result.color, fragment.texcoord[0];"
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
  state.pixelsType[0]                                  = REIV_PIXELS_TYPE_NONE;
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

  reivResources(1, &mesh, 0, NULL, 0, NULL, 1, &pipeline);

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

  ReivBatchDraw draws[4] = {};

  draws[0].registerIndex       = REIV_REGISTER_VIEWPORT;
  draws[0].register32BitValues = &viewport;

  draws[1].registerIndex       = REIV_REGISTER_SCISSOR;
  draws[1].register32BitValues = &scissor;

  draws[2].registerIndex       = REIV_REGISTER_CLEAR;
  draws[2].register32BitValues = &clear;

  draws[3].meshIndex        = 0;
  draws[3].pipelineIndex    = 0;
  draws[3].pixelsIndexes[0] = 0;
  draws[3].pixelsIndexes[1] = 0;
  draws[3].pixelsIndexes[2] = 0;
  draws[3].pixelsIndexes[3] = 0;
  draws[3].instancesCount   = 1;

  for (; glfwWindowShouldClose(window) == 0;) {
    glfwPollEvents();

    reivDraw(_countof(draws), draws);

    reivPresent();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
