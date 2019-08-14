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

