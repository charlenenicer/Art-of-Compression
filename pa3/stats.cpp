#include "stats.h"


/* returns the sums of all pixel values across all color channels.
 * useful in computing the score of a rectangle
 * PA3 function
 * @param channel is one of r, g, or b
 * @param ul is (x,y) of the upper left corner of the rectangle
 * @param lr is (x,y) of the lower right corner of the rectangle */
long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){
    if(channel == 'r'){
        long redResult = sumRed[lr.second][lr.first];
        if(ul.first>0)
            redResult = redResult - sumRed[lr.second][ul.first-1];
        
        if(ul.second>0)
            redResult = redResult - sumRed[ul.second-1][lr.first];
        
        if((ul.first>0) && (ul.second>0))
            redResult = redResult + sumRed[ul.second-1][ul.first-1];
        
        return redResult;
    }
    
    else if(channel == 'g'){
        long greenResult = sumGreen[lr.second][lr.first];
        
        if(ul.first>0)
            greenResult = greenResult - sumGreen[lr.second][ul.first-1];
        
        if(ul.second>0)
            greenResult = greenResult - sumGreen[ul.second-1][lr.first];
        
        if((ul.first>0) && (ul.second>0))
            greenResult = greenResult + sumGreen[ul.second-1][ul.first-1];
        
        return greenResult;
        
    }
    
    else{
        long blueResult = sumBlue[lr.second][lr.first];
        
        if(ul.first>0)
            blueResult = blueResult - sumBlue[lr.second][ul.first-1];
        
        if(ul.second>0)
            blueResult = blueResult - sumBlue[ul.second-1][lr.first];
        
        if((ul.first>0) && (ul.second>0))
            blueResult = blueResult + sumBlue[ul.second-1][ul.first-1];
        
        return blueResult;
    }
    
}





long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){
    
   

    if(channel == 'r'){
        long redResultsq = sumsqRed[lr.second][lr.first];
        if(ul.first>0)
            redResultsq = redResultsq - sumsqRed[lr.second][ul.first-1];

        if(ul.second>0)
            redResultsq = redResultsq - sumsqRed[ul.second-1][lr.first];
        
        if((ul.first>0) && (ul.second>0))
            redResultsq = redResultsq + sumsqRed[ul.second-1][ul.first-1];
        
        return redResultsq;
    }
    
    else if(channel == 'g'){
        long greenResultsq = sumsqGreen[lr.second][lr.first];
        
        if(ul.first>0)
            greenResultsq = greenResultsq - sumsqGreen[lr.second][ul.first-1];

        if(ul.second>0)
            greenResultsq = greenResultsq - sumsqGreen[ul.second-1][lr.first];
        
        if((ul.first>0) && (ul.second>0))
            greenResultsq = greenResultsq + sumsqGreen[ul.second-1][ul.first-1];
        
        return greenResultsq;
        
    }
    
    else{
        long blueResultsq = sumsqBlue[lr.second][lr.first];
        
        if(ul.first>0)
            blueResultsq = blueResultsq - sumsqBlue[lr.second][ul.first-1];
        
        if(ul.second>0)
            blueResultsq = blueResultsq - sumsqBlue[ul.second-1][lr.first];
        
        if((ul.first>0) && (ul.second>0))
            blueResultsq = blueResultsq + sumsqBlue[ul.second-1][ul.first-1];
        
        return blueResultsq;
    }
    

}

// initialize the private vectors so that, for each color,  entry
// (x,y) is the cumulative sum of the the color values from (0,0)
// to (x,y). Similarly, the sumSq vectors are the cumulative
// sum of squares from (0,0) to (x,y).
stats::stats(PNG & im){
    
    int rows = im.height();
    int columns = im.width();
   
    
    for (int j = 0; j < rows; j++){
        vector<long> tempRed;
        vector<long> tempGreen;
        vector<long> tempBlue;
        vector<long> tempRedsq;
        vector<long> tempGreensq;
        vector<long> tempBluesq;
        
    for(int i = 0; i <columns; i++){
        RGBAPixel* pixel = im.getPixel(i,j);
        tempRed.push_back(pixel->r);
        tempGreen.push_back(pixel->g);
        tempBlue.push_back(pixel->b);
        tempRedsq.push_back((pixel->r)*(pixel->r));
        tempGreensq.push_back((pixel->g)*(pixel->g));
        tempBluesq.push_back((pixel->b)*(pixel->b));
    }
    
    sumRed.push_back(tempRed);
    sumGreen.push_back(tempGreen);
    sumBlue.push_back(tempBlue);
    sumsqRed.push_back(tempRedsq);
    sumsqGreen.push_back(tempGreensq);
    sumsqBlue.push_back(tempBluesq);
    
    }
    
    for(int k = 1; k < rows; k++){
       
        for(int j = 0; j <columns; j++){
            RGBAPixel* pixel = im.getPixel(j,k);
            sumRed[k][j] = pixel->r + sumRed[k-1][j];
            sumGreen[k][j] = pixel->g + sumGreen[k-1][j];
            sumBlue[k][j] = pixel->b + sumBlue[k-1][j];
            sumsqRed[k][j] = (pixel->r)*(pixel->r) + sumsqRed[k-1][j];
            sumsqGreen[k][j] = (pixel->g)*(pixel->g) + sumsqGreen[k-1][j];
            sumsqBlue[k][j] = (pixel->b)*(pixel->b) + sumsqBlue[k-1][j];
        }
    }
    

    for(int k = 0; k < rows; k++){
        for(int j = 1; j <columns; j++){
            sumRed[k][j] += sumRed[k][j-1];
            sumGreen[k][j] += sumGreen[k][j-1];
            sumBlue[k][j] += sumBlue[k][j-1];
            sumsqRed[k][j] += sumsqRed[k][j-1];
            sumsqGreen[k][j] += sumsqGreen[k][j-1];
            sumsqBlue[k][j] += sumsqBlue[k][j-1];
        }
    }

}




// given a rectangle, compute its sum of squared deviations from
// mean, over all color channels. Will be used to make split when
// building tree.
/* @param ul is (x,y) of the upper left corner of the rectangle
 * @param lr is (x,y) of the lower right corner of the rectangle */
long stats::getScore(pair<int,int> ul, pair<int,int> lr){
    long redScore, greenScore, blueScore;
    long area = rectArea(ul,lr);
    
    redScore = getSum('r',ul,lr)*getSum('r',ul,lr);
    greenScore = getSum('g',ul,lr)*getSum('g',ul,lr);
    blueScore = getSum('b',ul,lr)*getSum('b',ul,lr);
    
    redScore = redScore/area;
    greenScore = greenScore/area;
    blueScore = blueScore/area;
    
    redScore = getSumSq('r', ul, lr) - redScore;
    greenScore = getSumSq('g', ul, lr) - greenScore;
    blueScore = getSumSq('b', ul, lr) - blueScore;
    
    
    return redScore + greenScore + blueScore;

}

// given a rectangle, return the average color value over the
// rectangle as a pixel.
/* Each color component of the pixel is the average value of that
 * component over the rectangle.
 * @param ul is (x,y) of the upper left corner of the rectangle
 * @param lr is (x,y) of the lower right corner of the rectangle */
RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){
    long redScore, greenScore, blueScore;
    long area = rectArea(ul,lr);

    redScore = getSum('r', ul, lr);
    greenScore = getSum('g', ul, lr);
    blueScore = getSum('b', ul, lr);
    
    
//    return RGBAPixel(redScore, greenScore, blueScore);
    
    int redScore1 = redScore/area;
    int greenScore1 = greenScore/area;
    int blueScore1 = blueScore/area;
    

    RGBAPixel result = RGBAPixel(redScore1, greenScore1, blueScore1);
    
    
    return result;

}


// given a rectangle, return the number of pixels in the rectangle
/* @param ul is (x,y) of the upper left corner of the rectangle
 * @param lr is (x,y) of the lower right corner of the rectangle */
long stats::rectArea(pair<int,int> ul, pair<int,int> lr){
    int x = lr.first - ul.first +1;
    int y = lr.second - ul.second +1;
  
    long area = x*y;

    return abs(area);
}
