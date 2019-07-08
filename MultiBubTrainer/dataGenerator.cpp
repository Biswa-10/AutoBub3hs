#include <opencv2/opencv.hpp>
#include <cstdlib> 
#include <bits/stdc++.h> 
#include <iostream> 
#include <sys/stat.h> 
#include <sys/types.h> 

using namespace std;
#define canvasSize 50

int findClosestBounary(int x,int y){
    int l1=x>y?y:x;
    int l2=(canvasSize-x)>(canvasSize-y)?(canvasSize -y):(canvasSize-x);
    return l1>l2?l2:l1;
}

cv::Mat generateOneCircle(cv::Mat input){
    int xCoord, yCoord,radius=0;
    while(radius<canvasSize/3){
        xCoord = rand()%(canvasSize-1) +1;
        yCoord = rand()%(canvasSize-1) +1;
        int closestBoundary =findClosestBounary(xCoord,yCoord);
        radius = rand()%closestBoundary+1;
    }
    cout<<xCoord<<" "<<yCoord<<" "<<radius<<endl;
    circle(input,cv::Point(xCoord,yCoord),radius,255,-1);
    return input;

}

cv::Mat generateTwoCircles(cv::Mat input){
    int xCoord1,yCoord1, radius1=0;
    while(radius1<canvasSize/4){

        xCoord1 = rand()%(canvasSize-1) +1;
        yCoord1 = rand()%(canvasSize-1) +1;

        int closestBoundary =findClosestBounary(xCoord1,yCoord1);
        radius1 = rand()%closestBoundary+1;
    }
    int xCoord2,yCoord2,radius2;

    int flag = 0,countOuter =0;

    while(flag == 0 && countOuter<10){

        int rad_difference = rand()%5;
        int offset = rad_difference-2;
        radius2 = radius1+offset;
        int countInner =0;

        while(radius2>0 && countInner<30 && flag == 0){

            xCoord2 = rand()%(canvasSize-1) +1;
            yCoord2 = rand()%(canvasSize-1) +1;

            double dist = sqrt((xCoord1-xCoord2)*(xCoord1-xCoord2)+(yCoord1-yCoord2)*(yCoord1-yCoord2));

            if(dist<=(radius1+radius2) && (findClosestBounary(xCoord2,yCoord2)-radius2)>=0 && dist>abs(radius1-radius2)&&dist>radius1/2){
                flag =1;
                break;
            }
            countInner++;
        }
        countOuter++;
    }
    if(flag == 0)
        input = generateTwoCircles(input);
    else{
        circle(input,cv::Point(xCoord1,yCoord1),radius1,255,-1);
        circle(input,cv::Point(xCoord2,yCoord2),radius2,255,-1);
    }
    return input;

}

cv::Mat generateThreeCircles(cv::Mat input){
    int xCoord1,yCoord1,radius1=0;
    while(radius1<canvasSize/5)
    {
        xCoord1 = rand()%(canvasSize-1) +1;
        yCoord1 = rand()%(canvasSize-1) +1;
        int closestBoundary =findClosestBounary(xCoord1,yCoord1);
        radius1 = rand()%closestBoundary+1;
    }
    int xCoord2,yCoord2,radius2;
    int xCoord3,yCoord3,radius3;

    int flag = 0,countOuter =0;

    while(flag == 0 && countOuter<10){

        int rad_difference12 = rand()%3;
        int rad_difference31 = rand()%3;

        int offset12 = rad_difference12-1;
        int offset31 = rad_difference31-1;

        radius2 = radius1+offset12;
        radius3 = radius1+offset31;

        int countInner =0;

        while(radius2>0 && radius3>0 && countInner<30 && flag == 0){

            xCoord2 = rand()%(canvasSize-1) +1;
            yCoord2 = rand()%(canvasSize-1) +1;
            
            
            double dist12 = sqrt((xCoord1-xCoord2)*(xCoord1-xCoord2)+(yCoord1-yCoord2)*(yCoord1-yCoord2));
            int flag1=0;
            if(dist12<=(radius1+radius2) && (findClosestBounary(xCoord2,yCoord2)-radius2)>=0 && dist12>abs(radius1-radius2) && dist12>radius1/2){
                int count3 =0;
                while (count3<20){
                    xCoord3 = rand()%(canvasSize-1) +1;
                    yCoord3 = rand()%(canvasSize-1) +1;
                
                    double dist31 = sqrt((xCoord1-xCoord3)*(xCoord1-xCoord3)+(yCoord1-yCoord3)*(yCoord1-yCoord3));
                    double dist23 = sqrt((xCoord3-xCoord2)*(xCoord3-xCoord2)+(yCoord3-yCoord2)*(yCoord3-yCoord2));
                    if(dist31<=(radius1+radius3) && (findClosestBounary(xCoord3,yCoord3)-radius3)>=0 && dist31>3*abs(radius1-radius3) && dist23>3*abs(radius2-radius3) 
                           && dist31>dist12 && dist23>dist12){
                        flag =1;
                        break;
                    }
                }
            }
            countInner++;
        }
        countOuter++;
    }
    if(flag == 0)
        input = generateTwoCircles(input);
    else{
        circle(input,cv::Point(xCoord1,yCoord1),radius1,255,-1);
        circle(input,cv::Point(xCoord2,yCoord2),radius2,255,-1);
        circle(input,cv::Point(xCoord3,yCoord3),radius3,255,-1);
    }
    return input;
}

int main()
{
    

    if (mkdir("1Circle", 0777) == -1) 
        cerr << "Error :  " << strerror(errno) << endl; 

    if (mkdir("2Circle", 0777) == -1) 
        cerr << "Error :  " << strerror(errno) << endl; 
  
    if (mkdir("3Circle", 0777) == -1) 
        cerr << "Error :  " << strerror(errno) << endl; 
    else
        cout << "Directory created"; 
        
    for(int i = 0 ;i<10000 ; i++){

        std::string dir1 = "./1Circle/"+to_string(i)+".jpg";
        std::string dir2 = "./2Circle/"+to_string(i)+".jpg";
        std::string dir3 = "./3Circle/"+to_string(i)+".jpg";
        
        //circle(generated,cv::Point(25,25),25,255,-1);

        cv::Mat c1 = cv::Mat::zeros(cv::Size(canvasSize,canvasSize), CV_8UC1);
        c1 = generateOneCircle(c1);
        distanceTransform(c1, c1, CV_DIST_L1, 3);
        normalize(c1, c1, 0, 1.0, CV_MINMAX);
        imwrite(dir1,c1*255);

        cv::Mat c2 = cv::Mat::zeros(cv::Size(canvasSize,canvasSize), CV_8UC1);
        c2 = generateTwoCircles(c2);
        distanceTransform(c2, c2, CV_DIST_L1, 3);
        normalize(c2, c2, 0, 1.0, CV_MINMAX);
        imwrite(dir2,c2*255);

        cv::Mat c3 = cv::Mat::zeros(cv::Size(canvasSize,canvasSize), CV_8UC1);
        c3 = generateTwoCircles(c3);
        distanceTransform(c3, c3, CV_DIST_L1, 3);
        normalize(c3, c3, 0, 1.0, CV_MINMAX);
        imwrite(dir3,c3*255);


        //imshow("gen ",c3);
        
        //cvWaitKey(1000);
    }

}