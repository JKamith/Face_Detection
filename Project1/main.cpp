#include <opencv2/opencv.hpp>

int main() {
    // Load the pre-trained face detection classifier
    cv::CascadeClassifier faceCascade; //CascadeClassifier object named faceCascade is created. It's used to load a pre-trained face detection classifier from an XML file (haarcascade_frontalface_default.xml). If the loading fails, an error message is printed to the standard error stream (std::cerr), and the program exits with a return code of -1.
    if (!faceCascade.load("C:\\Users\\JAMITH KAUR\\Downloads\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading face cascade. Make sure you have the XML file." << std::endl;
        return -1;
    }

    // Open a video capture object (0 represents the default camera)
    cv::VideoCapture cap(0); //A VideoCapture object named cap is created, representing the default camera (camera index 0). If the camera fails to open, an error message is printed, and the program exits with a return code of -1.
    if (!cap.isOpened()) {
        std::cerr << "Error opening camera." << std::endl;
        return -1;
    }

    cv::Mat frame; //A Mat object named frame is declared to store each frame from the video stream. The program enters a continuous loop to capture frames and perform face detection.
    while (true) {
        // Capture a frame from the camera
        cap >> frame;

        // Convert the frame to grayscale (required for face detection)
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Detect faces in the frame
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.3, 5);

        // Draw rectangles around detected faces
        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        }

        // Display the frame
        cv::imshow("Face Detection", frame);

        // Break the loop if the user presses 'ESC'
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    // Release the video capture object
    cap.release();

    // Close all OpenCV windows
    cv::destroyAllWindows();

    return 0;
}
