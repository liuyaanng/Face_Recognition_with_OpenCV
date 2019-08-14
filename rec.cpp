#include <opencv2/opencv.hpp>  
#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
 
using namespace cv;
using namespace cv::face;
using namespace std;
 
#define ROW_MIN		45
 
int exitFlag = 0;

int Recognition_And_Draw();

int Recognition_And_Draw(){
  int ret = 0; //
  double scale = 4; //Zoom factor
  double fx = 1 / scale;
  Mat frame;  //Video frame
  VideoCapture cap(0);    //Open the camera
  if(!cap.isOpened()){
    cout << "Open camera failed.\n" << endl;
    return -1;
  }

  //Load cascade classifier
  CascadeClassifier cascade;
  ret = cascade.load("haarcascade_frontalface_alt2.xml");

  if(!ret){
    printf("Load xml failed[ret = %d]. \n", ret);
    return -1;
  }
  cout << "Load xml succeed." << endl;

  // Loading trained face models
  Ptr<BasicFaceRecognizer> modelPCA = EigenFaceRecognizer::create();  
  modelPCA->read("../Train/MyFacePCAModel.xml");  
  Ptr<BasicFaceRecognizer> modelFisher = FisherFaceRecognizer::create();
  modelFisher->read("../Train/MyFaceFisherModel.xml");  
  Ptr<LBPHFaceRecognizer> modelLBPH = LBPHFaceRecognizer::create();  
  modelLBPH->read("../Train/MyFaceLBPHModel.xml");  

  while(!exitFlag){
    cap >> frame;
    if(frame.empty())
      continue;
  
    Mat facesImg;  //
    vector<Rect> faces;  //
    Mat gary_img; //grayscale image
    Mat scl_gary_img; //Scaled grayscale image
  
    cvtColor(frame, gary_img, COLOR_BGR2GRAY); //Convert the original image to a grayscale image
    resize(gary_img, scl_gary_img, Size(), fx, fx, INTER_LINEAR); //resize img
    equalizeHist( scl_gary_img, scl_gary_img );

  //face detection
    cascade.detectMultiScale(scl_gary_img, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE,Size(30, 30));
    printf("Face.size = %ld\n", faces.size());
  //facesImg = scl_gary_img(faces[0]);
  //
    Mat face_resize;  //To prevent the picture is too small (that is, people too far away from the camera)
    int predictPCA = 0;  
    int predictFisher = 0;  
    int predictLBPH = 0;
    for(size_t i = 0; i < faces.size(); i++){
      
      Rect rectFace = faces[i];
      facesImg = scl_gary_img(faces[i]);
      if(facesImg.rows >= ROW_MIN){
        resize(facesImg, face_resize, Size(92, 112));
      }
      else{
        printf("faceImg.rows[%d] < %d \n", facesImg.rows, ROW_MIN);
        continue;
      }
      if(!face_resize.empty()){
        predictPCA = modelPCA->predict(face_resize);  
        predictFisher = modelFisher->predict(face_resize);  
        predictLBPH = modelLBPH->predict(face_resize); 
      }
      cout << "predictPCA   : " << predictPCA    << endl;
      cout << "predictFisher: " << predictFisher << endl;
      cout << "predictLBPH  : " << predictLBPH   << endl;
      rectangle(frame, Point(rectFace.x, rectFace.y) * scale, Point(rectFace.x + rectFace.width, rectFace.y + rectFace.height) * scale, Scalar(0, 255, 0), 2, 8);
      if (predictPCA == 41){
        putText(frame, "Liuyang", Point(faces[i].x, faces[i].y) * scale, FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
      }
      else{
        putText(frame, "X", Point(faces[i].x, faces[i].y) * scale, FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2);
      }
      
  // if(faces.size() <= 0){
  //  cout << "There are no faces in the camera.\n" << endl;
 // }
    }
    imshow("frame", frame);
      if (waitKey(1) == 27){
			    exitFlag = 1;
			    cout << "Esc..." << endl;
			    break;
      }
  }
}


int main(){
  Recognition_And_Draw();
  return 0;
}

