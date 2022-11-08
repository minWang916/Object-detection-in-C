#include<stdio.h>

#include<stdlib.h>

#include<math.h>

#include<string.h>


#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

unsigned char processing_image(unsigned char * Template, int width, int height, int channel) {

    for (int o = 0; o <= 62; o++) {

        char temp[5];

        sprintf(temp, "%d", o);

        char path_background[] = "./images/img";

        char jpg[] = ".jpg";

        strcat(path_background, temp);
        strcat(path_background, jpg);
        printf("Load image %s \n", path_background);

        int width1, height1, channel1;
        unsigned char * background = stbi_load(path_background, & width1, & height1, & channel1, 0);

        double max = 0;
        int x = 0;
        int y = 0;

        char * tem = (char * ) malloc(width * height);

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                tem[i * width + j] = (0.299 * Template[i * width * channel + j * channel + 0]) + (0.587 * Template[i * width * channel + j * channel + 1]) + (0.114 * Template[i * width * channel + j * channel + 2]);
            }
        }

        char * back = (char * ) malloc(width1 * height1);

        for (int i = 0; i < height1; i++) {
            for (int j = 0; j < width1; j++) {
                back[i * width1 + j] = (0.299 * background[i * width1 * 3 + j * 3 + 0]) + (0.587 * background[i * width1 * 3 + j * 3 + 1]) + (0.114 * background[i * width1 * 3 + j * 3 + 2]);
            }
        }

        for (int i = 0; i < height1 - height + 1; i = i + 10) {

            for (int j = 0; j < width1 - width + 1; j = j + 10) {

                double cosine = 0;
                double dot = 0;
                double A = 0;
                double B = 0;

                for (int h = 0; h < height; h++) {
                    for (int w = 0; w < width; w++) {

                        A += pow(tem[h * width + w], 2.0);
                        B += pow(back[(i + h) * width1 + (j + w)], 2.0);
                        dot += tem[h * width + w] * back[(i + h) * width1 + (j + w)];

                    }
                }
                cosine += dot / (pow(A, 0.5) * pow(B, 0.5));
                if (cosine > max) {
                    max = cosine;
                    x = j;
                    y = i;
                }
                if (i * j % 20000 == 0 && i * j != 0) {
                	
                    printf("%c", 219);
                }
				
            }
        }
        printf("   Processing complete!\n");

        for (int w = 0; w < width; w++) {
            background[(y - 1) * width1 * channel + (x + w) * channel + 0] = 255;
            background[(y - 1) * width1 * channel + (x + w) * channel + 1] = 0;
            background[(y - 1) * width1 * channel + (x + w) * channel + 2] = 0;

            background[(y - 2) * width1 * channel + (x + w) * channel + 0] = 255;
            background[(y - 2) * width1 * channel + (x + w) * channel + 1] = 0;
            background[(y - 2) * width1 * channel + (x + w) * channel + 2] = 0;

            background[(y + height + 2) * width1 * channel + (x + w) * channel + 0] = 255;
            background[(y + height + 2) * width1 * channel + (x + w) * channel + 1] = 0;
            background[(y + height + 2) * width1 * channel + (x + w) * channel + 2] = 0;

            background[(y + height + 1) * width1 * channel + (x + w) * channel + 0] = 255;
            background[(y + height + 1) * width1 * channel + (x + w) * channel + 1] = 0;
            background[(y + height + 1) * width1 * channel + (x + w) * channel + 2] = 0;
        }

        for (int h = 0; h < height; h++) {

            background[(y + h) * width1 * channel + (x - 2) * channel + 0] = 255;
            background[(y + h) * width1 * channel + (x - 2) * channel + 1] = 0;
            background[(y + h) * width1 * channel + (x - 2) * channel + 2] = 0;

            background[(y + h) * width1 * channel + (x - 1) * channel + 0] = 255;
            background[(y + h) * width1 * channel + (x - 1) * channel + 1] = 0;
            background[(y + h) * width1 * channel + (x - 1) * channel + 2] = 0;

            background[(y + h) * width1 * channel + (x + width + 2) * channel + 0] = 255;
            background[(y + h) * width1 * channel + (x + width + 2) * channel + 1] = 0;
            background[(y + h) * width1 * channel + (x + width + 2) * channel + 2] = 0;

            background[(y + h) * width1 * channel + (x + width + 1) * channel + 0] = 255;
            background[(y + h) * width1 * channel + (x + width + 1) * channel + 1] = 0;
            background[(y + h) * width1 * channel + (x + width + 1) * channel + 2] = 0;
        }
        char save_path[] = "./Results/img";

        char temp1[5];

        sprintf(temp1, "%d", o);
        strcat(save_path, temp1);
        strcat(save_path, jpg);

        printf("Save to %s\n\n", save_path);

        stbi_write_png(save_path, width1, height1, channel1, background, width1 * channel1);

        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                Template[h * width * channel + w * channel + 0] = background[(y + h) * width1 * channel + (x + w) * channel + 0];
                Template[h * width * channel + w * channel + 1] = background[(y + h) * width1 * channel + (x + w) * channel + 1];
                Template[h * width * channel + w * channel + 2] = background[(y + h) * width1 * channel + (x + w) * channel + 2];
            }

        }

    }
}

int main() {

    char path_template[] = "template.jpg";

    //load template
    int width, height, channel;
    unsigned char * Template = stbi_load(path_template, & width, & height, & channel, 0);
    if (Template == NULL) {
        printf("\ nCan't load Template \n");
        exit(1);
    }
    printf("Template load successful Width = %d Height = %d Channel = %d\n\n", width, height, channel);

    processing_image(Template, width, height, channel);

}
