/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Fri Feb 23 16:25:05 2024
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "network.h"
#include "network_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "1ba27ba6c023fd8c90b192ad27706fc4"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Fri Feb 23 16:25:05 2024"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

static ai_ptr g_network_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_network_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_10_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)
/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_11_Gemm_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)
/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  output_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 10, AI_STATIC)
/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 144, AI_STATIC)
/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)
/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_3_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4608, AI_STATIC)
/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_3_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)
/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_6_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 18432, AI_STATIC)
/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_6_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_9_Gemm_output_0_weights_array, AI_ARRAY_FORMAT_LUT8_FLOAT,
  NULL, NULL, 401408, AI_STATIC)
/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_9_Gemm_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)
/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_11_Gemm_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1280, AI_STATIC)
/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_11_Gemm_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)
/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  input_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 784, AI_STATIC)
/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12544, AI_STATIC)
/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_1_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12544, AI_STATIC)
/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_2_MaxPool_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3136, AI_STATIC)
/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_3_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6272, AI_STATIC)
/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_4_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6272, AI_STATIC)
/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_5_MaxPool_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1568, AI_STATIC)
/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_6_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3136, AI_STATIC)
/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_7_Relu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3136, AI_STATIC)
/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_8_Flatten_output_0_to_chlast_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3136, AI_STATIC)
/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  _model_model_9_Gemm_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)
/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_10_Relu_output_0_output, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_model_10_Relu_output_0_output_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_11_Gemm_output_0_output, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &_model_model_11_Gemm_output_0_output_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  output_output, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &output_output_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_0_Conv_output_0_weights, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 16), AI_STRIDE_INIT(4, 4, 4, 64, 192),
  1, &_model_model_0_Conv_output_0_weights_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_0_Conv_output_0_bias, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_model_model_0_Conv_output_0_bias_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_3_Conv_output_0_weights, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 16, 3, 3, 32), AI_STRIDE_INIT(4, 4, 64, 2048, 6144),
  1, &_model_model_3_Conv_output_0_weights_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_3_Conv_output_0_bias, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &_model_model_3_Conv_output_0_bias_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_6_Conv_output_0_weights, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 64), AI_STRIDE_INIT(4, 4, 128, 8192, 24576),
  1, &_model_model_6_Conv_output_0_weights_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_6_Conv_output_0_bias, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_model_6_Conv_output_0_bias_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_9_Gemm_output_0_weights, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 3136, 128, 1, 1), AI_STRIDE_INIT(4, 1, 3136, 401408, 401408),
  1, &_model_model_9_Gemm_output_0_weights_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_9_Gemm_output_0_bias, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_model_9_Gemm_output_0_bias_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_11_Gemm_output_0_weights, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 128, 10, 1, 1), AI_STRIDE_INIT(4, 4, 512, 5120, 5120),
  1, &_model_model_11_Gemm_output_0_weights_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_11_Gemm_output_0_bias, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &_model_model_11_Gemm_output_0_bias_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  input_output, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 28, 28), AI_STRIDE_INIT(4, 4, 4, 4, 112),
  1, &input_output_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_0_Conv_output_0_output, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 28, 28), AI_STRIDE_INIT(4, 4, 4, 64, 1792),
  1, &_model_model_0_Conv_output_0_output_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_1_Relu_output_0_output, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 28, 28), AI_STRIDE_INIT(4, 4, 4, 64, 1792),
  1, &_model_model_1_Relu_output_0_output_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_2_MaxPool_output_0_output, AI_STATIC,
  16, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 14, 14), AI_STRIDE_INIT(4, 4, 4, 64, 896),
  1, &_model_model_2_MaxPool_output_0_output_array, NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_3_Conv_output_0_output, AI_STATIC,
  17, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 14, 14), AI_STRIDE_INIT(4, 4, 4, 128, 1792),
  1, &_model_model_3_Conv_output_0_output_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_4_Relu_output_0_output, AI_STATIC,
  18, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 14, 14), AI_STRIDE_INIT(4, 4, 4, 128, 1792),
  1, &_model_model_4_Relu_output_0_output_array, NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_5_MaxPool_output_0_output, AI_STATIC,
  19, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 7, 7), AI_STRIDE_INIT(4, 4, 4, 128, 896),
  1, &_model_model_5_MaxPool_output_0_output_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_6_Conv_output_0_output, AI_STATIC,
  20, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 7, 7), AI_STRIDE_INIT(4, 4, 4, 256, 1792),
  1, &_model_model_6_Conv_output_0_output_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_7_Relu_output_0_output, AI_STATIC,
  21, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 7, 7), AI_STRIDE_INIT(4, 4, 4, 256, 1792),
  1, &_model_model_7_Relu_output_0_output_array, NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_8_Flatten_output_0_to_chlast_output, AI_STATIC,
  22, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 7, 64), AI_STRIDE_INIT(4, 4, 4, 28, 196),
  1, &_model_model_8_Flatten_output_0_to_chlast_output_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_8_Flatten_output_0_to_chlast_output0, AI_STATIC,
  23, 0x0,
  AI_SHAPE_INIT(4, 1, 3136, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12544, 12544),
  1, &_model_model_8_Flatten_output_0_to_chlast_output_array, NULL)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  _model_model_9_Gemm_output_0_output, AI_STATIC,
  24, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_model_9_Gemm_output_0_output_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  output_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_11_Gemm_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  output_layer, 13,
  NL_TYPE, 0x0, NULL,
  nl, forward_sm,
  &output_chain,
  NULL, &output_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_model_11_Gemm_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_10_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_11_Gemm_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_model_11_Gemm_output_0_weights, &_model_model_11_Gemm_output_0_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_model_11_Gemm_output_0_layer, 12,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &_model_model_11_Gemm_output_0_chain,
  NULL, &output_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_model_10_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_9_Gemm_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_10_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_model_10_Relu_output_0_layer, 11,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_model_model_10_Relu_output_0_chain,
  NULL, &_model_model_11_Gemm_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_model_9_Gemm_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_8_Flatten_output_0_to_chlast_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_9_Gemm_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_model_9_Gemm_output_0_weights, &_model_model_9_Gemm_output_0_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_model_9_Gemm_output_0_layer, 10,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &_model_model_9_Gemm_output_0_chain,
  NULL, &_model_model_10_Relu_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_model_8_Flatten_output_0_to_chlast_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_7_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_8_Flatten_output_0_to_chlast_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_model_8_Flatten_output_0_to_chlast_layer, 9,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &_model_model_8_Flatten_output_0_to_chlast_chain,
  NULL, &_model_model_9_Gemm_output_0_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_HEIGHT, AI_SHAPE_CHANNEL, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_model_7_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_6_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_7_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_model_7_Relu_output_0_layer, 8,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_model_model_7_Relu_output_0_chain,
  NULL, &_model_model_8_Flatten_output_0_to_chlast_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_model_6_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_5_MaxPool_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_6_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_model_6_Conv_output_0_weights, &_model_model_6_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_model_6_Conv_output_0_layer, 7,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_model_6_Conv_output_0_chain,
  NULL, &_model_model_7_Relu_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_model_5_MaxPool_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_4_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_5_MaxPool_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_model_5_MaxPool_output_0_layer, 6,
  POOL_TYPE, 0x0, NULL,
  pool, forward_mp,
  &_model_model_5_MaxPool_output_0_chain,
  NULL, &_model_model_6_Conv_output_0_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_model_4_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_3_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_4_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_model_4_Relu_output_0_layer, 5,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_model_model_4_Relu_output_0_chain,
  NULL, &_model_model_5_MaxPool_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_model_3_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_2_MaxPool_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_3_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_model_3_Conv_output_0_weights, &_model_model_3_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_model_3_Conv_output_0_layer, 4,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_model_3_Conv_output_0_chain,
  NULL, &_model_model_4_Relu_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_model_2_MaxPool_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_1_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_2_MaxPool_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_model_2_MaxPool_output_0_layer, 3,
  POOL_TYPE, 0x0, NULL,
  pool, forward_mp,
  &_model_model_2_MaxPool_output_0_chain,
  NULL, &_model_model_3_Conv_output_0_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_model_1_Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_1_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_model_1_Relu_output_0_layer, 2,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_model_model_1_Relu_output_0_chain,
  NULL, &_model_model_2_MaxPool_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_model_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_model_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_model_0_Conv_output_0_weights, &_model_model_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_model_0_Conv_output_0_layer, 1,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_model_0_Conv_output_0_chain,
  NULL, &_model_model_1_Relu_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 501288, 1, 1),
    501288, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 53312, 1, 1),
    53312, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &output_output),
  &_model_model_0_Conv_output_0_layer, 0, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 501288, 1, 1),
      501288, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 53312, 1, 1),
      53312, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &output_output),
  &_model_model_0_Conv_output_0_layer, 0, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_network_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    input_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    input_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    
    _model_model_0_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3136);
    _model_model_0_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3136);
    
    _model_model_1_Relu_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3136);
    _model_model_1_Relu_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3136);
    
    _model_model_2_MaxPool_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3136);
    _model_model_2_MaxPool_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3136);
    
    _model_model_3_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 15680);
    _model_model_3_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 15680);
    
    _model_model_4_Relu_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 15680);
    _model_model_4_Relu_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 15680);
    
    _model_model_5_MaxPool_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _model_model_5_MaxPool_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    
    _model_model_6_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 6272);
    _model_model_6_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6272);
    
    _model_model_7_Relu_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 18816);
    _model_model_7_Relu_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 18816);
    
    _model_model_8_Flatten_output_0_to_chlast_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _model_model_8_Flatten_output_0_to_chlast_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    
    _model_model_9_Gemm_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 12544);
    _model_model_9_Gemm_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 12544);
    
    _model_model_10_Relu_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _model_model_10_Relu_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    
    _model_model_11_Gemm_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 512);
    _model_model_11_Gemm_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 512);
    
    output_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    output_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_network_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    _model_model_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_model_0_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 0);
    _model_model_0_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 0);
    
    _model_model_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_model_0_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 576);
    _model_model_0_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 576);
    
    _model_model_3_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_model_3_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 640);
    _model_model_3_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 640);
    
    _model_model_3_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_model_3_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 19072);
    _model_model_3_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 19072);
    
    _model_model_6_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_model_6_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 19200);
    _model_model_6_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 19200);
    
    _model_model_6_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_model_6_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 92928);
    _model_model_6_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 92928);
    
    _model_model_9_Gemm_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_model_9_Gemm_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 94208);
    _model_model_9_Gemm_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 93184);
    
    _model_model_9_Gemm_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_model_9_Gemm_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 495616);
    _model_model_9_Gemm_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 495616);
    
    _model_model_11_Gemm_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_model_11_Gemm_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 496128);
    _model_model_11_Gemm_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 496128);
    
    _model_model_11_Gemm_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_model_11_Gemm_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 501248);
    _model_model_11_Gemm_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 501248);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/


AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 2364784,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_bool ai_network_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 2364784,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_error ai_network_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
    ai_error err;
    ai_network_params params;

    err = ai_network_create(network, AI_NETWORK_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE)
        return err;
    if (ai_network_data_params_get(&params) != true) {
        err = ai_network_get_error(*network);
        return err;
    }
#if defined(AI_NETWORK_DATA_ACTIVATIONS_COUNT)
    if (activations) {
        /* set the addresses of the activations buffers */
        for (int idx=0;idx<params.map_activations.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
    }
#endif
#if defined(AI_NETWORK_DATA_WEIGHTS_COUNT)
    if (weights) {
        /* set the addresses of the weight buffers */
        for (int idx=0;idx<params.map_weights.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
    }
#endif
    if (ai_network_init(*network, &params) != true) {
        err = ai_network_get_error(*network);
    }
    return err;
}

AI_API_ENTRY
ai_buffer* ai_network_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_buffer* ai_network_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if (!net_ctx) return false;

  ai_bool ok = true;
  ok &= network_configure_weights(net_ctx, params);
  ok &= network_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

