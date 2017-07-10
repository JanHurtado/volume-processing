/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
//
// This example shows how to use the DiffusionTensor3DReconstructionImageFilter
// to reconstruct an image of tensors from Diffusion weighted images. See the
// documentation of DiffusionTensor3DReconstructionImageFilter,
// TensorRelativeAnisotropyImageFilter, TensorFractionalAnisotropyImageFilter
// first.
//
// The example takes diffusion weighted images in the Nrrd format, writes out
// the gradient and reference images for the users reference and computes and
// writes out the Fractional Anisotropy and Relative Anisotropy images.
//
// The easiest way to get started is to try out the filter on a sample dataset.
//
// Acquiring sample datasets:
//  1. Get the DWI datasets from
//        ftp://public.kitware.com/pub/namic/DTI/Data/dwi.nhdr
//        ftp://public.kitware.com/pub/namic/DTI/Data/dwi.img.gz (gunzip this)
//     These datasets contain a reference T1 image and 30 diffusion weighted
//     images. See the nrrd header for details such as B value etc..
//
//  2. Run the example with the following args
//       dwi.nhdr 80 Tensors.mhd FractionalAnisotropy.mhd RelativeAnisotropy.mhd 1
//
//  3. You should find 30 gradient images, 1 reference image, the FA and RA images
//     in your working directory, which you can fire up in your favourite volume
//     browser.
//
// This work is part of the National Alliance for Medical Image
// Computing (NAMIC), funded by the National Institutes of Health
// through the NIH Roadmap for Medical Research, Grant U54 EB005149.
//
// Additional documentation: For details on the Nrrd format for DTI, see
// http://wiki.na-mic.org/Wiki/index.php/NAMIC_Wiki:DTI:Nrrd_format
//
#include "itkDiffusionTensor3DReconstructionImageFilter.h"
#include "itkTensorFractionalAnisotropyImageFilter.h"
#include "itkTensorRelativeAnisotropyImageFilter.h"
#include "itkNrrdImageIO.h"
#include "itkImageSeriesReader.h"
#include "itkImageFileWriter.h"
#include "itkImageRegionIterator.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "error";
		return EXIT_FAILURE;
	}
	const unsigned int Dimension = 3;
	unsigned int numberOfImages = 0;
	unsigned int numberOfGradientImages = 0;
	bool readb0 = false;
	double b0 = 0;
	typedef unsigned short                      PixelType;
	typedef itk::VectorImage<unsigned short, 3> ImageType;
	itk::ImageFileReader<ImageType>::Pointer reader
		= itk::ImageFileReader<ImageType>::New();
	ImageType::Pointer img;
	// Set the properties for NrrdReader
	reader->SetFileName(argv[1]);
	// Read in the nrrd data. The file contains the reference image and the gradient
	// images.
	try
	{
		reader->Update();
		img = reader->GetOutput();
		cout << "done" << endl;
	}
	catch (itk::ExceptionObject &ex)
	{
		std::cout << ex << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}