#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>


#define STB_IMAGE_IMPLEMENTATION
#include "F:\Intro to C\Project1\stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION  
#include "F:\Intro to C\Project1\stb_image_write.h"

#define BLOCK_SIZE 512

unsigned char *new_array(int _size)
{
    return (unsigned char *) calloc(_size, sizeof(unsigned char));
}

unsigned char filter(unsigned char *background, unsigned char *foreground, unsigned char *weather, int width, int height, int channel)
{

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            // int a = 1;
            int diff = 0;

            for (int k = 0; k < channel; k++)
            {
           
                //Find the difference between the R,G,B of foreground and background
                //Threshold
                diff += abs(foreground[i*width*channel+j*channel+k] - background[i*width*channel+j*channel+k]);
                
            }

            //guess the threshold of diff to be qualified as green
            if ( diff < 157 ){//this mean that as long as the difference is not larger than 150, the pixel is still greenish
                //Replace ALL 3 RGB with weather forecast if it belongs to green category
                for (int k = 0; k < channel; k++)
                {
                    foreground[i*width*channel+j*channel+k] = weather[i*width*channel+j*channel+k];
                }

            }
        }
        
    }
    
}


int main(){

    //Open background
    int width, height, channel;
    char path_img[] = "F:/Intro to C/Project1/images/background.png";

    unsigned char *image = stbi_load(path_img, &width, &height, &channel, 0);
    if (image == NULL)
    {
        printf("\n Error loading image");
        exit(1);
    }
    printf("Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);
    
    //open foreground
    int width2, height2, channel2;
    char path_img2[] = "F:/Intro to C/Project1/images/foreground.png";

    unsigned char *image2 = stbi_load(path_img2, &width2, &height2, &channel2, 0);
    if (image2 == NULL)
    {
        printf("\n Error loading image");
        exit(1);
    }
    printf("\nWidth = %d\nHeight = %d\nChannel = %d\n", width2, height2, channel2);
  

    //open weather
    int width3, height3, channel3;
    char path_img3[] = "F:/Intro to C/Project1/images/weather.jpg";

    unsigned char *image3 = stbi_load(path_img3, &width3, &height3, &channel3, 0);
    if (image3 == NULL)
    {
        printf("\n Error loading image");
        exit(1);
    }
    printf("\nWidth = %d\nHeight = %d\nChannel = %d\n", width3, height3, channel3);

    //filter
    filter(image,image2,image3,width,height,channel);
    
    //save new image
    char save_path[] = "F:/Intro to C/Project1/new.png";
    stbi_write_png(save_path,width2,height2,channel2,image2,width2*channel2);

  

}
