Mat left, right;
///Reading from cameras sequentially
CvCapture* capture1 = cvCaptureFromCAM(1);
CvCapture* capture2 = cvCaptureFromCAM(2);
if(capture1 && capture2)
{
    while(true)
    {
        left = cvQueryFrame(capture1);
        imshow("left", left);
 
        right=cvQueryFrame(capture2);
        imshow("right", right);
 
        int c = waitKey(5);
        if(c == 'c')
            break;
    }
} else
    printf("Failure in capture\n");
 
///Reading from cameras in parallel
parallel_invoke(
    [&left]()
    {
        CvCapture* capture1 = cvCaptureFromCAM(1);
        while(true)
        {
            left = cvQueryFrame(capture1);
            if(!left.empty())
                imshow("left", left);
            int c = waitKey(5);
            if(c=='c') break;
        }
    },
    [&right]()
    {
        CvCapture* capture2 = cvCaptureFromCAM(2);
        while(true)
        {
            right=cvQueryFrame(capture2);
            if(!right.empty())
                imshow("right", right);
            int c = waitKey(5);
            if(c=='c')
                break;
        }
    }
);
