#include <stdlib.h>
#include <unistd.h>
#include <x265.h>
#include "getVmaf.h"


void setX265Data(x265_vmaf_data* data, int width, int height, int internalBitDepth, FILE* reference_file, FILE* distorted_file){
  data->width = width;
  data->height = height;
  data->internalBitDepth = internalBitDepth;
  data->reference_file = reference_file;
  data->distorted_file = distorted_file;
}


int main() {
  //temporarally hardcode values
  int width = 576;
  int height = 324;
  int internalBitDepth = 10;
  //I believe offset gets set by x265_calculate_vmafscore  
 
  //open files
  FILE* origFile = fopen("/home/vimeo/vmaf/video_file_encoded/test_1.yuv","r");
  FILE* encFile = fopen("/home/vimeo/vmaf/video_file_not_encoded/test_1.yuv","r");

  //set up param struct
  x265_param* param = x265_param_alloc();
  x265_param_default(param);
  
  //set up data struct
  x265_vmaf_data* data = malloc(sizeof(x265_vmaf_data));
  setX265Data(data, width, height, internalBitDepth, origFile, encFile);
  
  //calculate and print vmaf score  
  double score = x265_calculate_vmafscore(param,data);
  printf("%f\n",score);
  
  //free mallocs
  free(data);
  x265_param_free(param);
  
  //close files
  fclose(origFile);
  fclose(encFile);
}
