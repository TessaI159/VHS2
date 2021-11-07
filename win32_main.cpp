#include <opencv2/opencv.hpp>
#include <vector>
#include <stdint.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

struct Pixel
{
  uint8 Red;
  uint8 Blue;
  uint8 Green;
  uint64 ID;
  uint8 OwnedByVectorID;
};

void ScanImage(std::string filename, std::vector<Pixel> *PixelVector)
{
  cv::Mat Image = cv::imread(filename);
  if(!Image.data)
    {
      exit(0);
    }
  PixelVector->clear();
  int ID = -1;

  int Rows = Image.rows;
  int Cols = Image.cols;
  int Pitch = Image.cols * Image.elemSize();
  

  uint8 *Row = (uint8 *)Image.data;

  for(int Y = 0; Y < Rows; ++Y)
    {
      uint8 *PixelPtr = Row;
      for(int X = 0; X < Cols; ++X)
	{
	  Pixel TempPixel;
	  TempPixel.Blue = *PixelPtr++;
	  TempPixel.Green = *PixelPtr++;
	  TempPixel.Red = *PixelPtr++;
	  TempPixel.ID = ++ID;
	  PixelVector->push_back(TempPixel);
	}
      Row += Pitch;
    }
}

int main(int argc, char* args[])
{
  std::vector<Pixel> PixelVector;

  ScanImage("Pride.png", &PixelVector);
  return(0);
}
