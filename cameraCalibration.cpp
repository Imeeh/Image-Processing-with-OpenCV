void CaptureCalibrationImages()
{
    Mat left, right;                                 //Declare matrices for storing the recieved images
 
    int num = 0;                                    // Variable to increment filename for saving images
 
    ///Reading from cameras sequentially
    CvCapture* capture1 = cvCaptureFromCAM(1);      //Capture stream for left camera
    CvCapture* capture2 = cvCaptureFromCAM(2);      //Capture stream for right camera
     
    if(capture1 && capture2)
    {
        clock_t start = clock();                    //Note current time
        while(true) 
        {
            left = cvQueryFrame(capture1);          //Get frame from left camera
            imshow("left", left);                   //Display frame from left camera
 
            right=cvQueryFrame(capture2);           //Get frame from right camera
            imshow("right", right);                 //Display frame from right camera
 
            ///A rudimentary timer to capture images every 3 seconds.
            clock_t end = clock() - start;                          //Note time elapsed
            double time = (double) end / (double)CLOCKS_PER_SEC;    //Convert time elapsed to seconds
             
            if(time >= 3)
            {
                cout << "Picture number "<< intToString(num) << endl;
                imwrite("CalibrationImages/left" + intToString(num) + ".ppm", left);   //Write left image to disc
                imwrite("CalibrationImages/right" + intToString(num) + ".ppm", right); //Write right image to disc
                num++;                                                                 //Increment file count 
                start = clock();                                                       //Reset the timer (essentially)
            }
 
            int c = waitKey(5);    //Listen for keystroke
            if(c == 'c') break;    //Exit if user presses 'c'
        }
    } else printf("Failure in capture\n");
}
