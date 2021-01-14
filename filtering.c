/////////////////////////////////////
// CSCI 558 Multimedia - Image filtering by difference operators
// Author: Chu-An Tsai
// 04/05/2020
/////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define DATASIZE 375000 //99856 //307200
#define H 500 //316 //480
#define W 750 //316 //640

FILE *file_id1, *file_33_Y, *file_33_X, *file_55_Y, *file_55_X;
unsigned char img[H][W], out_33_Y[H][W], out_33_X[H][W], out_55_Y[H][W], out_55_X[H][W];
int i, j, k, l, temp_33Y, temp_33X, temp_33y, temp_33x, temp_55Y, temp_55X, temp_55y, temp_55x;
int temp1, temp33Y[H][W], temp33X[H][W], temp55Y[H][W], temp55X[H][W];
float max_33y, min_33y, max_33x, min_33x, max_55y, min_55y, max_55x, min_55x;
float normal_33y, normal_33x, normal_55y, normal_55x;
// Filters
int filt33_x[3][3] = {-1,0,1,-2,0,2,-1,0,1};
int filt33_y[3][3] = {-1,-2,-1,0,0,0,1,2,1};
int filt55_x[5][5] = {-1,-2,0,2,1,-2,-4,0,4,2,-4,-8,0,8,4,-2,-4,0,4,2,-1,-2,0,2,1};
int filt55_y[5][5] = {-1,-2,-4,-2,-1,-2,-4,-8,-4,-2,0,0,0,0,0,2,4,8,4,2,1,2,4,2,1};
// Filters turning 180 degrees to perform convolution
int filt33_180x[3][3] = {1,0,-1,2,0,-2,1,0,-1};
int filt33_180y[3][3] = {1,2,1,0,0,0,-1,-2,-1};
int filt55_180x[5][5] = {1,2,0,-2,-1,2,4,0,-4,-2,4,8,0,-8,-4,2,4,0,-4,-2,1,2,0,-2,-1};
int filt55_180y[5][5] = {1,2,4,2,1,2,4,8,4,2,0,0,0,0,0,-2,-4,-8,-4,-2,-1,-2,-4,-2,-1};

int main( ) {
	
	// Read input
    file_id1 = fopen("CB.raw","rb");
    fread(img, 1, DATASIZE, file_id1);
    fclose(file_id1);
		
	// For 3*3 filters
    for (i=0; i<H; i++) {
        for (j=0; j<W; j++) {
        	
        	// Skip 1 line (the filter is not fully inside the image)
            if (i==0 || i==H-1 || j==0 || j==W-1){
            	out_33_Y[i][j] = 128;
            	out_33_X[i][j] = 128;           	
			}
			
			// Do convolution when the whole filter moves inside the image
			else {				
				temp_33Y=0;
				temp_33X=0;	
				
				// Convolution		
				for (k=0; k<3; k++){										
					for (l=0; l<3; l++){														
						temp_33y = filt33_180y[k][l]*img[i-1+k][j-1+l];
						temp_33Y += temp_33y;
						temp_33x = filt33_180x[k][l]*img[i-1+k][j-1+l];
						temp_33X += temp_33x;
					}					
				}
				
				out_33_Y[i][j] = temp_33Y/4/2 + 128;
            	out_33_X[i][j] = temp_33X/4/2 + 128;
				
				/*				
				temp33Y[i][j] = temp_33Y;
				temp33X[i][j] = temp_33X;
				
				// Find the Max and Min value (to perform normalization later)
				if (temp33Y[i][j]>max_33y) {
    				max_33y = temp33Y[i][j];
				}
				if (temp33Y[i][j]<min_33y) {
    				min_33y = temp33Y[i][j];
				}
				if (temp33X[i][j]>max_33x) {
    				max_33x = temp33X[i][j];
				}
				if (temp33X[i][j]<min_33x) {
    				min_33x = temp33X[i][j];
				}
				*/				
			}   			     
        }
    }
    
    /*
    // Normalization
    for (i=1; i<H-1; i++){
    	for (j=1; j<W-1; j++){
    		if (temp33Y[i][j] ==0){
    			out_33_Y[i][j] = 128;
			}
			else{
				normal_33y = ((temp33Y[i][j]-min_33y)/(max_33y-min_33y))*255;
				//printf("%f\n",normal_33h);
				temp1 = normal_33y/1;
				//printf("%d\n",temp1);
				out_33_Y[i][j] = temp1;
			}
			
			if (temp33X[i][j] ==0){
    			out_33_X[i][j] = 128;
			}
			else{					
				normal_33x = ((temp33X[i][j]-min_33x)/(max_33x-min_33x))*255;
				//printf("%f\n",normal_33h);
				temp1 = normal_33x/1;
				//printf("%d\n",temp1);
				out_33_X[i][j] = temp1;
			}  		
		}
	}
    */
    
	// For 5*5 filters
    for (i=0; i<H; i++) {
        for (j=0; j<W; j++) {
        	
        	// Skip 2 lines (the filter is not fully inside the image)
            if (i==0 || i==1 || i==H-1 || i== H-2 || j==0 || j==1 || j==W-1 || j==W-2){
            	out_55_Y[i][j] = 128;
            	out_55_X[i][j] = 128;
			}
			
			// Do convolution when the whole filter moves inside the image
			else {
				temp_55Y=0;
				temp_55X=0;
				
				// Convolution
				for (k=0; k<5; k++){										
					for (l=0; l<5; l++){						
						temp_55y = filt55_180y[k][l]*img[i-2+k][j-2+l];
						temp_55Y += temp_55y;						
						temp_55x = filt55_180x[k][l]*img[i-2+k][j-2+l];
						temp_55X += temp_55x;
					}
				}	
				
				out_55_Y[i][j] = temp_55Y/30/2 + 128;
            	out_55_X[i][j] = temp_55X/30/2 + 128;
				
				/*							
				//temp55Y[i][j] = temp_55Y; 		
				//temp55X[i][j] = temp_55X; 
								
				// Find the Max and Min value (to perform normalization later)				
				if (temp55Y[i][j]>max_55y) {
    				max_55y = temp55Y[i][j];
				}
				if (temp55Y[i][j]<min_55y) {
    				min_55y = temp55Y[i][j];
				}
				if (temp55X[i][j]>max_55x) {
    				max_55x = temp55X[i][j];
				}
				if (temp55X[i][j]<min_55x) {
    				min_55x = temp55X[i][j];
				}
				*/				
			}       
        }
    }
	/*    
    // Normalization
 	for (i=2; i<H-2; i++){
    	for (j=2; j<W-2; j++){
    		if (temp55Y[i][j] ==0){
    			out_55_Y[i][j] = 128;
			}
			else{
				normal_55y = ((temp55Y[i][j]-min_55y)/(max_55y-min_55y))*255;
				//printf("%f\n",normal_33y);
				temp1 = normal_55y/1;
				//printf("%d\n",temp1);
				out_55_Y[i][j] = temp1;				
			} 
			
			if (temp55X[i][j] ==0){
    			out_55_X[i][j] = 128;
			}
			else{
				normal_55x = ((temp55X[i][j]-min_55x)/(max_55x-min_55x))*255;
				//printf("%f\n",normal_33y);
				temp1 = normal_55x/1;
				//printf("%d\n",temp1);
				out_55_X[i][j] = temp1;
			}
		}
	}
	*/	
	// Output
    file_33_Y = fopen("Gy33.raw","wb");
    fwrite(out_33_Y, 1, DATASIZE, file_33_Y);
    fclose(file_33_Y);

    file_33_X = fopen("Gx33.raw","wb");
    fwrite(out_33_X, 1, DATASIZE, file_33_X);
    fclose(file_33_X);

    file_55_Y = fopen("Gy55.raw","wb");
    fwrite(out_55_Y, 1, DATASIZE, file_55_Y);
    fclose(file_55_Y);

    file_55_X = fopen("Gx55.raw","wb");
    fwrite(out_55_X, 1, DATASIZE, file_55_X);
    fclose(file_55_X);
   
    return 0;
}
