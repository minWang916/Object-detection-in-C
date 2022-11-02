#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

unsigned char processing_image(unsigned char *Template,int width, int height,int channel,unsigned char *background,int width1, int height1, int channel1)
{

	for(int i = 0; i < height1 - height + 1; i++)
	{
		for(int j = 0; j < width1 - width + 1;j++)
		{
			
			/*
			double cosine = 0;
			double dot = 0;
			double A = 0;
			double B = 0;
			
			for(int h = 0;h < height; h++)
			{
				for(int w = 0; w < width; w++)
				{
					double pixel_template = (Template[h*width*channel + w * channel + 0]/255.0 + Template[h*width*channel + w * channel + 1]/255.0 + Template[h*width*channel + w * channel + 2]/255.0)/3.0;
					double pixel_background = (background[(i+h)*width1*channel + (j+w)* channel + 0]/255.0 + background[(i+h)*width1*channel + (j+w) * channel + 1]/255.0 + background[(i+h)*width1*channel + (j+w) * channel + 2]/255.0)/3.0;
					
					A   += pow(pixel_template, 2.0);
					B   += pow(pixel_background, 2.0);
					dot += pixel_template*pixel_background;
									
				}
				cosine += dot/(pow(A,0.5)*pow(B,0.5));
				
			}
			cosine = cosine/height;
			if (cosine > 0.99) 
			{
				
			}
			*/
			
			double cosine = 0;
			double dot = 0;
			double A = 0;
			double B = 0;
			
			
			for(int h = 0;h < height; h++)
			{
				for(int w = 0; w < width; w++)
				{
					double pixel_template = (Template[h*width*channel + w * channel + 0]/255.0 + Template[h*width*channel + w * channel + 1]/255.0 + Template[h*width*channel + w * channel + 2]/255.0)/3.0;
					double pixel_background = (background[(i+h)*width1*channel + (j+w)* channel + 0]/255.0 + background[(i+h)*width1*channel + (j+w) * channel + 1]/255.0 + background[(i+h)*width1*channel + (j+w) * channel + 2]/255.0)/3.0;
					
					A   += pow(pixel_template, 2.0);
					B   += pow(pixel_background, 2.0);
					dot += pixel_template*pixel_background;
					
				}
				cosine += dot/(pow(A,0.5)*pow(B,0.5));
			}
			cosine = cosine/height;
			if (cosine > 0.95) {
				
				
				
					for(int w = 0; w < width;w++){
						background[(i)*width1*channel + (j+w)* channel + 0] = 255;
						background[(i)*width1*channel + (j+w)* channel + 1] = 0;
						background[(i)*width1*channel + (j+w)* channel + 2] = 0;
						
						background[(i+height - 1)*width1*channel + (j+w)* channel + 0] = 255;
						background[(i+height - 1)*width1*channel + (j+w)* channel + 1] = 0;
						background[(i+height - 1)*width1*channel + (j+w)* channel + 2] = 0;
					}
						
					for(int h = 0; h < height;h++){
						
						background[(i+h)*width1*channel + (j)*channel + 0] = 255;
						background[(i+h)*width1*channel + (j)*channel + 1] = 0;
						background[(i+h)*width1*channel + (j)*channel + 2] = 0;
						
						background[(i+h)*width1*channel + (j+width-1)*channel + 0] = 255;
						background[(i+h)*width1*channel + (j+width-1)*channel + 1] = 0;
						background[(i+h)*width1*channel + (j+width-1)*channel + 2] = 0;
					}
				
				
				
			}
		}
		
	}

		
}

int main()
{
    
	char path_template[] = "template.jpg";
	
	//load template
	int width, height, channel;
	unsigned char *Template = stbi_load(path_template, &width, &height, &channel, 0);
	if ( Template == NULL )
	{
		printf("\ nCan't load Template \n");
		exit(1);
	}
	printf ("Template Width = %d Height = %d Channel = %d\n", width , height, channel );

	char path_background[] = "./images/img17.jpg";
	
	//load background
	int width1, height1, channel1;
	unsigned char *background = stbi_load(path_background, &width1, &height1, &channel1, 0);
	if ( background == NULL )
	{
		printf("\ nCan't load background \n");
		exit(1);
	}
	printf ("Background Width = %d Height = %d Channel = %d\n", width1 , height1, channel1 );
	
	
	processing_image(Template, width, height, channel, background, width1, height1, channel1);
	
	char save_path[] = "result_image.jpg";
	stbi_write_png(save_path , width1 , height1 , channel1 , background, width1 * channel1 );
	printf("\nSave image complete\n");
	return 0;
	
}
