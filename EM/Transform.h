#pragma once
using namespace System::Drawing;

Bitmap^ ToGrayscale(Bitmap^);
Bitmap^ FastFourierTransform(Bitmap^);
Bitmap^ InvFastFourierTransform(Bitmap^);
Bitmap^ LowPassFilter(Bitmap^);
Bitmap^ HighPassFilter(Bitmap^);
Bitmap^ DiscreteFourierTransform(Bitmap^);
Bitmap^ InvDiscreteFourierTransform(Bitmap^);
