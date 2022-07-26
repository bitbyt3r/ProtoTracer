

#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <omp.h>
#include <set>

#include "Controller.h"
#include "../Render/Camera.h"
#include "../Flash/PixelGroups/HUB75_Parallel.h"
#include "rpi-led-matrix/include/led-matrix-c.h"


class RPI_LED_Matrix_Controller : public Controller {
private:
	CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);

	Transform camTransform = Transform(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));

	PixelGroup cam_1_Pixels = PixelGroup(HUB75_Section_One, 512);
	PixelGroup cam_2_Pixels = PixelGroup(HUB75_Section_Two, 512);
	PixelGroup cam_3_Pixels = PixelGroup(HUB75_Section_Three, 512);
	PixelGroup cam_4_Pixels = PixelGroup(HUB75_Section_Four, 512);
	Camera cam_1 = Camera(&camTransform, &cameraLayout, &cam_1_Pixels);
	Camera cam_2 = Camera(&camTransform, &cameraLayout, &cam_2_Pixels);
	Camera cam_3 = Camera(&camTransform, &cameraLayout, &cam_3_Pixels);
	Camera cam_4 = Camera(&camTransform, &cameraLayout, &cam_4_Pixels);
	;
	Camera *cameras[4] = {
		&cam_1,
		&cam_2,
		&cam_3,
		&cam_4
	};

	struct RGBLedMatrix *matrix;
	struct LedCanvas *backBuffer;
	

public:
	RPI_LED_Matrix_Controller(uint8_t maxBrightness)
		: Controller(cameras, 4, maxBrightness)
	{
	}
	
	~RPI_LED_Matrix_Controller() {

		led_matrix_delete(matrix);
	}

	void Initialize() override {

		struct RGBLedMatrixOptions options;
		struct RGBLedRuntimeOptions runtime;
		
		memset(&options, 0, sizeof(options));
		memset(&runtime, 0, sizeof(runtime));
		
		options.cols = 64;
		options.rows = 32;
		options.chain_length = 2;
		options.hardware_mapping = "adafruit-hat-pwm";
		runtime.gpio_slowdown = 2;

		matrix = led_matrix_create_from_options_and_rt_options(&options, &runtime);
		
		if (matrix == NULL) {
			printf("LED Matrix driver failed to start");
			return;
		}
		led_matrix_set_brightness(matrix, 255);
		backBuffer = led_matrix_create_offscreen_canvas(matrix);
		led_canvas_clear(backBuffer);
		backBuffer = led_matrix_swap_on_vsync(matrix, backBuffer);
	}

	void Display() override {
		for (uint16_t y = 0; y < 8; y++) {
			for (uint16_t x = 0; x < 64; x++) {
				uint16_t pixelNum = y * 64 + x;

				//Panel 1
				led_canvas_set_pixel(backBuffer, x, y, (uint8_t)cam_1_Pixels.GetPixel(pixelNum)->Color.R, (uint8_t)cam_1_Pixels.GetPixel(pixelNum)->Color.G, (uint8_t)cam_1_Pixels.GetPixel(pixelNum)->Color.B);
				led_canvas_set_pixel(backBuffer, x, y + 8, (uint8_t)cam_2_Pixels.GetPixel(pixelNum)->Color.R, (uint8_t)cam_2_Pixels.GetPixel(pixelNum)->Color.G, (uint8_t)cam_2_Pixels.GetPixel(pixelNum)->Color.B);
				led_canvas_set_pixel(backBuffer, x, y + 16, (uint8_t)cam_3_Pixels.GetPixel(pixelNum)->Color.R, (uint8_t)cam_3_Pixels.GetPixel(pixelNum)->Color.G, (uint8_t)cam_3_Pixels.GetPixel(pixelNum)->Color.B);
				led_canvas_set_pixel(backBuffer, x, y + 24, (uint8_t)cam_4_Pixels.GetPixel(pixelNum)->Color.R, (uint8_t)cam_4_Pixels.GetPixel(pixelNum)->Color.G, (uint8_t)cam_4_Pixels.GetPixel(pixelNum)->Color.B);
				
				//Panel 2
				led_canvas_set_pixel(backBuffer, 64 + x, y, (uint8_t)cam_1_Pixels.GetPixel(pixelNum)->Color.R, (uint8_t)cam_1_Pixels.GetPixel(pixelNum)->Color.G, (uint8_t)cam_1_Pixels.GetPixel(pixelNum)->Color.B);
				led_canvas_set_pixel(backBuffer, 64 + x, y + 8, (uint8_t)cam_2_Pixels.GetPixel(pixelNum)->Color.R, (uint8_t)cam_2_Pixels.GetPixel(pixelNum)->Color.G, (uint8_t)cam_2_Pixels.GetPixel(pixelNum)->Color.B);
				led_canvas_set_pixel(backBuffer, 64 + x, y + 16, (uint8_t)cam_3_Pixels.GetPixel(pixelNum)->Color.R, (uint8_t)cam_3_Pixels.GetPixel(pixelNum)->Color.G, (uint8_t)cam_3_Pixels.GetPixel(pixelNum)->Color.B);
				led_canvas_set_pixel(backBuffer, 64 + x, y + 24, (uint8_t)cam_4_Pixels.GetPixel(pixelNum)->Color.R, (uint8_t)cam_4_Pixels.GetPixel(pixelNum)->Color.G, (uint8_t)cam_4_Pixels.GetPixel(pixelNum)->Color.B);
			}
		}
#pragma omp critical(swap_buffers)
		backBuffer = led_matrix_swap_on_vsync(matrix, backBuffer);
	
	}
};
