#include <opencv2/opencv.hpp>
#include <vector>
#include <stdint.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

#define internal static
#define local_persist static
#define global_variable static

struct Pixel
{
  uint8 Red;
  uint8 Green;
  uint8 Blue;
  int ID;
  uint8 OwnedByVectorID;
};

struct PixelBuffer
{
  int Width;
  int Height;
  int Pitch;
  int BytesPerPixel;
  void *Memory;
};

int CalculatePixelPosition(int, int, int);

void ScanImage(std::string filename, PixelBuffer *PixelBuffer)
{
  cv::Mat Image = cv::imread(filename);
  if(!Image.data)
    {
      exit(0);
    }

  if(PixelBuffer->Memory)
    {
      free(PixelBuffer->Memory);
    }

  int ImageWidth = Image.cols;
  int ImageHeight = Image.rows;
  int ImageBytesPerPixel = Image.elemSize();
  int ImagePitch = ImageWidth * ImageBytesPerPixel;

  PixelBuffer->Height = Image.rows;
  PixelBuffer->Width = Image.cols;
  PixelBuffer->BytesPerPixel = sizeof(Pixel);
  PixelBuffer->Pitch = PixelBuffer->Width*PixelBuffer->BytesPerPixel;
  PixelBuffer->Memory = malloc(PixelBuffer->Width*PixelBuffer->Height*PixelBuffer->BytesPerPixel);

  int ID = -1;

  uint8 *ImageRow = (uint8 *)Image.data;
  uint8 *BufferRow = (uint8 *)PixelBuffer->Memory;

  for(int Y = 0; Y < ImageHeight; ++Y)
    {
      uint8 *PixelRead = ImageRow;
      Pixel *PixelWrite = (Pixel *)BufferRow;
      for(int X = 0; X < ImageWidth; ++X)
	{
	  Pixel TempPixel = {0};
	  TempPixel.Blue = *PixelRead++;
	  TempPixel.Green = *PixelRead++;
	  TempPixel.Red = *PixelRead++;
	  TempPixel.ID = ++ID;
	  TempPixel.OwnedByVectorID = 0;

	  *PixelWrite = TempPixel;
	  ++PixelWrite;
	}
      BufferRow += PixelBuffer->Pitch;
      ImageRow += ImagePitch;
    }
}

int CalculatePixelPosition(int X, int Y, int W)
{
  return (Y*(W + 1) + X);
}

int main(int argc, char* args[])
{
  PixelBuffer Buffer = {0};
  ScanImage("Pride.png", &Buffer);
  Pixel * Test = (Pixel *)Buffer.Memory;
  // NOTE (Tess): Should be R0, G121, B64
  Test += CalculatePixelPosition(392, 724, Buffer.Width);
  return(0);
}
