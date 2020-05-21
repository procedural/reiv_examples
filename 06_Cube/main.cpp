#include "../reiv/reiv.h"
#define GLFW_INCLUDE_NONE
#include "../glfw/include/glfw3.h"

#include <stdio.h>
#include <math.h>
#ifdef __linux__
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_LINEAR
#define STBI_NO_HDR
#define STBI_NO_SIMD
#include "stb_image.h"

const float meshVertexesFloats[] = {
#include "mesh_vertices.h"
};

const float meshNormalsFloats[] = {
#include "mesh_normals.h"
};

#define _countof(staticArray) (sizeof(staticArray) / sizeof((staticArray)[0]))

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_RESIZABLE, 0);
  glfwWindowHint(GLFW_SAMPLES, 4);
  GLFWwindow * window = glfwCreateWindow(700, 700, "", NULL, NULL);

  reivWindow(0, 0, NULL, window);

  char codeVertexSkybox[] =
    "!!ARBvp1.0"
    "TEMP pos;"
    "TEMP R0;"
    "MOV pos, vertex.position;"
    "MUL R0.xyzw, pos.xzzx, program.env[1].xyxy;"
    "ADD pos.x, R0.x,-R0.y;"
    "ADD pos.z, R0.z, R0.w;"
    "MUL R0.xyzw, pos.yzzy, program.env[1].zwzw;"
    "ADD pos.y, R0.x,-R0.y;"
    "ADD pos.z, R0.z, R0.w;"
    "MOV result.texcoord[0], vertex.position;"
    "MOV result.position.xyw, pos.xyzz;"
    "MOV result.position.z, 0.1;"
    "END";

  char codeFragmentSkybox[] =
    "!!ARBfp1.0"
    "TEX result.color, fragment.texcoord[0], texture[0], CUBE;"
    "END";

  char codeVertex[] =
    "!!ARBvp1.0"
    "TEMP pos;"
    "TEMP R0;"
    "ADD pos, vertex.position, -program.env[0];"
    "MUL R0.xyzw, pos.xzzx, program.env[1].xyxy;"
    "ADD pos.x, R0.x,-R0.y;"
    "ADD pos.z, R0.z, R0.w;"
    "MUL R0.xyzw, pos.yzzy, program.env[1].zwzw;"
    "ADD pos.y, R0.x,-R0.y;"
    "ADD pos.z, R0.z, R0.w;"
    "MOV result.texcoord[0], vertex.position;"
    "MOV result.texcoord[1], vertex.texcoord[0];"
    "MOV result.position.xyw, pos.xyzz;"
    "MOV result.position.z, 0.1;"
    "END";

  char codeFragment[] =
    "!!ARBfp1.0"
    "TEMP R0;"
    "TEMP R1;"
    "ADD R0.xyz, fragment.texcoord[0], -program.env[0];"
    "DP3 R0.w, fragment.texcoord[1], R0;"
    "MUL R1.xyz, fragment.texcoord[1], R0.w;"
    "MAD R0.xyz, -R1, 2, R0;"
    "TEX result.color, R0, texture[0], CUBE;"
    "END";

  ReivPipelineState stateSkybox                              = {};
  stateSkybox.codeVertex                                     = codeVertexSkybox;
  stateSkybox.codeFragment                                   = codeFragmentSkybox;
  stateSkybox.rasterizationDepthClampEnable                  = 0;
  stateSkybox.rasterizationCullMode                          = REIV_CULL_MODE_NONE;
  stateSkybox.rasterizationFrontFace                         = REIV_FRONT_FACE_COUNTER_CLOCKWISE;
  stateSkybox.rasterizationDepthBiasEnable                   = 0;
  stateSkybox.rasterizationDepthBiasConstantFactor           = 0;
  stateSkybox.rasterizationDepthBiasSlopeFactor              = 0;
  stateSkybox.multisampleEnable                              = 0;
  stateSkybox.multisampleAlphaToCoverageEnable               = 0;
  stateSkybox.multisampleAlphaToOneEnable                    = 0;
  stateSkybox.depthTestEnable                                = 0;
  stateSkybox.depthTestDepthWriteEnable                      = 0;
  stateSkybox.depthTestDepthCompareOp                        = REIV_COMPARE_OP_GREATER_OR_EQUAL;
  stateSkybox.stencilTestEnable                              = 0;
  stateSkybox.stencilTestFrontStencilTestFailOp              = REIV_STENCIL_OP_KEEP;
  stateSkybox.stencilTestFrontStencilTestPassDepthTestPassOp = REIV_STENCIL_OP_KEEP;
  stateSkybox.stencilTestFrontStencilTestPassDepthTestFailOp = REIV_STENCIL_OP_KEEP;
  stateSkybox.stencilTestFrontCompareOp                      = REIV_COMPARE_OP_NEVER;
  stateSkybox.stencilTestFrontCompareMask                    = 0;
  stateSkybox.stencilTestFrontWriteMask                      = 0;
  stateSkybox.stencilTestFrontReference                      = 0;
  stateSkybox.stencilTestBackStencilTestFailOp               = REIV_STENCIL_OP_KEEP;
  stateSkybox.stencilTestBackStencilTestPassDepthTestPassOp  = REIV_STENCIL_OP_KEEP;
  stateSkybox.stencilTestBackStencilTestPassDepthTestFailOp  = REIV_STENCIL_OP_KEEP;
  stateSkybox.stencilTestBackCompareOp                       = REIV_COMPARE_OP_NEVER;
  stateSkybox.stencilTestBackCompareMask                     = 0;
  stateSkybox.stencilTestBackWriteMask                       = 0;
  stateSkybox.stencilTestBackReference                       = 0;
  stateSkybox.blendLogicOpEnable                             = 0;
  stateSkybox.blendLogicOp                                   = REIV_LOGIC_OP_CLEAR;
  stateSkybox.blendConstants[0]                              = 0;
  stateSkybox.blendConstants[1]                              = 0;
  stateSkybox.blendConstants[2]                              = 0;
  stateSkybox.blendConstants[3]                              = 0;
  stateSkybox.outputColorWriteEnableR                        = 1;
  stateSkybox.outputColorWriteEnableG                        = 1;
  stateSkybox.outputColorWriteEnableB                        = 1;
  stateSkybox.outputColorWriteEnableA                        = 1;
  stateSkybox.outputColorBlendEnable                         = 0;
  stateSkybox.outputColorBlendColorFactorSource              = REIV_BLEND_FACTOR_ZERO;
  stateSkybox.outputColorBlendColorFactorTarget              = REIV_BLEND_FACTOR_ZERO;
  stateSkybox.outputColorBlendColorOp                        = REIV_BLEND_OP_ADD;
  stateSkybox.outputColorBlendAlphaFactorSource              = REIV_BLEND_FACTOR_ZERO;
  stateSkybox.outputColorBlendAlphaFactorTarget              = REIV_BLEND_FACTOR_ZERO;
  stateSkybox.outputColorBlendAlphaOp                        = REIV_BLEND_OP_ADD;
  stateSkybox.pixelsType[0]                                  = REIV_PIXELS_TYPE_CUBE;
  stateSkybox.pixelsType[1]                                  = REIV_PIXELS_TYPE_NONE;
  stateSkybox.pixelsType[2]                                  = REIV_PIXELS_TYPE_NONE;
  stateSkybox.pixelsType[3]                                  = REIV_PIXELS_TYPE_NONE;
  stateSkybox.pixelsSamplerState[0]                          = REIV_SAMPLER_STATE_LINEAR;
  stateSkybox.pixelsSamplerState[1]                          = REIV_SAMPLER_STATE_NEAREST;
  stateSkybox.pixelsSamplerState[2]                          = REIV_SAMPLER_STATE_NEAREST;
  stateSkybox.pixelsSamplerState[3]                          = REIV_SAMPLER_STATE_NEAREST;

  ReivPipelineState state                              = {};
  state.codeVertex                                     = codeVertex;
  state.codeFragment                                   = codeFragment;
  state.rasterizationDepthClampEnable                  = 0;
  state.rasterizationCullMode                          = REIV_CULL_MODE_BACK;
  state.rasterizationFrontFace                         = REIV_FRONT_FACE_CLOCKWISE;
  state.rasterizationDepthBiasEnable                   = 0;
  state.rasterizationDepthBiasConstantFactor           = 0;
  state.rasterizationDepthBiasSlopeFactor              = 0;
  state.multisampleEnable                              = 1;
  state.multisampleAlphaToCoverageEnable               = 0;
  state.multisampleAlphaToOneEnable                    = 0;
  state.depthTestEnable                                = 1;
  state.depthTestDepthWriteEnable                      = 1;
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
  state.pixelsType[0]                                  = REIV_PIXELS_TYPE_CUBE;
  state.pixelsType[1]                                  = REIV_PIXELS_TYPE_NONE;
  state.pixelsType[2]                                  = REIV_PIXELS_TYPE_NONE;
  state.pixelsType[3]                                  = REIV_PIXELS_TYPE_NONE;
  state.pixelsSamplerState[0]                          = REIV_SAMPLER_STATE_LINEAR;
  state.pixelsSamplerState[1]                          = REIV_SAMPLER_STATE_NEAREST;
  state.pixelsSamplerState[2]                          = REIV_SAMPLER_STATE_NEAREST;
  state.pixelsSamplerState[3]                          = REIV_SAMPLER_STATE_NEAREST;

  ReivBatchPipeline pipelines[2] = {};

  pipelines[0].pipelineIndex = 0;
  pipelines[0].state         = &stateSkybox;

  pipelines[1].pipelineIndex = 1;
  pipelines[1].state         = &state;

#ifdef _WIN32
  FILE * cubePxFileFd = NULL;
  FILE * cubeNxFileFd = NULL;
  FILE * cubePyFileFd = NULL;
  FILE * cubeNyFileFd = NULL;
  FILE * cubePzFileFd = NULL;
  FILE * cubeNzFileFd = NULL;

  fopen_s(&cubePxFileFd, "cube/cube_px_right.png",  "rb");
  fopen_s(&cubeNxFileFd, "cube/cube_nx_left.png",   "rb");
  fopen_s(&cubePyFileFd, "cube/cube_py_top.png",    "rb");
  fopen_s(&cubeNyFileFd, "cube/cube_ny_bottom.png", "rb");
  fopen_s(&cubePzFileFd, "cube/cube_pz_front.png",  "rb");
  fopen_s(&cubeNzFileFd, "cube/cube_nz_back.png",   "rb");

  int cubeW = 0, cubeH = 0, cubeBpp = 0;
  void * cubePx = stbi_load_from_file(cubePxFileFd, &cubeW, &cubeH, &cubeBpp, STBI_rgb_alpha);
  void * cubeNx = stbi_load_from_file(cubeNxFileFd, &cubeW, &cubeH, &cubeBpp, STBI_rgb_alpha);
  void * cubePy = stbi_load_from_file(cubePyFileFd, &cubeW, &cubeH, &cubeBpp, STBI_rgb_alpha);
  void * cubeNy = stbi_load_from_file(cubeNyFileFd, &cubeW, &cubeH, &cubeBpp, STBI_rgb_alpha);
  void * cubePz = stbi_load_from_file(cubePzFileFd, &cubeW, &cubeH, &cubeBpp, STBI_rgb_alpha);
  void * cubeNz = stbi_load_from_file(cubeNzFileFd, &cubeW, &cubeH, &cubeBpp, STBI_rgb_alpha);
#else
  int cubePxFileFd = open("cube/cube_px_right.png",  O_RDONLY);
  int cubeNxFileFd = open("cube/cube_nx_left.png",   O_RDONLY);
  int cubePyFileFd = open("cube/cube_py_top.png",    O_RDONLY);
  int cubeNyFileFd = open("cube/cube_ny_bottom.png", O_RDONLY);
  int cubePzFileFd = open("cube/cube_pz_front.png",  O_RDONLY);
  int cubeNzFileFd = open("cube/cube_nz_back.png",   O_RDONLY);

  struct stat cubePxFileSt = {};
  struct stat cubeNxFileSt = {};
  struct stat cubePyFileSt = {};
  struct stat cubeNyFileSt = {};
  struct stat cubePzFileSt = {};
  struct stat cubeNzFileSt = {};

  fstat(cubePxFileFd, &cubePxFileSt);
  fstat(cubeNxFileFd, &cubeNxFileSt);
  fstat(cubePyFileFd, &cubePyFileSt);
  fstat(cubeNyFileFd, &cubeNyFileSt);
  fstat(cubePzFileFd, &cubePzFileSt);
  fstat(cubeNzFileFd, &cubeNzFileSt);

  unsigned char * cubePxFileMem = mmap(0, cubePxFileSt.st_size, PROT_READ, MAP_PRIVATE, cubePxFileFd, 0);
  unsigned char * cubeNxFileMem = mmap(0, cubeNxFileSt.st_size, PROT_READ, MAP_PRIVATE, cubeNxFileFd, 0);
  unsigned char * cubePyFileMem = mmap(0, cubePyFileSt.st_size, PROT_READ, MAP_PRIVATE, cubePyFileFd, 0);
  unsigned char * cubeNyFileMem = mmap(0, cubeNyFileSt.st_size, PROT_READ, MAP_PRIVATE, cubeNyFileFd, 0);
  unsigned char * cubePzFileMem = mmap(0, cubePzFileSt.st_size, PROT_READ, MAP_PRIVATE, cubePzFileFd, 0);
  unsigned char * cubeNzFileMem = mmap(0, cubeNzFileSt.st_size, PROT_READ, MAP_PRIVATE, cubeNzFileFd, 0);

  int cubeW = 0, cubeH = 0, cubeBpp = 0;
  void * cubePx = stbi_load_from_memory(cubePxFileMem, cubePxFileSt.st_size, &cubeW, &cubeH, &cubeBpp, STBI_rgb_alpha);
  void * cubeNx = stbi_load_from_memory(cubeNxFileMem, cubeNxFileSt.st_size, &cubeW, &cubeH, &cubeBpp, STBI_rgb_alpha);
  void * cubePy = stbi_load_from_memory(cubePyFileMem, cubePyFileSt.st_size, &cubeW, &cubeH, &cubeBpp, STBI_rgb_alpha);
  void * cubeNy = stbi_load_from_memory(cubeNyFileMem, cubeNyFileSt.st_size, &cubeW, &cubeH, &cubeBpp, STBI_rgb_alpha);
  void * cubePz = stbi_load_from_memory(cubePzFileMem, cubePzFileSt.st_size, &cubeW, &cubeH, &cubeBpp, STBI_rgb_alpha);
  void * cubeNz = stbi_load_from_memory(cubeNzFileMem, cubeNzFileSt.st_size, &cubeW, &cubeH, &cubeBpp, STBI_rgb_alpha);
#endif

  ReivBatchPixels pixels = {};

  pixels.pixelsIndex         = 0;
  pixels.allocateLevelsCount = 1;
  pixels.level               = 0;
  pixels.x                   = 0;
  pixels.y                   = 0;
  pixels.w                   = cubeW;
  pixels.h                   = cubeH;
  pixels.rgba[0]             = cubePx;
  pixels.rgba[1]             = cubeNx;
  pixels.rgba[2]             = cubePy;
  pixels.rgba[3]             = cubeNy;
  pixels.rgba[4]             = cubePz;
  pixels.rgba[5]             = cubeNz;

  ReivBatchMeshAos meshes[2] = {};

  float skybox[36 * 4] = {};

  skybox[0  * 4 + 0] = -1; skybox[0  * 4 + 1] = -1; skybox[0  * 4 + 2] =  1; skybox[0  * 4 + 3] =  1;
  skybox[1  * 4 + 0] = -1; skybox[1  * 4 + 1] = -1; skybox[1  * 4 + 2] = -1; skybox[1  * 4 + 3] =  1;
  skybox[2  * 4 + 0] =  1; skybox[2  * 4 + 1] = -1; skybox[2  * 4 + 2] = -1; skybox[2  * 4 + 3] =  1;
  skybox[3  * 4 + 0] =  1; skybox[3  * 4 + 1] = -1; skybox[3  * 4 + 2] = -1; skybox[3  * 4 + 3] =  1;
  skybox[4  * 4 + 0] =  1; skybox[4  * 4 + 1] = -1; skybox[4  * 4 + 2] =  1; skybox[4  * 4 + 3] =  1;
  skybox[5  * 4 + 0] = -1; skybox[5  * 4 + 1] = -1; skybox[5  * 4 + 2] =  1; skybox[5  * 4 + 3] =  1;
  skybox[6  * 4 + 0] = -1; skybox[6  * 4 + 1] =  1; skybox[6  * 4 + 2] = -1; skybox[6  * 4 + 3] =  1;
  skybox[7  * 4 + 0] = -1; skybox[7  * 4 + 1] = -1; skybox[7  * 4 + 2] = -1; skybox[7  * 4 + 3] =  1;
  skybox[8  * 4 + 0] = -1; skybox[8  * 4 + 1] = -1; skybox[8  * 4 + 2] =  1; skybox[8  * 4 + 3] =  1;
  skybox[9  * 4 + 0] = -1; skybox[9  * 4 + 1] = -1; skybox[9  * 4 + 2] =  1; skybox[9  * 4 + 3] =  1;
  skybox[10 * 4 + 0] = -1; skybox[10 * 4 + 1] =  1; skybox[10 * 4 + 2] =  1; skybox[10 * 4 + 3] =  1;
  skybox[11 * 4 + 0] = -1; skybox[11 * 4 + 1] =  1; skybox[11 * 4 + 2] = -1; skybox[11 * 4 + 3] =  1;
  skybox[12 * 4 + 0] =  1; skybox[12 * 4 + 1] = -1; skybox[12 * 4 + 2] = -1; skybox[12 * 4 + 3] =  1;
  skybox[13 * 4 + 0] =  1; skybox[13 * 4 + 1] =  1; skybox[13 * 4 + 2] = -1; skybox[13 * 4 + 3] =  1;
  skybox[14 * 4 + 0] =  1; skybox[14 * 4 + 1] =  1; skybox[14 * 4 + 2] =  1; skybox[14 * 4 + 3] =  1;
  skybox[15 * 4 + 0] =  1; skybox[15 * 4 + 1] =  1; skybox[15 * 4 + 2] =  1; skybox[15 * 4 + 3] =  1;
  skybox[16 * 4 + 0] =  1; skybox[16 * 4 + 1] = -1; skybox[16 * 4 + 2] =  1; skybox[16 * 4 + 3] =  1;
  skybox[17 * 4 + 0] =  1; skybox[17 * 4 + 1] = -1; skybox[17 * 4 + 2] = -1; skybox[17 * 4 + 3] =  1;
  skybox[18 * 4 + 0] = -1; skybox[18 * 4 + 1] =  1; skybox[18 * 4 + 2] = -1; skybox[18 * 4 + 3] =  1;
  skybox[19 * 4 + 0] = -1; skybox[19 * 4 + 1] =  1; skybox[19 * 4 + 2] =  1; skybox[19 * 4 + 3] =  1;
  skybox[20 * 4 + 0] =  1; skybox[20 * 4 + 1] =  1; skybox[20 * 4 + 2] =  1; skybox[20 * 4 + 3] =  1;
  skybox[21 * 4 + 0] =  1; skybox[21 * 4 + 1] =  1; skybox[21 * 4 + 2] =  1; skybox[21 * 4 + 3] =  1;
  skybox[22 * 4 + 0] =  1; skybox[22 * 4 + 1] =  1; skybox[22 * 4 + 2] = -1; skybox[22 * 4 + 3] =  1;
  skybox[23 * 4 + 0] = -1; skybox[23 * 4 + 1] =  1; skybox[23 * 4 + 2] = -1; skybox[23 * 4 + 3] =  1;
  skybox[24 * 4 + 0] = -1; skybox[24 * 4 + 1] = -1; skybox[24 * 4 + 2] =  1; skybox[24 * 4 + 3] =  1;
  skybox[25 * 4 + 0] =  1; skybox[25 * 4 + 1] = -1; skybox[25 * 4 + 2] =  1; skybox[25 * 4 + 3] =  1;
  skybox[26 * 4 + 0] =  1; skybox[26 * 4 + 1] =  1; skybox[26 * 4 + 2] =  1; skybox[26 * 4 + 3] =  1;
  skybox[27 * 4 + 0] =  1; skybox[27 * 4 + 1] =  1; skybox[27 * 4 + 2] =  1; skybox[27 * 4 + 3] =  1;
  skybox[28 * 4 + 0] = -1; skybox[28 * 4 + 1] =  1; skybox[28 * 4 + 2] =  1; skybox[28 * 4 + 3] =  1;
  skybox[29 * 4 + 0] = -1; skybox[29 * 4 + 1] = -1; skybox[29 * 4 + 2] =  1; skybox[29 * 4 + 3] =  1;
  skybox[30 * 4 + 0] = -1; skybox[30 * 4 + 1] = -1; skybox[30 * 4 + 2] = -1; skybox[30 * 4 + 3] =  1;
  skybox[31 * 4 + 0] = -1; skybox[31 * 4 + 1] =  1; skybox[31 * 4 + 2] = -1; skybox[31 * 4 + 3] =  1;
  skybox[32 * 4 + 0] =  1; skybox[32 * 4 + 1] = -1; skybox[32 * 4 + 2] = -1; skybox[32 * 4 + 3] =  1;
  skybox[33 * 4 + 0] =  1; skybox[33 * 4 + 1] = -1; skybox[33 * 4 + 2] = -1; skybox[33 * 4 + 3] =  1;
  skybox[34 * 4 + 0] = -1; skybox[34 * 4 + 1] =  1; skybox[34 * 4 + 2] = -1; skybox[34 * 4 + 3] =  1;
  skybox[35 * 4 + 0] =  1; skybox[35 * 4 + 1] =  1; skybox[35 * 4 + 2] = -1; skybox[35 * 4 + 3] =  1;

  meshes[0].meshIndex     = 0;
  meshes[0].vertexesFirst = 0;
  meshes[0].vertexesCount = _countof(skybox) / 4;
  meshes[0].xyzw[0]       = NULL;
  meshes[0].xyzw[1]       = NULL;
  meshes[0].xyzw[2]       = NULL;
  meshes[0].xyzw[3]       = skybox;

  meshes[1].meshIndex     = 1;
  meshes[1].vertexesFirst = 0;
  meshes[1].vertexesCount = _countof(meshVertexesFloats) / 4;
  meshes[1].xyzw[0]       = meshNormalsFloats;
  meshes[1].xyzw[1]       = NULL;
  meshes[1].xyzw[2]       = NULL;
  meshes[1].xyzw[3]       = meshVertexesFloats;

  reivResources(2, meshes, 0, NULL, 1, &pixels, 2, pipelines);

  if (cubePx != NULL) { stbi_image_free(cubePx); cubePx = NULL; }
  if (cubeNx != NULL) { stbi_image_free(cubeNx); cubeNx = NULL; }
  if (cubePy != NULL) { stbi_image_free(cubePy); cubePy = NULL; }
  if (cubeNy != NULL) { stbi_image_free(cubeNy); cubeNy = NULL; }
  if (cubePz != NULL) { stbi_image_free(cubePz); cubePz = NULL; }
  if (cubeNz != NULL) { stbi_image_free(cubeNz); cubeNz = NULL; }

#ifdef _WIN32
  if (cubePxFileFd != NULL) { fclose(cubePxFileFd); cubePxFileFd = 0; }
  if (cubeNxFileFd != NULL) { fclose(cubeNxFileFd); cubeNxFileFd = 0; }
  if (cubePyFileFd != NULL) { fclose(cubePyFileFd); cubePyFileFd = 0; }
  if (cubeNyFileFd != NULL) { fclose(cubeNyFileFd); cubeNyFileFd = 0; }
  if (cubePzFileFd != NULL) { fclose(cubePzFileFd); cubePzFileFd = 0; }
  if (cubeNzFileFd != NULL) { fclose(cubeNzFileFd); cubeNzFileFd = 0; }
#else
  if (cubePxFileMem != NULL) { munmap(cubePxFileMem, cubePxFileSt.st_size); cubePxFileMem = NULL; }
  if (cubeNxFileMem != NULL) { munmap(cubeNxFileMem, cubeNxFileSt.st_size); cubeNxFileMem = NULL; }
  if (cubePyFileMem != NULL) { munmap(cubePyFileMem, cubePyFileSt.st_size); cubePyFileMem = NULL; }
  if (cubeNyFileMem != NULL) { munmap(cubeNyFileMem, cubeNyFileSt.st_size); cubeNyFileMem = NULL; }
  if (cubePzFileMem != NULL) { munmap(cubePzFileMem, cubePzFileSt.st_size); cubePzFileMem = NULL; }
  if (cubeNzFileMem != NULL) { munmap(cubeNzFileMem, cubeNzFileSt.st_size); cubeNzFileMem = NULL; }

  if (cubePxFileFd != 0) { close(cubePxFileFd); cubePxFileFd = 0; }
  if (cubeNxFileFd != 0) { close(cubeNxFileFd); cubeNxFileFd = 0; }
  if (cubePyFileFd != 0) { close(cubePyFileFd); cubePyFileFd = 0; }
  if (cubeNyFileFd != 0) { close(cubeNyFileFd); cubeNyFileFd = 0; }
  if (cubePzFileFd != 0) { close(cubePzFileFd); cubePzFileFd = 0; }
  if (cubeNzFileFd != 0) { close(cubeNzFileFd); cubeNzFileFd = 0; }
#endif

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
  clear.clearDepth   = 1;
  clear.clearStencil = 0;
  clear.clearColor   = 1;
  clear.depth        = 0.f;
  clear.stencil      = 0;
  clear.color[0]     = 0.f;
  clear.color[1]     = 0.f;
  clear.color[2]     = 0.f;
  clear.color[3]     = 1.f;

  ReivBatchDraw draws[7] = {};

  draws[0].registerIndex       = REIV_REGISTER_VIEWPORT;
  draws[0].register32BitValues = &viewport;

  draws[1].registerIndex       = REIV_REGISTER_SCISSOR;
  draws[1].register32BitValues = &scissor;

  draws[2].registerIndex       = REIV_REGISTER_CLEAR;
  draws[2].register32BitValues = &clear;

  float pos[4] = {};
  pos[0] = 0;
  pos[1] = 0;
  pos[2] = -2.f;
  pos[3] = 0;

  draws[3].registerIndex            = 0;
  draws[3].register32BitValuesCount = 4;
  draws[3].register32BitValues      = pos;

  float rot[4] = {};
  rot[0] = 0;
  rot[1] = 0;
  rot[2] = 0;
  rot[3] = 0;

  draws[4].registerIndex            = 1;
  draws[4].register32BitValuesCount = 4;
  draws[4].register32BitValues      = rot;

  draws[5].meshIndex        = 0;
  draws[5].pipelineIndex    = 0;
  draws[5].pixelsIndexes[0] = 0;
  draws[5].pixelsIndexes[1] = 0;
  draws[5].pixelsIndexes[2] = 0;
  draws[5].pixelsIndexes[3] = 0;
  draws[5].instancesCount   = 1;

  draws[6].meshIndex        = 1;
  draws[6].pipelineIndex    = 1;
  draws[6].pixelsIndexes[0] = 0;
  draws[6].pixelsIndexes[1] = 0;
  draws[6].pixelsIndexes[2] = 0;
  draws[6].pixelsIndexes[3] = 0;
  draws[6].instancesCount   = 1;

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  float rotationX = 0;
  float rotationY = 0;

  glfwPollEvents();

  double startMouseX = 0;
  double startMouseY = 0;
  glfwGetCursorPos(window, &startMouseX, &startMouseY);
  double prevMouseX = startMouseX;
  double prevMouseY = startMouseY;

  for (; glfwWindowShouldClose(window) == 0;) {
    glfwPollEvents();

    double mouseX = 0;
    double mouseY = 0;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    float mouseDispX = (float)(prevMouseX - mouseX) * 0.0035f;
    float mouseDispY = (float)(mouseY - prevMouseY) * 0.0035f;

    rotationX += mouseDispX;
    rotationY += mouseDispY;

    float moveVecX = 0;
    float moveVecY = 0;
    float moveVecZ = 0;

    moveVecX += glfwGetKey(window, GLFW_KEY_D);
    moveVecX -= glfwGetKey(window, GLFW_KEY_A);

    moveVecY += glfwGetKey(window, GLFW_KEY_E);
    moveVecY -= glfwGetKey(window, GLFW_KEY_Q);

    moveVecZ += glfwGetKey(window, GLFW_KEY_W);
    moveVecZ -= glfwGetKey(window, GLFW_KEY_S);

    float moveVecLen = sqrtf(moveVecX*moveVecX + moveVecY*moveVecY + moveVecZ*moveVecZ);
    if (moveVecLen != 0) {
      moveVecX /= moveVecLen;
      moveVecY /= moveVecLen;
      moveVecZ /= moveVecLen;
    }

    {
      float rotationCos = cosf(rotationY);
      float rotationSin = sinf(rotationY);
      float positionY = moveVecY;
      float positionZ = moveVecZ;
      moveVecY = positionY * rotationCos - positionZ * rotationSin;
      moveVecZ = positionZ * rotationCos + positionY * rotationSin;
    }

    {
      float rotationCos = cosf(rotationX);
      float rotationSin = sinf(rotationX);
      float positionX = moveVecX;
      float positionZ = moveVecZ;
      moveVecX = positionX * rotationCos - positionZ * rotationSin;
      moveVecZ = positionZ * rotationCos + positionX * rotationSin;
    }

    pos[0] += moveVecX * 0.025;
    pos[1] += moveVecY * 0.025;
    pos[2] += moveVecZ * 0.025;

    rot[0] = cosf(-rotationX);
    rot[1] = sinf(-rotationX);
    rot[2] = cosf(-rotationY);
    rot[3] = sinf(-rotationY);

    reivDraw(_countof(draws), draws);

    reivPresent();

    prevMouseX = mouseX;
    prevMouseY = mouseY;
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
