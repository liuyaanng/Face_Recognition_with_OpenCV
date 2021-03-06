# Face_Recognition_with_OpenCV

You can refer to my [blog](https://godliuyang.wang/2019/08/10/face-recognition-with-opencv/) to learn more about the principles and processes.


Given that the configuration is not the same for everyone, I will explain the program where needs to be changed in detail.

- My configuration

  - OpenCV 3.3.0

  - OpenCV_contrib 3.3.0

  - Ubuntu 16.04

You can clone the three branchs to your computer and put them in **a folder**.  Like this:    

```bash
Face_recognition/
├── Create_database
│   ├── CMakeLists.txt
│   ├── creda.cpp
│   ├── haarcascade_frontalface_alt2.xml
│   └── Img
├── Recognition
│   ├── CMakeLists.txt
│   ├── haarcascade_frontalface_alt2.xml
│   └── rec.cpp
└── Train
    ├── at.py
    ├── CMakeLists.txt
    └── train.cpp
```



The first thing you have to do is to go into each  **Step**  folder. And

```bash
cmake .
make
```
You should pay attention to  ** ~ . ~**    
The premise is that you have already installed **'CMake'**.    
Then follow the steps.

Step 1: [Create Your Own Face Database](https://github.com/liuyaanng/Face_Recognition_with_OpenCV/tree/step1-Create_database)    
Step 2: [Train](https://github.com/liuyaanng/Face_Recognition_with_OpenCV/tree/step2-Train)    
Step 3: [Face Recognition](https://github.com/liuyaanng/Face_Recognition_with_OpenCV/tree/step3-Recognition)    
