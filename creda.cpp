#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/face.hpp>
#include <iostream>
#include <fstream>
#include <sstream> 
using namespace cv;
using namespace std;
using namespace cv::face;

#define CV_COLOR_GREEN cv::Scalar(0, 255, 0)

int resize_save(Mat& faceIn, char* path, int  faceseq);
//Input: current image, the path of file, the name or faceseq of images.
//Output: None
//Function: resize the current image to (92, 112), which is same to the train data.
int get_face(char* path);
//Input: the path of file.
//Output: None
//Function: Use face_cascade to detect if there are faces in the window, and save the faces through function reszie_save.


int resize_save(Mat& faceIn, char* path, int  faceseq){
  string strname;
  Mat faceOut;
  bool ret;
  if(faceIn.empty()){
    printf("FaceIn is empty.\n");
    return -1;
  }

  if(faceIn.cols > 100){
    resize(faceIn, faceOut, Size(92, 112));
    //Resize and Keep a match with the train database.
    strname = format("%s/%d.jpg", path, faceseq); //mkdir
    ret = imwrite(strname, faceOut); //save image. Note the file suffix.
    if(ret == false){
      printf("Image write failed!\n");
      printf("Please check filename[%s] is legal!\n", strname.c_str());
      return -1;
    }
    imshow(strname, faceOut);
  }
  waitKey(20);
  return 0;
}

int get_face(char* path){
  CascadeClassifier face_cascade;
  VideoCapture camera;
  int ret;
  Mat frame;  //camera frame
  vector<Rect> objects; //The faces coordinates.
  Mat img_gary; //Gradation pictures.
  Mat faceImg;
  int faceNum = 1; //
  char key;
  camera.open(0);
  if(!camera.isOpened()){
    cout << "Open camera failed." << endl;
    return -1;
  }
  cout << "Open camera succeed. " << endl;

  //Load the face cascadeclassifier.
  ret = face_cascade.load("haarcascade_frontalface_alt2.xml");
  if(!ret){
    cout << "Load xml failed." << endl;
    return -1;
  }
  cout << "Load xml succeed." << endl;
  
  while(1){
    camera >> frame;
    if(frame.empty()){
      continue;
    }
    cvtColor(frame, img_gary, COLOR_BGR2GRAY); //Transform frame as the gradation picture, note imshow is still the original frame.
    equalizeHist(img_gary, img_gary); //Histogram equalization, which is helpful to improve the quality of pictures.

    //Face detection
    face_cascade.detectMultiScale(img_gary, objects, 1.1,3 , 0, Size(50,50));
    for(size_t i = 0; i < objects.size(); i++){
      rectangle(frame, objects[i], CV_COLOR_GREEN);
    }
    imshow("Camera", frame);
    key = waitKey(1);
    switch (key){
      case 'p': //tap 'P' to save.
        if(objects.size() == 1){
          faceImg = frame(objects[0]);
          ret = resize_save(faceImg, path, faceNum);
          if(ret == 0){
            cout << "resize_save succeed.\n" << endl;
            faceNum++;
          }
        }
        break;
      case 27:   //switch to ESC
        cout << "Esc ..." << endl;
        return 0;
      default:
        break;
    }
  }
}


int main(int argc, char* argv[]){
  if(argc != 2)
  	{
		printf("usage: %s <path>\n", argv[0]);
		return -1;
  	}
  get_face(argv[1]);
  return 0;
}
