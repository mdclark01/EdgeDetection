//
//  main.cpp
//  LineFinder
//
//  Created by Michael Clark on 2/10/15.
//  Copyright (c) 2015 IUPUI. All rights reserved.
//
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

//************************* Function Prototype **************************//
int getTheFileSize(FILE *theImage);


int main(int argc, const char * argv[]) {
    
//*************************** Setup Overhead ****************************//
    
    //set to 1 to print pixels from 2d array before sobel
    const int debug = 0;
    
    //set mask size to either 5 or 3
    int maskSize = 3; //********* CHANGE THIS TO EITHER 3 OR 5 **********//

    
    const int imgWidth = 500; //Height of image
    int imgHeight;  //width of image calculated from height and size
    int i,j,x,y,sum,sumX,sumY; //counter variables
    FILE *theImage; //create a file pointer

    
//******************************** Start ********************************//
    theImage = fopen("input.raw", "r");  //Open file for reading
    
    if(theImage != NULL){

        
        const int size = getTheFileSize(theImage);
        imgHeight = (size/imgWidth) / 3;
        
        cout << "Image Opened" << endl;
        cout << "Image size = " << size << endl;
        cout << "Image height = " << imgHeight << " Image width =" << imgWidth << endl;

        //create 2d array to hold pixels

        unsigned char imagePixels[size/3][3];
        unsigned char newImagePixels[size/3][3];

        //store on the heap
        //unsigned char** imagePixels = new unsigned char*[size/3];
        //unsigned char** newImagePixels = new unsigned char*[size/3];
        
        //for(int i = 0; i < size/3; ++i){
            //imagePixels[i] = new unsigned char[3];
            //newImagePixels[i] = new unsigned char[3];
        //}


        for(i=0; i<size/3; i++){
            //Hold R Values
            imagePixels[i][0] = fgetc(theImage);
            //Hold G values
            imagePixels[i][1] = fgetc(theImage);
            //Hold B values
            imagePixels[i][2] = fgetc(theImage);
        }

        if(debug == 1){
            for(i=0; i<size/3; i++){
               cout << "[" << imagePixels[i][0] <<","<< imagePixels[i][1] << "," << imagePixels[i][2] <<"]";
            }//end for
        }//end if debug

        //close file we now have a copy on the stack
        fclose(theImage);
        cout << "Image File Closed" << endl;
        
        for (y=0; y<imgHeight; y++) {
            for (x=0; x<imgWidth; x++) {
                sumX = 0;
                sumY = 0;
                
                //3x3 mask size
                if (maskSize == 3) {
                    //set edges of image to RGB 255
                    if (y == 0 || y == imgWidth-1) {
                        sum = 0;
                    }else if (x == 0 || x == imgHeight-1){
                        sum = 0;
                    }else{
                        //apply sobel Algorithm
                        //create 2 2d arrays to hold the mask
                        int mX[3][3];
                        int mY[3][3];
                        
                        //mask for x
                        mX[0][0] = -1; mX[0][1] = 0; mX[0][2] = 1;
                        mX[1][0] = -2; mX[1][1] = 0; mX[1][2] = 2;
                        mX[2][0] = -1; mX[2][1] = 0; mX[2][2] = 1;
                        
                        //mask for y
                        mY[0][0] = -1; mY[0][1] = -2; mY[0][2] = -1;
                        mY[1][0] =  0; mY[1][1] =  0; mY[1][2] =  0;
                        mY[2][0] =  1; mY[2][1] =  2; mY[2][2] =  1;
                        
                        for (i=-1; i<2; i++) {
                            for (j=-1; j<2; j++) {
                                sumX = sumX + imagePixels[x+i+((y+j)*imgWidth)][0] * mX[i+1][j+1];
                                sumY = sumY + imagePixels[x+i+((y+j)*imgWidth)][0] * mY[i+1][j+1];
                            }//end for
                        }//end for
                        
                    }//end if
                }//end if
                
                //5x5 mask size
                if (maskSize == 5) {
                    //set edges of image to RGB 255
                    if (y <= 0 || y >= imgWidth-2) {
                        sum = 0;
                    }else if (x <= 1 || x >= imgHeight-2){
                        sum = 0;
                    }else{
                        //apply sobel Algorithm
                        //create 2 2d arrays to hold the mask
                        int mX[5][5];
                        int mY[5][5];
                        
                        //mask for x
                        mX[0][0] = 1; mX[0][1] =  2; mX[0][2] = 0; mX[0][3] =  -2; mX[0][4] = -1;
                        mX[1][0] = 4; mX[1][1] =  8; mX[1][2] = 0; mX[1][3] =  -8; mX[1][4] = -4;
                        mX[2][0] = 6; mX[2][1] = 12; mX[2][2] = 0; mX[2][3] = -12; mX[2][4] = -6;
                        mX[3][0] = 4; mX[3][1] =  8; mX[3][2] = 0; mX[3][3] =  -8; mX[3][4] = -4;
                        mX[4][0] = 1; mX[4][1] =  2; mX[4][2] = 0; mX[4][3] =  -2; mX[4][4] = -1;
                        
                        //mask for y
                        mY[0][0] = -1; mY[0][1] = -4; mY[0][2] =  -6; mY[0][3] = -4; mY[0][4] = -1;
                        mY[1][0] = -2; mY[1][1] = -8; mY[1][2] = -12; mY[1][3] = -8; mY[1][4] = -2;
                        mY[2][0] =  0; mY[2][1] =  0; mY[2][2] =   0; mY[2][3] =  0; mY[2][4] =  0;
                        mY[3][0] =  2; mY[3][1] =  8; mY[3][2] =  12; mY[3][3] =  8; mY[3][4] =  2;
                        mY[4][0] =  1; mY[4][1] =  4; mY[4][2] =   6; mY[4][3] =  4; mY[4][4] =  1;
                        
                        for (i=-2; i<3; i++) {
                            for (j=-2; j<3; j++) {
                                sumX = sumX + imagePixels[x+i+((y+j)*imgWidth)][0] * mX[i+2][j+2];
                                sumY = sumY + imagePixels[x+i+((y+j)*imgWidth)][0] * mY[i+2][j+2];
                            }//end for
                        }//end for
                        
                    }//end if
                }//end if
                
                
//******** UNCOMMMENT THESE FOR DIFFERENT OPTIONS *******//
//************************* 3x3 *************************//
                //ydiff
//                sum = 128 + (sumY * 128) / 1020; //ydiff
                
                //xdiff
//                sum = 128 + (sumX * 128) / 1020; //xdiff
                
//                gradient
//                sumY = 128 + (sumY * 128) / 1020; //ydiff
//                sumX = 128 + (sumX * 128) / 1020; //xdiff
//                sum = (sumX + sumY)/2; //gradient
                
                
//************************* 5x5 *************************//
                
                //ydiff
//                sum = 128 + (sumY * 128) / 16830;
                
                //xdiff
//                sum = 128 + (sumX * 128) / 16830;
                
////                gradient
//                sumY = 128 + (sumY * 128) / 16830; //ydiff
//                sumX = 128 + (sumX * 128) / 16830; //xdiff
//                sum = (sumX + sumY)/2;

                //Edget Detection
                sum = abs(sumX) + abs(sumY);
              
                if (sum < 0) {
                    sum = 0;
                }else if (sum > 255){
                    sum = 255;
                }
                
                //black color lines are white
                newImagePixels[y+(x*imgWidth)][0] = sum;
                newImagePixels[y+(x*imgWidth)][1] = sum;
                newImagePixels[y+(x*imgWidth)][2] = sum;

                //Invert Colors
//                newImagePixels[y+(x*imgWidth)][0] = 255 - sum;
//                newImagePixels[y+(x*imgWidth)][1] = 255 - sum;
//                newImagePixels[y+(x*imgWidth)][2] = 255 - sum;
                
            }//end for
        }//end for
        
        cout << "Creating new file called output.raw" << endl;
        theImage = fopen("output.raw", "w");  //Open file for reading

        for(y=0;y<imgWidth;y++){
            for(x=0;x<imgHeight;x++){
                fputc(newImagePixels[y+(x*imgWidth)][0], theImage);
                fputc(newImagePixels[y+(x*imgWidth)][1], theImage);
                fputc(newImagePixels[y+(x*imgWidth)][2], theImage);
            }
        }
        fclose(theImage);
        cout << "Closed file output.raw" << endl;
        
    }//end if testing image for null
    
    return 0;
}//end main

//************************* Additional Functions *************************//
int  getTheFileSize(FILE *theImage){
    // start offset from the begging
    int start = ftell(theImage);
    //go to end of the file
    fseek(theImage, 0L, SEEK_END);
    //get the end postion
    int size = ftell(theImage);
    //go back to the start
    fseek(theImage, start, SEEK_SET);

    return size;
}