
// File:        main.cpp
// Author:      cheeren
// Date:        2018-02-25
// Description: Partial test of PA3 functionality
//              Reads Point data from external files
//              Produces PNG images of the point sets


#include "twoDtree.h"
#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"
#include <iostream>
#include "stats.h"

using namespace cs221util;
using namespace std;

int main()
{

//    // read in image
    PNG origIm1;
    origIm1.readFromFile("images/stanley-totem-poles.png");
//    PNG origIm2;
//    origIm2.readFromFile("images/ubc-totem-poles.png");
//    PNG origIm3;
//    origIm3.readFromFile("images/remb.png");
//    PNG origIm4;
//    origIm4.readFromFile("images/rosa.png");

// printf("%u\n", origIm1.width());
// printf("%u\n", origIm1.height());

     stats s = stats(origIm1);

        for (unsigned x=0; x<origIm1.width();x++){
            for (unsigned  y=0;y<origIm1.height();y++){
                cout<< y <<","<<x<<"  :" << s.sumRed[y][x]<<"   ";
                pair<int,int> p1 = {y,x};
                pair<int,int> p2 = {x,y};
                pair<int,int> ori = {0,0};
            //    cout<<"pixel: "<< s.getSum('r',ori,p1)<<endl;
              // if(y == 462 && x == 461){
              //   cout<< y <<","<<x<<"  :" << s.sumsqRed[y][x]<<"   ";
              //   cout<< y <<","<<x<<"  :" << s.sumsqBlue[y][x]<<"   ";
              //   cout<< y <<","<<x<<"  :" << s.sumsqGreen[y][x]<<"   ";
              //   cout<<"get score:  "<<s.getScore(p1,p1) <<endl;
                //
                 cout<<"get scorefrom original:  "<<s.getScore(ori,p2) <<endl;
              //  cout<<endl;

            }
        }


	// use it to build a twoDtree
//       twoDtree t1(test);
//    twoDtree t1(origIm1);
    //twoDtree tCopy1(t1);
//    twoDtree t2(origIm2);
//    twoDtree tCopy2(t2);
//    twoDtree t3(origIm3);
//    twoDtree tCopy3(t3);
//    twoDtree t4(origIm4);
//    twoDtree tCopy4(t4);

	// prune the twoDtree
	//where at least 100*X% of pixels are within Y of mean
//       t1.prune(0.95, 10000);
//    t1.prune(0.95, 10000);
//    tCopy2.prune(0.95, 10000);
//    tCopy3.prune(0.95, 3000);
//    tCopy4.prune(0.95, 3000);
//    t1.prune(0.95, 15000);
//    tCopy2.prune(0.95, 15000);
//    tCopy3.prune(0.95, 3000);
//    tCopy4.prune(0.95, 3000);
//

	// render the twoDtree
//
//      PNG ppic1 = t1.render();
//   PNG ppic1 = t1.render();
//    PNG ppic2 = tCopy2.render();
//    PNG ppic3 = tCopy3.render();
//    PNG ppic4 = tCopy4.render();
//
//  ppic1.writeToFile("images/haha--output_______.png");
//   ppic1.writeToFile("images/prunedstanleytotem.png");
//    ppic2.writeToFile("images/prunedubctotem.png");
//    ppic3.writeToFile("images/prunedremb.png");
//    ppic4.writeToFile("images/prunedrosa.png");

  return 0;
}
