/*
 * x264Encoder.c
 *
 *  Created on: Jul 16, 2014
 *      Author: zsy
 */

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "global.h"
#include "x264Encoder.h"

#ifdef __cplusplus
extern "C"{
#endif
/* c++引用C，将#include "x264.h"放到extern "C" 中 */
#include "x264.h"
/* x264 */
static x264_param_t 	x264_param;
static x264_picture_t	x264_picture;
static x264_t			*x264_fd;
static x264_nal_t 		*nal;
static FILE 			*x264_file=NULL;
static unsigned char	*h264_buf;

void init_x264(int width, int height, int rate) {
	x264_param_default(&x264_param);
	x264_param.i_width = width;
	x264_param.i_height = height;
	x264_param.i_fps_num = rate;
	x264_param.i_fps_den = 1;
	/* 和x264_picture的i_csp一致 */
	x264_param.i_csp = X264_CSP_I422;
	x264_param_apply_profile(&x264_param, x264_profile_names[0]);
	x264_fd = x264_encoder_open(&x264_param);
	dePrintf("i_csp:%d\n", x264_param.i_csp);
	x264_picture_alloc(&x264_picture, X264_CSP_I422, x264_param.i_width,
			x264_param.i_height);
	x264_picture.img.i_csp = X264_CSP_I422;
	x264_picture.img.i_plane = 3;
	x264_file = fopen("test.h264", "wa+");
	h264_buf = (unsigned char*)malloc(width*height*3);
}

void encode2h264(const void *p, int size) {
	x264_picture_t pic_out;
	int nNal = -1;
	int len = 0;
	unsigned char *y = x264_picture.img.plane[0];
	unsigned char *u = x264_picture.img.plane[1];
	unsigned char *v = x264_picture.img.plane[2];

	int i=0;
	int is_y = 1, is_u = 1;
	int y_index = 0, u_index = 0, v_index = 0;
	dePrintf("size:%d\n", size);
	//序列为YU YV YU YV，一个yuv422帧的长度 width * height * 2 个字节
	for (i = 0; i < size; ++i) {
		if (is_y) {
			*(y + y_index) = *(unsigned char*)(p + i);
			++y_index;
			is_y = 0;
		} else {
			if (is_u) {
				*(u + u_index) = *(unsigned char*)(p + i);
				++u_index;
				is_u = 0;
			} else {
				*(v + v_index) = *(unsigned char*)(p + i);
				++v_index;
				is_u = 1;
			}
			is_y = 1;
		}
	}
	x264_picture.i_type = X264_TYPE_AUTO;
	x264_encoder_encode(x264_fd, &nal, &nNal, &x264_picture,
			&pic_out);
	x264_picture.i_pts++;
	for (i=0; i<nNal; i++) {
		memcpy(h264_buf+len, nal[i].p_payload, nal[i].i_payload);
		len += nal[i].i_payload;
	}
	fwrite(h264_buf, len, 1, x264_file);
}

void deinit_x264(void) {
	x264_picture_clean(&x264_picture);
	x264_encoder_close(x264_fd);
	fclose(x264_file);
	free(h264_buf);
}
#ifdef __cplusplus
}
#endif
