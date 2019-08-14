# Step 2:

- Create a label file CSV

```bash
python at.py /home/kevin/OpenCV/Face_recognition/Create_database/Img
```

- Model training

```bash
./train at.csv
```
You will get three files in the current folder.    
`MyFaceFisherModel.xml`、`MyFaceLBPHModel.xml`、`MyFacePCAModel.xml`

Note:    
- If your OpenCV version is before 3.3.0, you should change `Ptr<BasicFaceRecognizer> model0 = EigenFaceRecognizer::create();` to `Ptr<BasicFaceRecognizer> model =  createEigenFaceRecognizer();`    
If you want to know the reason, you can refer to my [blog](https://godliuyang.wang/2019/08/10/face-recognition-with-opencv/#toc-heading-8).
