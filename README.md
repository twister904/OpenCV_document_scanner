# Document Scanner with OpenCV

This project utilizes OpenCV for document scanning, contour detection, and image perspective correction.

## Feature Highlights

- Real-time document scanning using a webcam or image file.
- Detection of document contours in the scene.
- Automatic cropping and perspective correction for scanned documents.
- Output the scanned and corrected document as an image file.

## Usage Examples

1. **Running the Application with Webcam**

   - Compile the code using a C++ compiler. Ensure that OpenCV is correctly installed and configured in your development environment.

   - Run the compiled binary.

   ```bash
   ./your-binary-name
Point your webcam at the document you want to scan.

The program will detect the document, apply perspective correction, and display the scanned result.
1. Scanning an Image File

Modify the code to read an image file by providing the file path.
string path = "path/to/your/image.jpg";
imgorig = imread(path);
Recompile the code.

Run the compiled binary to scan the image file and obtain the corrected result.
Installation Guide
To set up this project on your local machine, follow these steps:
git clone https://github.com/twister904/OpenCV_document_scanner.git
Install OpenCV

Ensure you have OpenCV installed and properly configured in your C++ development environment. Refer to the OpenCV documentation for installation instructions.
Compile and Run

Navigate to the project directory.
cd your-repo
Compile the code using your preferred C++ compiler. Ensure that you link the OpenCV libraries correctly.

Run the compiled binary.
./your-binary-name

Scanning Documents

When running the application, point your webcam at a document or specify the path to an image file.

The program will automatically detect and scan the document, correcting any perspective distortion.

Save the Result

The scanned and corrected document will be saved as an image file with the name "scanimg.jpg" in the "Resources" directory of the project.

Feel free to customize and enhance this project as needed. If you encounter any issues or have suggestions for improvement, please open an issue or submit a pull request.

Happy scanning!

Replace `your-username`, `your-repo`, and `your-binary-name` with the actual details related to your GitHub username, repository name, and the name of the binary generated when you compile your C++ code.

