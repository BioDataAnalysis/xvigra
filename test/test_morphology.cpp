/************************************************************************/
/*                                                                      */
/*     Copyright 2017-2018 by Ullrich Koethe                            */
/*                                                                      */
/*    This file is part of the XVIGRA image analysis library.           */
/*                                                                      */
/*    Permission is hereby granted, free of charge, to any person       */
/*    obtaining a copy of this software and associated documentation    */
/*    files (the "Software"), to deal in the Software without           */
/*    restriction, including without limitation the rights to use,      */
/*    copy, modify, merge, publish, distribute, sublicense, and/or      */
/*    sell copies of the Software, and to permit persons to whom the    */
/*    Software is furnished to do so, subject to the following          */
/*    conditions:                                                       */
/*                                                                      */
/*    The above copyright notice and this permission notice shall be    */
/*    included in all copies or substantial portions of the             */
/*    Software.                                                         */
/*                                                                      */
/*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND    */
/*    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES   */
/*    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND          */
/*    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT       */
/*    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,      */
/*    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING      */
/*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR     */
/*    OTHER DEALINGS IN THE SOFTWARE.                                   */
/*                                                                      */
/************************************************************************/

#include <gtest/gtest.h>
#include <xtensor/xtensor.hpp>
#include <xvigra/morphology.hpp>

xt::xtensor<std::uint8_t, 2> 
    img1 {{0, 1, 1, 1, 1, 1, 0},
          {0, 1, 1, 1, 1, 1, 0},
          {0, 1, 1, 1, 1, 1, 0},
          {0, 1, 1, 1, 1, 1, 0},
          {0, 1, 1, 1, 1, 1, 0},
          {0, 1, 1, 1, 1, 1, 0},
          {0, 1, 1, 1, 1, 1, 0}},
    img2 {{0, 1, 2, 3, 4, 5, 6},
          {0, 1, 2, 3, 4, 5, 6},
          {0, 1, 2, 3, 4, 5, 6},
          {0, 1, 2, 3, 4, 5, 6},
          {0, 1, 2, 3, 4, 5, 6},
          {0, 1, 2, 3, 4, 5, 6},
          {0, 1, 2, 3, 4, 5, 6}};

xt::xtensor<std::uint8_t, 3>
    vol {{{0, 0, 0, 0, 0}, 
          {0, 0, 0, 0, 0},  
          {0, 0, 0, 0, 0},  
          {0, 0, 0, 0, 0},  
          {0, 0, 0, 0, 0}},

         {{0, 0, 0, 0, 0},  
          {0, 1, 1, 1, 0},  
          {0, 1, 1, 1, 0},  
          {0, 1, 1, 1, 0},  
          {0, 0, 0, 0, 0}},
 
         {{0, 0, 0, 0, 0},  
          {0, 1, 1, 1, 0},  
          {0, 1, 1, 1, 0},  
          {0, 1, 1, 1, 0},  
          {0, 0, 0, 0, 0}},

         {{0, 0, 0, 0, 0},  
          {0, 1, 1, 1, 0},  
          {0, 1, 1, 1, 0},  
          {0, 1, 1, 1, 0},  
          {0, 0, 0, 0, 0}},

         {{0, 0, 0, 0, 0}, 
          {0, 0, 0, 0, 0},  
          {0, 0, 0, 0, 0},  
          {0, 0, 0, 0, 0},  
          {0, 0, 0, 0, 0}}};

namespace xvigra 
{
    TEST(morphology, 2d_binary)
    {
		xt::xtensor<std::uint8_t, 2> out(img1.shape()),
		    ref1 {{0, 0, 0, 1, 0, 0, 0},
			      {0, 0, 0, 1, 0, 0, 0},
			      {0, 0, 0, 1, 0, 0, 0},
			      {0, 0, 0, 1, 0, 0, 0},
			      {0, 0, 0, 1, 0, 0, 0},
			      {0, 0, 0, 1, 0, 0, 0},
			      {0, 0, 0, 1, 0, 0, 0}},
			ref2 {{0, 0, 0, 1, 1, 1, 1},
                  {0, 0, 0, 1, 1, 1, 1},
                  {0, 0, 0, 1, 1, 1, 1},
                  {0, 0, 0, 1, 1, 1, 1},
                  {0, 0, 0, 1, 1, 1, 1},
                  {0, 0, 0, 1, 1, 1, 1},
                  {0, 0, 0, 1, 1, 1, 1}};

		binary_erosion(img1, out, 2);
		EXPECT_EQ(out, ref1);
		binary_dilation(out, out, 2);
		EXPECT_EQ(out, img1);
		binary_erosion(img2, out, 2);
		EXPECT_EQ(out, ref2);
		binary_dilation(out, out, 2);
		EXPECT_EQ(out, not_equal(img2, 0));
		binary_opening(img1, out, 2);
		EXPECT_EQ(out, img1);
		binary_opening(ref1, out, 2);
		EXPECT_FALSE(any(out));
		binary_closing(ref1, out, 2);
		EXPECT_EQ(out, ref1);
		binary_closing(img1, out, 2);
		EXPECT_TRUE(all(out));
    }

    TEST(morphology, 3d_binary)
    {
		xt::xtensor<std::uint8_t, 3> out(vol.shape()),
		    ref1 {{{0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0}},

                  {{0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0}},

                  {{0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 1, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0}},

                  {{0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0}},

                  {{0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0}}},

		    ref2 {{{0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0}},

                  {{0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 1, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0}},

                  {{0, 0, 0, 0, 0},
                   {0, 0, 1, 0, 0},
                   {0, 1, 1, 1, 0},
                   {0, 0, 1, 0, 0},
                   {0, 0, 0, 0, 0}},

                  {{0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 1, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0}},

                  {{0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0}}};

		binary_erosion(vol, out, 1);
		EXPECT_EQ(out, ref1);
		binary_dilation(ref1, out, 1);
		EXPECT_EQ(out, ref2);
		binary_dilation(ref1, out, 1.9);
		EXPECT_EQ(out, vol);
    }

} // namespace xvigra